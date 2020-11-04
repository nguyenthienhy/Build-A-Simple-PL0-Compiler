#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cstring>
#include<ctype.h>
#include "lexical_analysis.h"

State getToken(char* letters, char* digits, char* str, char ch, int current_index){ // lay ra tat ca cac token trong mot file code
	char lexical_array[MAX_CHARACTER_IN_TOKEN]; // mang cac ky tu cho mot token trong 1 dong code
	int index = 0; // khoi tao chi so ban dau cho mang cac ky tu trong 1 token
	int length_lexical = 0; // do dai của 1 token
	if(ch == ' '){
		while(ch == ' '){ // khi gap ky tu SPACE thi bo qua, doc sang ky tu tiep theo
			length_lexical += 1;
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		char lexical_fix[length_lexical]; // tao 1 mang ky tu co so phan tu bang do dai cua token
		for(int i = 0; i < length_lexical; i ++){
			lexical_fix[i] = lexical_array[i];
		}
		return create_state(NONE, lexical_fix, ch, current_index, length_lexical);
	}
	else if(ch == '\t'){
		while(ch == '\t'){ // khi gap ky tu TAB xu ly tuong tu nhu ky tu SPACE
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
	else if(ch == '\n'){ // khi gap ky tu xuong dong(ENTER) xu ly tuong tu nhu ky tu SPACE
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
	else if(isLetter(letters, ch) == 1){ // khi gap ky tu la chu cai
		while(isLetter(letters, ch) == 1 || isDigit(digits, ch) == 1){ // ten bien co the co chu so
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
		if(isKeyword(lexical_fix) == 1){ // neu chuoi ky tu nhan duoc la KEYWORD
			char lexical_fix_two[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix_two[i] = toupper(lexical_array[i]);
			}
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state(lexical_fix_two, length_lexical, index_add - 1); // them phan tu nay vao MANG TOKEN
			return create_state(getKeyword(lexical_fix), lexical_array, ch, current_index, length_lexical);
		}
		else if(isKeyword(lexical_fix) == 0){// bo sung nhan dang ten qua 10 ky tu
			if(length_lexical > MAX_IDENT_LEN){ // neu qua 10 ky tu
                char lexical_fix_two[10];
				for(int i = 0; i < 10; i ++){
                    lexical_fix_two[i] = lexical_fix[i];
				}
                int index_add = count_token_in_token_array();
			    TokenArray[index_add - 1] = create_token_state(lexical_fix_two, 10, index_add - 1);
			    return create_state(IDENT, lexical_fix_two, ch, current_index, 10);	
			}
			else{
                int index_add = count_token_in_token_array();
			    TokenArray[index_add - 1] = create_token_state(lexical_fix, length_lexical, index_add - 1);
			    return create_state(IDENT, lexical_fix, ch, current_index, length_lexical);
			}
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
		if (length_lexical > 6){
			char lexical_fix_two[6];
			for(int i = 0; i < 6; i ++){
				lexical_fix_two[i] = lexical_fix[i];
			}
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"NUMBER", 6, index_add - 1);
			return create_state(NUMBER, lexical_fix_two, ch, current_index, length_lexical);
		}
		else{
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"NUMBER", 6, index_add - 1);
			return create_state(NUMBER, lexical_fix, ch, current_index, length_lexical);
		}
		
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"PLUS", 4, index_add - 1);
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
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"COMMENT_C", 9, index_add - 1);
			return create_state(COMMENT_C, lexical_fix, ch, current_index, length_lexical);
		}
		else{
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"TIMES", 5, index_add - 1);
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
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"GEQ", 3, index_add - 1);
			return create_state(GEQ, lexical_fix, ch, current_index, length_lexical);
		}
		else{
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"GTR", 3, index_add - 1);
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
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"LEQ", 3, index_add - 1);
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
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"NEQ", 3, index_add - 1);
			return create_state(NEQ, lexical_fix, ch, current_index, length_lexical);
		}
		else{
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"LSS", 3, index_add - 1);
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"EQU", 3, index_add - 1);
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
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"COMMENT_O", 9, index_add - 1);
			return create_state(COMMENT_O, lexical_fix, ch, current_index, length_lexical);
		}
		else{
			char lexical_fix[length_lexical];
			for(int i = 0; i < length_lexical; i ++){
				lexical_fix[i] = lexical_array[i];
			}
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"LPARENT", 7, index_add - 1);
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"LBRACK", 6, index_add - 1);
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
			int index_add = count_token_in_token_array();
			TokenArray[index_add - 1] = create_token_state((char*)"ASSIGN", 6, index_add - 1);
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"COMMA", 5, index_add - 1);
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"PERCENT", 7, index_add - 1);
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"MINUS", 5, index_add - 1);
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"SLASH", 5, index_add - 1);
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"RPARENT", 7, index_add - 1);
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"RBRACK", 6, index_add - 1);
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"SEMICOLON", 9, index_add - 1);
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
		int index_add = count_token_in_token_array();
		TokenArray[index_add - 1] = create_token_state((char*)"PREIOD", 6, index_add - 1);
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
	State state;
	return state; // NULL
}

void compile(char* filename){
	// fix so lon, ten qua dai, input sai
    char line[MAX_CHARACTER_IN_LINE];
    FILE* file = fopen(filename, "r");
	initial_TokenArray(TokenArray);
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
	int count_token = count_token_in_token_array() - 1; // khong thuc hien dem nua nen phai tru di 1
	remove_comment(TokenArray, count_token);
	// phan comment se duoc in ra gia tri COMMENT
	for(int i = 0 ; i < count_token; i ++){
		for(int j = 0; j < TokenArray[i].lexical_length; j ++){
			printf("%c", TokenArray[i].lexical[j]);
		}
		printf("\n");
	}
	fclose(file);
}

int	main(int argc, char * argv[]){
	if(argc == 1) compile((char*)"data/t.3.pl0");
    else if(argc == 2) compile((char*)argv[1]); 
	else printf("Syntax error \n");
 	return 0;
}
