void codeGeneration(void)
{
    char r[20], a[20], op[10], b[20];

    printf("\nTarget Code:\n");

    for (int i = 0; i < codeCount; i++)
    {
        int n = sscanf(code[i], "%19s = %19s %9s %19s",
                       r, a, op, b);

        /* Simple assignment */
        if (n == 2)
        {
            printf("MOV R0, %s\n", a);
            printf("MOV %s, R0\n", r);
        }

        /* Arithmetic operations */
        else if (n == 4 &&
                 (strcmp(op, "+") == 0 ||
                  strcmp(op, "-") == 0 ||
                  strcmp(op, "*") == 0 ||
                  strcmp(op, "/") == 0 ||
                  strcmp(op, "%") == 0))
        {
            printf("MOV R0, %s\n", a);

            if (strcmp(op, "+") == 0)
                printf("ADD R0, %s\n", b);
            else if (strcmp(op, "-") == 0)
                printf("SUB R0, %s\n", b);
            else if (strcmp(op, "*") == 0)
                printf("MUL R0, %s\n", b);
            else if (strcmp(op, "/") == 0)
                printf("DIV R0, %s\n", b);
            else
                printf("MOD R0, %s\n", b);

            printf("MOV %s, R0\n", r);
        }

        /* Relational operations */
        else if (n == 4 &&
                 (strcmp(op, "<") == 0 ||
                  strcmp(op, ">") == 0 ||
                  strcmp(op, "<=") == 0 ||
                  strcmp(op, ">=") == 0 ||
                  strcmp(op, "==") == 0 ||
                  strcmp(op, "!=") == 0))
        {
            printf("MOV R0, %s\n", a);
            printf("CMP R0, %s\n", b);

            if (strcmp(op, "<") == 0)
                printf("SETL R0\n");
            else if (strcmp(op, ">") == 0)
                printf("SETG R0\n");
            else if (strcmp(op, "<=") == 0)
                printf("SETLE R0\n");
            else if (strcmp(op, ">=") == 0)
                printf("SETGE R0\n");
            else if (strcmp(op, "==") == 0)
                printf("SETE R0\n");
            else
                printf("SETNE R0\n");

            printf("MOV %s, R0\n", r);
        }

        /* ifFalse condition goto L1 */
        else if (strncmp(code[i], "ifFalse ", 8) == 0)
        {
            char cond[20], dest[20];

            sscanf(code[i], "ifFalse %19s goto %19s",
                   cond, dest);

            printf("MOV R0, %s\n", cond);
            printf("CMP R0, 0\n");
            printf("JE %s\n", dest);
        }

        /* if a < b goto L1 */
        else if (strncmp(code[i], "if ", 3) == 0)
        {
            char x[20], cond[10], y[20], dest[20];

            sscanf(code[i], "if %19s %9s %19s goto %19s",
                   x, cond, y, dest);

            printf("MOV R0, %s\n", x);
            printf("CMP R0, %s\n", y);

            if (strcmp(cond, "<") == 0)
                printf("JL %s\n", dest);
            else if (strcmp(cond, ">") == 0)
                printf("JG %s\n", dest);
            else if (strcmp(cond, "<=") == 0)
                printf("JLE %s\n", dest);
            else if (strcmp(cond, ">=") == 0)
                printf("JGE %s\n", dest);
            else if (strcmp(cond, "!=") == 0)
                printf("JNE %s\n", dest);
            else if (strcmp(cond, "==") == 0)
                printf("JE %s\n", dest);
        }

        /* Unconditional jump */
        else if (strncmp(code[i], "goto ", 5) == 0)
        {
            char dest[20];

            sscanf(code[i], "goto %19s", dest);
            printf("JMP %s\n", dest);
        }

        /* Labels */
        else if (strchr(code[i], ':') != NULL)
        {
            printf("%s\n", code[i]);
        }

        /* Declarations do not generate instructions here */
        else if (strncmp(code[i], "declare ", 8) == 0)
        {
            continue;
        }

        /* Instructions not handled yet */
        else
        {
            printf("; Unsupported: %s\n", code[i]);
        }
    }
}