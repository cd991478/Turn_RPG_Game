#define _CRT_SECURE_NO_WARNINGS
#define randomize() srand((unsigned)time(NULL))	
#define random(n) (rand() % (n))
#define cls system("cls")
#define delay(n) Sleep(n)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include <time.h>

void gotoxy(int x, int y)
{
    COORD Cur;
    Cur.X = x;
    Cur.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO BufInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
    return BufInfo.dwCursorPosition.X;
}
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO BufInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
    return BufInfo.dwCursorPosition.Y;
}
typedef enum {
    NOCURSOR,
    SOLIDCURSOR,
    NORMALCURSOR
} CURSOR_TYPE;
typedef enum {
    BLACK = 0, BLUE = 1, GREEN = 2, SKYBLUE = 3, RED = 4, PURPLE = 5, ORANGE = 6,
    WHITE = 7, GREY = 8, LIGHTBLUE = 9, LIGHTGREEN = 10, BLUEGREEN = 11, LIGHTRED = 12, LIGHTPURPLE = 13,
    YELLOW = 14, LIGHTWHITE = 15
} COLOR_TYPE;
void setcursortype(CURSOR_TYPE c)
{
    CONSOLE_CURSOR_INFO CurInfo;

    switch (c) {
    case NOCURSOR:
        CurInfo.dwSize = 1;
        CurInfo.bVisible = FALSE;
        break;
    case SOLIDCURSOR:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case NORMALCURSOR:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}
void setcolor(COLOR_TYPE text, COLOR_TYPE back)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
void textcolor(COLOR_TYPE text)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}

void setConsoleSize(int width, int height) {
    // 콘솔 화면 버퍼 크기 설정
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    // 콘솔 창 크기 설정
    SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
}

int player_level = 1;
int player_hp = 100;
int player_maxhp = 100;
int player_mp = 100;
int player_maxmp = 100;
int player_att = 10;
int player_def = 0;
int player_defup = 0;
int player_exp = 0;
int player_maxexp = 100;
int player_statpoint = 0;
int player_skillpoint = 0;

int speed = 800;
int cheat;
int c_value = 0;
int play_time = 0;
int time_h = 0;
int time_m = 0;
int time_s = 0;
int defover_state = 0;
int win = 0;
int lose = 0;
int total = 0;
int rating = 1000;
char rank[128] = "D";

int player_skill1 = 1;
int player_skill2 = 1;
int player_skill3 = 1;
int player_skill4 = 1;
int player_skill5 = 1;
int player_gold = 0;
int player_skill1max = 5;
int player_skill2max = 5;
int player_skill3max = 5;
int player_skill4max = 5;
int player_skill5max = 5;
int com_level = 1;
int com_hp = 100;
int com_maxhp = 100;
int com_att = 10;
int com_def;
int stage_level = 1;
int menu_fight = 0;
int menu_stat = 0;
int menu_skill = 0;
int menu_item = 0;
int goto_stage = 1;
int turn = 0;
int com_skill;
int player_stun = 0;
int player_defmain = 0;
int player_dote = 0;
int player_dotecount = 0;
int* item_att;
int* item_mp;
int item_code = 0;

char order;
char stat_up;
char skill_up;
char choose;
char item_choose;
char stage01[] = { "용병" };
char stage02[] = { "전사" };
char stage03[] = { "저격수" };
char stage04[] = { "얼음 마법사" };
char stage05[] = { "번개 마법사" };
char stage06[] = { "화염 마법사" };
char stage07[] = { "천공 마법사" };
char stage08[] = { "암흑 마법사" };
char stage09[] = { "검객" };
char stage10[] = { "창의 달인" };
#define cls system("cls")
void d1s()
{
    delay(speed);
}
void char_eft()
{
    gotoxy(20, 16);
    puts(" ");
    gotoxy(50, 16);
    puts(" ");
    gotoxy(20, 16);
    puts("옷");
    gotoxy(50, 16);
    puts("옷");
    gotoxy(0, 18);
    printf("──────────────────────────────────────────────────────────────────────────────\n");
}
void char_cls()
{
    gotoxy(0, 15);
    puts("                                                                                ");
    gotoxy(0, 16);
    puts("                                                                                ");
    gotoxy(0, 17);
    puts("                                                                                ");
}
void txt_cls()
{
    gotoxy(0, 19);
    puts("                                                                                ");
    gotoxy(0, 20);
    puts("                                                                                ");
    gotoxy(0, 21);
    puts("                                                                                ");
    gotoxy(0, 22);
    puts("                                                                                ");
}
void txt_pos()
{
    gotoxy(0, 19);
}
void eft_set()
{
    char_cls();
    char_eft();
    txt_cls();
    txt_pos();
}
void move_set()
{
    gotoxy(0, 15);
    puts("                                                                                ");
    gotoxy(0, 16);
    puts("                                                                                ");
    gotoxy(0, 17);
    puts("                                                                                ");
    gotoxy(20, 16);
    puts(" ");
    gotoxy(50, 16);
    puts(" ");
    gotoxy(20, 16);
    puts("옷");
    gotoxy(28, 16);
    puts("옷");
    gotoxy(0, 18);
    printf("──────────────────────────────────────────────────────────────────────────────\n");
}
void char_set()
{
    char_cls();
    char_eft();
}
void playerhp_eft()
{
    gotoxy(19, 15);
    puts("+");
    delay(100);
    char_set();
    gotoxy(22, 17);
    puts("+");
    delay(100);
    char_set();
    gotoxy(19, 17);
    puts("+");
    delay(100);
    char_set();
    gotoxy(22, 15);
    puts("+");
    delay(100);
    char_set();
    gotoxy(20, 17);
    puts("+");
    delay(100);
    char_set();
    gotoxy(19, 16);
    puts("+");
    delay(100);
    char_set();
    gotoxy(20, 15);
    puts("+");
    delay(100);
    char_set();
    gotoxy(22, 16);
    puts("+");
    delay(100);
    char_set();
}
void playermp_eft()
{
    gotoxy(19, 15);
    puts("*");
    delay(100);
    char_set();
    gotoxy(22, 17);
    puts("*");
    delay(100);
    char_set();
    gotoxy(19, 17);
    puts("*");
    delay(100);
    char_set();
    gotoxy(22, 15);
    puts("*");
    delay(100);
    char_set();
    gotoxy(20, 17);
    puts("*");
    delay(100);
    char_set();
    gotoxy(19, 16);
    puts("*");
    delay(100);
    char_set();
    gotoxy(20, 15);
    puts("*");
    delay(100);
    char_set();
    gotoxy(22, 16);
    puts("*");
    delay(100);
    char_set();
}
void playerdfup_eft()
{
    gotoxy(22, 16);
    puts("│");
    delay(100);
    gotoxy(22, 17);
    puts("┘");
    delay(100);
    gotoxy(20, 17);
    puts("──");
    delay(100);
    gotoxy(18, 17);
    puts("└");
    delay(100);
    gotoxy(18, 16);
    puts("│");
    delay(100);
    gotoxy(18, 15);
    puts("┌");
    delay(100);
    gotoxy(20, 15);
    puts("──");
    delay(100);
    gotoxy(22, 15);
    puts("┐");
    delay(100);
    char_set();
    gotoxy(22, 16);
    puts("■");
    gotoxy(22, 17);
    puts("■");
    gotoxy(20, 17);
    puts("■");
    gotoxy(18, 17);
    puts("■");
    gotoxy(18, 16);
    puts("■");
    gotoxy(18, 15);
    puts("■");
    gotoxy(20, 15);
    puts("■");
    gotoxy(22, 15);
    puts("■");
    delay(100);
    char_set();
}
void comdfup_eft()
{
    gotoxy(52, 16);
    puts("│");
    delay(100);
    gotoxy(52, 17);
    puts("┘");
    delay(100);
    gotoxy(50, 17);
    puts("──");
    delay(100);
    gotoxy(48, 17);
    puts("└");
    delay(100);
    gotoxy(48, 16);
    puts("│");
    delay(100);
    gotoxy(48, 15);
    puts("┌");
    delay(100);
    gotoxy(50, 15);
    puts("──");
    delay(100);
    gotoxy(52, 15);
    puts("┐");
    delay(100);
    char_set();
    gotoxy(52, 16);
    puts("■");
    gotoxy(52, 17);
    puts("■");
    gotoxy(50, 17);
    puts("■");
    gotoxy(48, 17);
    puts("■");
    gotoxy(48, 16);
    puts("■");
    gotoxy(48, 15);
    puts("■");
    gotoxy(50, 15);
    puts("■");
    gotoxy(52, 15);
    puts("■");
    delay(100);
    eft_set();
}
void playerboom_eft()
{
    gotoxy(18, 15);
    puts("※");
    gotoxy(22, 17);
    puts("※");
    gotoxy(18, 17);
    puts("※");
    gotoxy(22, 15);
    puts("※");
    gotoxy(20, 17);
    puts("※");
    gotoxy(18, 16);
    puts("※");
    gotoxy(20, 15);
    puts("※");
    gotoxy(22, 16);
    puts("※");
    delay(200);
    eft_set();
}
void playerfreeze_eft()
{
    gotoxy(18, 15);
    puts("◇");
    gotoxy(22, 17);
    puts("◇");
    gotoxy(18, 17);
    puts("◇");
    gotoxy(22, 15);
    puts("◇");
    gotoxy(20, 17);
    puts("◇");
    gotoxy(18, 16);
    puts("◇");
    gotoxy(20, 15);
    puts("◇");
    gotoxy(22, 16);
    puts("◇");
    delay(200);
    eft_set();
}
void playerthunder_eft()
{
    gotoxy(18, 15);
    puts("☆");
    gotoxy(22, 17);
    puts("☆");
    gotoxy(18, 17);
    puts("☆");
    gotoxy(22, 15);
    puts("☆");
    gotoxy(20, 17);
    puts("☆");
    gotoxy(18, 16);
    puts("☆");
    gotoxy(20, 15);
    puts("☆");
    gotoxy(22, 16);
    puts("☆");
    delay(200);
}
void dote_eft()
{
    gotoxy(22, 15);
    puts("!");
    delay(500);
    eft_set();
}

void window()
{
    int x, y;
    gotoxy(0, 0);
    puts("┌");
    gotoxy(78, 0);
    puts("┐");
    gotoxy(0, 22);
    puts("└");
    gotoxy(78, 22);
    puts("┘");
    for (x = 2; x < 78; x = x + 2)
    {
        gotoxy(x, 0);
        puts("──");
        gotoxy(x, 22);
        puts("──");
    }
    for (y = 1; y < 22; y++)
    {
        gotoxy(0, y);
        puts("│");
        gotoxy(78, y);
        puts("│");
    }
}
void comhp_eft()
{
    gotoxy(50, 15);
    puts("+");
    delay(100);
    char_set();
    gotoxy(50, 17);
    puts("+");
    delay(100);
    char_set();
    gotoxy(49, 16);
    puts("+");
    delay(100);
    char_set();
    gotoxy(52, 16);
    puts("+");
    delay(100);
    char_set();
    gotoxy(49, 15);
    puts("+");
    delay(100);
    char_set();
    gotoxy(52, 17);
    puts("+");
    delay(100);
    char_set();
    gotoxy(49, 17);
    puts("+");
    delay(100);
    char_set();
    gotoxy(52, 15);
    puts("+");
    delay(100);
    eft_set();
}
void move_eft()
{
    int k;
    for (k = 50; k > 27; k--)
    {
        gotoxy(k, 16);
        puts("옷");
        delay(10);
        if (k != 28)
        {
            gotoxy(k, 16);
            puts("　");
        }
    }
}
void back_eft()
{
    int k;
    for (k = 27; k < 50; k++)
    {
        gotoxy(k, 16);
        puts("옷");
        delay(10);
        gotoxy(k, 16);
        puts("　");
    }
}
void skill0_eft()
{
    int k;
    for (k = 22; k < 49; k++)
    {
        gotoxy(k, 16);
        puts("→");
        delay(10);
        gotoxy(k, 16);
        puts(" ");
    }

    playermp_eft();
    eft_set();
}
void skill1_eft()
{
    int t;
    if (player_skill1 == 1)
        t = 20;
    if (player_skill1 == 2)
        t = 15;
    if (player_skill1 >= 3)
        t = 10;
    int k;
    for (k = 22; k < 49; k++)
    {
        if (k % 2 == 0)
        {
            gotoxy(k, 16);
            puts("●");
            delay(t);
            gotoxy(k, 16);
            puts(" ");
        }
        if (k % 2 == 1)
        {
            gotoxy(k, 16);
            puts("◎");
            delay(t);
            gotoxy(k, 16);
            puts(" ");
        }
    }
    if (player_skill1 == 1)
    {
        gotoxy(48, 16);
        puts("※");
        gotoxy(48, 15);
        puts("※");
        gotoxy(48, 17);
        puts("※");
        gotoxy(50, 16);
        puts("※");
        gotoxy(52, 16);
        puts("※");
        gotoxy(50, 15);
        puts("※");
        gotoxy(50, 17);
        puts("※");
        gotoxy(52, 17);
        puts("※");
        gotoxy(52, 15);
        puts("※");
        delay(100);
    }
    if (player_skill1 >= 2)
    {
        gotoxy(48, 17);
        puts("※");
        delay(20);
        gotoxy(50, 17);
        puts("※");
        delay(20);
        gotoxy(52, 17);
        puts("※");
        delay(20);
        gotoxy(48, 16);
        puts("※");
        delay(20);
        gotoxy(50, 16);
        puts("※");
        delay(20);
        gotoxy(52, 16);
        puts("※");
        delay(20);
        gotoxy(48, 15);
        puts("※");
        delay(20);
        gotoxy(50, 15);
        puts("※");
        delay(20);
        gotoxy(52, 15);
        puts("※");
        delay(50);
        char_set();
        delay(50);
        gotoxy(48, 16);
        puts("※");
        gotoxy(48, 15);
        puts("※");
        gotoxy(48, 17);
        puts("※");
        gotoxy(50, 16);
        puts("※");
        gotoxy(52, 16);
        puts("※");
        gotoxy(50, 15);
        puts("※");
        gotoxy(50, 17);
        puts("※");
        gotoxy(52, 17);
        puts("※");
        gotoxy(52, 15);
        puts("※");
        delay(100);
    }
    eft_set();
}
void skill2_eft()
{
    int t;
    if (player_skill2 == 1)
        t = 30;
    if (player_skill2 == 2)
        t = 25;
    if (player_skill2 >= 3)
        t = 20;
    int k;
    int i;
    for (k = 22; k < 49; k = k + 2)
    {
        gotoxy(k, 16);
        puts("／");
        delay(t);

        gotoxy(k + 2, 16);
        puts("＼");
        delay(t);
        k = k + 2;
    }
    int p;
    if (player_skill2 == 1)
    {
        p = 4;
    }
    if (player_skill2 == 2)
    {
        p = 5;
    }
    if (player_skill2 >= 3)
    {
        p = 6;
    }
    for (i = 0; i < p; i++)
    {
        for (k = 22; k < 49; k = k + 2)
        {
            gotoxy(k, 16);
            puts("＼");
            gotoxy(k + 2, 16);
            puts("／");
            k = k + 2;
        }
        gotoxy(48, 16);
        puts("☆");
        gotoxy(48, 15);
        puts("☆");
        gotoxy(48, 17);
        puts("☆");
        gotoxy(50, 16);
        puts("☆");
        gotoxy(52, 16);
        puts("☆");
        gotoxy(50, 15);
        puts("☆");
        gotoxy(50, 17);
        puts("☆");
        gotoxy(52, 17);
        puts("☆");
        gotoxy(52, 15);
        puts("☆");

        delay(t * 2);
        char_set();
        for (k = 22; k < 49; k = k + 2)
        {
            gotoxy(k, 16);
            puts("／");
            gotoxy(k + 2, 16);
            puts("＼");
            k = k + 2;
        }
        delay(t * 2);
    }

    eft_set();
}
void skill3_eft()
{
    playerhp_eft();
    eft_set();
}
void skill4_eft()
{
    playerdfup_eft();
    eft_set();
}
void skill5_eft()
{
    playermp_eft();
    eft_set();
}
void gunshot_eft()
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("-");
        delay(10);
        gotoxy(k, 16);
        puts(" ");
    }
    eft_set();
}
void gunshot_eft2()
{
    gotoxy(42, 16);
    puts("-");
    delay(50);
    char_set();
    gotoxy(46, 15);
    puts("-");
    delay(50);
    char_set();
    gotoxy(35, 17);
    puts("-");
    delay(50);
    char_set();
    gotoxy(33, 15);
    puts("-");
    delay(50);
    char_set();
    gotoxy(48, 17);
    puts("-");
    delay(50);
    char_set();
    gotoxy(37, 16);
    puts("-");
    delay(50);
    char_set();
    eft_set();
}
void boom_eft()
{
    int k;
    for (k = 48; k > 21; k=k-2)
    {
        gotoxy(k, 16);
        puts("㉿");
        delay(20);
        gotoxy(k, 16);
        puts(" ");
    }
    playerboom_eft();
}
void sword_eft()
{
    gotoxy(50, 15);
    puts("／");
    delay(50);
    char_set();
    gotoxy(48, 15);
    puts("＼");
    delay(50);
    char_set();
    gotoxy(48, 16);
    puts("──");
    delay(50);
    char_set();
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("／");
        delay(10);
        gotoxy(k, 16);
        puts(" ");
    }
    eft_set();
}
void roar_eft()
{
    gotoxy(48, 15);
    puts("＼");
    gotoxy(48, 16);
    puts("──");
    gotoxy(48, 17);
    puts("／");
    gotoxy(46, 16);
    puts("!");
    d1s();
    gotoxy(42, 15);
    puts("!");
    d1s();
    gotoxy(44, 17);
    puts("!");
    d1s();
    eft_set();
}
void powerslash_eft()
{
    move_eft();
    gotoxy(22, 15);
    puts("／");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("／");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("／");
    delay(100);
    gotoxy(18, 15);
    puts("＼");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("＼");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("＼");
    delay(100);
    move_set();
    gotoxy(22, 15);
    puts("／");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("／");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("／");
    delay(100);
    gotoxy(18, 15);
    puts("＼");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("＼");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("＼");
    delay(100);
    move_set();
    gotoxy(22, 15);
    puts("／");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("／");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("／");
    delay(100);
    gotoxy(18, 15);
    puts("＼");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("＼");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("＼");
    delay(100);
    move_set();
    back_eft();
    eft_set();
}
void sniper_eft()
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("──");
        delay(5);
        gotoxy(k, 16);
        puts(" ");
    }
    eft_set();
}
void focus_eft()
{
    gotoxy(48, 16);
    puts("↑");
    delay(100);
    char_set();
    gotoxy(48, 15);
    puts("↑");
    delay(100);
    char_set();
    gotoxy(52, 16);
    puts("↑");
    delay(100);
    char_set();
    gotoxy(52, 15);
    puts("↑");
    delay(100);
    char_set();
    gotoxy(48, 16);
    puts("↑");
    delay(100);
    char_set();
    gotoxy(48, 15);
    puts("↑");
    delay(100);
    char_set();
    gotoxy(52, 16);
    puts("↑");
    delay(100);
    char_set();
    gotoxy(52, 15);
    puts("↑");
    delay(100);
    eft_set();
}
void headshot_eft()
{
    int k;
    gotoxy(20, 15);
    puts("│");
    gotoxy(20, 17);
    puts("│");
    gotoxy(18, 16);
    puts("──");
    gotoxy(22, 16);
    puts("──");
    delay(500);
    char_set();
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("──");
        delay(5);
        gotoxy(k, 16);
        puts(" ");
    }
    eft_set();
}
void ice_eft()
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("◇");
        delay(20);
        gotoxy(k, 16);
        puts(" ");
    }
    playerfreeze_eft();
}
void blizzard_eft()
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 15);
        puts("*");
        gotoxy(k - 2, 15);
        puts("*");
        gotoxy(k - 4, 15);
        puts("*");
        gotoxy(k - 2, 16);
        puts("*");
        gotoxy(k - 4, 16);
        puts("*");
        gotoxy(k - 6, 16);
        puts("*");
        gotoxy(k - 4, 17);
        puts("*");
        gotoxy(k - 6, 17);
        puts("*");
        gotoxy(k - 8, 17);
        puts("*");
        delay(20);
        char_set();
    }
    playerfreeze_eft();
}
void thunder_eft()
{
    int k;
    for (k = 48; k > 21; k = k - 2)
    {
        gotoxy(k, 16);
        puts("／");
        delay(20);
        gotoxy(k - 2, 16);
        puts("＼");
        delay(20);
        k = k - 2;
    }
    char_set();
    playerthunder_eft();
    delay(100);
    char_set();
    delay(100);
    playerthunder_eft();
    delay(100);
    char_set();
    delay(100);
    playerthunder_eft();
    delay(100);
    eft_set();
}
void powerthunder_eft()
{
    int k;
    int t;
    for (t = 0; t < 10; t++)
    {
        for (k = 48; k > 21; k = k - 2)
        {
            gotoxy(k, 16);
            puts("／");
            gotoxy(k - 2, 16);
            puts("＼");
            k = k - 2;
        }
        gotoxy(20, 15);
        puts("│");
        gotoxy(22, 16);
        puts("──");
        gotoxy(20, 17);
        puts("│");
        gotoxy(18, 16);
        puts("──");
        delay(50);
        char_set();
        for (k = 48; k > 21; k = k - 2)
        {
            gotoxy(k, 16);
            puts("＼");
            gotoxy(k - 2, 16);
            puts("／");
            k = k - 2;
        }
        gotoxy(22, 15);
        puts("／");
        gotoxy(22, 17);
        puts("＼");
        gotoxy(18, 17);
        puts("／");
        gotoxy(18, 15);
        puts("＼");
        delay(50);
        char_set();
    }
    eft_set();
}
void fireshot_eft()
{
    int k;
    int t;
    for (k = 48; k > 21; k = k - 2)
    {
        gotoxy(k, 16);
        puts("§");
        delay(20);
    }
    char_set();
    for (t = 0; t < 4; t++)
    {
        for (k = 48; k > 21; k = k - 4)
        {
            gotoxy(k, 16);
            puts("§");
        }
        playerboom_eft();
        delay(50);
        char_set();
        for (k = 46; k > 21; k = k - 4)
        {
            gotoxy(k, 16);
            puts("§");
        }
        playerboom_eft();
        delay(50);
        char_set();
    }
    eft_set();
}
void warmup_eft()
{
    int k;
    for (k = 0; k < 3; k++)
    {
        gotoxy(50, 15);
        puts("♨");
        delay(200);
        char_set();
        gotoxy(48, 15);
        puts("♨");
        gotoxy(52, 15);
        puts("♨");
        delay(200);
        char_set();
    }
    eft_set();
}
void firepunch_eft()
{
    int k;
    move_eft();
    for (k = 0; k < 4; k++)
    {
        gotoxy(26, 16);
        puts("◎");
        delay(50);
        move_set();
        gotoxy(24, 16);
        puts("◎");
        delay(50);
        move_set();
        gotoxy(22, 16);
        puts("◎");
        delay(50);
        move_set();
        gotoxy(18, 17);
        puts("♨");
        gotoxy(20, 17);
        puts("♨");
        gotoxy(22, 17);
        puts("♨");
        delay(20);
        move_set();
        gotoxy(18, 16);
        puts("♨");
        gotoxy(22, 16);
        puts("♨");
        delay(20);
        move_set();
        gotoxy(18, 15);
        puts("♨");
        gotoxy(20, 15);
        puts("♨");
        gotoxy(22, 15);
        puts("♨");
        delay(50);
        move_set();
    }
    back_eft();
    eft_set();
}
void fireblast_eft()
{
    int k;
    for (k = 48; k > 21; k--)
    {
        if (k % 2 == 0)
        {
            gotoxy(k, 15);
            puts("◎");
            gotoxy(k - 2, 15);
            puts("◎");
            gotoxy(k - 4, 15);
            puts("◎");
            gotoxy(k, 16);
            puts("◎");
            gotoxy(k - 2, 16);
            puts("◎");
            gotoxy(k - 4, 16);
            puts("◎");
            gotoxy(k, 17);
            puts("◎");
            gotoxy(k - 2, 17);
            puts("◎");
            gotoxy(k - 4, 17);
            puts("◎");
            delay(20);
            char_set();
        }
        if (k % 2 == 1)
        {
            gotoxy(k, 15);
            puts("●");
            gotoxy(k - 2, 15);
            puts("●");
            gotoxy(k - 4, 15);
            puts("●");
            gotoxy(k, 16);
            puts("●");
            gotoxy(k - 2, 16);
            puts("●");
            gotoxy(k - 4, 16);
            puts("●");
            gotoxy(k, 17);
            puts("●");
            gotoxy(k - 2, 17);
            puts("●");
            gotoxy(k - 4, 17);
            puts("●");
            delay(20);
            char_set();
        }
    }
    eft_set();
}
void windbind_eft()
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 15);
        puts("~");
        gotoxy(k - 2, 15);
        puts("~");
        gotoxy(k - 4, 15);
        puts("~");
        gotoxy(k - 2, 16);
        puts("~");
        gotoxy(k - 4, 16);
        puts("~");
        gotoxy(k - 6, 16);
        puts("~");
        gotoxy(k - 4, 17);
        puts("~");
        gotoxy(k - 6, 17);
        puts("~");
        gotoxy(k - 8, 17);
        puts("~");
        delay(20);
        char_set();
    }
    eft_set();
}
void absorb_eft()
{
    int k;
    int t;
    for (t = 0; t < 4; t++)
    {
        for (k = 22; k < 49; k++)
        {
            gotoxy(k, 16);
            puts("＊");
            delay(10);
            gotoxy(k, 16);
            puts(" ");
        }
    }
    eft_set();
}
void windstorm_eft()
{
    int k;
    for (k = 0; k < 6; k++)
    {
        gotoxy(18, 15);
        puts("~");
        gotoxy(22, 16);
        puts("~");
        gotoxy(18, 17);
        puts("~");
        delay(50);
        char_set();
        gotoxy(20, 15);
        puts("~");
        gotoxy(20, 16);
        puts("~");
        gotoxy(20, 17);
        puts("~");
        delay(50);
        char_set();
        gotoxy(22, 15);
        puts("~");
        gotoxy(18, 16);
        puts("~");
        gotoxy(22, 17);
        puts("~");
        delay(50);
        char_set();
    }
    eft_set();
}
void darkbeam_eft()
{
    int k;
    for (k = 48; k > 21; k = k - 2)
    {
        gotoxy(k, 16);
        puts("●");
        delay(20);
    }
    gotoxy(22, 15);
    puts("●");
    gotoxy(22, 16);
    puts("●");
    gotoxy(22, 17);
    puts("●");
    delay(100);
    gotoxy(20, 15);
    puts("●");
    gotoxy(20, 16);
    puts("●");
    gotoxy(20, 17);
    puts("●");
    delay(100);
    gotoxy(18, 15);
    puts("●");
    gotoxy(18, 16);
    puts("●");
    gotoxy(18, 17);
    puts("●");
    delay(100);
    eft_set();
}
void silence_eft()
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("⊙");
        delay(10);
        gotoxy(k, 16);
        puts(" ");
    }
    delay(200);
    gotoxy(22, 15);
    puts("!");
    delay(500);
    eft_set();
}
void empower_eft()
{
    int k;
    for (k = 0; k < 2; k++)
    {
        gotoxy(18, 15);
        puts("↓");
        delay(100);
        char_set();
        gotoxy(18, 16);
        puts("↓");
        delay(100);
        char_set();
        gotoxy(22, 15);
        puts("↓");
        delay(100);
        char_set();
        gotoxy(22, 16);
        puts("↓");
        delay(100);
        char_set();
    }
    eft_set();
}
void swiftsword_eft()
{
    int k;
    int t;
    for (t = 0; t < 2; t++)
    {
        gotoxy(48, 15);
        puts("／");
        delay(20);
        gotoxy(46, 16);
        puts("／");
        delay(20);
        gotoxy(44, 17);
        puts("／");
        delay(20);
        char_set();
        delay(20);
        for (k = 42; k > 22; k = k - 2)
        {
            gotoxy(k, 15);
            puts("／");
            gotoxy(k - 2, 16);
            puts("／");
            gotoxy(k - 4, 17);
            puts("／");
            delay(10);
            char_set();
        }
        gotoxy(44, 15);
        puts("＼");
        delay(20);
        gotoxy(46, 16);
        puts("＼");
        delay(20);
        gotoxy(48, 17);
        puts("＼");
        delay(20);
        char_set();
        delay(20);
        for (k = 44; k > 18; k = k - 2)
        {
            gotoxy(k, 15);
            puts("＼");
            gotoxy(k + 2, 16);
            puts("＼");
            gotoxy(k + 4, 17);
            puts("＼");
            delay(10);
            char_set();
        }
    }
    eft_set();
}
void sworddance_eft()
{
    int k;
    for (k = 0; k < 2; k++)
    {
        gotoxy(48, 15);
        puts("│");
        gotoxy(48, 16);
        puts("┼");
        delay(200);
        char_set();
        gotoxy(52, 15);
        puts("│");
        gotoxy(52, 16);
        puts("┼");
        delay(200);
        char_set();
    }
    eft_set();
}
void armorbash_eft()
{
    int k;
    move_eft();
    for (k = 0; k < 3; k++)
    {
        gotoxy(18, 15);
        puts("＼");
        delay(100);
        gotoxy(20, 16);
        puts("＼");
        delay(100);
        gotoxy(22, 17);
        puts("＼");
        delay(100);
        move_set();
        delay(100);
    }
    back_eft();
    eft_set();
}
void bleedslash_eft()
{
    move_eft();
    gotoxy(18, 16);
    puts("──");
    delay(20);
    gotoxy(20, 16);
    puts("──");
    delay(20);
    gotoxy(22, 16);
    puts("──");
    delay(20);
    move_set();
    back_eft();
    eft_set();
}
void triplespear_eft()
{
    int k;
    move_eft();
    move_set();
    delay(100);
    for (k = 0; k < 3; k++)
    {
        if (k != 0)
        {
            gotoxy(24, 16);
            puts("──");
            gotoxy(26, 16);
            puts("──");
            gotoxy(30, 16);
            puts("──");
            delay(200);
            move_set();
        }
        gotoxy(22, 16);
        puts("──");
        gotoxy(24, 16);
        puts("──");
        gotoxy(26, 16);
        puts("──");
        if (k == 2)
        {
            gotoxy(20, 16);
            puts(" ");
            gotoxy(20, 15);
            puts("옷");
        }
        delay(100);
        move_set();
    }
    gotoxy(24, 16);
    puts("──");
    gotoxy(26, 16);
    puts("──");
    gotoxy(30, 16);
    puts("──");
    delay(200);
    move_set();
    back_eft();
    eft_set();
}
void challenge_eft()
{
    move_eft();
    gotoxy(26, 15);
    puts("!");
    delay(500);
    move_set();
    back_eft();
    eft_set();
}
void molwang_eft()
{
    int k;
    for (k = 22; k < 49; k = k + 2)
    {
        gotoxy(k, 16);
        puts("〓");
        delay(10);
    }
    for (k = 22; k < 49; k = k + 2)
    {
        gotoxy(k, 16);
        puts(" ");
        delay(10);
    }
    comhp_eft();
    eft_set();
}
void spearsweep_eft()
{
    move_eft();
    delay(30);
    gotoxy(24, 16);
    puts("──");
    gotoxy(26, 16);
    puts("──");
    delay(30);
    move_set();
    gotoxy(26, 17);
    puts("／");
    delay(30);
    move_set();
    gotoxy(28, 17);
    puts("│");
    delay(30);
    move_set();
    gotoxy(30, 17);
    puts("＼");
    delay(30);
    move_set();
    gotoxy(30, 15);
    puts("──");
    delay(20);
    move_set();
    gotoxy(30, 15);
    puts("／");
    delay(20);
    move_set();
    gotoxy(28, 15);
    puts("│");
    delay(20);
    move_set();
    gotoxy(26, 15);
    puts("＼");
    delay(20);
    move_set();
    gotoxy(24, 16);
    puts("──");
    gotoxy(26, 16);
    puts("──");
    delay(20);
    move_set();
    back_eft();
    eft_set();
}
void time_up()
{
    delay(1000);
    time_s++;
}
void time_set()
{
    if (time_s >= 60)
    {
        time_m++;
        time_s = 0;
    }
    if (time_m >= 60)
    {
        time_h++;
        time_m = 0;
    }
}

void statchoose_message()
{
    printf("┌──────────────────────────────────────────────────────────────────┐\n");
    printf("│               향상 시킬 능력치를 선택 하세요.                    │    \n");
    printf("│   1.체력+50   2.마나+50   3.공격력+10   4.방어력+5   5.취소      │      \n");
    printf("└──────────────────────────────────────────────────────────────────┘\n");
} // 스탯 강화 화면
int statchoose(int a)
{
    if (a == 1) {
        player_maxhp = player_maxhp + 50;
    }
    if (a == 2) {
        player_maxmp = player_maxmp + 50;
    }
    if (a == 3) {
        player_att = player_att + 10;
    }
    if (a == 4) {
        if (player_defmain >= 100)
        {
            player_statpoint++;
            defover_state = 1;
        }
        if (player_defmain + 5 <= 100)
        {
            player_defmain = player_defmain + 5;
        }
    }
    return 0;
} // 스탯 증가
void playerstat_message()
{
    printf("┌────────────────────────────┐\n");
    printf("│       <<< 스탯 >>>              \n");
    printf("│ 직업   : 마법사               \n");
    printf("│ 레벨   : %d                     \n", player_level);
    printf("│ 체력   : %d / %d               \n", player_hp, player_maxhp);
    printf("│ 마나   : %d / %d             \n", player_mp, player_maxmp);
    printf("│ 공격력 : %d                  \n", player_att);
    printf("│ 방어력 : %d                 \n", player_defmain);
    printf("│ 경험치 : %d / %d (%.2f %%) \n", player_exp, player_maxexp, (float)player_exp / (float)player_maxexp * 100);
    printf("│ 보유한 골드 : %d           \n", player_gold);
    printf("└────────────────────────────┘\n");
    int k;
    for (k = 1; k < 10; k++)
    {
        gotoxy(29, k);
        puts("│");
    }
    gotoxy(0, 11);
   
} // 스탯 화면 스탯 정보
void comstat_message()
{
    printf("  <<<적>>>\n");
}
void menu_choose()
{
    printf("┌────────────────────────────────────────────────────────────────────┐   \n");
    printf("│                         무엇을 하시겠습니까?                       │ \n");
    printf("│  1.전투  2.스탯  3.스킬  4.무기  5.치트  6.설정  7.도움말  8.정보  │  \n");
    printf("└────────────────────────────────────────────────────────────────────┘    \n");
    if (stage_level >= 11)
    {
        printf("   축하드립니다! 모든 스테이지를 클리어 하였습니다.\n");
        printf("     엔딩 코드를 확인 하려면 숫자 0을 누르세요.\n");
    }
    if (player_statpoint > 0)
    {
        printf("\n      * 사용하지 않은 스탯 포인트가 남아 있습니다.\n");
    }
    if (player_skillpoint > 0)
    {
        printf("\n      * 사용하지 않은 스킬 포인트가 남아 있습니다.\n");
    }
    if (player_gold >= 10000 && item_code != 3)
    {
        printf("\n      * 골드가 많이 모였습니다. 무기를 착용 해보세요.\n");
    }
} // 메인 메뉴 화면
int skill_1()
{
    //파이어볼
    int d;
    d = (player_level * 10) + (player_att / 2) + (player_skill1 * 20);
    return d;
}
int skill_2()
{
    //썬더볼트
    int d;
    d = (player_level * 9) + (player_att / 2) + (player_skill2 * 18);
    return d;
}
int skill_3()
{
    //큐어
    int d;
    d = (player_level * 10) + (player_skill3 * 15) + (player_maxhp / 20) + (player_maxmp / 20);
    return d;
}
int skill_4()
{
    //가드 업
    int d;
    d = (player_skill4 * 2) + (player_maxhp / 100);
    return d;
}
int skill_5()
{
    //메디테이션
    int d;
    d = 45 + (player_skill5 * 5) + (player_maxhp / 100);
    return d;
}
void skillchoose_message() // 스킬 선택 메세지
{
    printf("┌──────────────────────────────────────────────────────────────────┐   \n");
    printf("│                <<< 강화할 스킬을 선택하세요 >>>                  │  \n");
    printf("│ 1. 파이어 볼 (%d레벨/5)                                           │\n", player_skill1);
    printf("│   - 적을 공격하여 %d만큼의 피해를 입힘(+20)                        \n", skill_1());
    printf("│                                                                  │  \n");
    printf("│ 2. 썬더 볼트 (%d레벨/5)                                           │   \n", player_skill2);
    printf("│   - 적에게 %d만큼의 피해를 입히고, 방어력을 %d 감소시킴(+18,+2)     \n", skill_2(), player_skill2 * 2);
    printf("│                                                                  │  \n");
    printf("│ 3. 큐어 (%d레벨/5)                                                │   \n", player_skill3);
    printf("│   - 자신의 체력을 %d만큼 회복함(+15)                               \n", skill_3());
    printf("│                                                                  │ \n");
    printf("│ 4. 가드 업 (%d레벨/5)                                             │  \n", player_skill4);
    printf("│   - 전투동안 자신의 방어력을 %d만큼 증가 시킴(+2)                   \n", skill_4());
    printf("│                                                                  │  \n");
    printf("│ 5. 메디테이션 (%d레벨/5)                                          │  \n", player_skill5);
    printf("│   - 현재 체력의 40%%를 소모하여 최대 마나의 %d%% 마나를 회복(+5%%)     \n", skill_5());
    printf("│                                                                  │  \n");
    printf("│ 6. 메뉴로 돌아가기                                               │   \n");
    printf("└──────────────────────────────────────────────────────────────────┘    \n");
    gotoxy(67, 3);
    puts("│");
    gotoxy(67, 6);
    puts("│");
    gotoxy(67, 9);
    puts("│");
    gotoxy(67, 12);
    puts("│");
    gotoxy(67, 15);
    puts("│");
    gotoxy(0, 19);
}
void stat_restore() // 플레이어 스탯 초기화
{
    player_hp = player_maxhp;
    player_mp = player_maxmp;
    player_defup = 0;
    player_def = player_defmain;
    com_hp = com_maxhp;
    player_dotecount = 0;
    player_stun = 0;
    turn = 0;
}
void stat_over() // 스탯 오버시 재설정
{
    if (player_hp < 0) {
        player_hp = 0;
    }
    if (player_hp > player_maxhp) {
        player_hp = player_maxhp;
    }
    if (player_mp < 0) {
        player_mp = 0;
    }
    if (player_mp > player_maxmp) {
        player_mp = player_maxmp;
    }
    if (player_def < 0) {
        player_def = 0;
    }
    if (player_defup < 0) {
        player_defup = 0;
    }
    if (player_defmain < 0) {
        player_defmain = 0;
    }
    if (com_hp < 0) {
        com_hp = 0;
    }
    if (com_hp > com_maxhp) {
        com_hp = com_maxhp;
    }
    if (com_def < 0) {
        com_def = 0;
    }
    if (player_def + player_defup > 100)
    {
        for (; player_def + player_defup > 100;)
        {
            player_defup--;
        }
    }
    if (player_defmain > 100)
    {
        for (; player_defmain > 100;)
        {
            player_defmain--;
        }
    }
    if (com_def > 100)
    {
        for (; com_def > 100;)
        {
            com_def--;
        }
    }
}
int stage_name(int a) // 스테이지 이름 출력
{
    if (a == 1) {
        printf("     <<< Stage %d : %s >>>\n", a, stage01);
    }
    if (a == 2) {
        printf("     <<< Stage %d : %s >>>\n", a, stage02);
    }
    if (a == 3) {
        printf("     <<< Stage %d : %s >>>\n", a, stage03);
    }
    if (a == 4) {
        printf("     <<< Stage %d : %s >>>\n", a, stage04);
    }
    if (a == 5) {
        printf("     <<< Stage %d : %s >>>\n", a, stage05);
    }
    if (a == 6) {
        printf("     <<< Stage %d : %s >>>\n", a, stage06);
    }
    if (a == 7) {
        printf("     <<< Stage %d : %s >>>\n", a, stage07);
    }
    if (a == 8) {
        printf("       <<< Stage %d : %s >>>\n", a, stage08);
    }
    if (a == 9) {
        printf("       <<< Stage %d : %s >>>\n", a, stage09);
    }
    if (a == 10) {
        printf("       <<< Stage %d : %s >>>\n", a, stage10);
    }
    return 0;
}
void fight_stat() // 전투시 스탯 화면
{
    printf("┌──────<플레이어>────────────────────────────────────<적>──────────────────┐\n");
    printf("│   체력   : %d / %d                          체력 : %d / %d          \n", player_hp, player_maxhp, com_hp, com_maxhp);
    printf("│   마나   : %d / %d                                                  \n", player_mp, player_maxmp);
    printf("│   공격력 : %d                                 공격력 : %d           \n", player_att, com_att);
    printf("│   방어력 : %d                                  방어력 : %d          \n", player_def + player_defup, com_def);
    gotoxy(75, 2);
    puts("│");
    gotoxy(75, 3);
    puts("│");
    gotoxy(75, 4);
    puts("│");
    gotoxy(75, 5);
    puts("│");
}
void fight_skill()
{
    printf("├────────────────< 스킬을 사용하려면 숫자 버튼을 누르세요 >────────────────┤\n");
    printf("│     1.파이어 볼 (20 마나) : %d 의 피해를 입힘                           \n", skill_1());
    printf("│     2.썬더 볼트 (25 마나) : %d 의 피해를 입히고, 방어력을 %d 감소시킴    \n", skill_2(), player_skill2 * 2);
    printf("│     3.큐어      (30 마나) : 자신의 체력을 %d 만큼 회복함                 \n", skill_3());
    printf("│     4.가드 업   (20 마나) : 자신의 방어력을 %d 만큼 증가시킴             \n", skill_4());
    printf("│     5.메디테이션 (0 마나) : 체력의 40%%를 소모하여 %d%%의 마나 회복     \n", skill_5());
    printf("│     0.기본 공격  (0 마나) : %d 의 피해를 입히고 %d의 마나 회복          \n", player_att, player_att + (player_maxmp / 20));
    printf("└──────────────────────────────────────────────────────────────────────────┘\n");
    gotoxy(75, 7);
    puts("│");
    gotoxy(75, 8);
    puts("│");
    gotoxy(75, 9);
    puts("│");
    gotoxy(75, 10);
    puts("│");
    gotoxy(75, 11);
    puts("│");
    gotoxy(75, 12);
    puts("│");
}
int com_demage(int a)
{
    if (a > com_def) {
        printf("적이 %d 만큼의 피해를 받았습니다. \n", a - com_def);
        com_hp = com_hp - (a)+com_def;
    }
    if (a <= com_def) {
        printf("적이 1 만큼의 피해를 받았습니다.\n");
        com_hp = com_hp - 1;
    }

    return a;
}
int player_demage(int a)
{
    if (a > (player_def + player_defup)) {
        printf("%d 만큼의 피해를 받았습니다. \n", a - (player_def + player_defup));
        player_hp = player_hp - (a)+player_def + player_defup;
    }
    if (a <= (player_def + player_defup)) {
        printf("1 만큼의 피해를 받았습니다.\n");
        player_hp = player_hp - 1;
    }
    return a;
}
int player_hpdown(int a)
{
    printf("체력이 %d 만큼 감소합니다. \n", a);
    player_hp = player_hp - a;
    return a;
}
int com_defup(int a)
{
    printf("적의 방어력이 %d 만큼 올랐습니다. \n", a);
    com_def = com_def + a;
    return a;
}
int com_defdown(int a)
{
    printf("적의 방어력이 %d 만큼 감소 했습니다. \n", a);
    com_def = com_def - a;
    return a;
}
int com_attup(int a)
{
    printf("적의 공격력이 %d 만큼 증가 했습니다. \n", a);
    com_att = com_att + a;
    return a;
}
int player_defdown(int a)
{
    printf("방어력이 %d 만큼 감소합니다.\n", a);
    if (player_defup == 0) {
        player_def = player_def - a;
    }
    else if (player_defup < a && player_defup>0)
    {
        player_defup = player_defup - a;
        player_def = player_def + player_defup;
        player_defup = 0;
    }
    else if (player_defup >= a) {
        player_defup = player_defup - a;
    }
    else {
    }
    return a;
}
int player_hpup(int a)
{
    printf("체력이 %d 만큼 회복 됩니다.\n", a);
    player_hp = player_hp + a;
    return a;
}
int player_mplose(int a)
{
    printf("마나가 %d 만큼 감소합니다.\n", a);
    player_mp = player_mp - a;
    return a;
}
int com_hpup(int a)
{
    if (a >= 0) {
        printf("적의 체력이 %d 만큼 회복 됩니다.\n", a);
        com_hp = com_hp + a;
    }
    if (a < 0) {
        printf("적의 체력이 1 만큼 회복 됩니다.\n");
        com_hp = com_hp + 1;
    }
    return a;
}
int player_mpup(int a)
{
    printf("마나가 %d 만큼 회복 됩니다.\n", a);
    player_mp = player_mp + a;
    return a;
}
int player_mppup(int a)
{
    printf("마나가 %d%% 만큼 회복 됩니다.\n", a);
    player_mp = player_mp + (player_maxmp * (a) / 100);
    return a;
}
int player_mpdown(int a)
{
    player_mp = player_mp - a;
    return a;
}
void nomp()
{
    printf("마나가 부족합니다.\n");
}
char player_skill(char a)
{
    if (a == 0x30) {
        printf("<0. 기본 공격>을 사용 했습니다.\n");
        d1s();
        skill0_eft();
        d1s();
        com_demage(player_att);
        d1s();
        player_mpup(player_att + (player_maxmp / 20));
        d1s();
        turn++;
    }
    if (a == 0x31 && player_mp < 20) {
        nomp();
        d1s();
    }
    if (a == 0x31 && player_mp >= 20) {
        printf("<1. 파이어 볼>을 사용 했습니다.\n");
        d1s();
        skill1_eft();
        d1s();
        if (goto_stage == 6)
        {
            printf("적은 화염 속성에 면역입니다.\n");
            d1s();
            printf("피해를 받지 않습니다.\n");
        }
        if (goto_stage != 6)
        {
            com_demage(skill_1());
        }
        d1s();
        player_mpdown(20);
        turn++;
    }
    if (a == 0x32 && player_mp < 25) {
        nomp();
        d1s();
    }
    if (a == 0x32 && player_mp >= 25) {
        printf("<2. 썬더 볼트>를 사용 했습니다.\n");
        d1s();
        skill2_eft();
        d1s();
        if (goto_stage == 5)
        {
            printf("적은 번개 속성에 면역입니다.\n");
            d1s();
            printf("피해를 받지 않습니다.\n");
        }
        if (goto_stage != 5)
        {
            com_demage(skill_2());
            d1s();
            com_defdown(player_skill2 * 2);
        }

        d1s();
        player_mpdown(25);
        turn++;
    }
    if (a == 0x33 && player_mp < 30) {
        nomp();
        d1s();
    }
    if (a == 0x33 && player_mp >= 30) {
        printf("<3. 큐어>를 사용 했습니다.\n");
        d1s();
        skill3_eft();
        d1s();
        player_hpup(skill_3());
        d1s();
        player_mpdown(30);
        turn++;
    }
    if (a == 0x34 && player_mp < 20) {
        nomp();
        d1s();
    }
    if (a == 0x34 && player_mp >= 20) {
        printf("<4. 가드 업>을 사용 했습니다.\n");
        d1s();
        skill4_eft();
        d1s();
        printf("방어력이 %d 만큼 증가 합니다\n", skill_4());
        player_defup = player_defup + skill_4();
        d1s();
        player_mpdown(20);
        turn++;
    }
    if (a == 0x35) {
        printf("<5. 메디테이션>을 사용 했습니다.\n");
        d1s();
        skill5_eft();
        d1s();
        player_hpdown(player_hp * 40 / 100);
        d1s();
        player_mppup(skill_5());
        d1s();
        turn++;
    }
    return a;
}
int level_up(int a)
{
    if (a >= player_maxexp)
    {
        gotoxy(20, 16);
        printf("    축하합니다! 레벨업을 하였습니다!\n");
        gotoxy(20, 17);
        printf("스탯 포인트 3, 스킬 포인트 1을 얻었습니다.\n");
        player_statpoint = player_statpoint + 3;
        player_skillpoint = player_skillpoint + 1;
        player_exp = player_exp - player_maxexp;
        player_maxexp = player_maxexp + 100;
        player_level++;
    }
    if (a < player_maxexp)
    {
        return a;
    }
}
void player_stunon()
{
    printf("아무것도 할 수 없습니다.\n");
    player_stun = 1;
    turn++;
}
void stage01_skill()
{
    int r1;
    randomize();
    r1 = random(40) + 11;
    if (com_skill == 0) {
        printf("적이 <조준 사격>을 사용 했습니다.\n");
        d1s();
        gunshot_eft();
        gunshot_eft();
        gunshot_eft();
        d1s();
        player_demage(30);
        d1s();
    }
    if (com_skill == 1) {
        printf("적이 <총기 난사>를 사용 했습니다.\n");
        d1s();
        gunshot_eft2();
        gunshot_eft2();
        gunshot_eft2();
        gunshot_eft2();
        gunshot_eft2();
        d1s();
        player_demage(r1);
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <수류탄 투척>을 사용 했습니다.\n");
        d1s();
        boom_eft();
        d1s();
        player_demage(35);
        d1s();
        player_defdown(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <응급 치료>를 사용 했습니다.\n");
        d1s();
        comhp_eft();
        d1s();
        com_hpup(30);
        d1s();
    }
}
void stage02_skill()
{
    if (com_skill == 0) {
        printf("적이 <검 휘두르기>를 사용 했습니다.\n");
        d1s();
        sword_eft();
        d1s();
        player_demage(com_att + 15);
        d1s();
    }
    if (com_skill == 1) {
        printf("적이 <방어 태세>를 사용 했습니다.\n");
        d1s();
        comdfup_eft();
        d1s();
        com_defup(5);
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <전사의 함성>을 사용 했습니다.\n");
        d1s();
        roar_eft();
        d1s();
        com_attup(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <강력한 일격>을 사용 했습니다.\n");
        d1s();
        powerslash_eft();
        d1s();
        player_demage(com_att + 20);
        d1s();
    }
}
void stage03_skill()
{
    if (com_skill == 0) {
        printf("적이 <저격>을 사용 했습니다.\n");
        d1s();
        sniper_eft();
        d1s();
        player_demage(com_att + 30);
        d1s();
    }
    if (com_skill == 1) {
        printf("적이 <정신집중>을 사용 했습니다.\n");
        d1s();
        focus_eft();
        d1s();
        com_attup(7);
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <헤드샷>을 사용 했습니다.\n");
        d1s();
        headshot_eft();
        d1s();
        printf("방어력을 무시하여 피해를 입힙니다.\n");
        d1s();
        player_demage(com_att + 30 + player_defup + player_def);
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <응급 치료>를 사용 했습니다.\n");
        d1s();
        comhp_eft();
        d1s();
        com_hpup(45);
        d1s();
    }
}
void stage04_skill()
{
    if (com_skill == 0) {
        printf("적이 <아이스 볼>을 사용 했습니다.\n");
        d1s();
        ice_eft();
        d1s();
        player_demage(com_att + 20);
        d1s();
    }
    if (com_skill == 1) {
        printf("적이 <얼음 장막>을 사용 했습니다.\n");
        d1s();
        comdfup_eft();
        d1s();
        com_defup(8);
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <얼음 폭풍>을 사용 했습니다.\n");
        d1s();
        blizzard_eft();
        d1s();
        player_demage(com_att + 20);
        d1s();
        player_defdown(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <마력 결빙>을 사용 했습니다.\n");
        d1s();
        playerfreeze_eft();
        delay(200);
        playerfreeze_eft();
        delay(200);
        playerfreeze_eft();
        d1s();
        player_mplose(com_att + 20);
        d1s();
    }
}
void stage05_skill()
{
    if (com_skill == 0) {
        printf("적이 <번개 강타>를 사용 했습니다.\n");
        d1s();
        thunder_eft();
        d1s();
        player_demage(com_att + 10);
        d1s();
    }
    if (com_skill == 1) {
        printf("적이 <번개 장막>을 사용 했습니다.\n");
        d1s();
        comdfup_eft();
        d1s();
        com_defup(5);
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <전기 충전>을 사용 했습니다.\n");
        d1s();
        focus_eft();
        d1s();
        com_attup(5);
        d1s();
        com_hpup(25);
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <심판의 번개>를 사용 했습니다.\n");
        d1s();
        powerthunder_eft();
        d1s();
        printf("방어력을 무시하여 피해를 입힙니다\n");
        d1s();
        player_demage(com_att + 10 + player_def + player_defup);
        d1s();
    }
}
void stage06_skill()
{
    if (com_skill == 0) {
        printf("적이 <열기 분사>를 사용 했습니다.\n");
        d1s();
        fireshot_eft();
        d1s();
        player_mplose(com_att + 20);
        d1s();
    }
    if (com_skill == 1) {
        printf("적이 <발열>을 사용 했습니다.\n");
        d1s();
        warmup_eft();
        d1s();
        com_hpup(25);
        d1s();
        com_attup(10);
        d1s();
        com_defup(5);
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <화염 주먹>을 사용 했습니다.\n");
        d1s();
        firepunch_eft();
        d1s();
        player_demage(com_att + 15);
        d1s();
        player_defdown(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <폭류 화염>을 사용 했습니다.\n");
        d1s();
        fireblast_eft();
        d1s();
        player_demage(com_att + 20);
        d1s();
    }
}
void stage07_skill()
{
    if (com_skill == 0) {
        printf("적이 <바람 감옥>을 사용 했습니다.\n");
        d1s();
        windstorm_eft();
        d1s();
        player_demage(com_att / 2);
        d1s();
        printf("아무것도 할 수 없습니다.\n");
        d1s();
        player_stun = 1;
        turn++;
    }
    if (com_skill == 1) {
        printf("적이 <기운 흡수>를 사용 했습니다.\n");
        d1s();
        absorb_eft();
        d1s();
        player_demage(com_att);
        d1s();
        com_hpup(com_att / 2);
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <바람의 가호>를 사용 했습니다.\n");
        d1s();
        focus_eft();
        d1s();
        com_attup(10);
        d1s();
        com_defup(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <대폭풍>을 사용 했습니다.\n");
        d1s();
        windbind_eft();
        d1s();
        player_demage((com_att)+(com_hp / 100));
        d1s();
    }
}
void stage08_skill()
{
    if (com_skill == 0) {
        printf("적이 <암흑 파동>을 사용 했습니다.\n");
        d1s();
        darkbeam_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_defdown(10);
        d1s();
    }
    if (com_skill == 1) {
        printf("적이 <침묵>을 사용 했습니다.\n");
        d1s();
        silence_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_stunon();
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <무력화>를 사용 했습니다.\n");
        d1s();
        empower_eft();
        d1s();
        player_mplose(player_mp / 2);
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <흡수>를 사용 했습니다.\n");
        d1s();
        absorb_eft();
        d1s();
        player_demage(com_att);
        d1s();
        com_hpup(com_att - (player_def + player_defup));
        d1s();
    }
}
void stage09_skill()
{
    if (com_skill == 0) {
        printf("적이 <날렵한 검기>를 사용 했습니다.\n");
        d1s();
        swiftsword_eft();
        d1s();
        player_demage(com_att);
        d1s();
    }
    if (com_skill == 1) {
        printf("적이 <칼의 춤>을 사용 했습니다.\n");
        d1s();
        sworddance_eft();
        d1s();
        com_attup((com_att / 15));
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <갑옷 베기>를 사용 했습니다.\n");
        d1s();
        armorbash_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_defdown(15);
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <출혈>을 사용 했습니다.\n");
        d1s();
        bleedslash_eft();
        d1s();
        player_demage(com_att);
        d1s();
        printf("매 턴마다 지속적으로 피해를 입습니다. (총 3회)\n");
        player_dotecount = 3;
        d1s();
    }
}
void stage10_skill()
{
    int r;
    randomize();
    if (com_skill == 0) {
        r = random(100);
        if (r < 15)
        {
            printf(" 적이 <삼조격>을 사용 했습니다.\n");
            d1s();
            triplespear_eft();
            d1s();
            printf("치명타가 터졌습니다.\n");
            d1s();
            player_demage(com_att * 6);
            d1s();
        }
        else
        {
            printf("적이 <삼조격>을 사용 했습니다.\n");
            d1s();
            triplespear_eft();
            d1s();
            player_demage(com_att * 3);
            d1s();
        }
    }
    if (com_skill == 1) {
        printf("적이 <도전>을 사용 했습니다.\n");
        d1s();
        challenge_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_defdown(15);
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <초승달 휩쓸기>를 사용 했습니다.\n");
        d1s();
        spearsweep_eft();
        d1s();
        player_demage(player_hp * 15 / 100);
        d1s();
        com_defup(10);
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <몰락한 왕의 검>을 사용 했습니다.\n");
        d1s();
        molwang_eft();
        d1s();
        player_demage(player_maxhp * 10 / 100);
        d1s();
        com_hpup((player_maxhp * 10 / 100) - player_defup - player_def);
        d1s();
    }
}
void all_set()
{
    stat_over();
    system("cls");
    stage_name(goto_stage);
    fight_stat();
    fight_skill();
    char_eft();
    txt_pos();
}
void txt_set()
{
    system("cls");
    stage_name(goto_stage);
    fight_stat();
    fight_skill();
    char_eft();
    txt_pos();
}
int player_doteon(int a)
{
    printf("지속적으로 피해를 입습니다.\n");
    d1s();
    dote_eft();
    d1s();
    player_demage(a);
    d1s();
    all_set();
    return a;
}
void main(void) // 메인 함수 ///////////////////////////////////////////////////////////////////////////////////////////////////////
{
    setcursortype(NOCURSOR);
    
    window();
    gotoxy(24, 2);
    printf("         마법사의 모험\n");
    gotoxy(24, 3);
    printf("           Ver 1.0\n");
    gotoxy(50, 20);
    printf("Made by cd991478 / 백성진\n");
    gotoxy(22, 14);
    printf("   시작하려면 아무 키나 누르세요.\n");
    gotoxy(50, 18);
    printf("  cd991478@naver.com\n");
    _getch();
    item_att = &player_att;
    item_mp = &player_maxmp;
    for (;;) // 반복 구문
    {
        randomize();
        menu_fight = 0;
        menu_stat = 0;
        menu_skill = 0;
        menu_item = 0;
        system("cls");
        menu_choose(); // 메인 메뉴 호출
        choose = _getch(); // 메뉴 선택 버튼
        if (choose == 0x31) { // 메뉴에서 1. 전투 입력시
            total = win + lose;
            menu_fight = 1;
            stat_restore();
            stat_over();
            system("cls");
            printf("┌────────────────────────────────────────────────────┐      \n");
            printf("│   <<<스테이지 번호를 입력하고 엔터를 누르세요>>>   │   \n");
            printf("│            1-10 스테이지 까지 있으며,              │    \n");
            printf("│ %d 스테이지 클리어시 그 다음 스테이지 플레이 가능.      \n", stage_level);
            printf("│      (메인 메뉴로 돌아가려면 숫자 0을 입력)        │      \n");
            printf("└────────────────────────────────────────────────────┘   \n");
            if (win >= 1 || lose >= 1)
            {
                printf("      %d승 %d패   승률 : %.2f %%  점수 : %d\n", win, lose, (float)win * 100 / (float)total, rating);
            }
            if (total < 3)
            {
                printf("              현재 등급 : Unranked\n");
                printf("       최소 3판을 할경우 등급을 배정 받습니다.\n");
            }
            if (total >= 3)
            {
                if (rating < 1000) {
                    strcpy(rank, "Bronze ▼");
                }
                if (rating >= 1000 && rating < 1050) {
                    strcpy(rank, "Silver ♤");
                }
                if (rating >= 1050 && rating < 1100) {
                    strcpy(rank, "Gold ♧");
                }
                if (rating >= 1100 && rating < 1200) {
                    strcpy(rank, "Platinum ◇");
                }
                if (rating >= 1200 && rating < 1250) {
                    strcpy(rank, "Diamond ◈");
                }
                if (rating >= 1250) {
                    strcpy(rank, "Master ☆");
                }
                printf("                  현재 등급 : %s\n", rank);
            }
            gotoxy(53, 3);
            puts("│");
            gotoxy(0, 10);
            scanf_s("%d", &goto_stage);
            if (stage_level < goto_stage)
            {
                printf("해당 스테이지는 아직 플레이 할 수 없습니다.\n");
                printf("     계속 하려면 아무 키나 누르세요.\n");
                _getch();
                continue;
            }
            if (goto_stage == 1) {
                com_maxhp = 100;
                com_att = 20;
                com_def = 1;
            }
            else if (goto_stage == 2) {
                com_maxhp = 200;
                com_att = 30;
                com_def = 3;
            }
            else if (goto_stage == 3) {
                com_maxhp = 300;
                com_att = 40;
                com_def = 6;
            }
            else if (goto_stage == 4) {
                com_maxhp = 500;
                com_att = 50;
                com_def = 10;
            }
            else if (goto_stage == 5) {
                com_maxhp = 700;
                com_att = 60;
                com_def = 15;
            }
            else if (goto_stage == 6) {
                com_maxhp = 1000;
                com_att = 70;
                com_def = 20;
            }
            else if (goto_stage == 7) {
                com_maxhp = 1500;
                com_att = 80;
                com_def = 25;
            }
            else if (goto_stage == 8) {
                com_maxhp = 2000;
                com_att = 90;
                com_def = 30;
            }
            else if (goto_stage == 9) {
                com_maxhp = 3000;
                com_att = 100;
                com_def = 35;
            }
            else if (goto_stage == 10) {
                com_maxhp = 5000;
                com_att = 100;
                com_def = 40;
            }
            else if (goto_stage == 0) {
                continue;
            }
            else {
                system("cls");
                printf("    잘못 입력 하였습니다\n");
                d1s();
                printf("계속 하려면 아무 키나 누르세요.\n");
                _getch();
                continue;
            }
            turn = 0;
            stat_restore();
            for (;;) // 전투 반복
            {
                all_set();
                if (player_dotecount > 0) // 도트 데미지
                {
                    player_doteon(com_att);
                }
                if (turn % 2 == 0 && player_hp > 0 && player_stun == 0) {
                    for (;;) {
                        printf("      당신의 턴입니다!\n");
                        order = _getch();
                        player_skill(order);
                        if (turn % 2 == 1) {
                            break;
                        }
                    }
                }

                if (turn % 2 == 1 && com_hp > 0) {
                    all_set();
                    player_stun = 0;
                    printf("       적의 턴입니다.\n");
                    d1s();
                    com_skill = random(4);
                    if (goto_stage == 1) {
                        stage01_skill();
                    }
                    if (goto_stage == 2) {
                        stage02_skill();
                    }
                    if (goto_stage == 3) {
                        stage03_skill();
                    }
                    if (goto_stage == 4) {
                        stage04_skill();
                    }
                    if (goto_stage == 5) {
                        stage05_skill();
                    }
                    if (goto_stage == 6) {
                        stage06_skill();
                    }
                    if (goto_stage == 7) {
                        stage07_skill();
                    }
                    if (goto_stage == 8) {
                        stage08_skill();
                    }
                    if (goto_stage == 9) {
                        stage09_skill();
                    }
                    if (goto_stage == 10) {
                        stage10_skill();
                    }
                    turn++;
                }
                if (player_hp <= 0)
                {
                    all_set();
                    printf("체력이 0이 되어 쓰러졌습니다.\n");
                    delay(2000);
                    system("cls");
                    window();
                    gotoxy(20, 9);
                    printf("    << 패배 하였습니다 >>\n");
                    lose++;
                    rating = rating - (stage_level - goto_stage) - 21;
                    if (player_maxhp >= 150 && player_maxmp >= 150)
                    {
                        gotoxy(20, 10);
                        printf("      능력치가 감소합니다.\n");
                        player_maxhp = player_maxhp - 10;
                        player_maxmp = player_maxmp - 10;
                    }
                    gotoxy(20, 13);
                    printf("계속 하려면 아무 키나 누르세요.\n");
                    _getch();
                    break;
                }
                if (com_hp <= 0 && stage_level == goto_stage)
                {
                    all_set();
                    printf("적이 쓰러졌습니다.\n");
                    gotoxy(50, 16);
                    puts("   ");
                    gotoxy(50, 16);
                    puts("OTL");
                    delay(2000);
                    system("cls");
                    printf("\n");
                    gotoxy(20, 9);
                    printf("         << 승리 하였습니다! >>\n");
                    win++;
                    rating = rating + 21;
                    gotoxy(20, 10);
                    player_exp = player_exp + (goto_stage * 100);
                    printf("      경험치를 %d 만큼 얻었습니다.\n", goto_stage * 100);
                    gotoxy(20, 11);
                    player_gold = player_gold + (goto_stage * 500);
                    printf("       골드를 %d 만큼 얻었습니다.\n", goto_stage * 500);
                    level_up(player_exp);
                    gotoxy(20, 12);
                    printf("   다음 스테이지에 도전 할 수 있습니다.\n");
                    gotoxy(20, 13);
                    printf("     계속 하려면 아무 키나 누르세요.\n");
                    window();
                    stage_level = stage_level + 1;
                    _getch();
                    break;
                }
                if (com_hp <= 0 && stage_level > goto_stage)
                {
                    printf("적이 쓰러졌습니다.\n");
                    gotoxy(50, 16);
                    puts("   ");
                    gotoxy(50, 16);
                    puts("OTL");
                    delay(2000);
                    system("cls");
                    window();
                    gotoxy(20, 9);
                    printf("     승리 하였습니다!\n");
                    win++;
                    rating = rating + goto_stage;
                    gotoxy(20, 10);
                    player_exp = player_exp + (goto_stage * 80);
                    printf(" 경험치를 %d 만큼 얻었습니다.\n", goto_stage * 80);
                    gotoxy(20, 11);
                    player_gold = player_gold + (goto_stage * 300);
                    printf("  골드를 %d 만큼 얻었습니다.\n", goto_stage * 300);
                    level_up(player_exp);
                    gotoxy(20, 12);
                    printf("계속 하려면 아무 키나 누르세요.\n");



                    _getch();
                    break;
                }
                if (player_dotecount > 0) {
                    player_dotecount = player_dotecount - 1;
                }
            }
        }
        if (choose == 0x32 && player_statpoint > 0) { // 메뉴에서 2. 스탯 입력시 (조건 o)
            menu_stat = 1;
            system("cls");
            stat_restore();
            playerstat_message();
            statchoose_message();
            printf("남은 스탯 포인트 : %d\n", player_statpoint);
            stat_up = _getch(); // 원하는 스탯 선택
            if (stat_up == 0x31 || stat_up == 0x32 || stat_up == 0x33 || stat_up == 0x34) {
                player_statpoint = player_statpoint - 1;
                choose = NULL;
            }
            if (stat_up == 0x31) {
                statchoose(1);
            }
            if (stat_up == 0x32) {
                statchoose(2);
            }
            if (stat_up == 0x33) {
                statchoose(3);
            }
            if (stat_up == 0x34) {
                statchoose(4);
            }
            if (stat_up == 0x35) {
                continue;
            }
            if (stat_up == 0x31 || stat_up == 0x32 || stat_up == 0x33 || stat_up == 0x34 || stat_up == 0x35) {
                system("cls");
                stat_restore();
                playerstat_message();

                if (player_defmain >= 100)
                {
                    printf(" 방어력은 100을 넘을 수 없습니다.\n");
                }
                printf(" 계속하려면 아무키나 누르세요\n");
                defover_state = 0;
                _getch();

                continue;
            }


        }
        if (choose == 0x32 && player_statpoint == 0) { // 메뉴에서 2. 스탯 입력시 (조건 x)
            system("cls");
            stat_restore();
            playerstat_message();
            printf("스탯 포인트가 없습니다.\n");
            _getch();
        }
        if (choose == 0x33 && player_skillpoint > 0) { // 메뉴에서 3. 스킬 입력시 (조건 o)
            menu_skill = 1;
            system("cls");
            skillchoose_message();
            printf("남은 스킬 포인트 : %d\n", player_skillpoint);
            skill_up = _getch();
            if (skill_up == 0x31 || skill_up == 0x32 || skill_up == 0x33 || skill_up == 0x34 || skill_up == 0x35) {
                player_skillpoint = player_skillpoint - 1; // 포인트 1 감소
                choose = NULL;
            }
            if (skill_up == 0x31 && player_skill1 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("해당 스킬은 이미 최대 레벨 입니다.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x32 && player_skill2 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("해당 스킬은 이미 최대 레벨 입니다.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x33 && player_skill3 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("해당 스킬은 이미 최대 레벨 입니다.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x34 && player_skill4 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("해당 스킬은 이미 최대 레벨 입니다.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x35 && player_skill5 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("해당 스킬은 이미 최대 레벨 입니다.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x31 && player_skill1 < 5) {
                player_skill1 = player_skill1 + 1; // 스킬 1번 업
            }


            if (skill_up == 0x32 && player_skill2 < 5) {
                player_skill2 = player_skill2 + 1; // 스킬 2번 업
            }

            if (skill_up == 0x33 && player_skill3 < 5) {
                player_skill3 = player_skill3 + 1; // 스킬 3번 업
            }

            if (skill_up == 0x34 && player_skill4 < 5) {
                player_skill4 = player_skill4 + 1; // 스킬 4번 업
            }

            if (skill_up == 0x35 && player_skill5 < 5) {
                player_skill5 = player_skill5 + 1; // 스킬 5번 업
            }

            if (skill_up == 0x31 || skill_up == 0x32 || skill_up == 0x33 || skill_up == 0x34 || skill_up == 0x35) {
                system("cls");
                skillchoose_message();
                printf("스킬 레벨이 올랐습니다. 계속 하려면 아무 키나 누르세요.\n");
                _getch();
            }

        }
        if (choose == 0x33 && player_skillpoint == 0) { // 메뉴에서 3. 스킬 입력시 (조건 x) 
            system("cls");
            skillchoose_message();
            printf("스킬 포인트가 없습니다.\n");
            _getch();
        }
        if (choose == 0x34) { // 메뉴에서 4. 무기 입력시
            menu_item = 1;
            for (;;)
            {
                system("cls");
                printf("┌──────────────────────────────────────────────────────┐ \n");
                printf("│                 <<< 무기 정보 >>>                    │   \n");
                if (item_code == 0)
                    printf("│             현재 장착중인 무기 : 없음                │  \n");
                if (item_code == 1)
                    printf("│           현재 장착중인 무기 : 증폭의 고서           │  \n");
                if (item_code == 2)
                    printf("│          현재 장착중인 무기 : 방출의 마법봉          │   \n");
                if (item_code == 3) {
                    printf("│          현재 장착중인 무기 : 현자의 지팡이          │    \n");
                }
                printf("└──────────────────────────────────────────────────────┘     \n");
                printf("                현재 보유한 골드 : %d                       \n", player_gold);
                printf("┌──────────────────────────────────────────────────────┐   \n");
                printf("│ 1. 증폭의 고서    (공격력 20 마나 400 / 10000골드)   │ \n");
                printf("│ 2. 방출의 마법봉  (공격력 80 마나 100 / 10000골드)   │ \n");
                printf("│ 3. 현자의 지팡이  (공격력 60 마나 300 / 14000골드)   │  \n");
                printf("│ 4. 무기 장착 해제 (장작 해제한 무기는 소멸)          │   \n");
                printf("├──────────────────────────────────────────────────────┤    \n");
                printf("│     아이템을 구매 하려면 해당 숫자를 눌러주세요.     │     \n");
                printf("│           메뉴로 돌아가려면 숫자 0을 입력            │    \n");
                printf("└──────────────────────────────────────────────────────┘   \n");
                item_choose = _getch();
                if (item_choose == 0x31)
                {
                    if (player_gold >= 10000 && item_code == 0)
                    {
                        printf("증폭의 고서를 장착 했습니다.\n");
                        item_code = 1;
                        *item_att = player_att + 20;
                        *item_mp = player_maxmp + 400;
                        player_gold = player_gold - 10000;
                        printf("계속 하려면 아무 키나 누르세요.\n");
                        _getch();
                        break;
                    }
                    else
                    {
                        printf("구입 불가능! 골드 부족 혹은 무기 장착 해제 후 재시도 하세요\n");
                        _getch();
                    }
                }
                if (item_choose == 0x32)
                {
                    if (player_gold >= 10000 && item_code == 0)
                    {
                        printf("방출의 마법봉을 장착 했습니다.\n");
                        item_code = 2;
                        *item_att = player_att + 80;
                        *item_mp = player_maxmp + 100;
                        player_gold = player_gold - 10000;
                        printf("계속 하려면 아무 키나 누르세요.\n");
                        _getch();
                        break;
                    }
                    else
                    {
                        printf("구입 불가능! 골드 부족 혹은 무기 장착 해제 후 재시도 하세요\n");
                        _getch();
                    }
                }
                if (item_choose == 0x33)
                {
                    if (player_gold >= 14000 && item_code == 0)
                    {
                        printf("현자의 지팡이를 장착 했습니다.\n");
                        item_code = 3;
                        *item_att = player_att + 60;
                        *item_mp = player_maxmp + 300;
                        player_gold = player_gold - 14000;
                        printf("계속 하려면 아무 키나 누르세요.\n");
                        _getch();
                        break;
                    }
                    else
                    {
                        printf("구입 불가능! 골드 부족 혹은 무기 장착 해제 후 재시도 하세요\n");
                        _getch();
                    }
                }
                if (item_choose == 0x34)
                {
                    if (item_code == 1)
                    {
                        printf("무기 장착 해제 완료.\n");
                        item_code = 0;
                        *item_att = player_att - 20;
                        *item_mp = player_maxmp - 400;
                    }
                    if (item_code == 2)
                    {
                        printf("무기 장착 해제 완료.\n");
                        item_code = 0;
                        *item_att = player_att - 80;
                        *item_mp = player_maxmp - 100;
                    }
                    if (item_code == 3)
                    {
                        printf("무기 장착 해제 완료.\n");
                        item_code = 0;
                        *item_att = player_att - 60;
                        *item_mp = player_maxmp - 300;
                    }
                    _getch();
                }
                if (item_choose == 0x30)
                {
                    break;
                }
            }
        }
        if (choose == 0x35)
        {
            for (;;)
            {
                system("cls");
                printf("┌──────────────────────────────────────┐     \n");
                printf("│ 치트 코드를 입력하세요. (숫자 4자리) │    \n");
                printf("│    메뉴로 나가려면 숫자 0을 입력     │      \n");
                printf("└──────────────────────────────────────┘    \n");
                scanf_s("%d", &cheat);
                if (cheat == 1234)
                {
                    printf("체력이 100 증가합니다!\n");
                    player_maxhp = player_maxhp + 100;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("마나가 100 증가합니다!\n");
                    player_maxmp = player_maxmp + 100;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("공격력이 20 증가합니다!\n");
                    player_att = player_att + 20;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("방어력이 10 증가합니다!\n");
                    player_defmain = player_defmain + 10;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("골드가 2000 증가 합니다!\n");
                    player_gold = player_gold + 2000;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("스탯 포인트가 1 증가합니다!\n");
                    player_statpoint = player_statpoint + 1;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("스킬 포인트가 1 증가합니다!\n");
                    player_skillpoint++;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("스테이지 레벨이 10으로 설정 되었습니다!\n");
                    stage_level = 10;
                    c_value++;
                    _getch();
                }
                else if (cheat == 12341234)
                {
                    printf("Admin mode enabled.\n");
                    player_gold = 100000;
                    stage_level = 11;
                    player_statpoint = 100;
                    player_skillpoint = 100;
                    _getch();
                }
                else if (cheat == 0)
                {
                    break;
                }
                else
                {
                    printf("잘못된 치트 코드 입니다\n");
                    _getch();
                    cheat = 0;
                }
            }

        }
        if (choose == 0x36)
        {
            system("cls");
            int temp_speed;
            temp_speed = speed;
            printf("┌──────────────────────────────────────────────────────┐  \n");
            printf("│               게임 속도를 입력하세요.                    \n");
            printf("│  * 이펙트를 제외한 상황판 메세지 속도만 적용됩니다.           \n");
            printf("│   숫자가 낮을수록 빠릅니다. 메뉴로 가려면 0을 입력.            \n");
            printf("│             현재 속도 : %d ( 권장 500-800 )                             \n", speed);
            printf("└──────────────────────────────────────────────────────┘ \n");
            gotoxy(55, 1);
            puts("│");
            gotoxy(55, 2);
            puts("│");
            gotoxy(55, 3);
            puts("│");
            gotoxy(55, 4);
            puts("│");
            gotoxy(0, 6);
            scanf_s("%d", &speed);
            if (speed == 0)
            {
                speed = temp_speed;
            }
            else if (speed < 100)
            {
                speed = temp_speed;
                printf("최소 100 부터 가능 합니다.\n");
                _getch();
                continue;
            }
            else if (speed > 2000)
            {
                speed = temp_speed;
                printf("최대 2000 까지 가능 합니다.\n");
                _getch();
                continue;
            }
            else if (speed >= 100 && speed <= 2000)
            {
                printf("적용이 완료 되었습니다.\n");
                _getch();
            }
            else
            {
                continue;
            }
        }
        if (choose == 0x30 && stage_level >= 11)
        {
            system("cls");
            printf(" CODE   : %d_%d_12345\n", win, lose);
            printf("C_Value : %d\n", c_value);
            _getch();
        }
        if (choose == 0x37)
        {
            system("cls");
            window();
            gotoxy(16, 1);
            printf("                  <도움말>\n");
            gotoxy(16, 2);
            printf(" 이 게임은 1단계의 적부터 차례대로 싸워가며\n");
            gotoxy(16, 3);
            printf("     레벨 업을 통하여 능력을 강화시켜\n");
            gotoxy(16, 4);
            printf(" 10단계의 보스를 무찌르는 것이 목표 입니다.\n");
            gotoxy(16, 6);
            printf("        턴 형식의 전투 방식이며\n");
            gotoxy(16, 8);
            printf("  적은 4가지 기술을 랜덤으로 사용 합니다.\n");
            gotoxy(16, 10);
            printf("  만약 현재 도전하는 스테이지가 어렵다면 \n");
            gotoxy(16, 12);
            printf(" 더 낮은 스테이지에서 레벨 업을 해보세요.\n");
            gotoxy(16, 14);
            printf("       더 성장한 뒤 다시 도전할 경우\n");
            gotoxy(16, 16);
            printf("훨씬 더 쉽게 스테이지를 클리어 할 수 있을겁니다.\n");
            _getch();
        }
        if (choose == 0x38)
        {
            system("cls");
            printf("게임명    : 마법사의 모험\n");
            printf("장르      : 턴 방식 싱글 플레이 RPG 게임");
            printf("버젼      : 1.0\n");
            printf("환경      : 윈도우 7 32비트\n");
            printf("기획      : 백성진\n");
            printf("개발자    : 백성진\n");
            printf("툴        : Microsoft Visual C++ 2010 Express\n");
            printf("제작 완료 : 2014/6/16\n");
            printf("제작 기간 : 시간 나는대로 제작.\n");
            printf("이메일    : cd991478@naver.com\n");
            printf("한마디    : 초보작이라 허접하지만 많이 고생했음 ㅠㅠ\n");
            printf("\n");
            _getch();
        }
    } // for(;;)
} // int main(void)