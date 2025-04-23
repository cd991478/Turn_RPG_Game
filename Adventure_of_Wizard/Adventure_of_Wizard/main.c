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

int player_level = 1;   // �÷��̾� ĳ���� ����
int player_hp = 100;    // �÷��̾� ���� ü��
int player_maxhp = 100; // �÷��̾� �ִ� ü��
int player_mp = 100;    // �÷��̾� ���� ����
int player_maxmp = 100; // �÷��̾� �ִ� ����
int player_att = 10;    // �÷��̾� ���ݷ�
int player_def = 0;     // �÷��̾� ����
int player_defup = 0;   // �÷��̾� �߰� ����
int player_exp = 0;     // �÷��̾� ����ġ
int player_maxexp = 100;// �÷��̾� ����ġ ���޽� ������
int player_statpoint = 0;   // ���� ���� ����Ʈ
int player_skillpoint = 0;  // ���� ��ų ����Ʈ

int player_gold = 0;    // �÷��̾� ���� ���
int player_stun = 0;    // �÷��̾��� ���� ����
int player_defmain = 0;
int player_dote = 0;    // �÷��̾��� �������� ����
int player_dotecount = 0; // �÷��̾��� �������� ���� Ƚ��

int speed = 800;    // ��Ȳ�� �ؽ�Ʈ �ӵ�
int cheat;          // ġƮŰ �ڵ�
int c_value = 0;    // ġƮŰ ��� Ƚ��
int play_time = 0;  // �÷��� Ÿ��
int time_h = 0;     // �ð�
int time_m = 0;     // ��
int time_s = 0;     // ��
int defover_state = 0;  // ���� �ִ�ġ 100 �ʰ� ����
int win = 0;        // �¸� Ƚ��
int lose = 0;       // �й� Ƚ��
int total = 0;      // �� ���� Ƚ��
int rating = 1000;  // ������ ����
char rank[128] = "D";   // ��ũ ���

int player_skill1_level = 1;  // ��ų 1.���̾ ����
int player_skill2_level = 1;  // ��ų 2.�����Ʈ ����
int player_skill3_level = 1;  // ��ų 3.ť�� ����
int player_skill4_level = 1;  // ��ų 4.����� ����
int player_skill5_level = 1;  // ��ų 5.�޵����̼� ����

int player_skill1_maxlevel = 5;   // ��ų 1 �ִ� ����
int player_skill2_maxlevel = 5;   // ��ų 2 �ִ� ����
int player_skill3_maxlevel = 5;   // ��ų 3 �ִ� ����
int player_skill4_maxlevel = 5;   // ��ų 4 �ִ� ����
int player_skill5_maxlevel = 5;   // ��ų 5 �ִ� ����


int com_level = 1;      // ��ǻ�� ����
int com_hp = 100;       // ��ǻ�� ���� ü��
int com_maxhp = 100;    // ��ǻ�� �ִ� ü��
int com_att = 10;       // ��ǻ�� ���ݷ�
int com_def;            // ��ǻ�� ����

int stage_level = 1;    // ������ ��������
int goto_stage = 1;     // ������ ��������

int menu_fight = 0;     
int menu_stat = 0;
int menu_skill = 0;
int menu_item = 0;

int turn = 0;           // ¦�� = �÷��̾��� // Ȧ�� = ��ǻ����
int com_skill;          // ��ǻ�� ��ų

int* item_att;     // ���ο��� item_att = &player_att;
int* item_mp;      // ���ο��� item_mp = &player_maxmp;
int item_code = 0; // ������ ������ ��ȣ

char order;
char stat_up;
char skill_up;
char choose;
char item_choose;

char stage01[] = { "�뺴" }; // ���������� ��ǻ�� �̸�
char stage02[] = { "����" };
char stage03[] = { "���ݼ�" };
char stage04[] = { "���� ������" };
char stage05[] = { "���� ������" };
char stage06[] = { "ȭ�� ������" };
char stage07[] = { "õ�� ������" };
char stage08[] = { "���� ������" };
char stage09[] = { "�˰�" };
char stage10[] = { "â�� ����" };


void window() // �׵θ� ����
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
void intro_screen()
{
    window();       // �׵θ�
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
}

void d1s() // delay 1 second 1�� ���
{
    delay(speed);
}

void char_eft() // ĳ���� �⺻ ��ġ ���
{
    textcolor(WHITE);
    gotoxy(20, 16);
    puts("��");
    gotoxy(50, 16);
    puts("��");
    gotoxy(20, 16); // �÷��̾� ĳ���� �⺻ ��ġ
    puts("��");
    gotoxy(50, 16); // ��ǻ�� ĳ���� �⺻ ��ġ
    puts("��");
    gotoxy(0, 18); // ���ٴ� ��ġ
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}
void char_cls() // ĳ���� ȭ�� ���� ����
{
    gotoxy(0, 15);
    puts("                                                                                ");
    gotoxy(0, 16);
    puts("                                                                                ");
    gotoxy(0, 17);
    puts("                                                                                ");
}
void txt_cls() // ��Ȳ�� �ؽ�Ʈ ����
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
void txt_pos() // ��Ȳ�� ��ġ�� �̵�
{
    gotoxy(0, 19);
}
void eft_set() // ����Ʈ �ʱ�ȭ ����
{
    char_cls(); // ĳ���� ȭ�� ����
    char_eft(); // ĳ���� ȭ�� ����
    txt_cls();  // ��Ȳ�� ���� ����
    txt_pos();  // ��Ȳ�� ��ġ �̵�
}
void move_set() // ��ǻ�� ĳ���Ͱ� �÷��̾� �տ� �޶���� ���¿��� ȭ�� ���� ȿ��
{
    textcolor(WHITE);
    gotoxy(0, 15);
    puts("                                                                                ");
    gotoxy(0, 16);
    puts("                                                                                ");
    gotoxy(0, 17);
    puts("                                                                                ");
    gotoxy(20, 16);
    puts("��");
    gotoxy(50, 16);
    puts("��");
    gotoxy(20, 16); // �÷��̾� ��ġ
    puts("��");
    gotoxy(28, 16); // �÷��̾� �� ��ġ�� ��ǻ��
    puts("��");
    gotoxy(0, 18);
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}
void char_set() // �� ĳ���� �⺻ ��ǥ�� ���� �ʱ�ȭ
{
    char_cls(); // ĳ���� ȭ�� ����
    char_eft(); // �� ĳ���� �⺻ ��ǥ�� ����
}

void playerhp_eft() // �÷��̾� ü��ȸ�� ����Ʈ
{
    gotoxy(19, 15);
    puts("+"); // ���ڰ� ������� ü�� ȸ�� ȿ��
    delay(100);
    char_set(); // ��� ���� �� ����
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
void playermp_eft() // �÷��̾� ����ȸ�� ����Ʈ
{
    gotoxy(19, 15);
    puts("*"); // ��¦�� ������� ����ȸ���ϴ� ȿ��
    delay(100);
    char_set(); // ��� ���� �� ����
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
void playerdfup_eft() // �÷��̾� ����� ����Ʈ
{
    gotoxy(22, 16); // �ð� �������� �ѹ��� ���鼭 �簢�� �����
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
    char_set(); // �����
    gotoxy(22, 16); // �ܴ��� �庮 �θ� ȿ�� ���
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
void comdfup_eft() // ��ǻ�� ���� ��ȭ ��ų ����Ʈ
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
void playerboom_eft() // �÷��̾� ��ź���� �ǰ� ����Ʈ
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
void playerfreeze_eft() // �÷��̾� ���� ���� �ǰ� ����Ʈ
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
void playerthunder_eft() // �÷��̾� �������� �ǰݽ� ����Ʈ
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
void dote_eft() // �÷��̾� ���� ���� �ǰ� ����Ʈ
{
    gotoxy(22, 15);
    puts("!"); // ����ǥ�� ĳ���Ͱ� ��Ȳ�ϴ� ȿ��
    delay(500);
    eft_set();
}
void comhp_eft() // ��ǻ�� ü��ȸ�� ����Ʈ
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

void move_eft() // ��ǻ�� ĳ������ ���� ���� ���� �÷��̾�� ������ �޷����� ����Ʈ
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
void back_eft() // ��ǻ�� ĳ���Ͱ� �÷��̾�κ��� ����ġ�� ������ �ǵ��ư��� ����Ʈ
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

void skill0_eft() // �÷��̾� 0����ų �⺻���� ����Ʈ
{
    int k;
    for (k = 22; k < 49; k++) // ����ȭ���� ������ ���󰡴� ȿ��
    {
        gotoxy(k, 16);
        puts("��"); 
        delay(10);
        gotoxy(k, 16);
        puts("��");
    }

    playermp_eft(); // ���� ȸ�� ����Ʈ
    eft_set();
}
void skill1_eft()   // �÷��̾� ��ų 1 ���̾ ����Ʈ
{
    textcolor(ORANGE);
    int t;
    if (player_skill1_level == 1) // ��ų ������ ���������� ���󰡴� �ӵ��� ������ ����
    {
        t = 20;
    }
    if (player_skill1_level == 2)
    {
        t = 15;
    }
    if (player_skill1_level >= 3)
    {
        t = 10;
    }
    int k;
    for (k = 22; k < 49; k++)   // ���̾ ����ü �����ϸ� ���󰡴� ȿ��
    {
        if (k % 2 == 0)
        {
            gotoxy(k, 16);
            puts("��");
            delay(t);
            gotoxy(k, 16);
            puts("��");
        }
        if (k % 2 == 1)
        {
            gotoxy(k, 16);
            puts("��");
            delay(t);
            gotoxy(k, 16);
            puts("��");
        }
    }
    if (player_skill1_level == 1) // ��ų 1������ �� Ÿ�� ����Ʈ
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
    if (player_skill1_level >= 2) // ��ų 2���� �̻�� �� Ÿ�� ����Ʈ
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
        textcolor(ORANGE);
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
    textcolor(WHITE);
    eft_set();
}
void skill2_eft()   // �÷��̾� ��ų 2 �����Ʈ ����Ʈ
{
    textcolor(YELLOW);
    int t=30;
    if (player_skill2_level == 1) // ��ų ������ �������� �ӵ� ������
    {
        t = 30;
    }
    if (player_skill2_level == 2)
    {
        t = 25;
    }
    if (player_skill2_level >= 3)
    {
        t = 20;
    }
    int k;
    int i;
    for (k = 22; k < 49; k = k + 2) // ���� MMMMM ���·� ���󰡴� ����Ʈ
    {
        gotoxy(k, 16);
        puts("��");
        delay(t);

        gotoxy(k + 2, 16);
        puts("��");
        delay(t);
        k = k + 2;
    }
    int p = 4;
    if (player_skill2_level == 1)
    {
        p = 4;
    }
    if (player_skill2_level == 2)
    {
        p = 5;
    }
    if (player_skill2_level >= 3)
    {
        p = 6;
    }
    for (i = 0; i < p; i++) // �÷��̾�κ��� �� ��ġ���� ���� ���Ⱑ �䵿ġ�� ȿ�� + ���� �����ϸ� ���� ���� ���ϴ� ȿ��
    {
        for (k = 22; k < 49; k = k + 2) // ���� �ٱ� WWWWW ���� ����
        {
            gotoxy(k, 16);
            puts("��");
            gotoxy(k + 2, 16);
            puts("��");
            k = k + 2;
        }
        gotoxy(48, 16); // �� Ÿ�� ȿ�� ����
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
        char_set(); // ĳ���� ��ũ�� �ʱ�ȭ
        textcolor(YELLOW);
        for (k = 22; k < 49; k = k + 2) // �� ���� �ٱ� MMMMM ���� ����
        {
            gotoxy(k, 16);
            puts("��");
            gotoxy(k + 2, 16);
            puts("��");
            k = k + 2;
        }
        delay(t * 2);
    }
    textcolor(WHITE);
    eft_set();
}
void skill3_eft() // �÷��̾� ��ų 3 ť��
{
    playerhp_eft(); // �÷��̾� ü�� ȸ�� ����Ʈ
    eft_set();
}
void skill4_eft() // �÷��̾� ��ų 4 �����
{
    playerdfup_eft(); // �÷��̾� ��� �帷 ����Ʈ
    eft_set();
}
void skill5_eft() // �÷��̾� ��ų 5 �޵����̼�
{
    playermp_eft(); // �÷��̾� ���� ȸ�� ����Ʈ
    eft_set();
}

void gunshot_eft() // ��ǻ�� ��ų �ѱ� ��� ����Ʈ
{
    int k;
    for (k = 48; k > 21; k--) // �������� �Ѿ��� ���󰡴� ȿ��
    {
        gotoxy(k, 16);
        puts("-");
        delay(10);
        gotoxy(k, 16);
        puts("��"); 
    }
    eft_set();
}
void gunshot_eft2() // ��ǻ�� ��ų �ѱ� ���� ����Ʈ
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
void boom_eft() // ��ǻ�� ��ų ����ź ��ô ����Ʈ
{
    int k;
    for (k = 48; k > 21; k=k-2) // ����ź �������� ���󰡴� ȿ��
    {
        gotoxy(k, 16);
        puts("��"); 
        delay(20);
        gotoxy(k, 16);
        puts("��");
    }
    playerboom_eft(); // �÷��̾� ���� ȿ��
}
void sword_eft() // ��ǻ�� ��ų �˱� �ĵ� ����Ʈ
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
        puts("��");
    }
    eft_set();
}
void roar_eft() // ��ǻ�� ��ų ��ȿ ����Ʈ
{
    gotoxy(48, 15);
    puts("��"); // ��ǻ�� ĳ���Ͱ� ���� �������� �Ҹ� ���µ��� ȿ��
    gotoxy(48, 16);
    puts("����"); // ""
    gotoxy(48, 17);
    puts("��"); // ""
    gotoxy(46, 16);
    puts("!"); // ����ǥ�� ����Ͽ� ��ġ�µ��� ȿ��
    d1s(); // speed�� ��� 0.8 sec
    gotoxy(42, 15);
    puts("!");
    d1s();
    gotoxy(44, 17);
    puts("!");
    d1s();
    eft_set();
}
void powerslash_eft() // ��ǻ�� ��ų Į�� ���� ����Ʈ
{
    move_eft(); // ȭ�� �������� ��ǻ�� ĳ���Ͱ� ������ �÷��̾� ĳ���� ������ �޷���
    gotoxy(22, 15);
    puts("��"); // �÷��̾� ������ ������ 
    delay(50);
    move_set(); 
    gotoxy(20, 16);
    puts("��");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("��"); // �÷��̾� ���� �Ʒ��� ���� Į�� ���µ��� ȿ��
    delay(100);
    gotoxy(18, 15);
    puts("��"); // �÷��̾� ���� ��ܿ���
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("��");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("��"); // �÷��̾� ������ �ϴ��� ���� Į�� ���µ��� ȿ�� // �ݺ������� ��ü ����
    delay(100); 
    move_set();
    gotoxy(22, 15);
    puts("��"); // �ݺ�
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
    move_set(); // ��ǻ�Ͱ� �÷��̾�տ� �ٰ��� �����϶� �ʱ�ȭ
    back_eft(); // ������ ��ǻ�Ͱ� �ٽ� �ڱ� ��ġ�� ���������� ���ư�
    eft_set();
}
void sniper_eft() // ��ǻ�� ��ų ���� ����Ʈ
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("����"); // ��� ���� ������ źȯ �߻� ȿ��
        delay(5);
        gotoxy(k, 16);
        puts("��");
    }
    eft_set();
}
void focus_eft() // ��ǻ�� �ɷ�ġ ��ȭ ���� ��ų ���� ���� ����Ʈ
{
    gotoxy(48, 16); // �¿� �����Ƽ� ȭ��ǥ�� ���οö󰡴� ȿ���� �ݺ������ν� ���� ����ϴµ��� ȿ��
    puts("��"); // ��ǻ�� ĳ���� ���� �Ʒ����� ������� ȭ��ǥ�� �ö�
    delay(100);
    char_set();
    gotoxy(48, 15);
    puts("��");
    delay(100);
    char_set();
    gotoxy(52, 16); // ��ǻ�� ĳ���� ������ �Ʒ����� ������� ȭ��ǥ�� �ö�
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
void headshot_eft() // ��ǻ�� ��ų ��弦 ����Ʈ
{
    int k;
    gotoxy(20, 15); // �÷��̾� ĳ���͸� �� ������� �����ϴ� ȿ��
    puts("��"); // �÷��̾� ĳ���� ����� ���ڼ�
    gotoxy(20, 17);
    puts("��"); // �÷��̾� ĳ���� �ϴ��� ���ڼ�
    gotoxy(18, 16);
    puts("����"); // �÷��̾� ĳ���� ������ ���ڼ�
    gotoxy(22, 16);
    puts("����"); // �÷��̾� ĳ���� ������ ���ڼ�
    delay(500);
    char_set();
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("����"); // ���� ū �Ѿ� �߻� ����Ʈ
        delay(5);
        gotoxy(k, 16);
        puts("��");
    }
    eft_set();
}
void ice_eft() // ��ǻ�� ��ų ���̽� �� ����Ʈ
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("��"); // ���� ��� ��ô ȿ��
        delay(20);
        gotoxy(k, 16);
        puts("��");
    }
    playerfreeze_eft(); // �÷��̾� �ǰݽ� ���ٴ� ȿ��
}
void blizzard_eft() // ��ǻ�� ��ų ������ǳ ����Ʈ
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 15);
        puts("*");          // 3 x 3 �� ������ ���󰡴� ȿ��
        gotoxy(k - 2, 15);  // ������ ���� ������� ����
        puts("*");          //       * * *
        gotoxy(k - 4, 15);  //     * * *
        puts("*");          //   * * *
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
    playerfreeze_eft(); // �÷��̾� ���ٴ� ȿ��
}
void thunder_eft() // ��ǻ�� ��ų ���� ��Ÿ ����Ʈ
{
    int k;
    for (k = 48; k > 21; k = k - 2)
    {
        gotoxy(k, 16);
        puts("��"); // MMM ������ ���� �����ʿ��� �������� �߻�
        delay(20);
        gotoxy(k - 2, 16);
        puts("��");
        delay(20);
        k = k - 2;
    }
    char_set(); // ĳ���� ��ũ�� �ʱ�ȭ �Ͽ� ���� ȿ�� ����
    playerthunder_eft(); // �÷��̾� ���� ���ϴ� ����Ʈ �ݺ�
    delay(100);          // �١١�
    char_set();          // �ٿʡ�
    delay(100);          // �١١�
    playerthunder_eft();
    delay(100);
    char_set();
    delay(100);
    playerthunder_eft();
    delay(100);
    eft_set();
}
void powerthunder_eft() // ��ǻ�� ��ų ������ ���� ����Ʈ
{
    int k;
    int t;
    for (t = 0; t < 10; t++)  // ���� �ٱⰡ �ⷷ�̸� �÷��̾ ġ�������� ���� ���ϴ� ȿ��
    {
        for (k = 48; k > 21; k = k - 2) // ���� �ٱ� MMM ���� ��� ��� (�߻�X)
        {
            textcolor(YELLOW);
            gotoxy(k, 16);              // ��������������������
            puts("��");
            gotoxy(k - 2, 16);
            puts("��");
            k = k - 2;
        }
        gotoxy(20, 15);     // �÷��̾� ���� ����Ʈ 1 (+ ����)
        puts("��");
        gotoxy(22, 16);     //   ��
        puts("����");       //  �ѿʤ�
        gotoxy(20, 17);     //   ��
        puts("��");
        gotoxy(18, 16);
        puts("����");
        delay(50);
        char_set();         // ��� ����

        for (k = 48; k > 21; k = k - 2) // �����ٱ� WWW���� ��� ��� (�߻�X)
        {
            textcolor(YELLOW);
            gotoxy(k, 16);              // ��������������������
            puts("��");
            gotoxy(k - 2, 16);
            puts("��");
            k = k - 2;
        }
        gotoxy(22, 15);     // �÷��̾� ���� ����Ʈ 2 (x ����)
        puts("��");
        gotoxy(22, 17);     //  ��  ��
        puts("��");         //    ��
        gotoxy(18, 17);     //  ��  ��
        puts("��");
        gotoxy(18, 15);
        puts("��");
        delay(50);
        char_set();         // ��� ����
    }
    eft_set();
}
void fireshot_eft() // ��ǻ�� ��ų ȭ�� �л� ����Ʈ
{
    int k;
    int t;
    for (k = 48; k > 21; k = k - 2)
    {   
        gotoxy(k, 16); puts("��");       // ȭ�� �ٱ� �߻� ȿ��
        delay(20);                       // �ʡס��ס��ס��ס��ס��ס���  ��
    }
    char_set();     // ����Ʈ ����

    for (t = 0; t < 4; t++)              // ȭ�� �ٱ� �������� �մ� ȿ�� + �մµ��� �÷��̾� ��Ÿ�� ȿ��
    {                                    // �ʡס��ס��ס��ס��ס��ס���  ��
        for (k = 48; k > 21; k = k - 4)  // ��  �ס��ס��ס��ס��ס��ס��׿�
        {                                
            gotoxy(k, 16); puts("��");   
        }
        playerboom_eft();   // �÷��̾� ���� ����Ʈ
        delay(50);
        char_set();
        for (k = 46; k > 21; k = k - 4)
        {
            gotoxy(k, 16); puts("��");
        }
        playerboom_eft();
        delay(50);
        char_set();
    }
    eft_set();
}
void warmup_eft() // ��ǻ�� ��ȭ ���� ��ų �߿� ����Ʈ
{
    int k;
    for (k = 0; k < 3; k++)
    {
        gotoxy(50, 15);
        puts("��");  // �߰ſ����� ������ ȿ��
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
void firepunch_eft() // ��ǻ�� ��ų ȭ���ָ԰�Ÿ ��ų
{
    int k;
    move_eft(); // ��ǻ�Ͱ� �÷��̾� ������ �޷���
    
    for (k = 0; k < 4; k++) // �ٷξտ��� �ָ��� ������ ������ ȿ�� + ġ�������� ��� �°� ��Ÿ�� ȿ�� �ݺ�
    {
        textcolor(ORANGE);
        gotoxy(26, 16);     // �ָ� ������ ȿ��
        puts("��");         
        delay(50);          //���ʡ����ݿ�
        move_set();
        textcolor(ORANGE);
        gotoxy(24, 16);     //���ʡ��ݡ���
        puts("��");
        delay(50);          //���ʡݡ�����
        move_set();
        textcolor(ORANGE);
        gotoxy(22, 16);
        puts("��");
        delay(50);
        move_set();
        textcolor(LIGHTRED);
        gotoxy(18, 17);      // �ǰ� ���ϴ� ȿ��
        puts("��");          // �Ʒ����� ���� ���Ⱑ �ö�
        gotoxy(20, 17);      //���ʡ�������
        puts("��");          //�͢͢�
        gotoxy(22, 17);
        puts("��");          //�Ϳʢ͡�����
        delay(20);          
        move_set();          //�͢͢�
        textcolor(LIGHTRED); //���ʡ�������
        gotoxy(18, 16);      
        puts("��");
        gotoxy(22, 16);
        puts("��");
        delay(20);
        move_set();
        textcolor(LIGHTRED);
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
void fireblast_eft() // ��ǻ�� ��ų ȭ�� ��ȿ ����Ʈ
{
    int k;
    for (k = 48; k > 21; k--) // ȭ�� �ٱ⸦ ��� �л��ϰ� �䵿ġ�� ȿ��
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
void windbind_eft() // ��ǻ�� ��ų �ٶ� ���� ����Ʈ
{
    int k;
    for (k = 48; k > 21; k--)   // �ٶ� ����� ������ ȿ��
    {
        gotoxy(k, 15);          //   ~ ~ ~
        puts("~");              //  ~ ~ ~
        gotoxy(k - 2, 15);      // ~ ~ ~
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
void absorb_eft() // ��ǻ�� ȸ�� ��ų ��� ����Ʈ
{
    int k;
    int t;
    for (t = 0; t < 4; t++)
    {
        for (k = 22; k < 49; k++) // �÷��̾�κ��� �������� ����ϴµ��� ȿ��
        {                         // �÷��̾� ��ġ�� * �� �����Ͽ� ���������� �̵� 4ȸ �ݺ�
            gotoxy(k, 16);
            puts("��");
            delay(10);
            gotoxy(k, 16);
            puts("��");
        }
    }
    eft_set();
}
void windstorm_eft() // ��ǻ�� ��ų �ٶ��������� ���� �ӹ� �����̻� ���� ����Ʈ
{
    int k;
    for (k = 0; k < 6; k++) // �㸮������ �䵿ġ�� �÷��̾ �ӹ��ϴµ��� ȿ��
    {
        gotoxy(18, 15);     //��������~
        puts("~");          //��������  ~
        gotoxy(22, 16);     //��������    ~
        puts("~");
        gotoxy(18, 17);
        puts("~");
        delay(50);
        char_set();
        gotoxy(20, 15);     //          ~
        puts("~");          //          ~
        gotoxy(20, 16);     //          ~
        puts("~");
        gotoxy(20, 17);
        puts("~");
        delay(50);
        char_set();
        gotoxy(22, 15);     //            ~
        puts("~");          //          ~
        gotoxy(18, 16);     //        ~
        puts("~");
        gotoxy(22, 17);
        puts("~");
        delay(50);
        char_set();
    }
    eft_set();
}
void darkbeam_eft() // ��ǻ�� ��ų ����� �ĵ� ����Ʈ
{
    int k;
    for (k = 48; k > 21; k = k - 2) // �ĵ� �ٱ� �л� ȿ��
    {
        gotoxy(k, 16);
        puts("��");
        delay(20);
    }
    gotoxy(22, 15); // �÷��̾� �ǰ� ȿ��
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
void silence_eft() // ��ǻ�� �����̻� ��ų ħ�� ����Ʈ
{
    int k;
    for (k = 48; k > 21; k--) // ��ü�� ����
    {
        gotoxy(k, 16);
        puts("��");
        delay(10);
        gotoxy(k, 16);
        puts("��");
    }
    delay(200);
    gotoxy(22, 15);
    puts("!"); // �÷��̾� ĳ���Ϳ��� ����ǥ�� ����Ͽ� ħ�� ���� ���� ȿ��
    delay(500);
    eft_set();
}
void empower_eft() // ��ǻ�� ����� ��ų ��ȭ ����Ʈ
{
    int k;
    for (k = 0; k < 2; k++) // ��ǻ�� �ɷ�ġ ��ȭ ��ų�� ���� ����Ʈ�� �ݴ�� ����
    {                       // �÷��̾� ���� ������ ������ ȭ��ǥ�� �Ʒ��� �������� ȿ��
        gotoxy(18, 15);     // �ɷ��� ���ϵǴ� ������ ȿ��
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
void swiftsword_eft() // ��ǻ�� ��ų ������ �˱� ��ų
{
    int k;
    int t;
    for (t = 0; t < 2; t++)
    {
        textcolor(BLUEGREEN);
        gotoxy(48, 15); // ��ǻ�� �տ� ��ī�ο� �˱� ������ ����Ʈ�� �̾Ƴ�
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
        for (k = 42; k > 22; k = k - 2) // �ش� �˱⸦ �÷��̾ ���� ������ �߻�
        {
            textcolor(LIGHTGREEN);
            gotoxy(k, 15);          
            puts("��");             
            gotoxy(k - 2, 16);
            puts("��");
            gotoxy(k - 4, 17);
            puts("��");
            delay(10);
            char_set();
        }
        textcolor(BLUEGREEN);
        gotoxy(44, 15); // �ٽ� ��ǻ�� �տ� ������ ����� �˱� ����Ʈ�� ����
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
        for (k = 44; k > 18; k = k - 2) // �ش� ������ �˱⸦ �÷��̾ ���� ������ �߻�
        {
            textcolor(LIGHTGREEN);
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
void sworddance_eft() // ��ǻ�� �ɷ�ġ ��ȭ ���� ��ų Į���� ����Ʈ
{
    int k;
    for (k = 0; k < 2; k++) // ��ǻ�� ĳ���Ͱ� Į����� ���� �ߴµ��� ������ ȿ�� �ݺ�
    {
        gotoxy(48, 15);     //      ��      
        puts("��");         //      ����
        gotoxy(48, 16);     
        puts("��");
        delay(200);
        char_set();
        gotoxy(52, 15);     //          ��
        puts("��");         //        �ʦ�
        gotoxy(52, 16);
        puts("��");
        delay(200);
        char_set();
    }
    eft_set();
}
void armorbash_eft() // ��ǻ�� ��ų ���� ���� ����Ʈ
{
    int k;
    move_eft(); // ��ǻ�� ĳ���Ͱ� �������� �޷���

    for (k = 0; k < 3; k++) // �÷��̾� ĳ���͸� Į�� ���µ��� ȿ�� �ݺ�
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
    back_eft(); // ��ǻ�� ĳ���� ����ġ�� ����
    eft_set();
}
void bleedslash_eft() // ��ǻ�� ���� ���� ��ų ���� ����Ʈ
{
    move_eft();     // ��ǻ�� ĳ���Ͱ� �޷���
    gotoxy(22, 16); // �÷��̾� ĳ���͸� Į�� ����� ��� ȿ�� 
    puts("����");   //   �ʤѿ�
    delay(20);
    move_set();
    gotoxy(20, 16); 
    puts("����");   //   ��  ��
    delay(20);
    move_set();
    gotoxy(18, 16); 
    puts("����");   // ����  ��
    delay(20);      
    move_set();
    gotoxy(20, 16);
    puts("����");   //   ��  ��
    delay(20);      
    move_set();
    gotoxy(22, 16);
    puts("����");   //   �ʤѿ�
    delay(20);      
    move_set();
    back_eft();     // ��ǻ�� ĳ���� ����ġ�� ����
    eft_set();
}
void triplespear_eft() // ��ǻ�� ��ų ������ ����Ʈ
{
    int k;
    move_eft(); // ��ǻ�� ĳ���� �޷���
    move_set();
    delay(100);
    for (k = 0; k < 3; k++) // 3�� �
    {
        if (k != 0)
        {
            gotoxy(24, 16); // ��ǻ�� ĳ���Ͱ� â�� �� ȿ��
            puts("����");
            gotoxy(26, 16);
            puts("����");
            gotoxy(30, 16);
            puts("����");
            delay(200);
            move_set();
        }
        gotoxy(22, 16); // â�� ��� ȿ��
        puts("����");
        gotoxy(24, 16);
        puts("����");
        gotoxy(26, 16);
        puts("����");
        if (k == 2) // 3��° ��⿡�� �÷��̾� ĳ���Ͱ� �������� Ƣ������� ȿ��
        {
            gotoxy(20, 16);
            puts("��");
            gotoxy(20, 15);
            puts("��");
        }
        delay(100);
        move_set();
    }
    gotoxy(24, 16); // â ����ġ ȿ��
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
void challenge_eft() // ��ǻ�� ��ų ���� ����Ʈ
{
    move_eft(); // ��ǻ�� ĳ���Ͱ� �÷��̾� ĳ���Ϳ��� �ٰ��� ��ȿ�ϴ� ȿ��
    gotoxy(26, 15);
    puts("!");
    delay(500);
    move_set();
    back_eft();
    eft_set();
}
void molwang_eft() // ��ǻ�� ��ų ������ ���� �� ����Ʈ
{
    int k;
    for (k = 22; k < 49; k = k + 2) // �÷��̾�κ��� ����� ����ϴ� ������ ȿ��
    {
        gotoxy(k, 16);
        puts("��");
        delay(10);
    }
    for (k = 22; k < 49; k = k + 2) // ����� ����ϴ� �ٱ� ����Ʈ�� ���� �Ҹ�
    {
        gotoxy(k, 16);
        puts("��");
        delay(10);
    }
    comhp_eft(); // ��ǻ�� ü�� ȸ�� ����Ʈ
    eft_set();
}
void spearsweep_eft() // ��ǻ�� ��ų �ʽ´� �۾��� ����Ʈ
{
    move_eft();     // ��ǻ�� ĳ���Ͱ� �޷����� ȿ��
    delay(30);
    gotoxy(24, 16);     // �ݽð� �������� â�� 360�� ȸ�� ��Ű�� ������ ȿ��
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

void statchoose_message() // ���� ����Ʈ ������� ���� ��ȭ ȭ��
{
    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��               ��� ��ų �ɷ�ġ�� ���� �ϼ���.                    ��    \n");

    printf("��   ");
    textcolor(LIGHTGREEN);
    printf("1.ü�� +50   ");

    textcolor(SKYBLUE);
    printf("2.���� +50   ");
    textcolor(WHITE);
    printf("3.���ݷ� +10   4.���� +5   5.���  ��      \n");

    printf("����������������������������������������������������������������������������������������������������������������������������������������\n");
}
void statchoose(int a) // ������ ���� ��ȣ�� ���� ���� ��ȭ
{
    if (a == 1) { // ü�� ����
        player_maxhp = player_maxhp + 50;
    }
    if (a == 2) { // ���� ����
        player_maxmp = player_maxmp + 50;
    }
    if (a == 3) { // ���ݷ� ����
        player_att = player_att + 10;
    }
    if (a == 4) { // ���� ����
        if (player_defmain >= 100) // ������ �ʹ� �������
        {
            player_statpoint++; // ���� ����Ʈ ȯ��
            defover_state = 1;  // ���� �ѵ� ���� ON
        }
        if (player_defmain + 5 <= 100) // ��ȭ�Ͽ��� �ѵ�ġ���� ������쿡�� ���� ����
        {
            player_defmain = player_defmain + 5;
        }
    }
}
void playerstat_message() // ���� �޴� ȭ��
{
    printf("������������������������������������������������������������\n");
    printf("��       <<< ���� >>>\n");
    printf("�� ����   : ������\n");
    printf("�� ����   : %d\n", player_level);
    printf("�� "); 
    textcolor(LIGHTGREEN);
    printf("ü��   : %d / %d\n", player_hp, player_maxhp);
    textcolor(WHITE);
    printf("�� ");
    textcolor(SKYBLUE);
    printf("����   : %d / %d\n", player_mp, player_maxmp);
    textcolor(WHITE);
    printf("�� ���ݷ� : %d\n", player_att);
    printf("�� ���� : %d\n", player_defmain);
    printf("�� ");
    textcolor(ORANGE);
    printf("����ġ : %d / %d (%.2f%%)\n", player_exp, player_maxexp, (float)player_exp / (float)player_maxexp * 100);
    textcolor(WHITE);
    printf("�� ");
    textcolor(YELLOW);
    printf("������ ��� : %d\n", player_gold);
    textcolor(WHITE);
    printf("������������������������������������������������������������\n");
    int k;
    for (k = 1; k < 10; k++)
    {
        gotoxy(29, k);
        puts("��");
    }
    gotoxy(0, 11);
   
}

void menu_choose() // ���� �޴� ȭ��
{
    printf("��������������������������������������������������������������������������������������������������������������������������������������������   \n");
    printf("��                         ������ �Ͻðڽ��ϱ�?                       �� \n");
    printf("��  1.����  2.����  3.��ų  4.����  5.ġƮ  6.����  7.����  8.����  ��  \n");
    printf("��������������������������������������������������������������������������������������������������������������������������������������������    \n");

    if (stage_level >= 11)
    {
        printf("   ���ϵ帳�ϴ�! ��� ���������� Ŭ���� �Ͽ����ϴ�.\n");
        printf("     Ŭ���� �ڵ带 Ȯ�� �Ϸ��� ���� 0�� ��������.\n");
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
}

int skill_1() // �÷��̾� ��ų 1 ���̾ ���ط� ���
{
    int d; // ��ų ǥ��ʹ� ������, ���������� �÷��̾� ������, ���ݷ��� ��������쿡�� ��ġ�� �����ϵ��� ����
    d = (player_level * 10) + (player_att / 2) + (player_skill1_level * 20);
    return d;
}
int skill_2() // �÷��̾� ��ų 2 �����Ʈ ���ط� ���
{
    int d;
    d = (player_level * 9) + (player_att / 2) + (player_skill2_level * 18);
    return d;
}
int skill_3() // �÷��̾� ��ų 3 ť�� ȸ���� ���
{
    int d;
    d = (player_level * 10) + (player_skill3_level * 15) + (player_maxhp / 20) + (player_maxmp / 20);
    return d;
}
int skill_4() // �÷��̾� ��ų 4 ����� ���� ������ ��ġ ���
{
    int d;
    d = (player_skill4_level * 2) + (player_maxhp / 100);
    return d;
}
int skill_5() // �÷��̾� ��ų 5 �޵����̼� ���� ȸ���� % ��ġ ���
{
    int d;
    d = 45 + (player_skill5_level * 5) + (player_maxhp / 100);
    return d;
}

void skillchoose_message() // ��ų �޴� ȭ��
{
    printf("����������������������������������������������������������������������������������������������������������������������������������������   \n");
    printf("��                <<< ��ȭ�� ��ų�� �����ϼ��� >>>                  ��  \n");
    printf("�� 1. ���̾� �� (%d����/5)                                           ��\n", player_skill1_level);
    printf("��   - ���� �����Ͽ� %d��ŭ�� ���ظ� ����(+20)                        \n", skill_1());
    printf("��                                                                  ��  \n");
    printf("�� 2. ��� ��Ʈ (%d����/5)                                           ��   \n", player_skill2_level);
    printf("��   - ������ %d��ŭ�� ���ظ� ������, ������ %d ���ҽ�Ŵ(+18,+2)     \n", skill_2(), player_skill2_level * 2);
    printf("��                                                                  ��  \n");
    printf("�� 3. ť�� (%d����/5)                                                ��   \n", player_skill3_level);
    printf("��   - �ڽ��� ü���� %d��ŭ ȸ����(+15)                               \n", skill_3());
    printf("��                                                                  �� \n");
    printf("�� 4. ���� �� (%d����/5)                                             ��  \n", player_skill4_level);
    printf("��   - �������� �ڽ��� ������ %d��ŭ ���� ��Ŵ(+2)                   \n", skill_4());
    printf("��                                                                  ��  \n");
    printf("�� 5. �޵����̼� (%d����/5)                                          ��  \n", player_skill5_level);
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

void stat_restore() // ����, ���� ���� ���� ���� �ʱ�ȭ
{
    player_hp = player_maxhp; // ü�� ���󺹱�
    player_mp = player_maxmp; // ���� ���󺹱�
    player_defup = 0;         // ���� ����� �ʱ�ȭ
    player_def = player_defmain; // ������ ������ �⺻ �������� �ʱ�ȭ
    com_hp = com_maxhp;          // ��ǻ�� ü���� �ʱ�ȭ
    player_dotecount = 0;        // �÷��̾� ���� ���ظ� �ʱ�ȭ
    player_stun = 0;             // �÷��̾� ���� ���¸� �ʱ�ȭ
    turn = 0;                    // ���� �ʱ�ȭ
}
void stat_over() // ���� ������ �缳��
{
    if (player_hp < 0) { // ü�� ���� ó��
        player_hp = 0;
    }
    if (player_hp > player_maxhp) { // ü�� �ִ�ġ �ʰ� ó��
        player_hp = player_maxhp;
    }
    if (player_mp < 0) { // ���� ���� ó��
        player_mp = 0;
    }
    if (player_mp > player_maxmp) { // ���� �ִ�ġ �ʰ� ó��
        player_mp = player_maxmp;
    }
    if (player_def < 0) { // ���� ���� ���� ó��
        player_def = 0;
    }
    if (player_defup < 0) { // ���� ����� ���� ó��
        player_defup = 0;
    }
    if (player_defmain < 0) { // ���� ���� ���� ó��
        player_defmain = 0;
    }
    if (com_hp < 0) { // ��ǻ�� ü�� ���� ó��
        com_hp = 0;
    }
    if (com_hp > com_maxhp) { // ��ǻ�� ü�� �ִ�ġ �ʰ� ó��
        com_hp = com_maxhp;
    }
    if (com_def < 0) { // ��ǻ�� ���� ���� ó��
        com_def = 0;
    }
    if (player_def + player_defup > 100)    // �÷��̾� ������ �ѵ�ġ�� �ʰ��Ѱ�� ó��
    {
        for (; player_def + player_defup > 100;) // 100�� �ʰ��ϸ� 100�� �ǵ��� ����
        {
            player_defup--;
        }
    }
    if (player_defmain > 100)   // �÷��̾� ���� ���� �ѵ�ġ �ʰ� ó��
    {
        for (; player_defmain > 100;)
        {
            player_defmain--;
        }
    }
    if (com_def > 100) // ��ǻ�� ���� �ѵ�ġ �ʰ� ó��
    {
        for (; com_def > 100;)
        {
            com_def--;
        }
    }
}

void stage_name(int a) // ���� ȭ�� �ֻ�� �������� �̸� ���
{
    textcolor(LIGHTWHITE);
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
    textcolor(WHITE);
}
void fight_stat() // ���� ȭ�� ���� ����â ���
{
    printf("��������������");
    textcolor(LIGHTGREEN);
    printf("<�÷��̾�>"); 
    textcolor(WHITE);
    printf("������������������������������������������������������������������������");
    textcolor(LIGHTRED);
    printf("<��>");
    textcolor(WHITE);
    printf("��������������������������������������\n");
    printf("��  ");
    textcolor(LIGHTGREEN);
    printf(" ü�� : %d / %d                            ü�� : %d / %d          \n", player_hp, player_maxhp, com_hp, com_maxhp);
    textcolor(WHITE);
    printf("��  ");
    textcolor(SKYBLUE);
    printf(" ���� : %d / %d                                                  \n", player_mp, player_maxmp);
    textcolor(WHITE);
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
void fight_skill() // ���� ȭ�� ��ų ����â ���
{
    
    printf("����������������������������������");
    textcolor(YELLOW);
    printf("< ��ų�� ����Ϸ��� ���� ��ư�� �������� >");
    textcolor(WHITE);
    printf("����������������������������������\n");
    printf("��     1.���̾� �� (20 ����) : %d �� ���ظ� ����                           \n", skill_1());
    printf("��     2.��� ��Ʈ (25 ����) : %d �� ���ظ� ������, ������ %d ���ҽ�Ŵ    \n", skill_2(), player_skill2_level * 2);
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

void com_demage(int a) // �÷��̾ ��ǻ�Ϳ��� ������ ������ ����
{
    if (a > com_def) { // ���� ���ط��� ���� ���º��� �������
        printf("���� %d ��ŭ�� ���ظ� �޾ҽ��ϴ�. \n", a - com_def);
        com_hp = com_hp - (a)+com_def;
    }
    if (a <= com_def) { // ������ �� �������
        printf("���� 1 ��ŭ�� ���ظ� �޾ҽ��ϴ�.\n");
        com_hp = com_hp - 1;
    }
}
void player_demage(int a) // �÷��̾ ���� ���Ѱ�� ���� ����
{
    if (a > (player_def + player_defup)) { // �������� (������ �⺻���� + ��� ����) ���� �������
        printf("%d ��ŭ�� ���ظ� �޾ҽ��ϴ�. \n", a - (player_def + player_defup));
        player_hp = player_hp - (a)+player_def + player_defup;
    }
    if (a <= (player_def + player_defup)) { // ������ �� ���� ���
        printf("1 ��ŭ�� ���ظ� �޾ҽ��ϴ�.\n");
        player_hp = player_hp - 1;
    }
}
void player_hpdown(int a) // �÷��̾� ü�� ���� ȿ�� ���� (���� ���� ���������� ��쿡��)
{
    printf("ü���� %d ��ŭ �����մϴ�. \n", a);
    player_hp = player_hp - a;
}
void com_defup(int a) // ��ǻ�� ���� ���� ȿ�� ����
{
    printf("���� ������ %d ��ŭ �ö����ϴ�. \n", a);
    com_def = com_def + a;
}
void com_defdown(int a) // ��ǻ�� ���� ���� ȿ�� ����
{
    printf("���� ������ %d ��ŭ ���� �߽��ϴ�. \n", a);
    com_def = com_def - a;
}
void com_attup(int a) // ��ǻ�� ���ݷ� ���� ȿ�� ����
{
    printf("���� ���ݷ��� %d ��ŭ ���� �߽��ϴ�. \n", a);
    com_att = com_att + a;
}
void player_defdown(int a) // �÷��̾� ���� ���� ȿ�� ����
{
    printf("������ %d ��ŭ �����մϴ�.\n", a);

    if (player_defup == 0) { // ���� ���� ��ġ�� ������
        player_def = player_def - a; // �⺻ ������ ����
    }
    else if (player_defup < a && player_defup > 0) // ���� ���� ��ġ�� �ణ�ְ�(����� ��ġ���ٴ� ����), �⺻ ������ 0 �̻��϶�
    {
        player_defup = player_defup - a;    // ���� ������ġ�� �� (�� ���� ��������)
        player_def = player_def + player_defup; // �׸��� �⺻ ���¿� ������ ���Ͽ� ����
        player_defup = 0; // ���� ������ �ʱ�ȭ
    }
    else if (player_defup >= a) {   // ���� ������� ����� ��ġ���� ū���
        player_defup = player_defup - a; // ���� ��������� �׳� ��
    }

}
void player_hpup(int a) // �÷��̾� ü�� ȸ�� ����
{
    printf("ü���� %d ��ŭ ȸ�� �˴ϴ�.\n", a);
    player_hp = player_hp + a;
}
void player_mplose(int a) // �÷��̾� ���� ���� ����
{
    printf("������ %d ��ŭ �����մϴ�.\n", a);
    player_mp = player_mp - a;
}
void com_hpup(int a) // ��ǻ�� ü�� ȸ�� ����
{
    if (a >= 0) {
        printf("���� ü���� %d ��ŭ ȸ�� �˴ϴ�.\n", a);
        com_hp = com_hp + a;
    }
    if (a < 0) {
        printf("���� ü���� 1 ��ŭ ȸ�� �˴ϴ�.\n");
        com_hp = com_hp + 1;
    }
}
void player_mpup(int a) // �÷��̾� ���� ȸ�� ����
{
    printf("������ %d ��ŭ ȸ�� �˴ϴ�.\n", a);
    player_mp = player_mp + a;
}
void player_mppup(int a) // �÷��̾� ���� ȸ�� �ۼ�Ʈ ����
{
    printf("������ %d%% ��ŭ ȸ�� �˴ϴ�.\n", a);
    player_mp = player_mp + (player_maxmp * (a) / 100);
}
void player_mpdown(int a) // �÷��̾� ���� ���� ���� (��ų ����)
{
    player_mp = player_mp - a;
}
void nomp() // �÷��̾� ��ų ��� ���� ���� ���� ���
{
    printf("������ �����մϴ�.\n");
}


void player_skill(char a) // ������ �Է¹��� ��ų ��ȣ�� ���� ��ų ���
{
    // ���� 0 �⺻���� ��� (���� ���� ��밡��)
    if (a == 0x30) {    
        printf("<0. �⺻ ����>�� ��� �߽��ϴ�.\n");
        d1s();          // ��� (�⺻�� 0.8��)
        skill0_eft();   // ����Ʈ ���
        d1s();          // ���
        com_demage(player_att); // ���� ���� ��� �� ������ ���
        d1s();          // ���
        player_mpup(player_att + (player_maxmp / 20));  // ���� ȸ�� ���� ��� �� ����
        d1s();          // ���
        turn++;         // ���� ���濡�� �ѱ�
    }

    // ���� 1 ���̾ ��� �ߴµ� ������ ������� ���
    if (a == 0x31 && player_mp < 20) { 
        nomp(); // ���� ���� ���� ���
        d1s();  // speed�� ��� (�⺻�� 800sec)
    }
    // ���� 1 ���̾ ��� �ߴµ� ������ ����Ѱ��
    if (a == 0x31 && player_mp >= 20) { 
        printf("<1. ���̾� ��>�� ��� �߽��ϴ�.\n"); // ���� ���
        d1s();
        skill1_eft(); // ���̾ ����Ʈ
        d1s();
        if (goto_stage == 6) // ���� ���������� 6�ΰ�� (ȭ�� ������)
        {
            printf("���� ȭ�� �Ӽ��� �鿪�Դϴ�.\n");
            d1s();
            printf("���ظ� ���� �ʽ��ϴ�.\n");
        }
        if (goto_stage != 6) // ���������� 6�� �ƴѰ��
        {
            com_demage(skill_1()); // ��ǻ�Ϳ���, ��ų 1 ���̾ ������ ����
        }
        d1s();
        player_mpdown(20); // �÷��̾� ���� �Ҹ�
        turn++;            // �� �ѱ�
    }

    // ���� 2 �����Ʈ ��� �ߴµ� ������ ������� ���
    if (a == 0x32 && player_mp < 25) { 
        nomp();
        d1s();
    }
    // ���� 2 �����Ʈ ��� �ߴµ� ������ ����� ���
    if (a == 0x32 && player_mp >= 25) {
        printf("<2. ��� ��Ʈ>�� ��� �߽��ϴ�.\n");
        d1s();
        skill2_eft();        // ��� ��Ʈ ����Ʈ ���
        d1s();
        if (goto_stage == 5) // �������� 5 ���� ������ �ΰ��
        {
            printf("���� ���� �Ӽ��� �鿪�Դϴ�.\n");
            d1s();
            printf("���ظ� ���� �ʽ��ϴ�.\n");
        }
        if (goto_stage != 5)
        {
            com_demage(skill_2()); // �����Ʈ ���ط� ��ǻ�Ϳ��� ����
            d1s();
            com_defdown(player_skill2_level * 2); // ��ǻ�� ���� ���� ȿ�� ����
        }

        d1s();
        player_mpdown(25);  // ���� �Ҹ� ����
        turn++;             // �� �ѱ�
    }

    // ���� 3�� ť��
    if (a == 0x33 && player_mp < 30) { 
        nomp();
        d1s();
    }
    // ���� 3�� ť��
    if (a == 0x33 && player_mp >= 30) {
        printf("<3. ť��>�� ��� �߽��ϴ�.\n");
        d1s();
        skill3_eft();   // ť�� ����Ʈ ���
        d1s();
        player_hpup(skill_3()); // ü�� ȸ�� ����
        d1s();
        player_mpdown(30);      // ���� �Ҹ�
        turn++;
    }

    // ���� 4�� �����
    if (a == 0x34 && player_mp < 20) { 
        nomp();
        d1s();
    }
    // ���� 4�� �����
    if (a == 0x34 && player_mp >= 20) { 
        printf("<4. ���� ��>�� ��� �߽��ϴ�.\n");
        d1s();
        skill4_eft(); // ���� �� ����Ʈ
        d1s();
        printf("������ %d ��ŭ ���� �մϴ�\n", skill_4());
        player_defup = player_defup + skill_4(); // �÷��̾� ���� ���ġ ����
        d1s();
        player_mpdown(20);
        turn++;
    }

    // ���� 5�� �޵����̼�
    if (a == 0x35) { 
        printf("<5. �޵����̼�>�� ��� �߽��ϴ�.\n");
        d1s();
        skill5_eft(); // �޵����̼� ����Ʈ
        d1s();
        player_hpdown(player_hp * 40 / 100); // ���� ü���� 40% �Ҹ�
        d1s();
        player_mppup(skill_5());    // ���� ȸ�� ����
        d1s();
        turn++;
    }

}

void level_up(int a) // ���� ���� �� �������ߴ��� üũ
{
    if (a >= player_maxexp) // ���� ����ġ�� �ִ� ����ġ�� �����Ұ��
    {
        gotoxy(20, 16);
        printf("    �����մϴ�! �������� �Ͽ����ϴ�!\n");
        gotoxy(20, 17);
        printf("���� ����Ʈ 3, ��ų ����Ʈ 1�� ������ϴ�.\n"); // ���� ��� â���� ���� ���

        player_statpoint = player_statpoint + 3;    // ���� ����Ʈ ����
        player_skillpoint = player_skillpoint + 1;  // ��ų ����Ʈ ����
        player_exp = player_exp - player_maxexp;    // ����ġ �ʰ��� ���
        player_maxexp = player_maxexp + 100;        // ������ ������ ���� �����ؾ��� �ִ� ����ġ ����
        player_level++;      // �÷��̾� ĳ���� ���� ����
    }
}

void all_set()      // ��ü ȭ�� ���� + ���� ���� ����
{
    stat_over();    // ���� �ʰ�, ���� ó��
    system("cls");  // ȭ�� ��� ����
    stage_name(goto_stage); // �������� �̸�, ���� ���������� ���� 
    fight_stat();   // ���� ���� ���� â ���
    fight_skill();  // ���� ��ų ���� â ���
    char_eft();     // �� ĳ���� ����ġ ���
    txt_pos();      // ��Ȳ ���� �޼��� ��ǥ�� �̵�
}
void txt_set()      // ��ü ȭ�� ���� 
{
    system("cls");
    stage_name(goto_stage);
    fight_stat();
    fight_skill();
    char_eft();
    txt_pos();
}

void player_stunon() // �÷��̾�� ���� ���� ����
{
    printf("�ƹ��͵� �� �� �����ϴ�.\n");
    player_stun = 1; // ���� ���� �� ����
    turn++;          // �� �ѱ�
}
void player_doteon(int a) // ���� ���� ��Ʈ ������ ����
{
    printf("���������� ���ظ� �Խ��ϴ�.\n");
    d1s();
    dote_eft(); // ��Ʈ ���� ����Ʈ
    d1s();
    player_demage(a); // ������ ����
    d1s();
    all_set();      // ȭ�� ���� + ���� ���� ����
}

void stage01_skill() // �������� 1 ��ǻ�� ��ų
{
    int r1;
    randomize();
    r1 = random(40) + 11; // �ѱ� ���� ��ų �������� �����ϰ� ����

    if (com_skill == 0) { // com_skill �� ���� 25%
        printf("���� <���� ���>�� ��� �߽��ϴ�.\n");
        d1s();
        gunshot_eft(); // �Ѿ� ���󰡴� ����Ʈ ����
        gunshot_eft(); 
        gunshot_eft();
        d1s();
        player_demage(30); // �÷��̾�� ���ط� ���� �� ���� ���
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
        player_demage(r1); // ���� ������ ����
        d1s();
    }
    if (com_skill == 2) {
        printf("���� <����ź ��ô>�� ��� �߽��ϴ�.\n");
        d1s();
        boom_eft();         // ����ź ��ô ����Ʈ
        d1s();
        player_demage(35);  // ���ط� ���� �� ���� ���
        d1s();
        player_defdown(5);  // ���� ���� ȿ�� ���� �� ���� ���
        d1s();
    }
    if (com_skill == 3) {
        printf("���� <���� ġ��>�� ��� �߽��ϴ�.\n");
        d1s();
        comhp_eft();        // ��ǻ�� ü�� ȸ�� ����Ʈ
        d1s();
        com_hpup(30);       // ��ǻ�� ü�� ȸ�� ���� �� ���� ���
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
void stage06_skill() // �������� 6 ��ǻ�� ��ų
{
    if (com_skill == 0) { // com_skill �� ���� 25%
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
        firepunch_eft(); // ȭ�� �ָ� ����Ʈ ���
        d1s();
        player_demage(com_att + 15); // �÷��̾� ���ط� ����, ���
        d1s();
        player_defdown(5); // �÷��̾� ���� ���� ȿ�� ����, ���
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
void stage10_skill() // ������ �������� ��ǻ�� ��ų
{
    int r;
    randomize();

    if (com_skill == 0) { // ��ǻ�� ������ ��ų�� 15% Ȯ���� ġ��Ÿ ����
        r = random(100);
        if (r < 15)
        {
            printf(" ���� <������>�� ��� �߽��ϴ�.\n");
            d1s();
            triplespear_eft();
            d1s();
            printf("ġ��Ÿ�� �������ϴ�.\n");
            d1s();
            player_demage(com_att * 6); // �⺻ ��� �ι��� ���ط� ����
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



/////////////////////////////////////////////// ���� /////////////////////////////////////////////////

void main(void) 
{
    setcursortype(NOCURSOR);
    
    intro_screen();

    _getch();
    item_att = &player_att;
    item_mp = &player_maxmp;

    for (;;) // �ݺ�
    {
        randomize();

        menu_fight = 0; // ���� �޴� �÷��� ����
        menu_stat = 0;  // ���� �޴�
        menu_skill = 0; // ��ų �޴�
        menu_item = 0;  // ���� �޴�

        system("cls");

        menu_choose(); // ���� �޴� ���
        choose = _getch(); // �޴� ����

        // 1. ���� ����
        if (choose == 0x31) {   

            total = win + lose; // �� ���� Ƚ�� ����
            menu_fight = 1;     // ���� �޴� ���� �÷��� ���� ����

            stat_restore();     // ���� ����
            stat_over();        // ���� ����
            system("cls");
            printf("������������������������������������������������������������������������������������������������������������      \n");
            printf("��   <<<�������� ��ȣ�� �Է��ϰ� ���͸� ��������>>>   ��   \n");
            printf("��            1-10 �������� ���� ������,              ��    \n");
            printf("�� %d �������� Ŭ����� �� ���� �������� �÷��� ����.      \n", stage_level);
            printf("��      (���� �޴��� ���ư����� ���� 0�� �Է�)        ��      \n");
            printf("������������������������������������������������������������������������������������������������������������   \n");

            if (win >= 1 || lose >= 1) // �ѹ��̶� ������ ġ�� ��� �·� �� ���� ǥ��
            {
                printf("      %d�� %d��   �·� : %.2f %%  ���� : %d\n", win, lose, (float)win * 100 / (float)total, rating);
            }
            if (total < 3)  // ���� Ƚ���� ���� ����� ���� ���� ���� ���
            {
                printf("              ���� ��� : Unranked\n");
                printf("       �ּ� 3���� �Ұ�� ����� ���� �޽��ϴ�.\n");
            }
            if (total >= 3) // ����� ������ ġ�� ����� ���� �Ȱ��
            {
                if (rating < 1000) { // ������ ���� ��ũ ��� ����
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

            scanf_s("%d", &goto_stage);     // �������� �Է� �ޱ�

            if (stage_level < goto_stage)   // �÷��� ������ �������� �̻����� �õ� �ϴ� ���
            {
                printf("�ش� ���������� ���� �÷��� �� �� �����ϴ�.\n");
                printf("     ��� �Ϸ��� �ƹ� Ű�� ��������.\n");
                _getch();
                continue;
            }

            if (goto_stage == 1) {      // ���������� ��ǻ�� �ɷ�ġ ����
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

            turn = 0;       // �� �ʱ�ȭ
            stat_restore(); // ���� ���� ����

            for (;;)   // ���� �ݺ�
            {
                all_set();  // ���� ȭ�� ���� �� ���� ����

                if (player_dotecount > 0) // ���� ���� ���� Ƚ���� �����ִ� ���
                {
                    player_doteon(com_att); // ���� ���� ���� (all_set����)
                }

                        
                if (turn % 2 == 0 && player_hp > 0 && player_stun == 0) { // �÷��̾� ���̸鼭, �÷��̾� ü���� ���� �ְ�, ���� ���°��ƴ� ���

                    for (;;) {                                            // ��, ������ ������ �����ΰ��, �÷��̾� �� ����

                        printf("      ����� ���Դϴ�!\n");
                        order = _getch();
                        player_skill(order);    // �Է� ���� ��ų ��� �� turn++

                        if (turn % 2 == 1) {    // turn�� ���� �Ǹ� Ż��
                            break;
                        }
                    }
                }

                if (turn % 2 == 1 && com_hp > 0) {  // ��ǻ�� ���̵Ǿ���, ��ǻ���� ü���� ���� �ִ°��

                    all_set();          // ȭ�� ����

                    player_stun = 0;    // �÷��̾� ���� �������Ƿ�, �÷��̾� ���� ���¸� ����

                    printf("       ���� ���Դϴ�.\n");
                    d1s();

                    com_skill = random(4);  // ��ǻ�� 4���� ��ų ���� ����

                    // ���� �������� ������ ���� �ٸ� ��ǻ�� ��ų ����
                    if (goto_stage == 1) {stage01_skill();}
                    if (goto_stage == 2) {stage02_skill();}
                    if (goto_stage == 3) {stage03_skill();}
                    if (goto_stage == 4) {stage04_skill();}
                    if (goto_stage == 5) {stage05_skill();}
                    if (goto_stage == 6) {stage06_skill();}
                    if (goto_stage == 7) {stage07_skill();}
                    if (goto_stage == 8) {stage08_skill();}
                    if (goto_stage == 9) {stage09_skill();}
                    if (goto_stage == 10) {stage10_skill();}

                    turn++; // ��ǻ�� ��ų ����� �������� �� �ѱ�
                }


                if (player_hp <= 0) // �÷��̾� ü�� üũ
                {
                    all_set();
                    printf("ü���� 0�� �Ǿ� ���������ϴ�.\n");
                    delay(2000);
                    system("cls");
                    window();
                    gotoxy(20, 9);
                    printf("    << �й� �Ͽ����ϴ� >>\n");

                    lose++;   // �й� ��ġ ����
                    rating = rating - (stage_level - goto_stage) - 21;  // �������� ������ ���� �ٸ��� ���� �϶�

                    if (player_maxhp >= 150 && player_maxmp >= 150) // �ɷ�ġ �϶�
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

                // ��ǻ�� ü�� üũ
                if (com_hp <= 0 && stage_level == goto_stage) // ���� �ְ� ���������� ������ ���, ���� �ܰ� ����
                {
                    all_set();
                    printf("���� ���������ϴ�.\n");
                    gotoxy(50, 16);
                    puts("   ");
                    gotoxy(50, 16);
                    puts("OTL");    // ��ǻ�� ĳ���� ������ ��� ȿ��
                    delay(2000);
                    system("cls");
                    printf("\n");
                    gotoxy(20, 9);
                    printf("         << �¸� �Ͽ����ϴ�! >>\n");

                    win++;                  // �¸� Ƚ�� ����
                    rating = rating + 21;   // ���� ����
                    
                    player_exp = player_exp + (goto_stage * 100);   // ����ġ ����
                    gotoxy(20, 10);
                    printf("      ����ġ�� %d ��ŭ ������ϴ�.\n", goto_stage * 100);
                    
                    player_gold = player_gold + (goto_stage * 500); // ��� ����
                    gotoxy(20, 11);
                    printf("       ��带 %d ��ŭ ������ϴ�.\n", goto_stage * 500);

                    level_up(player_exp);   // �÷��̾� ������ üũ

                    gotoxy(20, 12);
                    printf("   ���� ���������� ���� �� �� �ֽ��ϴ�.\n");
                    gotoxy(20, 13);
                    printf("     ��� �Ϸ��� �ƹ� Ű�� ��������.\n");
                    window();   // �׵θ� ���

                    stage_level = stage_level + 1; // ���� ���� ������ �ְ� �������� �ܰ� ����
                    _getch();
                    break;
                }

                if (com_hp <= 0 && stage_level > goto_stage) // ���� ������������ �����Ѱ��
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
                    rating = rating + goto_stage;   // ���� �ܰ� ���� �̹Ƿ� ���� ���� ȹ��

                    player_exp = player_exp + (goto_stage * 80);    // �ְ� �ܰ� ������ �ƴ�, ���� �ܰ� �����̹Ƿ� ���� ���� ȹ��
                    gotoxy(20, 10);
                    printf(" ����ġ�� %d ��ŭ ������ϴ�.\n", goto_stage * 80);

                    player_gold = player_gold + (goto_stage * 300);
                    gotoxy(20, 11);
                    printf("  ��带 %d ��ŭ ������ϴ�.\n", goto_stage * 300);
                    
                    level_up(player_exp);   // ���� �� üũ
                    
                    gotoxy(20, 12);
                    printf("��� �Ϸ��� �ƹ� Ű�� ��������.\n");

                    _getch();
                    break;
                }

                if (player_dotecount > 0) { // �÷��̾� ���� ���� �����ΰ�� Ƚ�� ����
                    player_dotecount = player_dotecount - 1;
                }
            }
        }

        // 2. ���� ���� (���� ����Ʈ�� ������ ���)
        if (choose == 0x32 && player_statpoint > 0) {  

            menu_stat = 1;  // ���� �޴� ���� �÷��� ���� ����

            system("cls");          // ȭ�� �����
            stat_restore();         // ���� ����
            playerstat_message();   // ���� ���� ȭ�� ���
            statchoose_message();   // ���� ���� ȭ�� ��� (���� ����Ʈ ���� ��쿡��)
            printf("���� ���� ����Ʈ : %d\n", player_statpoint);

            stat_up = _getch(); // ���ϴ� ���� ����

            if (stat_up == 0x31 || stat_up == 0x32 || stat_up == 0x33 || stat_up == 0x34) { // 1~4 �� ������ �����
                player_statpoint = player_statpoint - 1;    // ���� ����Ʈ ����
                choose = NULL;
            }

            if (stat_up == 0x31) {  // 1�� ü�� ���� ���� �� ����
                statchoose(1);
            }
            if (stat_up == 0x32) {  // 2�� ���� ���� ���� �� ����
                statchoose(2);
            }
            if (stat_up == 0x33) {  // 3�� ���ݷ� ���� ���� �� ����
                statchoose(3);
            }
            if (stat_up == 0x34) {  // 4�� ���� ���� ���� �� ����
                statchoose(4);      // ������ 100�� �Ѿ��ٸ�, ���� ����Ʈ�� ȯ�� ������, defover_state �÷��� ���� 1�� ����
            }
            if (stat_up == 0x35) {  // 5�� �ڷΰ��� ����
                continue;
            }

            // ������ �����߰�, ���� ��������, ȭ�� ����
            if (stat_up == 0x31 || stat_up == 0x32 || stat_up == 0x33 || stat_up == 0x34 || stat_up == 0x35) {

                system("cls");
                stat_restore();
                playerstat_message();

                if (player_defmain >= 100) // ������ �ִ�ġ�� �����Ѱ�� �˷���
                {
                    printf(" ������ 100�� ���� �� �����ϴ�.\n");
                }

                printf(" ����Ϸ��� �ƹ�Ű�� ��������\n");
                defover_state = 0;
                _getch();

                continue;
            }
        }

        // 2. ���� ���� (���� ����Ʈ�� ���� ���)
        if (choose == 0x32 && player_statpoint == 0) { 
            system("cls");
            stat_restore();
            playerstat_message();
            printf("���� ����Ʈ�� �����ϴ�.\n");
            _getch();
        }

        // 3. ��ų ���� (��ų ����Ʈ�� �ִ� ���)
        if (choose == 0x33 && player_skillpoint > 0) { 

            menu_skill = 1;         // �÷��� ���� ����
            system("cls");          // ȭ�� ����
            skillchoose_message();  // ��ų �޴� ȭ�� ���
            printf("���� ��ų ����Ʈ : %d\n", player_skillpoint);

            skill_up = _getch();

            // 1~5�� �� ��ȭ�� ��ų�� ���� �� ���
            if (skill_up == 0x31 || skill_up == 0x32 || skill_up == 0x33 || skill_up == 0x34 || skill_up == 0x35) {
                player_skillpoint = player_skillpoint - 1; // ����Ʈ 1 ����
                choose = NULL;
            }

            if (skill_up == 0x31 && player_skill1_level >= 5) // ��ų 1 ���̾�� �����ߴµ� �ִ� ������ ������ ���
            {
                player_skillpoint = player_skillpoint + 1;  // ��ų ����Ʈ ȯ��
                printf("�ش� ��ų�� �̹� �ִ� ���� �Դϴ�.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x32 && player_skill2_level >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("�ش� ��ų�� �̹� �ִ� ���� �Դϴ�.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x33 && player_skill3_level >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("�ش� ��ų�� �̹� �ִ� ���� �Դϴ�.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x34 && player_skill4_level >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("�ش� ��ų�� �̹� �ִ� ���� �Դϴ�.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x35 && player_skill5_level >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("�ش� ��ų�� �̹� �ִ� ���� �Դϴ�.\n");
                _getch();
                continue;
            }

            // ��ų ������ �ִ�ġ�� �ƴѰ��, ������ ��ų ���� ����
            if (skill_up == 0x31 && player_skill1_level < 5) { 
                player_skill1_level = player_skill1_level + 1; // ��ų 1�� ��
            }
            if (skill_up == 0x32 && player_skill2_level < 5) {
                player_skill2_level = player_skill2_level + 1; // ��ų 2�� ��
            }
            if (skill_up == 0x33 && player_skill3_level < 5) {
                player_skill3_level = player_skill3_level + 1; // ��ų 3�� ��
            }
            if (skill_up == 0x34 && player_skill4_level < 5) {
                player_skill4_level = player_skill4_level + 1; // ��ų 4�� ��
            }
            if (skill_up == 0x35 && player_skill5_level < 5) {
                player_skill5_level = player_skill5_level + 1; // ��ų 5�� ��
            }

            // ��ų�� ��ȭ�� ���, ������ ���� ����
            if (skill_up == 0x31 || skill_up == 0x32 || skill_up == 0x33 || skill_up == 0x34 || skill_up == 0x35) {
                system("cls");         // ȭ�� ����
                skillchoose_message(); // ��ų ȭ�� ���
                printf("��ų ������ �ö����ϴ�. ��� �Ϸ��� �ƹ� Ű�� ��������.\n");
                _getch();
            }

        }

        // 3. ��ų ���� (��ų ����Ʈ�� ���� ���) 
        if (choose == 0x33 && player_skillpoint == 0) { 
            system("cls");
            skillchoose_message();
            printf("��ų ����Ʈ�� �����ϴ�.\n");
            _getch();
        }

        // 4. ���� ����
        if (choose == 0x34) { 

            menu_item = 1;

            for (;;)
            {
                system("cls");
                printf("���������������������������������������������������������������������������������������������������������������� \n");
                printf("��                 <<< ���� ���� >>>                    ��   \n");

                if (item_code == 0) { // ���� ���� ���Ⱚ�� ���� ���
                    printf("��             ���� �������� ���� : ����                ��  \n");
                }
                if (item_code == 1) {
                    printf("��           ���� �������� ���� : ������ ��           ��  \n");
                }
                if (item_code == 2){
                    printf("��          ���� �������� ���� : ������ ������          ��   \n");
                }
                if (item_code == 3) {
                    printf("��          ���� �������� ���� : ������ ������          ��    \n");
                }

                printf("����������������������������������������������������������������������������������������������������������������     \n");
                textcolor(YELLOW);
                printf("                ���� ������ ��� : %d                       \n", player_gold);

                textcolor(WHITE);
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

                if (item_choose == 0x31) // ���� 1. ������ ���� ���� �� ���
                {
                    if (player_gold >= 10000 && item_code == 0) // ���� ����ϰ�, �������� ���� ���� ���� ������ ��쿡��
                    {
                        printf("������ ���� ���� �߽��ϴ�.\n");
                        item_code = 1;  // ������ ������ �� ����
                        *item_att = player_att + 20;    // ���ݷ� ����
                        *item_mp = player_maxmp + 400;  // ���� ����
                        player_gold = player_gold - 10000;  // ��� ����
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

                if (item_choose == 0x32) // ���� 2. ����
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

                if (item_choose == 0x33) // ���� 3. ����
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

                if (item_choose == 0x34) // 4. ���� ���� ���� ����
                {
                    if (item_code == 1) // ���� 1���� ������ ��� �׸�ŭ�� ���� �ٽ� ��
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

                if (item_choose == 0x30) // 0. �ڷΰ��� ���� ���
                {
                    break;
                }
            }
        }

        // 5. ġƮ ����
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
                if (cheat == 1234) // ġƮ�� ���� ���
                {
                    printf("ü���� 100 �����մϴ�!\n");
                    player_maxhp = player_maxhp + 100; // �ɷ�ġ ���
                    c_value++;  // ġƮ ��� Ƚ�� ����
                    _getch();
                }
                else if (cheat == 2345)
                {
                    printf("������ 100 �����մϴ�!\n");
                    player_maxmp = player_maxmp + 100;
                    c_value++;
                    _getch();
                }
                else if (cheat == 4567)
                {
                    printf("���ݷ��� 20 �����մϴ�!\n");
                    player_att = player_att + 20;
                    c_value++;
                    _getch();
                }
                else if (cheat == 5678)
                {
                    printf("������ 10 �����մϴ�!\n");
                    player_defmain = player_defmain + 10;
                    c_value++;
                    _getch();
                }
                else if (cheat == 6789)
                {
                    printf("��尡 2000 ���� �մϴ�!\n");
                    player_gold = player_gold + 2000;
                    c_value++;
                    _getch();
                }
                else if (cheat == 7777)
                {
                    printf("���� ����Ʈ�� 1 �����մϴ�!\n");
                    player_statpoint = player_statpoint + 1;
                    c_value++;
                    _getch();
                }
                else if (cheat == 9999)
                {
                    printf("��ų ����Ʈ�� 1 �����մϴ�!\n");
                    player_skillpoint++;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1111)
                {
                    printf("�������� ������ 10���� ���� �Ǿ����ϴ�!\n");
                    stage_level = 10;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1134)
                {
                    printf("Admin mode enabled.\n");
                    player_gold = player_gold + 999999;
                    stage_level = 11;   // ��� �������� ����
                    player_statpoint = player_statpoint + 9999;
                    player_skillpoint = player_skillpoint + 9999;
                    _getch();
                }
                else if (cheat == 0) // �ڷ� ���� �Է�
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

        // 6. ���� ����
        if (choose == 0x36) 
        {
            int temp_speed; 
            temp_speed = speed; // �� ���� ���н� �ʱ� ������ �ǵ����� ���� ���� ����

            system("cls");
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

            if (speed == 0) // 0���� �����ϰų�, ���� ���� ���� ���
            {
                speed = temp_speed; // ���� �ӵ� �� ����
            }
            else if (speed < 100) // �ӵ��� �ʹ� �������
            {
                speed = temp_speed;
                printf("�ּ� 100 ���� ���� �մϴ�.\n");
                _getch();
                continue;
            }
            else if (speed > 2000) // �ʹ� ���� ���
            {
                speed = temp_speed;
                printf("�ִ� 2000 ���� ���� �մϴ�.\n");
                _getch();
                continue;
            }
            else if (speed >= 100 && speed <= 2000) // ���� ���� ���
            {
                printf("������ �Ϸ� �Ǿ����ϴ�.\n");
                _getch();
            }
            else
            {
                continue;
            }
        }

        // 7. ���� ����
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

        // 8. ���� ����
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

        // 0. Ŭ���� �ڵ� Ȯ�� ���� (�������� ��� Ŭ�����)
        if (choose == 0x30 && stage_level >= 11)
        {
            system("cls");
            printf(" CODE   : %d_%d_%d\n", win, lose, rating);
            printf("C_Value : %d\n", c_value);
            _getch();
        }

    } // for(;;)
} // int main(void)