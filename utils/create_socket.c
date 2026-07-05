/**
 * @file create_socket.c
 * @brief Implementation of raw socket creation.
 */

#include "create_socket.h"
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

int create_raw_socket() {
    int raw_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if(raw_socket < 0) {
        perror("Socket Error");
        return -1; 
    }
    return raw_socket;
}