// Run the program from terminal with these commands:

// gcc -Wall -o vigenere_cypher vigenere_cypher.c
// ./vigenere_cypher message.txt key vector

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  char *fname, *keyword, *vector;
  char message[10000], msg[10000], alphaNumMsg[10000];
  int i, index, msgLen, keyLen;
  int pad, padAlphaNumMsgLen;

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
       strcat(message, msg);
  fclose(file);

  printf("Message file name: %s\n\n", fname);
  msgLen = strlen(message);
  printf("Message length = %d\n\n", msgLen);

  printf("Original Message text:\n");
  for(i=1; i<=msgLen; i++)
    printf("%c", message[i-1]);
  printf("\n");

  // Clean message.txt into only alphanumeric characters.
  for (i=0; i<msgLen; i++)
    if((int)message[i] >= 65 && (int)message[i] <= 90)
    {
      alphaNumMsg[index] = message[i];
      index++;
    } else if((int)message[i] >= 97 && (int)message[i] <= 122)
      {
        alphaNumMsg[index] = message[i];
        index++;
      }

  // Store new length value of cleaned up message array.
  msgLen = strlen(alphaNumMsg);
  printf("\nCleaned message length = %d\n\n", msgLen);

  // Convert letters to lowercase
  for(i=0; i<msgLen; i++)
    alphaNumMsg[i] = tolower(alphaNumMsg[i]);

  printf("Lowercase alphanumeric message text:\n");
  for(i=1; i<=msgLen; i++)
    printf("%c", alphaNumMsg[i-1]);
  printf("\n");

  // Set length of keyword.
  keyLen = strlen(keyword);

  // Size of padding to be added to the message.
  // https://en.wikipedia.org/wiki/Padding_(cryptography)
  pad = keyLen - (msgLen % keyLen);
  printf("\nNumber of characters to be padded = %d\n\n", pad);

  // Obtain new length for padded message.
  padAlphaNumMsgLen = msgLen + pad;
  printf("Cleaned message length with padding = %d\n", padAlphaNumMsgLen);

  // Add 'x' as the padding to the end of the alpha alphanumeric message.

  return 0;
}
