#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  char *fname, *keyword, *vector;
  char msg[10000], text[10000], alphaText[10000];
  int i, index, msgLen;
  // Respectively set variable parameters equal to input arguments.
  fname = argv[1];
  keyword = argv[2];
  vector = argv[3];

  printf("Cipher Block Chaining Vigenere\n");
  printf("Vigenere keyword: %s\n", keyword);
  printf("Initialization vector: %s\n\n", vector);

  // Open message.txt and store in text array.
  FILE *file = fopen(fname, "r" );
  if (file)
      while (fscanf(file, "%s", msg)!=EOF)
       strcat(text, msg);
  fclose(file);

  printf("Plaintext file name: %s\n", fname);
  // msgLen = strlen(msg);
  // printf("Message length = %d\n", msgLen);
  msgLen = strlen(text);
  printf("Message length = %d\n", msgLen);

  // Clean message.txt into only alphanumeric characters.
  for (i=0; i<msgLen; i++)
    if((int)text[i] >= 65 && (int)text[i] <= 90)
    {
      alphaText[index] = text[i];
      index++;
    } else if((int)text[i] >= 97 && (int)text[i] <= 122)
      {
        alphaText[index] = text[i];
        index++;
      }

  msgLen = strlen(alphaText);
  printf("Cleaned message length = %d\n\n", msgLen);

  printf("Clean plaintext:\n");
  for(i=1; i<=msgLen; i++)
    printf("%c", alphaText[i-1]);
  printf("\n");

  return 0;
}

// gcc vigenere_cypher.c -Wall
// ./a.out message.txt key vector
