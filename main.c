/**
 * @file main.c
 * @brief Main entry point for the Packet Sniffer application.
 * 
 * This program utilizes a raw socket to continuously capture packets 
 * from the network interface and displays their size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include "create_socket.h"
/**
 * @brief Restarts the raw socket connection.
 * 
 * Closes the existing socket and attempts to create a new one.
 * Includes a brief delay to prevent CPU exhaustion in case of continuous failures.
 * 
 * @param old_socket The file descriptor of the socket that failed.
 * @return int Returns the new socket file descriptor.
 */
int restart_server(int old_socket) {
    if (old_socket >= 0) {
        close(old_socket);
    }
    
    printf("Attempting to restart socket...\n");
    // 1-second delay to prevent CPU exhaustion if the error persists
    sleep(1); 
    
    return create_raw_socket();
}

/**
 * @brief Main function to run the packet sniffer.
 * 
 * Initializes the raw socket and enters an infinite loop to receive packets.
 * It allocates a buffer for the maximum possible packet size and prints
 * the number of bytes received for each packet.
 * 
 * @return int Returns 0 on successful termination, or 1 on error.
 */
int main() {
    int raw_socket = create_raw_socket();
    // If initial creation fails, attempt to recover immediately
    while (raw_socket < 0) {
        perror("Initial socket creation failed");
        raw_socket = restart_server(raw_socket);
    }

    printf("Raw socket created successfully.\n");

    /** @brief Buffer to hold the incoming packet data (Max size: 65536 bytes) */
    unsigned char buffer[65536]; 

    while(1) {
        int data_size = recv(raw_socket, buffer, sizeof(buffer),0);
        if(data_size < 0) {
            perror("Recvfrom error");
            // Recovery attempt: update the current socket with the newly created one
            raw_socket = restart_server(raw_socket); 
            // Check if the new socket was created successfully; if not, retry
            if (raw_socket >= 0) {
                printf("Socket restarted successfully. Resuming capture...\n");
            }
            // Skip the rest of the loop and return to the start for a new read attempt
            continue;
        }
        printf("Received packet: %d bytes\n", data_size);
    }
    close(raw_socket);
    return 0;
}