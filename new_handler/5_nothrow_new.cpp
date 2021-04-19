#include <iostream>

void new_bad_alloc()
{
	std::cout << "Attempting to allocate a very big mem block..."; 
    try {
        while (true) {
            new int[100000000ul];
        }
    } catch (const std::bad_alloc& e) {
        std::cout << "[main] exception: "<< e.what() << '\n';
    }
    catch(...){
        std::cout<<"[main] exception: Unkown Exception\n";
    }
}

void new_noexcept()
{
	std::cout << "Attempting to allocate a very big mem block..."; 
    int* p;
    while (true) {
        p = new (std::nothrow) int[100000000ul];
        if (p==0){ 
            std::cout << "Failed!\n"; 
            return;
        }
        else { 
            std::cout << "Success!\n"; 
        } 
    }
}

int main () 
{ 
    new_bad_alloc();
    new_noexcept();
	return 0; 
}
