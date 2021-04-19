#include <iostream>

void my_new_handler() 
{ 
	std::cout << "[handler] new handler called" << std::endl; 
} 

class NoMemory 
{ 
public: 
	NoMemory(){ std::cout << "NoMemory::NoMemory()" << std::endl; }
 
	void* operator new(size_t sz) noexcept
	{ 
		std::cout << "NoMemory::operator new" << std::endl;
 		// throw std::bad_alloc(); // "Out of memory" 
		//return malloc(sz);
        return NULL;
	} 
}; 

int main() 
{ 
	std::set_new_handler(my_new_handler); 

	try{
		NoMemory* pNM = new NoMemory; 
		std::cout << "pNM = " << pNM << std::endl; 
	}
	catch(std::bad_alloc& e){
		std::cout<<"[main]: "<<e.what()<<std::endl;
	}

	return 0;
}
