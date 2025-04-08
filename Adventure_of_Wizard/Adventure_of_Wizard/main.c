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
    // �ܼ� ȭ�� ���� ũ�� ����
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    // �ܼ� â ũ�� ����
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
char stage01[] = { "�뺴" };
char stage02[] = { "����" };
char stage03[] = { "���ݼ�" };
char stage04[] = { "���� ������" };
char stage05[] = { "���� ������" };
char stage06[] = { "ȭ�� ������" };
char stage07[] = { "õ�� ������" };
char stage08[] = { "���� ������" };
char stage09[] = { "�˰�" };
char stage10[] = { "â�� ����" };
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
    puts("��");
    gotoxy(50, 16);
    puts("��");
    gotoxy(0, 18);
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
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
    puts("��");
    gotoxy(28, 16);
    puts("��");
    gotoxy(0, 18);
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
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
    puts("��");
    delay(100);
    gotoxy(22, 17);
    puts("��");
    delay(100);
    gotoxy(20, 17);
    puts("����");
    delay(100);
    gotoxy(18, 17);
    puts("��");
    delay(100);
    gotoxy(18, 16);
    puts("��");
    delay(100);
    gotoxy(18, 15);
    puts("��");
    delay(100);
    gotoxy(20, 15);
    puts("����");
    delay(100);
    gotoxy(22, 15);
    puts("��");
    delay(100);
    char_set();
    gotoxy(22, 16);
    puts("��");
    gotoxy(22, 17);
    puts("��");
    gotoxy(20, 17);
    puts("��");
    gotoxy(18, 17);
    puts("��");
    gotoxy(18, 16);
    puts("��");
    gotoxy(18, 15);
    puts("��");
    gotoxy(20, 15);
    puts("��");
    gotoxy(22, 15);
    puts("��");
    delay(100);
    char_set();
}
void comdfup_eft()
{
    gotoxy(52, 16);
    puts("��");
    delay(100);
    gotoxy(52, 17);
    puts("��");
    delay(100);
    gotoxy(50, 17);
    puts("����");
    delay(100);
    gotoxy(48, 17);
    puts("��");
    delay(100);
    gotoxy(48, 16);
    puts("��");
    delay(100);
    gotoxy(48, 15);
    puts("��");
    delay(100);
    gotoxy(50, 15);
    puts("����");
    delay(100);
    gotoxy(52, 15);
    puts("��");
    delay(100);
    char_set();
    gotoxy(52, 16);
    puts("��");
    gotoxy(52, 17);
    puts("��");
    gotoxy(50, 17);
    puts("��");
    gotoxy(48, 17);
    puts("��");
    gotoxy(48, 16);
    puts("��");
    gotoxy(48, 15);
    puts("��");
    gotoxy(50, 15);
    puts("��");
    gotoxy(52, 15);
    puts("��");
    delay(100);
    eft_set();
}
void playerboom_eft()
{
    gotoxy(18, 15);
    puts("��");
    gotoxy(22, 17);
    puts("��");
    gotoxy(18, 17);
    puts("��");
    gotoxy(22, 15);
    puts("��");
    gotoxy(20, 17);
    puts("��");
    gotoxy(18, 16);
    puts("��");
    gotoxy(20, 15);
    puts("��");
    gotoxy(22, 16);
    puts("��");
    delay(200);
    eft_set();
}
void playerfreeze_eft()
{
    gotoxy(18, 15);
    puts("��");
    gotoxy(22, 17);
    puts("��");
    gotoxy(18, 17);
    puts("��");
    gotoxy(22, 15);
    puts("��");
    gotoxy(20, 17);
    puts("��");
    gotoxy(18, 16);
    puts("��");
    gotoxy(20, 15);
    puts("��");
    gotoxy(22, 16);
    puts("��");
    delay(200);
    eft_set();
}
void playerthunder_eft()
{
    gotoxy(18, 15);
    puts("��");
    gotoxy(22, 17);
    puts("��");
    gotoxy(18, 17);
    puts("��");
    gotoxy(22, 15);
    puts("��");
    gotoxy(20, 17);
    puts("��");
    gotoxy(18, 16);
    puts("��");
    gotoxy(20, 15);
    puts("��");
    gotoxy(22, 16);
    puts("��");
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
    puts("��");
    gotoxy(78, 0);
    puts("��");
    gotoxy(0, 22);
    puts("��");
    gotoxy(78, 22);
    puts("��");
    for (x = 2; x < 78; x = x + 2)
    {
        gotoxy(x, 0);
        puts("����");
        gotoxy(x, 22);
        puts("����");
    }
    for (y = 1; y < 22; y++)
    {
        gotoxy(0, y);
        puts("��");
        gotoxy(78, y);
        puts("��");
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
        puts("��");
        delay(10);
        if (k != 28)
        {
            gotoxy(k, 16);
            puts("��");
        }
    }
}
void back_eft()
{
    int k;
    for (k = 27; k < 50; k++)
    {
        gotoxy(k, 16);
        puts("��");
        delay(10);
        gotoxy(k, 16);
        puts("��");
    }
}
void skill0_eft()
{
    int k;
    for (k = 22; k < 49; k++)
    {
        gotoxy(k, 16);
        puts("��");
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
            puts("��");
            delay(t);
            gotoxy(k, 16);
            puts(" ");
        }
        if (k % 2 == 1)
        {
            gotoxy(k, 16);
            puts("��");
            delay(t);
            gotoxy(k, 16);
            puts(" ");
        }
    }
    if (player_skill1 == 1)
    {
        gotoxy(48, 16);
        puts("��");
        gotoxy(48, 15);
        puts("��");
        gotoxy(48, 17);
        puts("��");
        gotoxy(50, 16);
        puts("��");
        gotoxy(52, 16);
        puts("��");
        gotoxy(50, 15);
        puts("��");
        gotoxy(50, 17);
        puts("��");
        gotoxy(52, 17);
        puts("��");
        gotoxy(52, 15);
        puts("��");
        delay(100);
    }
    if (player_skill1 >= 2)
    {
        gotoxy(48, 17);
        puts("��");
        delay(20);
        gotoxy(50, 17);
        puts("��");
        delay(20);
        gotoxy(52, 17);
        puts("��");
        delay(20);
        gotoxy(48, 16);
        puts("��");
        delay(20);
        gotoxy(50, 16);
        puts("��");
        delay(20);
        gotoxy(52, 16);
        puts("��");
        delay(20);
        gotoxy(48, 15);
        puts("��");
        delay(20);
        gotoxy(50, 15);
        puts("��");
        delay(20);
        gotoxy(52, 15);
        puts("��");
        delay(50);
        char_set();
        delay(50);
        gotoxy(48, 16);
        puts("��");
        gotoxy(48, 15);
        puts("��");
        gotoxy(48, 17);
        puts("��");
        gotoxy(50, 16);
        puts("��");
        gotoxy(52, 16);
        puts("��");
        gotoxy(50, 15);
        puts("��");
        gotoxy(50, 17);
        puts("��");
        gotoxy(52, 17);
        puts("��");
        gotoxy(52, 15);
        puts("��");
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
        puts("��");
        delay(t);

        gotoxy(k + 2, 16);
        puts("��");
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
            puts("��");
            gotoxy(k + 2, 16);
            puts("��");
            k = k + 2;
        }
        gotoxy(48, 16);
        puts("��");
        gotoxy(48, 15);
        puts("��");
        gotoxy(48, 17);
        puts("��");
        gotoxy(50, 16);
        puts("��");
        gotoxy(52, 16);
        puts("��");
        gotoxy(50, 15);
        puts("��");
        gotoxy(50, 17);
        puts("��");
        gotoxy(52, 17);
        puts("��");
        gotoxy(52, 15);
        puts("��");

        delay(t * 2);
        char_set();
        for (k = 22; k < 49; k = k + 2)
        {
            gotoxy(k, 16);
            puts("��");
            gotoxy(k + 2, 16);
            puts("��");
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
        puts("��");
        delay(20);
        gotoxy(k, 16);
        puts(" ");
    }
    playerboom_eft();
}
void sword_eft()
{
    gotoxy(50, 15);
    puts("��");
    delay(50);
    char_set();
    gotoxy(48, 15);
    puts("��");
    delay(50);
    char_set();
    gotoxy(48, 16);
    puts("����");
    delay(50);
    char_set();
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("��");
        delay(10);
        gotoxy(k, 16);
        puts(" ");
    }
    eft_set();
}
void roar_eft()
{
    gotoxy(48, 15);
    puts("��");
    gotoxy(48, 16);
    puts("����");
    gotoxy(48, 17);
    puts("��");
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
    puts("��");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("��");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("��");
    delay(100);
    gotoxy(18, 15);
    puts("��");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("��");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("��");
    delay(100);
    move_set();
    gotoxy(22, 15);
    puts("��");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("��");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("��");
    delay(100);
    gotoxy(18, 15);
    puts("��");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("��");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("��");
    delay(100);
    move_set();
    gotoxy(22, 15);
    puts("��");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("��");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("��");
    delay(100);
    gotoxy(18, 15);
    puts("��");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("��");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("��");
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
        puts("����");
        delay(5);
        gotoxy(k, 16);
        puts(" ");
    }
    eft_set();
}
void focus_eft()
{
    gotoxy(48, 16);
    puts("��");
    delay(100);
    char_set();
    gotoxy(48, 15);
    puts("��");
    delay(100);
    char_set();
    gotoxy(52, 16);
    puts("��");
    delay(100);
    char_set();
    gotoxy(52, 15);
    puts("��");
    delay(100);
    char_set();
    gotoxy(48, 16);
    puts("��");
    delay(100);
    char_set();
    gotoxy(48, 15);
    puts("��");
    delay(100);
    char_set();
    gotoxy(52, 16);
    puts("��");
    delay(100);
    char_set();
    gotoxy(52, 15);
    puts("��");
    delay(100);
    eft_set();
}
void headshot_eft()
{
    int k;
    gotoxy(20, 15);
    puts("��");
    gotoxy(20, 17);
    puts("��");
    gotoxy(18, 16);
    puts("����");
    gotoxy(22, 16);
    puts("����");
    delay(500);
    char_set();
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("����");
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
        puts("��");
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
        puts("��");
        delay(20);
        gotoxy(k - 2, 16);
        puts("��");
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
            puts("��");
            gotoxy(k - 2, 16);
            puts("��");
            k = k - 2;
        }
        gotoxy(20, 15);
        puts("��");
        gotoxy(22, 16);
        puts("����");
        gotoxy(20, 17);
        puts("��");
        gotoxy(18, 16);
        puts("����");
        delay(50);
        char_set();
        for (k = 48; k > 21; k = k - 2)
        {
            gotoxy(k, 16);
            puts("��");
            gotoxy(k - 2, 16);
            puts("��");
            k = k - 2;
        }
        gotoxy(22, 15);
        puts("��");
        gotoxy(22, 17);
        puts("��");
        gotoxy(18, 17);
        puts("��");
        gotoxy(18, 15);
        puts("��");
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
        puts("��");
        delay(20);
    }
    char_set();
    for (t = 0; t < 4; t++)
    {
        for (k = 48; k > 21; k = k - 4)
        {
            gotoxy(k, 16);
            puts("��");
        }
        playerboom_eft();
        delay(50);
        char_set();
        for (k = 46; k > 21; k = k - 4)
        {
            gotoxy(k, 16);
            puts("��");
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
        puts("��");
        delay(200);
        char_set();
        gotoxy(48, 15);
        puts("��");
        gotoxy(52, 15);
        puts("��");
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
        puts("��");
        delay(50);
        move_set();
        gotoxy(24, 16);
        puts("��");
        delay(50);
        move_set();
        gotoxy(22, 16);
        puts("��");
        delay(50);
        move_set();
        gotoxy(18, 17);
        puts("��");
        gotoxy(20, 17);
        puts("��");
        gotoxy(22, 17);
        puts("��");
        delay(20);
        move_set();
        gotoxy(18, 16);
        puts("��");
        gotoxy(22, 16);
        puts("��");
        delay(20);
        move_set();
        gotoxy(18, 15);
        puts("��");
        gotoxy(20, 15);
        puts("��");
        gotoxy(22, 15);
        puts("��");
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
            puts("��");
            gotoxy(k - 2, 15);
            puts("��");
            gotoxy(k - 4, 15);
            puts("��");
            gotoxy(k, 16);
            puts("��");
            gotoxy(k - 2, 16);
            puts("��");
            gotoxy(k - 4, 16);
            puts("��");
            gotoxy(k, 17);
            puts("��");
            gotoxy(k - 2, 17);
            puts("��");
            gotoxy(k - 4, 17);
            puts("��");
            delay(20);
            char_set();
        }
        if (k % 2 == 1)
        {
            gotoxy(k, 15);
            puts("��");
            gotoxy(k - 2, 15);
            puts("��");
            gotoxy(k - 4, 15);
            puts("��");
            gotoxy(k, 16);
            puts("��");
            gotoxy(k - 2, 16);
            puts("��");
            gotoxy(k - 4, 16);
            puts("��");
            gotoxy(k, 17);
            puts("��");
            gotoxy(k - 2, 17);
            puts("��");
            gotoxy(k - 4, 17);
            puts("��");
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
            puts("��");
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
        puts("��");
        delay(20);
    }
    gotoxy(22, 15);
    puts("��");
    gotoxy(22, 16);
    puts("��");
    gotoxy(22, 17);
    puts("��");
    delay(100);
    gotoxy(20, 15);
    puts("��");
    gotoxy(20, 16);
    puts("��");
    gotoxy(20, 17);
    puts("��");
    delay(100);
    gotoxy(18, 15);
    puts("��");
    gotoxy(18, 16);
    puts("��");
    gotoxy(18, 17);
    puts("��");
    delay(100);
    eft_set();
}
void silence_eft()
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("��");
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
        puts("��");
        delay(100);
        char_set();
        gotoxy(18, 16);
        puts("��");
        delay(100);
        char_set();
        gotoxy(22, 15);
        puts("��");
        delay(100);
        char_set();
        gotoxy(22, 16);
        puts("��");
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
        puts("��");
        delay(20);
        gotoxy(46, 16);
        puts("��");
        delay(20);
        gotoxy(44, 17);
        puts("��");
        delay(20);
        char_set();
        delay(20);
        for (k = 42; k > 22; k = k - 2)
        {
            gotoxy(k, 15);
            puts("��");
            gotoxy(k - 2, 16);
            puts("��");
            gotoxy(k - 4, 17);
            puts("��");
            delay(10);
            char_set();
        }
        gotoxy(44, 15);
        puts("��");
        delay(20);
        gotoxy(46, 16);
        puts("��");
        delay(20);
        gotoxy(48, 17);
        puts("��");
        delay(20);
        char_set();
        delay(20);
        for (k = 44; k > 18; k = k - 2)
        {
            gotoxy(k, 15);
            puts("��");
            gotoxy(k + 2, 16);
            puts("��");
            gotoxy(k + 4, 17);
            puts("��");
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
        puts("��");
        gotoxy(48, 16);
        puts("��");
        delay(200);
        char_set();
        gotoxy(52, 15);
        puts("��");
        gotoxy(52, 16);
        puts("��");
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
        puts("��");
        delay(100);
        gotoxy(20, 16);
        puts("��");
        delay(100);
        gotoxy(22, 17);
        puts("��");
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
    puts("����");
    delay(20);
    gotoxy(20, 16);
    puts("����");
    delay(20);
    gotoxy(22, 16);
    puts("����");
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
            puts("����");
            gotoxy(26, 16);
            puts("����");
            gotoxy(30, 16);
            puts("����");
            delay(200);
            move_set();
        }
        gotoxy(22, 16);
        puts("����");
        gotoxy(24, 16);
        puts("����");
        gotoxy(26, 16);
        puts("����");
        if (k == 2)
        {
            gotoxy(20, 16);
            puts(" ");
            gotoxy(20, 15);
            puts("��");
        }
        delay(100);
        move_set();
    }
    gotoxy(24, 16);
    puts("����");
    gotoxy(26, 16);
    puts("����");
    gotoxy(30, 16);
    puts("����");
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
        puts("��");
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
    puts("����");
    gotoxy(26, 16);
    puts("����");
    delay(30);
    move_set();
    gotoxy(26, 17);
    puts("��");
    delay(30);
    move_set();
    gotoxy(28, 17);
    puts("��");
    delay(30);
    move_set();
    gotoxy(30, 17);
    puts("��");
    delay(30);
    move_set();
    gotoxy(30, 15);
    puts("����");
    delay(20);
    move_set();
    gotoxy(30, 15);
    puts("��");
    delay(20);
    move_set();
    gotoxy(28, 15);
    puts("��");
    delay(20);
    move_set();
    gotoxy(26, 15);
    puts("��");
    delay(20);
    move_set();
    gotoxy(24, 16);
    puts("����");
    gotoxy(26, 16);
    puts("����");
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
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��               ��� ��ų �ɷ�ġ�� ���� �ϼ���.                    ��    \n");
    printf("��   1.ü��+50   2.����+50   3.���ݷ�+10   4.����+5   5.���      ��      \n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
} // ���� ��ȭ ȭ��
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
} // ���� ����
void playerstat_message()
{
    printf("������������������������������������������������������������\n");
    printf("��       <<< ���� >>>              \n");
    printf("�� ����   : ������               \n");
    printf("�� ����   : %d                     \n", player_level);
    printf("�� ü��   : %d / %d               \n", player_hp, player_maxhp);
    printf("�� ����   : %d / %d             \n", player_mp, player_maxmp);
    printf("�� ���ݷ� : %d                  \n", player_att);
    printf("�� ���� : %d                 \n", player_defmain);
    printf("�� ����ġ : %d / %d (%.2f %%) \n", player_exp, player_maxexp, (float)player_exp / (float)player_maxexp * 100);
    printf("�� ������ ��� : %d           \n", player_gold);
    printf("������������������������������������������������������������\n");
    int k;
    for (k = 1; k < 10; k++)
    {
        gotoxy(29, k);
        puts("��");
    }
    gotoxy(0, 11);
   
} // ���� ȭ�� ���� ����
void comstat_message()
{
    printf("  <<<��>>>\n");
}
void menu_choose()
{
    printf("��������������������������������������������������������������������������������������������������������������������������������������������   \n");
    printf("��                         ������ �Ͻðڽ��ϱ�?                       �� \n");
    printf("��  1.����  2.����  3.��ų  4.����  5.ġƮ  6.����  7.����  8.����  ��  \n");
    printf("��������������������������������������������������������������������������������������������������������������������������������������������    \n");
    if (stage_level >= 11)
    {
        printf("   ���ϵ帳�ϴ�! ��� ���������� Ŭ���� �Ͽ����ϴ�.\n");
        printf("     ���� �ڵ带 Ȯ�� �Ϸ��� ���� 0�� ��������.\n");
    }
    if (player_statpoint > 0)
    {
        printf("\n      * ������� ���� ���� ����Ʈ�� ���� �ֽ��ϴ�.\n");
    }
    if (player_skillpoint > 0)
    {
        printf("\n      * ������� ���� ��ų ����Ʈ�� ���� �ֽ��ϴ�.\n");
    }
    if (player_gold >= 10000 && item_code != 3)
    {
        printf("\n      * ��尡 ���� �𿴽��ϴ�. ���⸦ ���� �غ�����.\n");
    }
} // ���� �޴� ȭ��
int skill_1()
{
    //���̾
    int d;
    d = (player_level * 10) + (player_att / 2) + (player_skill1 * 20);
    return d;
}
int skill_2()
{
    //�����Ʈ
    int d;
    d = (player_level * 9) + (player_att / 2) + (player_skill2 * 18);
    return d;
}
int skill_3()
{
    //ť��
    int d;
    d = (player_level * 10) + (player_skill3 * 15) + (player_maxhp / 20) + (player_maxmp / 20);
    return d;
}
int skill_4()
{
    //���� ��
    int d;
    d = (player_skill4 * 2) + (player_maxhp / 100);
    return d;
}
int skill_5()
{
    //�޵����̼�
    int d;
    d = 45 + (player_skill5 * 5) + (player_maxhp / 100);
    return d;
}
void skillchoose_message() // ��ų ���� �޼���
{
    printf("����������������������������������������������������������������������������������������������������������������������������������������   \n");
    printf("��                <<< ��ȭ�� ��ų�� �����ϼ��� >>>                  ��  \n");
    printf("�� 1. ���̾� �� (%d����/5)                                           ��\n", player_skill1);
    printf("��   - ���� �����Ͽ� %d��ŭ�� ���ظ� ����(+20)                        \n", skill_1());
    printf("��                                                                  ��  \n");
    printf("�� 2. ��� ��Ʈ (%d����/5)                                           ��   \n", player_skill2);
    printf("��   - ������ %d��ŭ�� ���ظ� ������, ������ %d ���ҽ�Ŵ(+18,+2)     \n", skill_2(), player_skill2 * 2);
    printf("��                                                                  ��  \n");
    printf("�� 3. ť�� (%d����/5)                                                ��   \n", player_skill3);
    printf("��   - �ڽ��� ü���� %d��ŭ ȸ����(+15)                               \n", skill_3());
    printf("��                                                                  �� \n");
    printf("�� 4. ���� �� (%d����/5)                                             ��  \n", player_skill4);
    printf("��   - �������� �ڽ��� ������ %d��ŭ ���� ��Ŵ(+2)                   \n", skill_4());
    printf("��                                                                  ��  \n");
    printf("�� 5. �޵����̼� (%d����/5)                                          ��  \n", player_skill5);
    printf("��   - ���� ü���� 40%%�� �Ҹ��Ͽ� �ִ� ������ %d%% ������ ȸ��(+5%%)     \n", skill_5());
    printf("��                                                                  ��  \n");
    printf("�� 6. �޴��� ���ư���                                               ��   \n");
    printf("����������������������������������������������������������������������������������������������������������������������������������������    \n");
    gotoxy(67, 3);
    puts("��");
    gotoxy(67, 6);
    puts("��");
    gotoxy(67, 9);
    puts("��");
    gotoxy(67, 12);
    puts("��");
    gotoxy(67, 15);
    puts("��");
    gotoxy(0, 19);
}
void stat_restore() // �÷��̾� ���� �ʱ�ȭ
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
void stat_over() // ���� ������ �缳��
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
int stage_name(int a) // �������� �̸� ���
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
void fight_stat() // ������ ���� ȭ��
{
    printf("��������������<�÷��̾�>������������������������������������������������������������������������<��>��������������������������������������\n");
    printf("��   ü��   : %d / %d                          ü�� : %d / %d          \n", player_hp, player_maxhp, com_hp, com_maxhp);
    printf("��   ����   : %d / %d                                                  \n", player_mp, player_maxmp);
    printf("��   ���ݷ� : %d                                 ���ݷ� : %d           \n", player_att, com_att);
    printf("��   ���� : %d                                  ���� : %d          \n", player_def + player_defup, com_def);
    gotoxy(75, 2);
    puts("��");
    gotoxy(75, 3);
    puts("��");
    gotoxy(75, 4);
    puts("��");
    gotoxy(75, 5);
    puts("��");
}
void fight_skill()
{
    printf("����������������������������������< ��ų�� ����Ϸ��� ���� ��ư�� �������� >����������������������������������\n");
    printf("��     1.���̾� �� (20 ����) : %d �� ���ظ� ����                           \n", skill_1());
    printf("��     2.��� ��Ʈ (25 ����) : %d �� ���ظ� ������, ������ %d ���ҽ�Ŵ    \n", skill_2(), player_skill2 * 2);
    printf("��     3.ť��      (30 ����) : �ڽ��� ü���� %d ��ŭ ȸ����                 \n", skill_3());
    printf("��     4.���� ��   (20 ����) : �ڽ��� ������ %d ��ŭ ������Ŵ             \n", skill_4());
    printf("��     5.�޵����̼� (0 ����) : ü���� 40%%�� �Ҹ��Ͽ� %d%%�� ���� ȸ��     \n", skill_5());
    printf("��     0.�⺻ ����  (0 ����) : %d �� ���ظ� ������ %d�� ���� ȸ��          \n", player_att, player_att + (player_maxmp / 20));
    printf("��������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    gotoxy(75, 7);
    puts("��");
    gotoxy(75, 8);
    puts("��");
    gotoxy(75, 9);
    puts("��");
    gotoxy(75, 10);
    puts("��");
    gotoxy(75, 11);
    puts("��");
    gotoxy(75, 12);
    puts("��");
}
int com_demage(int a)
{
    if (a > com_def) {
        printf("���� %d ��ŭ�� ���ظ� �޾ҽ��ϴ�. \n", a - com_def);
        com_hp = com_hp - (a)+com_def;
    }
    if (a <= com_def) {
        printf("���� 1 ��ŭ�� ���ظ� �޾ҽ��ϴ�.\n");
        com_hp = com_hp - 1;
    }

    return a;
}
int player_demage(int a)
{
    if (a > (player_def + player_defup)) {
        printf("%d ��ŭ�� ���ظ� �޾ҽ��ϴ�. \n", a - (player_def + player_defup));
        player_hp = player_hp - (a)+player_def + player_defup;
    }
    if (a <= (player_def + player_defup)) {
        printf("1 ��ŭ�� ���ظ� �޾ҽ��ϴ�.\n");
        player_hp = player_hp - 1;
    }
    return a;
}
int player_hpdown(int a)
{
    printf("ü���� %d ��ŭ �����մϴ�. \n", a);
    player_hp = player_hp - a;
    return a;
}
int com_defup(int a)
{
    printf("���� ������ %d ��ŭ �ö����ϴ�. \n", a);
    com_def = com_def + a;
    return a;
}
int com_defdown(int a)
{
    printf("���� ������ %d ��ŭ ���� �߽��ϴ�. \n", a);
    com_def = com_def - a;
    return a;
}
int com_attup(int a)
{
    printf("���� ���ݷ��� %d ��ŭ ���� �߽��ϴ�. \n", a);
    com_att = com_att + a;
    return a;
}
int player_defdown(int a)
{
    printf("������ %d ��ŭ �����մϴ�.\n", a);
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
    printf("ü���� %d ��ŭ ȸ�� �˴ϴ�.\n", a);
    player_hp = player_hp + a;
    return a;
}
int player_mplose(int a)
{
    printf("������ %d ��ŭ �����մϴ�.\n", a);
    player_mp = player_mp - a;
    return a;
}
int com_hpup(int a)
{
    if (a >= 0) {
        printf("���� ü���� %d ��ŭ ȸ�� �˴ϴ�.\n", a);
        com_hp = com_hp + a;
    }
    if (a < 0) {
        printf("���� ü���� 1 ��ŭ ȸ�� �˴ϴ�.\n");
        com_hp = com_hp + 1;
    }
    return a;
}
int player_mpup(int a)
{
    printf("������ %d ��ŭ ȸ�� �˴ϴ�.\n", a);
    player_mp = player_mp + a;
    return a;
}
int player_mppup(int a)
{
    printf("������ %d%% ��ŭ ȸ�� �˴ϴ�.\n", a);
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
    printf("������ �����մϴ�.\n");
}
char player_skill(char a)
{
    if (a == 0x30) {
        printf("<0. �⺻ ����>�� ��� �߽��ϴ�.\n");
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
        printf("<1. ���̾� ��>�� ��� �߽��ϴ�.\n");
        d1s();
        skill1_eft();
        d1s();
        if (goto_stage == 6)
        {
            printf("���� ȭ�� �Ӽ��� �鿪�Դϴ�.\n");
            d1s();
            printf("���ظ� ���� �ʽ��ϴ�.\n");
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
        printf("<2. ��� ��Ʈ>�� ��� �߽��ϴ�.\n");
        d1s();
        skill2_eft();
        d1s();
        if (goto_stage == 5)
        {
            printf("���� ���� �Ӽ��� �鿪�Դϴ�.\n");
            d1s();
            printf("���ظ� ���� �ʽ��ϴ�.\n");
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
        printf("<3. ť��>�� ��� �߽��ϴ�.\n");
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
        printf("<4. ���� ��>�� ��� �߽��ϴ�.\n");
        d1s();
        skill4_eft();
        d1s();
        printf("������ %d ��ŭ ���� �մϴ�\n", skill_4());
        player_defup = player_defup + skill_4();
        d1s();
        player_mpdown(20);
        turn++;
    }
    if (a == 0x35) {
        printf("<5. �޵����̼�>�� ��� �߽��ϴ�.\n");
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
        printf("    �����մϴ�! �������� �Ͽ����ϴ�!\n");
        gotoxy(20, 17);
        printf("���� ����Ʈ 3, ��ų ����Ʈ 1�� ������ϴ�.\n");
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
    printf("�ƹ��͵� �� �� �����ϴ�.\n");
    player_stun = 1;
    turn++;
}
void stage01_skill()
{
    int r1;
    randomize();
    r1 = random(40) + 11;
    if (com_skill == 0) {
        printf("���� <���� ���>�� ��� �߽��ϴ�.\n");
        d1s();
        gunshot_eft();
        gunshot_eft();
        gunshot_eft();
        d1s();
        player_demage(30);
        d1s();
    }
    if (com_skill == 1) {
        printf("���� <�ѱ� ����>�� ��� �߽��ϴ�.\n");
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
        printf("���� <����ź ��ô>�� ��� �߽��ϴ�.\n");
        d1s();
        boom_eft();
        d1s();
        player_demage(35);
        d1s();
        player_defdown(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <���� ġ��>�� ��� �߽��ϴ�.\n");
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
        printf("���� <�� �ֵθ���>�� ��� �߽��ϴ�.\n");
        d1s();
        sword_eft();
        d1s();
        player_demage(com_att + 15);
        d1s();
    }
    if (com_skill == 1) {
        printf("���� <��� �¼�>�� ��� �߽��ϴ�.\n");
        d1s();
        comdfup_eft();
        d1s();
        com_defup(5);
        d1s();
    }
    if (com_skill == 2) {
        printf("���� <������ �Լ�>�� ��� �߽��ϴ�.\n");
        d1s();
        roar_eft();
        d1s();
        com_attup(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <������ �ϰ�>�� ��� �߽��ϴ�.\n");
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
        printf("���� <����>�� ��� �߽��ϴ�.\n");
        d1s();
        sniper_eft();
        d1s();
        player_demage(com_att + 30);
        d1s();
    }
    if (com_skill == 1) {
        printf("���� <��������>�� ��� �߽��ϴ�.\n");
        d1s();
        focus_eft();
        d1s();
        com_attup(7);
        d1s();
    }
    if (com_skill == 2) {
        printf("���� <��弦>�� ��� �߽��ϴ�.\n");
        d1s();
        headshot_eft();
        d1s();
        printf("������ �����Ͽ� ���ظ� �����ϴ�.\n");
        d1s();
        player_demage(com_att + 30 + player_defup + player_def);
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <���� ġ��>�� ��� �߽��ϴ�.\n");
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
        printf("���� <���̽� ��>�� ��� �߽��ϴ�.\n");
        d1s();
        ice_eft();
        d1s();
        player_demage(com_att + 20);
        d1s();
    }
    if (com_skill == 1) {
        printf("���� <���� �帷>�� ��� �߽��ϴ�.\n");
        d1s();
        comdfup_eft();
        d1s();
        com_defup(8);
        d1s();
    }
    if (com_skill == 2) {
        printf("���� <���� ��ǳ>�� ��� �߽��ϴ�.\n");
        d1s();
        blizzard_eft();
        d1s();
        player_demage(com_att + 20);
        d1s();
        player_defdown(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <���� ���>�� ��� �߽��ϴ�.\n");
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
        printf("���� <���� ��Ÿ>�� ��� �߽��ϴ�.\n");
        d1s();
        thunder_eft();
        d1s();
        player_demage(com_att + 10);
        d1s();
    }
    if (com_skill == 1) {
        printf("���� <���� �帷>�� ��� �߽��ϴ�.\n");
        d1s();
        comdfup_eft();
        d1s();
        com_defup(5);
        d1s();
    }
    if (com_skill == 2) {
        printf("���� <���� ����>�� ��� �߽��ϴ�.\n");
        d1s();
        focus_eft();
        d1s();
        com_attup(5);
        d1s();
        com_hpup(25);
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <������ ����>�� ��� �߽��ϴ�.\n");
        d1s();
        powerthunder_eft();
        d1s();
        printf("������ �����Ͽ� ���ظ� �����ϴ�\n");
        d1s();
        player_demage(com_att + 10 + player_def + player_defup);
        d1s();
    }
}
void stage06_skill()
{
    if (com_skill == 0) {
        printf("���� <���� �л�>�� ��� �߽��ϴ�.\n");
        d1s();
        fireshot_eft();
        d1s();
        player_mplose(com_att + 20);
        d1s();
    }
    if (com_skill == 1) {
        printf("���� <�߿�>�� ��� �߽��ϴ�.\n");
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
        printf("���� <ȭ�� �ָ�>�� ��� �߽��ϴ�.\n");
        d1s();
        firepunch_eft();
        d1s();
        player_demage(com_att + 15);
        d1s();
        player_defdown(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <���� ȭ��>�� ��� �߽��ϴ�.\n");
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
        printf("���� <�ٶ� ����>�� ��� �߽��ϴ�.\n");
        d1s();
        windstorm_eft();
        d1s();
        player_demage(com_att / 2);
        d1s();
        printf("�ƹ��͵� �� �� �����ϴ�.\n");
        d1s();
        player_stun = 1;
        turn++;
    }
    if (com_skill == 1) {
        printf("���� <��� ���>�� ��� �߽��ϴ�.\n");
        d1s();
        absorb_eft();
        d1s();
        player_demage(com_att);
        d1s();
        com_hpup(com_att / 2);
        d1s();
    }
    if (com_skill == 2) {
        printf("���� <�ٶ��� ��ȣ>�� ��� �߽��ϴ�.\n");
        d1s();
        focus_eft();
        d1s();
        com_attup(10);
        d1s();
        com_defup(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <����ǳ>�� ��� �߽��ϴ�.\n");
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
        printf("���� <���� �ĵ�>�� ��� �߽��ϴ�.\n");
        d1s();
        darkbeam_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_defdown(10);
        d1s();
    }
    if (com_skill == 1) {
        printf("���� <ħ��>�� ��� �߽��ϴ�.\n");
        d1s();
        silence_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_stunon();
        d1s();
    }
    if (com_skill == 2) {
        printf("���� <����ȭ>�� ��� �߽��ϴ�.\n");
        d1s();
        empower_eft();
        d1s();
        player_mplose(player_mp / 2);
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <���>�� ��� �߽��ϴ�.\n");
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
        printf("���� <������ �˱�>�� ��� �߽��ϴ�.\n");
        d1s();
        swiftsword_eft();
        d1s();
        player_demage(com_att);
        d1s();
    }
    if (com_skill == 1) {
        printf("���� <Į�� ��>�� ��� �߽��ϴ�.\n");
        d1s();
        sworddance_eft();
        d1s();
        com_attup((com_att / 15));
        d1s();
    }
    if (com_skill == 2) {
        printf("���� <���� ����>�� ��� �߽��ϴ�.\n");
        d1s();
        armorbash_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_defdown(15);
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <����>�� ��� �߽��ϴ�.\n");
        d1s();
        bleedslash_eft();
        d1s();
        player_demage(com_att);
        d1s();
        printf("�� �ϸ��� ���������� ���ظ� �Խ��ϴ�. (�� 3ȸ)\n");
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
            printf(" ���� <������>�� ��� �߽��ϴ�.\n");
            d1s();
            triplespear_eft();
            d1s();
            printf("ġ��Ÿ�� �������ϴ�.\n");
            d1s();
            player_demage(com_att * 6);
            d1s();
        }
        else
        {
            printf("���� <������>�� ��� �߽��ϴ�.\n");
            d1s();
            triplespear_eft();
            d1s();
            player_demage(com_att * 3);
            d1s();
        }
    }
    if (com_skill == 1) {
        printf("���� <����>�� ��� �߽��ϴ�.\n");
        d1s();
        challenge_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_defdown(15);
        d1s();
    }
    if (com_skill == 2) {
        printf("���� <�ʽ´� �۾���>�� ��� �߽��ϴ�.\n");
        d1s();
        spearsweep_eft();
        d1s();
        player_demage(player_hp * 15 / 100);
        d1s();
        com_defup(10);
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <������ ���� ��>�� ��� �߽��ϴ�.\n");
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
    printf("���������� ���ظ� �Խ��ϴ�.\n");
    d1s();
    dote_eft();
    d1s();
    player_demage(a);
    d1s();
    all_set();
    return a;
}
void main(void) // ���� �Լ� ///////////////////////////////////////////////////////////////////////////////////////////////////////
{
    setcursortype(NOCURSOR);
    
    window();
    gotoxy(24, 2);
    printf("         �������� ����\n");
    gotoxy(24, 3);
    printf("           Ver 1.0\n");
    gotoxy(50, 20);
    printf("Made by cd991478 / �鼺��\n");
    gotoxy(22, 14);
    printf("   �����Ϸ��� �ƹ� Ű�� ��������.\n");
    gotoxy(50, 18);
    printf("  cd991478@naver.com\n");
    _getch();
    item_att = &player_att;
    item_mp = &player_maxmp;
    for (;;) // �ݺ� ����
    {
        randomize();
        menu_fight = 0;
        menu_stat = 0;
        menu_skill = 0;
        menu_item = 0;
        system("cls");
        menu_choose(); // ���� �޴� ȣ��
        choose = _getch(); // �޴� ���� ��ư
        if (choose == 0x31) { // �޴����� 1. ���� �Է½�
            total = win + lose;
            menu_fight = 1;
            stat_restore();
            stat_over();
            system("cls");
            printf("������������������������������������������������������������������������������������������������������������      \n");
            printf("��   <<<�������� ��ȣ�� �Է��ϰ� ���͸� ��������>>>   ��   \n");
            printf("��            1-10 �������� ���� ������,              ��    \n");
            printf("�� %d �������� Ŭ����� �� ���� �������� �÷��� ����.      \n", stage_level);
            printf("��      (���� �޴��� ���ư����� ���� 0�� �Է�)        ��      \n");
            printf("������������������������������������������������������������������������������������������������������������   \n");
            if (win >= 1 || lose >= 1)
            {
                printf("      %d�� %d��   �·� : %.2f %%  ���� : %d\n", win, lose, (float)win * 100 / (float)total, rating);
            }
            if (total < 3)
            {
                printf("              ���� ��� : Unranked\n");
                printf("       �ּ� 3���� �Ұ�� ����� ���� �޽��ϴ�.\n");
            }
            if (total >= 3)
            {
                if (rating < 1000) {
                    strcpy(rank, "Bronze ��");
                }
                if (rating >= 1000 && rating < 1050) {
                    strcpy(rank, "Silver ��");
                }
                if (rating >= 1050 && rating < 1100) {
                    strcpy(rank, "Gold ��");
                }
                if (rating >= 1100 && rating < 1200) {
                    strcpy(rank, "Platinum ��");
                }
                if (rating >= 1200 && rating < 1250) {
                    strcpy(rank, "Diamond ��");
                }
                if (rating >= 1250) {
                    strcpy(rank, "Master ��");
                }
                printf("                  ���� ��� : %s\n", rank);
            }
            gotoxy(53, 3);
            puts("��");
            gotoxy(0, 10);
            scanf_s("%d", &goto_stage);
            if (stage_level < goto_stage)
            {
                printf("�ش� ���������� ���� �÷��� �� �� �����ϴ�.\n");
                printf("     ��� �Ϸ��� �ƹ� Ű�� ��������.\n");
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
                printf("    �߸� �Է� �Ͽ����ϴ�\n");
                d1s();
                printf("��� �Ϸ��� �ƹ� Ű�� ��������.\n");
                _getch();
                continue;
            }
            turn = 0;
            stat_restore();
            for (;;) // ���� �ݺ�
            {
                all_set();
                if (player_dotecount > 0) // ��Ʈ ������
                {
                    player_doteon(com_att);
                }
                if (turn % 2 == 0 && player_hp > 0 && player_stun == 0) {
                    for (;;) {
                        printf("      ����� ���Դϴ�!\n");
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
                    printf("       ���� ���Դϴ�.\n");
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
                    printf("ü���� 0�� �Ǿ� ���������ϴ�.\n");
                    delay(2000);
                    system("cls");
                    window();
                    gotoxy(20, 9);
                    printf("    << �й� �Ͽ����ϴ� >>\n");
                    lose++;
                    rating = rating - (stage_level - goto_stage) - 21;
                    if (player_maxhp >= 150 && player_maxmp >= 150)
                    {
                        gotoxy(20, 10);
                        printf("      �ɷ�ġ�� �����մϴ�.\n");
                        player_maxhp = player_maxhp - 10;
                        player_maxmp = player_maxmp - 10;
                    }
                    gotoxy(20, 13);
                    printf("��� �Ϸ��� �ƹ� Ű�� ��������.\n");
                    _getch();
                    break;
                }
                if (com_hp <= 0 && stage_level == goto_stage)
                {
                    all_set();
                    printf("���� ���������ϴ�.\n");
                    gotoxy(50, 16);
                    puts("   ");
                    gotoxy(50, 16);
                    puts("OTL");
                    delay(2000);
                    system("cls");
                    printf("\n");
                    gotoxy(20, 9);
                    printf("         << �¸� �Ͽ����ϴ�! >>\n");
                    win++;
                    rating = rating + 21;
                    gotoxy(20, 10);
                    player_exp = player_exp + (goto_stage * 100);
                    printf("      ����ġ�� %d ��ŭ ������ϴ�.\n", goto_stage * 100);
                    gotoxy(20, 11);
                    player_gold = player_gold + (goto_stage * 500);
                    printf("       ��带 %d ��ŭ ������ϴ�.\n", goto_stage * 500);
                    level_up(player_exp);
                    gotoxy(20, 12);
                    printf("   ���� ���������� ���� �� �� �ֽ��ϴ�.\n");
                    gotoxy(20, 13);
                    printf("     ��� �Ϸ��� �ƹ� Ű�� ��������.\n");
                    window();
                    stage_level = stage_level + 1;
                    _getch();
                    break;
                }
                if (com_hp <= 0 && stage_level > goto_stage)
                {
                    printf("���� ���������ϴ�.\n");
                    gotoxy(50, 16);
                    puts("   ");
                    gotoxy(50, 16);
                    puts("OTL");
                    delay(2000);
                    system("cls");
                    window();
                    gotoxy(20, 9);
                    printf("     �¸� �Ͽ����ϴ�!\n");
                    win++;
                    rating = rating + goto_stage;
                    gotoxy(20, 10);
                    player_exp = player_exp + (goto_stage * 80);
                    printf(" ����ġ�� %d ��ŭ ������ϴ�.\n", goto_stage * 80);
                    gotoxy(20, 11);
                    player_gold = player_gold + (goto_stage * 300);
                    printf("  ��带 %d ��ŭ ������ϴ�.\n", goto_stage * 300);
                    level_up(player_exp);
                    gotoxy(20, 12);
                    printf("��� �Ϸ��� �ƹ� Ű�� ��������.\n");



                    _getch();
                    break;
                }
                if (player_dotecount > 0) {
                    player_dotecount = player_dotecount - 1;
                }
            }
        }
        if (choose == 0x32 && player_statpoint > 0) { // �޴����� 2. ���� �Է½� (���� o)
            menu_stat = 1;
            system("cls");
            stat_restore();
            playerstat_message();
            statchoose_message();
            printf("���� ���� ����Ʈ : %d\n", player_statpoint);
            stat_up = _getch(); // ���ϴ� ���� ����
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
                    printf(" ������ 100�� ���� �� �����ϴ�.\n");
                }
                printf(" ����Ϸ��� �ƹ�Ű�� ��������\n");
                defover_state = 0;
                _getch();

                continue;
            }


        }
        if (choose == 0x32 && player_statpoint == 0) { // �޴����� 2. ���� �Է½� (���� x)
            system("cls");
            stat_restore();
            playerstat_message();
            printf("���� ����Ʈ�� �����ϴ�.\n");
            _getch();
        }
        if (choose == 0x33 && player_skillpoint > 0) { // �޴����� 3. ��ų �Է½� (���� o)
            menu_skill = 1;
            system("cls");
            skillchoose_message();
            printf("���� ��ų ����Ʈ : %d\n", player_skillpoint);
            skill_up = _getch();
            if (skill_up == 0x31 || skill_up == 0x32 || skill_up == 0x33 || skill_up == 0x34 || skill_up == 0x35) {
                player_skillpoint = player_skillpoint - 1; // ����Ʈ 1 ����
                choose = NULL;
            }
            if (skill_up == 0x31 && player_skill1 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("�ش� ��ų�� �̹� �ִ� ���� �Դϴ�.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x32 && player_skill2 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("�ش� ��ų�� �̹� �ִ� ���� �Դϴ�.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x33 && player_skill3 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("�ش� ��ų�� �̹� �ִ� ���� �Դϴ�.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x34 && player_skill4 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("�ش� ��ų�� �̹� �ִ� ���� �Դϴ�.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x35 && player_skill5 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("�ش� ��ų�� �̹� �ִ� ���� �Դϴ�.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x31 && player_skill1 < 5) {
                player_skill1 = player_skill1 + 1; // ��ų 1�� ��
            }


            if (skill_up == 0x32 && player_skill2 < 5) {
                player_skill2 = player_skill2 + 1; // ��ų 2�� ��
            }

            if (skill_up == 0x33 && player_skill3 < 5) {
                player_skill3 = player_skill3 + 1; // ��ų 3�� ��
            }

            if (skill_up == 0x34 && player_skill4 < 5) {
                player_skill4 = player_skill4 + 1; // ��ų 4�� ��
            }

            if (skill_up == 0x35 && player_skill5 < 5) {
                player_skill5 = player_skill5 + 1; // ��ų 5�� ��
            }

            if (skill_up == 0x31 || skill_up == 0x32 || skill_up == 0x33 || skill_up == 0x34 || skill_up == 0x35) {
                system("cls");
                skillchoose_message();
                printf("��ų ������ �ö����ϴ�. ��� �Ϸ��� �ƹ� Ű�� ��������.\n");
                _getch();
            }

        }
        if (choose == 0x33 && player_skillpoint == 0) { // �޴����� 3. ��ų �Է½� (���� x) 
            system("cls");
            skillchoose_message();
            printf("��ų ����Ʈ�� �����ϴ�.\n");
            _getch();
        }
        if (choose == 0x34) { // �޴����� 4. ���� �Է½�
            menu_item = 1;
            for (;;)
            {
                system("cls");
                printf("���������������������������������������������������������������������������������������������������������������� \n");
                printf("��                 <<< ���� ���� >>>                    ��   \n");
                if (item_code == 0)
                    printf("��             ���� �������� ���� : ����                ��  \n");
                if (item_code == 1)
                    printf("��           ���� �������� ���� : ������ ��           ��  \n");
                if (item_code == 2)
                    printf("��          ���� �������� ���� : ������ ������          ��   \n");
                if (item_code == 3) {
                    printf("��          ���� �������� ���� : ������ ������          ��    \n");
                }
                printf("����������������������������������������������������������������������������������������������������������������     \n");
                printf("                ���� ������ ��� : %d                       \n", player_gold);
                printf("����������������������������������������������������������������������������������������������������������������   \n");
                printf("�� 1. ������ ��    (���ݷ� 20 ���� 400 / 10000���)   �� \n");
                printf("�� 2. ������ ������  (���ݷ� 80 ���� 100 / 10000���)   �� \n");
                printf("�� 3. ������ ������  (���ݷ� 60 ���� 300 / 14000���)   ��  \n");
                printf("�� 4. ���� ���� ���� (���� ������ ����� �Ҹ�)          ��   \n");
                printf("����������������������������������������������������������������������������������������������������������������    \n");
                printf("��     �������� ���� �Ϸ��� �ش� ���ڸ� �����ּ���.     ��     \n");
                printf("��           �޴��� ���ư����� ���� 0�� �Է�            ��    \n");
                printf("����������������������������������������������������������������������������������������������������������������   \n");
                item_choose = _getch();
                if (item_choose == 0x31)
                {
                    if (player_gold >= 10000 && item_code == 0)
                    {
                        printf("������ ���� ���� �߽��ϴ�.\n");
                        item_code = 1;
                        *item_att = player_att + 20;
                        *item_mp = player_maxmp + 400;
                        player_gold = player_gold - 10000;
                        printf("��� �Ϸ��� �ƹ� Ű�� ��������.\n");
                        _getch();
                        break;
                    }
                    else
                    {
                        printf("���� �Ұ���! ��� ���� Ȥ�� ���� ���� ���� �� ��õ� �ϼ���\n");
                        _getch();
                    }
                }
                if (item_choose == 0x32)
                {
                    if (player_gold >= 10000 && item_code == 0)
                    {
                        printf("������ �������� ���� �߽��ϴ�.\n");
                        item_code = 2;
                        *item_att = player_att + 80;
                        *item_mp = player_maxmp + 100;
                        player_gold = player_gold - 10000;
                        printf("��� �Ϸ��� �ƹ� Ű�� ��������.\n");
                        _getch();
                        break;
                    }
                    else
                    {
                        printf("���� �Ұ���! ��� ���� Ȥ�� ���� ���� ���� �� ��õ� �ϼ���\n");
                        _getch();
                    }
                }
                if (item_choose == 0x33)
                {
                    if (player_gold >= 14000 && item_code == 0)
                    {
                        printf("������ �����̸� ���� �߽��ϴ�.\n");
                        item_code = 3;
                        *item_att = player_att + 60;
                        *item_mp = player_maxmp + 300;
                        player_gold = player_gold - 14000;
                        printf("��� �Ϸ��� �ƹ� Ű�� ��������.\n");
                        _getch();
                        break;
                    }
                    else
                    {
                        printf("���� �Ұ���! ��� ���� Ȥ�� ���� ���� ���� �� ��õ� �ϼ���\n");
                        _getch();
                    }
                }
                if (item_choose == 0x34)
                {
                    if (item_code == 1)
                    {
                        printf("���� ���� ���� �Ϸ�.\n");
                        item_code = 0;
                        *item_att = player_att - 20;
                        *item_mp = player_maxmp - 400;
                    }
                    if (item_code == 2)
                    {
                        printf("���� ���� ���� �Ϸ�.\n");
                        item_code = 0;
                        *item_att = player_att - 80;
                        *item_mp = player_maxmp - 100;
                    }
                    if (item_code == 3)
                    {
                        printf("���� ���� ���� �Ϸ�.\n");
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
                printf("��������������������������������������������������������������������������������     \n");
                printf("�� ġƮ �ڵ带 �Է��ϼ���. (���� 4�ڸ�) ��    \n");
                printf("��    �޴��� �������� ���� 0�� �Է�     ��      \n");
                printf("��������������������������������������������������������������������������������    \n");
                scanf_s("%d", &cheat);
                if (cheat == 1234)
                {
                    printf("ü���� 100 �����մϴ�!\n");
                    player_maxhp = player_maxhp + 100;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("������ 100 �����մϴ�!\n");
                    player_maxmp = player_maxmp + 100;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("���ݷ��� 20 �����մϴ�!\n");
                    player_att = player_att + 20;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("������ 10 �����մϴ�!\n");
                    player_defmain = player_defmain + 10;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("��尡 2000 ���� �մϴ�!\n");
                    player_gold = player_gold + 2000;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("���� ����Ʈ�� 1 �����մϴ�!\n");
                    player_statpoint = player_statpoint + 1;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("��ų ����Ʈ�� 1 �����մϴ�!\n");
                    player_skillpoint++;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("�������� ������ 10���� ���� �Ǿ����ϴ�!\n");
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
                    printf("�߸��� ġƮ �ڵ� �Դϴ�\n");
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
            printf("����������������������������������������������������������������������������������������������������������������  \n");
            printf("��               ���� �ӵ��� �Է��ϼ���.                    \n");
            printf("��  * ����Ʈ�� ������ ��Ȳ�� �޼��� �ӵ��� ����˴ϴ�.           \n");
            printf("��   ���ڰ� �������� �����ϴ�. �޴��� ������ 0�� �Է�.            \n");
            printf("��             ���� �ӵ� : %d ( ���� 500-800 )                             \n", speed);
            printf("���������������������������������������������������������������������������������������������������������������� \n");
            gotoxy(55, 1);
            puts("��");
            gotoxy(55, 2);
            puts("��");
            gotoxy(55, 3);
            puts("��");
            gotoxy(55, 4);
            puts("��");
            gotoxy(0, 6);
            scanf_s("%d", &speed);
            if (speed == 0)
            {
                speed = temp_speed;
            }
            else if (speed < 100)
            {
                speed = temp_speed;
                printf("�ּ� 100 ���� ���� �մϴ�.\n");
                _getch();
                continue;
            }
            else if (speed > 2000)
            {
                speed = temp_speed;
                printf("�ִ� 2000 ���� ���� �մϴ�.\n");
                _getch();
                continue;
            }
            else if (speed >= 100 && speed <= 2000)
            {
                printf("������ �Ϸ� �Ǿ����ϴ�.\n");
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
            printf("                  <����>\n");
            gotoxy(16, 2);
            printf(" �� ������ 1�ܰ��� ������ ���ʴ�� �ο�����\n");
            gotoxy(16, 3);
            printf("     ���� ���� ���Ͽ� �ɷ��� ��ȭ����\n");
            gotoxy(16, 4);
            printf(" 10�ܰ��� ������ ����� ���� ��ǥ �Դϴ�.\n");
            gotoxy(16, 6);
            printf("        �� ������ ���� ����̸�\n");
            gotoxy(16, 8);
            printf("  ���� 4���� ����� �������� ��� �մϴ�.\n");
            gotoxy(16, 10);
            printf("  ���� ���� �����ϴ� ���������� ��ƴٸ� \n");
            gotoxy(16, 12);
            printf(" �� ���� ������������ ���� ���� �غ�����.\n");
            gotoxy(16, 14);
            printf("       �� ������ �� �ٽ� ������ ���\n");
            gotoxy(16, 16);
            printf("�ξ� �� ���� ���������� Ŭ���� �� �� �����̴ϴ�.\n");
            _getch();
        }
        if (choose == 0x38)
        {
            system("cls");
            printf("���Ӹ�    : �������� ����\n");
            printf("�帣      : �� ��� �̱� �÷��� RPG ����");
            printf("����      : 1.0\n");
            printf("ȯ��      : ������ 7 32��Ʈ\n");
            printf("��ȹ      : �鼺��\n");
            printf("������    : �鼺��\n");
            printf("��        : Microsoft Visual C++ 2010 Express\n");
            printf("���� �Ϸ� : 2014/6/16\n");
            printf("���� �Ⱓ : �ð� ���´�� ����.\n");
            printf("�̸���    : cd991478@naver.com\n");
            printf("�Ѹ���    : �ʺ����̶� ���������� ���� ������� �Ф�\n");
            printf("\n");
            _getch();
        }
    } // for(;;)
} // int main(void)