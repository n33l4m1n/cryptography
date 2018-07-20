#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  char *fname, *keyword, *vector;
  char msg[5000], text[5000];
  int msgLen;
  // Respectively set variable parameters equal to input arguments.
  fname = argv[1];
  keyword = argv[2];
  vector = argv[3];

  printf("Cipher Block Chaining Vigenere\n");
  printf("Plaintext file name: %s\n", fname);
  printf("Vigenere keyword: %s\n", keyword);
  printf("Initialization vector: %s\n\n", vector);
  printf("Clean plaintext:\n\n");

  // Open message.txt and store in text array.
  FILE *file = fopen(fname, "r" );
  if (file)
      while (fscanf(file, "%s", msg)!=EOF)
       strcat(text, msg);
  fclose(file);

  msgLen = strlen(msg);
  printf("Message length = %d\n", msgLen);
  msgLen = strlen(text);
  printf("Message length = %d\n", msgLen);

  return 0;
}
