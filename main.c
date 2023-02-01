#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h> 
#include <sys/types.h>
#include <direct.h>
#include <windows.h>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


#define MAX_CONTENT 2048
#define MAX_LINE 2048
#define MAX_ADD 1024

FILE *filepointer;
char command[MAX_ADD];
char command_extension[MAX_ADD];
char address[MAX_ADD];

void cat();
void createfile();
void insertstr();
void removestr();
void copystr();
void cutstr();
void pastestr();
void compare();
void FindCommand();



int main()
{
    while(1)
    {
    // char buff[FILENAME_MAX];
    // GetCurrentDir( buff, FILENAME_MAX);
    // printf("%s\n", buff);
    // printf("------------------------------------\n");
    scanf("%s", command);
    if(!strcmp(command, "exit"))
        break;
    FindCommand();
    }

    return 0;    
}

void FindCommand()
{
    if(!strcmp(command, "cat")) {
        cat();
        return;
    } 
    else if(!strcmp(command, "createfile")) {
        createfile();
        return;
    }
    else if(!strcmp(command, "insertstr")) {
        insertstr();
        return;
    }
    else if(!strcmp(command, "removestr")) {
        removestr();
        return;
    }
    else if(!strcmp(command, "copystr")) {
        copystr();
        return;
    }
    else if(!strcmp(command, "cutstr")) {
        cutstr();
        return;
    }
    else if(!strcmp(command, "pastestr")) {
        pastestr();
        return;
    }
    else if(!strcmp(command,"compare")) {
        compare();
        return;
    }
    else {
        printf("Invalid Command!\nSimply type <--help> for more information.\n");
        return;
    }

}

void cat() 
{
    char x;
    char *new_address = malloc(sizeof(char) * MAX_ADD);

    scanf(" %[^ ]s", command_extension);

    if(strcmp(command_extension, "--file") != 0) {
        printf("Invalid Command!\nTry cat --file!\n");
        free(new_address);
        return;
    }

    getchar();
    scanf("%c", &x);
    scanf(" %[^\n]s", address);

    if(x == '/') {
        new_address = address;
    }else if(x == '"') {
        new_address = address + 1;
        new_address[strlen(new_address) - 1] = '\0';
    }


    // int str[MAX];
    char str;
    filepointer = fopen(new_address , "r");
    if(filepointer != NULL) {
        str = fgetc(filepointer);
        while(str != EOF) {
            printf("%c", str);
            str = getc(filepointer);
        }
        printf("\n");
    }else {
        printf("No Such A File!\n");
        free(new_address);
        return;
    }
    fclose(filepointer);
    free(new_address);
}

void createfile()
{
    char *directory = malloc(sizeof(char) * MAX_ADD);
    char *next_directory = malloc(sizeof(char) * MAX_ADD);
    char *new_address = malloc(sizeof(char) * MAX_ADD);
    char x;
    int counter = 0;
    int result;

    scanf(" %[^ ]s", command_extension);

    if(strcmp(command_extension, "--file") != 0) {
        printf("Invalid Command!\nTry createfile --file!\n");
        free(directory);
        free(next_directory);
        free(new_address);
        return;
    }

    getchar();
    scanf("%c", &x);
    scanf(" %[^\n]s", address);

    if(x == '/') {
        new_address = address;
    }else if(x == '"') {
        new_address = address + 1;
        new_address[strlen(new_address) - 1] = '\0';
    }

    directory = strtok(new_address, "/");

    // printf("%s\n", directory);
    while(directory != NULL)
    {
        // printf("dir = %s\n", directory);
        counter++;
        next_directory = strtok(NULL, "/");
        if(next_directory == NULL) {
            if(!access(directory, F_OK)) {
                printf("File already exist!\n");
                free(directory);
                free(next_directory);
                free(new_address);
                return;
            }
            filepointer = fopen(directory, "a");
            fclose(filepointer);
            printf("File created successfully!\n");
            break;
        }
        mkdir(directory); 
        chdir(directory);

        // mkdir(directory);
        strcpy(directory, next_directory);
    }
    // printf("count = %d\n", counter);
    
    while(counter != 1)
    {
        chdir("..");
        counter--;
    }
    free(directory);
    free(next_directory);
    free(new_address);
}

void insertstr() 
{
    FILE *temp;
    char *new_address = malloc(sizeof(char) * MAX_ADD);
    char str[MAX_LINE];
    char *new_str = malloc(sizeof(char) * MAX_CONTENT);
    char x;
    int row, column, current_row = 0, current_column = 0;

    scanf(" %[^ ]s", command_extension);
    // printf("command ext = i%si\n", command_extension);

    if(strcmp(command_extension, "--file") != 0) {
        printf("Invalid Command!\nTry insertstr --file or --str or --pos!\n");
        free(new_address);
        free(new_str);
        return;
    }

    getchar();
    scanf("%c", &x);
    // printf("x = %c\n", x);

    if(x == '/') {
        scanf("%s", address);
        new_address = address;
        x = '\0';
    }else if(x == '"') {
        scanf("%[^\"]s", address);
        new_address = address + 1;
        // new_address[strlen(new_address) - 1] = '\0';
        x = '\0';
    }
    // printf("address = i%si\n", new_address);

    getchar();
    scanf(" %[^ ]s", command_extension);
    // printf("command ext = i%si\n", command_extension);

    if(strcmp(command_extension, "--str") != 0) {
        printf("Invalid Command!\nTry insertstr --file or --str or --pos!\n");
        free(new_address);
        free(new_str);
        return;
    }

    getchar();
    scanf("%c", &x);
    // printf("c = %c\n", x);
    if(x == '"') {
        scanf("%[^-]s", str);
        new_str = str;
        new_str[strlen(new_str) - 2] = '\0';
    }else {
        scanf("%s", str);
        new_str = str;
        for(int i = sizeof(str) - 2; i >=0; i--) {
            new_str[i + 1] = new_str[i];
        }
        new_str[0] = x;
    }
    int length = strlen(new_str);
    // printf("new str = i%si\n", new_str);

    scanf("%[^ ]s", command_extension);
    // printf("command ext = i%si\n", command_extension);

    if(strcmp(command_extension, "--pos") != 0) {
        printf("Invalid Command!\nTry insertstr --file or --str or --pos!\n");
        free(new_address);
        free(new_str);
        return;
    }

    scanf("%d:%d", &row, &column);

    filepointer = fopen(new_address, "r");
    if(filepointer == NULL) {
        printf("File Doesn't Exist!\n");
        free(new_address);
        free(new_str);
        return;
    }
    temp = fopen("temp", "w");


    while(current_row != row - 1) 
    { 
        x = fgetc(filepointer);
        if(x == '\n') {
            current_row++;
        }
        if(x == EOF) {
            x = '\n';
        }
        fputc(x, temp);
    }

    while(current_column != column)
    {
        x = fgetc(filepointer);
        if(x == EOF) {
            x = ' ';
        }
        fputc(x, temp);
        current_column++;
    }

    for(int i = 0; i < length; i++)
    {
        if(new_str[i] == '\\' && new_str[i + 1] == 'n') {
            fprintf(temp, "\n");
            i++;
        }else if(new_str[i] == '\\' && new_str[i + 1] == '\\' && new_str[i + 2] == 'n') { 
            fprintf(temp, "\\n");
            i += 2;
        }else {
            x = new_str[i];
            fputc(x, temp);
        }
    }

    while((x = fgetc(filepointer)) != EOF)
    {
        fputc(x, temp);
    }

    fclose(filepointer);
    fclose(temp);

    filepointer = fopen(new_address, "w");
    temp = fopen("temp", "r");

    x = fgetc(temp);
    while(x != EOF)
    {
        fputc(x, filepointer);
        x = fgetc(temp);
    }

    fclose(temp);
    fclose(filepointer);

    int result = remove("temp");
    if(!result) {
        printf("Text Inserted Successfully!\n");
    }
    free(new_address);
    free(new_str);
}

void removestr()
{
    FILE *temp;
    char *new_address = malloc(sizeof(char) * MAX_ADD);
    char x;
    int row, column, current_row = 1, current_column = 0, size;

    scanf(" %[^ ]s", command_extension);

    if(strcmp(command_extension, "--file") != 0) {
        printf("Invalid Command!\nTry removestr --file!\n");
        free(new_address);
        return;
    }

    getchar();
    scanf("%c", &x);

    if(x == '/') {
        scanf("%s", address);
        new_address = address;
        x = '\0';
    }else if(x == '"') {
        scanf("%[^\"]s", address);
        new_address = address + 1;
        x = '\0';
    }

    getchar();
    scanf("%[^ ]s", command_extension); 

    if(strcmp(command_extension, "--pos") != 0) {
        printf("Invalid Command!\nTry removestr --file or --pos!\n");
        free(new_address);    
        return;
    }

    scanf("%d:%d", &row, &column);

    getchar();
    scanf("%[^ ]s", command_extension);   

    if(strcmp(command_extension, "-size") != 0) {
        printf("Invalid Command!\nTry removestr --file or --pos or -size!\n");
        free(new_address);
        return;
    } 

    scanf("%d", &size);

    getchar();
    scanf("%[^\n]s", command_extension);
    
    filepointer = fopen(new_address, "r");
    if(filepointer == NULL) {
        printf("File Doesn't Exist!\n");
        free(new_address);
        return;
    }
    temp = fopen("temp", "w");
    
    if(!strcmp(command_extension, "-b")) {

        while(current_row != row) 
        {       
            x = fgetc(filepointer);
            if(x == '\n') {
                current_row++;
            }
            if(x == EOF) {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(temp);
                remove("temp");
                free(new_address);
                return;
            }            
        }

        while(current_column != column)
        {
            x = fgetc(filepointer);
            if(x == EOF || x == '\n') {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(temp);
                remove("temp");
                free(new_address);
                return;
            }
            current_column++;
        }

        for(int i = size; i > 0; i--)
        {
            if(current_column == 0 && current_row != 1) {
                current_row--;
                fclose(filepointer);
                filepointer = fopen(new_address, "r");
                
                row = current_row;
                current_row = 1;
                while(current_row != row) 
                {       
                    x = fgetc(filepointer);
                    if(x == '\n') {
                        current_row++;
                    }
                }
                while((x = fgetc(filepointer)) != '\n') {
                    current_column++;
                }
            } else {
                current_column--;
            }
            if(current_column < 0) {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(temp);
                remove("temp");
                free(new_address);
                return;
            }
        }

        row = current_row;
        column = current_column;
        current_column = 0;
        current_row = 1;

        fclose(filepointer);
        fclose(temp);

        filepointer = fopen(new_address, "r");
        temp = fopen("temp", "w");

        while(current_row != row) 
        {    
            x = fgetc(filepointer);
            if(x == '\n') {
                current_row++;
            }
            if(x == EOF) {
                x = '\n';
            }
            fputc(x, temp);
        }

        while(current_column != column)
        {
            x = fgetc(filepointer);
            if(x == EOF) {
                x = ' ';
            }
            fputc(x, temp);
            current_column++;
        }

        while(current_column != column + size) 
        {
            x = fgetc(filepointer);
            current_column++;
        }

        while((x = fgetc(filepointer)) != EOF)
        {
            fputc(x, temp);
        }

        fclose(filepointer);
        fclose(temp);

    }else if(!strcmp(command_extension, "-f")) {
        current_row = 0;
        
        while(current_row != row - 1) 
        {    
            x = fgetc(filepointer);
            if(x == '\n') {
                current_row++;
            }
            if(x == EOF) {
                x = '\n';
            }
            fputc(x, temp);
        }

        while(current_column != column)
        {
            x = fgetc(filepointer);
            if(x == EOF) {
                x = ' ';
            }
            fputc(x, temp);
            current_column++;
        }

        while(current_column != column + size) 
        {
            x = fgetc(filepointer);
            current_column++;
        }

        while((x = fgetc(filepointer)) != EOF)
        {
            fputc(x, temp);
        }

        fclose(filepointer);
        fclose(temp);

    }else {
        printf("Invalid Command!\nTry insertstr --file or --pos or -size or -b/-f\n");
        fclose(filepointer);
        fclose(temp);
        remove("temp");
        free(new_address);
        return;
    }

    filepointer = fopen(new_address, "w");
    temp = fopen("temp", "r");

    //copy temp into main file
    x = fgetc(temp);
    while(x != EOF)
    {
        fputc(x, filepointer);
        x = fgetc(temp);
    }

    fclose(temp);
    fclose(filepointer);

    int result = remove("temp");
    if(!result) {
        printf("Text Removed Successfully!\n");
    }

    free(new_address);
}

void copystr() 
{
    FILE *temp;
    char *new_address = malloc(sizeof(char) * MAX_ADD);
    char x;
    int row, column, current_row = 1, current_column = 0, size;
        
    scanf(" %[^ ]s", command_extension);

    if(strcmp(command_extension, "--file") != 0) {
        printf("Invalid Command!\nTry copystr --file!\n");
        free(new_address);
        return;
    }
    // printf("comm ext : i%si\n", command_extension);

    getchar();
    scanf("%c", &x);
    // printf("x : %c\n", x);

    if(x == '/') {
        scanf("%s", address);
        new_address = address;
        x = '\0';
    }else if(x == '"') {
        scanf("%[^\"]s", address);
        new_address = address + 1;
        x = '\0';
    }
    // printf("new address : i%si\n", new_address);

    getchar();
    scanf("%[^ ]s", command_extension); 
    // printf("comm ext : i%si\n", command_extension);

    if(strcmp(command_extension, "--pos") != 0) {
        printf("Invalid Command!\nTry copystr --file or --pos!\n");
        free(new_address);
        return;
    }

    scanf("%d:%d", &row, &column);

    getchar();
    scanf("%[^ ]s", command_extension);   
    // printf("comm ext : i%si\n", command_extension);

    if(strcmp(command_extension, "-size") != 0) {
        printf("Invalid Command!\nTry copystr --file or --pos or -size!\n");
        free(new_address);
        return;
    } 

    scanf("%d", &size);
    // printf("size : %d\n", size);

    getchar();
    scanf("%[^\n]s", command_extension);
    // printf("comm ext : i%si\n", command_extension);

    
    filepointer = fopen(new_address, "r");
    if(filepointer == NULL) {
        printf("File Doesn't Exist!\n");
        free(new_address);
        return;
    }
    temp = fopen("TempCopy", "w");

    if(!strcmp(command_extension, "-b")) {

        while(current_row != row)
        {
            x = fgetc(filepointer);
            if(x == '\n') {
                current_row++;
            }
            if(x == EOF) {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(temp);
                remove("temp");
                free(new_address);
                return;
            }            
        }

        while(current_column != column)
        {
            x = fgetc(filepointer);
            if(x == EOF || x == '\n') {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(temp);
                remove("temp");
                free(new_address);
                return;
            }
            current_column++;
        }

        for(int i = size; i > 0; i--)
        {
            if(current_column == 0 && current_row != 1) {
                current_row--;
                fclose(filepointer);
                filepointer = fopen(new_address, "r");
                
                row = current_row;
                current_row = 1;
                while(current_row != row) 
                {       
                    x = fgetc(filepointer);
                    if(x == '\n') {
                        current_row++;
                    }
                }
                while((x = fgetc(filepointer)) != '\n') {
                    current_column++;
                }
            } else {
                current_column--;
            }
            if(current_column < 0) {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(temp);
                remove("temp");
                free(new_address);
                return;
            }
        }

        row = current_row;
        column = current_column;
        current_column = 0;
        current_row = 1;

        fclose(filepointer);
        fclose(temp);

        filepointer = fopen(new_address, "r");
        temp = fopen("TempCopy", "w");

        while(current_row != row) 
        {    
            x = fgetc(filepointer);
            if(x == '\n') {
                current_row++;
            }
        }

        while(current_column != column)
        {
            x = fgetc(filepointer);
            current_column++;
        }

        while(current_column != column + size) 
        {
            x = fgetc(filepointer);
            fputc(x, temp);
            current_column++;
        }

        fclose(filepointer);
        fclose(temp);
        printf("Text Copied Successfully!\n");


    }else if(!strcmp(command_extension, "-f")) {
        current_row = 0;

        while(current_row != row - 1) 
        {    
            x = fgetc(filepointer);
            if(x == '\n') {
                current_row++;
            }
            if(x == EOF) {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(temp);
                remove("temp");
                free(new_address);
                return;
            }
        }

        while(current_column != column)
        {
            x = fgetc(filepointer);
            if(x == EOF) {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(temp);
                remove("temp");
                free(new_address);
                return;
            }
            current_column++;
        }

        while(current_column != column + size) 
        {
            x = fgetc(filepointer);
            fputc(x, temp);
            current_column++;
        }

    fclose(filepointer);
    fclose(temp);
    printf("Text Copied Successfully!\n");

    } else {
        printf("Invalid Command!\nTry insertstr --file or --pos or -size or -b/-f\n");
        fclose(filepointer);
        fclose(temp);
        remove("temp");
        free(new_address);
        return;
    }
    
    free(new_address);
}

void cutstr()
{
    FILE *TempCopy, *temp;
    char *new_address = malloc(sizeof(char) * MAX_ADD);
    char x;
    int row, column, current_row = 1, current_column = 0, size;
        
    scanf(" %[^ ]s", command_extension);

    if(strcmp(command_extension, "--file") != 0) {
        printf("Invalid Command!\nTry cutstr --file!\n");
        free(new_address);
        return;
    }
    // printf("comm ext : i%si\n", command_extension);

    getchar();
    scanf("%c", &x);
    // printf("x : %c\n", x);

    if(x == '/') {
        scanf("%s", address);
        new_address = address;
        x = '\0';
    }else if(x == '"') {
        scanf("%[^\"]s", address);
        new_address = address + 1;
        x = '\0';
    }
    // printf("new address : i%si\n", new_address);

    getchar();
    scanf("%[^ ]s", command_extension); 
    // printf("comm ext : i%si\n", command_extension);

    if(strcmp(command_extension, "--pos") != 0) {
        printf("Invalid Command!\nTry cutstr --file or --pos!\n");
        free(new_address);
        return;
    }

    scanf("%d:%d", &row, &column);

    getchar();
    scanf("%[^ ]s", command_extension);   
    // printf("comm ext : i%si\n", command_extension);

    if(strcmp(command_extension, "-size") != 0) {
        printf("Invalid Command!\nTry cutstr --file or --pos or -size!\n");
        free(new_address);
        return;
    } 

    scanf("%d", &size);
    // printf("size : %d\n", size);

    getchar();
    scanf("%[^\n]s", command_extension);
    // printf("comm ext : i%si\n", command_extension);

    
    filepointer = fopen(new_address, "r");
    if(filepointer == NULL) {
        printf("File Doesn't Exist!\n");
        free(new_address);
        return;
    }
    TempCopy = fopen("TempCopy", "w");
    temp = fopen("temp", "w");

    if(!strcmp(command_extension, "-b")) {

        while(current_row != row)
        {
            x = fgetc(filepointer);
            if(x == '\n') {
                current_row++;
            }
            if(x == EOF) {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(TempCopy);
                fclose(temp);
                remove("temp");
                remove("TempCopy");
                free(new_address);
                return;
            }            
        }

        while(current_column != column)
        {
            x = fgetc(filepointer);
            if(x == EOF || x == '\n') {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(TempCopy);
                fclose(temp);
                remove("temp");
                remove("TempCopy");
                free(new_address);
                return;
            }
            current_column++;
        }

        for(int i = size; i > 0; i--)
        {
            if(current_column == 0 && current_row != 1) {
                current_row--;
                fclose(filepointer);
                filepointer = fopen(new_address, "r");
                
                row = current_row;
                current_row = 1;
                while(current_row != row) 
                {       
                    x = fgetc(filepointer);
                    if(x == '\n') {
                        current_row++;
                    }
                }
                while((x = fgetc(filepointer)) != '\n') {
                    current_column++;
                }
            } else {
                current_column--;
            }
            if(current_column < 0) {
                printf("Out Of Range Position!\n");
                fclose(filepointer);
                fclose(TempCopy);
                fclose(temp);
                remove("temp");
                remove("TempCopy");
                free(new_address);
                return;
            }
        }

        row = current_row;
        column = current_column;
        current_column = 0;
        current_row = 1;

        fclose(filepointer);
        fclose(TempCopy);
        fclose(temp);

        filepointer = fopen(new_address, "r");
        TempCopy = fopen("TempCopy", "w");
        temp = fopen("temp", "w");

        while(current_row != row) 
        {    
            x = fgetc(filepointer);
            if(x == '\n') {
                current_row++;
            }
            if(x == EOF) {
                x = '\n';
            }
            fputc(x, temp);
        }

        while(current_column != column)
        {
            x = fgetc(filepointer);
            if(x == EOF) {
                x = ' ';
            }
            fputc(x, temp);
            current_column++;
        }

        while(current_column != column + size) 
        {
            x = fgetc(filepointer);
            fputc(x, TempCopy);
            current_column++;
        }

        while((x = fgetc(filepointer)) != EOF)
        {
            fputc(x, temp);
        }

        fclose(filepointer);
        fclose(TempCopy);
        fclose(temp);

        filepointer = fopen(new_address, "w");
        temp = fopen("temp", "r");

        x = fgetc(temp);
        while(x != EOF)
        {
            fputc(x, filepointer);
            x = fgetc(temp);
        }

        fclose(temp);
        fclose(filepointer);

    int result = remove("temp");
    if(!result) {
        printf("Text Cut Successfully!\n");
    }

    }else if(!strcmp(command_extension, "-f")) {
        current_row = 0;

        while(current_row != row - 1) 
        {    
            x = fgetc(filepointer);
            if(x == '\n') {
                current_row++;
            }
            if(x == EOF) {
                x = '\n';
            }
            fputc(x, temp);
        }

        while(current_column != column)
        {
            x = fgetc(filepointer);
            if(x == EOF) {
                x = ' ';
            }
            fputc(x, temp);
            current_column++;
        }

        while(current_column != column + size) 
        {
            x = fgetc(filepointer);
            fputc(x, TempCopy);
            current_column++;
        }

        while((x = fgetc(filepointer)) != EOF)
        {
            fputc(x, temp);
        }

        fclose(filepointer);
        fclose(TempCopy);
        fclose(temp);

        filepointer = fopen(new_address, "w");
        temp = fopen("temp", "r");

        x = fgetc(temp);
        while(x != EOF)
        {
            fputc(x, filepointer);
            x = fgetc(temp);
        }

        fclose(temp);
        fclose(filepointer);

    int result = remove("temp");
    if(!result) {
        printf("Text Cut Successfully!\n");
    }

    } else {
        printf("Invalid Command!\nTry cutstr --file or --pos or -size or -b/-f\n");
        fclose(filepointer);
        fclose(TempCopy);
        fclose(temp);
        remove("temp");
        remove("TempCopy");
        free(new_address);
        return;
    }
    free(new_address);
}

void pastestr()
{
    FILE *temp;
    FILE *TempCopy;
    char *new_address = malloc(sizeof(char) * MAX_ADD);
    char x;
    int row, column, current_row = 0, current_column = 0;

    scanf(" %[^ ]s", command_extension);

    if(strcmp(command_extension, "--file") != 0) {
        printf("Invalid Command!\nTry pastestr --file!\n");
        free(new_address);
        return;
    }

    getchar();
    scanf("%c", &x);

    if(x == '/') {
        scanf("%s", address);
        new_address = address;
        x = '\0';
    }else if(x == '"') {
        scanf("%[^\"]s", address);
        new_address = address + 1;
        x = '\0';
    }

    getchar();
    scanf("%[^ ]s", command_extension); 

    if(strcmp(command_extension, "--pos") != 0) {
        printf("Invalid Command!\nTry pastestr --file or --pos!\n");
        free(new_address);
        return;
    }

    scanf("%d:%d", &row, &column);
    
    filepointer = fopen(new_address, "r");
    if(filepointer == NULL) {
        printf("File Doesn't Exist!\n");
        free(new_address);
        return;
    }
    temp = fopen("temp", "w");
    TempCopy = fopen("TempCopy", "r");

    while(current_row != row - 1) 
    { 
        x = fgetc(filepointer);
        if(x == '\n') {
            current_row++;
        }
        if(x == EOF) {
            x = '\n';
        }
        fputc(x, temp);
    }

    while(current_column != column)
    {
        x = fgetc(filepointer);
        if(x == EOF) {
            x = ' ';
        }
        fputc(x, temp);
        current_column++;
    }

    while((x = fgetc(TempCopy)) != EOF) 
    {
        fputc(x, temp);
    }

    while((x = fgetc(filepointer)) != EOF)
    {
        fputc(x, temp);
    }

    fclose(filepointer);
    fclose(temp);
    fclose(TempCopy);

    filepointer = fopen(new_address, "w");
    temp = fopen("temp", "r");

    //copy temp into main file
    x = fgetc(temp);
    while(x != EOF)
    {
        fputc(x, filepointer);
        x = fgetc(temp);
    }

    fclose(temp);
    fclose(filepointer);

    int result = remove("temp");
    if(!result) {
        printf("Text Pasted Successfully!\n");
    }
    free(new_address);
}
void compare()
{
    FILE *fptr1, *fptr2;
    char *address1 = malloc(sizeof(char) * MAX_ADD);
    char *address2 = malloc(sizeof(char) * MAX_ADD); 
    char *new_address1 = malloc(sizeof(char) * MAX_ADD); 
    char *new_address2 = malloc(sizeof(char) * MAX_ADD);
    char x;
    int row = 1;
    char str1[1000][1000];
    char str2[1000][1000];


    getchar();
    scanf("%c", &x);
    // printf("x : %c\n", x);
    if(x == '/') {
        scanf("%s", address1);
        new_address1 = address1;
        // x = '\0';
    }else if(x == '"') {
        scanf("%[^\"]s", address1);
        new_address1 = address1 + 1;
        // x = '\0';
    }
    // printf("new address : i%si\n", new_address1);
    
    getchar();
    if(x == '"') {
        getchar();
    }

    scanf("%c", &x);
    // printf("x : %c\n", x);

    if(x == '/') {
        scanf("%s", address2);
        new_address2 = address2;
        x = '\0';
    }else if(x == '"') {
        scanf("%[^\"]s", address2);
        new_address2 = address2 + 1;
        x = '\0';
    }
    // printf("new address2 : i%si\n", new_address2);

    fptr1 = fopen(new_address1, "r");
    fptr2 = fopen(new_address2, "r");

    int i = 0;

    while(fgets(str1[i], MAX_CONTENT, fptr1))
    {
        i++;
    }
    for(int j = 0; j < i - 1; j++){
        str1[j][strlen(str1[j]) - 1] = '\0';
    }

    int z = 0;

    while(fgets(str2[z], MAX_CONTENT, fptr2))
    {
        z++;
    }
    for(int y = 0 ; y < z - 1; y++){
        str2[y][strlen(str2[y]) - 1] = '\0';
    }
    
    if(i > z) {
        printf("\"Fisrt File > Second File\"\n");
    }else if(i == z) {
        printf("\"Fisrt File = Second File\"\n");
    }else {
        printf("\"First File < Second File\"\n");
    }

    int size1 = i;
    int size2 = z;
    i = 0;
    z = 0;

    while(i < size1 && z < size2)
    {
        if(strcmp(str1[i], str2[z])) {
            printf("======== #%d ========\n", row);
            printf("%s\n", str1[i]);
            printf("%s\n", str2[z]);
        }
        i++;
        z++;
        row++;
    }

    if(size1 > size2) {
        printf(">>>>>>>> #%d - #%d >>>>>>>>\n", i+1, size1);
        while(i < size1) 
        {
            printf("%s\n", str1[i]);
            i++;
        }
    }
    else if(size2 > size1) {
        printf(">>>>>>>> #%d - #%d >>>>>>>>\n", z+1, size2);
        while(z < size2) 
        {
            printf("%s\n", str2[z]);
            z++;
        }
    }
    free(new_address1);
    free(new_address2);
    free(address1);
    free(address2);

}