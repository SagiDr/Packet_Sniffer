#include "payload.h"
#include <stdio.h>

void print_payload(const unsigned char *data, int size) {
    if (size <= 0) {
        printf("Payload: None\n");
        return;
    }

    printf("\nPayload (%d bytes):\n", size);
    
    // --- Print HEX block ---
    printf("\nPayload (HEX)\n");
    for (int i = 0; i < size; i++) {
        printf("%02X ", data[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n"); // Newline every 16 bytes for readability
        }
    }
    
    // add a final newline if the last row wasn't exactly 16 bytes
    if (size % 16 != 0) {
        printf("\n");
    }

    // --- Print ASCII block ---
    printf("\nPayload (ASCII)\n");
    for (int i = 0; i < size; i++) {
        unsigned char c = data[i];
        
        // Print printable characters, including standard newlines (for HTTP)
        if ((c >= 32 && c <= 126) || c == '\n' || c == '\r') {
            printf("%c", c);
        } else {
            // Replace non-printable characters with a dot
            printf(".");
        }
    }
    printf("\n");
}
