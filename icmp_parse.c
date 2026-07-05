#include "icmp_parse.h"
#include <stdio.h>
#include <arpa/inet.h>

void parse_icmp(const unsigned char *buffer, int *offset) {
    const struct icmp_header *icmp = (const struct icmp_header *)(buffer + *offset);

    printf("\nLayer 3: Network\n");
    printf("Protocol: ICMP\n");
    printf("Type: %u\n", icmp->type);
    printf("Code: %u\n", icmp->code);
    printf("Checksum: %u\n", ntohs(icmp->checksum));

    // type 8 is echo request (ping), type 0 is echo reply
    if (icmp->type == 8 || icmp->type == 0) {
        printf("Identifier: %u\n", ntohs(icmp->id));
        printf("Sequence Number: %u\n", ntohs(icmp->seq_num));
    }

    *offset += 8; // ICMP header is 8 bytes
}