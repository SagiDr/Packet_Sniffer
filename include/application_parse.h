/**
 * @file application_parse.h
 * @brief Header file for Application Layer (Layer 5-7) parsing.
 * 
 * Contains the declaration for identifying and parsing application layer protocols.
 */

#ifndef APPLICATION_PARSE_H
#define APPLICATION_PARSE_H

#include <stdint.h>

/**
 * @brief Parses and identifies the application layer protocol.
 * 
 * Checks the source and destination ports to identify the protocol.
 * If the protocol is HTTP, it also extracts and prints the Method, URI, and Version from the payload.
 * 
 * @param src_port The source port extracted from the transport layer.
 * @param dest_port The destination port extracted from the transport layer.
 * @param payload Pointer to the start of the application payload.
 * @param payload_length The size of the payload in bytes.
 */
void parse_application(uint16_t src_port, uint16_t dest_port, const unsigned char *payload, int payload_length);

#endif