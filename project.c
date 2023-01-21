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
void insert();
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
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) return 0;
        if (strcmp(input, "createfile") == 0) create_file();
        if( strcmp(input, "insertstr") == 0) insert();
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

void insert() {
    int slash_check = 0, slash_counter = 0, counter = 0, quoflag = 0, line, start, enter_counter = 0, char_num = 0, flag = 0, path_len;
    char c;
    char path[100], current_dr[100], file_check[20], file_name[100], str[20], pos[20], string[100], root_check[10];
    char *file_content = (char *) malloc(1000000 * sizeof(char));
    scanf("%s", file_check);
    if (strcmp(file_check, "--file") != 0) {
        printf("spell '--file' right!\n");
        return;
    }
    scanf(" %c", &c);
    if (c == '"') {
        quoflag = 1;
        scanf("%c", &c);
    }
    scanf("%s", path);
    for (int i = 0; i < strlen(path); i++) {
        if (path[i] == '/') slash_counter++;
    }
    for (int i = 0; i < strlen(path); i++) {
        if (path[i] == '/') slash_check++;
        if (slash_check == slash_counter) {
            for (int j = i + 1; j < strlen(path); j++) {
                file_name[j - i - 1] = path[j];
            }
            for (int j = i + 1; j < strlen(path); j++) {
                path[j] = '\0';
            }
            break;
        }
    }
    for (int i = 0; i < 4; i++) {
        root_check[i] = path[i];
    }
    if (strcmp(root_check, "root") != 0) {
        printf("you should start from root\n");
        return;
    }
    path_len = strlen(path);
    path[0] = '.';
    for (int i = 0; i < path_len - 4; i++) {
        path[i + 1] = path[i + 4];
    }
    for (int i = path_len - 4; i < path_len; i++) {
        path[i] = '\0';
    }
    printf("file name is :%s\n", file_name);
    printf("path is :%s\n", path);
    int chdr = !chdir(path);
    if (!chdr) {
        printf("write a correct address -_-\n");
        return;
    }
    scanf("%s", str);
    if (strcmp(str, "--str") != 0) {
        printf("type '--str' pls\n");
        return;
    }
    scanf("%s", string);
    scanf("%s", pos);
    if (strcmp(pos, "--pos") != 0) {
        printf("type '--pos' pls\n");
        return;
    }
    getchar();
    scanf("%d", &line);
    c = getchar();
    if (c != ':') {
        printf("you forgot to type ':'\n");
    }
    scanf("%d", &start);
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("this file doesn' exist\n");
        return;
    }
    while (true) {
        c = fgetc(file);
        if (c == '\n') enter_counter++;
        if (c == EOF) break;
        file_content[char_num] = c;
        char_num++;
        if ((enter_counter == line - 1) && (flag == 0)) {
            for (int i = 0; i < start; i++) {
                c = fgetc(file);
                file_content[char_num] = c;
                char_num++;
            }
            for (int i = 0; i < strlen(string); i++) {
                file_content[char_num] = string[i];
                char_num++;
            }
            flag = 1;
        }
    }
    fclose(file);
    FILE *write_file = fopen(file_name, "w");
    fprintf(write_file, "%s", file_content);
    break_get_dr = 0;
    chdir("..");
    return;
}