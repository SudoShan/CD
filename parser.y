
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);

int temp = 0, label = 0;

char elseLabel[20], exitLabel[20];
char begin[20], loopExit[20];

char currentType[20];

/* Simple for-loop variables */
char forBegin[20], forExit[20];
char forVar[20], forOp[5];
%}

%union {
    char str[20];
}

%token <str> ID NUM
%token INT FLOAT CHAR DOUBLE
%token IF ELSE WHILE FOR CONTINUE BREAK DO
%token LE GE NE EQ AND OR NOT
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN INC DEC
%token IFX

%type <str> expression condition assignment type

/* Dangling else */
%nonassoc IFX
%nonassoc ELSE

/* Operator precedence */
%left OR
%left AND
%right NOT
%nonassoc '<' '>' LE GE EQ NE
%left '+' '-'
%left '*' '/' '%'

%%

program
    : statementList
      {
          printf("Syntax is valid\n");
      }
    ;

statementList
    : statementList statement
    |
    ;

statement
    : declaration ';'

    | assignment ';'

    /* IF without ELSE */
    | ifHeader statement %prec IFX
      {
          printf("%s:\n", elseLabel);
      }

    /* IF-ELSE */
    | ifHeader statement ELSE
      {
          printf("goto %s\n", exitLabel);
          printf("%s:\n", elseLabel);
      }
      statement
      {
          printf("%s:\n", exitLabel);
      }

    /* WHILE loop */
    | WHILE
      {
          sprintf(begin, "L%d", ++label);
          printf("%s:\n", begin);
      }
      '(' condition ')'
      {
          sprintf(loopExit, "L%d", ++label);
          printf("ifFalse %s goto %s\n", $4, loopExit);
      }
      statement
      {
          printf("goto %s\n", begin);
          printf("%s:\n", loopExit);
      }

    /* FOR loop: initialization; condition; i++/i-- */
    | FOR '(' assignment ';'
      {
          sprintf(forBegin, "L%d", ++label);
          printf("%s:\n", forBegin);
      }
      condition ';'
      {
          sprintf(forExit, "L%d", ++label);
          printf("ifFalse %s goto %s\n", $6, forExit);
      }
      forUpdate ')'
      statement
      {
          sprintf($<str>$, "t%d", ++temp);

          if (strcmp(forOp, "++") == 0)
              printf("%s = %s + 1\n", $<str>$, forVar);
          else
              printf("%s = %s - 1\n", $<str>$, forVar);

          printf("%s = %s\n", forVar, $<str>$);
          printf("goto %s\n", forBegin);
          printf("%s:\n", forExit);
      }

    | '{' statementList '}'

    | CONTINUE ';'
      {
          printf("continue;\n");
      }

    | BREAK ';'
      {
          printf("break;\n");
      }

    | DO statement WHILE '(' condition ')' ';'
      {
          printf("if %s goto L%d\n", $5, label);
      }

    | ';'
    | error ';'
    {
        yyerrok;
    }
    ;

ifHeader
    : IF '(' condition ')'
      {
          sprintf(elseLabel, "L%d", ++label);
          sprintf(exitLabel, "L%d", ++label);
          printf("ifFalse %s goto %s\n", $3, elseLabel);
      }
    ;

/* Variable declarations */
declaration
    : type ID
      {
          printf("declare %s %s\n", $1, $2);
          strcpy(currentType, $1);
      }

    | declaration ',' ID
      {
          printf("declare %s %s\n", currentType, $3);
      }
    ;

type
    : INT
      {
          strcpy($$, "int");
      }

    | FLOAT
      {
          strcpy($$, "float");
      }

    | CHAR
      {
          strcpy($$, "char");
      }

    | DOUBLE
      {
          strcpy($$, "double");
      }
    ;

/* FOR update: only i++ or i-- */
forUpdate
    : ID INC
      {
          strcpy(forVar, $1);
          strcpy(forOp, "++");
      }

    | ID DEC
      {
          strcpy(forVar, $1);
          strcpy(forOp, "--");
      }
    ;

assignment
    : ID '=' expression
      {
          strcpy($$, $1);
          printf("%s = %s\n", $1, $3);
      }

    | ID ADD_ASSIGN expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s + %s\n", $$, $1, $3);
          printf("%s = %s\n", $1, $$);
      }

    | ID SUB_ASSIGN expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s - %s\n", $$, $1, $3);
          printf("%s = %s\n", $1, $$);
      }

    | ID MUL_ASSIGN expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s * %s\n", $$, $1, $3);
          printf("%s = %s\n", $1, $$);
      }

    | ID DIV_ASSIGN expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s / %s\n", $$, $1, $3);
          printf("%s = %s\n", $1, $$);
      }

    | ID INC
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s + 1\n", $$, $1);
          printf("%s = %s\n", $1, $$);
      }

    | ID DEC
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s - 1\n", $$, $1);
          printf("%s = %s\n", $1, $$);
      }
    ;

expression
    : expression '+' expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s + %s\n", $$, $1, $3);
      }

    | expression '-' expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s - %s\n", $$, $1, $3);
      }

    | expression '*' expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s * %s\n", $$, $1, $3);
      }

    | expression '/' expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s / %s\n", $$, $1, $3);
      }

    | expression '%' expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s %% %s\n", $$, $1, $3);
      }

    | '(' expression ')'
      {
          strcpy($$, $2);
      }

    | ID
      {
          strcpy($$, $1);
      }

    | NUM
      {
          strcpy($$, $1);
      }
    ;

condition
    : expression '<' expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s < %s\n", $$, $1, $3);
      }

    | expression '>' expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s > %s\n", $$, $1, $3);
      }

    | expression LE expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s <= %s\n", $$, $1, $3);
      }

    | expression GE expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s >= %s\n", $$, $1, $3);
      }

    | expression EQ expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s == %s\n", $$, $1, $3);
      }

    | expression NE expression
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s != %s\n", $$, $1, $3);
      }

    | condition AND condition
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s && %s\n", $$, $1, $3);
      }

    | condition OR condition
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = %s || %s\n", $$, $1, $3);
      }

    | NOT condition
      {
          sprintf($$, "t%d", ++temp);
          printf("%s = !%s\n", $$, $2);
      }

    | '(' condition ')'
      {
          strcpy($$, $2);
      }
    ;

%%

void yyerror(const char *s)
{
    fprintf(stderr, "Syntax error: Invalid syntax\n");
}

int main(void)
{
    printf("Three Address Code:\n");
    return yyparse();
}
