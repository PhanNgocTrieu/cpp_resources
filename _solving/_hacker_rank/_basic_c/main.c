#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void digital_frequency(const char* string) {
    int matrix[10][1];
    for (int i = 48; i < 58; ++i) {
        matrix[i][0] = 0;
        printf("%c - %d\n", (char)i, matrix[i][0]);
    }

    for (int i = 0; i < strlen(string); ++i) {
        if ((int)*(string + i) >= (int)'0' && 
            (int)*(string + i) <= (int)'9') {
            matrix[(int)(*(string + i))][0]++;
        }
    }

    for (int i = 48; i < 58; ++i) {
        printf("%c - %d\n", (char)i, matrix[i][0]);
        if (i == 57) {
            printf("\n");
            break;
        }
    }
}

int main()
{
    char* s;
    s = malloc(1024 * sizeof(char));
    // Reading whole line until get the '\n'
    scanf("%[^\n]",s);
    digital_frequency("a11472o5t6");
    return 0;
}   