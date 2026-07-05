#include "application_parse.h"
#include "transport_parse.h"
#include <stdio.h>
#include <arpa/inet.h>

void parse_tcp(const unsigned char *buffer, int *offset,int data_size){
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
    printf("Checksum: 0x%04X\n", ntohs(tcp->checksum));
    printf("Urgent Pointer: %u\n", ntohs(tcp->urgent_pointer));

    // Update the offset to point to the next protocol header after the TCP header
    uint8_t data_offset_bytes = (tcp->data_offset_res >> 4) * 4;

    //if 
    if (data_offset_bytes < 20) {
        printf("Error: TCP header is too short (%u bytes). Missing fields or corrupted packet!\n", data_offset_bytes);
    } else {
    // Calculate the pointer to the payload and its length
        const unsigned char *payload = buffer + *offset + data_offset_bytes;
        int payload_length = data_size - (*offset + data_offset_bytes);
        
        // Pass the payload details to the application layer parser
        parse_application(ntohs(tcp->src_port), ntohs(tcp->dest_port), payload, payload_length > 0 ? payload_length : 0);
    }
    *offset += data_offset_bytes;
}