#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>  
#include <time.h>    

void moving_character_signboard(char file_name[], int line_length, int sp, int color);
void gotoxy(int x, int y);
void draw_rectangle(int c, int r);
void display_file_name(const char* file_name);
void set_text_color(int color);
void intro_animation();

int main(void)
{
    char file_name[20];
    int sp, color;
    
    intro_animation();
    
    system("cls");
    
    printf("광고내용이 들어있는 파일 이름을 입력하고 Enter> ");
    scanf("%s", file_name);
    printf("광고판의 속도를 입력하고 Enter> ");
    scanf("%d", &sp);
    printf("광고판의 글자 색상을 입력하고 Enter> (0~15 사이의 색상 코드 입력) ");
    scanf("%d", &color);
    
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        printf("\n없는 파일입니다.\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END); 
    int line_length = ftell(fp); 
    rewind(fp); 
    fclose(fp); 
    
    display_file_name(file_name);
    moving_character_signboard(file_name, line_length, sp, color);
    return 0;
}

void set_text_color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void moving_character_signboard(char file_name[], int line_length, int sp, int color)
{
    char *ptr, chr[121];
    int i, j, length;
    FILE *fp;
    
    ptr = (char *)malloc(121);
    gotoxy(1, 9);
    draw_rectangle(line_length*2, 1);
    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        printf("\n없는 파일입니다.\n");
        exit(1);
    }
    
    set_text_color(color);

    time_t start_time = time(NULL);

     fgets(chr, 120, fp);
    length = strlen(chr);
    
    if (chr[length - 1] == '\n')
    {
        chr[length - 1] = '\0';
        length--;
    }

    ptr[120] = '\0';

    while (1)
    {
        for (j = 0; j < length; j++)
        {
            if (_kbhit())
            {
                time_t end_time = time(NULL);
                double elapsed = difftime(end_time, start_time);
                
                _getch();
                free(ptr); 
                fclose(fp); 
                set_text_color(7);
                
                printf("\n\n%.0f초 동안 광고하셨습니다.\n", elapsed);
                return;
            }

            for (i = 0; i < length; i++)
                ptr[i] = (i < length - j) ? chr[(i + j) % length] : ' '; 

            gotoxy(3, 10);
            printf("%s", ptr);
            Sleep(sp);
            
            gotoxy(3, 10);
            for (i = 0; i < line_length; i++)
                printf(" "); 
            Sleep(sp / 3); 
        }

        for (j = 0; j < length; j++)
        {
            if (_kbhit()) 
            {
                time_t end_time = time(NULL);
                double elapsed = difftime(end_time, start_time);
                
                _getch();   
                free(ptr);  
                fclose(fp);
                set_text_color(7);
                
                printf("\n\n%.0f초 동안 광고하셨습니다.\n", elapsed);
                return;  
            }

            for (i = length - 1; i >= j; i--)
                ptr[i] = ptr[i - 1];  
            ptr[j] = chr[j % length];

            gotoxy(3, 10);
            Sleep(sp);
            printf("%s", ptr);
        }
    }
    fclose(fp);
    set_text_color(7);
}

void gotoxy(int x, int y)
{
    COORD Pos = {x - 1, y - 1};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void draw_rectangle(int c, int r)
{
    int i, j;
    unsigned char a = 0xa6;
    unsigned char b[7];
    for (i = 1; i < 7; i++)
        b[i] = 0xa0 + i;

    printf("%c%c", a, b[3]);
    for (i = 0; i < c/2+1; i++)
        printf("%c%c", a, b[1]);
    printf("%c%c", a, b[4]);
    printf("\n");
    for (i = 0; i < r; i++)
    {
        printf("%c%c", a, b[2]);
        for (j = 0; j < c/2+1; j++)
            printf(" ");
        printf("%c%c", a, b[2]);
        printf("\n");
    }
    printf("%c%c", a, b[6]);
    for (i = 0; i < c/2+1; i++)
        printf("%c%c", a, b[1]);
    printf("%c%c", a, b[5]);
    printf("\n");
}

void display_file_name(const char* file_name)
{
    char display_name[20];
    strcpy(display_name, file_name);

    char* dot = strrchr(display_name, '.');
    if (dot != NULL)
    {
        *dot = '\0';
    }

    gotoxy(3, 7);
    printf("%s 광고\n", display_name);
}

void intro_animation()
{
    char intro_text[] = "움직이는 글자 광고판";
    int length = strlen(intro_text);
    int start_pos = 1;
    int end_pos = 30;

    while (!_kbhit())
    {
        for (int pos = start_pos; pos < end_pos; pos++)
        {
            gotoxy(pos, 3);
            printf("%s", intro_text);
            Sleep(100);
            gotoxy(pos, 3);  
            printf("                    ");
        }
        for (int pos = end_pos; pos > start_pos; pos--)
        {
            gotoxy(pos, 3);  
            printf("%s", intro_text);
            Sleep(100);
            gotoxy(pos, 3);  
            printf("                    ");
        }
    }
    _getch();
    system("cls");
}
