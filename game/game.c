#include "turboc.h"
#include <time.h>
#define BX 5 //�������� ��ġ
#define BY 1
#define BW 6 //�������� ũ��
#define BH 20
#define GREY     "\x1b[90m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define BBLUE    "\x1b[96m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define WHITE  "\x1b[37m"
#define BRIGHTWHITE   "\x1b[97m"
#define BRIGHTGREEN   "\x1b[92m"
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

 

enum { EMPTY, BRICK, WALL};
char* arTile[] = { ". ", "��", "��"};
int board[BW + 2][BH + 2];
int color[BW+2][BH+2];
int nx, ny;
int ncolor;
int addtime;
int brick, rot;   // brick�� ������ȣ, rot�� �� ������ ȸ����ȣ
int victory;
int gage;
double time_spent = 0.0;
void DrawScreen();
void PrintBrick(BOOL Show);
int GetAround(int x, int y, int b, int r);
BOOL ProcessKey();
BOOL MoveDown();
void TestFull();
void DrawBoard();
void uponeline();
bool c =true;
int gagetime;
clock_t cbeign;
clock_t timegage;
clock_t begin;
struct Point {
    int x, y;
};

 

struct Point Shape[][4][4] = {
{ {0,0,1,0,2,0,-1,0}, {0,0,0,1,0,-1,0,-2},
{0,0,1,0,2,0,-1,0}, {0,0,0,1,0,-1,0,-2} }, //0�� ����
{ {0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1},
{0,0,1,0,0,1,1,1}, {0,0,1,0,0,1,1,1} }, //1�� ����
{ {0,0,-1,0,0,-1,1,-1}, {0,0,0,1,-1,0,-1,-1},
{0,0,-1,0,0,-1,1,-1}, {0,0,0,1,-1,0,-1,-1} }, //2�� ����
{ {0,0,-1,-1,0,-1,1,0}, {0,0,-1,0,-1,1,0,-1},
{0,0,-1,-1,0,-1,1,0}, {0,0,-1,0,-1,1,0,-1} }, //3�� ����
{ {0,0,-1,0,1,0,-1,-1}, {0,0,0,-1,0,1,-1,1},
{0,0,-1,0,1,0,1,1}, {0,0,0,-1,0,1,1,-1} }, //4�� ����
{ {0,0,1,0,-1,0,1,-1}, {0,0,0,1,0,-1,-1,-1},
{0,0,1,0,-1,0,-1,1}, {0,0,0,-1,0,1,1,1} }, //5�� ����
{ {0,0,-1,0,1,0,0,1}, {0,0,0,-1,0,1,1,0},
{0,0,-1,0,1,0,0,-1}, {0,0,-1,0,0,-1,0,1} }, //6�� ����
};

 

void main()
{
    int x, y;
    bool startonce = true;
    setCursorType(NOCURSOR); // Ŀ���� �Ⱥ��̰� �ϴ� �Լ�
    clearScreen();   // ȭ���� ������ ����� �Լ�
    for (y = 0; y < BH + 2; y++)
    {
        int t = rand()% (BW) + 1;
        for (x = 0; x < BW + 2; x++)
        {
            board[x][y] = (y == 0 || y == BH + 1 || x == 0 ||
                x == BW + 1) ? WALL : EMPTY;
            if ( y <BH+1 &&y>BH-3 && x>0 && x <BW + 1&&  x != t)
            {
                board[x][y] = BRICK;
                color[x][y] = 1;
                ncolor ++;
            }
        }
    }
    DrawScreen();    // ����ȭ�� �׸��� �Լ� ȣ��
    //getch();
    _getch();
    // ( ) ȭ���� �Ͻ������ϱ� ���� ���
    clearScreen();    // ȭ���� ������ ����� �Լ�

 

    int nFrame, nStay; //������ �������� �ӵ�
    srand((unsigned)time(NULL)); //�����߻��� �ʱ�ȭ
    nFrame = 20; //������ �������� �ӵ�����

 

    for (; 1;) {
        if (startonce)
        {
            begin = clock();
            timegage = clock();
            startonce = false;
        }
        clock_t end = clock();
        time_spent  = (double)(end-begin) / CLOCKS_PER_SEC + addtime;
        if ((double)(end-cbeign) / CLOCKS_PER_SEC >15)
            {
                c = true;
            }
        if (ncolor <6)
        {
            gagetime = 1;
        }
        else
        {
            gagetime = 2;
        }
        if ((double)(end-timegage) / CLOCKS_PER_SEC >gagetime)
            {
             gage++;
             timegage = clock();
              if (gage>BW)
                 {
                    gage = 0;
                     uponeline();
                 }
            }
        clearScreen();
        DrawScreen();
        // ���� �����ϱ�
        brick = rand() % (sizeof(Shape) / sizeof(Shape[0]));
        switch(brick)
            {
            case 0:
                gotoXY(30,20); printf("��: ������ Ǯ �� �پ��� �Ĺ��� �ɾ �³�ȭ�� �����ϴ� �����̴�.");
                break;
            case 1:
                gotoXY(30,20); printf("��: ���� �ִ� �������� �̻�ȭź�Ҹ� ������� �Ѵ�.");
                break;
             case 2:
                gotoXY(30,20); printf("�����: ������ �ؾ���°��� �ı��� �׾�� �ִ�.");
                break;
             case 3:
                gotoXY(30,20); printf("�����: ������ �ؾ���°��� �ı��� �׾�� �ִ�.");
                break;
             case 4:
                gotoXY(30,20); printf("�ٴ�ǥ��: �ϱذ� ������ ��� �� �ڸ��� �Ұ� �ִ�.");
                break;
             case 5:
                gotoXY(30,20); printf("�ٴ�ǥ��: �ϱذ� ������ ��� �� �ڸ��� �Ұ� �ִ�.");
                break;
             case 6:
                gotoXY(30,20); printf("����: �̻�ȭź�Ҹ� �������ִ� ������ ����ü�̴�. ����ȭ�� �װ� �ִ�.");
                break;
            }
        nx = BW / 2; //������ �ʱ� x ��ǥ
        ny = 2; //������ �ʱ� y ��ǥ
        rot = 0;  //������ ȸ����� ��ȣ
        PrintBrick(TRUE); // ���� �׸��� �Լ� ȣ��

 

        //�����ֺ��� ������� üũ
        if (GetAround(nx, ny, brick, rot) != EMPTY) break;
        nStay = nFrame;
        for (; 2;)
        {
            clock_t end = clock();
            time_spent  = (double)(end-begin) / CLOCKS_PER_SEC + addtime;
             if ((double)(end-cbeign) / CLOCKS_PER_SEC >15)
            {
                c = true;
            }
        if (ncolor <6)
        {
            gagetime = 1;
        }
        else
        {
            gagetime = 2;
        }
            if ((double)(end-timegage) / CLOCKS_PER_SEC >gagetime)
            {
             gage++;
             timegage = clock();
              if (gage>BW)
                 {
                    gage = 0;
                     uponeline();
                 }
            }
            if (--nStay == 0) {
                nStay = nFrame;

 

                // (false) ������ �� ������ �� ������
                // ���� ��������
                if (MoveDown()) break;
            }
            if (ProcessKey()) break;
            delay(1000 / 20);
        }
        if (ncolor == 0)
        {
            clock_t end = clock();
            time_spent  = (double)(end-begin) / CLOCKS_PER_SEC + addtime;
            victory = 1;
            break;
        }
    }
    clearScreen();
    if (victory)
    {
        gotoXY(30, 12); puts("VICTORY");
         gotoXY(30, 14); printf("Your Record Was %.2f Seconds",time_spent);
    }
    else
    {
        gotoXY(30, 12); puts("G A M E O V E R");
    }
    setCursorType(NORMALCURSOR);
}

 

void DrawScreen()
{
    int x, y;
    gotoXY(5,0); printf("EcoGauge");
    for(int i=15; i<BW+16; i++)
    {
                            gotoXY(i,0); printf(arTile[1]);
    }
    for(int i=15; i<gage+15; i++)
    {
        gotoXY(i,0); printf(RED "%s" RESET, arTile[1]);
    }
    static BOOL t = true;
    for (x = 0; x < BW + 2; x++)
    {
        for (y = 0; y < BH + 2; y++)
        {
            gotoXY(BX + x * 2, BY + y);
            if (color[x][y])
            {
                printf(BLUE "%s" RESET, arTile[board[x][y]]);
            }
            else
            puts(arTile[board[x][y]]);
        }
    }
    if (c)
    {
        gotoXY(50, 10); puts( "Press C to do something" );
    }
    else
    {
        gotoXY(50, 10); puts( "C cooltime");
    }
    gotoXY(50, 3); puts(RED "Tetris: Planet Rescue" RESET);
    if (t)
    {
        t = false;
        gotoXY(50, 8); puts("Press any key to Start");
    }
    else
    {
        gotoXY(50,0); printf("%.2f (s)",time_spent);
    }
    gotoXY(50, 5); puts("�¿�:�̵�, ��:ȸ�� ,�Ʒ�:����");
    gotoXY(50, 6); puts("����:���� ����");
}

 

void PrintBrick(BOOL Show)
{
    int i;
    gotoXY(50,0); printf("%.2f (s)",time_spent);
    if (c)
    {
        gotoXY(50, 10); puts( "Press C to do something" );
    }
    else
    {
        gotoXY(50, 10); puts( "C cooltime");
    }
    gotoXY(5,0); printf("EcoGauge");
    for(int i=15; i<BW+16; i++)
    {
                            gotoXY(i,0); printf(arTile[1]);
    }
    for(int i=15; i<gage+15; i++)
    {
        gotoXY(i,0); printf(RED "%s" RESET, arTile[1]);
    }
    for (i = 0; i < 4; i++) {
        gotoXY(BX + (Shape[brick][rot][i].x + nx) * 2, BY + Shape[brick][rot][i].y + ny);
        if (!Show)
        {
            printf("%s", arTile[EMPTY] );
        }
        else
        {
            switch (brick)
            {
            case 0:
                printf(GREY "%s" RESET, arTile[BRICK] );
                break;
            case 1:
                printf(GREEN "%s" RESET, arTile[BRICK] );
                break;
            case 2:
                printf(BBLUE "%s" RESET, arTile[BRICK] );
                break;
            case 3:
                printf(BBLUE "%s" RESET, arTile[BRICK] );
                break;
            case 4:
                printf(WHITE "%s" RESET, arTile[BRICK] );
                break;
            case 5:
                printf(WHITE "%s" RESET, arTile[BRICK] );
                break;
            case 6:
                printf(BRIGHTGREEN "%s" RESET, arTile[BRICK] );
                break;
            }

 

        }
    }
}

 

int GetAround(int x, int y, int b, int r)
{
    int i, k = EMPTY;

 

    for (i = 0; i < 4; i++) {
        k = max(k, board[x + Shape[b][r][i].x]
            [y + Shape[b][r][i].y]);

 

    }
    return k;
}

 

BOOL ProcessKey()
{
    int ch, trot;
    if (_kbhit()) {
        // �Է¹��ۿ��� 1����Ʈ (�ƽ�Ű�ڵ�)�� �����´�.
        //ch = getch();
        ch = _getch();
        //ch ���� 224 �Ǵ� 0�̸� ���� �� ����
        if (ch == 0xE0 || ch == 0) {
            // 1 ( ) . �ٽ� ����Ʈ ��ĵ�ڵ� �� �����´�
            //ch = getch();
            ch = _getch();
            int x,y;
            switch (ch) {
            case LEFT: //���� Ű ������ ��
                if (GetAround(nx - 1, ny, brick, rot) == EMPTY) {
                    PrintBrick(FALSE); //���� �����
                    nx--;
                    PrintBrick(TRUE); //���� �׸���
                }
                break;
            case RIGHT: //������ Ű ������ ��
                if (GetAround(nx + 1, ny, brick, rot) == EMPTY) {
                    PrintBrick(FALSE);
                    nx++;
                    PrintBrick(TRUE);
                }
                break;
            case UP: //���� ȸ��
                trot = (rot == 3 ? 0 : rot + 1);
                if (GetAround(nx, ny, brick, trot) == EMPTY) {
                    PrintBrick(FALSE);
                    rot = trot;
                    PrintBrick(TRUE);
                }
                break;
            case DOWN: //���� �� ���� ������
                if (MoveDown()) {
                    return TRUE;
                }
                break;

 

            }
        }
        else {
                int x, y;
            switch (ch) {
            case ' ': //�����̽��� Ű �Է½�
                while (MoveDown() == FALSE) { ; }
                return TRUE;
            case 'c':
                if (c)
                {
                    addtime += 10;
                    c = false;
                    cbeign = clock();
                        y = BH;
                        for (x = 1; x < BW + 1; x++)
                        {
                            if (color[x][y] == 1)
                            {
                                ncolor--;
                            }
                            color[x][y] = 0;
                        }
                        for (int ty = y; ty > 1; ty--) {
                            for (x = 1; x < BW + 1; x++) {
                                board[x][ty] = board[x][ty - 1];
                                color[x][ty] = color[x][ty-1];
                            }
                        }
                        DrawBoard();
                        delay(200);
                        return TRUE;
                }

 

                }
            }

 

        }
    return FALSE;
}

 

BOOL MoveDown()
{
    if (GetAround(nx, ny + 1, brick, rot) != EMPTY) {
        TestFull();
        return TRUE;
    }
    PrintBrick(FALSE);
    ny++;
    PrintBrick(TRUE);
    return FALSE;
}

 

void TestFull()
{
    int i, x, y, ty;

 

    for (i = 0; i < 4; i++) {
        board[nx + Shape[brick][rot][i].x][ny + Shape[brick][rot][i].y] = BRICK;
    }
bool t = false;
    for (y = 1; y < BH + 1; y++) {
        for (x = 1; x < BW + 1; x++) {
            if (board[x][y] != BRICK) break;
        }
        if (x == BW + 1) {
            for (x = 1; x < BW + 1; x++)
            {
                if (color[x][y] == 1)
                {
                    ncolor--;
                    t = true;
                }
                color[x][y] = 0;
            }
            for (ty = y; ty > 1; ty--) {
                for (x = 1; x < BW + 1; x++) {
                    board[x][ty] = board[x][ty - 1];
                    color[x][y] = color[x][ty-1];
                }
            }
            DrawBoard();
            delay(200);
        }
    }
    if (t)
    {
        gage -= 3;
        timegage = clock();
        if (gage <0)
        {
            gage = 0;
        }
    }
}

 

void DrawBoard()
{
    int x, y;
    if (c)
    {
        gotoXY(50, 10); puts( "Press C to do something" );
    }
    else
    {
        gotoXY(50, 10); puts( "C cooltime");
    }
    gotoXY(50,0); printf("%.2f (s)",time_spent);
    for (x = 1; x < BW + 1; x++) {
        for (y = 1; y < BH + 1; y++) {
            gotoXY(BX + x * 2, BY + y);
            if (color[x][y])
            {
                printf(BLUE "%s" RESET, arTile[board[x][y]]);
            }
            else
            puts(arTile[board[x][y]]);
        }
    }
}

 

void uponeline()
{
    int t = rand()% (BW) + 1;
    for(int y= 1; y<BH; y++)
    {
        for(int x=1; x<BW+1; x++)
        {
            board[x][y] = board[x][y+1];
            color[x][y] = color[x][y+1];
        }
    }
    for(int x=1; x<BW+1; x++)
    {
        if (x != t)
        {
                ncolor ++;
            color[x][BH] = 1;
            board[x][BH] = 1;
        }
        else{
            board[x][BH] = 0;
            color[x][BH] = 0;
        }
    }
    DrawBoard();
}