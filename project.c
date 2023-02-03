#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdbool.h>
#define max_file_len 100000
#define max_str_len 1000
#define max_path_len 1000

/*
to do list:
    create file     this is not goot
    insert          this works but not for " in string
    cat             I did it mama!
    remove          there
    copy            hehe haha
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
void cut();
void paste();
void find();
void replace();
// void grep();
// void undo();
// void closing_pairs();
// void text_comparator();
// void directory_tree();
// void arman();
    /*extra functions*/
void get_directory(char *dr);
void create_file();
void check_directory(char *dr);
bool _exists(char *address);
char *read_path();
char *dircut(char *dir);
char *filecut(char *dir);
char *read_find_string();     /*read entry string*/
int return_dir(char *dir);
void return_to_base(int back_dir);






int main() {
    char input[100];
    while (1) {
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) return 0;
        if (strcmp(input, "createfile") == 0) create_file();
        if (strcmp(input, "insertstr") == 0) insert();
        if (strcmp(input, "cat") == 0) cat();
        if (strcmp(input, "removestr") == 0) removestr();
        if (strcmp(input, "copystr") == 0) copy();
        if (strcmp(input, "cutstr") == 0) cut();
        if (strcmp(input, "pastestr") == 0) paste();
        if (strcmp(input, "find") == 0) find();
        if (strcmp(input, "replace") == 0) replace();
    }
    return 0;
}




char *dircut(char *dir) {               /*gets directory from address*/
    int len, last_slash;
    char *temp, *direction;
    temp = (char *) calloc(max_path_len, sizeof(char));
    direction = (char *) calloc(max_path_len, sizeof(char));
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

char *filecut(char *dir) {                  /*gets filename from address*/
    int len, last_slash;
    char *temp;
    temp = (char *) calloc(max_path_len, sizeof(char));
    len = strlen(dir);
    for (int i = 0; i < len; i++) {
        if (dir[i] == '/') last_slash = i;
    }
    for (int i = last_slash + 1, j = 0; i < len; i++, j++) {
        temp[j] = dir[i];
    }
    return temp;
}

char *read_path() {                 /*generally read*/
    int path_counter = 0;
    char *path;
    path = (char *) calloc(max_path_len, sizeof(char));
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

int return_dir(char *dir) {        /*to see how many .. chdir needed*/
    int slash_counter = 0;
    int len = strlen(dir);
    for (int i = 0; i < len; i++) {
        if (dir[i] == '/') slash_counter++;
    }
    return slash_counter;
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

void return_to_base(int back_dir) {
    for (int i = 0; i < back_dir; i++) {
        chdir("..");
    }
    return;
}

char *read_find_string() {
    int index = 0, flag = 0;
    char *string, c;
    string = (char *) calloc(10000, sizeof(char));
    c = getchar();
    c = getchar();
    if (c == '"') {
        while (true) {
            c = getchar();
            if (c == '"') {
                if (string[index - 1] == 92) {
                    index--;
                    string[index] = c;
                }
                else {
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
            if (c == '*') {
                if (string[index - 1] == 92) {
                    index--;
                    string[index] = c;
                }
            }
            string[index] = c;
            index++;
        }
    }
    else {
        while (true) {
            if (c == '"') {
                if (string[index - 1] == 92) {
                    index--;
                    string[index] = c;
                }
            }
            if (c == ' ') break;
            if (flag) break;
            if (c == '*') {
                if (string[index - 1] == 92) {
                    index--;
                    string[index] = c;
                }
            }
            string[index] = c;
            index++;
            c = getchar();
        }
    }
    return string;
}

void create_file() {
    char trash[100], *path, *dir, *file_name, *address;
    path = (char *) calloc(1000, sizeof(char));
    dir = (char *) calloc(1000, sizeof(char));
    file_name = (char *) calloc(1000, sizeof(char));
    address = (char *) calloc(1000, sizeof(char));
    scanf("%s", trash);
    path = read_path();
    dir = dircut(path);
    int back_dir = return_dir(dir);
    file_name = filecut(path);
    char *token = strtok(dir, "/");
    strcpy(address, token);
    strcat(address, "/");
    while (true) {
        token = strtok(NULL, "/");
        if (token == NULL) break;
        strcat(address, token);
        mkdir(address);
        strcat(address, "/");
    }
    chdir(address);
    FILE *file = fopen(file_name, "r");
    if (file != NULL) {
        printf("file already exists!\n");
        return;
    }
    fclose(file);
    file = fopen(file_name, "w");
    for (int i = 0; i < back_dir; i++) {
        chdir("..");
    }
    return;
}

void insert() {
    int slash_check = 0, slash_counter = 0, counter = 0, enter_counter = 0, char_num = 0, path_index = 0, space_reduc = 0, string_index = 0; /*counters*/
    int quoflag = 0, line, start, flag = 0, entry_len, flag2 = 0;
    char c;
    char *path, *dir, *file_name, current_dr[max_path_len], file_check[20], str[max_str_len], pos[20], string[max_str_len], root_check[4], string_temp[max_str_len];
    char *file_content = (char *) malloc(1000000 * sizeof(char));
    path = (char *) calloc(1000, sizeof(char));
    dir = (char *) calloc(1000, sizeof(char));
    file_name = (char *) calloc(1000, sizeof(char));
    scanf("%s", file_check);
    if (strcmp(file_check, "--file") != 0) {
        printf("spell '--file' right!\n");
        return;
    }
    path = read_path();
    printf("path is: %s\n", path);
    dir = dircut(path);
    int back_dir = return_dir(dir);
    file_name = filecut(path);
    printf("file name is :%s\n", file_name);
    // printf("dir is :%s\n", dir);
    int chdr = !chdir(dir);
    if (!chdr) {
        printf("write a correct address -_-\n");
        return;
    }
    scanf("%s", str);
    // if (strcmp(str, "--str") != 0) {
    //     printf("type '--str' pls\n");
    //     return;
    // }
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
    // printf("string is: %s\n", string);
    entry_len = strlen(string);
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
    // printf("the entry string is :%s\n", string);
    scanf("%s", pos);
    // if (strcmp(pos, "--pos") != 0) {
    //     printf("type '--pos' pls\n");
    //     return;
    // }
    getchar();
    scanf("%d", &line);
    c = getchar();
    if (c != ':') {
        printf("you forgot to type ':'\n");
        for (int i = 0; i < back_dir; i++) {
            chdir("..");
        }
        return;
    }
    scanf("%d", &start);
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("this file doesn't exist\n");
        for (int i = 0; i < back_dir; i++) {
            chdir("..");
        }
        return;
    }
    while (true) {                    /*inserting string to file*/
        if ((line == 1) && (flag2 == 0)) {            /*if pos line 1*/
            for (int i = 0; i < start; i++) {
                c = fgetc(file);
                if (c == '\n') {
                    printf("there are not enough characters in this line\n");
                    for (int i = 0; i < back_dir; i++) {
                        chdir("..");
                    }
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
                for (int i = 0; i < back_dir; i++) {
                    chdir("..");
                }
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
                    for (int i = 0; i < back_dir; i++) {
                    chdir("..");
                    }
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
    fclose(write_file);
    break_get_dr = 0;
    for (int i = 0; i < back_dir; i++) {
        chdir("..");
    }
    return;
}


void cat() {
    int quoflag = 0;       /*flag*/
    int dir_index = 0, file_name_len = 0, path_len;
    char c;
    char file_check[10], root_check[10], real_path[100], *file_name, *path, *dir;
    file_name = (char *) calloc(1000, sizeof(char));
    path = (char *) calloc(1000, sizeof(char));
    dir = (char *) calloc(1000, sizeof(char));
    scanf("%s", file_check);
    if (strcmp(file_check, "--file") != 0) {
        printf("type --file correct pls\n");
        return;
    }
    path = read_path();
    dir = dircut(path);
    file_name = filecut(path);
    int back_dir = return_dir(dir);
    chdir(dir);
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("this file doesn't exist\n");
        return;
    }
    while (true) {
        c = fgetc(file);
        if (c == EOF) {
            printf("\n");
            break;
        }
        printf("%c", c);
    }
    fclose(file);
    for (int i = 0; i < back_dir; i++) {
        chdir("..");
    }
    return;
}


void removestr() {
    int line, start, size, line_counter = 0, index_file = 0, line_char = 0, flag_line = 0;
    char c, way;
    char filecheck[20], root[10], pos[10], check_size[10];
    char *path, *dir, *file_name, *content;
    path = (char *) calloc(max_path_len, sizeof(char));
    dir = (char *) calloc(max_path_len, sizeof(char));
    file_name = (char *) calloc(100, sizeof(char));
    content = (char *) calloc(max_str_len, sizeof(char));
    scanf("%s", filecheck);
    if (strcmp(filecheck, "--file") != 0) {
        printf("printf --file !\n");
        return;
    }
    path = read_path();
    dir = dircut(path);
    int back_dir = return_dir(dir);
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
    for (int i = 0; i < back_dir; i++) {
        chdir("..");
    }
    return;
}

void copy() {
    char check_file[20], check_pos[10], check_size[10], *path, *dir, *file_name, c, way, *content, *cpy;
    int line, start, num;
    int flag_line = 0, enter_counter = 0, index_content = 0, index_cpy = 0, line_char = 0;          /*line number error*/
    content = (char *) calloc(100000, sizeof(char));
    cpy = (char *) calloc(10000, sizeof(char));
    path = (char *) calloc(1000, sizeof(char));
    dir = (char *) calloc(1000, sizeof(char));
    file_name = (char *) calloc(100, sizeof(char));
    scanf("%s", check_file);
    if (strcmp(check_file, "--file") != 0) {
        printf("type --file\n");
        return;
    }
    path = read_path();
    dir = dircut(path);
    int back_dir = return_dir(dir);
    file_name = filecut(path);
    scanf("%s", check_pos);
    if (strcmp(check_pos, "--pos") != 0) {
        printf("type --pos\n");
        return;
    }
    getchar();
    scanf("%d", &line);
    c = getchar();
    if (c != ':') {
        printf("put : between line and start\n");
        return;
    }
    scanf("%d", &start);
    scanf("%s", check_size);
    if (strcmp(check_size, "-size") != 0) {
        printf("type -size pls\n");
        return;
    }
    scanf(" %d", &num);
    scanf(" -%c", &way);
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
    while (true) {
        if (c == EOF) {
            if (!flag_line) {
                printf("line out of range\n");
                return;
            }
            break;
        }
        if (c == '\n') enter_counter++;
        content[index_content] = c;
        index_content++;
        if ((enter_counter == line - 1) && (flag_line == 0)) {
            if (way == 'f') {
                while (true) {
                    c = fgetc(file);
                    content[index_content] = c;
                    if (line_char + 1 == start) {
                        for (int j = 0; j < num; j++) {
                            c = fgetc(file);
                            cpy[index_cpy] = c;
                            index_cpy++;
                        }
                        break;
                    }
                    index_content++;
                    line_char++;
                }
            }
            if (way == 'b') {
                while (true) {
                    c = fgetc(file);
                    content[index_content] = c;
                    if (line_char == start) {
                        c = fgetc(file);
                        index_content++;
                        content[index_content] = c;
                        for (int j = 1; j <= num; j++) {
                            cpy[num - j] = content[index_content - j];
                            // printf("%c", cpy[num - j]);
                            index_cpy++;
                        }
                        printf("\n");
                        break;
                    }
                    index_content++;
                    line_char++;
                }
            }
            flag_line = 1;
        }
        c = fgetc(file);
    }
    fclose(file);
    printf("copied text is %s\n", cpy);
    for (int i = 0; i < back_dir; i++) {
        chdir("..");
    }
    file = fopen("./cpy.txt", "w");
    fprintf(file, "%s", cpy);
    fclose(file);
    return;
}

void cut() {
    char check_file[20], check_pos[20], check_size[20], way;
    char *path, *file_name, *dir, *cpy, *content, c;
    int line, start, num, flag_line = 0, line_counter = 0, index_file = 0, line_char = 0, index_cpy = 0, flag = 0;
    path = (char *) calloc(1000, sizeof(char));
    file_name = (char *) calloc(1000, sizeof(char));
    dir = (char *) calloc(1000, sizeof(char));
    cpy = (char *) calloc(10000, sizeof(char));
    content = (char *) calloc(10000, sizeof(char));
    scanf("%s", check_file);
    if (strcmp(check_file, "--file") != 0) {
        printf("type --file\n");
        return;
    }
    path = read_path();
    dir = dircut(path);
    int back_dir = return_dir(dir);
    file_name = filecut(path);
    scanf("%s", check_pos);
    if (strcmp(check_pos, "--pos") != 0) {
        printf("type --pos\n");
        return;
    }
    getchar();
    scanf("%d", &line);
    c = getchar();
    if (c != ':') {
        printf("put : between line and start\n");
        return;
    }
    scanf("%d", &start);
    scanf("%s", check_size);
    if (strcmp(check_size, "-size") != 0) {
        printf("type -size pls\n");
        return;
    }
    scanf(" %d", &num);
    scanf(" -%c", &way);
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
                        for (int j = 0; j < num; j++) {
                            c = fgetc(file);
                            if (!flag) {
                                content[index_file] = c;
                                index_file++;
                                flag = 1;
                            }
                            cpy[index_cpy] = c;
                            index_cpy++;
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
                        for (int j = 0; j < num; j++) {
                            cpy[j] = content[index_file - num + j + 1];
                        }
                        for (int j = 0; j < num - 1; j++) {
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
    for (int i = 0; i < back_dir; i++) {
        chdir("..");
    }
    file = fopen("./cpy.txt", "w");
    fprintf(file, "%s", cpy);
    fclose(file);
    return;
}

void paste() {
    int flag_line = 0;               /*flag*/
    int index_cpy = 0, index_file = 0, line_counter = 0, line_char = 0;                  /*index*/
    int line, start;
    char *path, *file_name, *dir, *cpy, *content, c;
    char check_file[20], check_pos[20];
    path = (char *) calloc(1000, sizeof(char));
    file_name = (char *) calloc(1000, sizeof(char));
    dir = (char *) calloc(1000, sizeof(char));
    cpy = (char *) calloc(10000, sizeof(char));
    content = (char *) calloc(10000, sizeof(char));
    scanf("%s", check_file);
    if (strcmp(check_file, "--file") != 0) {
        printf("type --file\n");
        return;
    }
    path = read_path();
    dir = dircut(path);
    int back_dir = return_dir(dir);
    file_name = filecut(path);
    scanf("%s", check_pos);
    if (strcmp(check_pos, "--pos") != 0) {
        printf("type --pos\n");
        return;
    }
    scanf(" %d", &line);
    c = getchar();
    if (c != ':') {
        printf("type :\n");
        return;
    }
    scanf("%d", &start);
    FILE *file = fopen("./cpy.txt", "r");
    while (true) {
        c = fgetc(file);
        if (c == EOF) break;
        cpy[index_cpy] = c;
        index_cpy++;
    }
    fclose(file);
    int len = strlen(cpy);
    int chdr = chdir(dir);
    if (chdr) {
        printf("this directory doesn't exsit\n");
        return;
    }
    file = fopen(file_name, "r");
    if (file == NULL) {
        printf("this file doesn't exist!\n");
        return;
    }
    while (true) {
        c = fgetc(file);
        if (c == EOF) {
            if (flag_line == 0) {
                printf("line out of range!\n");
                fclose(file);
                return;
            }
            fclose(file);
            break;
        }
        if (c == '\n') {
            line_counter++;
        }
        content[index_file] = c;
        index_file++;
        if ((line_counter == line - 1) && (flag_line == 0)) {
            while (true) {
                c = fgetc(file);
                content[index_file] = c;
                if (line_char == start) {
                    for (int i = 0; i < len; i++) {
                        index_file++;
                        content[index_file] = cpy[i];
                    }
                    index_file++;
                    break;
                }
                index_file++;
                line_char++;
            }
            flag_line = 1;
        }
    }
    file = fopen(file_name, "w");
    fprintf(file, "%s", content);
    fclose(file);
    return;
}

void find() {
    char trash[30], *path, *dir, *file_name, *str, *content, c, *style;
    int index_content = 0, len_str, flag = 0, i, j, index = -1, words = 1, count = 0, times = 0;
    scanf("%s", trash);
    style = (char *) calloc(100, sizeof(char));
    path = (char *) calloc(1000, sizeof(char));
    dir = (char *) calloc(1000, sizeof(char));
    file_name = (char *) calloc(1000, sizeof(char));
    str = (char *) calloc(max_str_len, sizeof(char));
    content = (char *) calloc(max_file_len, sizeof(char));
    str = read_find_string();
    scanf("%s", trash);
    path = read_path();
    dir = dircut(path);
    int back_dir = return_dir(dir);
    file_name = filecut(path);
    int chdr = chdir(dir);
    if (chdr) {
        printf("this directory doesn't exsit\n");
        return;
    }
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("this file doesn't exist\n");
        return_to_base(back_dir);
        return;
    }
    scanf("%[^\n]%*c", style);
    while (true) {
        c = fgetc(file);
        if (c == EOF) {
            break;
        }
        content[index_content] = c;
        index_content++;
    }
    fclose(file);
    len_str = strlen(str);
    if (strcmp(style, " -count") == 0) {
        for (i = 0; i <= index_content - len_str; i++) {
            for (j = 0; j < len_str; j++) {
                if (*(content + i + j) != *(str + j)) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                count++;
            }
            flag = 0;
        }
        printf("%d\n", count);
    }
    else if (strcmp(style, " -byword") == 0) {
        for (i = 0; i < index_content - len_str; i++) {
            if ((*(content + i) == ' ') && (*(content + i - 1) != ' ')) words++;
            for (j = 0; j < len_str; j++) {
                if (*(content + i + j) != *(str + j)) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                break;
            }
            flag = 0;
        }
        if (flag == 0) printf("%d\n", words);
        else printf("-1\n");
    }
    else if (strcmp(style, " -all") == 0) {
        for (i = 0; i <= index_content - len_str; i++) {
            for (j = 0; j < len_str; j++) {
                if (*(content + i + j) != *(str + j)) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf("%d ", i);
            }
            flag = 0;
        }
        printf("\n");
    }
    else if (strncmp(style, " -at", 4) == 0) {
        style += 4;
        int size = atoi(style);
        for (i = 0; i < index_content - len_str; i++) {
            if ((*(content + i) == ' ') && (*(content + i - 1) != ' ')) words++;
            for (j = 0; j < len_str; j++) {
                if (*(content + i + j) != *(str + j)) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                times++;
                if (times == size) {
                    printf("%d\n", i);
                    break;
                }
            }
            flag = 0;
        }
    }
    else {
        for (i = 0; i <= index_content - len_str; i++) {
            for (j = 0; j < len_str; j++) {
                if (*(content + i + j) != *(str + j)) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                printf("%d\n", i);
                break;
            }
            flag = 0;
        }
    }
    for (i = 0; i < back_dir; i++) {
        chdir("..");
    }
    return;
}

void replace() {
    char trash[20], *str1, *str2, *path, *dir, *file_name, *style, *content;
    int content_index = 0, len_str1, len_str2, flag = 0, i, j;
    scanf("%s", trash);
    str1 = (char *) calloc(max_str_len, sizeof(char));
    str2 = (char *) calloc(max_str_len, sizeof(char));
    dir = (char *) calloc(max_path_len, sizeof(char));
    path = (char *) calloc(max_path_len, sizeof(char));
    file_name = (char *) calloc(max_path_len, sizeof(char));
    style = (char *) calloc(30, sizeof(char));
    str1 = read_find_string();
    scanf("%s", trash);
    str2 = read_find_string();
    scanf("%s", trash);
    path = read_path();
    scanf("%[^\n]%*c", style);
    dir = dircut(path);
    int back_dir = return_dir(dir);
    file_name = filecut(path);
    int chdr = chdir(dir);
    if (chdr) {
        printf("this file doesn't exist\n");
        return;
    }
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("this file doesn't exist\n");
        return_to_base(back_dir);
        return;
    }
    while (true) {
        c = fgetc(file);
        if (c == EOF) break;
        content[content_index] = c;
        content_index++;
    }
    fclose(file);
    len_str1 = strlen(str1);
    len_str2 = strlen(str2);
    //all feature
    if (strcmp(style, " -all") == 0) {
        for (i = 0; *(content + i) != '\0'; i++) {
            for (j = 0; j < len_str1; j++) {
                if (*(content + i + j) != *(str1 + j)) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                if (len_str1 > len_str2) {
                    for (j = i; *(content + j) != '\0'; j++) {
                        *(content + j) = *(content + j + len_str1 - len_str2);
                    }
                }
                for (j = 0; j < len_str2; j++) {
                    *(content + i + j) = *(str2 + j);
                }
            }
            flag = 0;
        }
    }
    for (int i = 0; i < back_dir; i++) {
        chdir("..");
    }
    return;
}