// Pointers in the C language.

#include<stdio.h>
#include<stdlib.h>

int main() 
{
  int *num = malloc(sizeof(int) * 3);
  num[0] = 3;
  num[1] = 2;
  num[2] = 1;

  printf("%p -> %d\n", num, *num );
  printf("%p -> %d\n", num+1, *(num+1) );
  printf("%p -> %d\n", num+2, *(num+2) );

  return 0;
}
