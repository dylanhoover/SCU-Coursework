#include <arpa/inet.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>

typedef struct{    
    int     seq_ack;    
    int len;    
    int cksum;
    } Header;
    
typedef struct{    
    Header  header;    
    char    data[10];
    } Packet;