#include "a2.h"

int bitwise_xor(int value)
{

    int keyint = (int)KEY;
    return value ^ keyint;
}

char *xor_encrypt(char c)
{

    // int a[7] = { 0 };
    char *a = (char *)malloc(sizeof(char) * 7 + 1);
    // initialize char values to 0
    for (int i = 0; i < 7; i++)
    {
        a[i] = '0';
    }
    int i = 0;
    int n = (int)c;
    int keyint = (int)KEY;
    int xor = c ^ KEY;
    // converting xor to binary
    while (xor > 0)
    {
        a[i] = xor % 2 + '0';
        xor = xor / 2;
        i++;
    }
    for (int j = 6; j >= 0; j--)
    {
        // //printf("%c", a[j]);
    }

    // //printf("\n");
    a[7] = '\0';
    strrev(a);

    return a;
}

char xor_decrypt(char *s)
{
    int value = 0;
    for (int i = 0; i < 7; i++)
    {
        value += (s[i] - 48) << (6 - i);
    }
    return bitwise_xor(value);
}
void print_code(char **code)
{

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            //printf("%c", code[i][j]);
            if (j == 15)
            {
                //printf("\n");
            }
        }
    }
}
char **make_blank_grid()
{
    char **grid = (char **)malloc(16 * sizeof(char *));
    for (int i = 0; i < 16; i++)
    {
        grid[i] = (char *)malloc(16 * sizeof(char));
    }
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grid[i][j] = '0';
            // code[i][j + 11] = '1';
            // code[i + 11][j] = '1';
        }
    }

    // print_code(grid);
    return grid;
}
char **do_corners(char **code)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            code[i][j] = '1';
            code[i][j + 11] = '1';
            code[i + 11][j] = '1';
        }
    }
    for (int i = 1; i < 4; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            if (i != 2)
            {
                code[i][j] = '0';
                code[i][j + 11] = '0';
                code[i + 11][j] = '0';
            }
            else
            {
                if (j != 2)
                {
                    code[i][j] = '0';
                    code[i][j + 11] = '0';
                    code[i + 11][j] = '0';
                }
            }
        }
    }
    code[15][15] = '1';
    return code;
}
char **make_blank_code()
{
    char **code = make_blank_grid();
    // make 3 corners all 0 first
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            code[i][j] = 'D';
            code[i][j + 11] = 'D';
            code[i + 11][j] = 'D';
        }
    }

    // blank char big D is funny
    code[15][15] = 'D';
    // print_code(code);
    return code;
}
char *string_enc(char *msg)
{
    char *enc = (char *)malloc(strlen(msg) * (7 + 1));
    char *temp = xor_encrypt(msg[0]);
    // //printf("%s\n", xor_encrypt(msg[0]));
    strcpy(enc, temp);
    // //printf("%d\n",(strlen(enc)));

    for (int i = 1; i < strlen(msg); i++)
    {
        // //printf("%s\n", enc);
        strcat(enc, xor_encrypt(msg[i]));
    }
    enc[strlen(msg) * 7] = '\0';

    return enc;
}
char *grid_to_string(char **code)
{
    char *out = malloc(256 + 1);
    int ind = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            out[ind++] = code[i][j];
        }
    }
    out[256] = '\0';
    // //printf("%s\n", out);
    return out;
}
char **undo_corners(char **code)
{

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            code[i][j] = 'D';
            code[i][j + 11] = 'D';
            code[i + 11][j] = 'D';
        }
    }
    for (int i = 1; i < 4; i++)
    {
        for (int j = 1; j < 4; j++)
        {
            if (i != 2)
            {
                code[i][j] = 'D';
                code[i][j + 11] = 'D';
                code[i + 11][j] = 'D';
            }
            else
            {
                if (j != 2)
                {
                    code[i][j] = 'D';
                    code[i][j + 11] = 'D';
                    code[i + 11][j] = 'D';
                }
            }
        }
    }
    code[15][15] = 'D';
    return code;
}
char *string_no_D(char **grid)
{
    int ind = 0;
    int usable_size = 180;
    char *out = malloc(181);
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            if (grid[i][j] != 'D')
            {
                // //printf("%c",grid[i][j]);
                out[ind++] = grid[i][j];
            }
        }
    }
    out[180] = '\0';
    // //printf("\n%s\n",out);
    return out;
}
void remove_corners(char *s1)
{
    char **grid = (char **)malloc(16 * sizeof(char *));
    for (int i = 0; i < 16; i++)
    {
        grid[i] = (char *)malloc(16 * sizeof(char));
    }

    int ind = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grid[i][j] = s1[ind++];
        }
    }
    grid = undo_corners(grid);
    print_code(grid);
    char *s2 = string_no_D(grid); // this returns a string of just the encrypted characters no corner nonsense
                                  // //printf("%s\n",s2);
    char *null_term = xor_encrypt('\0');
    char *mess = malloc(180 / 7 + 1); // num possible chars
    int indm = 0;
    // //printf("NULL TERM %s\n", null_term);
    int nul_term = 0;
    int i = 0;
    while (!nul_term)
    {

        char *temp = malloc(8);

        // //printf("%c\n", s2[i * 7]);
        strncpy(temp, &s2[i * 7], 7);
        temp[7] = '\0';
        // //printf("%s\n", temp);
        char decr = xor_decrypt(temp);
        mess[indm++] = decr;
        if (strcmp(temp, null_term) == 0)
        {
            nul_term = 1;
        }
        i++;
        free(temp);
    }
    //printf("%s\n", mess);
}
char *gen_code(char *msg)
{

    char *enc = string_enc(msg);
    // //printf("\n");
    char *nul_term = xor_encrypt('\0');
    // //printf("%s\n", nul_term);
    int x = strlen(nul_term);
    strcat(enc, nul_term);

    char **code = make_blank_code();

    int ind = 0;
    int i, j;

    for (i = 0; i < 16; i++)
    {
        for (j = 0; j < 16; j++)
        {
            if (code[i][j] != 'D' && ind < strlen(enc))
            {
                code[i][j] = enc[ind++];
            }
        }
    }
    code = do_corners(code);
    //   print_code(code);
    char *s1 = grid_to_string(code);
    for (int i = 0; i < 16; i++)
    {
        free(code[i]);
    }
    free(code);

    return s1;
}

char *read_code(char *code)
{
    char **grid = (char **)malloc(16 * sizeof(char *));
    for (int i = 0; i < 16; i++)
    {
        grid[i] = (char *)malloc(16 * sizeof(char));
    }

    int ind = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            grid[i][j] = code[ind++];
        }
    }
    grid = undo_corners(grid);
    // print_code(grid);
    char *s2 = string_no_D(grid); // this returns a string of just the encrypted characters no corner nonsense
                                  // //printf("%s\n",s2);
    char *null_term = xor_encrypt('\0');
    char *mess = malloc(180 / 7 + 1); // num possible chars
    int indm = 0;
    // //printf("NULL TERM %s\n", null_term);
    int nul_term = 0;
    int i = 0;
    while (!nul_term)
    {

        char *temp = malloc(8);

        // //printf("%c\n", s2[i * 7]);
        strncpy(temp, &s2[i * 7], 7);
        temp[7] = '\0';
        // //printf("%s\n", temp);
        char decr = xor_decrypt(temp);
        mess[indm++] = decr;
        if (strcmp(temp, null_term) == 0)
        {
            nul_term = 1;
        }
        i++;
        free(temp);
    }
    // //printf("%s\n", mess);
    for (int i = 0; i < 16; i++)
    {
        free(grid[i]);
    }
    free(grid);
    free(s2);
    // free grid
    // string_no_d s2
    return mess;
}
int decimal_to_bin(char *bin)
{
    int decimal = 0;
    int position = 0;
    int index = 3;
    while (index >= 0)
    {
        decimal = decimal + (bin[index] - 48) * pow(2, position);
        index--;
        position++;
    }
    return decimal;
}
char *compress(char *code)
{
    char *out = malloc(65);
    out[64] = '\0';

    // break into 4 turn those 4 into dec then hexa

    for (int i = 0; i < 64; i++)
    {
        char *cur_bin = malloc(5);
        strncpy(cur_bin, &code[4 * i], 4);
        cur_bin[4] = '\0';

        int cur_dec = decimal_to_bin(cur_bin);

        char *hex = malloc(sizeof(char) * 2);
        hex[1] = '\0';
        sprintf(hex, "%X", cur_dec);
        out[i] = hex[0];
    }
    // //printf("%s", out);
    return out;
}

int toBin(int dno)
{
    int bno = 0, remainder, f = 1;
    while (dno != 0)
    {
        remainder = dno % 2;
        bno = bno + remainder * f;
        f = f * 10;
        dno = dno / 2;
    }
    return bno;
}
char *decompress(char *code)
{
    char *out = malloc(257);
    out[0] = '\0';

    for (int i = 0; i < 64; i++)
    {
        if (code[i] >= 65)
        {

            int x = 10 + ((int)code[i] - 65);
            x = toBin(x);
            char *ar = malloc(5);

            sprintf(ar, "%04d", x);
            ar[5] = '\0';

            strncat(out, ar, 4);
            free(ar);
        }
        else
        {
            char *ar = malloc(5);
            // //printf("%d\n", (int)code[i] - 48);
            int x = toBin((int)code[i] - 48);
            sprintf(ar, "%04d", x);
            ar[5] = '\0';

            strncat(out, ar, 4);
            free(ar);
        }
    }
    // //printf("%s\n", out);
    return out;
}
int min(int a, int b){
    if(a < b) return a;
    return b;
}
int calc_ld(char *sandy, char *cima){
    // calculate the  Levenshtein distance between two strings
    int sLen = strlen(sandy);
    int cLen= strlen(cima);
    int **mat = malloc(sizeof(int *) * (sLen+ 1));
    for (int i = 0; i < sLen+ 1; i++) {
        mat[i] = malloc(sizeof(int) * (cLen+ 1));
    }

    //row is cima
    for (int j = 0; j < cLen+ 1; j++) {
        mat[0][j] = j;
    }
    //col sandy
      for (int i = 0; i < sLen+ 1; i++) {
        mat[i][0] = i;
    }
    //if substrings r same at index i j 
    for (int i = 1; i < sLen+ 1; i++) {
        for (int j = 1; j < cLen+ 1; j++) {
            if (sandy[i - 1] == cima[j - 1]) {
                mat[i][j] = mat[i - 1][j - 1];
            } else {
                mat[i][j] = 1 + min(mat[i - 1][j - 1], min(mat[i - 1][j], mat[i][j - 1]));
            }
        }
    }

    int mini = mat[sLen][cLen];

    for (int i = 0; i < sLen+ 1; i++) {
        free(mat[i]);
    }
    free(mat);
    return mini;
}

// int main()
// {
//     //printf("%d\n", calc_ld("COMMENCE", "CODING"));

//     //printf("%d\n", calc_ld("COMMENCE", "PROCRASTINATING"));
// }