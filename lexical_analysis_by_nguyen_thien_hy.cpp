#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cstring>
#include<ctype.h>

#define MAX_IDENT_LEN 10
#define MAX_CHARACTER_IN_TOKEN 100
#define MAX_LINES 1000
#define MAX_CHARACTER_IN_LINE 256

char letters[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'u', 's', 't', 'v', 'r', 'x', 'w', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'U', 'S', 'T', 'V', 'R', 'X', 'W', 'Y', 'Z'};
char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

typedef enum { //Cac loai token su dung trong PL/0
	NONE=0, IDENT, NUMBER,
	BEGIN, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS, LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, RBRACK, PERIOD, COMMA, SEMICOLON,  ASSIGN, PERCENT, COMMENT
} TokenType;

struct State{ // trang thai sau khi doc xong 1 token
	TokenType nameToken; // ten token
	char* lexical; // chuoi mo ta token
	char current_char; // ky tu hien tai dang chuan bi duoc xet
	int current_index; // vi tri hien tai
	int number_character; // so luong ky tu cua token
};

State create_state(TokenType nameToken, char* lexical, char current_char, char current_index, int number_character){ // tao doi tuong trang thai sau khi doc xong 1 token
	State state;
	state.nameToken = IDENT;
	state.lexical = lexical;
	state.current_char = current_char;
	state.current_index = current_index;
	state.number_character = number_character;
	return state;
}

char* convert_to_upper_case(char* str){ // chuyen ve dang chu hoa
	int j = 0;
	int len = strlen(str);
	char str_up[len]; 
    while(str[j]){ 
        str_up[j] = toupper(str[j]); 
        j++; 
    }
    return str_up;
}

int strcmp_config(char* str1, char* str2){// so sanh 2 xau
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

int isKeyword(char* str){ // kiem tra ten bien co phai la IDENT hay khong
	char* upper_str = convert_to_upper_case(str);
	if(strcmp_config(upper_str, "BEGIN") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "CALL") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "CONST") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "DO") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "ELSE") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "FOR") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "IF") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "ODD") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "PROCEDURE") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "PROGRAM") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "THEN") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "TO") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "VAR") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "WHILE") == 0){
		return 1;
	}
	else if(strcmp_config(upper_str, "END") == 0){
		return 1;
	}
	else{
		return 0;	
	}
}

TokenType getKeyword(char* str){ // lay ra keyword nhan dang duoc
	char* upper_str = convert_to_upper_case(str);
	if(strcmp_config(upper_str, "BEGIN") == 0){
		return BEGIN;
	}
	else if(strcmp_config(upper_str, "CALL") == 0){
		return CALL;
	}
	else if(strcmp_config(upper_str, "CONST") == 0){
		return CONST;
	}
	else if(strcmp_config(upper_str, "DO") == 0){
		return DO;
	}
	else if(strcmp_config(upper_str, "ELSE") == 0){
		return ELSE;
	}
	else if(strcmp_config(upper_str, "FOR") == 0){
		return FOR;
	}
	else if(strcmp_config(upper_str, "IF") == 0){
		return IF;
	}
	else if(strcmp_config(upper_str, "ODD") == 0){
		return ODD;
	}
	else if(strcmp_config(upper_str, "PROCEDURE") == 0){
		return PROCEDURE;
	}
	else if(strcmp_config(upper_str, "PROGRAM") == 0){
		return PROGRAM;
	}
	else if(strcmp_config(upper_str, "THEN") == 0){
		return THEN;
	}
	else if(strcmp_config(upper_str, "TO") == 0){
		return TO;
	}
	else if(strcmp_config(upper_str, "VAR") == 0){
		return VAR;
	}
	else if(strcmp_config(upper_str, "WHILE") == 0){
		return WHILE;
	}
	else if(strcmp_config(upper_str, "END") == 0){
		return END;
	}
	return NONE;
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

State getToken(char* letters, char* digits, char* str, char ch, int current_index){ // lay ra tat ca cac token trong mot file code
	char lexical_array[MAX_CHARACTER_IN_TOKEN];
	int index = 0;
	int length_lexical = 0;
	if(ch == ' '){
		while(ch == ' '){
			length_lexical += 1;
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		return create_state(NONE, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '\t'){
		while(ch == '\t'){
			length_lexical += 1;
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		return create_state(NONE, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '\n'){
		while(ch == '\n'){
			length_lexical += 1;
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		return create_state(NONE, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '{'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		return create_state(NONE, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '}'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		return create_state(NONE, lexical_fix, ch, current_index, length_lexical);
	}
	else if(isLetter(letters, ch) == 1){
		while(isLetter(letters, ch) == 1 || isDigit(digits, ch) == 1){
			length_lexical += 1;
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		if(isKeyword(lexical_fix) == 1){
			for(int i = 0; i < length_lexical; i ++){
				printf("%c", toupper(lexical_fix[i]));
			}
			printf("\n");
			return create_state(getKeyword(lexical_fix), lexical_array, ch, current_index, length_lexical);
		}
		else if(isKeyword(lexical_fix) == 0){// bo sung nhan dang ten qua 10 ky tu
			printf("IDENT(");
			if(length_lexical > MAX_IDENT_LEN){
				for(int i = 0; i < 10; i ++){
					printf("%c", lexical_fix[i]);
				}	
			}
			else{
				for(int i = 0; i < length_lexical; i ++){
					printf("%c", lexical_fix[i]);
				}
			}
			printf(")");
			printf("\n");
			return create_state(IDENT, lexical_fix, ch, current_index, length_lexical);
		}
	}
	else if(isDigit(digits, ch) == 1){
		while(isDigit(digits, ch) == 1){
			length_lexical += 1;
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("NUMBER\n");
		return create_state(NUMBER, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '+'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("PLUS\n");
		return create_state(PLUS, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '*'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		if(ch == ')'){
			length_lexical = 2;
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			printf("COMMENT\n");
			return create_state(COMMENT, lexical_fix, ch, current_index, length_lexical);
		}
		else{
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			printf("TIMES\n");
			return create_state(TIMES, lexical_fix, ch, current_index, length_lexical);
		}
	}
	else if(ch == '>'){
		length_lexical = 1;
		lexical_array[index] = ch;
		index += 1;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		if(ch == '='){
			length_lexical = 2;
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			printf("GEQ\n");
			return create_state(GEQ, lexical_fix, ch, current_index, length_lexical);
		}
		else{
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
            printf("GTR\n");
			return create_state(GTR, lexical_fix, ch, current_index, length_lexical);
		}
	}
	else if(ch == '<'){
		length_lexical = 1;
		lexical_array[index] = ch;
		index += 1;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		if(ch == '='){
			length_lexical = 2;
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			printf("LEQ\n");
			return create_state(LEQ, lexical_fix, ch, current_index, length_lexical);
		}
		else if(ch == '>'){
			length_lexical = 2;
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			printf("NEQ\n");
			return create_state(NEQ, lexical_fix, ch, current_index, length_lexical);
		}
		else{
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
            printf("LSS\n");
			return create_state(LSS, lexical_fix, ch, current_index, length_lexical);
		}
	}
	else if(ch == '='){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("EQU\n");
		return create_state(EQU, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '('){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		if(ch == '*'){
			length_lexical = 2;
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			printf("COMMENT\n");
			return create_state(COMMENT, lexical_fix, ch, current_index, length_lexical);
		}
		else{
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			printf("LPARENT\n");
			return create_state(LPARENT, lexical_fix, ch, current_index, length_lexical);
		}
	}
	else if(ch == '['){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("LBRACK\n");
		return create_state(LBRACK, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == ':'){
		length_lexical = 1;
		lexical_array[index] = ch;
		index += 1;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		if(ch == '='){
			length_lexical = 2;
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			printf("ASSIGN\n");
			return create_state(ASSIGN, lexical_fix, ch, current_index, length_lexical);
		}
		else{
			length_lexical = 1;
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			return create_state(NONE, lexical_fix, ch, current_index, length_lexical);
		}
	}
	else if(ch == ','){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("COMMA\n");
		return create_state(COMMA, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '%'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("PERCENT\n");
		return create_state(PERCENT, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '-'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("MINUS\n");
		return create_state(MINUS, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '/'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("SLASH\n");
		return create_state(SLASH, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == ')'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("RPARENT\n");
		return create_state(RPARENT, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == ']'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("RBRACK\n");
		return create_state(RBRACK, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == ';'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("SEMICOLON\n");
		return create_state(SEMICOLON, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '.'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		printf("PERIOD\n");
		return create_state(PERIOD, lexical_fix, ch, current_index, length_lexical);
	}
	else{
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		char lexical_fix[length_lexical];
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		return create_state(NONE, lexical_fix, ch, current_index, length_lexical);
	}
}

int main(int argc, char* argv[]){
	// fix so lon, ten qua dai, input sai
    char line[MAX_CHARACTER_IN_LINE];
    char filename[256];
    printf("Nhap vao file test: ");
    gets(filename);
    FILE* file = fopen(filename, "r");
    printf("\n");
    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line); // do dai cua dong trong file
        State result = getToken(letters, digits, line, line[0], 0);
        char current_character = result.current_char;
        int current_index = result.current_index;
        while(current_index < len){
            State result_tmp = getToken(letters, digits, line, current_character, current_index);
            current_character = result_tmp.current_char;
            current_index = result_tmp.current_index;
        }
    }
	fclose(file);
	return 0;
}
