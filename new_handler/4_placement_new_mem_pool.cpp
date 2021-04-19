#include <iostream>

class Data {
public:
    Data() { std::cout<<"[Data] default ctor\n"; }
    ~Data() { std::cout<<"[Data] destructor\n"; }
    int x;
};

int main(){
    void* pMemPool = malloc(256);
    void* pNextAlloc = pMemPool ;

    Data* pData = new (pNextAlloc) Data;
    
    pNextAlloc = (char*)(pNextAlloc) + sizeof(Data);

    // Writing to it
    pData->x = 10;
    // Destroying c
    pData->~Data();
    
    pNextAlloc = (char*)(pNextAlloc) - sizeof(Data); 
    
    free(pMemPool); 
    pMemPool=NULL; 
    pNextAlloc=NULL;
}
