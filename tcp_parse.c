#include "application_parse.h"
#include "transport_parse.h"
#include <stdio.h>
#include <arpa/inet.h>

void parse_tcp(const unsigned char *buffer, int *offset) {
    const struct tcp_header *tcp = (const struct tcp_header *)(buffer + *offset);

    printf("\nLayer 4: Transport\n");
    printf("Protocol: TCP\n");
    printf("Source Port: %u\n", ntohs(tcp->src_port));
    printf("Destination Port: %u\n", ntohs(tcp->dest_port));

    printf("Sequence Number : %u\n", ntohl(tcp->seq_num));
    printf("Acknowledgment Number : %u\n", ntohl(tcp->ack_num));
    
    // Calculate the data offset (header length) in bytes
    printf("Flags: ");
    if (tcp->flags & 0x01) printf("FIN ");
    if (tcp->flags & 0x02) printf("SYN ");
    if (tcp->flags & 0x04) printf("RST ");
    if (tcp->flags & 0x08) printf("PSH ");
    if (tcp->flags & 0x10) printf("ACK ");
    if (tcp->flags & 0x20) printf("URG ");
    printf("\n");

    printf("Window Size : %u\n", ntohs(tcp->window_size));

    // Call the application layer parser with the source and destination ports
    parse_application(ntohs(tcp->src_port), ntohs(tcp->dest_port));

    // Update the offset to point to the next protocol header after the TCP header
    uint8_t data_offset_bytes = (tcp->data_offset_res >> 4) * 4;
    *offset += data_offset_bytes;
}