#include <fstream>
#include <new>
using namespace std;

#include "classNewDelete.h"

unsigned char MemBlock::_pool[MAX_POOL_SIZE *sizeof(MemBlock)];
//one byte for every block 
unsigned char MemBlock::_alloc_map[MAX_POOL_SIZE] = {0};

ofstream local_out("MemBlock.out"); //log file


MemBlock::MemBlock()
{ local_out << "MemBlock()\n"; }

MemBlock::~MemBlock()
{ local_out << "~MemBlock() ... "; }

// Size is ignored -- assume a Framis object
void* MemBlock::operator new(size_t)
{
	//search through the allocation map looking for a zero byte, 
	//then sets that byte to one to indicate it’s been allocated 
	//and returns the address of that particular block.
	//If it can’t find any memory, it issues a message and returns zero 
	for(int i = 0; i < MAX_POOL_SIZE; i++)
	{
		if(!_alloc_map[i]) 
		{
			local_out << "using block " << i << " ... ";
			_alloc_map[i] = 1; // Mark it used
			return _pool + (i * sizeof(MemBlock));
		}
	}
	local_out << "out of memory" << endl;
	return NULL;
}

//The operator delete assumes the Framis address was created in the pool
void MemBlock::operator delete(void* ptr) 
{
	//calculates which block in the pool this pointer represents, 
	//and then sets the allocation map’s flag for that block to zero 
	//to indicate the block has been released. 

	if(!ptr){ 
		return; // Check for null pointer
	}
	// Assume it was created in the pool
	// Calculate which block number it is:
	unsigned long block = (unsigned long)ptr - (unsigned long)_pool;
	block /= sizeof(MemBlock);
	local_out << "freeing block " << block << endl;
	// Mark it free:
	_alloc_map[block] = 0;
}


////////////////////////////////////////////////

//In main( ), enough Framis objects are dynamically allocated to run out of memory; 
//this checks the out-of-memory behavior. Then one of the objects is freed, 
//and another one is created to show that the released memory is reused. 

int main_class() 
{
	//The pool of memory for the Framis heap is created by allocating 
	//an array of bytes large enough to hold psize Framis objects. 
	MemBlock* f[MemBlock::MAX_POOL_SIZE];
	for(int i = 0; i < MemBlock::MAX_POOL_SIZE; i++){
		f[i] = new MemBlock;
	}

	local_out<<"------------------\n";

	new MemBlock; // Out of memory

	local_out<<"------------------\n";

	delete f[10];
	f[10] = 0;

	local_out<<"------------------\n";

	// Use released memory:
	MemBlock* x = new MemBlock;

	local_out<<"------------------\n";

	delete x;

	local_out<<"------------------\n";

	for(int j = 0; j < MemBlock::MAX_POOL_SIZE; j++)
	{
		delete f[j]; // Delete f[10] OK
	}

	local_out<<"------------------\n";

	return 0;
}

