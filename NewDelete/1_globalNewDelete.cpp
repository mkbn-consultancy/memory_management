#include <cstdio>
#include <cstdlib>
using namespace std;

void* operator new(size_t sz) 
{
  printf("[new] operator new: %d Bytes\n", sz);
  void* m = malloc(sz);
  if(!m) puts("[new] out of memory");
  return m;
}

void* operator new[](size_t sz) 
{
  printf("[new[]] operator new: %d Bytes\n", sz);
  void* m = malloc(sz);
  if(!m) puts("[new[]] out of memory");
  return m;
}

void operator delete(void* m) noexcept
{
  puts("[delete] operator delete");
  free(m);
}

void operator delete[](void* m) noexcept
{
  puts("[delete[]] operator delete");
  free(m);
}

void operator delete[](void* m, std::size_t sz) noexcept
{
  printf("[delete[],size_t] operator delete, size = %d\n",sz);
  free(m);
}

class S 
{
  int i[100]; //400 bytes
public:
  S() { puts("[class S] S::S()"); }
  ~S() { puts("[class S] S::~S()"); }
};

int main() 
{
  puts("[main] creating & destroying an int");
  int* p = new int;
  delete p;
  puts("[main] creating & destroying an array int[3]");
  int* pArr = new int[3];
  delete[] pArr;
  puts("[main] creating & destroying an s");
  S* s = new S;
  delete s;
  puts("[main] creating & destroying S[3]");
  S* sa = new S[3];
  delete[] sa;
  puts("[main] main finished");

  return 0;
} 