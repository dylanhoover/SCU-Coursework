//Lab6 Client
#include "lab6.h"

int sequence;

//getChecksum()
int getChecksum(Packet packet) {
    packet.header.cksum = 0;
    int checksum = 0;
    char *ptr = (char *)&packet;
    char *end = ptr + sizeof(Header) + packet.header.len;
    while (ptr < end) {
        checksum ^= *ptr++;
    } 
        return checksum;
}

void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

void ClientSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, Packet packet, unsigned retries) {

    while (1) {
        // calculate the checksum

        packet.header.cksum = getChecksum(packet);

        if(retries == 3){
            printf("Too many tries");
            break;
        }

        // log what is being sent
        printf("Created: ");
        printPacket(packet);

        // Simulate lost packet.
        if (rand()%10 == 0) {
            printf("Dropping packet\n");
        } else {
            
            sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
            perror("sendto");
            }

        // wait until either a packet is received or timeout, i.e using the select statement
        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;
        fd_set readfds;
        
        fcntl(sockfd, F_SETFL, O_NONBLOCK);
        FD_ZERO(&readfds);
        FD_SET(sockfd, &readfds);

        int rv = select(sockfd + 1, &readfds, NULL, NULL, &tv);
        if(rv == 0){
            retries++;
            continue;
        }
    
        // receive an ACK from the server
        Packet recvpacket;
        //******STUDENT WORK******
        recvfrom(sockfd, &recvpacket, sizeof(recvpacket), 0, address, &addrlen);

        // log what was received
        printf("Received ACK %d, checksum %d - ", recvpacket.header.seq_ack, recvpacket.header.cksum);

        // validate the ACK
        if ( recvpacket.header.cksum != getChecksum(recvpacket)) {
            // bad checksum, resend packet
            printf("Bad checksum, expected %d\n", getChecksum(recvpacket));
        } else if (recvpacket.header.seq_ack != sequence) {
            // incorrect sequence number, resend packet
            printf("Bad seqnum, expected %d\n", packet.header.seq_ack);
        } else {
            // good ACK, we're done
            printf("Good ACK\n");
            break;
        }
    }

    printf("\n");
}

int main(int argc, char *argv[]) {
    // check arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <ip> <port> <infile>\n", argv[0]);
        return 1;
    }

    // seed the RNG
    srand((unsigned)time(NULL));

    // create and configure the socket
  
   int sockfd; 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);   
    }

    // initialize the server address structure
    //******STUDENT WORK******
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    struct hostent *host;
    host = (struct hostent *)gethostbyname(argv[1]);
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2])); //Port 5000 is assigned
    address.sin_addr = *((struct in_addr *)host->h_addr); 

    // open file
    int file = open(argv[3], O_RDONLY);
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // send file contents to server
    Packet packet;
    int bytes;
    sequence = 0; 

    //******STUDENT WORK******
    while((bytes = read(file, packet.data, sizeof(packet.data))) > 0){
        packet.header.seq_ack = sequence;
        packet.header.len = bytes;
        ClientSend(sockfd, &address, sizeof(struct sockaddr), packet, 0);
        (sequence == 0)? (sequence = 1):(sequence = 0);
    }


    // send zero-length packet to server to end connection according the description provided in the Lab manual
    //******STUDENT WORK******
    packet.header.seq_ack = sequence;
    packet.header.len = 0;
    packet.header.cksum = getChecksum(packet);
    ClientSend(sockfd, &address, sizeof(struct sockaddr), packet, 0);


    // clean up
    //******STUDENT WORK******
    close(file);
    close(sockfd);
    return 0;
}
