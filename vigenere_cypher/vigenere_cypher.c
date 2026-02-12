// Vigenere Cipher with Cipher Block Chaining (CBC) - Encryption
//
// Reads a message file, strips non-alpha characters, pads to block size,
// and encrypts using CBC-mode Vigenere. The keyword length determines the
// block size. Each plaintext block is XOR'd (mod 26 addition) with the
// previous ciphertext block (or IV), then the Vigenere key is applied.
//
// Run the program from terminal with these commands:
//
// gcc -Wall -o vigenere_cypher vigenere_cypher.c
// ./vigenere_cypher message.txt keyword vect
//
// Known issues / TODO:
//   - 'message' array is uninitialized before strcat (undefined behavior).
//   - 'index' variable is uninitialized before first use (undefined behavior).
//   - Print loops access arr[-1] when i==0 (off-by-one / undefined behavior).
//   - fclose() is called outside the fopen-success check (UB if fopen fails).
//   - No argc validation; fewer than 4 args causes a segfault.
//   - fscanf "%s" has no width limit; long tokens overflow the buffer.
//   - messageText is never null-terminated after filtering.
//   - Lowercase loop iterates over original msgLen, not filtered length.
//   - Padding adds a full block of 'x' when message is already aligned,
//     which is ambiguous since 'x' is indistinguishable from plaintext.
//   - vec[] is written past keyLen in CBC loop (works by accident due to
//     buffer size, but is fragile and unconventional).
//   - Fixed 1000-byte buffers; could use malloc for dynamic sizing.
//   - No decryption routine.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  char *fname, *keyword, *vector;
  char message[1000], msg[1000], messageText[1000];
  char key[1000], vec[1000];
  char cypher[1000], cypherText[1000];
  int i, j, p, q, index;
  int msgLen, keyLen;
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
  for(i = 0; i <= msgLen; i++)
  {
    printf("%c", message[i-1]);
    if (i % 50 == 0 && i != 0)
      printf("\n");
  }
  printf("\n\n");

  // Remove all symbols from original message, keep only letters.
  // BUG: 'index' is uninitialized here; should be set to 0.
  // BUG: Using magic numbers 65/90/97/122 instead of 'A'/'Z'/'a'/'z'.
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
  // BUG: Should iterate over filtered length (index), not original msgLen.
  // BUG: messageText is not null-terminated after the filtering loop above.
  for(i = 0; i < msgLen; i++)
    messageText[i] = tolower(messageText[i]);

  // Update length value to reflect cleaned up message and print new array.
  msgLen = strlen(messageText);
  printf("\nClean Message Length = %d\n\n", msgLen);
  for(i = 0; i <= msgLen; i++)
  {
    printf("%c", messageText[i-1]);
    if (i % 50 == 0 && i != 0)
      printf("\n");
  }
  printf("\n\n");

  // Set keyword length.
  keyLen = strlen(keyword);
  printf("Block size from keyword length = %d\n", keyLen);

  // Size of padding to be added to the message.
  // https://en.wikipedia.org/wiki/Padding_(cryptography)
  pad = keyLen - (msgLen % keyLen);
  printf("\nNumber of characters to be padded = %d\n\n", pad);

  // Obtain new length for padded message.
  cypherLen = msgLen + pad;
  printf("Cleaned message length with padding = %d\n\n", cypherLen);

  // Add 'x' as the padding to the end of the alpha alphanumeric message.
  for(i = msgLen; i < cypherLen; i++)
    messageText[i] = 'x';

  for(i = 0; i <= cypherLen; i++)
  {
    printf("%c", messageText[i-1]);
    if (i % 50 == 0 && i != 0)
      printf("\n");
  }
  printf("\n\n");

  // Initialize vector to an array equal to the keyword length.
  for(i = 0; i < keyLen; i++)
    vec[i] = vector[i];

  // Capture keyword into an array equal to cypher length.
  i = 0;
  for(j = 0; j < cypherLen; j++)
  {
      // IF statement repeats keyword over entire array.
      if(i == keyLen)
          i = 0;

      key[j] = keyword[i];
      i++;
  }

  // NOTE: Vector array print has the same off-by-one bug as other loops.
  printf("Vector Array:\n\n");
  for(i = 0; i <= keyLen; i++)
    printf("%c", vec[i-1]);
  printf("\n\n");

  // Keyword array should repeat keyword to cypherLen.
  printf("Keyword Array:\n\n");
  for(i = 0; i <= cypherLen; i++)
  {
    printf("%c", key[i-1]);
    if (i % 50 == 0 && i != 0)
      printf("\n");
  }
  printf("\n\n");


  // Encryption step.
  p = 0;
  index = 0;

  for(i = 0; i < cypherLen; i++)
  {
    cypher[i] = ((((int)messageText[i]-'a')+((int)vec[p]-'a'))%26)+'a';
    p++;

    if((p % keyLen) == 0)
    {
      q = p;
      for(j = index; j < p; j++)
      {
        cypherText[j] = ((((int)cypher[j]-'a') + ((int)key[j]-'a'))%26)+'a';
        vec[q] = cypherText[j];
        q++;
      }
      index = p;
    }
  }

  // Print out encrypted message cypher.
  printf("Encrypted Vigenere Cypher:\n\n");
  for(i = 0; i <= cypherLen; i++)
  {
    printf("%c", cypherText[i-1]);
    if (i % 50 == 0 && i != 0)
      printf("\n");
  }
  printf("\n\n");

  return 0;
}
