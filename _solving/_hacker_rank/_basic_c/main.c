#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum BooleanRetcode{
    False = 0,
    True
};

typedef enum BooleanRetcode Bool;

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

Bool checking_word_only_number(const char* string) {
    for (int i = 0; i < strlen(string); i++) {
        if ( *(string + i) < 48 || *(string + i) > 57) {
            return False;
        }
    }
    return True;
}

void convert_to_words(const char* string) {
    if (checking_word_only_number(string) == False) {
        perror("convert_to_words just works witn string numbers\n");
        return;
    }

    static char* words[10] = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
        "Greater than 9"
    };

    int indx = atoi(string);
    if (indx > 0 && indx < 10) {
        printf("%s -> %s\n", string, words[indx - 1]);
    }
    else {
        printf("%s -> Greater than 9\n", string);
    }
    
}

void digital_frequency(const char* string) {
    int matrix[10][1];
    for (int i = 48; i < 58; ++i) {
        matrix[i][0] = 0;
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
    // char* s;
    // s = malloc(1024 * sizeof(char));
    // Reading whole line until get the '\n'
    // scanf("%[^\n]",s);
    digital_frequency("a11472o5t6");
    convert_to_words("2423");
    convert_to_words("3");
    convert_to_words("6");
    return 0;
}   