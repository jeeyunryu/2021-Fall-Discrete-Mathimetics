#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_input(int sudo_board[][9],  int x, int y);
void print_input(int sudo_board[][9], int x, int y);

const int W = 9;
const int H = 9;
int main()
{
    int x = 9;
    int y = 9;

    int i, j, n, m, s, r;

    
    int sudo_board[9][9];

   

    get_input(sudo_board, x, y);

    FILE *fp = fopen("formula", "w");

    for (i = 1; i <= 9; i++)
    {
        for (j = 1; j <= 9; j++)
        {
            for (n = 1; n <= 9; n++)
            {
                fprintf(fp, "(declare-const p%d%d%d Bool)\n", i, j, n);
            }
        }
    }
    fprintf(fp, "\n");

    // S0
    fprintf(fp, "; S0\n");
    fprintf(fp, "(assert ");
    fprintf(fp, "(and ");
    for (i = 0; i < x; i++)
    {
        for (j = 0; j < y; j++)
        {
            if (sudo_board[i][j] <= 9 && sudo_board[i][j] >= 1)
            {
                fprintf(fp, "p%d%d%d ", i + 1, j + 1, sudo_board[i][j]);
            }
        }
    }
    fprintf(fp, "))\n");

    // S1
    fprintf(fp, "; S1\n");
    fprintf(fp, "(assert (and ");
    for (i = 1; i <= 9; i++)
    {
        fprintf(fp, "(and ");
        for (j = 1; j <= 9; j++)
        {
            fprintf(fp, "(and ");
            for (n = 1; n <= 8; n++)
            {
                fprintf(fp, "(and ");
                for (m = n + 1; m <= 9; m++)
                {
                    fprintf(fp, "(not (and p%d%d%d p%d%d%d))", i, j, n, i, j, m);
                }
                fprintf(fp, ")");
            }
            fprintf(fp, ")");
        }
        fprintf(fp, ")");
    }
    fprintf(fp, "))\n");

    //S1-1
    fprintf(fp, "; S1-1\n");
    fprintf(fp, "(assert ");
    fprintf(fp, "(and ");
    for (i = 1; i <= 9; i++)
    {
        fprintf(fp, "(and ");
        for (j = 1; j <= 9; j++)
        {
            fprintf(fp, "(or ");
            for (n = 1; n <= 9; n++)
            {
                fprintf(fp, "p%d%d%d ", i, j, n);
            }
            fprintf(fp, ")");
        }
        fprintf(fp, ") ");
    }
    fprintf(fp, "))\n");

    // S2
    fprintf(fp, "; S2\n");
    fprintf(fp, "(assert ");
    fprintf(fp, "(and ");
    for (i = 1; i <= 9; i++)
    {
        fprintf(fp, "(and ");
        for (n = 1; n <= 9; n++)
        {
            fprintf(fp, "(or ");
            for (j = 1; j <= 9; j++)
            {
                fprintf(fp, "p%d%d%d ", i, j, n);
            }
            fprintf(fp, ")");
        }
        fprintf(fp, ")");
    }
    fprintf(fp, "))\n");

    // S3
    fprintf(fp, "; S3\n");
    fprintf(fp, "(assert ");
    fprintf(fp, "(and ");
    for (j = 1; j <= 9; j++)
    {
        fprintf(fp, "(and ");
        for (n = 1; n <= 9; n++)
        {
            fprintf(fp, "(or ");
            for (i = 1; i <= 9; i++)
            {
                fprintf(fp, "p%d%d%d ", i, j, n);
            }
            fprintf(fp, ")");
        }
        fprintf(fp, ")");
    }
    fprintf(fp, "))\n");

    //S4
    fprintf(fp, "; S4\n");
    fprintf(fp, "(assert (and ");
    for (r = 0; r <= 2; r++)
    {
        fprintf(fp, "(and ");
        for (s = 0; s <= 2; s++)
        {
            fprintf(fp, "(and ");
            for (n = 1; n <= 9; n++)
            {
                fprintf(fp, "(or ");
                for (i = 1; i <= 3; i++)
                {
                    fprintf(fp, "(or ");
                    for (j = 1; j <= 3; j++)
                    {
                        fprintf(fp, "p%d%d%d ", 3 * r + i, 3 * s + j, n);
                    }
                    fprintf(fp, ")");
                }
                fprintf(fp, ")");
            }
            fprintf(fp, ")");
        }
        fprintf(fp, ")");
    }
    fprintf(fp, "))\n");

    // S5
    fprintf(fp, "; S5\n");
    fprintf(fp, "(assert ");
    fprintf(fp, "(and ");
    for (i = 1; i <= 2; i++)
    {
        fprintf(fp, "(and ");
        for (j = 2; j <= 9; j++)
        {
            fprintf(fp, "(and ");
            for (n = 1; n <= 9; n++)
            {
                fprintf(fp, "(not (and p%d%d%d p%d%d%d))", 3*i, j, n, 3*i+1, j-1, n);
            }
            fprintf(fp, ")");
        }
        fprintf(fp, ")");
    }
    fprintf(fp, "))\n");

    // S5-1
    fprintf(fp, "; S5-1\n");
    fprintf(fp, "(assert ");
    fprintf(fp, "(and ");
    for (i = 1; i <= 2; i++)
    {
        fprintf(fp, "(and ");
        for (j = 1; j <= 8; j++)
        {
            fprintf(fp, "(and ");
            for (n = 1; n <= 9; n++)
            {
                fprintf(fp, "(not (and p%d%d%d p%d%d%d))", 3*i, j, n, 3*i+1, j+1, n);
            }
            fprintf(fp, ")");
        }
        fprintf(fp, ")");
    }
    fprintf(fp, "))\n");

    // S5-2
    fprintf(fp, "; S5-2\n");
    fprintf(fp, "(assert ");
    fprintf(fp, "(and ");
    for (j = 1; j <= 2; j++)
    {
        fprintf(fp, "(and ");
        for (i = 2; i <= 9; i++)
        {
            fprintf(fp, "(and ");
            for (n = 1; n <= 9; n++)
            {
                fprintf(fp, "(not (and p%d%d%d p%d%d%d))", i, 3*j, n, i-1, 3*j+1, n);
            }
            fprintf(fp, ")");
        }
        fprintf(fp, ")");
    }
    fprintf(fp, "))\n");

    // S5-3
    fprintf(fp, "; S5-3\n");
    fprintf(fp, "(assert ");
    fprintf(fp, "(and ");
    for (j = 1; j <= 2; j++)
    {
        fprintf(fp, "(and ");
        for (i = 1; i <= 8; i++)
        {
            fprintf(fp, "(and ");
            for (n = 1; n <= 9; n++)
            {
                fprintf(fp, "(not (and p%d%d%d p%d%d%d))", i, 3*j, n, i+1, 3*j+1, n);
            }
            fprintf(fp, ")");
        }
        fprintf(fp, ")");
    }
    fprintf(fp, "))\n");

    fprintf(fp, "\n(check-sat)\n(get-model)\n");

    fclose(fp);

    FILE *fin = popen("z3 formula", "r");
    char buf[128];
    fscanf(fin, "%s %s", buf, buf);
    char temp[128];
    while (!feof(fin))
    {
        temp[0] = '\0';

        fscanf(fin, "%s", buf); //printf("%s ", buf) ;
        fscanf(fin, "%s", buf); //printf("%s ", buf) ;
        strcpy(temp, buf);

        fscanf(fin, "%s", buf); //printf("%s ", buf) ;
        fscanf(fin, "%s", buf); //printf("%s ", buf) ;
        fscanf(fin, "%s", buf); //printf("%s\n", buf) ;

        if (strcmp(buf, "true)") == 0)
        {
            int x = temp[1] - '0';
            int y = temp[2] - '0';
            int n = temp[3] - '0';

            sudo_board[x - 1][y - 1] = n;
        }
    }

    print_input(sudo_board, x, y);

    pclose(fin);

    return 0;
}

void get_input(int sudo_board[][9], int x, int y)
{
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            char input[4];
            scanf("%s", input);
            sudo_board[i][j] = input[0] - '0';
        }
    }
}

void print_input(int sudo_board[][9], int x, int y){
    printf("\n");
    printf("------------------------\n");
    for (int i = 0; i < y; i++)
    {
        printf("|");
        for (int j = 0; j < x; j++)
        {
            printf("%d ", sudo_board[i][j]);
            if ((j + 1) % 3 == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % 3 == 0)
            printf("------------------------\n");
    } 
}
