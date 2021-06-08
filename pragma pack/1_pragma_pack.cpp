//source: https://docs.microsoft.com/en-us/cpp/preprocessor/pack?view=msvc-160

#include <stddef.h>
#include <stdio.h>

struct S {
   int i;       // size 4
   short j;     // size 2
   double k;    // size 8
};

#pragma pack(2)
struct T {
   int i;
   short j;
   double k;
};

int main() {
   printf("%zu ", offsetof(S, i));
   printf("%zu ", offsetof(S, j));
   printf("%zu\n", offsetof(S, k));

   printf("%zu ", offsetof(T, i));
   printf("%zu ", offsetof(T, j));
   printf("%zu\n", offsetof(T, k));
}