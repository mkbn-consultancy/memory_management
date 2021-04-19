#include <iostream>

class X 
{ 
	int i; 
public: 
	X(int ii = 0) : i(ii) { std::cout<<"X::X(int)\n";} 
	~X() { std::cout << "X::~X()\n"; } 

	void* operator new(size_t, void* loc) { 
        std::cout<<"[placement new] allocating on address "<<loc<<std::endl;
        return loc; 
    } 
};

int main() 
{ 
	int vec[10]{};
    std::cout<<"[main] address of vec: "<<vec<<"\n"; 
    std::cout<<"[main] allocating an X object on the vector's memory:\n"; 
	X* xp = new(vec) X(7); // X at location vec 
    std::cout<<"[main] only call the dtor for the object X:\n";
	xp->X::~X(); 	// Explicit destructor call 
				// ONLY use with placement!
	return 0; 
} 
