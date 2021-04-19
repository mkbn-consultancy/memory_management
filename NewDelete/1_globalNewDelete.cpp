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

void operator delete(void* m) 
{
  puts("[delete] operator delete");
  free(m);
}

void operator delete[](void* m) 
{
  puts("[delete[]] operator delete");
  free(m);
}

class S 
{
  int i[100];
public:
  S() { puts("[class S] S::S()"); }
  ~S() { puts("[class S] S::~S()"); }
};

int main() 
{
  puts("[main] creating & destroying an int");
  int* p = new int(47);
  delete p;
  puts("[main] creating & destroying an s");
  S* s = new S;
  delete s;
  puts("[main] creating & destroying S[3]");
  S* sa = new S[3];
  delete []sa;
  puts("[main] main finished");

  return 0;
} 