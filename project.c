#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

/*
to do list:
    create file
    insert
    cat
    remove
    copy
    cut
    paste
    find
    replace
    grep
    undo
    closing pairs
    text comparator
    directory tree
    arman
    now what \_o_/
*/

// void insert();
// void cat();
// void remove();
// void copy();
// void cut();
// void paste();
// void find();
// void replace();
// void grep();
// void undo();
// void closing_pairs();
// void text_comparator();
// void directory_tree();
// void arman();
void get_directory(char *dr);
void create_file(char *address, char *name);
void check_directory(char *dr);
bool _exists(char *address);

int main() {
    char c;
    int counter = 0, string_len;
    char input[20], file[10], address[200], dr[100], dr_temp[100], file_name[100];
    while (1) {
        scanf("%s", input);
        if (strcmp(input, "createfile") == 0) {
            scanf("%s", file);
            getchar();
            scanf("%c", &c);
            if (c == '"') {
                scanf("%c", &c);
            }
            get_directory(dr);
            // printf("%s\n", dr);
            if (strcmp(dr, "root") != 0) {
                printf("don't give wrong address you fool!");
                break;
            }
            while (true) {
                string_len = strlen(dr_temp);
                for (int i = 0; i < string_len; i++) {
                    if (dr_temp[i] == '.') {
                        for (int i = 0; i < string_len; i++) {
                            file_name[i] = dr_temp[i];
                        }
                        break;
                    }
                }
                get_directory(dr_temp);
            }
            while (dr_temp)
            create_file(dr, "sdf");
        }
    }
}

bool _exists(char* address) {
  struct stat st = { 0 };
  return stat(address, &st) != -1;
}

// void create_folder(char *address, char *name) {
//     mkdir()
// }

void check_directory(char *dr) {
    char main_dr[] = {"./"};
    strcat(main_dr, dr);
    if (!chdir(main_dr)) {
        mkdir(main_dr);
    }
    return;
}

void get_directory(char *dr) {
    char c;
    int counter = 0;
    while (true) {
        scanf("%c", &c);
        if ((c == '/') || (c == '\n')) break;
        dr[counter] = c;
        counter++;
    }
    return;
}
void create_file(char *address, char *name) {
    char main_dr[] = {"./"};
    strcat(main_dr, address);
    chdir(main_dr);
    FILE *file;
    file = fopen(name, "r");
    if (file != NULL) {
        printf("this file already exists!");
        return;
    }
    file = fopen(name, "w");
}