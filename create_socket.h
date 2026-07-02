/**
 * @file create_socket.h
 * @brief Header file for raw socket creation.
 * 
 * This file contains the declaration for the function responsible 
 * for creating and initializing a raw network socket.
 */

#ifndef CREATE_SOCKET_H
#define CREATE_SOCKET_H

/**
 * @brief Creates a raw socket for packet sniffing.
 * 
 * This function initializes a raw socket using the AF_PACKET family and SOCK_RAW type, 
 * allowing it to capture all packets at the data link layer (ETH_P_ALL). 
 * 
 * @return int Returns the socket file descriptor on success, or -1 on failure.
 */
int create_raw_socket();

#endif