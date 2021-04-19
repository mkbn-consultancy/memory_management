#include <iostream>
#include <new>
 
void outOfMemHandler()
{
    std::cout << "[handler] Memory allocation failed, terminating\n";
    std::set_new_handler(nullptr);
}
 
int main()
{
    std::set_new_handler(outOfMemHandler);
    try {
        while (true) {
            new int[100000000ul];
        }
    } catch (const std::bad_alloc& e) {
        std::cout << e.what() << '\n';
    }
}