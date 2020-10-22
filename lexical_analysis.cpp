#include<stdio.h>
#include<stdlib.h>
#define MAX_IDENT_LEN 10
#define MAX_CHARACTER 10

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
};

State create_state(TokenType nameToken, char* lexical, char current_char, char current_index){
	State state;
	state.nameToken = IDENT;
	state.lexical = lexical;
	state.current_char = current_char;
	state.current_index = current_index;
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
	char lexical_array[MAX_CHARACTER];
	int index = 0;
	if(ch == ' '){
		while(ch == ' '){
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		return create_state(NONE, lexical_array, ch, current_index);
	}
	else if(isLetter(letters, ch) == 1){
		while(isLetter(letters, ch) == 1 || isDigit(digits, ch) == 1){
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		return create_state(IDENT, lexical_array, ch, current_index);
	}
	else if(isDigit(digits, ch) == 1){
		while(isDigit(digits, ch) == 1){
			lexical_array[index] = ch;
			index += 1;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
		}
		return create_state(NUMBER, lexical_array, ch, current_index);
	}
	else if(ch == '+'){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(PLUS, lexical_array, ch, current_index);
	}
	else if(ch == '*'){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(TIMES, lexical_array, ch, current_index);
	}
	else if(ch == '>'){
		lexical_array[index] = ch;
		index += 1;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		if(ch == '='){
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			return create_state(GEQ, lexical_array, ch, current_index);
		}
		else{
			return create_state(GTR, lexical_array, ch, current_index);
		}
	}
	else if(ch == '<'){
		lexical_array[index] = ch;
		index += 1;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		if(ch == '='){
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			return create_state(LEQ, lexical_array, ch, current_index);
		}
		else if(ch == '>'){
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			return create_state(NEQ, lexical_array, ch, current_index);
		}
		else{
			return create_state(LSS, lexical_array, ch, current_index);
		}
	}
	else if(ch == '='){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(EQU, lexical_array, ch, current_index);
	}
	else if(ch == '('){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(LPARENT, lexical_array, ch, current_index);
	}
	else if(ch == '['){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(LBRACK, lexical_array, ch, current_index);
	}
	else if(ch == ':'){
		lexical_array[index] = ch;
		index += 1;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		if(ch == '='){
			lexical_array[index] = ch;
			ch = getCh(str, current_index + 1);
			current_index = current_index + 1;
			return create_state(ASSIGN, lexical_array, ch, current_index);
		}
	}
	else if(ch == ','){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(COMMA, lexical_array, ch, current_index);
	}
	else if(ch == '%'){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(PERCENT, lexical_array, ch, current_index);
	}
	else if(ch == '-'){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(MINUS, lexical_array, ch, current_index);
	}
	else if(ch == '/'){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(SLASH, lexical_array, ch, current_index);
	}
	else if(ch == ')'){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(RPARENT, lexical_array, ch, current_index);
	}
	else if(ch == ']'){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(RBRACK, lexical_array, ch, current_index);
	}
	else if(ch == ';'){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(SEMICOLON, lexical_array, ch, current_index);
	}
	else if(ch == '.'){
		lexical_array[index] = ch;
		ch = getCh(str, current_index + 1);
		current_index = current_index + 1;
		return create_state(PERIOD, lexical_array, ch, current_index);
	}
	else{
		lexical_array[index] = '$';
		return create_state(NONE, lexical_array, ch, current_index);
	}
}


int main(){
    FILE* file = fopen("exam.txt", "r");
    char* lines[100];
    char line[256];
    int index = 0;
    while (fgets(line, sizeof(line), file)) {
		lines[index] = line;
		index = index + 1;
    }
    //printf("%s", lines[1]);
	char* current_ch = lines[1];
	int current_index = 0;
	State result = getToken(letters, digits, current_ch, current_ch[0], current_index);
	for(int i = 0; i < 3; i ++){
		//printf("%c", result.lexical[i]);
	}
	char current_character = result.current_char;
	current_index = result.current_index;
	while(current_index < 9){
		State result = getToken(letters, digits, current_ch, current_character, current_index);
		for(int i = 0; i < 1; i ++){
			//printf("%c", result.lexical[i]);
		}
		printf("\n");
		current_character = result.current_char;
		current_index = result.current_index;
	}
	fclose(file);
	return 0;
}
