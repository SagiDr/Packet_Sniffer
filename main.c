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
#include "frame_parse.h"
#include "ipv4_parse.h"
#include "transport_parse.h"
#include "icmp_parse.h"
#include "payload.h"

/**
 * @brief Restarts the raw socket connection.
 * 
 * Closes the existing socket and attempts to create a new one.
 * 
 * @param old_socket The file descriptor of the socket that failed.
 * @return int Returns the new socket file descriptor.
 */
int restart_server(int old_socket) {
    if (old_socket >= 0) {
        close(old_socket);
    }
    
    printf("Attempting to restart socket...\n");
    return create_raw_socket();
}

/**
 * @brief Main function to run the packet sniffer.
 * 
 * Initializes the raw socket and enters an infinite loop to receive packets.
 * If an error occurs, it prompts the user to either retry or exit the application.
 * 
 * @return int Returns 0 on successful termination, or 1 on error.
 */
int main() {
    int raw_socket = create_raw_socket();
    char choice;

    // Handle failure on initial socket creation
    while (raw_socket < 0) {
        perror("Initial socket creation failed");
        
        printf("Do you want to retry? (r = retry, e = exit): ");
        scanf(" %c", &choice);
        
        if (choice == 'r' || choice == 'R') {
            raw_socket = restart_server(raw_socket);
        } else {
            printf("Exiting sniffer...\n");
            return 1;
        }
    }

    printf("Raw socket created successfully.\n");

    /** @brief Buffer to hold the incoming packet data (Max size: 65536 bytes) */
    unsigned char buffer[65536]; 

    unsigned int packet_counter =1;

    while(1) {
        int data_size = recv(raw_socket, buffer, sizeof(buffer), 0);
        
        if(data_size < 0) {
            perror("Recvfrom error");
            
            printf("Connection error. Do you want to restart the socket? (r = restart, e = exit): ");
            scanf(" %c", &choice);
            
            if (choice == 'r' || choice == 'R') {
                raw_socket = restart_server(raw_socket);
                
                if (raw_socket >= 0) {
                    printf("Socket restarted successfully. Resuming capture...\n");
                }
                continue; 
            } else {
                printf("Closing server and exiting sniffer...\n");
                break; // Exit the loop to terminate the program
            }
        }

        printf("\nPacket #%u\n", packet_counter);
        packet_counter++;
        int offset = 0; 
        uint16_t eth_type = parse_ethertype(buffer,&offset);
        if (eth_type == 0x0806) {
        parse_arp(buffer, offset);
} 
        else if (eth_type == 0x0800) {
        uint8_t protocol = parse_ipv4(buffer, &offset);
    
        // Call the appropriate transport layer parser based on the protocol
        if (protocol == 1) {             
                parse_icmp(buffer, &offset); // call the ICMP parser
            } else if (protocol == 6) {
                parse_tcp(buffer, &offset, data_size);// call the TCP parser
            } else if (protocol == 17) {
                parse_udp(buffer, &offset, data_size);// call the UDP parser
            }

            // Print the payload if it exists
            if (data_size > offset) {
                print_payload(buffer + offset, data_size - offset);
            } else {
                printf("\nPayload: None\n");
            }
        }

}
    // Ensure the socket is properly closed before exiting
    if (raw_socket >= 0) {
        close(raw_socket);
    }
    return 0;
}