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
    // 夔樂 �飛� 幗ぷ 觼晦 撲薑
    COORD bufferSize = { width, height };
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);

    // 夔樂 璽 觼晦 撲薑
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
char stage01[] = { "辨煽" };
char stage02[] = { "瞪餌" };
char stage03[] = { "盪問熱" };
char stage04[] = { "橡擠 葆徹餌" };
char stage05[] = { "廓偃 葆徹餌" };
char stage06[] = { "�倍� 葆徹餌" };
char stage07[] = { "繭奢 葆徹餌" };
char stage08[] = { "懍�� 葆徹餌" };
char stage09[] = { "匐偌" };
char stage10[] = { "璽曖 殖檣" };
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
    puts("褡");
    gotoxy(50, 16);
    puts("褡");
    gotoxy(0, 18);
    printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
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
    puts("褡");
    gotoxy(28, 16);
    puts("褡");
    gotoxy(0, 18);
    printf("式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式\n");
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
    puts("弛");
    delay(100);
    gotoxy(22, 17);
    puts("戎");
    delay(100);
    gotoxy(20, 17);
    puts("式式");
    delay(100);
    gotoxy(18, 17);
    puts("戌");
    delay(100);
    gotoxy(18, 16);
    puts("弛");
    delay(100);
    gotoxy(18, 15);
    puts("忙");
    delay(100);
    gotoxy(20, 15);
    puts("式式");
    delay(100);
    gotoxy(22, 15);
    puts("忖");
    delay(100);
    char_set();
    gotoxy(22, 16);
    puts("﹥");
    gotoxy(22, 17);
    puts("﹥");
    gotoxy(20, 17);
    puts("﹥");
    gotoxy(18, 17);
    puts("﹥");
    gotoxy(18, 16);
    puts("﹥");
    gotoxy(18, 15);
    puts("﹥");
    gotoxy(20, 15);
    puts("﹥");
    gotoxy(22, 15);
    puts("﹥");
    delay(100);
    char_set();
}
void comdfup_eft()
{
    gotoxy(52, 16);
    puts("弛");
    delay(100);
    gotoxy(52, 17);
    puts("戎");
    delay(100);
    gotoxy(50, 17);
    puts("式式");
    delay(100);
    gotoxy(48, 17);
    puts("戌");
    delay(100);
    gotoxy(48, 16);
    puts("弛");
    delay(100);
    gotoxy(48, 15);
    puts("忙");
    delay(100);
    gotoxy(50, 15);
    puts("式式");
    delay(100);
    gotoxy(52, 15);
    puts("忖");
    delay(100);
    char_set();
    gotoxy(52, 16);
    puts("﹥");
    gotoxy(52, 17);
    puts("﹥");
    gotoxy(50, 17);
    puts("﹥");
    gotoxy(48, 17);
    puts("﹥");
    gotoxy(48, 16);
    puts("﹥");
    gotoxy(48, 15);
    puts("﹥");
    gotoxy(50, 15);
    puts("﹥");
    gotoxy(52, 15);
    puts("﹥");
    delay(100);
    eft_set();
}
void playerboom_eft()
{
    gotoxy(18, 15);
    puts("≦");
    gotoxy(22, 17);
    puts("≦");
    gotoxy(18, 17);
    puts("≦");
    gotoxy(22, 15);
    puts("≦");
    gotoxy(20, 17);
    puts("≦");
    gotoxy(18, 16);
    puts("≦");
    gotoxy(20, 15);
    puts("≦");
    gotoxy(22, 16);
    puts("≦");
    delay(200);
    eft_set();
}
void playerfreeze_eft()
{
    gotoxy(18, 15);
    puts("﹢");
    gotoxy(22, 17);
    puts("﹢");
    gotoxy(18, 17);
    puts("﹢");
    gotoxy(22, 15);
    puts("﹢");
    gotoxy(20, 17);
    puts("﹢");
    gotoxy(18, 16);
    puts("﹢");
    gotoxy(20, 15);
    puts("﹢");
    gotoxy(22, 16);
    puts("﹢");
    delay(200);
    eft_set();
}
void playerthunder_eft()
{
    gotoxy(18, 15);
    puts("≧");
    gotoxy(22, 17);
    puts("≧");
    gotoxy(18, 17);
    puts("≧");
    gotoxy(22, 15);
    puts("≧");
    gotoxy(20, 17);
    puts("≧");
    gotoxy(18, 16);
    puts("≧");
    gotoxy(20, 15);
    puts("≧");
    gotoxy(22, 16);
    puts("≧");
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
    puts("忙");
    gotoxy(78, 0);
    puts("忖");
    gotoxy(0, 22);
    puts("戌");
    gotoxy(78, 22);
    puts("戎");
    for (x = 2; x < 78; x = x + 2)
    {
        gotoxy(x, 0);
        puts("式式");
        gotoxy(x, 22);
        puts("式式");
    }
    for (y = 1; y < 22; y++)
    {
        gotoxy(0, y);
        puts("弛");
        gotoxy(78, y);
        puts("弛");
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
        puts("褡");
        delay(10);
        if (k != 28)
        {
            gotoxy(k, 16);
            puts("﹛");
        }
    }
}
void back_eft()
{
    int k;
    for (k = 27; k < 50; k++)
    {
        gotoxy(k, 16);
        puts("褡");
        delay(10);
        gotoxy(k, 16);
        puts("﹛");
    }
}
void skill0_eft()
{
    int k;
    for (k = 22; k < 49; k++)
    {
        gotoxy(k, 16);
        puts("⊥");
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
            puts("≒");
            delay(t);
            gotoxy(k, 16);
            puts(" ");
        }
        if (k % 2 == 1)
        {
            gotoxy(k, 16);
            puts("≡");
            delay(t);
            gotoxy(k, 16);
            puts(" ");
        }
    }
    if (player_skill1 == 1)
    {
        gotoxy(48, 16);
        puts("≦");
        gotoxy(48, 15);
        puts("≦");
        gotoxy(48, 17);
        puts("≦");
        gotoxy(50, 16);
        puts("≦");
        gotoxy(52, 16);
        puts("≦");
        gotoxy(50, 15);
        puts("≦");
        gotoxy(50, 17);
        puts("≦");
        gotoxy(52, 17);
        puts("≦");
        gotoxy(52, 15);
        puts("≦");
        delay(100);
    }
    if (player_skill1 >= 2)
    {
        gotoxy(48, 17);
        puts("≦");
        delay(20);
        gotoxy(50, 17);
        puts("≦");
        delay(20);
        gotoxy(52, 17);
        puts("≦");
        delay(20);
        gotoxy(48, 16);
        puts("≦");
        delay(20);
        gotoxy(50, 16);
        puts("≦");
        delay(20);
        gotoxy(52, 16);
        puts("≦");
        delay(20);
        gotoxy(48, 15);
        puts("≦");
        delay(20);
        gotoxy(50, 15);
        puts("≦");
        delay(20);
        gotoxy(52, 15);
        puts("≦");
        delay(50);
        char_set();
        delay(50);
        gotoxy(48, 16);
        puts("≦");
        gotoxy(48, 15);
        puts("≦");
        gotoxy(48, 17);
        puts("≦");
        gotoxy(50, 16);
        puts("≦");
        gotoxy(52, 16);
        puts("≦");
        gotoxy(50, 15);
        puts("≦");
        gotoxy(50, 17);
        puts("≦");
        gotoxy(52, 17);
        puts("≦");
        gotoxy(52, 15);
        puts("≦");
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
        puts("ㄞ");
        delay(t);

        gotoxy(k + 2, 16);
        puts("′");
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
            puts("′");
            gotoxy(k + 2, 16);
            puts("ㄞ");
            k = k + 2;
        }
        gotoxy(48, 16);
        puts("≧");
        gotoxy(48, 15);
        puts("≧");
        gotoxy(48, 17);
        puts("≧");
        gotoxy(50, 16);
        puts("≧");
        gotoxy(52, 16);
        puts("≧");
        gotoxy(50, 15);
        puts("≧");
        gotoxy(50, 17);
        puts("≧");
        gotoxy(52, 17);
        puts("≧");
        gotoxy(52, 15);
        puts("≧");

        delay(t * 2);
        char_set();
        for (k = 22; k < 49; k = k + 2)
        {
            gotoxy(k, 16);
            puts("ㄞ");
            gotoxy(k + 2, 16);
            puts("′");
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
        puts("Ｐ");
        delay(20);
        gotoxy(k, 16);
        puts(" ");
    }
    playerboom_eft();
}
void sword_eft()
{
    gotoxy(50, 15);
    puts("ㄞ");
    delay(50);
    char_set();
    gotoxy(48, 15);
    puts("′");
    delay(50);
    char_set();
    gotoxy(48, 16);
    puts("式式");
    delay(50);
    char_set();
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("ㄞ");
        delay(10);
        gotoxy(k, 16);
        puts(" ");
    }
    eft_set();
}
void roar_eft()
{
    gotoxy(48, 15);
    puts("′");
    gotoxy(48, 16);
    puts("式式");
    gotoxy(48, 17);
    puts("ㄞ");
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
    puts("ㄞ");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("ㄞ");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("ㄞ");
    delay(100);
    gotoxy(18, 15);
    puts("′");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("′");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("′");
    delay(100);
    move_set();
    gotoxy(22, 15);
    puts("ㄞ");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("ㄞ");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("ㄞ");
    delay(100);
    gotoxy(18, 15);
    puts("′");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("′");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("′");
    delay(100);
    move_set();
    gotoxy(22, 15);
    puts("ㄞ");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("ㄞ");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("ㄞ");
    delay(100);
    gotoxy(18, 15);
    puts("′");
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("′");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("′");
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
        puts("式式");
        delay(5);
        gotoxy(k, 16);
        puts(" ");
    }
    eft_set();
}
void focus_eft()
{
    gotoxy(48, 16);
    puts("∟");
    delay(100);
    char_set();
    gotoxy(48, 15);
    puts("∟");
    delay(100);
    char_set();
    gotoxy(52, 16);
    puts("∟");
    delay(100);
    char_set();
    gotoxy(52, 15);
    puts("∟");
    delay(100);
    char_set();
    gotoxy(48, 16);
    puts("∟");
    delay(100);
    char_set();
    gotoxy(48, 15);
    puts("∟");
    delay(100);
    char_set();
    gotoxy(52, 16);
    puts("∟");
    delay(100);
    char_set();
    gotoxy(52, 15);
    puts("∟");
    delay(100);
    eft_set();
}
void headshot_eft()
{
    int k;
    gotoxy(20, 15);
    puts("弛");
    gotoxy(20, 17);
    puts("弛");
    gotoxy(18, 16);
    puts("式式");
    gotoxy(22, 16);
    puts("式式");
    delay(500);
    char_set();
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("式式");
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
        puts("﹢");
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
        puts("ㄞ");
        delay(20);
        gotoxy(k - 2, 16);
        puts("′");
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
            puts("ㄞ");
            gotoxy(k - 2, 16);
            puts("′");
            k = k - 2;
        }
        gotoxy(20, 15);
        puts("弛");
        gotoxy(22, 16);
        puts("式式");
        gotoxy(20, 17);
        puts("弛");
        gotoxy(18, 16);
        puts("式式");
        delay(50);
        char_set();
        for (k = 48; k > 21; k = k - 2)
        {
            gotoxy(k, 16);
            puts("′");
            gotoxy(k - 2, 16);
            puts("ㄞ");
            k = k - 2;
        }
        gotoxy(22, 15);
        puts("ㄞ");
        gotoxy(22, 17);
        puts("′");
        gotoxy(18, 17);
        puts("ㄞ");
        gotoxy(18, 15);
        puts("′");
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
        puts("＝");
        delay(20);
    }
    char_set();
    for (t = 0; t < 4; t++)
    {
        for (k = 48; k > 21; k = k - 4)
        {
            gotoxy(k, 16);
            puts("＝");
        }
        playerboom_eft();
        delay(50);
        char_set();
        for (k = 46; k > 21; k = k - 4)
        {
            gotoxy(k, 16);
            puts("＝");
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
        puts("卄");
        delay(200);
        char_set();
        gotoxy(48, 15);
        puts("卄");
        gotoxy(52, 15);
        puts("卄");
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
        puts("≡");
        delay(50);
        move_set();
        gotoxy(24, 16);
        puts("≡");
        delay(50);
        move_set();
        gotoxy(22, 16);
        puts("≡");
        delay(50);
        move_set();
        gotoxy(18, 17);
        puts("卄");
        gotoxy(20, 17);
        puts("卄");
        gotoxy(22, 17);
        puts("卄");
        delay(20);
        move_set();
        gotoxy(18, 16);
        puts("卄");
        gotoxy(22, 16);
        puts("卄");
        delay(20);
        move_set();
        gotoxy(18, 15);
        puts("卄");
        gotoxy(20, 15);
        puts("卄");
        gotoxy(22, 15);
        puts("卄");
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
            puts("≡");
            gotoxy(k - 2, 15);
            puts("≡");
            gotoxy(k - 4, 15);
            puts("≡");
            gotoxy(k, 16);
            puts("≡");
            gotoxy(k - 2, 16);
            puts("≡");
            gotoxy(k - 4, 16);
            puts("≡");
            gotoxy(k, 17);
            puts("≡");
            gotoxy(k - 2, 17);
            puts("≡");
            gotoxy(k - 4, 17);
            puts("≡");
            delay(20);
            char_set();
        }
        if (k % 2 == 1)
        {
            gotoxy(k, 15);
            puts("≒");
            gotoxy(k - 2, 15);
            puts("≒");
            gotoxy(k - 4, 15);
            puts("≒");
            gotoxy(k, 16);
            puts("≒");
            gotoxy(k - 2, 16);
            puts("≒");
            gotoxy(k - 4, 16);
            puts("≒");
            gotoxy(k, 17);
            puts("≒");
            gotoxy(k - 2, 17);
            puts("≒");
            gotoxy(k - 4, 17);
            puts("≒");
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
            puts("ㄙ");
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
        puts("≒");
        delay(20);
    }
    gotoxy(22, 15);
    puts("≒");
    gotoxy(22, 16);
    puts("≒");
    gotoxy(22, 17);
    puts("≒");
    delay(100);
    gotoxy(20, 15);
    puts("≒");
    gotoxy(20, 16);
    puts("≒");
    gotoxy(20, 17);
    puts("≒");
    delay(100);
    gotoxy(18, 15);
    puts("≒");
    gotoxy(18, 16);
    puts("≒");
    gotoxy(18, 17);
    puts("≒");
    delay(100);
    eft_set();
}
void silence_eft()
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("Ⅸ");
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
        puts("⊿");
        delay(100);
        char_set();
        gotoxy(18, 16);
        puts("⊿");
        delay(100);
        char_set();
        gotoxy(22, 15);
        puts("⊿");
        delay(100);
        char_set();
        gotoxy(22, 16);
        puts("⊿");
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
        puts("ㄞ");
        delay(20);
        gotoxy(46, 16);
        puts("ㄞ");
        delay(20);
        gotoxy(44, 17);
        puts("ㄞ");
        delay(20);
        char_set();
        delay(20);
        for (k = 42; k > 22; k = k - 2)
        {
            gotoxy(k, 15);
            puts("ㄞ");
            gotoxy(k - 2, 16);
            puts("ㄞ");
            gotoxy(k - 4, 17);
            puts("ㄞ");
            delay(10);
            char_set();
        }
        gotoxy(44, 15);
        puts("′");
        delay(20);
        gotoxy(46, 16);
        puts("′");
        delay(20);
        gotoxy(48, 17);
        puts("′");
        delay(20);
        char_set();
        delay(20);
        for (k = 44; k > 18; k = k - 2)
        {
            gotoxy(k, 15);
            puts("′");
            gotoxy(k + 2, 16);
            puts("′");
            gotoxy(k + 4, 17);
            puts("′");
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
        puts("弛");
        gotoxy(48, 16);
        puts("托");
        delay(200);
        char_set();
        gotoxy(52, 15);
        puts("弛");
        gotoxy(52, 16);
        puts("托");
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
        puts("′");
        delay(100);
        gotoxy(20, 16);
        puts("′");
        delay(100);
        gotoxy(22, 17);
        puts("′");
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
    puts("式式");
    delay(20);
    gotoxy(20, 16);
    puts("式式");
    delay(20);
    gotoxy(22, 16);
    puts("式式");
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
            puts("式式");
            gotoxy(26, 16);
            puts("式式");
            gotoxy(30, 16);
            puts("式式");
            delay(200);
            move_set();
        }
        gotoxy(22, 16);
        puts("式式");
        gotoxy(24, 16);
        puts("式式");
        gotoxy(26, 16);
        puts("式式");
        if (k == 2)
        {
            gotoxy(20, 16);
            puts(" ");
            gotoxy(20, 15);
            puts("褡");
        }
        delay(100);
        move_set();
    }
    gotoxy(24, 16);
    puts("式式");
    gotoxy(26, 16);
    puts("式式");
    gotoxy(30, 16);
    puts("式式");
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
        puts("㏑");
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
    puts("式式");
    gotoxy(26, 16);
    puts("式式");
    delay(30);
    move_set();
    gotoxy(26, 17);
    puts("ㄞ");
    delay(30);
    move_set();
    gotoxy(28, 17);
    puts("弛");
    delay(30);
    move_set();
    gotoxy(30, 17);
    puts("′");
    delay(30);
    move_set();
    gotoxy(30, 15);
    puts("式式");
    delay(20);
    move_set();
    gotoxy(30, 15);
    puts("ㄞ");
    delay(20);
    move_set();
    gotoxy(28, 15);
    puts("弛");
    delay(20);
    move_set();
    gotoxy(26, 15);
    puts("′");
    delay(20);
    move_set();
    gotoxy(24, 16);
    puts("式式");
    gotoxy(26, 16);
    puts("式式");
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
    printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("弛               щ鼻 衛鑒 棟溘纂蒂 摹鷗 ж撮蹂.                    弛    \n");
    printf("弛   1.羹溘+50   2.葆釭+50   3.奢問溘+10   4.寞橫溘+5   5.鏃模      弛      \n");
    printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
} // 蝶囌 鬼�� �飛�
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
} // 蝶囌 隸陛
void playerstat_message()
{
    printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖\n");
    printf("弛       <<< 蝶囌 >>>              \n");
    printf("弛 霜機   : 葆徹餌               \n");
    printf("弛 溯漣   : %d                     \n", player_level);
    printf("弛 羹溘   : %d / %d               \n", player_hp, player_maxhp);
    printf("弛 葆釭   : %d / %d             \n", player_mp, player_maxmp);
    printf("弛 奢問溘 : %d                  \n", player_att);
    printf("弛 寞橫溘 : %d                 \n", player_defmain);
    printf("弛 唳я纂 : %d / %d (%.2f %%) \n", player_exp, player_maxexp, (float)player_exp / (float)player_maxexp * 100);
    printf("弛 爾嶸и 埤萄 : %d           \n", player_gold);
    printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    int k;
    for (k = 1; k < 10; k++)
    {
        gotoxy(29, k);
        puts("弛");
    }
    gotoxy(0, 11);
   
} // 蝶囌 �飛� 蝶囌 薑爾
void comstat_message()
{
    printf("  <<<瞳>>>\n");
}
void menu_choose()
{
    printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖   \n");
    printf("弛                         鼠歙擊 ж衛啊蝗棲梱?                       弛 \n");
    printf("弛  1.瞪癱  2.蝶囌  3.蝶鑒  4.鼠晦  5.纂お  6.撲薑  7.紫遺蜓  8.薑爾  弛  \n");
    printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎    \n");
    if (stage_level >= 11)
    {
        printf("   蹴ж萄董棲棻! 賅萇 蝶纔檜雖蒂 贗葬橫 ж艘蝗棲棻.\n");
        printf("     縛註 囀萄蒂 �挫� ж溥賊 璋濠 0擊 援腦撮蹂.\n");
    }
    if (player_statpoint > 0)
    {
        printf("\n      * 餌辨ж雖 彊擎 蝶囌 ん檣お陛 陴嬴 氈蝗棲棻.\n");
    }
    if (player_skillpoint > 0)
    {
        printf("\n      * 餌辨ж雖 彊擎 蝶鑒 ん檣お陛 陴嬴 氈蝗棲棻.\n");
    }
    if (player_gold >= 10000 && item_code != 3)
    {
        printf("\n      * 埤萄陛 號檜 賅艘蝗棲棻. 鼠晦蒂 雜辨 п爾撮蹂.\n");
    }
} // 詭檣 詭景 �飛�
int skill_1()
{
    //だ檜橫獐
    int d;
    d = (player_level * 10) + (player_att / 2) + (player_skill1 * 20);
    return d;
}
int skill_2()
{
    //賬渦獐お
    int d;
    d = (player_level * 9) + (player_att / 2) + (player_skill2 * 18);
    return d;
}
int skill_3()
{
    //聽橫
    int d;
    d = (player_level * 10) + (player_skill3 * 15) + (player_maxhp / 20) + (player_maxmp / 20);
    return d;
}
int skill_4()
{
    //陛萄 機
    int d;
    d = (player_skill4 * 2) + (player_maxhp / 100);
    return d;
}
int skill_5()
{
    //詭蛤纔檜暮
    int d;
    d = 45 + (player_skill5 * 5) + (player_maxhp / 100);
    return d;
}
void skillchoose_message() // 蝶鑒 摹鷗 詭撮雖
{
    printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖   \n");
    printf("弛                <<< 鬼�倆� 蝶鑒擊 摹鷗ж撮蹂 >>>                  弛  \n");
    printf("弛 1. だ檜橫 獐 (%d溯漣/5)                                           弛\n", player_skill1);
    printf("弛   - 瞳擊 奢問ж罹 %d虜躑曖 Яп蒂 殮��(+20)                        \n", skill_1());
    printf("弛                                                                  弛  \n");
    printf("弛 2. 賬渦 獐お (%d溯漣/5)                                           弛   \n", player_skill2);
    printf("弛   - 瞳縑啪 %d虜躑曖 Яп蒂 殮�鱁�, 寞橫溘擊 %d 馬模衛霽(+18,+2)     \n", skill_2(), player_skill2 * 2);
    printf("弛                                                                  弛  \n");
    printf("弛 3. 聽橫 (%d溯漣/5)                                                弛   \n", player_skill3);
    printf("弛   - 濠褐曖 羹溘擊 %d虜躑 �蛹嘎�(+15)                               \n", skill_3());
    printf("弛                                                                  弛 \n");
    printf("弛 4. 陛萄 機 (%d溯漣/5)                                             弛  \n", player_skill4);
    printf("弛   - 瞪癱翕寰 濠褐曖 寞橫溘擊 %d虜躑 隸陛 衛霽(+2)                   \n", skill_4());
    printf("弛                                                                  弛  \n");
    printf("弛 5. 詭蛤纔檜暮 (%d溯漣/5)                                          弛  \n", player_skill5);
    printf("弛   - ⑷營 羹溘曖 40%%蒂 模賅ж罹 譆渠 葆釭曖 %d%% 葆釭蒂 �蛹�(+5%%)     \n", skill_5());
    printf("弛                                                                  弛  \n");
    printf("弛 6. 詭景煎 給嬴陛晦                                               弛   \n");
    printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎    \n");
    gotoxy(67, 3);
    puts("弛");
    gotoxy(67, 6);
    puts("弛");
    gotoxy(67, 9);
    puts("弛");
    gotoxy(67, 12);
    puts("弛");
    gotoxy(67, 15);
    puts("弛");
    gotoxy(0, 19);
}
void stat_restore() // Ы溯檜橫 蝶囌 蟾晦��
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
void stat_over() // 蝶囌 螃幗衛 營撲薑
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
int stage_name(int a) // 蝶纔檜雖 檜葷 轎溘
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
void fight_stat() // 瞪癱衛 蝶囌 �飛�
{
    printf("忙式式式式式式<Ы溯檜橫>式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式<瞳>式式式式式式式式式式式式式式式式式式忖\n");
    printf("弛   羹溘   : %d / %d                          羹溘 : %d / %d          \n", player_hp, player_maxhp, com_hp, com_maxhp);
    printf("弛   葆釭   : %d / %d                                                  \n", player_mp, player_maxmp);
    printf("弛   奢問溘 : %d                                 奢問溘 : %d           \n", player_att, com_att);
    printf("弛   寞橫溘 : %d                                  寞橫溘 : %d          \n", player_def + player_defup, com_def);
    gotoxy(75, 2);
    puts("弛");
    gotoxy(75, 3);
    puts("弛");
    gotoxy(75, 4);
    puts("弛");
    gotoxy(75, 5);
    puts("弛");
}
void fight_skill()
{
    printf("戍式式式式式式式式式式式式式式式式< 蝶鑒擊 餌辨ж溥賊 璋濠 幗が擊 援腦撮蹂 >式式式式式式式式式式式式式式式式扣\n");
    printf("弛     1.だ檜橫 獐 (20 葆釭) : %d 曖 Яп蒂 殮��                           \n", skill_1());
    printf("弛     2.賬渦 獐お (25 葆釭) : %d 曖 Яп蒂 殮�鱁�, 寞橫溘擊 %d 馬模衛霽    \n", skill_2(), player_skill2 * 2);
    printf("弛     3.聽橫      (30 葆釭) : 濠褐曖 羹溘擊 %d 虜躑 �蛹嘎�                 \n", skill_3());
    printf("弛     4.陛萄 機   (20 葆釭) : 濠褐曖 寞橫溘擊 %d 虜躑 隸陛衛霽             \n", skill_4());
    printf("弛     5.詭蛤纔檜暮 (0 葆釭) : 羹溘曖 40%%蒂 模賅ж罹 %d%%曖 葆釭 �蛹�     \n", skill_5());
    printf("弛     0.晦獄 奢問  (0 葆釭) : %d 曖 Яп蒂 殮�鱁� %d曖 葆釭 �蛹�          \n", player_att, player_att + (player_maxmp / 20));
    printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎\n");
    gotoxy(75, 7);
    puts("弛");
    gotoxy(75, 8);
    puts("弛");
    gotoxy(75, 9);
    puts("弛");
    gotoxy(75, 10);
    puts("弛");
    gotoxy(75, 11);
    puts("弛");
    gotoxy(75, 12);
    puts("弛");
}
int com_demage(int a)
{
    if (a > com_def) {
        printf("瞳檜 %d 虜躑曖 Яп蒂 嫡懊蝗棲棻. \n", a - com_def);
        com_hp = com_hp - (a)+com_def;
    }
    if (a <= com_def) {
        printf("瞳檜 1 虜躑曖 Яп蒂 嫡懊蝗棲棻.\n");
        com_hp = com_hp - 1;
    }

    return a;
}
int player_demage(int a)
{
    if (a > (player_def + player_defup)) {
        printf("%d 虜躑曖 Яп蒂 嫡懊蝗棲棻. \n", a - (player_def + player_defup));
        player_hp = player_hp - (a)+player_def + player_defup;
    }
    if (a <= (player_def + player_defup)) {
        printf("1 虜躑曖 Яп蒂 嫡懊蝗棲棻.\n");
        player_hp = player_hp - 1;
    }
    return a;
}
int player_hpdown(int a)
{
    printf("羹溘檜 %d 虜躑 馬模м棲棻. \n", a);
    player_hp = player_hp - a;
    return a;
}
int com_defup(int a)
{
    printf("瞳曖 寞橫溘檜 %d 虜躑 螢嫉蝗棲棻. \n", a);
    com_def = com_def + a;
    return a;
}
int com_defdown(int a)
{
    printf("瞳曖 寞橫溘檜 %d 虜躑 馬模 ц蝗棲棻. \n", a);
    com_def = com_def - a;
    return a;
}
int com_attup(int a)
{
    printf("瞳曖 奢問溘檜 %d 虜躑 隸陛 ц蝗棲棻. \n", a);
    com_att = com_att + a;
    return a;
}
int player_defdown(int a)
{
    printf("寞橫溘檜 %d 虜躑 馬模м棲棻.\n", a);
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
    printf("羹溘檜 %d 虜躑 �蛹� 腌棲棻.\n", a);
    player_hp = player_hp + a;
    return a;
}
int player_mplose(int a)
{
    printf("葆釭陛 %d 虜躑 馬模м棲棻.\n", a);
    player_mp = player_mp - a;
    return a;
}
int com_hpup(int a)
{
    if (a >= 0) {
        printf("瞳曖 羹溘檜 %d 虜躑 �蛹� 腌棲棻.\n", a);
        com_hp = com_hp + a;
    }
    if (a < 0) {
        printf("瞳曖 羹溘檜 1 虜躑 �蛹� 腌棲棻.\n");
        com_hp = com_hp + 1;
    }
    return a;
}
int player_mpup(int a)
{
    printf("葆釭陛 %d 虜躑 �蛹� 腌棲棻.\n", a);
    player_mp = player_mp + a;
    return a;
}
int player_mppup(int a)
{
    printf("葆釭陛 %d%% 虜躑 �蛹� 腌棲棻.\n", a);
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
    printf("葆釭陛 睡褶м棲棻.\n");
}
char player_skill(char a)
{
    if (a == 0x30) {
        printf("<0. 晦獄 奢問>擊 餌辨 ц蝗棲棻.\n");
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
        printf("<1. だ檜橫 獐>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        skill1_eft();
        d1s();
        if (goto_stage == 6)
        {
            printf("瞳擎 �倍� 樓撩縑 賊羲殮棲棻.\n");
            d1s();
            printf("Яп蒂 嫡雖 彊蝗棲棻.\n");
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
        printf("<2. 賬渦 獐お>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        skill2_eft();
        d1s();
        if (goto_stage == 5)
        {
            printf("瞳擎 廓偃 樓撩縑 賊羲殮棲棻.\n");
            d1s();
            printf("Яп蒂 嫡雖 彊蝗棲棻.\n");
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
        printf("<3. 聽橫>蒂 餌辨 ц蝗棲棻.\n");
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
        printf("<4. 陛萄 機>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        skill4_eft();
        d1s();
        printf("寞橫溘檜 %d 虜躑 隸陛 м棲棻\n", skill_4());
        player_defup = player_defup + skill_4();
        d1s();
        player_mpdown(20);
        turn++;
    }
    if (a == 0x35) {
        printf("<5. 詭蛤纔檜暮>擊 餌辨 ц蝗棲棻.\n");
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
        printf("    蹴жм棲棻! 溯漣機擊 ж艘蝗棲棻!\n");
        gotoxy(20, 17);
        printf("蝶囌 ん檣お 3, 蝶鑒 ん檣お 1擊 橢歷蝗棲棻.\n");
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
    printf("嬴鼠匙紫 й 熱 橈蝗棲棻.\n");
    player_stun = 1;
    turn++;
}
void stage01_skill()
{
    int r1;
    randomize();
    r1 = random(40) + 11;
    if (com_skill == 0) {
        printf("瞳檜 <褻遽 餌問>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        gunshot_eft();
        gunshot_eft();
        gunshot_eft();
        d1s();
        player_demage(30);
        d1s();
    }
    if (com_skill == 1) {
        printf("瞳檜 <識晦 陪餌>蒂 餌辨 ц蝗棲棻.\n");
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
        printf("瞳檜 <熱盟驕 癱繫>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        boom_eft();
        d1s();
        player_demage(35);
        d1s();
        player_defdown(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("瞳檜 <擬晝 纂猿>蒂 餌辨 ц蝗棲棻.\n");
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
        printf("瞳檜 <匐 �硉庛ㄠ�>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        sword_eft();
        d1s();
        player_demage(com_att + 15);
        d1s();
    }
    if (com_skill == 1) {
        printf("瞳檜 <寞橫 鷓撮>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        comdfup_eft();
        d1s();
        com_defup(5);
        d1s();
    }
    if (com_skill == 2) {
        printf("瞳檜 <瞪餌曖 л撩>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        roar_eft();
        d1s();
        com_attup(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("瞳檜 <鬼溘и 橾問>擊 餌辨 ц蝗棲棻.\n");
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
        printf("瞳檜 <盪問>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        sniper_eft();
        d1s();
        player_demage(com_att + 30);
        d1s();
    }
    if (com_skill == 1) {
        printf("瞳檜 <薑褐餵醞>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        focus_eft();
        d1s();
        com_attup(7);
        d1s();
    }
    if (com_skill == 2) {
        printf("瞳檜 <④萄憐>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        headshot_eft();
        d1s();
        printf("寞橫溘擊 鼠衛ж罹 Яп蒂 殮��棲棻.\n");
        d1s();
        player_demage(com_att + 30 + player_defup + player_def);
        d1s();
    }
    if (com_skill == 3) {
        printf("瞳檜 <擬晝 纂猿>蒂 餌辨 ц蝗棲棻.\n");
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
        printf("瞳檜 <嬴檜蝶 獐>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        ice_eft();
        d1s();
        player_demage(com_att + 20);
        d1s();
    }
    if (com_skill == 1) {
        printf("瞳檜 <橡擠 濰虞>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        comdfup_eft();
        d1s();
        com_defup(8);
        d1s();
    }
    if (com_skill == 2) {
        printf("瞳檜 <橡擠 ァЁ>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        blizzard_eft();
        d1s();
        player_demage(com_att + 20);
        d1s();
        player_defdown(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("瞳檜 <葆溘 唸綵>擊 餌辨 ц蝗棲棻.\n");
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
        printf("瞳檜 <廓偃 鬼顫>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        thunder_eft();
        d1s();
        player_demage(com_att + 10);
        d1s();
    }
    if (com_skill == 1) {
        printf("瞳檜 <廓偃 濰虞>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        comdfup_eft();
        d1s();
        com_defup(5);
        d1s();
    }
    if (com_skill == 2) {
        printf("瞳檜 <瞪晦 醱瞪>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        focus_eft();
        d1s();
        com_attup(5);
        d1s();
        com_hpup(25);
        d1s();
    }
    if (com_skill == 3) {
        printf("瞳檜 <褕っ曖 廓偃>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        powerthunder_eft();
        d1s();
        printf("寞橫溘擊 鼠衛ж罹 Яп蒂 殮��棲棻\n");
        d1s();
        player_demage(com_att + 10 + player_def + player_defup);
        d1s();
    }
}
void stage06_skill()
{
    if (com_skill == 0) {
        printf("瞳檜 <翮晦 碟餌>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        fireshot_eft();
        d1s();
        player_mplose(com_att + 20);
        d1s();
    }
    if (com_skill == 1) {
        printf("瞳檜 <嫦翮>擊 餌辨 ц蝗棲棻.\n");
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
        printf("瞳檜 <�倍� 輿詳>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        firepunch_eft();
        d1s();
        player_demage(com_att + 15);
        d1s();
        player_defdown(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("瞳檜 <ァ盟 �倍�>擊 餌辨 ц蝗棲棻.\n");
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
        printf("瞳檜 <夥塋 馬螟>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        windstorm_eft();
        d1s();
        player_demage(com_att / 2);
        d1s();
        printf("嬴鼠匙紫 й 熱 橈蝗棲棻.\n");
        d1s();
        player_stun = 1;
        turn++;
    }
    if (com_skill == 1) {
        printf("瞳檜 <晦遴 �篲�>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        absorb_eft();
        d1s();
        player_demage(com_att);
        d1s();
        com_hpup(com_att / 2);
        d1s();
    }
    if (com_skill == 2) {
        printf("瞳檜 <夥塋曖 陛��>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        focus_eft();
        d1s();
        com_attup(10);
        d1s();
        com_defup(5);
        d1s();
    }
    if (com_skill == 3) {
        printf("瞳檜 <渠ァЁ>擊 餌辨 ц蝗棲棻.\n");
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
        printf("瞳檜 <懍�� だ翕>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        darkbeam_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_defdown(10);
        d1s();
    }
    if (com_skill == 1) {
        printf("瞳檜 <藹僧>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        silence_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_stunon();
        d1s();
    }
    if (com_skill == 2) {
        printf("瞳檜 <鼠溘��>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        empower_eft();
        d1s();
        player_mplose(player_mp / 2);
        d1s();
    }
    if (com_skill == 3) {
        printf("瞳檜 <�篲�>蒂 餌辨 ц蝗棲棻.\n");
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
        printf("瞳檜 <陳滑и 匐晦>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        swiftsword_eft();
        d1s();
        player_demage(com_att);
        d1s();
    }
    if (com_skill == 1) {
        printf("瞳檜 <蠔曖 辭>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        sworddance_eft();
        d1s();
        com_attup((com_att / 15));
        d1s();
    }
    if (com_skill == 2) {
        printf("瞳檜 <骨褡 漆晦>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        armorbash_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_defdown(15);
        d1s();
    }
    if (com_skill == 3) {
        printf("瞳檜 <轎⑸>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        bleedslash_eft();
        d1s();
        player_demage(com_att);
        d1s();
        printf("衙 欐葆棻 雖樓瞳戲煎 Яп蒂 殮蝗棲棻. (識 3��)\n");
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
            printf(" 瞳檜 <鳴褻問>擊 餌辨 ц蝗棲棻.\n");
            d1s();
            triplespear_eft();
            d1s();
            printf("纂貲顫陛 攪螺蝗棲棻.\n");
            d1s();
            player_demage(com_att * 6);
            d1s();
        }
        else
        {
            printf("瞳檜 <鳴褻問>擊 餌辨 ц蝗棲棻.\n");
            d1s();
            triplespear_eft();
            d1s();
            player_demage(com_att * 3);
            d1s();
        }
    }
    if (com_skill == 1) {
        printf("瞳檜 <紫瞪>擊 餌辨 ц蝗棲棻.\n");
        d1s();
        challenge_eft();
        d1s();
        player_demage(com_att);
        d1s();
        player_defdown(15);
        d1s();
    }
    if (com_skill == 2) {
        printf("瞳檜 <蟾蝓殖 �蛨絞�>蒂 餌辨 ц蝗棲棻.\n");
        d1s();
        spearsweep_eft();
        d1s();
        player_demage(player_hp * 15 / 100);
        d1s();
        com_defup(10);
        d1s();
    }
    if (com_skill == 3) {
        printf("瞳檜 <路塊и 諾曖 匐>擊 餌辨 ц蝗棲棻.\n");
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
    printf("雖樓瞳戲煎 Яп蒂 殮蝗棲棻.\n");
    d1s();
    dote_eft();
    d1s();
    player_demage(a);
    d1s();
    all_set();
    return a;
}
void main(void) // 詭檣 л熱 ///////////////////////////////////////////////////////////////////////////////////////////////////////
{
    setcursortype(NOCURSOR);
    
    window();
    gotoxy(24, 2);
    printf("         葆徹餌曖 賅я\n");
    gotoxy(24, 3);
    printf("           Ver 1.0\n");
    gotoxy(50, 20);
    printf("Made by cd991478 / 寥撩霞\n");
    gotoxy(22, 14);
    printf("   衛濛ж溥賊 嬴鼠 酈釭 援腦撮蹂.\n");
    gotoxy(50, 18);
    printf("  cd991478@naver.com\n");
    _getch();
    item_att = &player_att;
    item_mp = &player_maxmp;
    for (;;) // 奩犒 掘僥
    {
        randomize();
        menu_fight = 0;
        menu_stat = 0;
        menu_skill = 0;
        menu_item = 0;
        system("cls");
        menu_choose(); // 詭檣 詭景 ��轎
        choose = _getch(); // 詭景 摹鷗 幗が
        if (choose == 0x31) { // 詭景縑憮 1. 瞪癱 殮溘衛
            total = win + lose;
            menu_fight = 1;
            stat_restore();
            stat_over();
            system("cls");
            printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖      \n");
            printf("弛   <<<蝶纔檜雖 廓�ㄧ� 殮溘ж堅 縛攪蒂 援腦撮蹂>>>   弛   \n");
            printf("弛            1-10 蝶纔檜雖 梱雖 氈戲貊,              弛    \n");
            printf("弛 %d 蝶纔檜雖 贗葬橫衛 斜 棻擠 蝶纔檜雖 Ы溯檜 陛棟.      \n", stage_level);
            printf("弛      (詭檣 詭景煎 給嬴陛溥賊 璋濠 0擊 殮溘)        弛      \n");
            printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎   \n");
            if (win >= 1 || lose >= 1)
            {
                printf("      %d蝓 %dぬ   蝓睦 : %.2f %%  薄熱 : %d\n", win, lose, (float)win * 100 / (float)total, rating);
            }
            if (total < 3)
            {
                printf("              ⑷營 蛔晝 : Unranked\n");
                printf("       譆模 3っ擊 й唳辦 蛔晝擊 寡薑 嫡蝗棲棻.\n");
            }
            if (total >= 3)
            {
                if (rating < 1000) {
                    strcpy(rank, "Bronze ∪");
                }
                if (rating >= 1000 && rating < 1050) {
                    strcpy(rank, "Silver Ⅲ");
                }
                if (rating >= 1050 && rating < 1100) {
                    strcpy(rank, "Gold Ⅶ");
                }
                if (rating >= 1100 && rating < 1200) {
                    strcpy(rank, "Platinum ﹢");
                }
                if (rating >= 1200 && rating < 1250) {
                    strcpy(rank, "Diamond Ⅹ");
                }
                if (rating >= 1250) {
                    strcpy(rank, "Master ≧");
                }
                printf("                  ⑷營 蛔晝 : %s\n", rank);
            }
            gotoxy(53, 3);
            puts("弛");
            gotoxy(0, 10);
            scanf_s("%d", &goto_stage);
            if (stage_level < goto_stage)
            {
                printf("п渡 蝶纔檜雖朝 嬴霜 Ы溯檜 й 熱 橈蝗棲棻.\n");
                printf("     啗樓 ж溥賊 嬴鼠 酈釭 援腦撮蹂.\n");
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
                printf("    澀跤 殮溘 ж艘蝗棲棻\n");
                d1s();
                printf("啗樓 ж溥賊 嬴鼠 酈釭 援腦撮蹂.\n");
                _getch();
                continue;
            }
            turn = 0;
            stat_restore();
            for (;;) // 瞪癱 奩犒
            {
                all_set();
                if (player_dotecount > 0) // 紫お 等嘐雖
                {
                    player_doteon(com_att);
                }
                if (turn % 2 == 0 && player_hp > 0 && player_stun == 0) {
                    for (;;) {
                        printf("      渡褐曖 欐殮棲棻!\n");
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
                    printf("       瞳曖 欐殮棲棻.\n");
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
                    printf("羹溘檜 0檜 腎橫 噙楝螺蝗棲棻.\n");
                    delay(2000);
                    system("cls");
                    window();
                    gotoxy(20, 9);
                    printf("    << ぬ寡 ж艘蝗棲棻 >>\n");
                    lose++;
                    rating = rating - (stage_level - goto_stage) - 21;
                    if (player_maxhp >= 150 && player_maxmp >= 150)
                    {
                        gotoxy(20, 10);
                        printf("      棟溘纂陛 馬模м棲棻.\n");
                        player_maxhp = player_maxhp - 10;
                        player_maxmp = player_maxmp - 10;
                    }
                    gotoxy(20, 13);
                    printf("啗樓 ж溥賊 嬴鼠 酈釭 援腦撮蹂.\n");
                    _getch();
                    break;
                }
                if (com_hp <= 0 && stage_level == goto_stage)
                {
                    all_set();
                    printf("瞳檜 噙楝螺蝗棲棻.\n");
                    gotoxy(50, 16);
                    puts("   ");
                    gotoxy(50, 16);
                    puts("OTL");
                    delay(2000);
                    system("cls");
                    printf("\n");
                    gotoxy(20, 9);
                    printf("         << 蝓葬 ж艘蝗棲棻! >>\n");
                    win++;
                    rating = rating + 21;
                    gotoxy(20, 10);
                    player_exp = player_exp + (goto_stage * 100);
                    printf("      唳я纂蒂 %d 虜躑 橢歷蝗棲棻.\n", goto_stage * 100);
                    gotoxy(20, 11);
                    player_gold = player_gold + (goto_stage * 500);
                    printf("       埤萄蒂 %d 虜躑 橢歷蝗棲棻.\n", goto_stage * 500);
                    level_up(player_exp);
                    gotoxy(20, 12);
                    printf("   棻擠 蝶纔檜雖縑 紫瞪 й 熱 氈蝗棲棻.\n");
                    gotoxy(20, 13);
                    printf("     啗樓 ж溥賊 嬴鼠 酈釭 援腦撮蹂.\n");
                    window();
                    stage_level = stage_level + 1;
                    _getch();
                    break;
                }
                if (com_hp <= 0 && stage_level > goto_stage)
                {
                    printf("瞳檜 噙楝螺蝗棲棻.\n");
                    gotoxy(50, 16);
                    puts("   ");
                    gotoxy(50, 16);
                    puts("OTL");
                    delay(2000);
                    system("cls");
                    window();
                    gotoxy(20, 9);
                    printf("     蝓葬 ж艘蝗棲棻!\n");
                    win++;
                    rating = rating + goto_stage;
                    gotoxy(20, 10);
                    player_exp = player_exp + (goto_stage * 80);
                    printf(" 唳я纂蒂 %d 虜躑 橢歷蝗棲棻.\n", goto_stage * 80);
                    gotoxy(20, 11);
                    player_gold = player_gold + (goto_stage * 300);
                    printf("  埤萄蒂 %d 虜躑 橢歷蝗棲棻.\n", goto_stage * 300);
                    level_up(player_exp);
                    gotoxy(20, 12);
                    printf("啗樓 ж溥賊 嬴鼠 酈釭 援腦撮蹂.\n");



                    _getch();
                    break;
                }
                if (player_dotecount > 0) {
                    player_dotecount = player_dotecount - 1;
                }
            }
        }
        if (choose == 0x32 && player_statpoint > 0) { // 詭景縑憮 2. 蝶囌 殮溘衛 (褻勒 o)
            menu_stat = 1;
            system("cls");
            stat_restore();
            playerstat_message();
            statchoose_message();
            printf("陴擎 蝶囌 ん檣お : %d\n", player_statpoint);
            stat_up = _getch(); // 錳ж朝 蝶囌 摹鷗
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
                    printf(" 寞橫溘擎 100擊 剩擊 熱 橈蝗棲棻.\n");
                }
                printf(" 啗樓ж溥賊 嬴鼠酈釭 援腦撮蹂\n");
                defover_state = 0;
                _getch();

                continue;
            }


        }
        if (choose == 0x32 && player_statpoint == 0) { // 詭景縑憮 2. 蝶囌 殮溘衛 (褻勒 x)
            system("cls");
            stat_restore();
            playerstat_message();
            printf("蝶囌 ん檣お陛 橈蝗棲棻.\n");
            _getch();
        }
        if (choose == 0x33 && player_skillpoint > 0) { // 詭景縑憮 3. 蝶鑒 殮溘衛 (褻勒 o)
            menu_skill = 1;
            system("cls");
            skillchoose_message();
            printf("陴擎 蝶鑒 ん檣お : %d\n", player_skillpoint);
            skill_up = _getch();
            if (skill_up == 0x31 || skill_up == 0x32 || skill_up == 0x33 || skill_up == 0x34 || skill_up == 0x35) {
                player_skillpoint = player_skillpoint - 1; // ん檣お 1 馬模
                choose = NULL;
            }
            if (skill_up == 0x31 && player_skill1 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("п渡 蝶鑒擎 檜嘐 譆渠 溯漣 殮棲棻.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x32 && player_skill2 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("п渡 蝶鑒擎 檜嘐 譆渠 溯漣 殮棲棻.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x33 && player_skill3 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("п渡 蝶鑒擎 檜嘐 譆渠 溯漣 殮棲棻.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x34 && player_skill4 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("п渡 蝶鑒擎 檜嘐 譆渠 溯漣 殮棲棻.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x35 && player_skill5 >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("п渡 蝶鑒擎 檜嘐 譆渠 溯漣 殮棲棻.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x31 && player_skill1 < 5) {
                player_skill1 = player_skill1 + 1; // 蝶鑒 1廓 機
            }


            if (skill_up == 0x32 && player_skill2 < 5) {
                player_skill2 = player_skill2 + 1; // 蝶鑒 2廓 機
            }

            if (skill_up == 0x33 && player_skill3 < 5) {
                player_skill3 = player_skill3 + 1; // 蝶鑒 3廓 機
            }

            if (skill_up == 0x34 && player_skill4 < 5) {
                player_skill4 = player_skill4 + 1; // 蝶鑒 4廓 機
            }

            if (skill_up == 0x35 && player_skill5 < 5) {
                player_skill5 = player_skill5 + 1; // 蝶鑒 5廓 機
            }

            if (skill_up == 0x31 || skill_up == 0x32 || skill_up == 0x33 || skill_up == 0x34 || skill_up == 0x35) {
                system("cls");
                skillchoose_message();
                printf("蝶鑒 溯漣檜 螢嫉蝗棲棻. 啗樓 ж溥賊 嬴鼠 酈釭 援腦撮蹂.\n");
                _getch();
            }

        }
        if (choose == 0x33 && player_skillpoint == 0) { // 詭景縑憮 3. 蝶鑒 殮溘衛 (褻勒 x) 
            system("cls");
            skillchoose_message();
            printf("蝶鑒 ん檣お陛 橈蝗棲棻.\n");
            _getch();
        }
        if (choose == 0x34) { // 詭景縑憮 4. 鼠晦 殮溘衛
            menu_item = 1;
            for (;;)
            {
                system("cls");
                printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖 \n");
                printf("弛                 <<< 鼠晦 薑爾 >>>                    弛   \n");
                if (item_code == 0)
                    printf("弛             ⑷營 濰雜醞檣 鼠晦 : 橈擠                弛  \n");
                if (item_code == 1)
                    printf("弛           ⑷營 濰雜醞檣 鼠晦 : 隸ァ曖 堅憮           弛  \n");
                if (item_code == 2)
                    printf("弛          ⑷營 濰雜醞檣 鼠晦 : 寞轎曖 葆徹瑰          弛   \n");
                if (item_code == 3) {
                    printf("弛          ⑷營 濰雜醞檣 鼠晦 : ⑷濠曖 雖な檜          弛    \n");
                }
                printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎     \n");
                printf("                ⑷營 爾嶸и 埤萄 : %d                       \n", player_gold);
                printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖   \n");
                printf("弛 1. 隸ァ曖 堅憮    (奢問溘 20 葆釭 400 / 10000埤萄)   弛 \n");
                printf("弛 2. 寞轎曖 葆徹瑰  (奢問溘 80 葆釭 100 / 10000埤萄)   弛 \n");
                printf("弛 3. ⑷濠曖 雖な檜  (奢問溘 60 葆釭 300 / 14000埤萄)   弛  \n");
                printf("弛 4. 鼠晦 濰雜 п薯 (濰濛 п薯и 鼠晦朝 模資)          弛   \n");
                printf("戍式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式扣    \n");
                printf("弛     嬴檜蠱擊 掘衙 ж溥賊 п渡 璋濠蒂 揚楝輿撮蹂.     弛     \n");
                printf("弛           詭景煎 給嬴陛溥賊 璋濠 0擊 殮溘            弛    \n");
                printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎   \n");
                item_choose = _getch();
                if (item_choose == 0x31)
                {
                    if (player_gold >= 10000 && item_code == 0)
                    {
                        printf("隸ァ曖 堅憮蒂 濰雜 ц蝗棲棻.\n");
                        item_code = 1;
                        *item_att = player_att + 20;
                        *item_mp = player_maxmp + 400;
                        player_gold = player_gold - 10000;
                        printf("啗樓 ж溥賊 嬴鼠 酈釭 援腦撮蹂.\n");
                        _getch();
                        break;
                    }
                    else
                    {
                        printf("掘殮 碳陛棟! 埤萄 睡褶 �分� 鼠晦 濰雜 п薯 �� 營衛紫 ж撮蹂\n");
                        _getch();
                    }
                }
                if (item_choose == 0x32)
                {
                    if (player_gold >= 10000 && item_code == 0)
                    {
                        printf("寞轎曖 葆徹瑰擊 濰雜 ц蝗棲棻.\n");
                        item_code = 2;
                        *item_att = player_att + 80;
                        *item_mp = player_maxmp + 100;
                        player_gold = player_gold - 10000;
                        printf("啗樓 ж溥賊 嬴鼠 酈釭 援腦撮蹂.\n");
                        _getch();
                        break;
                    }
                    else
                    {
                        printf("掘殮 碳陛棟! 埤萄 睡褶 �分� 鼠晦 濰雜 п薯 �� 營衛紫 ж撮蹂\n");
                        _getch();
                    }
                }
                if (item_choose == 0x33)
                {
                    if (player_gold >= 14000 && item_code == 0)
                    {
                        printf("⑷濠曖 雖な檜蒂 濰雜 ц蝗棲棻.\n");
                        item_code = 3;
                        *item_att = player_att + 60;
                        *item_mp = player_maxmp + 300;
                        player_gold = player_gold - 14000;
                        printf("啗樓 ж溥賊 嬴鼠 酈釭 援腦撮蹂.\n");
                        _getch();
                        break;
                    }
                    else
                    {
                        printf("掘殮 碳陛棟! 埤萄 睡褶 �分� 鼠晦 濰雜 п薯 �� 營衛紫 ж撮蹂\n");
                        _getch();
                    }
                }
                if (item_choose == 0x34)
                {
                    if (item_code == 1)
                    {
                        printf("鼠晦 濰雜 п薯 諫猿.\n");
                        item_code = 0;
                        *item_att = player_att - 20;
                        *item_mp = player_maxmp - 400;
                    }
                    if (item_code == 2)
                    {
                        printf("鼠晦 濰雜 п薯 諫猿.\n");
                        item_code = 0;
                        *item_att = player_att - 80;
                        *item_mp = player_maxmp - 100;
                    }
                    if (item_code == 3)
                    {
                        printf("鼠晦 濰雜 п薯 諫猿.\n");
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
                printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖     \n");
                printf("弛 纂お 囀萄蒂 殮溘ж撮蹂. (璋濠 4濠葬) 弛    \n");
                printf("弛    詭景煎 釭陛溥賊 璋濠 0擊 殮溘     弛      \n");
                printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎    \n");
                scanf_s("%d", &cheat);
                if (cheat == 1234)
                {
                    printf("羹溘檜 100 隸陛м棲棻!\n");
                    player_maxhp = player_maxhp + 100;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("葆釭陛 100 隸陛м棲棻!\n");
                    player_maxmp = player_maxmp + 100;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("奢問溘檜 20 隸陛м棲棻!\n");
                    player_att = player_att + 20;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("寞橫溘檜 10 隸陛м棲棻!\n");
                    player_defmain = player_defmain + 10;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("埤萄陛 2000 隸陛 м棲棻!\n");
                    player_gold = player_gold + 2000;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("蝶囌 ん檣お陛 1 隸陛м棲棻!\n");
                    player_statpoint = player_statpoint + 1;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("蝶鑒 ん檣お陛 1 隸陛м棲棻!\n");
                    player_skillpoint++;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1234)
                {
                    printf("蝶纔檜雖 溯漣檜 10戲煎 撲薑 腎歷蝗棲棻!\n");
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
                    printf("澀跤脹 纂お 囀萄 殮棲棻\n");
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
            printf("忙式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式忖  \n");
            printf("弛               啪歜 樓紫蒂 殮溘ж撮蹂.                    \n");
            printf("弛  * 檜めお蒂 薯諼и 鼻�笙� 詭撮雖 樓紫虜 瞳辨腌棲棻.           \n");
            printf("弛   璋濠陛 雪擊熱煙 緒落棲棻. 詭景煎 陛溥賊 0擊 殮溘.            \n");
            printf("弛             ⑷營 樓紫 : %d ( 掏濰 500-800 )                             \n", speed);
            printf("戌式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式式戎 \n");
            gotoxy(55, 1);
            puts("弛");
            gotoxy(55, 2);
            puts("弛");
            gotoxy(55, 3);
            puts("弛");
            gotoxy(55, 4);
            puts("弛");
            gotoxy(0, 6);
            scanf_s("%d", &speed);
            if (speed == 0)
            {
                speed = temp_speed;
            }
            else if (speed < 100)
            {
                speed = temp_speed;
                printf("譆模 100 睡攪 陛棟 м棲棻.\n");
                _getch();
                continue;
            }
            else if (speed > 2000)
            {
                speed = temp_speed;
                printf("譆渠 2000 梱雖 陛棟 м棲棻.\n");
                _getch();
                continue;
            }
            else if (speed >= 100 && speed <= 2000)
            {
                printf("瞳辨檜 諫猿 腎歷蝗棲棻.\n");
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
            printf("                  <紫遺蜓>\n");
            gotoxy(16, 2);
            printf(" 檜 啪歜擎 1欽啗曖 瞳睡攪 離滔渠煎 諄錶陛貊\n");
            gotoxy(16, 3);
            printf("     溯漣 機擊 鱔ж罹 棟溘擊 鬼�亳藥娖n");
            gotoxy(16, 4);
            printf(" 10欽啗曖 爾蝶蒂 鼠鎬腦朝 匙檜 跡ル 殮棲棻.\n");
            gotoxy(16, 6);
            printf("        欐 ⑽衝曖 瞪癱 寞衝檜貊\n");
            gotoxy(16, 8);
            printf("  瞳擎 4陛雖 晦獎擊 楠渾戲煎 餌辨 м棲棻.\n");
            gotoxy(16, 10);
            printf("  虜擒 ⑷營 紫瞪ж朝 蝶纔檜雖陛 橫滑棻賊 \n");
            gotoxy(16, 12);
            printf(" 渦 雪擎 蝶纔檜雖縑憮 溯漣 機擊 п爾撮蹂.\n");
            gotoxy(16, 14);
            printf("       渦 撩濰и 菴 棻衛 紫瞪й 唳辦\n");
            gotoxy(16, 16);
            printf("�徆� 渦 蔣啪 蝶纔檜雖蒂 贗葬橫 й 熱 氈擊匏棲棻.\n");
            _getch();
        }
        if (choose == 0x38)
        {
            system("cls");
            printf("啪歜貲    : 葆徹餌曖 賅я\n");
            printf("濰腦      : 欐 寞衝 諒旋 Ы溯檜 RPG 啪歜");
            printf("幗蟒      : 1.0\n");
            printf("�秣�      : 孺紫辦 7 32綠お\n");
            printf("晦��      : 寥撩霞\n");
            printf("偃嫦濠    : 寥撩霞\n");
            printf("罐        : Microsoft Visual C++ 2010 Express\n");
            printf("薯濛 諫猿 : 2014/6/16\n");
            printf("薯濛 晦除 : 衛除 釭朝渠煎 薯濛.\n");
            printf("檜詭橾    : cd991478@naver.com\n");
            printf("и葆蛤    : 蟾爾濛檜塭 ъ蕾ж雖虜 號檜 堅儅ц擠 壬壬\n");
            printf("\n");
            _getch();
        }
    } // for(;;)
} // int main(void)