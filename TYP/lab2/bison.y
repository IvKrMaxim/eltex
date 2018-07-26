%{
    #include "lib2.h"
    extern FILE *yyin;
    extern int yylineno;
    extern int ch;
    extern char *yytext;
    char str1[] = "(";
    char str2[] = ")";;
    void yyerror (char *);
%}

%union {
    char *str;
    struct treenode *tree;
}

%token <str> LCONST 
%token <str> ID
%right <str> ASSIGN
%left <str> LOPER
%type <tree> program
%type <tree> statement
%type <tree> prim
%type <tree> expr
%type <tree> prim_id

%%

program: 	statement { $$ = $1; showtree($1, 0); printf("\n\n"); }
	| 	program statement { showtree($2, 0); printf("\n\n"); }
statement:	prim_id ASSIGN expr';' { $$ = createnode($2, $1, $3); }
	| 	prim_id ASSIGN '('expr')'';' { $$ = createnode($2, $1, $4); addtree($4, str1, str2); }
expr:		expr LOPER expr { $$ = createnode($2, $1, $3); }
	| 	'('expr')' LOPER '('expr')' { $$ = createnode($4, $2, $6); addtree($2, str1, str2); addtree($6, str1, str2);  }
	| 	'('expr')' LOPER expr { $$ = createnode($4, $2, $5); addtree($2, str1, str2); }
	|	expr LOPER '('expr')' { $$ = createnode($2, $1, $4); addtree($4, str1, str2); }
	|	prim { $$ = $1; }
prim: 		ID { $$ = createnode($1, NULL, NULL); }
	|	LCONST { $$ = createnode($1, NULL, NULL); }
prim_id:	ID { $$ = createnode($1, NULL, NULL); }
%%

void yyerror(char *errmsg) {
    fprintf(stderr, "%s (%d, %d): %s\n", errmsg, yylineno, ch, yytext);
}

int main(int argc, char **argv) {
    if (argc < 2) {
	printf("Not arguments\n");
	return -1;
    }
    if ((yyin = fopen(argv[1], "r")) == NULL) {
	printf("Cannot open file\n");
	return -1;
    }
    ch = 1;
    yylineno = 1;
    yyparse();
    return 0;
}