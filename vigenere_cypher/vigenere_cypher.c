#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    char *fname, *keyword, *vector;
    char message[1000], msg[1000], messageText[1000];
    char key[1000], vec[1000];
    char cypher[1000], cypherText[1000];
    int i, j, p, q, index;
    int msgLen, keyLen;
    int pad, cypherLen;

    // Check for the correct number of command-line arguments.
    if (argc != 4) {
        printf("Usage: %s <message_file> <keyword> <vector>\n", argv[0]);
        return 1;
    }

    // Respectively set variable parameters equal to input arguments.
    fname = argv[1];
    keyword = argv[2];
    vector = argv[3];

    printf("Vigenere Cypher - Cipher Block Chaining\n\n");
    printf("Message File Name: %s\n", fname);
    printf("Vigenere Keyword: %s\n", keyword);
    printf("Initialization Vector: %s\n\n", vector);

    FILE *file = fopen(fname, "r");
    if (file == NULL) {
        perror("Error opening message file");
        return 1;
    }

    // Initialize arrays and variables.
    memset(message, 0, sizeof(message));
    memset(msg, 0, sizeof(msg));
    memset(messageText, 0, sizeof(messageText));
    memset(key, 0, sizeof(key));
    memset(vec, 0, sizeof(vec));
    memset(cypher, 0, sizeof(cypher));
    memset(cypherText, 0, sizeof(cypherText));
    index = 0;

    // Read and concatenate words from the message file.
    while (fscanf(file, "%s", msg) != EOF) {
        strcat(message, msg);
    }
    fclose(file);

    // Store the original message length and print it.
    msgLen = strlen(message);
    printf("Original Message Length = %d\n\n", msgLen);
    for (i = 0; i < msgLen; i++) {
        printf("%c", message[i]);
        if ((i + 1) % 50 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");

    // Remove all non-alphabetic characters from the original message and convert to lowercase.
    for (i = 0; i < msgLen; i++) {
        if (isalpha(message[i])) {
            messageText[index++] = tolower(message[i]);
        }
    }

    // Update the message length after cleaning it.
    msgLen = strlen(messageText);
    printf("Clean Message Length = %d\n\n", msgLen);
    for (i = 0; i < msgLen; i++) {
        printf("%c", messageText[i]);
        if ((i + 1) % 50 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");

    // Set keyword length.
    keyLen = strlen(keyword);
    printf("Block size from keyword length = %d\n", keyLen);

    // Calculate the number of characters to be padded.
    pad = keyLen - (msgLen % keyLen);
    printf("\nNumber of characters to be padded = %d\n\n", pad);

    // Obtain the new length for the padded message.
    cypherLen = msgLen + pad;
    printf("Cleaned message length with padding = %d\n\n", cypherLen);

    // Add 'x' as padding to the end of the alphanumeric message.
    for (i = msgLen; i < cypherLen; i++) {
        messageText[i] = 'x';
    }

    for (i = 0; i < cypherLen; i++) {
        printf("%c", messageText[i]);
        if ((i + 1) % 50 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");

    // Initialize the vector to an array equal to the keyword length.
    for (i = 0; i < keyLen; i++) {
        vec[i] = vector[i];
    }

    // Capture the keyword into an array equal to cypherLen.
    i = 0;
    for (j = 0; j < cypherLen; j++) {
        if (i == keyLen) {
            i = 0;
        }
        key[j] = keyword[i];
        i++;
    }

    // Print the vector and keyword arrays.
    printf("Vector Array:\n\n");
    for (i = 0; i < keyLen; i++) {
        printf("%c", vec[i]);
    }
    printf("\n\n");

    printf("Keyword Array:\n\n");
    for (i = 0; i < cypherLen; i++) {
        printf("%c", key[i]);
        if ((i + 1) % 50 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");

    // Encryption step.
    p = 0;
    index = 0;

    for (i = 0; i < cypherLen; i++) {
        cypher[i] = ((((int)messageText[i] - 'a') + ((int)vec[p] - 'a')) % 26) + 'a';
        p++;

        if ((p % keyLen) == 0) {
            q = p;
            for (j = index; j < p; j++) {
                cypherText[j] = ((((int)cypher[j] - 'a') + ((int)key[j] - 'a')) % 26) + 'a';
                vec[q] = cypherText[j];
                q++;
            }
            index = p;
        }
    }

    // Print out the encrypted message cypher.
    printf("Encrypted Vigenere Cipher:\n\n");
    for (i = 0; i < cypherLen; i++) {
        printf("%c", cypherText[i]);
        if ((i + 1) % 50 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");

    // Decryption step.
    p = 0;
    index = 0;

    for (i = 0; i < cypherLen; i++) {
        int temp = ((int)cypher[i] - 'a') - ((int)vec[p] - 'a');
        if (temp < 0) {
            temp += 26;
        }
        messageText[i] = (temp % 26) + 'a';
        p++;

        if ((p % keyLen) == 0) {
            q = p;
            for (j = index; j < p; j++) {
                int temp2 = ((int)cypherText[j] - 'a') - ((int)key[j] - 'a');
                if (temp2 < 0) {
                    temp2 += 26;
                }
                messageText[j] = (temp2 % 26) + 'a';
                vec[q] = cypherText[j];
                q++;
            }
            index = p;
        }
    }

    // Print out the decrypted message.
    printf("Decrypted Message:\n\n");
    for (i = 0; i < cypherLen; i++) {
        printf("%c", messageText[i]);
        if ((i + 1) % 50 == 0) {
            printf("\n");
        }
    }
    printf("\n\n");

    return 0;
}
