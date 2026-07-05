/**
 * @file application_parse.h
 * @brief Header file for identifying Application Layer protocols (Layers 5-7).
 */

#ifndef APPLICATION_PARSE_H
#define APPLICATION_PARSE_H

#include <stdint.h>

/**
 * @brief identifies and prints the application layer protocol based on ports.
 * @param src_port the source port from the transport layer.
 * @param dest_port the destination port from the transport layer.
 */
void parse_application(uint16_t src_port, uint16_t dest_port);

#endif