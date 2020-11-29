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
State statement(char*str, char ch, int current_index, int &error);
State block(char*str, char ch, int current_index, int &error);
State program(char*str, char ch, int current_index, int &error);

TokenType Token;

State getTokenRenew(char* letters, char* digits, char* str, char ch, int current_index, int &error){
    State result = getToken(letters, digits, str, ch, current_index, error);
    Token = result.nameToken;
    while(Token == NONE){
        result = getToken(letters, digits, str, result.current_char, result.current_index, error);
        Token = result.nameToken;
    }
    return result;
}

State factor(char*str, char ch, int current_index, int &error){
    State result;
    if(Token == IDENT){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == LBRACK){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = expression(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == RBRACK){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
            }
            else{
                error = 1;
                printf("Thieu dau ngoac vuong tai factor...");
            }
        }
        return result;
    }
    else if(Token == NUMBER){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        return result;
    }
    else if(Token == LPARENT){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        result = expression(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        if(Token == RPARENT){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            return result;
        }
        else{
            error = 1;
            printf("Thieu dau ngoac tron tai factor...");
        }
    }
    return result;
}

State term(char*str, char ch, int current_index, int &error){
    State result;
    result = factor(str, ch, current_index, error);
    Token = result.nameToken;
    while(Token == TIMES || Token == SLASH || Token == PERCENT){
        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
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
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
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
        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        result = term(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
    }
    return result;
}

State condition(char*str, char ch, int current_index, int &error){
    State result;
    if(Token == ODD){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        result = expression(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        return result;
    }
    else{
        result = expression(str, ch, current_index, error);
        if(Token == EQU || Token == NEQ || Token == LSS || Token == LEQ || Token == GTR || Token == GEQ){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = expression(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            return result;
        }
        else{
            error = 1;
            printf("Loi cu phap tai condition...");
        }
    }
    return result;
}

State statement(char*str, char ch, int current_index, int &error){
    State result;
    if(Token == IDENT){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == LBRACK){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = expression(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == RBRACK){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                if(Token == ASSIGN){
                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    result = expression(str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    return result;
                }
                else{
                    error = 1;
                    printf("Thieu toan tu gan tai statement...");
                }
            }
            else{
                error = 1;
                printf("Thieu dau ngoac vuong tai statement...");
            }
        }
        else if(Token == ASSIGN){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = expression(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            return result;
        }
        else{
            error = 1;
            printf("Thieu toan tu gan tai statement...");
        }
    }
    else if(Token == CALL){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == LPARENT){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                result = expression(str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                while(Token == COMMA){
                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    result = expression(str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                }
                if(Token == RPARENT){
                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                }
                else{
                    error = 1;
                    printf("Thieu dau ngoac trong tai statement...");
                }
            }
            return result;
        }
        else{
            error = 1;
            printf("Thieu ten thu tuc/ham tai statement...");
        }
    }
    else if(Token == BEGIN){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        result = statement(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        while(Token == SEMICOLON){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = statement(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
        }
        if(Token == END){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            return result;
        }
        else{
            error = 1;
            printf("Thieu tu khoa END tai statement...");
        }
    }
    else if(Token == IF){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        result = condition(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        if(Token == THEN){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = statement(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == ELSE){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                result = statement(str, result.current_char, result.current_index, error);
                Token = result.nameToken;
            }
            return result;
        }
        else{
            error = 1;
            printf("Thieu thu tuc THEN tai statement...");
        }
    }
    else if(Token == WHILE){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        result = condition(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        if(Token == DO){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = statement(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            return result;
        }
        else{
            error = 1;
            printf("Thieu thu tuc DO tai statement...");
        }
    }
    else if(Token == FOR){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == ASSIGN){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                result = expression(str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                if(Token == TO){
                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    result = expression(str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    if(Token == DO){
                        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        result = statement(str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        return result;
                    }
                    else{
                        error = 1;
                        printf("Thieu thu tuc DO tai statement...");
                    }
                }
                else{
                    error = 1;
                    printf("Thieu thu tuc TO tai statement...");
                }
            }
            else{
                error = 1;
                printf("Thieu toan tu gan tai statement...");
            }
        }
        else{
            error = 1;
            printf("Thieu ten IDENT tai statement...");
        }
    }
    return result;
}

State parameters(char*str, char ch, int current_index, int &error){
    State result;
    if(Token == VAR){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
        }
        return result;
    }
    else if(Token == IDENT){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        return result;
    }
    return result;
}

State block(char*str, char ch, int current_index, int &error){
    State result = create_state(NONE, (char*)"NONE", ch, current_index, 4);
    if(Token == CONST){
        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == EQU){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                if(Token == NUMBER){
                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    while(Token == COMMA){
                        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        if(Token == IDENT){
                            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                            Token = result.nameToken;
                            if(Token == EQU){
                                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                                Token = result.nameToken;
                                if(Token == NUMBER){
                                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                                    Token = result.nameToken;
                                }
                                else{
                                    error = 1;
                                    printf("Thieu gia tri duoc gan tai block...");
                                }
                            }
                            else{
                                error = 1;
                                printf("Thieu tu khoa EQU tai block...");
                            }
                        }
                        else{
                            error = 1;
                            printf("Thieu ten IDENT tai block...");
                        }
                    }
                    if(Token == SEMICOLON){
                        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                    }
                    else{
                        error = 1;
                        printf("Thieu dau cham phay tai block...");
                    }
                }
                else{
                    error = 1;
                    printf("Thieu gia tri gan cho CONST tai block...");
                }
            }
            else{
                error = 1;
                printf("Thieu tu khoa EQU tai block...");
            }
        }
        else{
            error = 1;
            printf("Thieu ten IDENT tai block...");
        }
    }
    if(Token == VAR){
        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == LBRACK){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                if(Token == NUMBER){
                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    if(Token == RBRACK){
                        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                    }
                    else{
                        error = 1;
                        printf("Thieu dau ngoac vuong tai block...");
                    }
                }
                else{
                    error = 1;
                    printf("Thieu chi so cho mang block...");
                }
            }
            while(Token == COMMA){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                if(Token == IDENT){
                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    if(Token == LBRACK){
                        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        if(Token == NUMBER){
                            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                            Token = result.nameToken;
                            if(Token == RBRACK){
                                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                                Token = result.nameToken;
                            }
                            else{
                                error = 1;
                                printf("Thieu dau ngoac vuong tai block...");
                            }
                        }
                        else{
                            error = 1;
                            printf("Thieu chi so cho mang tai block...");
                        }
                    }
                }
                else{
                    error = 1;
                    printf("Thieu ten IDENT tai block...");
                }
            }
            if(Token == SEMICOLON){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
            }
            else{
                error = 1;
                printf("Thieu dau cham phay tai block...");
            }
        }
        else{
            error = 1;
            printf("Thieu ten IDENT tai block...");
        }
    }
    if(Token == PROCEDURE){
        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == LPARENT){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                result = parameters(str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                while(Token == SEMICOLON){
                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    result = parameters(str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                }
                if(Token == RPARENT){
                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    if(Token == SEMICOLON){
                        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        result = block(str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                        if(Token == SEMICOLON){
                            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                            Token = result.nameToken;
                        }
                        else{
                            error = 1;
                            printf("Thieu dau cham phay tai block...");
                        }
                    }
                    else{
                        error = 1;
                        printf("Thieu dau cham phay tai block...");
                    }
                }
                else{
                    error = 1;
                    printf("Thieu dau ngoac tron tai block...");
                }
            }
            else{
                if(Token == SEMICOLON){
                    result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    result = block(str, result.current_char, result.current_index, error);
                    Token = result.nameToken;
                    if(Token == SEMICOLON){
                        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                        Token = result.nameToken;
                    }
                    else{
                        error = 1;
                        printf("Thieu dau cham phay tai block...");
                    }
                }
                else{
                    error = 1;
                    printf("Thieu dau cham phay tai block...");
                }
            }
        }
        else{
            error = 1;
            printf("Thieu ten IDENT tai block...");
        }
    }
    if(Token == BEGIN){
        result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        result = statement(str, result.current_char, result.current_index, error);
        Token = result.nameToken;
        while(Token == SEMICOLON){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            result = statement(str, result.current_char, result.current_index, error);
            Token = result.nameToken;
        }
        if(Token == END){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
        }
        else{
            error = 1;
            printf("Thieu tu khoa END tai block...");
        }
    }
    return result;
}

State program(char*str, char ch, int current_index, int &error){
    State result;
    if(Token == PROGRAM){
        result = getTokenRenew(letters, digits, str, ch, current_index, error);
        Token = result.nameToken;
        if(Token == IDENT){
            result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
            Token = result.nameToken;
            if(Token == SEMICOLON){
                result = getTokenRenew(letters, digits, str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                result = block(str, result.current_char, result.current_index, error);
                Token = result.nameToken;
                if(Token == PERIOD){
                    if(error == 0)
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
    return result;
}

void compile(char* filename){
	int error = 0;
    char line[MAX_CHARACTER_IN_LINE];
    char lines[MAX_CHARACTER_IN_LINE];
    lines[0] = ' ';
    FILE* file = fopen(filename, "r");
    while (fgets(line, sizeof(line), file)) {
    	int len = strlen(line);
    	if(line[len - 1] == '\n' || line[len - 1] == '\t')
    		line[len - 1] = ' ';
        strcat(lines, line);
        strcat(lines, " ");
    }
    initial_TokenArray(TokenArray);
    State result;
    result = getTokenRenew(letters, digits, lines, lines[0], 0, error);
    Token = result.nameToken;
    if(error_number == 1){
        printf("Loi so qua lon...");
    }
    result = program(lines, result.current_char, result.current_index, error);
	fclose(file);
}

int	main(int argc, char * argv[]){
	if(argc == 1) compile((char*)"data/t.cond.pl0");
    else if(argc == 2) compile((char*)argv[1]); 
	else printf("Syntax error \n");
 	return 0;
}
