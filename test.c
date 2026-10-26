int isNumber(const char *s)
{
    if (*s == '\0')
        return 0;

    for (int i = 0; s[i]; i++)
        if (s[i] < '0' || s[i] > '9')
            return 0;

    return 1;
}

int fold(char *result, const char *a, char op, const char *b)
{
    if (!isNumber(a) || !isNumber(b))
        return 0;

    long x = atol(a);
    long y = atol(b);
    long value;

    switch (op)
    {
    case '+':
        value = x + y;
        break;
    case '-':
        value = x - y;
        break;
    case '*':
        value = x * y;
        break;
    case '/':
        if (y == 0)
            return 0;
        value = x / y;
        break;
    case '%':
        if (y == 0)
            return 0;
        value = x % y;
        break;
    default:
        return 0;
    }

    sprintf(result, "%ld", value);
    return 1;
}

int simplify(char *result, const char *a, char op, const char *b)
{
    if (strcmp(b, "0") == 0)
    {
        if (op == '+' || op == '-')
        {
            strcpy(result, a);
            return 1;
        }

        if (op == '*')
        {
            strcpy(result, "0");
            return 1;
        }
    }

    if (strcmp(b, "1") == 0)
    {
        if (op == '*' || op == '/')
        {
            strcpy(result, a);
            return 1;
        }
    }

    if (strcmp(a, "0") == 0 && op == '*')
    {
        strcpy(result, "0");
        return 1;
    }

    if (strcmp(a, b) == 0 && op == '-')
    {
        strcpy(result, "0");
        return 1;
    }

    return 0;
}

#define MAX_CODE 1000
#define MAX_LEN 100

char code[MAX_CODE][MAX_LEN];
int codeCount = 0;

void emit(const char *s)
{
    if (codeCount < MAX_CODE)
        snprintf(code[codeCount++], MAX_LEN, "%s", s);
}

void commonSubexpressionElimination(void)
{
    char lhs[20], a[20], op[4], b[20];
    char prevLhs[20], prevA[20], prevOp[4], prevB[20];
    int i, j;

    for (i = 0; i < codeCount; i++)
    {
        /* Match: t = a operator b */
        if (sscanf(code[i], "%19s = %19s %3s %19s",
                   lhs, a, op, b) != 4)
            continue;

        for (j = 0; j < i; j++)
        {
            if (sscanf(code[j], "%19s = %19s %3s %19s",
                       prevLhs, prevA, prevOp, prevB) != 4)
                continue;

            if (strcmp(a, prevA) == 0 &&
                strcmp(op, prevOp) == 0 &&
                strcmp(b, prevB) == 0)
            {

                /* Replace repeated calculation with a copy */
                snprintf(code[i], MAX_LEN, "%s = %s",
                         lhs, prevLhs);
                break;
            }
        }
    }
}
int assignedInRange(const char *var, int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        char lhs[20];

        if (sscanf(code[i], "%19s =", lhs) == 1 &&
            strcmp(lhs, var) == 0)
            return 1;
    }

    return 0;
}

int isSimpleExpression(const char *line,
                       char *lhs, char *a, char *op, char *b)
{
    return sscanf(line, "%19s = %19s %3s %19s",
                  lhs, a, op, b) == 4;
}

void codeMotion(void)
{
    /* Find loop back-edges: goto Lx where Lx is a prior label */
    for (int end = 0; end < codeCount; end++)
    {
        char target[20];

        if (sscanf(code[end], "goto %19s", target) != 1)
            continue;

        int start = -1;

        for (int i = end - 1; i >= 0; i--)
        {
            char labelName[20];

            if (sscanf(code[i], "%19[^:]:", labelName) == 1 &&
                strcmp(labelName, target) == 0)
            {
                start = i;
                break;
            }
        }

        if (start == -1)
            continue;

        /* Check expressions inside the loop */
        for (int i = start + 1; i < end; i++)
        {
            char lhs[20], a[20], op[4], b[20];

            if (!isSimpleExpression(code[i], lhs, a, op, b))
                continue;

            /* Only move temporary calculations */
            if (lhs[0] != 't' ||
                !isdigit((unsigned char)lhs[1]))
                continue;

            /* Do not move if either operand changes inside the loop */
            if (assignedInRange(a, start + 1, end - 1) ||
                assignedInRange(b, start + 1, end - 1))
                continue;

            /* Insert the invariant instruction before the loop label */
            char invariant[MAX_LEN];
            strcpy(invariant, code[i]);

            for (int j = i; j > start; j--)
                strcpy(code[j], code[j - 1]);

            strcpy(code[start], invariant);

            /* Update loop boundaries after moving the instruction */
            start++;
            end++;
        }
    }
}