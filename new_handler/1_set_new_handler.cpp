#include <iostream>
#include <new>

struct MyMemException
{
};

void outOfMemHandler()
{
    std::cout << "\n[handler] Memory allocation failed, terminating\n";
    // std::set_new_handler(nullptr);
    throw MyMemException();
}
 
int main()
{
    std::set_new_handler(outOfMemHandler);
    try {
        while (true) {
            std::cout<<"*-";
            new int[100000000ul];
        }
    } catch (const std::bad_alloc& e) {
        std::cout << e.what() << '\n';
    }
    catch(const MyMemException& e){
        std::cout<<"inside MyMemException catch\n";
    }
}