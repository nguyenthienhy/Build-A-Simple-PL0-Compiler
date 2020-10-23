#include <stdio.h>
#include "scanner.h"

TokenType Token;
int		  Num;
char	  Id[MAX_IDENT_LEN + 1];

FILE * f;
char ch;

TokenType checkKeyword(char * str){
	//TODO: Kiem tra tham so truyen vao co phai la mot Tu khoa khong
	//................
	return NONE;
}

char getCh(){
  return fgetc(f);
}

TokenType getToken(){
//TODO:
//..............

    return NONE;
}


void compile(char * filename){
  	if((f = fopen(filename,"rt")) == NULL) printf("File %s not found",filename);
  	else{
		ch =' ';
		do{
		 	Token = getToken();
			printf(" %s",TabToken[Token]);
			if(Token==IDENT) printf("(%s) \n",Id);
			else if(Token==NUMBER) printf("(%d) \n",Num);
			else printf("\n");
		}while(Token != NONE);
	}
  fclose(f);
}
