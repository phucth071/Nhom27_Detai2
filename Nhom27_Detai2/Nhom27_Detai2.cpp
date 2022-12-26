#include "graphics.h"
#include "struct.h"
#include <dos.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>
int nx = 100, ny = 50;
int circle_X, circle_Y, serx, sery;
char temp[1000];

//Ve 1 don thuc
void DrawANode(MONO* k, int x1, int y1) {
    setcolor(7);
    line(x1 - 1, y1, x1 + nx, y1);
    line(x1, y1 + ny, x1 + nx, y1 + ny);
    line(x1, y1 - 1, x1, y1 + ny);
    line(x1 + nx, y1, x1 + nx, y1 + ny);
    serx = nx / 3, sery = ny / 2;
    line(x1, y1 + sery, x1 + nx, y1 + sery);
    line(x1 + serx, y1 + sery, x1 + serx, y1 + ny);
    line(x1 + 2 * serx, y1 + sery, x1 + 2 * serx, y1 + ny);
    //line(x1 + 3 * serx, y1 + sery, x1 + 3 * serx, y1 + ny);
    //line(x1 + 4 * serx, y1 + sery, x1 + 4 * serx, y1 + ny);
    line(x1 + nx, y1 + sery, x1 + nx + serx, y1 + sery);
    line(x1 + nx + serx, y1 + sery, x1 + nx + serx, y1 + ny);
    line(x1 + nx, y1 + ny, x1 + nx + serx, y1 + ny);
    sprintf_s(temp, " %d ", k->COEF);
    int len = strlen(temp);
    lineWithText(x1 + (nx / 2) - len * 5 + 9, y1, 0, 0, k->COEF);
    /*char* sign;
    if (k->S != 0) {
        char sign[] = " + ";
        lineWithText(x1 + (serx / 2) - 5, y1 + sery, 0, 0, sign);
    }
    else {
        char sign[] = " - ";
        lineWithText(x1 + (serx / 2) - 5, y1 + sery, 0, 0, sign);
    }*/
    sprintf_s(temp, " %d ", k->A);
    len = strlen(temp);
    lineWithText(x1 + (serx / 2) - 5, y1 + sery, 0, 0, k->A);
    sprintf_s(temp, " %d ", k->B);
    len = strlen(temp);
    lineWithText(x1 + serx + (serx / 2) - 5, y1 + sery, 0, 0, k->B);
    sprintf_s(temp, " %d ", k->C);
    len = strlen(temp);
    lineWithText(x1 + serx * 2 + (serx / 2) - 5, y1 + sery, 0, 0, k->C);
    setcolor(3);
    int centerCircle_X = x1 + nx + serx / 2, centerCircle_Y = y1 + ny - sery / 2;
    circle(centerCircle_X, centerCircle_Y, 8);
    if (k->S == 1) {
        setcolor(7);
        line(centerCircle_X, centerCircle_Y, centerCircle_X + 33, centerCircle_Y);
        line(centerCircle_X + 33, centerCircle_Y - sery / 2, centerCircle_X + 33, centerCircle_Y);
        line(centerCircle_X + 32, centerCircle_Y - sery / 2 - 1, centerCircle_X + 32 + serx / 2, centerCircle_Y - sery / 2 - 1);
        line(centerCircle_X + 32 + serx / 2 - 5, centerCircle_Y - sery / 2 - 1 - 5, centerCircle_X + 32 + serx / 2, centerCircle_Y - sery / 2 - 1);
        line(centerCircle_X + 32 + serx / 2 - 5, centerCircle_Y - sery / 2 - 1 + 5, centerCircle_X + 32 + serx / 2, centerCircle_Y - sery / 2 - 1);
    }
    else {
        setcolor(4);
        line(centerCircle_X, centerCircle_Y, centerCircle_X + 33, centerCircle_Y);
        line(centerCircle_X + 33, centerCircle_Y, centerCircle_X + 33, centerCircle_Y + sery);
        line(100 - serx / 2, centerCircle_Y + sery, centerCircle_X + 33, centerCircle_Y + sery);
        line(100 - serx / 2, centerCircle_Y, 100 - serx / 2, centerCircle_Y + sery);
        line(100 - serx / 2, y1 + sery, 100 - serx / 2, centerCircle_Y + sery);
        line(100 - serx / 2, y1 + sery, 100, y1 + sery);
        line(94, y1 + sery - 5, 99, y1 + sery);
        line(94, y1 + sery + 5, 99, y1 + sery);
    }
}

//Bieu dien da thuc duoi dang danh sach lien ket
void SHOW(POLY P, int x, int y) {
    int i = 0;
    MONO* k = P.Head;
    do {
        if (k->COEF != 0 || k->S == 0)
        {
            DrawANode(k, x, y);
            //_getch();

            //Draw link
            /*setcolor(8);
            if (k->S != 0) {
                int xx = circle_X - nx, yy1 = circle_Y + sery / 2 + 15, yy2 = circle_Y + ny + sery - 8;
                line(circle_X, circle_Y, circle_X, yy1);
                line(xx - 1, yy1, circle_X, yy1);
                line(xx, yy1, xx, yy2);
                line(xx, yy2, x, yy2);
            }
            else {
                setcolor(12);
                line(circle_X, circle_Y, circle_X + 50, circle_Y);
                line(circle_X + 50, 100 + sery, circle_X + 50, circle_Y);
                line(circle_X + serx / 2, 100 + sery, circle_X + 50, 100 + sery);
            }*/
            x += nx + 33 + nx / 3;
        }
        k = k->next;
    } while (k != nullptr && k != P.Head);
}

void setXY(POLY P, int x, int y) {
}

//In da thuc dang text o vi tri x, y
void InDaThuc(int x, int y, POLY P)
{
    wstring s = L"\0";
    wchar_t temp[256];
    MONO* k = P.Head;
    while (k->next != P.Head) {
        if (k->COEF != 0) {
            if (k->COEF != 1) {
                if (k->COEF != -1) {
                    _itow_s(k->COEF, temp, 10);
                    s += temp;
                }
                else {
                    s += L"-";
                }
            }
            if (k->A != 0) {
                s += L"x";
                s += superScript(k->A);
            }
            if (k->B != 0) {
                s += L"y";
                s += superScript(k->B);
            }
            if (k->C != 0) {
                s += L"z";
                s += superScript(k->C);
            }
            if (k->next != P.Head) {
                if (k->next->COEF > 0)
                    s += L"+";
            }
        }
        k = k->next;
    }
    lineWithText(x, y, 0, 0, s);
}

//Dang co loi -----------------------
//Phep cong 2 da thuc theo thuat toan
//void Add(POLY P, POLY Q) {
//    //Ket qua phep cong tra ve Q
//    MONO* mP, * mQ, * Q1, * Q2, * AVAIL; //mP la P, mQ la Q trong Algorithm A
//    AVAIL = (MONO*)malloc(sizeof(MONO));
//    Q1 = (MONO*)malloc(sizeof(MONO));
//    Q2 = (MONO*)malloc(sizeof(MONO));
//    mP = P.Head; mQ = Q.Head; //A1
//    int abcP, abcQ;
//    while (mP->next != P.Head && mQ->next != Q.Head) {
//        abcQ = mQ->A * 100 + mQ->B * 10 + mQ->C;
//        abcP = mP->A * 100 + mP->B * 10 + mP->C;
//
//        if (abcP < abcQ) { //A2
//            Q1 = mQ;
//            mQ = mQ->next;
//        }
//        else {
//            if (abcP == abcQ) //A3
//            {
//                if (abcP < 0)
//                    break;
//                else {
//                    mQ->COEF += mP->COEF;
//                    if (mQ->COEF == 0) { //A4
//                        Q2 = mQ;
//                        mQ = mQ->next;
//                        Q1->next = mQ;
//                        AVAIL = Q2;
//                        mP = mP->next;
//                    }
//                    else {
//                        mP = mP->next;
//                        Q1 = mQ;
//                        mQ = mQ->next;
//                    }
//                }
//            }
//            else //abcP > abcQ ; A5
//            {
//                Q2 = AVAIL;
//                Q2->COEF = mP->COEF; Q2->A = mP->A; Q2->B = mP->B; Q2->C = mP->C;
//                Q2->next = mQ; Q1->next = Q2; mP = mP->next;
//            }
//        }
//    }
//}

//Tinh ket qua cua phep cong 2 da thuc P va Q
POLY Add(POLY P, POLY Q) {
    POLY A;
    A.init();

    MONO* hP = P.Head, * hQ = Q.Head;
    MONO* hA, * p;

    while (hP->next != P.Head) {
        hA = (MONO*)malloc(sizeof(MONO));
        hA->COEF = hP->COEF; hA->A = hP->A; hA->B = hP->B; hA->C = hP->C; hA->S = 1;
        hA->next = A.Head;
        A.insertTail(hA);
        hP = hP->next;
    }
    while (hQ->next != Q.Head) {
        hA = (MONO*)malloc(sizeof(MONO));
        hA->COEF = hQ->COEF; hA->A = hQ->A; hA->B = hQ->B; hA->C = hQ->C; hA->S = 1;
        hA->next = A.Head;
        A.insertTail(hA);
        hQ = hQ->next;
    }
    p = (MONO*)malloc(sizeof(MONO));
    p->COEF = 0; p->A = 0; p->B = 0; p->C = 1; p->S = 0; p->next = A.Head;
    A.insertTail(p);
    A.RemoveDup();
    A.Sort();
    return A;
}

//Tinh ket qua cua phep nhan 2 da thuc P va Q
POLY Mul(POLY P, POLY Q) {
    POLY M;
    M.init();

    MONO* mP, * mQ, * hP, * hQ, * hM;
    hP = P.Head; hQ = Q.Head;

    mP = hP;
    while (mP->next != P.Head) {
        mQ = hQ;
        while (mQ->next != Q.Head) {
            hM = (MONO*)malloc(sizeof(MONO));
            hM->COEF = mP->COEF * mQ->COEF; hM->A = mP->A + mQ->A; hM->B = mP->B + mQ->B; hM->C = mP->C + mQ->C; hM->S = 1;
            hM->next = M.Head;
            M.insertTail(hM);
            mQ = mQ->next;
        }
        mP = mP->next;
    }
    MONO* p2 = (MONO*)malloc(sizeof(MONO));
    p2->COEF = 0; p2->A = 0; p2->B = 0; p2->C = 1; p2->S = 0; p2->next = M.Head;
    M.insertTail(p2);
    M.RemoveDup();
    M.Sort();
    return M;
}

int main()
{
    //_setmode(_fileno(stdout), _O_U16TEXT);
    char ini[] = "C:\\TURBOC3\\BGI";
    initgraph();
    int x = 100, y = 100;
    int coef, a, b, c, s;
    MONO* p1, * p2;
    POLY s1;
    s1.init();

    POLY s2;
    s2.init();

    FILE* file1 = fopen("../input1_2.txt", "r");
    FILE* file2 = fopen("../input2_2.txt", "r");
    if (!file1) {
        printf("Reading error!");
    }
    else {
        do {
            coef = 0; a = 0; b = 0; c = 0; s = 1;
            fscanf(file1, "%d %d %d %d\n", &coef, &a, &b, &c);
            p1 = (MONO*)malloc(sizeof(MONO));
            p1->COEF = coef; p1->A = a; p1->B = b; p1->C = c; p1->S = s;
            p1->next = s1.Head;
            s1.insertTail(p1);
        } while (!feof(file1));
    }
    p1 = (MONO*)malloc(sizeof(MONO));
    p1->COEF = 0; p1->A = 0; p1->B = 0; p1->C = 1; p1->S = 0; p1->next = s1.Head;
    s1.insertTail(p1);
    if (!file2) {
        printf("Reading error!");
    }
    else {
        do {
            coef = 0; a = 0; b = 0; c = 0; s = 1;
            fscanf(file2, "%d %d %d %d\n", &coef, &a, &b, &c);
            p2 = (MONO*)malloc(sizeof(MONO));
            p2->COEF = coef; p2->A = a; p2->B = b; p2->C = c; p2->S = s;
            p2->next = s2.Head;
            s2.insertTail(p2);
        } while (!feof(file2));
    }
    p2 = (MONO*)malloc(sizeof(MONO));
    p2->COEF = 0; p2->A = 0; p2->B = 0; p2->C = 1; p2->S = 0; p2->next = s2.Head;
    s2.insertTail(p2);
    fclose(file1);
    fclose(file2);

    s1.Sort(); s1.RemoveDup();
    s2.Sort(); s2.RemoveDup();
    ShowCur(0);
    system("pause");
    system("cls");
    bool co = false;
    do {
        int luachon = 0;
        if (!co) {
            system("cls");
            char* text = (char*)"==MENU==";
            lineWithText(920, 100, 0, 0, text);
            text = (char*)"1. Bieu dien da thuc thu nhat";
            lineWithText(850, 120, 0, 0, text);
            text = (char*)"2. Bieu dien da thuc thu hai";
            lineWithText(850, 140, 0, 0, text);
            text = (char*)"3. Ket qua phep cong";
            lineWithText(850, 160, 0, 0, text);
            text = (char*)"4. Ket qua phep nhan";
            lineWithText(850, 180, 0, 0, text);
            text = (char*)"0. Thoat khoi chuong trinh";
            lineWithText(850, 200, 0, 0, text);
        }
        co = true;
        if (_kbhit()) {
            char c = _getch();
            if (c >= '0' && c <= '9') {
                luachon = c - '0';
                co = false;
            }
            if (luachon != 1 && luachon != 2 && luachon != 3 && luachon != 4)
            {
                break;
            }
            else if (luachon == 1) {
                x = 100; y = 50;
                system("cls");
                char* text = (char*)"DA THUC THU NHAT: P = ";
                lineWithText(100, y, 0, 0, text);
                InDaThuc(100 + strlen(text) * 9, y, s1);
                y += 25;
                SHOW(s1, 100, 100);
                text = (char*)"AN NUT BAT KY DE QUAY VE MENU...";
                lineWithText(100, 170, 0, 0, text);
                _getch();
            }
            else if (luachon == 2) {
                x = 100; y = 50;
                system("cls");
                char* text = (char*)"DA THUC THU HAI: Q = ";
                lineWithText(100, y, 0, 0, text);
                InDaThuc(100 + strlen(text) * 9 - 7, y, s2);
                y += 25;
                SHOW(s2, 100, 100);
                text = (char*)"AN NUT BAT KY DE QUAY VE MENU...";
                lineWithText(100, 170, 0, 0, text);
                _getch();
            }
            else if (luachon == 3) {
                x = 100; y = 50;
                system("cls");
                /*char* text = (char*)"DA THUC THU NHAT: P = ";
                lineWithText(x, y, 0, 0, text);
                InDaThuc(x + strlen(text) * 9, y, s1);*/
                char* text = (char*)"P = ";
                lineWithText(50, 112, 0, 0, text);
                SHOW(s1, 100, 100);
                /*text = (char*)"DA THUC THU HAI: Q = ";
                lineWithText(x + 100 + (nx + 100), y, 0, 0, text);
                InDaThuc(x + 100 + strlen(text) * 9 - 6 + (nx + 100), y, s2);*/
                text = (char*)"Q = ";
                lineWithText(50, 192, 0, 0, text);
                SHOW(s2, 100, 180);
                POLY t1 = s1.CopyPoly();
                POLY t2 = s2.CopyPoly();
                POLY A = Add(t1, t2);
                text = (char*)"KET QUA PHEP CONG: A = P + Q = ";
                lineWithText(100, 370, 0, 0, text);
                InDaThuc(100 + strlen(text) * 9 - 9, 370, A);
                setcolor(1);
                line(0, 260, 2000, 260);
                text = (char*)"A = ";
                lineWithText(50, 312, 0, 0, text);
                SHOW(A, 100, 300);
                text = (char*)"AN NUT BAT KY DE QUAY VE MENU...";
                lineWithText(100, 410, 0, 0, text);
                _getch();
            }
            else if (luachon == 4) {
                x = 100; y = 50;
                system("cls");
                /*char* text = (char*)"DA THUC THU NHAT: P = ";
                lineWithText(x, y, 0, 0, text);
                InDaThuc(x + strlen(text) * 9, y, s1);*/
                char* text = (char*)"P = ";
                lineWithText(50, 112, 0, 0, text);
                SHOW(s1, 100, 100);
                /*text = (char*)"DA THUC THU HAI: Q = ";
                lineWithText(x + 100 + (nx + 100), y, 0, 0, text);
                InDaThuc(x + 100 + strlen(text) * 9 - 6 + (nx + 100), y, s2);*/
                text = (char*)"Q = ";
                lineWithText(50, 192, 0, 0, text);
                SHOW(s2, 100, 180);
                POLY t1 = s1.CopyPoly();
                POLY t2 = s2.CopyPoly();
                POLY M = Mul(t1, t2);
                text = (char*)"KET QUA PHEP NHAN: M = P x Q = ";
                lineWithText(100, 370, 0, 0, text);
                InDaThuc(100 + strlen(text) * 9 - 9, 370, M);
                setcolor(1);
                line(0, 260, 2000, 260);
                text = (char*)"M = ";
                lineWithText(50, 312, 0, 0, text);
                SHOW(M, 100, 300);
                text = (char*)"AN NUT BAT KY DE QUAY VE MENU...";
                lineWithText(100, 410, 0, 0, text);
                _getch();
            }
        }
    } while (true);
    return 0;
}