#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cstring>
#include<ctype.h>

#define MAX_IDENT_LEN 10 // do dai toi da cua ten bien
#define MAX_CHARACTER_IN_TOKEN 10 // do dai toi da tren mot token
#define MAX_LINES 1000 // so dong toi da trong 1 file code
#define MAX_CHARACTER_IN_LINE 1024 // so ky tu toi da tren 1 dong


char letters[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'u', 's', 't', 'v', 'r', 'x', 'w', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'U', 'S', 'T', 'V', 'R', 'X', 'W', 'Y', 'Z'};
char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int strcmp_config(char* str1, char* str2){ // so sanh 2 xau
	int count = 0;
	for(int i = 0 ; i < strlen(str2); i ++){
		if(str2[i] == str1[i]){
			count += 1;
		}
	}
	if(count == strlen(str2)){
		return 0;
	}
	return 1;
}

char* convert_to_upper_case(char* str){ // chuyen ve dang chu hoa
	int j = 0; 
    while(str[j]){ 
        str[j] = toupper(str[j]); 
        j++; 
    }
    return str;
}

int isKeyword(char* str){ // kiem tra ten bien co phai la KEYWORD hay khong
	char* upper_str = convert_to_upper_case(str);
	if(strcmp_config(upper_str, (char*)"BEGIN") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"CALL") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"CONST") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"DO") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"ELSE") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"FOR") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"IF") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"ODD") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"PROCEDURE") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"PROGRAM") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"THEN") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"TO") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"VAR") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"WHILE") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, (char*)"END") == 0){
		return 1;
	}
	else{
		return 0;	
	}
}

int isLetter(char* letters, char ch){ // kiem tra xem mot ky tu co phai la chu cai hay khong
	char ch_tmp = toupper(ch);
	for(int i = 0; i < 52; i ++){
		char letter_tmp = toupper(letters[i]);
		if(ch_tmp == letter_tmp){
			return 1;
		}
	}
	return 0;
}

int isDigit(char* digits, char ch){ // kiem tra xem mot ky tu co phai la chu so hay khong
	for(int i = 0; i < 10; i ++){
		if(ch == digits[i]){
			return 1;
		}
	}
	return 0;
}

char getCh(char* str, int index){ // lay ra mot ky tu trong chuoi tai vi tri index
	return str[index];
}

typedef enum { //Cac loai token su dung trong PL/0
	NONE=0, IDENT, NUMBER,
	BEGIN, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS, 
	LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, 
	RBRACK, PERIOD, COMMA, SEMICOLON,  ASSIGN, 
	PERCENT, COMMENT_O, COMMENT_C
} TokenType;

struct State{ // trang thai sau khi doc xong 1 token
	TokenType nameToken; // ten token
	char lexical[MAX_CHARACTER_IN_TOKEN]; // chuoi mo ta token
	char current_char; // ky tu hien tai dang chuan bi duoc xet
	int current_index; // vi tri hien tai
	int number_character; // so luong ky tu cua token
};

struct TokenState{ // doi tuong trong mang token duoc nhan dang trong file code pl0
	char lexical[MAX_IDENT_LEN]; // doi tuong token
	int lexical_length; // do dai token
	int index; // vi tri trong mang
};

TokenState TokenArray[MAX_LINES]; // mang token trong code

TokenType getKeyword(char* str){ // lay ra keyword nhan dang duoc
	char* upper_str = convert_to_upper_case(str);
	if(strcmp_config(upper_str, (char*)"BEGIN") == 0){
		return BEGIN;
	}
	else if(strcmp_config(upper_str, (char*)"CALL") == 0){
		return CALL;
	}
	else if(strcmp_config(upper_str, (char*)"CONST") == 0){
		return CONST;
	}
	else if(strcmp_config(upper_str, (char*)"DO") == 0){
		return DO;
	}
	else if(strcmp_config(upper_str, (char*)"ELSE") == 0){
		return ELSE;
	}
	else if(strcmp_config(upper_str, (char*)"FOR") == 0){
		return FOR;
	}
	else if(strcmp_config(upper_str, (char*)"IF") == 0){
		return IF;
	}
	else if(strcmp_config(upper_str, (char*)"ODD") == 0){
		return ODD;
	}
	else if(strcmp_config(upper_str, (char*)"PROCEDURE") == 0){
		return PROCEDURE;
	}
	else if(strcmp_config(upper_str, (char*)"PROGRAM") == 0){
		return PROGRAM;
	}
	else if(strcmp_config(upper_str, (char*)"THEN") == 0){
		return THEN;
	}
	else if(strcmp_config(upper_str, (char*)"TO") == 0){
		return TO;
	}
	else if(strcmp_config(upper_str, (char*)"VAR") == 0){
		return VAR;
	}
	else if(strcmp_config(upper_str, (char*)"WHILE") == 0){
		return WHILE;
	}
	else if(strcmp_config(upper_str, (char*)"END") == 0){
		return END;
	}
	return NONE;
}

TokenState create_token_state(char* lexical, int lexical_length, int index){ // tao mot doi tuong token trong mang
	TokenState tokenstate;
	for(int i = 0 ; i < lexical_length; i ++){
		tokenstate.lexical[i] = lexical[i]; // ten token : chuoi bieu dien
	}
	tokenstate.lexical_length = lexical_length;
	tokenstate.index = index; // vi tri trong mang
	return tokenstate;
}

void initial_TokenArray(TokenState* TokenArray){ // khoi tao cac doi tuong trong mang token ve dang mac dinh
	for(int i = 0 ; i < MAX_LINES; i ++){
		TokenArray[i] = create_token_state((char*)"NULL", MAX_IDENT_LEN, i);
	}
}

int count_token_in_token_array(){ // dem so phan tu hien co trong mang token (so phan tu ko co dang mac dinh)
	int count = 0;
	for(int i = 0; i < MAX_LINES; i ++){
		count += 1;
		if (strcmp_config(TokenArray[i].lexical, (char*)"NULL") == 0){
			return count;
		}
	}
	return 0;
}

State create_state(TokenType nameToken, char* lexical, char current_char, int current_index, int number_character){ // tao doi tuong trang thai sau khi doc xong 1 token
	State state;
	state.nameToken = nameToken;
    for(int i = 0 ; i < number_character; i ++){
	    state.lexical[i] = lexical[i]; // ten token : chuoi bieu dien
	}
	state.current_char = current_char;
	state.current_index = current_index;
	state.number_character = number_character;
	return state;
}

void remove_comment(TokenState* token_array, int number_token){ // loai bo comment trong code
	for(int i = 0; i < number_token; i ++){
		if(strcmp_config(token_array[i].lexical, (char*)"COMMENT_O") == 0){ // neu gap ky tu khoi tao comment
			int index_comment_start = i;
			int index_comment_last = -1;
			for(int j = i + 1; j < number_token - 1; j ++){
				if(strcmp_config(token_array[j].lexical, (char*)"COMMENT_C") == 0){ // neu gap ky tu ket thuc comment
					index_comment_last = j;
				}
			}
			for(int index = index_comment_start; index <= index_comment_last; index ++){
				token_array[index] = create_token_state((char*)"COMMENT", 7, index);
			}
		}
	}
}
