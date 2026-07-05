#include "application_parse.h"
#include <stdio.h>

void parse_application(uint16_t src_port, uint16_t dest_port) {
    printf("\nLayer 5-7\n");
    printf("---------\n");
    printf("Protocol : ");

    // Identify application layer protocol based on common port numbers
    if (src_port == 80 || dest_port == 80) {
        printf("HTTP\n");
    } else if (src_port == 443 || dest_port == 443) {
        printf("HTTPS\n");
    } else if (src_port == 53 || dest_port == 53) {
        printf("DNS\n");
    } else if (src_port == 67 || dest_port == 67 || src_port == 68 || dest_port == 68) {
        printf("DHCP\n");
    } else if (src_port == 20 || dest_port == 20 || src_port == 21 || dest_port == 21) {
        printf("FTP\n");
    } else if (src_port == 22 || dest_port == 22) {
        printf("SSH\n");
    } else if (src_port == 23 || dest_port == 23) {
        printf("Telnet\n");
    } else if (src_port == 123 || dest_port == 123) {
        printf("NTP\n");
    } else {
        printf("Unknown (Ports: %u -> %u)\n", src_port, dest_port);
    }
}