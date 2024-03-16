#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
int main(char argc, char* argv[]){
    if(argc != 4){
        printf("Tham so khong hop le.\n");
        return 1;
    }

    int listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listener == -1){
        printf("Failed to create socket.\n");
        return 1;
    }
    struct sockaddr_in addr;
    int port = atoi(argv[1]);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr))){
        printf("Bind() Failed.\n");
        return 1;
    }
    if(listen(listener, 5)){
        printf("Listen() Failed.\n");
        return 1;
    }
    printf("Waiting for a new client...\n");
    int client = accept(listener, NULL, NULL);
    if(client == -1){
        printf("Accept() Failed.\n");
    }
    printf("Connect succesfully.\n");
    char buf[256];
    int ret = recv(client, buf, sizeof(buf), 0);
    buf[ret] = 0;
    char msgFromServer[2048];
    FILE *fg = fopen(argv[2], "rb");
    while(fgets(msgFromServer, 1000, fg) != NULL)
    printf("Message from server: %s", msgFromServer);
    send(client, msgFromServer, sizeof(msgFromServer), 0);
    fclose(fg);
    FILE *fp = fopen(argv[3], "a");
    fprintf(fp, "%s", buf);
    fclose(fp);
    close(client);
    close(listener);
    return 1;
}