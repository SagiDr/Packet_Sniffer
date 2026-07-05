#ifndef IPV4_PARSE_H
#define IPV4_PARSE_H

#include <stdint.h>

/**
 * @brief Custom structure for IPv4 header.
 * Contains all fields to perform full parsing as required.
 */
struct ipv4_header {
    uint8_t  version_ihl;   // Internet Header Length (IHL) (4 bits)
    uint8_t  tos;           // Type of service (ToS)
    uint16_t total_length;  // Total Length of the packet
    uint16_t id;            // Identification
    uint16_t frag_offset;   // Flags (3 bits) + Fragment Offset (13 bits)
    uint8_t  ttl;           // Time to Live (TTL)
    uint8_t  protocol;      // Next level protocol (TCP=6, UDP=17, ICMP=1)
    uint16_t checksum;      // Header Checksum
    uint8_t  src_ip[4];     // Source IP Address
    uint8_t  dest_ip[4];    // Destination IP Address
} __attribute__((packed)); 

/**
 * @brief Parses the IPv4 header from the given buffer.
 * @param buffer Pointer to the raw packet data.
 * @param offset Pointer to the current offset in the buffer; will be updated after parsing.
 */
uint8_t parse_ipv4(const unsigned char *buffer, int *offset);

#endif