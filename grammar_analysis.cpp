#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cstring>
#include<ctype.h>
#include "lexical_analysis.cpp"

State factor(char*str, char ch, int current_index, int &error);
State term(char*str, char ch, int current_index, int &error);
State expression(char*str, char ch, int current_index, int &error);
State condition(char*str, char ch, int current_index, int &error);
// State statement(char*str, char ch, int current_index, int &error);
// State block(char*str, char ch, int current_index, int &error);
// State program(char*str, char ch, int current_index, int &error);

TokenType Token;

State factor(char*str, char ch, int current_index, int &error){
    State result;
    if(Token == IDENT){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == LBRACK){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = expression(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == RBRACK){
                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
            }
            else{
                error = 1;
                printf("Thieu dau ngoac vuong...");
            }
        }
        return result;
    }
    else if(Token == NUMBER){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        return result;
    }
    else if(Token == LPARENT){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        result = expression(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        if(Token == RPARENT){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            return result;
        }
        else{
            error = 1;
            printf("Thieu dau ngoac...");
        }
    }
}

State term(char*str, char ch, int current_index, int &error){
    State result;
    result = factor(str, ch, current_index, error);
    Token = result.nameToken;
    while(Token == TIMES || Token == SLASH || Token == PERCENT){
        result = getToken(letters, digits, str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        result = factor(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
    }
    return result;
}

State expression(char*str, char ch, int current_index, int &error){
    State result;
    bool flag_odd = false;
    if(Token == PLUS || Token == MINUS){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        flag_odd = true;
    }
    if(flag_odd == true){
        result = term(str, result.current_char, result.current_index, error);
    }
    else{
        result = term(str, ch, current_index, error);
    }
    Token = result.nameToken;
    while(Token == PLUS || Token == MINUS){
        result = getToken(letters, digits, str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        result = term(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
    }
    return result;
}

State condition(char*str, char ch, int current_index, int &error){
    State result;
    if(Token == ODD){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        result = expression(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        return result;
    }
    else{
        result = expression(str, ch, current_index, error);
        if(Token == EQU || Token == NEQ || Token == LSS || Token == LEQ || Token == GTR || Token == GEQ){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = expression(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            return result;
        }
        else{
            error = 1;
            printf("Loi cu phap...");
        }
    }
}

State statement(char*str, char ch, int current_index, int &error){
    State result;
    if(Token == IDENT){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == LBRACK){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = expression(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == RBRACK){
                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                if(Token == ASSIGN){
                    result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    result = expression(str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    return result;
                }
                else{
                    error = 1;
                    printf("Thieu toan tu gan...");
                }
            }
            else{
                error = 1;
                printf("Thieu dau ngoac vuong...");
            }
        }
        else if(Token == ASSIGN){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = expression(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            return result;
        }
        else{
            error = 1;
            printf("Thieu toan tu gan...");
        }
    }
    else if(Token == CALL){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            if(Token == LPARENT){
                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                result = expression(str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                while(Token == COMMA){
                    result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    result = expression(str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                }
                if(Token == RPARENT){
                    result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                }
                else{
                    error = 1;
                    printf("Thieu dau ngoac...");
                }
            }
            return result;
        }
        else{
            error = 1;
            printf("Thieu ten thu tuc/ham...");
        }
    }
    else if(Token == BEGIN){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        result = statement(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        while(Token == SEMICOLON){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = statement(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
        }
        if(Token == END){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            return result;
        }
        else{
            error = 1;
            printf("Thieu tu khoa END...");
        }
    }
    else if(Token == IF){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        result = condition(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        if(Token == THEN){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = statement(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == ELSE){
                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                result = statement(str, result.current_char, result.current_index, error);
                Token = result.nameToken;
            }
            return result;
        }
        else{
            error = 1;
            printf("Thieu thu tuc THEN...");
        }
    }
    else if(Token == WHILE){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        result = condition(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        if(Token == DO){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = statement(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            return result;
        }
        else{
            error = 1;
            printf("Thieu thu tuc DO...");
        }
    }
    else if(Token == FOR){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == ASSIGN){
                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                result = expression(str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                if(Token == TO){
                    result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    result = expression(str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    if(Token == DO){
                        result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        result = statement(str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        return result;
                    }
                    else{
                        error = 1;
                        printf("Thieu thu tuc DO...");
                    }
                }
                else{
                    error = 1;
                    printf("Thieu thu tuc TO...");
                }
            }
            else{
                error = 1;
                printf("Thieu toan tu gan...");
            }
        }
        else{
            error = 1;
            printf("Thieu ten IDENT...");
        }
    }
}

void block(char*str, char ch, int current_index, int &error){
    State result;
    bool flag_const = false;
    bool flag_var = false;
    bool flag_procedure = false;
    if(Token == CONST){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == EQU){
                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                if(Token == NUMBER){
                    result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    while(Token == COMMA){
                        result = getToken(letters, digits, str, ch, current_index, error);
                        Token = result.nameToken;
                        if(Token == IDENT){
                            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                            Token = result.nameToken;
                            if(Token == EQU){
                                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                                Token = result.nameToken;
                                if(Token == NUMBER){
                                    result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                                    Token = result.nameToken;
                                }
                            }
                        }
                    }
                    if(Token == SEMICOLON){
                        result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        flag_const = true;
                    }
                }
            }
        }
    }
    if(Token == VAR){
        if(flag_const == false){
            result = getToken(letters, digits, str, ch, current_index, error);
            Token = result.nameToken;
        }
        else{
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            flag_const = false;
        }
        if(Token == IDENT){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == LBRACK){
                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                if(Token == NUMBER){
                    result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    if(Token == RBRACK){
                        result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                    }
                }
            }
            while(Token == COMMA){
                result = getToken(letters, digits, str, ch, current_index, error);
                Token = result.nameToken;
                if(Token == IDENT){
                    result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    if(Token == LBRACK){
                        result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        if(Token == NUMBER){
                            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                            Token = result.nameToken;
                            if(Token == RBRACK){
                                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                                Token = result.nameToken;
                            }
                        }
                    }
                }
            }
            if(Token == SEMICOLON){
                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                flag_var = true;
            }
        }
    }
    if(Token == PROCEDURE){
        if(flag_var == false){
            result = getToken(letters, digits, str, ch, current_index, error);
            Token = result.nameToken;
        }
        else{
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            flag_var = false;
        }
        if(Token == IDENT){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == LPARENT){
                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                Token = parameters(str, result.current_char, result.current_index, error);
                while(Token == SEMICOLON){
                    result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    Token = parameters(str, result.current_char, result.current_index, error);
                }
                if(Token == RPARENT){
                    result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    if(Token == SEMICOLON){
                        result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        block(str, result.current_char, result.current_index, error);
                        result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        if(Token == SEMICOLON){
                            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                            Token = result.nameToken;
                            flag_procedure = true;
                        }
                    }
                }
            }
        }
    }
    if(Token == BEGIN){
        if(flag_const == false && flag_procedure == false && flag_var == false){
            result = getToken(letters, digits, str, ch, current_index, error);
            Token = result.nameToken;
        }
        else{
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
        }
        statement(str, result.current_char, result.current_index, error);
        while(Token == SEMICOLON){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            statement(str, result.current_char, result.current_index, error);
        }
        if(Token == END){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
        }
    }
}

TokenType parameters(char*str, char ch, int current_index, int &error){
    State result;
    if(Token == VAR){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
        }
        return Token;
    }
    else if(Token == IDENT){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        return Token;
    }
}

void program(char*str, char ch, int current_index, int &error){
    State result;
    if(Token == PROGRAM){
        result = getToken(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getToken(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == SEMICOLON){
                result = getToken(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                block(str, result.current_char, result.current_index, error);
                if(Token == PERIOD){
                    printf("Thanh cong...");
                }
                else{
                    printf("Thieu dau cham cau...");
                }
            }
            else{
                printf("Thieu dau cham phay...");
            }
        }
        else{
            printf("Thieu ten chuong trinh...");
        }
    }
    else{
        printf("Thieu tu khoa PROGRAM...");
    }
}

void compile(char* filename){
	int error = 0;
    char line[MAX_CHARACTER_IN_LINE];
    FILE* file = fopen(filename, "r");
	//initial_TokenArray(TokenArray);
    while (fgets(line, sizeof(line), file)) {
        int len = strlen(line); // do dai cua dong trong file
        State result = getToken(letters, digits, line, line[0], 0, error);
        Token = result.nameToken;
        result = condition(line, result.current_char, result.current_index, error);
        printf("%d", result.nameToken);
    }
	fclose(file);
}

int	main(int argc, char * argv[]){
	if(argc == 1) compile((char*)"data/test.pl0");
    else if(argc == 2) compile((char*)argv[1]); 
	else printf("Syntax error \n");
 	return 0;
}
