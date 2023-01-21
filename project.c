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

int break_get_dr = 0;
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
void create_file();
void check_directory(char *dr);
bool _exists(char *address);

int main() {
    char c;
    int counter = 0, string_len;
    char input[20], address[200], dr[100], dr_temp[100], file_name[100];
    while (1) {
        // get_directory(address);
        // printf("%s", address);
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) return 0;
        if (strcmp(input, "createfile") == 0) create_file();
    }
    return 0;
}

void check_directory(char *dr) {
    char main_dr[] = {"./"};
    strcat(main_dr, dr);
    if (chdir(main_dr)) {
        mkdir(main_dr);
    }
    printf("i'm in check directory!\n");
    return;
}

void get_directory(char *dr) {
    int counter = 0;
    while (true) {
        dr[counter] = getchar();
        if ((dr[counter] == '/') || (dr[counter] == '\n') || (dr[counter] == '"')) {
            if (dr[counter] == '\n' || dr[counter] == '"') break_get_dr++;
            dr[counter] = '\0';
            break;
        }
        counter++;
    }
    return;
}

void create_file() {
    int flag = 0;
    char file[20], dr[100], dr_temp[100], pfile_name[100], file_name[100], path[100];
    char c;
    int len, quoflag = 0, len_dr;
    scanf("%s", file);
    if (strcmp(file, "--file") != 0) {
        printf("spell '--file' right dammit!\n");
        return;
    }
    scanf("%c", &c);
    scanf("%c", &c);
    if (c == '"') {
        scanf("%c", &c);
        quoflag = 1;
    }
    get_directory(dr_temp);
    if (strcmp(dr_temp, "root") != 0) {
        printf("you should start from root\n");
        return;
    }
    while (true) {
        if (flag == 1) printf("hey second time\n");
        get_directory(dr_temp);
        len = strlen(dr_temp);
        printf("%s1\n", dr_temp);
        len_dr = strlen(dr);
        dr[len_dr] = '/';
        if (break_get_dr) {
            break;
        }
        strcat(dr, dr_temp);
        char main_dr[] = {"."};
        strcat(main_dr, dr);
        printf("main dr is :%s\n", main_dr);
        if (chdir(main_dr)) {
            mkdir(main_dr);
        }
        flag = 1;
    }
    break_get_dr = 0;
    printf("%s\n", dr);
    printf("%s\n", dr_temp);
    chdir(dr);
    FILE *open_file;
    open_file = fopen(dr_temp, "r");
    if (open_file != NULL) {
        printf("this file already exists!\n");
        return;
    }
    else printf("this file doesn't exist\n");
    open_file = fopen(dr_temp, "w");
    return;
}