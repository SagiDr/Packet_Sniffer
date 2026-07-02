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
    if (raw_socket < 0) {
        return 1;
    }

    printf("Raw socket created successfully.\n");

    /** @brief Buffer to hold the incoming packet data (Max size: 65536 bytes) */
    unsigned char buffer[65536]; 
    struct sockaddr saddr;
    socklen_t saddr_len = sizeof(saddr);

    while(1) {
        int data_size = recv(raw_socket, buffer, sizeof(buffer),0);
        if(data_size < 0) {
            perror("Recvfrom error");
            close(raw_socket);
            return 1;
        }

        printf("Received packet: %d bytes\n", data_size);
    }

    close(raw_socket);
    return 0;
}