#include <iostream>

struct alignas(8) data
{
    int a; 
    int b; 
    int c;
};

struct alignas(4) foo 
{ 
    int a; 
    int b; 
    int c;
}; 

struct bar 
{ 
    alignas(2) char a; 
    alignas(8) int  b; 
}; 

int main(){
    alignas(8)   int a; 
    alignas(256) long b[4];
    auto align = alignof(foo);

    data rArr[2];
    std::cout<<"[data:] alignment: "<<alignof(data)<<" sizeof: "<<sizeof(data)<<std::endl;
    // char* p0 = (char*)&rArr[0], *p1 = (char*)&rArr[1];
    // std::cout<<&(rArr[0])<<", "<<&(rArr[1])<<" => "<<p1-p0<<std::endl;
  
    foo fArr[2];
    std::cout<<"[foo: ] alignment: "<<alignof(foo)<<" sizeof: "<<sizeof(foo)<<std::endl;
    // p0 = (char*)&rArr[0], p1 = (char*)&rArr[1];
    // std::cout<<&(fArr[0])<<", "<<&(fArr[1])<<" => "<<p1-p0<<std::endl;

    bar bArr[2];
    std::cout<<"[bar: ] alignment: "<<alignof(bar)<<" sizeof: "<<sizeof(bar)<<std::endl;
    // p0 = (char*)&bArr[0], p1 = (char*)&bArr[1];
    // std::cout<<&(bArr[0])<<", "<<&(bArr[1])<<" => "<<p1-p0<<std::endl;
}

