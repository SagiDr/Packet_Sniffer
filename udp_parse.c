#include "transport_parse.h"
#include <stdio.h>
#include <arpa/inet.h>

void parse_udp(const unsigned char *buffer, int *offset) {
    const struct udp_header *udp = (const struct udp_header *)(buffer + *offset);

    printf("\nLayer 4: Transport\n");
    printf("Protocol: UDP\n");
    printf("Source Port: %u\n", ntohs(udp->src_port));
    printf("Dest Port: %u\n", ntohs(udp->dest_port));
    printf("Length: %u\n", ntohs(udp->length));


    *offset += 8; // UDP header is always 8 bytes
}