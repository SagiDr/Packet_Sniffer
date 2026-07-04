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
 }__attribute__((packed));

 uint16_t parse_ethertype(const unsigned char *buffer);
 
/** 
 * @brief Custom structure for VLAN (802.1Q) tag.
 * Follows immediately after the src_mac in Ethernet II if EtherType is 0x8100.
 */
struct vlan_header {
    uint16_t tci;       // Tag Control Information (PCP - priority, DEI - if we can drop the packet, VID)
    uint16_t ethertype; // The actual encapsulated EtherType
} __attribute__((packed));

#endif