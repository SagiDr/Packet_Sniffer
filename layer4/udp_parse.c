#include "transport_parse.h"
#include "application_parse.h"
#include <stdio.h>
#include <arpa/inet.h>

void parse_udp(const unsigned char *buffer, int *offset,int data_size) {
    const struct udp_header *udp = (const struct udp_header *)(buffer + *offset);

    printf("\nLayer 4: Transport\n");
    printf("Protocol: UDP\n");
    printf("Source Port: %u\n", ntohs(udp->src_port));
    printf("Dest Port: %u\n", ntohs(udp->dest_port));
    printf("Length: %u\n", ntohs(udp->length));// Length of the UDP header and data
    printf("Checksum: %u\n", ntohs(udp->checksum));

    // Calculate the pointer to the payload and its length
    int header_size = 8;
    const unsigned char *payload = buffer + *offset + header_size;
    int payload_length = data_size - (*offset + header_size);


    // Call the application layer parser with the payload details
    parse_application(ntohs(udp->src_port), ntohs(udp->dest_port), payload, payload_length > 0 ? payload_length : 0);

    *offset += 8; // UDP header is always 8 bytes
}