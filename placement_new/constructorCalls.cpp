#include <iostream>
using namespace std;

void my_new_handler() 
{
  cout << "new handler called" << endl;
}

class NoMemory 
{
public:
  NoMemory() 
  {
    cout << "NoMemory::NoMemory()" << endl;
  }
  void* operator new(size_t sz) throw(bad_alloc)
  {
    cout << "NoMemory::operator new" << endl;
    //throw bad_alloc(); // "Out of memory"
	return 0;
  }
};

void OutOfMem()
{
	std::cerr<<"Failed to allocate memory\n";
	std::abort();
}

int main()
{
	std::set_new_handler(OutOfMem);
	int* pBigDataArray = new int[499999999L];
	//…
}
/*
int mai1n() 
{

  set_new_handler(my_new_handler);
  
  NoMemory* pNM = new NoMemory;
  cout << "pNM = " << pNM << endl;

  return 0;
}

*/