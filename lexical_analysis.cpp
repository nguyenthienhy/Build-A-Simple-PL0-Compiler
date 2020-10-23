#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#define MAX_IDENT_LEN 10
#define MAX_CHARACTER_IN_TOKEN 10
#define MAX_LINES 100
#define MAX_CHARACTER_IN_LINE 256

typedef enum { //Cac loai token su dung trong PL/0
	NONE=0, IDENT, NUMBER,
	BEGIN, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS, LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, RBRACK, PERIOD, COMMA, SEMICOLON,  ASSIGN, PERCENT
} TokenType;

struct State{
	TokenType nameToken;
	char* lexical;
	char current_char;
	int current_index;
	int number_character;
};

State create_state(TokenType nameToken, char* lexical, char current_char, char current_index, int number_character){
	State state;
	state.nameToken = IDENT;
	state.lexical = lexical;
	state.current_char = current_char;
	state.current_index = current_index;
	state.number_character = number_character;
	return state;
}

char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'u', 's', 't', 'v', 'r', 'x', 'w', 'y', 'z'};
char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int isLetter(char* letters, char ch){
	for(int i = 0; i < 26; i ++){
		if(ch == letters[i]){
			return 1;
		}
	}
	return 0;
}

int isDigit(char* digits, char ch){
	for(int i = 0; i < 10; i ++){
		if(ch == digits[i]){
			return 1;
		}
	}
	return 0;
}

char getCh(char* str, int index){
	return str[index];
}

State getToken(char* letters, char* digits, char* str, char ch, int current_index){
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
		return create_state(NONE, lexical_array, ch, current_index, length_lexical);
	}
	else if(isLetter(letters, ch) == 1){
		while(isLetter(letters, ch) == 1 || isDigit(digits, ch) == 1){
			length_lexical += 1;
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		printf("IDENT\n");
		return create_state(IDENT, lexical_array, ch, current_index, length_lexical);
	}
	else if(isDigit(digits, ch) == 1){
		while(isDigit(digits, ch) == 1){
			length_lexical += 1;
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		printf("NUMBER\n");
		return create_state(NUMBER, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == '+'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("PLUS");
		return create_state(PLUS, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == '*'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("TIMES");
		return create_state(TIMES, lexical_array, ch, current_index, length_lexical);
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
			printf("GEQ");
			return create_state(GEQ, lexical_array, ch, current_index, length_lexical);
		}
		else{
            printf("GTR");
			return create_state(GTR, lexical_array, ch, current_index, length_lexical);
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
			printf("LEQ");
			return create_state(LEQ, lexical_array, ch, current_index, length_lexical);
		}
		else if(ch == '>'){
			length_lexical = 2;
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			printf("NEQ");
			return create_state(NEQ, lexical_array, ch, current_index, length_lexical);
		}
		else{
            printf("LSS");
			return create_state(LSS, lexical_array, ch, current_index, length_lexical);
		}
	}
	else if(ch == '='){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("EQU");
		return create_state(EQU, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == '('){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("LPARENT");
		return create_state(LPARENT, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == '['){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("LBRACK");
		return create_state(LBRACK, lexical_array, ch, current_index, length_lexical);
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
			printf("ASSIGN");
			return create_state(ASSIGN, lexical_array, ch, current_index, length_lexical);
		}
	}
	else if(ch == ','){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("COMMA\n");
		return create_state(COMMA, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == '%'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("PERCENT");
		return create_state(PERCENT, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == '-'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("MINUS");
		return create_state(MINUS, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == '/'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("SLASH");
		return create_state(SLASH, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == ')'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("RPARENT");
		return create_state(RPARENT, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == ']'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("RBRACK");
		return create_state(RBRACK, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == ';'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("SEMICOLON");
		return create_state(SEMICOLON, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == '.'){
		length_lexical = 1;
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		printf("PERIOD");
		return create_state(PERIOD, lexical_array, ch, current_index, length_lexical);
	}
	else if(ch == '\n'){
		length_lexical = 1;
		lexical_array[index] = '$';
		current_index = current_index + 1;
		return create_state(NONE, lexical_array, ch, current_index, length_lexical);
	}
}


int main(int argc, char* argv[]){
    char line[MAX_CHARACTER_IN_LINE];
    FILE* file = fopen("exam.txt", "r");
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
        printf("\n");
    }
	fclose(file);
	return 0;
}