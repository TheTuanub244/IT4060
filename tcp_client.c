#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
int main(char argc, char* argv[]){
    if(argc != 3){
        printf("Tham so khong hop le!\n");
        return 1;
    }
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    int port = atoi(argv[2]);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(port);
    int res = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if(res == -1){
        printf("Connect() Failed.\n");
        return 1;
    }
    char buf[256];
    fgets(buf, sizeof(buf), stdin);
    send(client, buf, sizeof(buf), 0);
    char msgFromServer[2048];
    recv(client, msgFromServer, sizeof(msgFromServer), 0);
    printf("Message from sever: %s\n", msgFromServer);
    close(client);
    return 1;
}