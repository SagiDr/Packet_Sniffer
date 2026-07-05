/**
 * @file icmp_parse.h
 * @brief Header file for ICMP parsing.
 */

#ifndef ICMP_PARSE_H
#define ICMP_PARSE_H

#include <stdint.h>

/**
 * @struct icmp_header
 * @brief Represents the ICMP header structure (RFC 792).
 */
struct icmp_header {
    uint8_t  type;       /**<  message type */
    uint8_t  code;       /**< message code */
    uint16_t checksum;   /**< checksum */
    uint16_t id;         /**< Identifier (for Echo request/reply) */
    uint16_t seq_num;        /**< Sequence Number (for Echo request/reply) */
} __attribute__((packed));

/**
 * @brief Parses the ICMP header from the buffer.
 * @param buffer Pointer to the raw packet data.
 * @param offset The starting position of the ICMP header in the buffer.
 */
void parse_icmp(const unsigned char *buffer, int *offset);

#endif