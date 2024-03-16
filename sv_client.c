#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>
struct SinhVien{
    char MSSV[2048];
    char hoTen[2048];
    char dob[2048];
    double diem;
};
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
    struct SinhVien sv;
    printf("Nhap MSSV: ");
    scanf("%s", &sv.MSSV);
    while(getchar() != '\n');
    printf("Nhap ho va ten: ");
    fgets(sv.hoTen, sizeof(sv.hoTen), stdin);
    if(sv.hoTen[strlen(sv.hoTen) - 1] == '\n'){
        sv.hoTen[strlen(sv.hoTen) - 1] = '\0';
    }
    printf("Nhap ngay sinh: ");
    scanf("%s", &sv.dob);
    printf("Nhap diem: ");
    scanf("%lf", &sv.diem);
    send(client, &sv, sizeof(sv), 0);
    char *ipAddr = argv[1];
    send(client, ipAddr, strlen(ipAddr), 0);
    close(client);
    return 1;
}