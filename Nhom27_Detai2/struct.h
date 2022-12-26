#include <iostream>

struct MONO {           //Don thuc (monomial)
    int COEF;           //COEF la he so
    int A, B, C, S;     //A la so mu cua x, B la y, C la z, S la sign
    MONO* next;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
};

int tinhABC(MONO* P) {
    if (P == nullptr || P->S == 0)
        return -1;
    return (P->A * 100 + P->B * 10 + P->C);
}

struct POLY {           //Da thuc (polynomial)
    MONO* Head, * Tail;
    void init() {
        Head = nullptr;
        Tail = nullptr;
    }
    void insertTail(MONO* Y)
    {
        if (Head == nullptr)
        {
            Head = Tail = Y;
        }
        else
        {
            Tail->next = Y;
            Tail = Y;
        }
    }
    void Sort() {
        MONO* temp = (MONO*)malloc(sizeof(MONO));
        for (MONO* i = Head; i->next->next != Head; i = i->next) {
            for (MONO* j = i->next; j->next != Head; j = j->next) {
                if (tinhABC(i) < tinhABC(j)) {
                    temp->COEF = i->COEF; temp->A = i->A; temp->B = i->B; temp->C = i->C; temp->S = i->S;
                    i->COEF = j->COEF; i->A = j->A; i->B = j->B; i->C = j->C; i->S = j->S;
                    j->COEF = temp->COEF; j->A = temp->A; j->B = temp->B; j->C = temp->C; j->S = temp->S;
                }
            }
        }
    }
    void RemoveDup() {
        MONO* dup, * i, * j;
        i = Head;
        while (i->next != Head) {
            j = i;
            while (j->next != Head) {
                if (tinhABC(i) == tinhABC(j->next)) {
                    i->COEF += j->next->COEF;
                    dup = j->next;
                    j->next = j->next->next;
                    delete(dup);
                }
                else j = j->next;
            }
            i = i->next;
        }
    }
    POLY CopyPoly() {
        POLY Q;
        MONO* cur = Head, * p;
        Q.Head = nullptr;
        Q.Tail = nullptr;
        while (cur->next != Head) {
            p = (MONO*)malloc(sizeof(MONO));
            p->COEF = cur->COEF; p->A = cur->A; p->B = cur->B; p->C = cur->C; p->S = cur->S;
            p->next = nullptr;
            Q.insertTail(p);
            cur = cur->next;
        }
        p = (MONO*)malloc(sizeof(MONO));
        p->COEF = 0; p->A = 0; p->B = 0; p->C = -1; p->S = 0; p->next = Q.Head;
        Q.insertTail(p);
        return Q;
    }

};
const wchar_t* superScript(int pow) {
    switch (pow)
    {
    case 2:
        return L"\u00b2";
    case 3:
        return L"\u00b3";
    case 4:
        return L"\u2074";
    case 5:
        return L"\u2075";
    case 6:
        return L"\u2076";
    case 7:
        return L"\u2077";
    case 8:
        return L"\u2078";
    case 9:
        return L"\u2079";
    default:
        return L"\0";
        break;
    }
}