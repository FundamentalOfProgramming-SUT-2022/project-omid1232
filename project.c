#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>

/*
to do list:
    create file     this is not goot
    insert          this almost works
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
    int slash_check = 0, slash_counter = 0, counter = 0, enter_counter = 0, char_num = 0, path_index = 0, space_reduc = 0, string_index = 0; /*counters*/
    int quoflag = 0, line, start, flag = 0, path_len, entry_len, flag2 = 0;
    char c;
    char path[100], current_dr[100], file_check[20], file_name[100], str[20], pos[20], string[100], root_check[4], string_temp[100];
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
        while (c != '"') {
            path[path_index] = c;
            path_index++;
            scanf("%c", &c);
        }
        path_len = strlen(path);
        for (int i = 0; i < path_len; i++) {
            if (path[i] == '/') {
                while ((path[i + 1] == ' ') || (path[i - 1] == ' ')) {
                    if (path[i + 1] == ' ') {
                        for (int j = i + 1; j < path_len - 1; j++) {
                            path[j] = path[j + 1];
                        }
                    }
                    if (path[i - 1] == ' ') {
                        for (int j = i - 1; j < path_len - 1; j++) {
                            path[j] = path[j - 1];
                        }
                        i--;
                    }
                    space_reduc++;
                }
            }
        }
        for (int j = path_len - space_reduc; j < path_len; j++) {
            path[j] = '\0';
        }
        for (int j = 0; j < path_len - 1; j++) {
            path[j] = path[j + 1];
        }
    }
    else scanf("%s", path);
    printf("path is: %s\n", path);
    for (int i = 0; i < strlen(path); i++) {
        if (path[i] == '/') slash_counter++;
    }
    for (int i = 0; i < strlen(path); i++) {
        if (path[i] == '/') slash_check++;
        if (slash_check == slash_counter) {
            for (int j = i + 1; j < strlen(path); j++) {
                file_name[j - i - 1] = path[j];
                file_name[strlen(path) - i - 1] = '\0';
            }
            for (int j = i + 1; j < strlen(path); j++) {
                path[j] = '\0';
            }
            break;
        }
    }
    // printf("path is: %s\n", path);
    // for (int i = 0; i < 4; i++) {
    //     root_check[i] = path[i];
    // }
    // printf("%d\n", strlen(root_check));
    // printf("root check: %s\n", root_check);
    // if (strcmp(root_check, "root") != 0) {             this was root check
    //     printf("you should start from root\n");
    //     return;
    // }
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
    getchar();
    scanf("%c", &c);
    if (c == '"') {                          /*scanning string*/
        scanf("%c", &c);
        while (c != '"') {
            string[string_index] = c;
            string_index++;
            scanf("%c", &c);
        }
    }
    else {
        scanf("%s", string);
        entry_len = strlen(string);
        for (int i = 0; i < entry_len; i++) {
            string_temp[i] = string[i];
        }
        for (int i = 0; i < entry_len; i++) {
            string[i + 1] = string_temp[i];
        }
        string[0] = c;
    }
    printf("string is: %s\n", string);
    entry_len = strlen(string);
    // for (int i = 0; i < entry_len; i++) {
    //     if (string[i] == 92) back
    // }
    for (int i = 0; i < entry_len - 1; i++) {                /*checking \n and \\n */
        if (string[i] == 92) {
            if ((string[i + 1] == 'n') && (string[i - 1] != 92)) {
                string[i] = 10;
                for (int j = i + 1; j < entry_len - 1; j++) {
                    string[j] = string[j + 1];
                }
            }
            if ((string[i + 1] == 'n') && (string[i - 1] == 92)) {
                // printf("%c\n", string[i]);
                for (int j = i; j < entry_len - 1; j++) {
                    string[j] = string[j + 1];
                }
                string[entry_len - 1] = '\0';
            }
        }
    }
    printf("the entry string is :%s\n", string);
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
        return;
    }
    scanf("%d", &start);
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("this file doesn't exist\n");
        return;
    }
    while (true) {                    /*inserting string to file*/
        if ((line == 1) && (flag2 == 0)) {            /*if pos line 1*/
            for (int i = 0; i < start; i++) {
                c = fgetc(file);
                if (c == '\n') {
                    printf("there are not enough characters in this line\n");
                    return;
                }
                file_content[char_num] = c;
                char_num++;
            }
            for (int i = 0; i < strlen(string); i++) {
                file_content[char_num] = string[i];
                char_num++;
            }
            flag2 = 1;
        }
            c = fgetc(file);
        if (c == '\n') enter_counter++;
        if (c == EOF) {
            if (enter_counter < line - 1) {
                printf("there are not enough lines\n");
                return;
            }
            break;
        }
        file_content[char_num] = c;
        char_num++;
        if ((enter_counter == line - 1) && (flag == 0) && (line != 1)) {
            for (int i = 0; i < start; i++) {
                c = fgetc(file);
                if (c == '\n') {
                    printf("there are not enough characters in this line\n");
                    return;
                }
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