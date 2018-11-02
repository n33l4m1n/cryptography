// Pointers in the C language.

#include<stdio.h>
#include<stdlib.h>

int main()
{
  int i;
  int *num = malloc(sizeof(int) * 1000);
  for(i=0; i<1000; i++)
  {
  num[i] = i;
  }

  //num[0] = 3;
  //num[1] = 2;
  //num[2] = 1;

  //printf("%p -> %d\n", num, *num );
  //printf("%p -> %d\n", num+1, *(num+1) );
  //printf("%p -> %d\n", num+2, *(num+2) );

  for(i=0; i<1000; i++)
  {
  printf("%p -> %d\n", num+i, *(num+i) );
  }

  return 0;
}
