#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#define max_str_len 100000
#define max_path_len 1000

/*
to do list:
    create file     this is not goot
    insert          this works but not for " in string
    cat             I did it mama!
    remove          there
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
void cat();
void removestr();
void copy();
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
char *dircut(char *dir);
char *filecut(char *dir);






int main() {
    char input[100];
    while (1) {
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) return 0;
        if (strcmp(input, "createfile") == 0) create_file();
        if (strcmp(input, "insertstr") == 0) insert();
        if (strcmp(input, "cat") == 0) cat();
        if (strcmp(input, "removestr") == 0) removestr();
    }
    return 0;
}




char *dircut(char *dir) {
    int len, last_slash;
    char *temp, *direction;
    temp = (char *) malloc(max_path_len * sizeof(char));
    direction = (char *) malloc(max_path_len * sizeof(char));
    strcpy(temp, dir);
    len = strlen(dir);
    for (int i = 0; i < len; i++) {
        if (dir[i] == '/') last_slash = i;
    }
    for (int i = last_slash; i < len; i++) {
        temp[i] = '\0';
    }
    direction[0] = '.';
    direction[1] = '/';
    len = strlen(temp);
    for (int i = 0; i < len; i++) {
        direction[i + 2] = temp[i];
    }
    direction[len + 2] = '\0';
    return direction;
}

char *filecut(char *dir) {
    int len, last_slash;
    char *temp;
    temp = (char *) malloc(max_path_len * sizeof(char));
    len = strlen(dir);
    for (int i = 0; i < len; i++) {
        if (dir[i] == '/') last_slash = i;
    }
    for (int i = last_slash + 1, j = 0; i < len; i++, j++) {
        temp[j] = dir[i];
    }
    return temp;
}

char *read_path() {
    int path_counter = 0, temp_counter = 0;
    char *path;
    path = (char *) malloc(max_path_len * sizeof(char));
    char temp[max_path_len];
    char c;
    scanf(" %c", &c);
    if (c == '"') {
        scanf("%c", &c);
        scanf("%c", &c);
        path[path_counter] = c;
        while (path[path_counter] != '"') {
            path_counter++;
            scanf("%c", path + path_counter);
        }
        path[path_counter] = '\0';
        path[path_counter + 1] = '\0';
    }
    else {
        scanf("%s", path);
    }
    return path;
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
    char file[max_str_len], dr[max_path_len], dr_temp[max_path_len], pfile_name[100], file_name[100], path[max_path_len];
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
    char path[max_str_len], current_dr[max_path_len], file_check[20], file_name[100], str[max_str_len], pos[20], string[max_str_len], root_check[4], string_temp[max_str_len];
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


void cat() {
    int quoflag = 0;       /*flag*/
    int dir_index = 0, file_name_len = 0, path_len;
    char c;
    char file_check[10], root_check[10], dir[100], real_path[100], file_name[100];
    scanf("%s", file_check);
    if (strcmp(file_check, "--file") != 0) {
        printf("type --file correct pls\n");
        return;
    }
    getchar();
    scanf("%c", &c);
    if (c == '"') {
        quoflag = 1;
        scanf("%c", &c);
        scanf("%c", &c);
        while (c != '"') {
            dir[dir_index] = c;
            dir_index++;
            scanf("%c", &c);
        }
    }
    else scanf("%s", dir);
    printf("dir is %s\n", dir);
    if (quoflag) {
        dir[dir_index] = '\0';
        dir[dir_index + 1] = '\0';
        dir[dir_index + 2] = '\0';
    }
    printf("dir is %s\n", dir);
    for (int i = 0; i < 4; i++) {
        root_check[i] = dir[i];
    }
    printf("root check:%s\n", root_check);
    // if (strcmp(root_check, "root") != 0) {
    //     printf("%d\n", strcmp(root_check, "root"));
    //     printf("%sroot\n", root_check);
    //     printf("start the directory from root!\n");
    //     return;
    // }
    real_path[0] = '.';
    for (int i = 0; i < strlen(dir) - 4; i++) {
        real_path[i + 1] = dir[i + 4];
    }
    path_len = strlen(real_path) - 1;
    for (int i = path_len, j = 0; real_path[i] != '/'; i--, j++) {
        file_name_len++;
        file_name[j] = real_path[i];
        real_path[i] = '\0';
    }
    strrev(file_name);
    file_name[file_name_len] = '\0';
    printf("file name is: %s\n", file_name);
    printf("real path is: %s\n", real_path);
    real_path[strlen(real_path) - 1] = '\0';
    chdir(real_path);
    FILE *file = fopen(file_name, "r");
    while (true) {
        c = fgetc(file);
        if (c == EOF) {
            // fclose(file_name);
            printf("\n");
            return;
        }
        printf("%c", c);
    }
    fclose(file);
    printf("\n");
    printf("real path is: %s\n", real_path);
    return;
}


void removestr() {
    int line, start, size, line_counter = 0, index_file = 0, line_char = 0, flag_line = 0;
    char c, way;
    char filecheck[20], root[10], pos[10], check_size[10];
    char *path, *dir, *file_name, *content;
    path = (char *) malloc(max_path_len * sizeof(char));
    dir = (char *) malloc(max_path_len * sizeof(char));
    file_name = (char *) malloc(100 * sizeof(char));
    content = (char *) malloc(max_str_len * sizeof(char));
    scanf("%s", filecheck);
    if (strcmp(filecheck, "--file") != 0) {
        printf("printf --file !\n");
        return;
    }
    path = read_path();
    dir = dircut(path);
    printf("dir is: %s\n", dir);
    file_name = filecut(path);
    printf("file name is: %s\n", file_name);
    for (int i = 0; i < 4; i++) {
        root[i] = path[i];
    }
    if (strcmp(root, "root") != 0) {
        printf("you should start from root!\n");
        return;
    }
    int chdr = chdir(dir);
    if (chdr) {
        printf("this directory doesn't exsit\n");
        return;
    }
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("this file doesn't exist!\n");
        return;
    }
    fclose(file);
    scanf("%s", pos);
    if (strcmp(pos, "-pos") != 0) {
        printf("type -pos correct\n");
        return;
    }
    scanf(" %d", &line);
    scanf("%c", &c);
    if (c != ':') {
        printf("type :\n");
        return;
    }
    scanf("%d", &start);
    scanf("%s", check_size);
    if (strcmp(check_size, "-size") != 0) {
        printf("type -size here\n");
        return;
    }
    scanf("%d", &size);
    getchar();
    getchar();
    way = getchar();
    file = fopen(file_name, "r");
    while (true) {
        c = fgetc(file);
        if (c == EOF) {
            if (flag_line == 0) {
                printf("line out of range!\n");
                return;
            }
            break;
        }
        if (c == '\n') {
            line_counter++;
        }
        content[index_file] = c;
        index_file++;
        if ((line_counter == line - 1) && (flag_line == 0)) {
            if (way == 'f') {
                while (true) {
                    c = fgetc(file);
                    content[index_file] = c;
                    if (line_char + 1 == start) {
                        for (int j = 0; j < size - 1; j++) {
                            fgetc(file);
                        }
                        break;
                    }
                    index_file++;
                    line_char++;
                }
            }
            if (way == 'b') {
                while (true) {
                    c = fgetc(file);
                    content[index_file] = c;
                    if (line_char == start) {
                        // index_file--;
                        // index_file--;
                        for (int j = 0; j < size; j++) {
                            content[index_file] = '\0';
                            index_file--;
                        }
                        break;
                    }
                    index_file++;
                    line_char++;
                }
            }
            flag_line = 1;
        }
    }
    fclose(file);
    file = fopen(file_name, "w");
    fprintf(file, "%s", content);
    fclose(file);
    printf("%s\n", content);
    return;
}

void copy() {}