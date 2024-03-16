#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<time.h>
struct SinhVien{
    char MSSV[2048];
    char hoTen[2048];
    char dob[2048];
    double diem;
};
int main(char argc, char* argv[]){
    if(argc != 3){
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
    struct SinhVien sv;
    int ret = recv(client, &sv, sizeof(sv), 0);
    char ipAddr[256];
    char time_str [1028];
    recv(client, ipAddr, sizeof(ipAddr), 0);
    time_t currentTime;
    struct tm *local_time;
    time(&currentTime);
    local_time = localtime(&currentTime);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
    FILE *fp = fopen(argv[2], "a");
    fprintf(fp, "%s %s %s %s %s %.2lf\n", ipAddr, time_str, sv.MSSV, sv.hoTen, sv.dob, sv.diem);
    fclose(fp);
    close(client);
    close(listener);
    return 1;
}