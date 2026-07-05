#include "ipv4_parse.h"
#include <stdio.h>
#include <arpa/inet.h>

uint8_t parse_ipv4(const unsigned char *buffer, int *offset){
    //position the pointer to the start of the IPv4 header based on the current offset    
    const struct ipv4_header *ip = (const struct ipv4_header *)(buffer + *offset);

   printf("\nLayer3: Network\n");
   printf("Protocol: IPv4\n");

   uint8_t version = (ip->version_ihl >> 4) & 0x0F; // Extract the version (first 4 bits)
   uint8_t ihl = ip->version_ihl & 0x0F;
   uint16_t header_length = ihl * 4;

   // Check for invalid version or header length
   if (version != 4) {
        printf("Error: Invalid IPv4 version (%u). Expected version 4!\n", version);
    }
    if (ihl < 5) {
        printf("Error: IPv4 header is too short (%u bytes). Missing fields!\n", header_length);
    }


   printf("Version: %u\n", version);
   printf("Length: %u bytes\n", header_length);
   printf("Total Length:" " %u bytes\n", ntohs(ip->total_length));
   printf("Identification: %u\n", ntohs(ip->id));

   uint16_t frag_offset_raw = ntohs(ip->frag_offset);
   uint8_t flags = (frag_offset_raw >> 13) & 0x07; // Extract the flags (first 3 bits)
   uint16_t fragment_offset = frag_offset_raw & 0x1FFF; // Extract the fragment offset (last 13 bits)

    printf("Flags: 0x%02X\n", flags);
    printf("Fragment Offset: %u\n", fragment_offset);
    printf("TTL: %u\n", ip->ttl);
    printf("Protocol: %u\n", ip->protocol);
    printf("Checksum: %u\n", ntohs(ip->checksum));
    
    //print the source and destination IP addresses
    printf("Source IP: %d.%d.%d.%d\n", 
           ip->src_ip[0], ip->src_ip[1], ip->src_ip[2], ip->src_ip[3]);
    printf("Destination IP: %d.%d.%d.%d\n", 
           ip->dest_ip[0], ip->dest_ip[1], ip->dest_ip[2], ip->dest_ip[3]);


    //if there is more then 5 words in the header,it means that there are options
    if (ihl > 5) {
        printf("Options: Yes (Size: %u bytes)\n", (ihl - 5) * 4);
    } else {
        printf("Options: None\n");
    }

    uint8_t protocol = ip->protocol; // Store the protocol for return
    *offset += header_length;// Update the offset to point to the next protocol header after the ipv4 header
    
    return protocol; //return the protocol for further processing in main.c
}