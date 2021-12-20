﻿#include <iostream>
#include <windows.h>
#include <conio.h>
//#include<unistd.h> 
#include<ctime>
#include<cstdlib>
#include<cstdio>
using namespace std;
//dinh nghia
class snake
{
public:
    int x;
    int y;
    int xcu;
    int ycu;
    snake()
    {

        xcu = 1;
        ycu = 1;
        x = 1;
        y = 1;
    }
};
void dieukhien();
void dinhnghiadieukhien();
void inramanhinh();
void xoamanhinh();
void khoitaomoi();
void rungame();

int Soluongduoi = 0;

float timerunning = 1000;
bool Run = true;
char key;
int diem = 0;

const int CaoConsole = 10;
const int RongConsole = 20;

snake ran[CaoConsole * RongConsole];
snake moi;

enum dieukhien
{
    LEN = 1, XUONG, TRAI, PHAI
};

int check = PHAI;
int doublecheck = PHAI;
//ham gotoxy
void gotoxy(short x, short y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

//ve khung
void vekhung()
{
    for (int i = 0; i <= CaoConsole; i++)
    {
        gotoxy(RongConsole, i);
        //cout << "*" ; 
        printf("%c", 219, 219);
        gotoxy(0, i);
        //cout << "*" ;
        printf("%c", 219, 219);
    }
    for (int i = 0; i <= RongConsole; i++)
    {
        gotoxy(i, CaoConsole);
        //cout << "|";
        printf("%c", 219, 219);
        gotoxy(i, 0);
        // cout << "|";
        printf("%c", 219, 219);
    }
}

//dieu khien
void dieukhien()
{
    if (_kbhit() == true)//Kiểm tra có bấm không
    {
        key = _getch();
        if (key == 75 && doublecheck != PHAI)
        {
            check = TRAI;
            doublecheck = TRAI;
        }
        else if (key == 77 && doublecheck != TRAI)
        {
            check = PHAI;
            doublecheck = PHAI;
        }
        else if (key == 80 && doublecheck != LEN)
        {
            check = XUONG;
            doublecheck = XUONG;
        }
        else if (key == 72 && doublecheck != XUONG)
        {
            check = LEN;
            doublecheck = LEN;
        }
        else if (key == 'f')
        {
            Run = false;
            gotoxy((RongConsole - 8) / 2, CaoConsole / 2);
            cout << "ket thuc";
            _getch();
        }
        else if (key == 't')
        {
            timerunning -= 100; Soluongduoi++;
        }
        else if (key == 'g')
        {
            timerunning += 100;
        }
    }
}

void dinhnghiadieukhien()
{
    if (check == TRAI)
    {
        ran[0].x--;
    }
    else if (check == PHAI)
    {
        ran[0].x++;
    }
    else if (check == XUONG)
    {
        ran[0].y++;
    }
    else if (check == LEN)
    {
        ran[0].y--;
    }
}

//khoi tao ran
void khoitaoran()
{
    //update vi tri ran cu
    for (int i = 0; i < 10; i++)
    {
        ran[i].xcu = ran[i].x;
        ran[i].ycu = ran[i].y;
    }
    //update vi tri moi cho duoi
    for (int i = 10 - 1; i >= 1; i--)
    {
        ran[i].x = ran[i - 1].x;
        ran[i].y = ran[i - 1].y;
    }
}

//in man hinh
void vedauran()
{
    //ve dau ran
    gotoxy(ran[0].x, ran[0].y);
    cout << "0";
}
void veduoiran()
{
    for (int i = 1; i <= Soluongduoi; i++)
    {
        gotoxy(ran[i].x, ran[i].y);
        cout << "o";
    }
}
void inramanhinh()
{
    //xu ly cham bien
    if (ran[0].x == RongConsole)
    {
        ran[0].x = 1;
    }
    if (ran[0].y == CaoConsole)
    {
        ran[0].y = 1;
    }
    if (ran[0].y == 0)
    {
        ran[0].y = CaoConsole - 1;
    }
    if (ran[0].x == 0)
    {
        ran[0].x = RongConsole - 1;
    }

    if (ran[0].x == moi.x && ran[0].y == moi.y)
    {
        khoitaomoi();
        Soluongduoi++;
        timerunning -= 50;
        diem++;
    }
    veduoiran();
    vedauran();
}

void xoadauran()
{
    gotoxy(ran[0].xcu, ran[0].ycu);
    cout << " ";
}
void xoaduoiran()
{
    for (int i = 1; i <= Soluongduoi; i++)
    {
        gotoxy(ran[i].xcu, ran[i].ycu);
        cout << " ";
    }
}
void xoamanhinh()
{
    //thay the bang cach chen dau cach vo vi tri cu cua dau ran va duoi ran
    xoadauran();
    xoaduoiran();
}
//moi
void khoitaomoi()
{
    srand(time(NULL));
QUAYLAIDEKHOITAOLAIMOI:
    moi.x = 0;
    while ((moi.x == RongConsole) || (moi.y == CaoConsole) || (moi.x == 0) || (moi.y == 0))
    {
        moi.x = rand() % 100;
        if (moi.x > RongConsole)
        {
            moi.x = moi.x - RongConsole * (moi.x / RongConsole);
        }
        moi.y = rand() % 100;
        if (moi.y > CaoConsole)
        {
            moi.y = moi.y - CaoConsole * (moi.y / CaoConsole);
        }
    }
    for (int i = 0; i <= Soluongduoi; i++)
    {
        if (moi.x == ran[i].x && moi.y == ran[i].y)
        {
            goto QUAYLAIDEKHOITAOLAIMOI;
        }
    }
    gotoxy(moi.x, moi.y);
    cout << "s";
}
bool kiemtravacham()
{
    for (int i = 1; i <= Soluongduoi; i++)
    {
        if (ran[0].x == ran[i].x && ran[0].y == ran[i].y)
        {
            return true;
        }
    }
    return false;
}

//ham chay game
void rungame()
{
    system("cls");

    ran[0].x = Soluongduoi + 1;
    vekhung();
    khoitaomoi();
    while (Run)
    {

        khoitaoran();
        dieukhien();
        dinhnghiadieukhien();
        xoamanhinh();
        inramanhinh();

        if (kiemtravacham() && Soluongduoi > 1)
        {
            Run = false;

            gotoxy((RongConsole - 13) / 2, CaoConsole / 2);
            cout << "ban thua roi!";
            _getch();
        }

        gotoxy(RongConsole + 5, 0);
        cout << "Points: " << diem;

        Sleep(timerunning);
    }
    system("cls");
}

//ham main
int main()
{hastag to my code 
    rungame();
    return 0;
}
