/*
* Name: Dylan Hoover
* Date: 2/5/2021
* Lab 5 - UDP Stop and wait
* This code is the server side for a UDP stop and wait server that sends a file
*/

#include "lab5.h"

//getChecksum()
int getChecksum(Packet packet) {
    packet.header.cksum = 0;
    int checksum = 0;
    char *ptr = (char *)&packet;//points to the address of struct packet
    char *end = ptr + sizeof(Header) + packet.header.len;
    while (ptr < end) {
        checksum ^= *ptr;//gets address and xors it
	ptr++;//goes to next location in memory
    }
    return checksum;
}

// printPacket()
void printPacket(Packet packet) {
    printf("Packet{ header: { seq_ack: %d, len: %d, cksum: %d }, data: \"",
            packet.header.seq_ack,
            packet.header.len,
            packet.header.cksum);
    fwrite(packet.data, (size_t)packet.header.len, 1, stdout);
    printf("\" }\n");
}

//Server sending ACK to the client
void serverSend(int sockfd, const struct sockaddr *address, socklen_t addrlen, int seqnum) {
    Packet packet;
	//Prepare the packet headers
	//send the packet
    packet.header.seq_ack = seqnum;
    packet.header.len = 0;
    packet.header.cksum = getChecksum(packet);
    sendto(sockfd, &packet, sizeof(packet), 0, address, addrlen);
    printf("\t Server: sending ACK %d, checksum %d\n", packet.header.seq_ack, packet.header.cksum);
}

//Server receiving packet
Packet serverReceive(int sockfd, struct sockaddr *address, socklen_t *addrlen, int seqnum) {
    Packet packet;
    while (1) {
        //recv packets from the client
	recvfrom(sockfd, &packet, sizeof(packet), 0, address, addrlen);
        // Print received packet
        printPacket(packet);

        if (packet.header.cksum != getChecksum(packet)) {
            printf("Bad checksum, expected checksum was: %d\n", getChecksum(packet));
            serverSend(sockfd, address, *addrlen, !seqnum);
        } else if (packet.header.seq_ack != seqnum) {
            printf("Bad seqnum, expected sequence number was:%d\n", !seqnum);
            serverSend(sockfd, address, *addrlen, !seqnum);	
        } else {
            printf("Good packet\n");
            serverSend(sockfd, address, *addrlen, seqnum);
            break;
        }
    }
    return packet;
}


int main(int argc, char *argv[]) {
	int sockfd;
	FILE *fp;
    // check arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <port> <outfile>\n", argv[0]);
        exit(1);
    }
    // seed the RNG
    srand((unsigned)time(NULL));
    
    // create a socket
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Failure to setup an endpoint socket.");
		exit(1);
	}

    // initialize the server address structure using argv[1]
    struct sockaddr_in address;
    address.sin_family = AF_INET;
	address.sin_port = htons(atoi(argv[1]));//converts port str to int
	address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket
	// [Question]: Do we need to bind the socket on the client side? Why?/Why not?
    // Answer: bind is not required on the client side for UDP because the client contacts the server first and the server socket is bound to a specific port
	if((bind(sockfd, (struct sockaddr *)&address, sizeof(struct sockaddr))) < 0)
	{
		perror("Failure to bind server address to endpoint socket");
		exit(1);
	}

    // open file using argv[2]
    int file = open(argv[2], O_CREAT|O_RDWR, S_IRWXU);

    // get file contents from client
    int seqnum = 0;
    Packet packet;
    struct sockaddr_in clientaddr;
    socklen_t clientaddr_len = sizeof(clientaddr);
    do {
        packet = serverReceive(sockfd, (struct sockaddr *)&clientaddr, &clientaddr_len, seqnum);
	    write(file, packet.data, packet.header.len);
	    (seqnum == 0) ? (seqnum = 1) : (seqnum = 0); //alternates between 0 and 1 for seqnum
    } while (packet.header.len != 0);
    close(file);
    close(sockfd);
    return 0;
}






