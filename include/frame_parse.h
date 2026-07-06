#ifndef FRAME_PARSE_H
#define FRAME_PARSE_H

#include <stdint.h>

#define MAC_ADDR_LEN 6 // Length of a MAC address in bytes

/** 
 * @brief Custom structure of the Ethernet header.
 * The "packed" attribute ensures that the compiler does not add any padding between the fields,
 *  which is crucial for correctly interpreting the raw data received from the network. 
 */

 struct eth_header{
    uint8_t dest_mac[MAC_ADDR_LEN]; // Destination MAC address,1byte(only needs 6)
    uint8_t src_mac[MAC_ADDR_LEN];  // Source MAC address,1byte(only needs 6)
    uint16_t ethertype; // Ethertype field,2bytes
 }__attribute__((packed));//

 
/** 
 * @brief Custom structure for VLAN tag.
 * Follows immediately after the src_mac in Ethernet II if ethertype is 0x8100.
 */
struct vlan_header {
    uint16_t tci;       // Tag Control Information (PCP - priority, DEI - if we can drop the packet, VID - VLAN ID)
    uint16_t ethertype; // The actual encapsulated ethertype after the VLAN tag
} __attribute__((packed));

/** 
 * @brief Custom structure for ARP header.
 */
struct arp_header {
    uint16_t hw_type;   // Hardware Type
    uint16_t proto_type;// Protocol Type
    uint8_t  hw_len;    // Hardware Address Length
    uint8_t  proto_len; // Protocol Address Length
    uint16_t opcode;    // Operation Code (Request/Reply)
    uint8_t  sender_mac[MAC_ADDR_LEN]; // Sender MAC Address
    uint8_t  sender_ip[4];             // Sender IP Address
    uint8_t  target_mac[MAC_ADDR_LEN]; // Target MAC Address
    uint8_t  target_ip[4];             // Target IP Address
} __attribute__((packed));

//updated function signature to include offset parameter
uint16_t parse_ethertype(const unsigned char *buffer, int *offset);

void parse_arp(const unsigned char *buffer, int offset);

#endif