#include <fstream>
#include <new>
#include <iostream>
using namespace std;

#include "classNewDelete.h"

unsigned char MemBlock::_pool[MAX_POOL_SIZE *sizeof(MemBlock)];
//one byte for every block 
unsigned char MemBlock::_alloc_map[MAX_POOL_SIZE] = {0};

ofstream local_out("MemBlock.out"); //log file


MemBlock::MemBlock()
{ local_out << "[ctor] MemBlock()\n"; }

MemBlock::~MemBlock()
{ local_out << "[dtor] ~MemBlock() ... "; }

// Size is ignored -- assume a Framis object
void* MemBlock::operator new(size_t)
{
	//search through the allocation map looking for a zero byte, 
	//then sets that byte to one to indicate it�s been allocated 
	//and returns the address of that particular block.
	//If it can�t find any memory, it issues a message and returns zero 
	void* result = nullptr;
	for(int i = 0; i < MAX_POOL_SIZE && !result; i++)
	{
		if(!_alloc_map[i]) 
		{
			local_out << "[new] using block " << i << " ... ";
			_alloc_map[i] = 1; // Mark it used
			result = _pool + (i * sizeof(MemBlock));
		}
	}
	if(!result){
		local_out << "[new] out of memory" << endl;
	}
	return result;
}

//The operator delete assumes the Framis address was created in the pool
void MemBlock::operator delete(void* ptr) noexcept
{
	//calculates which block in the pool this pointer represents, 
	//and then sets the allocation map�s flag for that block to zero 
	//to indicate the block has been released. 

	if(!ptr){ 
		return; // Check for null pointer
	}
	// Assume it was created in the pool
	// Calculate which block number it is:
	unsigned long block = (unsigned char*)ptr - _pool;
	// local_out<<block<<std::endl;
	block /= sizeof(MemBlock);
	local_out << "[delete] freeing block " << block << endl;
	// Mark it free:
	_alloc_map[block] = 0;
}


////////////////////////////////////////////////

//In main( ), enough MemBlock objects are dynamically allocated to run out of memory; 
//this checks the out-of-memory behavior. Then one of the objects is freed, 
//and another one is created to show that the released memory is reused. 

int main() 
{
	std::cout<<"[main] started... output written to file...";
	//The pool of memory for the Framis heap is created by allocating 
	//an array of bytes large enough to hold psize Framis objects. 
	local_out<<"[main] creating an array f of Memoblock*:\n";
	MemBlock* f[MemBlock::MAX_POOL_SIZE];
	local_out<<"[main] allocating "<<MemBlock::MAX_POOL_SIZE<<" blocks to the array from the pool:\n";
	for(int i = 0; i < MemBlock::MAX_POOL_SIZE; i++){
		f[i] = new MemBlock;
	}

	local_out<<"------------------\n";
	local_out<<"[main] trying to allocate another block:\n";
	new MemBlock; // Out of memory

	local_out<<"------------------\n";
	local_out<<"[main] deleting a block from the pool:\n";
	delete f[10];
	f[10] = 0;

	local_out<<"------------------\n";

	// Use released memory:
	local_out<<"[main] trying to allocate another block:\n";
	MemBlock* x = new MemBlock;

	local_out<<"------------------\n";
	local_out<<"[main] delete the latest allocated block:\n";
	delete x;

	local_out<<"------------------\n";

	local_out<<"[main] deleting all blocks in the array f:\n";
	for(int j = 0; j < MemBlock::MAX_POOL_SIZE; j++)
	{
		delete f[j]; // Delete f[10] OK
	}

	local_out<<"------------------\n";

	std::cout<<"done!\n";
	return 0;
}

