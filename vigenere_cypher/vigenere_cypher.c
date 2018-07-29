// Run the program from terminal with these commands:

// gcc -Wall -o vigenere_cypher vigenere_cypher.c
// ./vigenere_cypher message.txt key vector

// Note: Program can be more dynamic if arrays are malloc'd.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  char *fname, *keyword, *vector;
  char message[10000], msg[10000], messageText[10000];
  char key[27], vec[27];
  int i, index, msgLen, keyLen;
  int pad, cypherLen;

  // Respectively set variable parameters equal to input arguments.
  fname = argv[1];
  keyword = argv[2];
  vector = argv[3];

  printf("Vigenere Cypher - Cipher Block Chaining\n\n");
  printf("Message File Name: %s\n", fname);
  printf("Vigenere Keyword: %s\n", keyword);
  printf("Initialization Vector: %s\n\n", vector);

  // Open message file and concatenate string into an array.
  FILE *file = fopen(fname, "r" );
  if (file)
  {
      while (fscanf(file, "%s", msg)!=EOF)
        strcat(message, msg);
  }
  fclose(file);

  // Store original length and print message array.
  msgLen = strlen(message);
  printf("Original Message Length = %d\n\n", msgLen);
  for(i = 1; i <= msgLen; i++)
  {
    printf("%c", message[i-1]);
    if (i % 50 == 0 && i != 0)
      printf("\n");
  }
  printf("\n\n");

  // Remove all symbols from original message, keep only letters.
  for (i = 0; i < msgLen; i++)
    if((int)message[i] >= 65 && (int)message[i] <= 90)
    {
      messageText[index] = message[i];
      index++;
    }
    else if((int)message[i] >= 97 && (int)message[i] <= 122)
    {
      messageText[index] = message[i];
      index++;
    }

  // Convert all letters in clean message to lowercase.
  for(i = 0; i < msgLen; i++)
    messageText[i] = tolower(messageText[i]);

  // Update length value to reflect cleaned up message and print new array.
  msgLen = strlen(messageText);
  printf("\nClean Message Length = %d\n\n", msgLen);
  for(i = 1; i <= msgLen; i++)
  {
    printf("%c", messageText[i-1]);
    if (i % 50 == 0 && i != 0)
      printf("\n");
  }
  printf("\n\n");

  // // Set keyword length.
  // keyLen = strlen(keyword);
  //
  // // Size of padding to be added to the message.
  // // https://en.wikipedia.org/wiki/Padding_(cryptography)
  // pad = keyLen - (msgLen % keyLen);
  // printf("\nNumber of characters to be padded = %d\n\n", pad);
  //
  // // Obtain new length for padded message.
  // padAlphaNumMsgLen = msgLen + pad;
  // printf("Cleaned message length with padding = %d\n\n", padAlphaNumMsgLen);
  //
  // // Add 'x' as the padding to the end of the alpha alphanumeric message.
  // for(i = msgLen; i < padAlphaNumMsgLen; i++)
  //   alphaNumMsg[i] = 'x';
  //
  // printf("Lowercase alphanumeric message text with padding:\n");
  // for(i = 0; i <= padAlphaNumMsgLen; i++)
  //   printf("%c", alphaNumMsg[i-1]);
  // printf("\n");

  return 0;
}
