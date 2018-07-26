%option noyywrap yylineno

%{
    #include "lib.h"
    #include "bison.tab.h"
    int ch;
    extern void yyerror (char *);
    struct listnode *hashtab[HASH_SIZE];
%}

delim[();]
err[+\-*/\.]
letter[a-zA-Z]
digit[0-9]
ws[ \t\n]

%%

and|or|xor|not {
    //printf("LOGOPERATION (%d, %d): %s\n", yylineno, ch, yytext);
    ch += yyleng;
    yylval.str = strdup(yytext);
    return LOPER;
}
true|false {
    //printf("LOGCONST (%d, %d): %s\n", yylineno, ch, yytext);
    ch += yyleng;
    yylval.str = strdup(yytext);
    return LCONST;
}
("_"|{letter})("_"|{letter}|{digit})* {
    //printf("IDENTIFIER (%d, %d): %s\n", yylineno, ch, yytext);
    push_hash(hashtab, yytext, ch);
    ch += yyleng;
    yylval.str = strdup(yytext);
    return ID;
}
":=" { 
    //printf("ASSIGNATION (%d, %d): %s\n", yylineno, ch, yytext);
    ch += yyleng;
    yylval.str = strdup(yytext);
    return ASSIGN;
}
{delim} { 
    //printf("DELIMITER (%d, %d): %s\n", yylineno, ch, yytext);
    ch += yyleng;
    return *yytext;
}
{ws}+ { ch += yyleng; }
{err}|{digit} {
    yyerror("Unknown character");
    ch += yyleng;
}
%%
/*
int main (int argc, char **argv) {
    if (argc < 2) {
	printf("\nNot arguments.\n");
	return -1;
    }
    yyin = fopen(argv[1], "r");
    if (yyin == NULL) {
	printf("\nCannot open file\n");
	fclose (yyin);
	return 0;
    }
    ch = 1;
    yylineno = 1;
    hashtab_init(hashtab);
    yylex();
    print_hash(hashtab);
    fclose(yyin);
    return 0;
}
*/