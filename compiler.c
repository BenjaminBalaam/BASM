#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void printint(int out) {
    printf("%d\n", out);
}

void printstr(char* out) {
    printf("%s\n", out);
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

    FILE* f = fopen(argv[1], "r");

    fseek(f, 0, SEEK_END);
    int size = ftell(f);
    fseek(f, 0, SEEK_SET);

    int MAX = size + 1;

    if (MAX < 100000) {
        MAX = 100000;
    }

    char buffer[MAX];

    char* text = fgets(buffer, MAX, f);

    fclose(f);

    char c_code[10000];

    strcat(c_code, "#include <stdio.h>\n\
\n\
int main() {\n\
    int program_counter = 0;\n\
    int R1 = 0;\n\
    int R2 = 0;\n\
\n\
    int MAX = ");

    char max_str[10];
    sprintf(max_str, "%d", MAX);
    strcat(c_code, max_str);

    strcat(c_code, ";\n\
\n\
    int program[] = { ");

    int encode_index = 0;

    for (int i = 0; i < strlen(text); i++) {
        char c = text[i];

        char s[2] = { c, '\0' };

        if (!strcmp(s, "+")) {
            strcat(c_code, "100000, ");
        } else if (!strcmp(s, "-")) {
            strcat(c_code, "200000, ");
        } else if (!strcmp(s, "*")) {
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

            strcat(c_code, "3");
            if (strlen(number_char) < 5) {
                for (int j = 0; j < 5 - strlen(number_char); j++) {
                    strcat(c_code, "0");
                }
            }
            strcat(c_code, number_char);
            strcat(c_code, ", ");
        } else if (!strcmp(s, "^")) {
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

            strcat(c_code, "4");
            if (strlen(number_char) < 5) {
                for (int j = 0; j < 5 - strlen(number_char); j++) {
                    strcat(c_code, "0");
                }
            }
            strcat(c_code, number_char);
            strcat(c_code, ", ");
        } else if (!strcmp(s, "~")) {
            strcat(c_code, "500000, ");
        } else if (!strcmp(s, "/")) {
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

            strcat(c_code, "6");
            if (strlen(number_char) < 5) {
                for (int j = 0; j < 5 - strlen(number_char); j++) {
                    strcat(c_code, "0");
                }
            }
            strcat(c_code, number_char);
            strcat(c_code, ", ");
        } else if (!strcmp(s, "$")) {
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

            strcat(c_code, "7");
            if (strlen(number_char) < 5) {
                for (int j = 0; j < 5 - strlen(number_char); j++) {
                    strcat(c_code, "0");
                }
            }
            strcat(c_code, number_char);
            strcat(c_code, ", ");
        } else if (!strcmp(s, ">")) {
            strcat(c_code, "800000, ");
        } else if (!strcmp(s, "<")) {
            strcat(c_code, "900000, ");
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

            strcat(c_code, number_char);
            strcat(c_code, ", ");
        } else {
            continue;
        }

        encode_index++;
    }

    strcat(c_code, "};\n\
\n\
    int memory[MAX];\n\
\n\
    for (int i = 0; i < MAX; i++) {\n\
        if (i < sizeof(program)) {\n\
            memory[i] = program[i];\n\
        } else {\n\
            memory[i] = 0;\n\
        }\n\
    }\n\
\n\
    while (memory[program_counter] != 0) {\n\
        if (memory[program_counter] / 100000 == 1) {\n\
            R1 = R1 + R2;\n\
        } else if (memory[program_counter] / 100000 == 2) {\n\
            R1 = R1 - R2;\n\
            if (R1 < 0) {\n\
                R1 = 0;\n\
            }\n\
        } else if (memory[program_counter] / 100000 == 3) {\n\
            int address = memory[program_counter] % 100000;\n\
            memory[address] = R1;\n\
        } else if (memory[program_counter] / 100000 == 4) {\n\
            int address = memory[program_counter] % 100000;\n\
            int value = memory[address];\n\
            R1 = value;\n\
        } else if (memory[program_counter] / 100000 == 5) {\n\
            int temp = R1;\n\
            R1 = R2;\n\
            R2 = temp;\n\
        } else if (memory[program_counter] / 100000 == 6) {\n\
            int address = memory[program_counter] % 100000;\n\
            program_counter = address - 1;\n\
        } else if (memory[program_counter] / 100000 == 7) {\n\
            int address = memory[program_counter] % 100000;\n\
            if (R1 == 0) {\n\
                program_counter = address - 1;\n\
            }\n\
        } else if (memory[program_counter] / 100000 == 8) {\n\
            char input[256];\n\
            fgets(input, 256, stdin);\n\
            R1 = (int)input[0];\n\
        } else if (memory[program_counter] / 100000 == 9) {\n\
            char output = (char) R1;\n\
            printf(\"%c\", output);\n\
        }\n\
\n\
        program_counter++;\n\
    }\n\
\n\
    return 0;\n\
}");

    char *output_file = "a.out";
    if (argc == 3) {
        output_file = argv[2];
    }

    // printf("%s", c_code);

    FILE* temp_f = fopen("temp.c", "w");
    fprintf(temp_f, "%s", c_code);
    fclose(temp_f);
    char temp_1[100];
    sprintf(temp_1, "gcc temp.c -o %s", output_file);
    system(temp_1);
    system("rm temp.c");

    return 0;
}