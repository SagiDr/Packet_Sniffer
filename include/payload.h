/**
 * @file payload.h
 * @brief Header file for printing packet payloads.
 */

#ifndef PAYLOAD_H
#define PAYLOAD_H

/**
 * @brief print the payload data in HEX and ASCII format.
 * @param data pointer to the start of the payload.
 * @param size the size of the payload in bytes.
 */
void print_payload(const unsigned char *data, int size);

#endif