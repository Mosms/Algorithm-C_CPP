#include <cstdio>
#include <cmath>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cassert>

typedef std::string Bibmber;
const Bibmber One = {'1'};
const Bibmber Zero = {'0'};
const int maxL = 100;
bool Only_Pos_Bigger(Bibmber fi, Bibmber sec);
bool Bigger(Bibmber fi, Bibmber sec);
Bibmber Only_Pos_Muti(Bibmber num_1, Bibmber num_2);
Bibmber Muti(Bibmber num_1, Bibmber num_2);
Bibmber Only_Pos_Add(Bibmber num_1, Bibmber num_2);
Bibmber Only_Pos_Minus(Bibmber num_1, Bibmber num_2);
Bibmber Minus(Bibmber num_1, Bibmber num_2);
Bibmber Add(Bibmber num_1, Bibmber num_2);
Bibmber Square(Bibmber thisone);
Bibmber Cube(Bibmber thisone);
Bibmber Max(Bibmber fi, Bibmber sec);

int main(void)
{
    Bibmber a, b;
    while (std::cin >> a >> b)
    {
        std::cout << "Minus:" << Minus(a, b) << std::endl;
        std::cout << "Add:" << Add(a, b) << std::endl;
        std::cout << "Mutiply:" << Muti(a, b) << std::endl;
        std::cout << "Max:" << Max(a, b) << std::endl;
    }
    return 0;
}

bool Only_Pos_Bigger(Bibmber fi, Bibmber sec)
{ //大于等于返回true
    int len1 = fi.length(), len2 = sec.length();
    if (len1 > len2)
        return true;
    else if (len1 < len2)
        return false;
    else // len1==len2
        for (int i = 0; i < len1; i++)
            if (fi[i] > sec[i])
                return true;
            else if (fi[i] < sec[i])
                return false;
            else
                continue;
    return true; //决定相等的返回情况
}
bool Bigger(Bibmber fi, Bibmber sec)
{
    if (fi[0] == '-' && sec[0] == '-')
    {
        fi.erase(fi.begin());
        sec.erase(sec.begin());
        return !Only_Pos_Bigger(fi, sec);
    }
    else if (fi[0] == '-')
        return false;
    else if (sec[0] == '-')
        return true;
    else
        return Only_Pos_Bigger(fi, sec);
}

Bibmber Only_Pos_Muti(Bibmber num_1, Bibmber num_2)
{
    assert(num_1[0] != '-' && num_2[0] != '-');
    Bibmber Ans;
    int n1[maxL], n2[maxL], n_ans[maxL], L1 = num_1.size(), L2 = num_2.size();
    std::fill(n1, n1 + maxL, 0);
    std::fill(n2, n2 + maxL, 0);
    std::fill(n_ans, n_ans + maxL, 0);
    for (int i = L1 - 1; i >= 0; i--)
        n1[L1 - i] = num_1[i] - '0';
    for (int i = L2 - 1; i >= 0; i--)
        n2[L2 - i] = num_2[i] - '0';
    for (int i = 1; i <= L1; i++)
        for (int j = 1; j <= L2; j++)
            n_ans[i + j - 1] += n1[i] * n2[j];
    for (int i = 1; i <= L1 + L2; i++)
        n_ans[i + 1] += n_ans[i] / 10, n_ans[i] %= 10;
    if (n_ans[L1 + L2])
        Ans += n_ans[L1 + L2] + '0';
    for (int i = L1 + L2 - 1; i >= 1; i--)
        Ans += n_ans[i] + '0';
    return Ans;
}
Bibmber Muti(Bibmber num_1, Bibmber num_2)
{
    if (num_1[0] == '-' && num_2[0] == '-')
    {
        num_1.erase(num_1.begin());
        num_2.erase(num_2.begin());
        return Only_Pos_Muti(num_1, num_2);
    }
    else if (num_1[0] == '-')
    {
        num_1.erase(num_1.begin());
        return '-' + Only_Pos_Muti(num_1, num_2);
    }
    else if (num_2[0] == '-')
    {
        num_2.erase(num_2.begin());
        return '-' + Only_Pos_Muti(num_1, num_2);
    }
    else
        return Only_Pos_Muti(num_1, num_2);
}
Bibmber Only_Pos_Add(Bibmber num_1, Bibmber num_2)
{
    Bibmber Ans;
    int n1[maxL] = {0}, n2[maxL] = {0};
    int L1 = num_1.size(), L2 = num_2.size();
    for (int i = L1 - 1; i >= 0; i--)
        n1[L1 - 1 - i] = num_1[i] - '0';
    for (int i = L2 - 1; i >= 0; i--)
        n2[L2 - 1 - i] = num_2[i] - '0';
    int Lmax = std::max(L1, L2);
    for (int i = 0; i < Lmax; i++)
        n1[i] += n2[i], n1[i + 1] += n1[i] / 10, n1[i] %= 10;
    if (n1[Lmax])
        Lmax++;
    for (int i = Lmax - 1; i >= 0; i--)
        Ans += n1[i] + '0';
    return Ans;
}
Bibmber Only_Pos_Minus(Bibmber num_1, Bibmber num_2)
{
    Bibmber Ans;
    int n1[maxL] = {0}, n2[maxL] = {0};
    int L1 = num_1.size(), L2 = num_2.size();
    for (int i = L1 - 1; i >= 0; i--)
        n1[L1 - 1 - i] = num_1[i] - '0';
    for (int i = L2 - 1; i >= 0; i--)
        n2[L2 - 1 - i] = num_2[i] - '0';
    int Lmax = std::max(L1, L2);
    for (int i = 0; i < Lmax; i++)
    {
        n1[i] -= n2[i];
        if (n1[i] < 0) //借位
            n1[i] += 10, n1[i + 1]--;
    }
    while (!n1[--Lmax] && Lmax > 0)
        ;
    Lmax++;
    for (int i = Lmax - 1; i >= 0; i--)
        Ans += n1[i] + '0';
    return Ans;
}
Bibmber Add(Bibmber num_1, Bibmber num_2)
{
    if (num_1[0] == '-' && num_2[0] == '-')
    {
        num_1.erase(num_1.begin());
        num_2.erase(num_2.begin());
        return '-' + Only_Pos_Add(num_1, num_2);
    }
    else if (num_1[0] == '-' || num_2[0] == '-')
    {
        if (num_2[0] == '-')
            std::swap(num_1, num_2);
        num_1.erase(num_1.begin());
        if (Only_Pos_Bigger(num_2, num_1)) //正好在相等的时候返回0，不会返回-0
            return Only_Pos_Minus(num_2, num_1);
        else
            return '-' + Only_Pos_Minus(num_1, num_2);
    }
    else
        return Only_Pos_Add(num_1, num_2);
}
Bibmber Minus(Bibmber num_1, Bibmber num_2)
{
    if (num_2[0] == '-')
    {
        num_2.erase(num_2.begin());
        return Add(num_1, num_2);
    }
    else if (num_2[0] == '0') //等于0
        return num_1;
    else
        return Add(num_1, '-' + num_2);
}
Bibmber Square(Bibmber thisone)
{
    return Muti(thisone, thisone);
}
Bibmber Cube(Bibmber thisone)
{
    return Muti(Square(thisone), thisone);
}
Bibmber Max(Bibmber fi, Bibmber sec)
{
    if (Bigger(fi, sec))
        return fi;
    else
        return sec;
}