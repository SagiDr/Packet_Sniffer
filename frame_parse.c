#include "frame_parse.h"
#include <stdio.h>
#include <arpa/inet.h>

uint16_t parse_ethertype(const unsigned char *buffer){

    const struct eth_header *eth_header = (const struct eth_header*)buffer;

    printf("\nLayer2: DataLink\n");
    printf("Protocol:Ethernet II\n");


    printf("Destiontion Mac address: %02X:%02X:%02X:%02X:%02X:%02X\n",
        eth_header->dest_mac[0],eth_header->dest_mac[1],
        eth_header->dest_mac[2],eth_header->dest_mac[3],
        eth_header->dest_mac[4],eth_header->dest_mac[5]);

    
    printf("Source MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
           eth_header->src_mac[0], eth_header->src_mac[1],
           eth_header->src_mac[2], eth_header->src_mac[3],
           eth_header->src_mac[4], eth_header->src_mac[5]);

    
    uint16_t eth_type = ntohs(eth_header->ethertype);

    if (eth_type == 0x8100) {
        printf("Protocol: VLAN \n");
        const struct vlan_header *vlan = (const struct vlan_header *)(buffer + sizeof(struct eth_header));

        // Extract the Tag Control Information (TCI) from the VLAN header
        uint16_t tci = ntohs(vlan->tci);

        uint8_t pcp = (tci >> 13) & 0x07; // bits 13-15 for PCP
        uint8_t dei = (tci >> 12) & 0x01; //bit 12 for DEI
        uint16_t vid = tci & 0x0FFF; //bits 0-11 for VLAN ID

        printf("PCP (Priority): %u\n", pcp);
        printf("DEI (Drop Eligible): %u\n", dei);
        printf("VLAN ID: %u\n", vid);

        eth_type = ntohs(vlan->ethertype); // Update eth_type to the encapsulated EtherType
        printf("EtherType: 0x%04X\n", eth_type);
        } else {
        // If not VLAN, print the ethertype directly 
        printf("EtherType: 0x%04X\n", eth_type);
    }

    return eth_type;
}
