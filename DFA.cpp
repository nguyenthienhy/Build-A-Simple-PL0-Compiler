#include<stdio.h>
#include<string.h>
enum state {A, B, C, D};
int Delta[4][2] = {A, B, C, B, A, D, C, B};
char c;
char str[100];
int i, L;
enum state q = A; // automat o trang thai dau

int main(){
    printf("Nhap xau...:");
    fflush(stdin);
    gets(str);
    i = 0;
    L = strlen(str);
    c = str[i] - 48; // nhap vao la ky tu '1' phai tru di 48 de ve so nguyen 1
    while(i < L){
        if(c == 0 || c  == 1){
            q = state(Delta[int(q)][c]);
            i ++;
            c = str[i] - 48;
        }
        else{
            printf("Loi xau vao...\n");
            break;
        }
    }
    if(i == L){
        if(q == D){
            printf("\nXau vao %s duoc doan nhan !!!\n", str);
        }
        else{
            printf("\nXau vao %s khong duoc doan nhan !!!\n", str);
        }
    }
    return 0;
}
