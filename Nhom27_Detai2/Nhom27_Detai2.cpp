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
void DrawANode(MONO* k, int x1, int y1, int color, bool LINK) {
    setcolor(color);
    line(x1 - 1, y1, x1 + nx, y1);
    line(x1, y1 + ny, x1 + nx, y1 + ny);
    line(x1, y1 - 1, x1, y1 + ny);
    line(x1 + nx, y1, x1 + nx, y1 + ny);
    serx = nx / 3, sery = ny / 2;
    line(x1, y1 + sery, x1 + nx, y1 + sery);
    line(x1 + serx, y1 + sery, x1 + serx, y1 + ny);
    line(x1 + 2 * serx, y1 + sery, x1 + 2 * serx, y1 + ny);
    
    sprintf_s(temp, " %d ", k->COEF);
    int len = strlen(temp);
    lineWithText(x1 + (nx / 2) - len * 5 + 9, y1, 0, 0, k->COEF);
    sprintf_s(temp, " %d ", k->A);
    len = strlen(temp);
    lineWithText(x1 + (serx / 2) - 5, y1 + sery, 0, 0, k->A);
    sprintf_s(temp, " %d ", k->B);
    len = strlen(temp);
    lineWithText(x1 + serx + (serx / 2) - 5, y1 + sery, 0, 0, k->B);
    sprintf_s(temp, " %d ", k->C);
    len = strlen(temp);
    if (k->S == 0) {
        lineWithText(x1 + serx * 2 + (serx / 2) - 5, y1 + sery, 0, 0, -k->C);
    }
    else lineWithText(x1 + serx * 2 + (serx / 2) - 5, y1 + sery, 0, 0, k->C);
    setcolor(3);
    if (LINK == true) {
        line(x1 + nx, y1 + sery, x1 + nx + serx, y1 + sery);
        line(x1 + nx + serx, y1 + sery, x1 + nx + serx, y1 + ny);
        line(x1 + nx, y1 + ny, x1 + nx + serx, y1 + ny);
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
}

//Bieu dien da thuc duoi dang danh sach lien ket
void SHOW(POLY P, int x, int y) {
    int i = 0;
    MONO* k = P.Head;
    do {
        if (k->COEF != 0 || k->S == 0)
        {
            DrawANode(k, x, y, 7, 1);
            x += nx + 33 + nx / 3;
        }
        k = k->next;
    } while (k != nullptr && k != P.Head);
}

void SHOW(POLY P, int x, int y, bool LINK) {
    int i = 0;
    MONO* k = P.Head;
    do {
        if (k->COEF != 0 || k->S == 0)
        {
            DrawANode(k, x, y, 7, LINK);
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
    A.RemoveZero();
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
    M.RemoveZero();
    M.RemoveDup();
    M.Sort();
    return M;
}

void moPhongAdd(POLY P, POLY Q) {
    SHOW(P, 100, 100);
    SHOW(Q, 100, 180);
    POLY A = Add(P, Q);
    int xP = 100, yP = 100, xQ = 100, yQ = 180, xA = 100, yA = 300;
    MONO* hP = P.Head, * hQ = Q.Head, * hA = A.Head;
    Sleep(500);
    while (hA->next != A.Head) {
        if (tinhABC(hP) < tinhABC(hQ)) {
            DrawANode(hQ, xQ, yQ, 9, 0);
            xQ += nx + 33 + nx / 3;
            DrawANode(hA, xA, yA, 9, 0);
            xA += nx + 33 + nx / 3;
            hQ = hQ->next;
            hA = hA->next;
            Sleep(1000);
        }
        else if (tinhABC(hP) == tinhABC(hQ))
        {
            DrawANode(hP, xP, yP, 10, 0);
            xP += nx + 33 + nx / 3;
            DrawANode(hQ, xQ, yQ, 10, 0);
            xQ += nx + 33 + nx / 3;
            DrawANode(hA, xA, yA, 10, 0);
            xA += nx + 33 + nx / 3;
            hP = hP->next;
            hQ = hQ->next;
            hA = hA->next;
            Sleep(1000);
        }
        else if (tinhABC(hP) > tinhABC(hQ)) {
            DrawANode(hP, xP, yP, 8, 0);
            xP += nx + 33 + nx / 3;
            DrawANode(hA, xA, yA, 8, 0);
            xA += nx + 33 + nx / 3;
            hP = hP->next;
            hA = hA->next;
            Sleep(1000);
        }
        if (hA->next == A.Head) {
            DrawANode(hA, xA, yA, 7, 0);
            xA += nx + 33 + nx / 3;
            Sleep(1000);
        }
    }
}


void moPhongMul(POLY P, POLY Q) {
    POLY M = Mul(P, Q);
    POLY T;
    T.init();
    SHOW(P, 100, 100, 0);
    SHOW(Q, 100, 180, 0);
    MONO* hP = P.Head, * hQ = Q.Head, * hM = M.Head;
    int xP = 100, yP = 100, xQ = 100, yQ = 180, xM = 100, yM = 300, color = 1;
    int demY = 0;
    MONO* t; 
    int xt = 100, yt = 460;
    struct POS pos[1000];
    int ipos = 0;
    while (hP->next != P.Head) {
        color++;
        DrawANode(hP, xP, yP, color, 0);
        xP += nx + 33 + nx / 3;
        hQ = Q.Head;
        xQ = 100;
        if (color == 15 || color == 7 || color == 1)
            color++;
        while (hQ->next != Q.Head) {
            DrawANode(hQ, xQ, yQ, color, 0);
            xQ += nx + 33 + nx / 3;
            t = (MONO*)malloc(sizeof(MONO));
            t->COEF = hP->COEF * hQ->COEF; 
            t->A = hP->A + hQ->A; t->B = hP->B + hQ->B; t->C = hP->C + hQ->C; t->S = 2; t->next = T.Head;
            T.insertTail(t);
            hQ = hQ->next;
            pos[ipos].posx = xt;
            pos[ipos].posy = yt;
            ipos++;
            DrawANode(t, xt, yt, 1, 0);
            xt += nx + 33 + nx / 3;
            demY++;
            if (demY == 9)
            {
                yt += 60;
                xt = 100;
            }
            Sleep(500);
        }
        hP = hP->next;
    }
    hM = M.Head; color = 2;
    int i;
    MONO* hT;
    while (hM->next != M.Head) {
        i = 0;
        DrawANode(hM, xM, yM, color, 0);
        xM += nx + 33 + nx / 3;
        hT = T.Head;
        while (hT->next != T.Head) {
            if (tinhABC(hM) == tinhABC(hT)) {
                DrawANode(hT, pos[i].posx, pos[i].posy, color, 0);
                Sleep(500);
            }
            i++;
            hT = hT->next;
        }
        color++;
        hM = hM->next;
        if (hM->next == M.Head) {
            Sleep(500);
            DrawANode(hM, xM, yM, 7, 0);
            xM += nx + 33 + nx / 3;
            Sleep(1000);
        }
    }
}

int main()
{
    system("color f1");
    char ini[] = "C:\\TURBOC3\\BGI";
    initgraph();
    int x = 100, y = 100;
    int coef, a, b, c, s;
    MONO* p1, * p2;
    POLY s1;
    s1.init();

    POLY s2;
    s2.init();

    FILE* file1 = fopen("../input1_1.txt", "r");
    FILE* file2 = fopen("../input2_1.txt", "r");
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
    //system("pause");
    //system("cls");
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
                moPhongAdd(s1, s2); 
                Sleep(1000);
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
                moPhongMul(s1, s2);
                Sleep(1000);
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