// Pointers in the C language.

#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;
    
    // Allocate memory for an array of 1000 integers and store a pointer to it in 'num'.
    int *num = malloc(sizeof(int) * 1000);
    
    // Check if memory allocation was successful.
    if (num == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Initialize the array with values from 0 to 999.
    for (i = 0; i < 1000; i++) {
        num[i] = i;
    }

    // Print the addresses and values of the elements in the array.
    for (i = 0; i < 1000; i++) {
        printf("%p -> %d\n", (void *)(num + i), num[i]);
    }

    // Free the allocated memory to prevent memory leaks.
    free(num);

    return 0;
}
