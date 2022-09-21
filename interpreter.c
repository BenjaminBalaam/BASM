#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void debug(int R1, int R2, int program_counter, int memory[]) {
    printf("\nR1:%d, R2:%d\n", R1, R2);

    for (int i = 0; i < 40; i++) {
        if (i == program_counter) {
            printf("%d. %d <--- PC HERE\n", i, memory[i]);
        } else {
            printf("%d. %d\n", i, memory[i]);
        }
    }
    char temp[10];
    printf("DEBUG");
    fgets(temp, 10, stdin);
}

void printint(int out) {
    printf("%d\n", out);
}

void printstr(char* out) {
    printf("%s\n", out);
}

void removeChar(char * str, char charToRemmove){
    int i, j;
    int len = strlen(str);
    for(i=0; i<len; i++)
    {
        if(str[i] == charToRemmove)
        {
            for(j=i; j<len; j++)
            {
                str[j] = str[j+1];
            }
            len--;
            i--;
        }
    }
    
}

int main( int argc, char *argv[] ) {

    if( argc > 3 ) {
        printf("Expected 1 or 2 arguments, got %d.\n", argc-1);
        return 1;
    }
    else if ( argc < 2 ) {
        printf("1 or 2 arguments expected.\n");
        return 1;
    }
    
    // 1. + Add R1 R2
    // 2. - Subtract R1 R2
    // 3. * Store R1
    // 4. ^ Load R1
    // 5. ~ Swap R1 R2
    // 6. / Branch
    // 7. $ Branch if R1 = 0
    // 8. > Input R1
    // 9. < Output R1
    // N/A. : The following as a number
    // Using . in place of a number means, use the number from this address

    FILE* f = fopen(argv[1], "r");

    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);

    int MAX = size + 1;

    if (MAX < 100000) {
        MAX = 100000;
    }

    char text[MAX];

    int i = 0;

    while (fgets(&text[i], MAX, f)) {
        i = strlen(text);
    }

    int memory[MAX];
    for (int i = 0; i < MAX; i++) {
        memory[i] = 0;
    }

    int encode_index = 0;

    for (int i = 0; i < strlen(text); i++) {

        char c = text[i];

        char s[2] = { c, '\0' };

        if (!strcmp(s, "+")) {
            memory[encode_index] = 100000;
        } else if (!strcmp(s, "-")) {
            memory[encode_index] = 200000;
        } else if (!strcmp(s, "*")) {
            int len_num = 0;
            bool address = false;
            while (true) {
                char character = text[i+1+len_num];
                if (strpbrk(&character, "0123456789")) {
                    len_num++;
                } else if (!strcmp(&character, ".")) {
                    address = true;
                    i++;
                } else {
                    break;
                }
            }
            char number_char[5] = "";
            strncpy(number_char, text+i+1, len_num);

            int number = atoi(number_char);

            if (address) {
                memory[encode_index] = 1300000 + number;
            } else {
                memory[encode_index] = 300000 + number;
            }
        } else if (!strcmp(s, "^")) {
            int len_num = 0;
            bool address = false;
            while (true) {
                char character = text[i+1+len_num];
                if (strpbrk(&character, "0123456789")) {
                    len_num++;
                } else if (!strcmp(&character, ".")) {
                    address = true;
                    i++;
                } else {
                    break;
                }
            }
            char number_char[5] = "";
            strncpy(number_char, text+i+1, len_num);

            int number = atoi(number_char);

            if (address) {
                memory[encode_index] = 1400000 + number;
            } else {
                memory[encode_index] = 400000 + number;
            }
        } else if (!strcmp(s, "~")) {
            memory[encode_index] = 500000;
        } else if (!strcmp(s, "/")) {
            int len_num = 0;
            bool address = false;
            while (true) {
                char character = text[i+1+len_num];
                if (strpbrk(&character, "0123456789")) {
                    len_num++;
                } else if (!strcmp(&character, ".")) {
                    address = true;
                    i++;
                } else {
                    break;
                }
            }
            char number_char[5] = "";
            strncpy(number_char, text+i+1, len_num);
            strcat(number_char, "\0");

            int number = atoi(number_char);

            if (address) {
                memory[encode_index] = 1600000 + number;
            } else {
                memory[encode_index] = 600000 + number;
            }
        } else if (!strcmp(s, "$")) {
            int len_num = 0;
            bool address = false;
            while (true) {
                char character = text[i+1+len_num];
                if (strpbrk(&character, "0123456789")) {
                    len_num++;
                } else if (!strcmp(&character, ".")) {
                    address = true;
                    i++;
                } else {
                    break;
                }
            }
            char number_char[5] = "";
            strncpy(number_char, text+i+1, len_num);

            int number = atoi(number_char);

            if (address) {
                memory[encode_index] = 1700000 + number;
            } else {
                memory[encode_index] = 700000 + number;
            }
        } else if (!strcmp(s, ">")) {
            memory[encode_index] = 800000;
        } else if (!strcmp(s, "<")) {
            memory[encode_index] = 900000;
        } else if (!strcmp(s, ":")) {
            int len_num = 0;
            while (true) {
                char character = text[i+1+len_num];
                if (strpbrk(&character, "0123456789")) {
                    len_num++;
                } else {
                    break;
                }
            }
            char number_char[5] = "";
            strncpy(number_char, text+i+1, len_num);

            int number = atoi(number_char);

            memory[encode_index] = number;
        } else {
            continue;
        }

        encode_index++;
    }

    int program_counter = 0;
    int R1 = 0;
    int R2 = 0;

    while (memory[program_counter] != 0) {
        if (argc == 3) {
            if (!strcmp(argv[2], "--debug-mode") | !strcmp(argv[2], "-d")) {
                debug(R1, R2, program_counter, memory);
            }
        }

        if (memory[program_counter] / 100000 == 1) {
            R1 = R1 + R2;
        } else if (memory[program_counter] / 100000 == 2) {
            R1 = R1 - R2;
            if (R1 < 0) {
                R1 = 0;
            }
        } else if ((memory[program_counter] % 1000000) / 100000 == 3) {
            int address = memory[program_counter] % 100000;
            if (memory[program_counter] / 1000000) {
                address = memory[address];
            }
            memory[address] = R1;
        } else if ((memory[program_counter] % 1000000) / 100000 == 4) {
            int address = memory[program_counter] % 100000;
            if (memory[program_counter] / 1000000) {
                address = memory[address];
            }
            int value = memory[address];
            R1 = value;
        } else if ((memory[program_counter] % 1000000) / 100000 == 5) {
            int temp = R1;
            R1 = R2;
            R2 = temp;
        } else if ((memory[program_counter] % 1000000) / 100000 == 6) {
            int address = memory[program_counter] % 100000;
            if (memory[program_counter] / 1000000) {
                address = memory[address];
            }
            program_counter = address - 1;
        } else if ((memory[program_counter] % 1000000) / 100000 == 7) {
            int address = memory[program_counter] % 100000;
            if (memory[program_counter] / 1000000) {
                address = memory[address];
            }
            if (R1 == 0) {
                program_counter = address - 1;
            }
        } else if ((memory[program_counter] % 1000000) / 100000 == 8) {
            char input = getchar();
            R1 = (int)input;
        } else if ((memory[program_counter] % 1000000) / 100000 == 9) {
            char output = (char) R1;
            printf("%c", output);
        }

        program_counter++;
    }

    return 0;
}