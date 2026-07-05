/**
 * @file application_parse.c
 * @brief Implementation of Application Layer parsing.
 */

#include "application_parse.h"
#include <stdio.h>
#include <string.h>

void parse_application(uint16_t src_port, uint16_t dest_port, const unsigned char *payload, int payload_length) {
    printf("\nLayer 5-7\n");
    printf("---------\n");
    printf("Protocol : ");

    // Identify application layer protocol based on common port numbers
    if (src_port == 80 || dest_port == 80) {
        printf("HTTP\n");
        
        // see if  there is a payload to parse
        if (payload_length > 0) {
            char method[16] = {0};
            char uri[256] = {0};
            char version[16] = {0};
            
            // Ensure we don't read beyond the payload length to avoid buffer overflows
            int safe_len = payload_length < 500 ? payload_length : 499;
            char safe_payload[500] = {0};
            memcpy(safe_payload, payload, safe_len);

            // Extract the first three words (Method, URI, Version) from the payload 
            if (sscanf(safe_payload, "%15s %255s %15s", method, uri, version) == 3) {
                
                // Validate that the extracted strings represent a valid HTTP request or response
                if (strncmp(method, "GET", 3) == 0 || strncmp(method, "POST", 4) == 0 || strncmp(method, "HTTP", 4) == 0) {
                    printf("Method: %s\n", method);
                    printf("URI: %s\n", uri);
                    printf("Version: %s\n", version);
                }
            }
        }
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