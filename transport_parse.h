#ifndef TRANSPORT_PARSE_H
#define TRANSPORT_PARSE_H

#include <stdint.h>

/**
 * @struct tcp_header
 * @brief Represents the TCP header structure.
 */
struct tcp_header {
    uint16_t src_port;    /**< source port */
    uint16_t dest_port;   /**< destination port */
    uint32_t seq_num;     /**< sequence number */
    uint32_t ack_num;     /**< acknowledgment number */
    uint8_t  data_offset_res; /**< data offset and reserved bits */
    uint8_t  flags;       /**< TCP flags */
    uint16_t window_size; /**< window size */
    uint16_t checksum;    /**< checksum */
    uint16_t urgent_pointer; /**< urgent Pointer */
} __attribute__((packed));

/**
 * @struct udp_header
 * @brief Represents the UDP header structure.
 */
struct udp_header {
    uint16_t src_port;  /**< Source port */
    uint16_t dest_port; /**< Destination port */
    uint16_t length;    /**< Length of the header and data */
    uint16_t checksum;  /**< checksum */
} __attribute__((packed));

/**
 * @brief Parses the TCP header from the buffer.
 * @param buffer Pointer to the raw packet data.
 * @param offset The starting position of the TCP header in the buffer.
 */
void parse_tcp(const unsigned char *buffer, int *offset);

/**
 * @brief Parses the UDP header from the buffer.
 * @param buffer Pointer to the raw packet data.
 * @param offset The starting position of the UDP header in the buffer.
 */
void parse_udp(const unsigned char *buffer, int *offset);

#endif