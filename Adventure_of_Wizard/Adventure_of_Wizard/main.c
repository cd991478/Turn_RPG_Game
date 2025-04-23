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

int player_level = 1;   // 플레이어 캐릭터 레벨
int player_hp = 100;    // 플레이어 현재 체력
int player_maxhp = 100; // 플레이어 최대 체력
int player_mp = 100;    // 플레이어 현재 마나
int player_maxmp = 100; // 플레이어 최대 마나
int player_att = 10;    // 플레이어 공격력
int player_def = 0;     // 플레이어 방어력
int player_defup = 0;   // 플레이어 추가 방어력
int player_exp = 0;     // 플레이어 경험치
int player_maxexp = 100;// 플레이어 경험치 도달시 레벨업
int player_statpoint = 0;   // 남은 스탯 포인트
int player_skillpoint = 0;  // 남은 스킬 포인트

int player_gold = 0;    // 플레이어 보유 골드
int player_stun = 0;    // 플레이어의 기절 상태
int player_defmain = 0;
int player_dote = 0;    // 플레이어의 지속피해 상태
int player_dotecount = 0; // 플레이어의 지속피해 남은 횟수

int speed = 800;    // 상황판 텍스트 속도
int cheat;          // 치트키 코드
int c_value = 0;    // 치트키 사용 횟수
int play_time = 0;  // 플레이 타임
int time_h = 0;     // 시간
int time_m = 0;     // 분
int time_s = 0;     // 초
int defover_state = 0;  // 방어력 최대치 100 초과 상태
int win = 0;        // 승리 횟수
int lose = 0;       // 패배 횟수
int total = 0;      // 총 전투 횟수
int rating = 1000;  // 레이팅 점수
char rank[128] = "D";   // 랭크 등급

int player_skill1_level = 1;  // 스킬 1.파이어볼 레벨
int player_skill2_level = 1;  // 스킬 2.썬더볼트 레벨
int player_skill3_level = 1;  // 스킬 3.큐어 레벨
int player_skill4_level = 1;  // 스킬 4.가드업 레벨
int player_skill5_level = 1;  // 스킬 5.메디테이션 레벨

int player_skill1_maxlevel = 5;   // 스킬 1 최대 레벨
int player_skill2_maxlevel = 5;   // 스킬 2 최대 레벨
int player_skill3_maxlevel = 5;   // 스킬 3 최대 레벨
int player_skill4_maxlevel = 5;   // 스킬 4 최대 레벨
int player_skill5_maxlevel = 5;   // 스킬 5 최대 레벨


int com_level = 1;      // 컴퓨터 레벨
int com_hp = 100;       // 컴퓨터 현재 체력
int com_maxhp = 100;    // 컴퓨터 최대 체력
int com_att = 10;       // 컴퓨터 공격력
int com_def;            // 컴퓨터 방어력

int stage_level = 1;    // 도달한 스테이지
int goto_stage = 1;     // 진행할 스테이지

int menu_fight = 0;     
int menu_stat = 0;
int menu_skill = 0;
int menu_item = 0;

int turn = 0;           // 짝수 = 플레이어턴 // 홀수 = 컴퓨터턴
int com_skill;          // 컴퓨터 스킬

int* item_att;     // 메인에서 item_att = &player_att;
int* item_mp;      // 메인에서 item_mp = &player_maxmp;
int item_code = 0; // 장착한 아이템 번호

char order;
char stat_up;
char skill_up;
char choose;
char item_choose;

char stage01[] = { "용병" }; // 스테이지별 컴퓨터 이름
char stage02[] = { "전사" };
char stage03[] = { "저격수" };
char stage04[] = { "얼음 마법사" };
char stage05[] = { "번개 마법사" };
char stage06[] = { "화염 마법사" };
char stage07[] = { "천공 마법사" };
char stage08[] = { "암흑 마법사" };
char stage09[] = { "검객" };
char stage10[] = { "창의 달인" };


void window() // 테두리 생성
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
void intro_screen()
{
    window();       // 테두리
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
}

void d1s() // delay 1 second 1초 대기
{
    delay(speed);
}

void char_eft() // 캐릭터 기본 위치 출력
{
    textcolor(WHITE);
    gotoxy(20, 16);
    puts("　");
    gotoxy(50, 16);
    puts("　");
    gotoxy(20, 16); // 플레이어 캐릭터 기본 위치
    puts("옷");
    gotoxy(50, 16); // 컴퓨터 캐릭터 기본 위치
    puts("옷");
    gotoxy(0, 18); // 땅바닥 위치
    printf("──────────────────────────────────────────────────────────────────────────────\n");
}
void char_cls() // 캐릭터 화면 라인 지움
{
    gotoxy(0, 15);
    puts("                                                                                ");
    gotoxy(0, 16);
    puts("                                                                                ");
    gotoxy(0, 17);
    puts("                                                                                ");
}
void txt_cls() // 상황판 텍스트 지움
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
void txt_pos() // 상황판 위치로 이동
{
    gotoxy(0, 19);
}
void eft_set() // 이펙트 초기화 설정
{
    char_cls(); // 캐릭터 화면 지움
    char_eft(); // 캐릭터 화면 생성
    txt_cls();  // 상황판 문구 지움
    txt_pos();  // 상황판 위치 이동
}
void move_set() // 컴퓨터 캐릭터가 플레이어 앞에 달라붙은 상태에서 화면 갱신 효과
{
    textcolor(WHITE);
    gotoxy(0, 15);
    puts("                                                                                ");
    gotoxy(0, 16);
    puts("                                                                                ");
    gotoxy(0, 17);
    puts("                                                                                ");
    gotoxy(20, 16);
    puts("　");
    gotoxy(50, 16);
    puts("　");
    gotoxy(20, 16); // 플레이어 위치
    puts("옷");
    gotoxy(28, 16); // 플레이어 옆 위치의 컴퓨터
    puts("옷");
    gotoxy(0, 18);
    printf("──────────────────────────────────────────────────────────────────────────────\n");
}
void char_set() // 두 캐릭터 기본 좌표로 완전 초기화
{
    char_cls(); // 캐릭터 화면 지움
    char_eft(); // 두 캐릭터 기본 좌표에 생성
}

void playerhp_eft() // 플레이어 체력회복 이펙트
{
    gotoxy(19, 15);
    puts("+"); // 십자가 모양으로 체력 회복 효과
    delay(100);
    char_set(); // 모두 지움 및 생성
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
void playermp_eft() // 플레이어 마나회복 이펙트
{
    gotoxy(19, 15);
    puts("*"); // 빤짝이 모양으로 마나회복하는 효과
    delay(100);
    char_set(); // 모두 지움 및 생성
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
void playerdfup_eft() // 플레이어 가드업 이펙트
{
    gotoxy(22, 16); // 시계 방향으로 한바퀴 돌면서 사각형 만들고
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
    char_set(); // 지우고
    gotoxy(22, 16); // 단단한 장벽 두른 효과 출력
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
void comdfup_eft() // 컴퓨터 방어력 강화 스킬 이펙트
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
void playerboom_eft() // 플레이어 폭탄공격 피격 이펙트
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
void playerfreeze_eft() // 플레이어 얼음 공격 피격 이펙트
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
void playerthunder_eft() // 플레이어 번개공격 피격시 이펙트
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
void dote_eft() // 플레이어 지속 피해 피격 이펙트
{
    gotoxy(22, 15);
    puts("!"); // 느낌표로 캐릭터가 당황하는 효과
    delay(500);
    eft_set();
}
void comhp_eft() // 컴퓨터 체력회복 이펙트
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

void move_eft() // 컴퓨터 캐릭터의 근접 공격 사용시 플레이어에게 빠르게 달려오는 이펙트
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
void back_eft() // 컴퓨터 캐릭터가 플레이어로부터 원위치에 빠르게 되돌아가는 이펙트
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

void skill0_eft() // 플레이어 0번스킬 기본공격 이펙트
{
    int k;
    for (k = 22; k < 49; k++) // 마법화살이 빠르게 날라가는 효과
    {
        gotoxy(k, 16);
        puts("→"); 
        delay(10);
        gotoxy(k, 16);
        puts("　");
    }

    playermp_eft(); // 마나 회복 이펙트
    eft_set();
}
void skill1_eft()   // 플레이어 스킬 1 파이어볼 이펙트
{
    textcolor(ORANGE);
    int t;
    if (player_skill1_level == 1) // 스킬 레벨이 높아질수록 날라가는 속도를 빠르게 설정
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
    for (k = 22; k < 49; k++)   // 파이어볼 투사체 점멸하며 날라가는 효과
    {
        if (k % 2 == 0)
        {
            gotoxy(k, 16);
            puts("●");
            delay(t);
            gotoxy(k, 16);
            puts("　");
        }
        if (k % 2 == 1)
        {
            gotoxy(k, 16);
            puts("◎");
            delay(t);
            gotoxy(k, 16);
            puts("　");
        }
    }
    if (player_skill1_level == 1) // 스킬 1레벨시 적 타격 이펙트
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
    if (player_skill1_level >= 2) // 스킬 2레벨 이상시 적 타격 이펙트
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
        textcolor(ORANGE);
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
    textcolor(WHITE);
    eft_set();
}
void skill2_eft()   // 플레이어 스킬 2 썬더볼트 이펙트
{
    textcolor(YELLOW);
    int t=30;
    if (player_skill2_level == 1) // 스킬 레벨이 높을수록 속도 빠르게
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
    for (k = 22; k < 49; k = k + 2) // 전기 MMMMM 형태로 날라가는 이펙트
    {
        gotoxy(k, 16);
        puts("／");
        delay(t);

        gotoxy(k + 2, 16);
        puts("＼");
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
    for (i = 0; i < p; i++) // 플레이어로부터 적 위치까지 날라간 전기가 요동치는 효과 + 별이 점멸하며 적이 감전 당하는 효과
    {
        for (k = 22; k < 49; k = k + 2) // 번개 줄기 WWWWW 형태 생성
        {
            gotoxy(k, 16);
            puts("＼");
            gotoxy(k + 2, 16);
            puts("／");
            k = k + 2;
        }
        gotoxy(48, 16); // 적 타격 효과 생성
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
        char_set(); // 캐릭터 스크린 초기화
        textcolor(YELLOW);
        for (k = 22; k < 49; k = k + 2) // 역 번개 줄기 MMMMM 형태 생성
        {
            gotoxy(k, 16);
            puts("／");
            gotoxy(k + 2, 16);
            puts("＼");
            k = k + 2;
        }
        delay(t * 2);
    }
    textcolor(WHITE);
    eft_set();
}
void skill3_eft() // 플레이어 스킬 3 큐어
{
    playerhp_eft(); // 플레이어 체력 회복 이펙트
    eft_set();
}
void skill4_eft() // 플레이어 스킬 4 가드업
{
    playerdfup_eft(); // 플레이어 방어 장막 이펙트
    eft_set();
}
void skill5_eft() // 플레이어 스킬 5 메디테이션
{
    playermp_eft(); // 플레이어 마나 회복 이펙트
    eft_set();
}

void gunshot_eft() // 컴퓨터 스킬 총기 사격 이펙트
{
    int k;
    for (k = 48; k > 21; k--) // 좌측으로 총알이 날라가는 효과
    {
        gotoxy(k, 16);
        puts("-");
        delay(10);
        gotoxy(k, 16);
        puts("　"); 
    }
    eft_set();
}
void gunshot_eft2() // 컴퓨터 스킬 총기 난사 이펙트
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
void boom_eft() // 컴퓨터 스킬 수류탄 투척 이펙트
{
    int k;
    for (k = 48; k > 21; k=k-2) // 수류탄 좌측으로 날라가는 효과
    {
        gotoxy(k, 16);
        puts("●"); 
        delay(20);
        gotoxy(k, 16);
        puts("　");
    }
    playerboom_eft(); // 플레이어 폭파 효과
}
void sword_eft() // 컴퓨터 스킬 검기 파동 이펙트
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
        puts("　");
    }
    eft_set();
}
void roar_eft() // 컴퓨터 스킬 포효 이펙트
{
    gotoxy(48, 15);
    puts("＼"); // 컴퓨터 캐릭터가 왼쪽 방향으로 소리 내는듯한 효과
    gotoxy(48, 16);
    puts("──"); // ""
    gotoxy(48, 17);
    puts("／"); // ""
    gotoxy(46, 16);
    puts("!"); // 느낌표를 출력하여 외치는듯한 효과
    d1s(); // speed초 대기 0.8 sec
    gotoxy(42, 15);
    puts("!");
    d1s();
    gotoxy(44, 17);
    puts("!");
    d1s();
    eft_set();
}
void powerslash_eft() // 컴퓨터 스킬 칼날 베기 이펙트
{
    move_eft(); // 화면 오른쪽의 컴퓨터 캐릭터가 왼쪽의 플레이어 캐릭터 앞으로 달려옴
    gotoxy(22, 15);
    puts("／"); // 플레이어 오른쪽 위에서 
    delay(50);
    move_set(); 
    gotoxy(20, 16);
    puts("／");
    delay(50);
    move_set();
    gotoxy(18, 17);
    puts("／"); // 플레이어 왼쪽 아래를 향해 칼로 베는듯한 효과
    delay(100);
    gotoxy(18, 15);
    puts("＼"); // 플레이어 왼쪽 상단에서
    delay(50);
    move_set();
    gotoxy(20, 16);
    puts("＼");
    delay(50);
    move_set();
    gotoxy(22, 17);
    puts("＼"); // 플레이어 오른쪽 하단을 향해 칼로 베는듯한 효과 // 반복문으로 교체 가능
    delay(100); 
    move_set();
    gotoxy(22, 15);
    puts("／"); // 반복
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
    move_set(); // 컴퓨터가 플레이어앞에 다가온 상태일때 초기화
    back_eft(); // 왼쪽의 컴퓨터가 다시 자기 위치인 오른쪽으로 돌아감
    eft_set();
}
void sniper_eft() // 컴퓨터 스킬 저격 이펙트
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("──"); // 길고 굵은 저격총 탄환 발사 효과
        delay(5);
        gotoxy(k, 16);
        puts("　");
    }
    eft_set();
}
void focus_eft() // 컴퓨터 능력치 강화 버프 스킬 정신 집중 이펙트
{
    gotoxy(48, 16); // 좌우 번갈아서 화살표가 위로올라가는 효과를 반복함으로써 무언가 상승하는듯한 효과
    puts("↑"); // 컴퓨터 캐릭터 왼쪽 아래에서 상단으로 화살표가 올라감
    delay(100);
    char_set();
    gotoxy(48, 15);
    puts("↑");
    delay(100);
    char_set();
    gotoxy(52, 16); // 컴퓨터 캐릭터 오른쪽 아래에서 상단으로 화살표가 올라감
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
void headshot_eft() // 컴퓨터 스킬 헤드샷 이펙트
{
    int k;
    gotoxy(20, 15); // 플레이어 캐릭터를 ┼ 모양으로 조준하는 효과
    puts("│"); // 플레이어 캐릭터 상단의 십자선
    gotoxy(20, 17);
    puts("│"); // 플레이어 캐릭터 하단의 십자선
    gotoxy(18, 16);
    puts("──"); // 플레이어 캐릭터 좌측의 십자선
    gotoxy(22, 16);
    puts("──"); // 플레이어 캐릭터 우측의 십자선
    delay(500);
    char_set();
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("──"); // 굵고 큰 총알 발사 이펙트
        delay(5);
        gotoxy(k, 16);
        puts("　");
    }
    eft_set();
}
void ice_eft() // 컴퓨터 스킬 아이스 빔 이펙트
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 16);
        puts("◇"); // 얼음 덩어리 투척 효과
        delay(20);
        gotoxy(k, 16);
        puts("　");
    }
    playerfreeze_eft(); // 플레이어 피격시 얼어붙는 효과
}
void blizzard_eft() // 컴퓨터 스킬 얼음폭풍 이펙트
{
    int k;
    for (k = 48; k > 21; k--)
    {
        gotoxy(k, 15);
        puts("*");          // 3 x 3 의 눈보라가 날라가는 효과
        gotoxy(k - 2, 15);  // 다음과 같은 모양으로 날라감
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
    playerfreeze_eft(); // 플레이어 얼어붙는 효과
}
void thunder_eft() // 컴퓨터 스킬 번개 강타 이펙트
{
    int k;
    for (k = 48; k > 21; k = k - 2)
    {
        gotoxy(k, 16);
        puts("／"); // MMM 형태의 번개 오른쪽에서 왼쪽으로 발사
        delay(20);
        gotoxy(k - 2, 16);
        puts("＼");
        delay(20);
        k = k - 2;
    }
    char_set(); // 캐릭터 스크린 초기화 하여 번개 효과 지움
    playerthunder_eft(); // 플레이어 감전 당하는 이펙트 반복
    delay(100);          // ☆☆☆
    char_set();          // ☆옷☆
    delay(100);          // ☆☆☆
    playerthunder_eft();
    delay(100);
    char_set();
    delay(100);
    playerthunder_eft();
    delay(100);
    eft_set();
}
void powerthunder_eft() // 컴퓨터 스킬 심판의 번개 이펙트
{
    int k;
    int t;
    for (t = 0; t < 10; t++)  // 번개 줄기가 출렁이며 플레이어가 치명적으로 감전 당하는 효과
    {
        for (k = 48; k > 21; k = k - 2) // 번개 줄기 MMM 형태 즉시 출력 (발사X)
        {
            textcolor(YELLOW);
            gotoxy(k, 16);              // ／＼／＼／＼／＼／＼
            puts("／");
            gotoxy(k - 2, 16);
            puts("＼");
            k = k - 2;
        }
        gotoxy(20, 15);     // 플레이어 감전 이펙트 1 (+ 형태)
        puts("│");
        gotoxy(22, 16);     //   │
        puts("──");       //  ㅡ옷ㅡ
        gotoxy(20, 17);     //   │
        puts("│");
        gotoxy(18, 16);
        puts("──");
        delay(50);
        char_set();         // 모두 지움

        for (k = 48; k > 21; k = k - 2) // 번개줄기 WWW형태 즉시 출력 (발사X)
        {
            textcolor(YELLOW);
            gotoxy(k, 16);              // ＼／＼／＼／＼／＼／
            puts("＼");
            gotoxy(k - 2, 16);
            puts("／");
            k = k - 2;
        }
        gotoxy(22, 15);     // 플레이어 감전 이펙트 2 (x 형태)
        puts("／");
        gotoxy(22, 17);     //  ＼  ／
        puts("＼");         //    옷
        gotoxy(18, 17);     //  ／  ＼
        puts("／");
        gotoxy(18, 15);
        puts("＼");
        delay(50);
        char_set();         // 모두 지움
    }
    eft_set();
}
void fireshot_eft() // 컴퓨터 스킬 화염 분사 이펙트
{
    int k;
    int t;
    for (k = 48; k > 21; k = k - 2)
    {   
        gotoxy(k, 16); puts("§");       // 화염 줄기 발사 효과
        delay(20);                       // 옷§　§　§　§　§　§　§  옷
    }
    char_set();     // 이펙트 지움

    for (t = 0; t < 4; t++)              // 화염 줄기 지속으로 뿜는 효과 + 뿜는동안 플레이어 불타는 효과
    {                                    // 옷§　§　§　§　§　§　§  옷
        for (k = 48; k > 21; k = k - 4)  // 옷  §　§　§　§　§　§　§옷
        {                                
            gotoxy(k, 16); puts("§");   
        }
        playerboom_eft();   // 플레이어 폭파 이펙트
        delay(50);
        char_set();
        for (k = 46; k > 21; k = k - 4)
        {
            gotoxy(k, 16); puts("§");
        }
        playerboom_eft();
        delay(50);
        char_set();
    }
    eft_set();
}
void warmup_eft() // 컴퓨터 강화 버프 스킬 발열 이펙트
{
    int k;
    for (k = 0; k < 3; k++)
    {
        gotoxy(50, 15);
        puts("♨");  // 뜨거워지는 느낌의 효과
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
void firepunch_eft() // 컴퓨터 스킬 화염주먹강타 스킬
{
    int k;
    move_eft(); // 컴퓨터가 플레이어 앞으로 달려옴
    
    for (k = 0; k < 4; k++) // 바로앞에서 주먹을 날려서 때리는 효과 + 치명적으로 얻어 맞고 불타는 효과 반복
    {
        textcolor(ORANGE);
        gotoxy(26, 16);     // 주먹 날리는 효과
        puts("◎");         
        delay(50);          //　옷　　◎옷
        move_set();
        textcolor(ORANGE);
        gotoxy(24, 16);     //　옷　◎　옷
        puts("◎");
        delay(50);          //　옷◎　　옷
        move_set();
        textcolor(ORANGE);
        gotoxy(22, 16);
        puts("◎");
        delay(50);
        move_set();
        textcolor(LIGHTRED);
        gotoxy(18, 17);      // 피격 당하는 효과
        puts("♨");          // 아래에서 위로 열기가 올라감
        gotoxy(20, 17);      //　옷　　　옷
        puts("♨");          //♨♨♨
        gotoxy(22, 17);
        puts("♨");          //♨옷♨　　옷
        delay(20);          
        move_set();          //♨♨♨
        textcolor(LIGHTRED); //　옷　　　옷
        gotoxy(18, 16);      
        puts("♨");
        gotoxy(22, 16);
        puts("♨");
        delay(20);
        move_set();
        textcolor(LIGHTRED);
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
void fireblast_eft() // 컴퓨터 스킬 화염 포효 이펙트
{
    int k;
    for (k = 48; k > 21; k--) // 화염 줄기를 즉시 분사하고 요동치는 효과
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
void windbind_eft() // 컴퓨터 스킬 바람 감옥 이펙트
{
    int k;
    for (k = 48; k > 21; k--)   // 바람 기류를 날리는 효과
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
void absorb_eft() // 컴퓨터 회복 스킬 흡수 이펙트
{
    int k;
    int t;
    for (t = 0; t < 4; t++)
    {
        for (k = 22; k < 49; k++) // 플레이어로부터 에너지를 흡수하는듯한 효과
        {                         // 플레이어 위치에 * 을 생성하여 오른쪽으로 이동 4회 반복
            gotoxy(k, 16);
            puts("＊");
            delay(10);
            gotoxy(k, 16);
            puts("　");
        }
    }
    eft_set();
}
void windstorm_eft() // 컴퓨터 스킬 바람감옥으로 인한 속박 상태이상 지속 이펙트
{
    int k;
    for (k = 0; k < 6; k++) // 허리케인이 요동치며 플레이어를 속박하는듯한 효과
    {
        gotoxy(18, 15);     //　　　　~
        puts("~");          //　　　　  ~
        gotoxy(22, 16);     //　　　　    ~
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
void darkbeam_eft() // 컴퓨터 스킬 어둠의 파동 이펙트
{
    int k;
    for (k = 48; k > 21; k = k - 2) // 파동 줄기 분사 효과
    {
        gotoxy(k, 16);
        puts("●");
        delay(20);
    }
    gotoxy(22, 15); // 플레이어 피격 효과
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
void silence_eft() // 컴퓨터 상태이상 스킬 침묵 이펙트
{
    int k;
    for (k = 48; k > 21; k--) // 구체를 날림
    {
        gotoxy(k, 16);
        puts("⊙");
        delay(10);
        gotoxy(k, 16);
        puts("　");
    }
    delay(200);
    gotoxy(22, 15);
    puts("!"); // 플레이어 캐릭터에게 느낌표를 출력하여 침묵 당한 느낌 효과
    delay(500);
    eft_set();
}
void empower_eft() // 컴퓨터 디버프 스킬 약화 이펙트
{
    int k;
    for (k = 0; k < 2; k++) // 컴퓨터 능력치 강화 스킬인 집중 이펙트와 반대로 적용
    {                       // 플레이어 왼쪽 오른쪽 번갈아 화살표가 아래로 내려가는 효과
        gotoxy(18, 15);     // 능력이 저하되는 느낌의 효과
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
void swiftsword_eft() // 컴퓨터 스킬 날렵한 검기 스킬
{
    int k;
    int t;
    for (t = 0; t < 2; t++)
    {
        textcolor(BLUEGREEN);
        gotoxy(48, 15); // 컴퓨터 앞에 날카로운 검기 느낌의 이펙트를 뽑아냄
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
        for (k = 42; k > 22; k = k - 2) // 해당 검기를 플레이어를 향해 빠르게 발사
        {
            textcolor(LIGHTGREEN);
            gotoxy(k, 15);          
            puts("／");             
            gotoxy(k - 2, 16);
            puts("／");
            gotoxy(k - 4, 17);
            puts("／");
            delay(10);
            char_set();
        }
        textcolor(BLUEGREEN);
        gotoxy(44, 15); // 다시 컴퓨터 앞에 역방향 모양의 검기 이펙트를 생성
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
        for (k = 44; k > 18; k = k - 2) // 해당 역방향 검기를 플레이어를 향해 빠르게 발사
        {
            textcolor(LIGHTGREEN);
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
void sworddance_eft() // 컴퓨터 능력치 강화 버프 스킬 칼의춤 이펙트
{
    int k;
    for (k = 0; k < 2; k++) // 컴퓨터 캐릭터가 칼을들고 춤을 추는듯한 느낌의 효과 반복
    {
        gotoxy(48, 15);     //      │      
        puts("│");         //      ┼옷
        gotoxy(48, 16);     
        puts("┼");
        delay(200);
        char_set();
        gotoxy(52, 15);     //          │
        puts("│");         //        옷┼
        gotoxy(52, 16);
        puts("┼");
        delay(200);
        char_set();
    }
    eft_set();
}
void armorbash_eft() // 컴퓨터 스킬 갑옷 베기 이펙트
{
    int k;
    move_eft(); // 컴퓨터 캐릭터가 왼쪽으로 달려옴

    for (k = 0; k < 3; k++) // 플레이어 캐릭터를 칼로 베는듯한 효과 반복
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
    back_eft(); // 컴퓨터 캐릭터 원위치로 후퇴
    eft_set();
}
void bleedslash_eft() // 컴퓨터 지속 피해 스킬 출혈 이펙트
{
    move_eft();     // 컴퓨터 캐릭터가 달려옴
    gotoxy(22, 16); // 플레이어 캐릭터를 칼로 깊숙히 찌르는 효과 
    puts("──");   //   옷ㅡ옷
    delay(20);
    move_set();
    gotoxy(20, 16); 
    puts("──");   //   ㅡ  옷
    delay(20);
    move_set();
    gotoxy(18, 16); 
    puts("──");   // ─옷  옷
    delay(20);      
    move_set();
    gotoxy(20, 16);
    puts("──");   //   ㅡ  옷
    delay(20);      
    move_set();
    gotoxy(22, 16);
    puts("──");   //   옷ㅡ옷
    delay(20);      
    move_set();
    back_eft();     // 컴퓨터 캐릭터 원위치로 후퇴
    eft_set();
}
void triplespear_eft() // 컴퓨터 스킬 삼조격 이펙트
{
    int k;
    move_eft(); // 컴퓨터 캐릭터 달려옴
    move_set();
    delay(100);
    for (k = 0; k < 3; k++) // 3번 찌름
    {
        if (k != 0)
        {
            gotoxy(24, 16); // 컴퓨터 캐릭터가 창을 든 효과
            puts("──");
            gotoxy(26, 16);
            puts("──");
            gotoxy(30, 16);
            puts("──");
            delay(200);
            move_set();
        }
        gotoxy(22, 16); // 창을 찌르는 효과
        puts("──");
        gotoxy(24, 16);
        puts("──");
        gotoxy(26, 16);
        puts("──");
        if (k == 2) // 3번째 찌르기에서 플레이어 캐릭터가 공중으로 튀어오르는 효과
        {
            gotoxy(20, 16);
            puts("　");
            gotoxy(20, 15);
            puts("옷");
        }
        delay(100);
        move_set();
    }
    gotoxy(24, 16); // 창 원위치 효과
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
void challenge_eft() // 컴퓨터 스킬 도전 이펙트
{
    move_eft(); // 컴퓨터 캐릭터가 플레이어 캐릭터에게 다가와 포효하는 효과
    gotoxy(26, 15);
    puts("!");
    delay(500);
    move_set();
    back_eft();
    eft_set();
}
void molwang_eft() // 컴퓨터 스킬 몰락한 왕의 검 이펙트
{
    int k;
    for (k = 22; k < 49; k = k + 2) // 플레이어로부터 기운을 흡수하는 느낌의 효과
    {
        gotoxy(k, 16);
        puts("〓");
        delay(10);
    }
    for (k = 22; k < 49; k = k + 2) // 기운을 흡수하는 줄기 이펙트를 순차 소멸
    {
        gotoxy(k, 16);
        puts("　");
        delay(10);
    }
    comhp_eft(); // 컴퓨터 체력 회복 이펙트
    eft_set();
}
void spearsweep_eft() // 컴퓨터 스킬 초승달 휩쓸기 이펙트
{
    move_eft();     // 컴퓨터 캐릭터가 달려오는 효과
    delay(30);
    gotoxy(24, 16);     // 반시계 방향으로 창을 360도 회전 시키며 돌리는 효과
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

void statchoose_message() // 스탯 포인트 있을경우 스탯 강화 화면
{
    printf("┌──────────────────────────────────────────────────────────────────┐\n");
    printf("│               향상 시킬 능력치를 선택 하세요.                    │    \n");

    printf("│   ");
    textcolor(LIGHTGREEN);
    printf("1.체력 +50   ");

    textcolor(SKYBLUE);
    printf("2.마나 +50   ");
    textcolor(WHITE);
    printf("3.공격력 +10   4.방어력 +5   5.취소  │      \n");

    printf("└──────────────────────────────────────────────────────────────────┘\n");
}
void statchoose(int a) // 선택한 스탯 번호에 따라 스탯 강화
{
    if (a == 1) { // 체력 증가
        player_maxhp = player_maxhp + 50;
    }
    if (a == 2) { // 마나 증가
        player_maxmp = player_maxmp + 50;
    }
    if (a == 3) { // 공격력 증가
        player_att = player_att + 10;
    }
    if (a == 4) { // 방어력 증가
        if (player_defmain >= 100) // 방어력이 너무 높은경우
        {
            player_statpoint++; // 스탯 포인트 환불
            defover_state = 1;  // 방어력 한도 설정 ON
        }
        if (player_defmain + 5 <= 100) // 강화하여도 한도치보다 낮은경우에만 방어력 증가
        {
            player_defmain = player_defmain + 5;
        }
    }
}
void playerstat_message() // 스탯 메뉴 화면
{
    printf("┌────────────────────────────┐\n");
    printf("│       <<< 스탯 >>>\n");
    printf("│ 직업   : 마법사\n");
    printf("│ 레벨   : %d\n", player_level);
    printf("│ "); 
    textcolor(LIGHTGREEN);
    printf("체력   : %d / %d\n", player_hp, player_maxhp);
    textcolor(WHITE);
    printf("│ ");
    textcolor(SKYBLUE);
    printf("마나   : %d / %d\n", player_mp, player_maxmp);
    textcolor(WHITE);
    printf("│ 공격력 : %d\n", player_att);
    printf("│ 방어력 : %d\n", player_defmain);
    printf("│ ");
    textcolor(ORANGE);
    printf("경험치 : %d / %d (%.2f%%)\n", player_exp, player_maxexp, (float)player_exp / (float)player_maxexp * 100);
    textcolor(WHITE);
    printf("│ ");
    textcolor(YELLOW);
    printf("보유한 골드 : %d\n", player_gold);
    textcolor(WHITE);
    printf("└────────────────────────────┘\n");
    int k;
    for (k = 1; k < 10; k++)
    {
        gotoxy(29, k);
        puts("│");
    }
    gotoxy(0, 11);
   
}

void menu_choose() // 메인 메뉴 화면
{
    printf("┌────────────────────────────────────────────────────────────────────┐   \n");
    printf("│                         무엇을 하시겠습니까?                       │ \n");
    printf("│  1.전투  2.스탯  3.스킬  4.무기  5.치트  6.설정  7.도움말  8.정보  │  \n");
    printf("└────────────────────────────────────────────────────────────────────┘    \n");

    if (stage_level >= 11)
    {
        printf("   축하드립니다! 모든 스테이지를 클리어 하였습니다.\n");
        printf("     클리어 코드를 확인 하려면 숫자 0을 누르세요.\n");
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
}

int skill_1() // 플레이어 스킬 1 파이어볼 피해량 계산
{
    int d; // 스킬 표기와는 별도로, 내부적으로 플레이어 레벨과, 공격력이 높아질경우에도 수치가 증가하도록 설정
    d = (player_level * 10) + (player_att / 2) + (player_skill1_level * 20);
    return d;
}
int skill_2() // 플레이어 스킬 2 썬더볼트 피해량 계산
{
    int d;
    d = (player_level * 9) + (player_att / 2) + (player_skill2_level * 18);
    return d;
}
int skill_3() // 플레이어 스킬 3 큐어 회복량 계산
{
    int d;
    d = (player_level * 10) + (player_skill3_level * 15) + (player_maxhp / 20) + (player_maxmp / 20);
    return d;
}
int skill_4() // 플레이어 스킬 4 가드업 방어력 증가량 수치 계산
{
    int d;
    d = (player_skill4_level * 2) + (player_maxhp / 100);
    return d;
}
int skill_5() // 플레이어 스킬 5 메디테이션 마나 회복량 % 수치 계산
{
    int d;
    d = 45 + (player_skill5_level * 5) + (player_maxhp / 100);
    return d;
}

void skillchoose_message() // 스킬 메뉴 화면
{
    printf("┌──────────────────────────────────────────────────────────────────┐   \n");
    printf("│                <<< 강화할 스킬을 선택하세요 >>>                  │  \n");
    printf("│ 1. 파이어 볼 (%d레벨/5)                                           │\n", player_skill1_level);
    printf("│   - 적을 공격하여 %d만큼의 피해를 입힘(+20)                        \n", skill_1());
    printf("│                                                                  │  \n");
    printf("│ 2. 썬더 볼트 (%d레벨/5)                                           │   \n", player_skill2_level);
    printf("│   - 적에게 %d만큼의 피해를 입히고, 방어력을 %d 감소시킴(+18,+2)     \n", skill_2(), player_skill2_level * 2);
    printf("│                                                                  │  \n");
    printf("│ 3. 큐어 (%d레벨/5)                                                │   \n", player_skill3_level);
    printf("│   - 자신의 체력을 %d만큼 회복함(+15)                               \n", skill_3());
    printf("│                                                                  │ \n");
    printf("│ 4. 가드 업 (%d레벨/5)                                             │  \n", player_skill4_level);
    printf("│   - 전투동안 자신의 방어력을 %d만큼 증가 시킴(+2)                   \n", skill_4());
    printf("│                                                                  │  \n");
    printf("│ 5. 메디테이션 (%d레벨/5)                                          │  \n", player_skill5_level);
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

void stat_restore() // 스탯, 각종 전투 상태 변수 초기화
{
    player_hp = player_maxhp; // 체력 원상복구
    player_mp = player_maxmp; // 마나 원상복구
    player_defup = 0;         // 방어력 상승폭 초기화
    player_def = player_defmain; // 전투중 방어력을 기본 방어력으로 초기화
    com_hp = com_maxhp;          // 컴퓨터 체력을 초기화
    player_dotecount = 0;        // 플레이어 지속 피해를 초기화
    player_stun = 0;             // 플레이어 기절 상태를 초기화
    turn = 0;                    // 턴을 초기화
}
void stat_over() // 스탯 오버시 재설정
{
    if (player_hp < 0) { // 체력 음수 처리
        player_hp = 0;
    }
    if (player_hp > player_maxhp) { // 체력 최대치 초과 처리
        player_hp = player_maxhp;
    }
    if (player_mp < 0) { // 마나 음수 처리
        player_mp = 0;
    }
    if (player_mp > player_maxmp) { // 마나 최대치 초과 처리
        player_mp = player_maxmp;
    }
    if (player_def < 0) { // 전투 방어력 음수 처리
        player_def = 0;
    }
    if (player_defup < 0) { // 방어력 상승폭 음수 처리
        player_defup = 0;
    }
    if (player_defmain < 0) { // 메인 방어력 음수 처리
        player_defmain = 0;
    }
    if (com_hp < 0) { // 컴퓨터 체력 음수 처리
        com_hp = 0;
    }
    if (com_hp > com_maxhp) { // 컴퓨터 체력 최대치 초과 처리
        com_hp = com_maxhp;
    }
    if (com_def < 0) { // 컴퓨터 방어력 음수 처리
        com_def = 0;
    }
    if (player_def + player_defup > 100)    // 플레이어 방어력이 한도치를 초과한경우 처리
    {
        for (; player_def + player_defup > 100;) // 100을 초과하면 100이 되도록 설정
        {
            player_defup--;
        }
    }
    if (player_defmain > 100)   // 플레이어 메인 방어력 한도치 초과 처리
    {
        for (; player_defmain > 100;)
        {
            player_defmain--;
        }
    }
    if (com_def > 100) // 컴퓨터 방어력 한도치 초과 처리
    {
        for (; com_def > 100;)
        {
            com_def--;
        }
    }
}

void stage_name(int a) // 전투 화면 최상단 스테이지 이름 출력
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
void fight_stat() // 전투 화면 스탯 정보창 출력
{
    printf("┌──────");
    textcolor(LIGHTGREEN);
    printf("<플레이어>"); 
    textcolor(WHITE);
    printf("────────────────────────────────────");
    textcolor(LIGHTRED);
    printf("<적>");
    textcolor(WHITE);
    printf("──────────────────┐\n");
    printf("│  ");
    textcolor(LIGHTGREEN);
    printf(" 체력 : %d / %d                            체력 : %d / %d          \n", player_hp, player_maxhp, com_hp, com_maxhp);
    textcolor(WHITE);
    printf("│  ");
    textcolor(SKYBLUE);
    printf(" 마나 : %d / %d                                                  \n", player_mp, player_maxmp);
    textcolor(WHITE);
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
void fight_skill() // 전투 화면 스킬 정보창 출력
{
    
    printf("├────────────────");
    textcolor(YELLOW);
    printf("< 스킬을 사용하려면 숫자 버튼을 누르세요 >");
    textcolor(WHITE);
    printf("────────────────┤\n");
    printf("│     1.파이어 볼 (20 마나) : %d 의 피해를 입힘                           \n", skill_1());
    printf("│     2.썬더 볼트 (25 마나) : %d 의 피해를 입히고, 방어력을 %d 감소시킴    \n", skill_2(), player_skill2_level * 2);
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

void com_demage(int a) // 플레이어가 컴퓨터에게 공격한 데미지 적용
{
    if (a > com_def) { // 가한 피해량이 적의 방어력보다 높은경우
        printf("적이 %d 만큼의 피해를 받았습니다. \n", a - com_def);
        com_hp = com_hp - (a)+com_def;
    }
    if (a <= com_def) { // 방어력이 더 높은경우
        printf("적이 1 만큼의 피해를 받았습니다.\n");
        com_hp = com_hp - 1;
    }
}
void player_demage(int a) // 플레이어가 공격 당한경우 피해 적용
{
    if (a > (player_def + player_defup)) { // 데미지가 (전투중 기본방어력 + 상승 방어력) 보다 높은경우
        printf("%d 만큼의 피해를 받았습니다. \n", a - (player_def + player_defup));
        player_hp = player_hp - (a)+player_def + player_defup;
    }
    if (a <= (player_def + player_defup)) { // 방어력이 더 높은 경우
        printf("1 만큼의 피해를 받았습니다.\n");
        player_hp = player_hp - 1;
    }
}
void player_hpdown(int a) // 플레이어 체력 감소 효과 적용 (직접 공격 당하지않은 경우에서)
{
    printf("체력이 %d 만큼 감소합니다. \n", a);
    player_hp = player_hp - a;
}
void com_defup(int a) // 컴퓨터 방어력 증가 효과 적용
{
    printf("적의 방어력이 %d 만큼 올랐습니다. \n", a);
    com_def = com_def + a;
}
void com_defdown(int a) // 컴퓨터 방어력 감소 효과 적용
{
    printf("적의 방어력이 %d 만큼 감소 했습니다. \n", a);
    com_def = com_def - a;
}
void com_attup(int a) // 컴퓨터 공격력 증가 효과 적용
{
    printf("적의 공격력이 %d 만큼 증가 했습니다. \n", a);
    com_att = com_att + a;
}
void player_defdown(int a) // 플레이어 방어력 감소 효과 적용
{
    printf("방어력이 %d 만큼 감소합니다.\n", a);

    if (player_defup == 0) { // 방어력 증가 수치가 없을때
        player_def = player_def - a; // 기본 방어력을 감소
    }
    else if (player_defup < a && player_defup > 0) // 방어력 증가 수치가 약간있고(디버프 수치보다는 적은), 기본 방어력이 0 이상일때
    {
        player_defup = player_defup - a;    // 방어력 증가수치를 뺌 (이 값은 음수가됨)
        player_def = player_def + player_defup; // 그리고 기본 방어력에 음수를 더하여 적용
        player_defup = 0; // 방어력 증가량 초기화
    }
    else if (player_defup >= a) {   // 방어력 상승폭이 디버프 수치보다 큰경우
        player_defup = player_defup - a; // 방어력 상승폭에서 그냥 뺌
    }

}
void player_hpup(int a) // 플레이어 체력 회복 적용
{
    printf("체력이 %d 만큼 회복 됩니다.\n", a);
    player_hp = player_hp + a;
}
void player_mplose(int a) // 플레이어 마나 피해 적용
{
    printf("마나가 %d 만큼 감소합니다.\n", a);
    player_mp = player_mp - a;
}
void com_hpup(int a) // 컴퓨터 체력 회복 적용
{
    if (a >= 0) {
        printf("적의 체력이 %d 만큼 회복 됩니다.\n", a);
        com_hp = com_hp + a;
    }
    if (a < 0) {
        printf("적의 체력이 1 만큼 회복 됩니다.\n");
        com_hp = com_hp + 1;
    }
}
void player_mpup(int a) // 플레이어 마나 회복 적용
{
    printf("마나가 %d 만큼 회복 됩니다.\n", a);
    player_mp = player_mp + a;
}
void player_mppup(int a) // 플레이어 마나 회복 퍼센트 적용
{
    printf("마나가 %d%% 만큼 회복 됩니다.\n", a);
    player_mp = player_mp + (player_maxmp * (a) / 100);
}
void player_mpdown(int a) // 플레이어 마나 감소 적용 (스킬 사용시)
{
    player_mp = player_mp - a;
}
void nomp() // 플레이어 스킬 사용 마나 부족 문구 출력
{
    printf("마나가 부족합니다.\n");
}


void player_skill(char a) // 전투중 입력받은 스킬 번호에 따라 스킬 사용
{
    // 숫자 0 기본공격 사용 (마나 없이 사용가능)
    if (a == 0x30) {    
        printf("<0. 기본 공격>을 사용 했습니다.\n");
        d1s();          // 대기 (기본값 0.8초)
        skill0_eft();   // 이펙트 출력
        d1s();          // 대기
        com_demage(player_att); // 피해 문구 출력 및 데미지 계산
        d1s();          // 대기
        player_mpup(player_att + (player_maxmp / 20));  // 마나 회복 문구 출력 및 적용
        d1s();          // 대기
        turn++;         // 턴을 상대방에게 넘김
    }

    // 숫자 1 파이어볼 사용 했는데 마나가 불충분한 경우
    if (a == 0x31 && player_mp < 20) { 
        nomp(); // 마나 부족 문구 출력
        d1s();  // speed초 대기 (기본값 800sec)
    }
    // 숫자 1 파이어볼 사용 했는데 마나가 충분한경우
    if (a == 0x31 && player_mp >= 20) { 
        printf("<1. 파이어 볼>을 사용 했습니다.\n"); // 문구 출력
        d1s();
        skill1_eft(); // 파이어볼 이펙트
        d1s();
        if (goto_stage == 6) // 현재 스테이지가 6인경우 (화염 마법사)
        {
            printf("적은 화염 속성에 면역입니다.\n");
            d1s();
            printf("피해를 받지 않습니다.\n");
        }
        if (goto_stage != 6) // 스테이지가 6이 아닌경우
        {
            com_demage(skill_1()); // 컴퓨터에게, 스킬 1 파이어볼 데미지 적용
        }
        d1s();
        player_mpdown(20); // 플레이어 마나 소모
        turn++;            // 턴 넘김
    }

    // 숫자 2 썬더볼트 사용 했는데 마나가 불충분한 경우
    if (a == 0x32 && player_mp < 25) { 
        nomp();
        d1s();
    }
    // 숫자 2 썬더볼트 사용 했는데 마나가 충분한 경우
    if (a == 0x32 && player_mp >= 25) {
        printf("<2. 썬더 볼트>를 사용 했습니다.\n");
        d1s();
        skill2_eft();        // 썬더 볼트 이펙트 출력
        d1s();
        if (goto_stage == 5) // 스테이지 5 번개 마법사 인경우
        {
            printf("적은 번개 속성에 면역입니다.\n");
            d1s();
            printf("피해를 받지 않습니다.\n");
        }
        if (goto_stage != 5)
        {
            com_demage(skill_2()); // 썬더볼트 피해량 컴퓨터에게 적용
            d1s();
            com_defdown(player_skill2_level * 2); // 컴퓨터 방어력 감소 효과 적용
        }

        d1s();
        player_mpdown(25);  // 마나 소모 적용
        turn++;             // 턴 넘김
    }

    // 숫자 3번 큐어
    if (a == 0x33 && player_mp < 30) { 
        nomp();
        d1s();
    }
    // 숫자 3번 큐어
    if (a == 0x33 && player_mp >= 30) {
        printf("<3. 큐어>를 사용 했습니다.\n");
        d1s();
        skill3_eft();   // 큐어 이펙트 출력
        d1s();
        player_hpup(skill_3()); // 체력 회복 적용
        d1s();
        player_mpdown(30);      // 마나 소모
        turn++;
    }

    // 숫자 4번 가드업
    if (a == 0x34 && player_mp < 20) { 
        nomp();
        d1s();
    }
    // 숫자 4번 가드업
    if (a == 0x34 && player_mp >= 20) { 
        printf("<4. 가드 업>을 사용 했습니다.\n");
        d1s();
        skill4_eft(); // 가드 업 이펙트
        d1s();
        printf("방어력이 %d 만큼 증가 합니다\n", skill_4());
        player_defup = player_defup + skill_4(); // 플레이어 방어력 상승치 증가
        d1s();
        player_mpdown(20);
        turn++;
    }

    // 숫자 5번 메디테이션
    if (a == 0x35) { 
        printf("<5. 메디테이션>을 사용 했습니다.\n");
        d1s();
        skill5_eft(); // 메디테이션 이펙트
        d1s();
        player_hpdown(player_hp * 40 / 100); // 현재 체력의 40% 소모
        d1s();
        player_mppup(skill_5());    // 마나 회복 적용
        d1s();
        turn++;
    }

}

void level_up(int a) // 전투 종료 후 레벨업했는지 체크
{
    if (a >= player_maxexp) // 현재 경험치가 최대 경험치를 도달할경우
    {
        gotoxy(20, 16);
        printf("    축하합니다! 레벨업을 하였습니다!\n");
        gotoxy(20, 17);
        printf("스탯 포인트 3, 스킬 포인트 1을 얻었습니다.\n"); // 전투 결과 창에서 문구 출력

        player_statpoint = player_statpoint + 3;    // 스탯 포인트 증가
        player_skillpoint = player_skillpoint + 1;  // 스킬 포인트 증가
        player_exp = player_exp - player_maxexp;    // 경험치 초과분 계산
        player_maxexp = player_maxexp + 100;        // 레벨업 했으니 다음 도달해야할 최대 경험치 변경
        player_level++;      // 플레이어 캐릭터 레벨 증가
    }
}

void all_set()      // 전체 화면 리셋 + 스탯 변동 적용
{
    stat_over();    // 스탯 초과, 음수 처리
    system("cls");  // 화면 모두 지움
    stage_name(goto_stage); // 스테이지 이름, 현재 스테이지로 설정 
    fight_stat();   // 전투 스탯 정보 창 출력
    fight_skill();  // 전투 스킬 정보 창 출력
    char_eft();     // 두 캐릭터 정위치 출력
    txt_pos();      // 상황 설명 메세지 좌표로 이동
}
void txt_set()      // 전체 화면 리셋 
{
    system("cls");
    stage_name(goto_stage);
    fight_stat();
    fight_skill();
    char_eft();
    txt_pos();
}

void player_stunon() // 플레이어에게 기절 상태 적용
{
    printf("아무것도 할 수 없습니다.\n");
    player_stun = 1; // 기절 상태 값 설정
    turn++;          // 턴 넘김
}
void player_doteon(int a) // 지속 피해 도트 데미지 적용
{
    printf("지속적으로 피해를 입습니다.\n");
    d1s();
    dote_eft(); // 도트 피해 이펙트
    d1s();
    player_demage(a); // 데미지 적용
    d1s();
    all_set();      // 화면 리셋 + 스탯 변동 적용
}

void stage01_skill() // 스테이지 1 컴퓨터 스킬
{
    int r1;
    randomize();
    r1 = random(40) + 11; // 총기 난사 스킬 데미지를 랜덤하게 적용

    if (com_skill == 0) { // com_skill 은 랜덤 25%
        printf("적이 <조준 사격>을 사용 했습니다.\n");
        d1s();
        gunshot_eft(); // 총알 날라가는 이펙트 적용
        gunshot_eft(); 
        gunshot_eft();
        d1s();
        player_demage(30); // 플레이어에게 피해량 적용 및 문구 출력
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
        player_demage(r1); // 랜덤 데미지 적용
        d1s();
    }
    if (com_skill == 2) {
        printf("적이 <수류탄 투척>을 사용 했습니다.\n");
        d1s();
        boom_eft();         // 수류탄 투척 이펙트
        d1s();
        player_demage(35);  // 피해량 적용 및 문구 출력
        d1s();
        player_defdown(5);  // 방어력 감소 효과 적용 및 문구 출력
        d1s();
    }
    if (com_skill == 3) {
        printf("적이 <응급 치료>를 사용 했습니다.\n");
        d1s();
        comhp_eft();        // 컴퓨터 체력 회복 이펙트
        d1s();
        com_hpup(30);       // 컴퓨터 체력 회복 적용 및 문구 출력
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
void stage06_skill() // 스테이지 6 컴퓨터 스킬
{
    if (com_skill == 0) { // com_skill 은 랜덤 25%
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
        firepunch_eft(); // 화염 주먹 이펙트 재생
        d1s();
        player_demage(com_att + 15); // 플레이어 피해량 적용, 출력
        d1s();
        player_defdown(5); // 플레이어 방어력 감소 효과 적용, 출력
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
void stage10_skill() // 마지막 스테이지 컴퓨터 스킬
{
    int r;
    randomize();

    if (com_skill == 0) { // 컴퓨터 삼조격 스킬에 15% 확률로 치명타 적용
        r = random(100);
        if (r < 15)
        {
            printf(" 적이 <삼조격>을 사용 했습니다.\n");
            d1s();
            triplespear_eft();
            d1s();
            printf("치명타가 터졌습니다.\n");
            d1s();
            player_demage(com_att * 6); // 기본 대비 두배의 피해량 적용
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



/////////////////////////////////////////////// 메인 /////////////////////////////////////////////////

void main(void) 
{
    setcursortype(NOCURSOR);
    
    intro_screen();

    _getch();
    item_att = &player_att;
    item_mp = &player_maxmp;

    for (;;) // 반복
    {
        randomize();

        menu_fight = 0; // 전투 메뉴 플래그 변수
        menu_stat = 0;  // 스탯 메뉴
        menu_skill = 0; // 스킬 메뉴
        menu_item = 0;  // 상점 메뉴

        system("cls");

        menu_choose(); // 메인 메뉴 출력
        choose = _getch(); // 메뉴 선택

        // 1. 전투 선택
        if (choose == 0x31) {   

            total = win + lose; // 총 전투 횟수 설정
            menu_fight = 1;     // 전투 메뉴 진입 플래그 변수 설정

            stat_restore();     // 스탯 설정
            stat_over();        // 스탯 정리
            system("cls");
            printf("┌────────────────────────────────────────────────────┐      \n");
            printf("│   <<<스테이지 번호를 입력하고 엔터를 누르세요>>>   │   \n");
            printf("│            1-10 스테이지 까지 있으며,              │    \n");
            printf("│ %d 스테이지 클리어시 그 다음 스테이지 플레이 가능.      \n", stage_level);
            printf("│      (메인 메뉴로 돌아가려면 숫자 0을 입력)        │      \n");
            printf("└────────────────────────────────────────────────────┘   \n");

            if (win >= 1 || lose >= 1) // 한번이라도 전투를 치룬 경우 승률 및 점수 표시
            {
                printf("      %d승 %d패   승률 : %.2f %%  점수 : %d\n", win, lose, (float)win * 100 / (float)total, rating);
            }
            if (total < 3)  // 전투 횟수가 적어 등급이 배정 되지 않은 경우
            {
                printf("              현재 등급 : Unranked\n");
                printf("       최소 3판을 할경우 등급을 배정 받습니다.\n");
            }
            if (total >= 3) // 충분히 전투를 치뤄 등급이 배정 된경우
            {
                if (rating < 1000) { // 점수에 따라 랭크 등급 배정
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

            scanf_s("%d", &goto_stage);     // 스테이지 입력 받기

            if (stage_level < goto_stage)   // 플레이 가능한 스테이지 이상으로 시도 하는 경우
            {
                printf("해당 스테이지는 아직 플레이 할 수 없습니다.\n");
                printf("     계속 하려면 아무 키나 누르세요.\n");
                _getch();
                continue;
            }

            if (goto_stage == 1) {      // 스테이지별 컴퓨터 능력치 설정
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

            turn = 0;       // 턴 초기화
            stat_restore(); // 스탯 복구 설정

            for (;;)   // 전투 반복
            {
                all_set();  // 전투 화면 갱신 및 스탯 정리

                if (player_dotecount > 0) // 지속 피해 상태 횟수가 남아있는 경우
                {
                    player_doteon(com_att); // 지속 피해 적용 (all_set포함)
                }

                        
                if (turn % 2 == 0 && player_hp > 0 && player_stun == 0) { // 플레이어 턴이면서, 플레이어 체력이 남아 있고, 기절 상태가아닌 경우

                    for (;;) {                                            // 즉, 전투가 가능한 상태인경우, 플레이어 턴 실행

                        printf("      당신의 턴입니다!\n");
                        order = _getch();
                        player_skill(order);    // 입력 받은 스킬 사용 및 turn++

                        if (turn % 2 == 1) {    // turn이 변동 되면 탈출
                            break;
                        }
                    }
                }

                if (turn % 2 == 1 && com_hp > 0) {  // 컴퓨터 턴이되었고, 컴퓨터의 체력이 남아 있는경우

                    all_set();          // 화면 세팅

                    player_stun = 0;    // 플레이어 턴이 끝났으므로, 플레이어 기절 상태를 해제

                    printf("       적의 턴입니다.\n");
                    d1s();

                    com_skill = random(4);  // 컴퓨터 4가지 스킬 랜덤 적용

                    // 현재 스테이지 레벨에 따라 다른 컴퓨터 스킬 적용
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

                    turn++; // 컴퓨터 스킬 사용이 끝났으니 턴 넘김
                }


                if (player_hp <= 0) // 플레이어 체력 체크
                {
                    all_set();
                    printf("체력이 0이 되어 쓰러졌습니다.\n");
                    delay(2000);
                    system("cls");
                    window();
                    gotoxy(20, 9);
                    printf("    << 패배 하였습니다 >>\n");

                    lose++;   // 패배 수치 증가
                    rating = rating - (stage_level - goto_stage) - 21;  // 스테이지 레벨에 따라 다르게 점수 하락

                    if (player_maxhp >= 150 && player_maxmp >= 150) // 능력치 하락
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

                // 컴퓨터 체력 체크
                if (com_hp <= 0 && stage_level == goto_stage) // 현재 최고 스테이지에 도전한 경우, 다음 단계 개방
                {
                    all_set();
                    printf("적이 쓰러졌습니다.\n");
                    gotoxy(50, 16);
                    puts("   ");
                    gotoxy(50, 16);
                    puts("OTL");    // 컴퓨터 캐릭터 쓰러진 모습 효과
                    delay(2000);
                    system("cls");
                    printf("\n");
                    gotoxy(20, 9);
                    printf("         << 승리 하였습니다! >>\n");

                    win++;                  // 승리 횟수 증가
                    rating = rating + 21;   // 점수 증가
                    
                    player_exp = player_exp + (goto_stage * 100);   // 경험치 증가
                    gotoxy(20, 10);
                    printf("      경험치를 %d 만큼 얻었습니다.\n", goto_stage * 100);
                    
                    player_gold = player_gold + (goto_stage * 500); // 골드 증가
                    gotoxy(20, 11);
                    printf("       골드를 %d 만큼 얻었습니다.\n", goto_stage * 500);

                    level_up(player_exp);   // 플레이어 레벨업 체크

                    gotoxy(20, 12);
                    printf("   다음 스테이지에 도전 할 수 있습니다.\n");
                    gotoxy(20, 13);
                    printf("     계속 하려면 아무 키나 누르세요.\n");
                    window();   // 테두리 출력

                    stage_level = stage_level + 1; // 현재 도전 가능한 최고 스테이지 단계 증가
                    _getch();
                    break;
                }

                if (com_hp <= 0 && stage_level > goto_stage) // 이전 스테이지에서 전투한경우
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
                    rating = rating + goto_stage;   // 하위 단계 전투 이므로 적은 점수 획득

                    player_exp = player_exp + (goto_stage * 80);    // 최고 단계 도전이 아닌, 하위 단계 전투이므로 적은 보상 획득
                    gotoxy(20, 10);
                    printf(" 경험치를 %d 만큼 얻었습니다.\n", goto_stage * 80);

                    player_gold = player_gold + (goto_stage * 300);
                    gotoxy(20, 11);
                    printf("  골드를 %d 만큼 얻었습니다.\n", goto_stage * 300);
                    
                    level_up(player_exp);   // 레벨 업 체크
                    
                    gotoxy(20, 12);
                    printf("계속 하려면 아무 키나 누르세요.\n");

                    _getch();
                    break;
                }

                if (player_dotecount > 0) { // 플레이어 지속 피해 상태인경우 횟수 차감
                    player_dotecount = player_dotecount - 1;
                }
            }
        }

        // 2. 스탯 선택 (스탯 포인트를 보유한 경우)
        if (choose == 0x32 && player_statpoint > 0) {  

            menu_stat = 1;  // 스탯 메뉴 진입 플래그 변수 설정

            system("cls");          // 화면 지우기
            stat_restore();         // 스탯 복원
            playerstat_message();   // 스탯 정보 화면 출력
            statchoose_message();   // 스탯 선택 화면 출력 (스탯 포인트 있을 경우에만)
            printf("남은 스탯 포인트 : %d\n", player_statpoint);

            stat_up = _getch(); // 원하는 스탯 선택

            if (stat_up == 0x31 || stat_up == 0x32 || stat_up == 0x33 || stat_up == 0x34) { // 1~4 중 스탯을 고른경우
                player_statpoint = player_statpoint - 1;    // 스탯 포인트 차감
                choose = NULL;
            }

            if (stat_up == 0x31) {  // 1번 체력 증가 선택 및 적용
                statchoose(1);
            }
            if (stat_up == 0x32) {  // 2번 마나 증가 선택 및 적용
                statchoose(2);
            }
            if (stat_up == 0x33) {  // 3번 공격력 증가 선택 및 적용
                statchoose(3);
            }
            if (stat_up == 0x34) {  // 4번 방어력 증가 선택 및 적용
                statchoose(4);      // 방어력이 100을 넘었다면, 스탯 포인트를 환불 받으며, defover_state 플래그 변수 1로 설정
            }
            if (stat_up == 0x35) {  // 5번 뒤로가기 선택
                continue;
            }

            // 스탯을 선택했고, 증가 시켰으니, 화면 갱신
            if (stat_up == 0x31 || stat_up == 0x32 || stat_up == 0x33 || stat_up == 0x34 || stat_up == 0x35) {

                system("cls");
                stat_restore();
                playerstat_message();

                if (player_defmain >= 100) // 방어력이 최대치에 도달한경우 알려줌
                {
                    printf(" 방어력은 100을 넘을 수 없습니다.\n");
                }

                printf(" 계속하려면 아무키나 누르세요\n");
                defover_state = 0;
                _getch();

                continue;
            }
        }

        // 2. 스탯 선택 (스탯 포인트가 없는 경우)
        if (choose == 0x32 && player_statpoint == 0) { 
            system("cls");
            stat_restore();
            playerstat_message();
            printf("스탯 포인트가 없습니다.\n");
            _getch();
        }

        // 3. 스킬 선택 (스킬 포인트가 있는 경우)
        if (choose == 0x33 && player_skillpoint > 0) { 

            menu_skill = 1;         // 플래그 변수 설정
            system("cls");          // 화면 지움
            skillchoose_message();  // 스킬 메뉴 화면 출력
            printf("남은 스킬 포인트 : %d\n", player_skillpoint);

            skill_up = _getch();

            // 1~5번 중 강화할 스킬을 선택 한 경우
            if (skill_up == 0x31 || skill_up == 0x32 || skill_up == 0x33 || skill_up == 0x34 || skill_up == 0x35) {
                player_skillpoint = player_skillpoint - 1; // 포인트 1 차감
                choose = NULL;
            }

            if (skill_up == 0x31 && player_skill1_level >= 5) // 스킬 1 파이어볼을 선택했는데 최대 레벨을 도달한 경우
            {
                player_skillpoint = player_skillpoint + 1;  // 스킬 포인트 환급
                printf("해당 스킬은 이미 최대 레벨 입니다.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x32 && player_skill2_level >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("해당 스킬은 이미 최대 레벨 입니다.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x33 && player_skill3_level >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("해당 스킬은 이미 최대 레벨 입니다.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x34 && player_skill4_level >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("해당 스킬은 이미 최대 레벨 입니다.\n");
                _getch();
                continue;
            }
            if (skill_up == 0x35 && player_skill5_level >= 5)
            {
                player_skillpoint = player_skillpoint + 1;
                printf("해당 스킬은 이미 최대 레벨 입니다.\n");
                _getch();
                continue;
            }

            // 스킬 레벨이 최대치가 아닌경우, 선택한 스킬 레벨 증가
            if (skill_up == 0x31 && player_skill1_level < 5) { 
                player_skill1_level = player_skill1_level + 1; // 스킬 1번 업
            }
            if (skill_up == 0x32 && player_skill2_level < 5) {
                player_skill2_level = player_skill2_level + 1; // 스킬 2번 업
            }
            if (skill_up == 0x33 && player_skill3_level < 5) {
                player_skill3_level = player_skill3_level + 1; // 스킬 3번 업
            }
            if (skill_up == 0x34 && player_skill4_level < 5) {
                player_skill4_level = player_skill4_level + 1; // 스킬 4번 업
            }
            if (skill_up == 0x35 && player_skill5_level < 5) {
                player_skill5_level = player_skill5_level + 1; // 스킬 5번 업
            }

            // 스킬을 강화한 경우, 변동된 사항 갱신
            if (skill_up == 0x31 || skill_up == 0x32 || skill_up == 0x33 || skill_up == 0x34 || skill_up == 0x35) {
                system("cls");         // 화면 지움
                skillchoose_message(); // 스킬 화면 출력
                printf("스킬 레벨이 올랐습니다. 계속 하려면 아무 키나 누르세요.\n");
                _getch();
            }

        }

        // 3. 스킬 선택 (스킬 포인트가 없는 경우) 
        if (choose == 0x33 && player_skillpoint == 0) { 
            system("cls");
            skillchoose_message();
            printf("스킬 포인트가 없습니다.\n");
            _getch();
        }

        // 4. 무기 선택
        if (choose == 0x34) { 

            menu_item = 1;

            for (;;)
            {
                system("cls");
                printf("┌──────────────────────────────────────────────────────┐ \n");
                printf("│                 <<< 무기 정보 >>>                    │   \n");

                if (item_code == 0) { // 장착 중인 무기값에 따라 출력
                    printf("│             현재 장착중인 무기 : 없음                │  \n");
                }
                if (item_code == 1) {
                    printf("│           현재 장착중인 무기 : 증폭의 고서           │  \n");
                }
                if (item_code == 2){
                    printf("│          현재 장착중인 무기 : 방출의 마법봉          │   \n");
                }
                if (item_code == 3) {
                    printf("│          현재 장착중인 무기 : 현자의 지팡이          │    \n");
                }

                printf("└──────────────────────────────────────────────────────┘     \n");
                textcolor(YELLOW);
                printf("                현재 보유한 골드 : %d                       \n", player_gold);

                textcolor(WHITE);
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

                if (item_choose == 0x31) // 무기 1. 증폭의 고서를 선택 한 경우
                {
                    if (player_gold >= 10000 && item_code == 0) // 돈이 충분하고, 아이템을 장착 하지 않은 상태일 경우에만
                    {
                        printf("증폭의 고서를 장착 했습니다.\n");
                        item_code = 1;  // 장착한 아이템 값 설정
                        *item_att = player_att + 20;    // 공격력 증가
                        *item_mp = player_maxmp + 400;  // 마나 증가
                        player_gold = player_gold - 10000;  // 골드 차감
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

                if (item_choose == 0x32) // 무기 2. 선택
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

                if (item_choose == 0x33) // 무기 3. 선택
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

                if (item_choose == 0x34) // 4. 무기 장착 해제 선택
                {
                    if (item_code == 1) // 무기 1번을 장착한 경우 그만큼의 값을 다시 뺌
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

                if (item_choose == 0x30) // 0. 뒤로가기 누른 경우
                {
                    break;
                }
            }
        }

        // 5. 치트 선택
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
                if (cheat == 1234) // 치트를 맞춘 경우
                {
                    printf("체력이 100 증가합니다!\n");
                    player_maxhp = player_maxhp + 100; // 능력치 상승
                    c_value++;  // 치트 사용 횟수 증가
                    _getch();
                }
                else if (cheat == 2345)
                {
                    printf("마나가 100 증가합니다!\n");
                    player_maxmp = player_maxmp + 100;
                    c_value++;
                    _getch();
                }
                else if (cheat == 4567)
                {
                    printf("공격력이 20 증가합니다!\n");
                    player_att = player_att + 20;
                    c_value++;
                    _getch();
                }
                else if (cheat == 5678)
                {
                    printf("방어력이 10 증가합니다!\n");
                    player_defmain = player_defmain + 10;
                    c_value++;
                    _getch();
                }
                else if (cheat == 6789)
                {
                    printf("골드가 2000 증가 합니다!\n");
                    player_gold = player_gold + 2000;
                    c_value++;
                    _getch();
                }
                else if (cheat == 7777)
                {
                    printf("스탯 포인트가 1 증가합니다!\n");
                    player_statpoint = player_statpoint + 1;
                    c_value++;
                    _getch();
                }
                else if (cheat == 9999)
                {
                    printf("스킬 포인트가 1 증가합니다!\n");
                    player_skillpoint++;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1111)
                {
                    printf("스테이지 레벨이 10으로 설정 되었습니다!\n");
                    stage_level = 10;
                    c_value++;
                    _getch();
                }
                else if (cheat == 1134)
                {
                    printf("Admin mode enabled.\n");
                    player_gold = player_gold + 999999;
                    stage_level = 11;   // 모든 스테이지 개방
                    player_statpoint = player_statpoint + 9999;
                    player_skillpoint = player_skillpoint + 9999;
                    _getch();
                }
                else if (cheat == 0) // 뒤로 가기 입력
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

        // 6. 설정 선택
        if (choose == 0x36) 
        {
            int temp_speed; 
            temp_speed = speed; // 값 설정 실패시 초기 값으로 되돌리기 위해 값을 저장

            system("cls");
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

            if (speed == 0) // 0으로 설정하거나, 설정 하지 않은 경우
            {
                speed = temp_speed; // 원래 속도 값 적용
            }
            else if (speed < 100) // 속도가 너무 빠른경우
            {
                speed = temp_speed;
                printf("최소 100 부터 가능 합니다.\n");
                _getch();
                continue;
            }
            else if (speed > 2000) // 너무 느린 경우
            {
                speed = temp_speed;
                printf("최대 2000 까지 가능 합니다.\n");
                _getch();
                continue;
            }
            else if (speed >= 100 && speed <= 2000) // 적정 값일 경우
            {
                printf("적용이 완료 되었습니다.\n");
                _getch();
            }
            else
            {
                continue;
            }
        }

        // 7. 도움말 선택
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

        // 8. 정보 선택
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

        // 0. 클리어 코드 확인 선택 (스테이지 모두 클리어시)
        if (choose == 0x30 && stage_level >= 11)
        {
            system("cls");
            printf(" CODE   : %d_%d_%d\n", win, lose, rating);
            printf("C_Value : %d\n", c_value);
            _getch();
        }

    } // for(;;)
} // int main(void)