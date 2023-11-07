#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;
class intx
{
private:
    bool sign;
    int *num;
    int len;
    static int process_char(const char *s, bool &sign, int *&num);
    static bool unsign_gt(const int *a, const int lena, const int *b, const int lenb);
    static bool unsign_gte(const int *a, const int lena, const int *b, const int lenb);
    static int unsign_plus(const int *a, int lena, const int *b, int lenb, int *&result);
    static int unsign_minus(const int *a, int lena, const int *b, int lenb, int *&result);
    static int multiply_base(const int *a, const int lena, int n, int *&result);
    static int unsgin_multiply(const int *a, const int lena, const int *b, const int lenb, int *&result);
    static bool divide_gte(const int *a, int end, const int *b, int lenb);
    static int unsign_divide(const int *a, const int lena, const int *b, const int lenb, int *&result);
    static int unsign_mod(const int *a, const int lena, const int *b, const int lenb, int *&result);

public:
    // constructor
    intx();
    intx(const char *s);
    intx(const std::string &str);
    intx(int n);
    intx(const intx &b);
    // destructor
    ~intx();
    // calc
    int turnIntxToint() const;
    bool operator==(const intx &b) const;
    bool operator>(const intx &b) const;
    bool operator>=(const intx &b) const;
    bool operator<(const intx &b) const;
    bool operator<=(const intx &b) const;
    intx operator-() const;
    intx operator+(const intx &b) const;
    intx operator-(const intx &b) const;
    intx operator*(const intx &b) const;
    intx operator/(const intx &b) const;
    intx operator%(const intx &b) const;
    // others
    friend std::ostream &operator<<(std::ostream &os, const intx &a);
    friend std::istream &operator>>(std::istream &is, intx &a);
    int &operator[](const int sub) const;
    intx &operator=(const intx &b);
    intx &operator=(const char *s);
    intx &operator=(const std::string &str);
    int size() { return len; }
    bool IsNatural() const { return sign; }
};

// private
int intx::turnIntxToint() const
{
    int ans = 0;
    for (int i = 0; i < len; i++)
        ans = ans * 10 + num[i];
    return ans;
}

int intx::process_char(const char *s, bool &sign, int *&num)
{
    int len = strlen(s);
    if (!len) // len == 0
    {
        sign = true;
        num = new int[1];
        num[0] = 0;
        len = 1;
    }
    else
        switch (s[0])
        {
        case '+':
            sign = true;
            --len;
            num = new int[len];
            for (int i = 0; i < len; ++i)
                num[i] = s[i + 1] - '0';
            break;
        case '-':
            sign = false;
            --len;
            num = new int[len];
            for (int i = 0; i < len; ++i)
                num[i] = s[i + 1] - '0';
            break;
        default:
            sign = true;
            num = new int[len];
            for (int i = 0; i < len; ++i)
                num[i] = s[i] - '0';
            break;
        }
    return len;
}
bool intx::unsign_gt(const int *a, const int lena, const int *b, const int lenb)
{
    if (lena < lenb)
        return false;
    else if (lena > lenb)
        return true;
    else
    {
        for (int i = 0; i < lena; ++i)
            if (a[i] < b[i])
                return false;
            else if (a[i] > b[i])
                return true;
        return false;
    }
}
bool intx::unsign_gte(const int *a, const int lena, const int *b, const int lenb)
{
    if (lena < lenb)
        return false;
    else if (lena > lenb)
        return true;
    else
    {
        for (int i = 0; i < lena; ++i)
            if (a[i] < b[i])
                return false;
            else if (a[i] > b[i])
                return true;
        return true;
    }
}
int intx::unsign_plus(const int *a, int lena, const int *b, int lenb, int *&result)
{
    int rem;
    if (lenb > lena)
    {
        const int *temp = a;
        a = b;
        b = temp;
        rem = lena;
        lena = lenb;
        lenb = rem;
    }
    int len = lena + 1;
    result = new int[len];
    int sub = lena;
    rem = 0;
    --lena;
    --lenb;
    while (lenb >= 0)
    {
        rem += a[lena--] + b[lenb--];
        result[sub--] = rem % 10;
        rem /= 10;
    }
    while (lena >= 0)
    {
        rem += a[lena--];
        result[sub--] = rem % 10;
        rem /= 10;
    }
    if (rem > 0)
    {
        result[sub] = rem;
    }
    else
    {
        --len;
        int *p = new int[len];
        memcpy(p, result + 1, sizeof(int) * len);
        delete[] result;
        result = p;
    }
    return len;
}
int intx::unsign_minus(const int *a, int lena, const int *b, int lenb, int *&result) // a must > b
{
    int len = lena;
    result = new int[len];
    memcpy(result, a, sizeof(int) * len); // const int *a can't modify
    --lenb;
    --lena;
    while (lenb >= 0)
    {
        if (a[lena] >= b[lenb])
            result[lena] -= b[lenb];
        else
        {
            result[lena] += 10 - b[lenb];
            --result[lena - 1];
        }
        --lena;
        --lenb;
    }
    while (lena >= 0)
    {
        if (result[lena] < 0)
        {
            result[lena] += 10;
            --result[lena - 1];
            --lena;
        }
        else
            break;
    }
    int zero = 0;
    while (zero < len)
        if (result[zero] == 0)
            ++zero;
        else
            break;
    if (zero == len)
    {
        delete[] result;
        result = new int[1]{0};
        len = 1;
    }
    else if (zero != 0)
    {
        len -= zero;
        int *p = new int[len];
        memcpy(p, result + zero, sizeof(int) * len);
        delete[] result;
        result = p;
    }
    return len;
}
bool intx::divide_gte(const int *a, const int end, const int *b, const int lenb)
{
    int begin = 0;
    while (a[begin] == 0)
    {
        ++begin;
    }
    if (end - begin + 1 < lenb)
        return false;
    else if (end - begin + 1 > lenb)
        return true;
    else
    {
        for (int i = 0; i < lenb; ++begin, ++i)
            if (a[begin] > b[i])
                return true;
            else if (a[begin] < b[i])
                return false;
        return true;
    }
}
int intx::multiply_base(const int *a, int lena, const int n, int *&result) // the first may be 0
{
    int len = lena + 1;
    result = new int[len];
    int rem = 0;
    int sub = lena;
    --lena;
    while (lena >= 0)
    {
        rem += n * a[lena];
        result[sub] = rem % 10;
        rem /= 10;
        --lena;
        --sub;
    }
    if (rem > 0)
        result[sub] = rem;
    else
        result[sub] = 0;
    return len;
}
int intx::unsgin_multiply(const int *a, const int lena, const int *b, const int lenb, int *&result) // a on the top
{
    int len = lena + lenb;
    result = new int[len]{0};
    int *MultiplyTemp;
    int MultiplyBit = lenb - 1; // the subscript of number in the b to be multiplied
    while (MultiplyBit >= 0)
    {
        int MultiplyTempSub = multiply_base(a, lena, b[MultiplyBit], MultiplyTemp);
        // plus
        int rem = 0;
        int sub = len - (lenb - MultiplyBit); // the bit when result begin plus
        --MultiplyTempSub;
        while (MultiplyTempSub >= 0)
        {
            rem += result[sub] + MultiplyTemp[MultiplyTempSub];
            result[sub] = rem % 10;
            rem /= 10;
            --sub;
            --MultiplyTempSub;
        }
        if (rem > 0)
            result[sub] += rem;
        --MultiplyBit;
        delete[] MultiplyTemp;
    }
    int zero = 0;
    while (zero < len)
        if (result[zero] == 0)
            ++zero;
        else
            break;
    if (zero == len)
    {
        delete[] result;
        result = new int[1]{0};
        return 1;
    }
    else if (zero != 0)
    {
        len -= zero;
        int *p = new int[len];
        memcpy(p, result + zero, sizeof(int) * len);
        delete[] result;
        result = p;
    }
    return len;
}
int intx::unsign_divide(const int *a, const int lena, const int *b, const int lenb, int *&result)
{
    if (lena < lenb)
    {
        result = new int[1]{0};
        return 1;
    }
    // Judge the first bit
    int CurrentBit = lenb - 1; // the current number on the consult
    int len;
    if (!divide_gte(a, CurrentBit, b, lenb))
        if (CurrentBit + 1 == lena) // lena == lenb && a < b
        {
            result = new int[1]{0};
            return 1;
        }
        else
        {
            ++CurrentBit;
            len = lena - lenb;
            result = new int[len];
        }
    else
    {
        len = lena - lenb + 1;
        result = new int[len];
    }
    // copy
    int *A = new int[lena];
    memcpy(A, a, sizeof(int) * lena);
    int sub = 0; // sub = CurrentBit - (lena - lenb)，too much calc
    while (CurrentBit < lena)
    {
        result[sub] = 0;
        do
        {
            // minus
            int Asub = CurrentBit;
            for (int i = lenb - 1; i >= 0; --Asub, --i)
                if (A[Asub] >= b[i])
                    A[Asub] -= b[i];
                else
                {
                    A[Asub] += 10 - b[i];
                    --A[Asub - 1];
                }
            while (Asub >= 0)
                if (A[Asub] < 0)
                {
                    A[sub] += 10;
                    --A[Asub - 1];
                    --Asub;
                }
                else
                    break;
            ++result[sub];
        } while (divide_gte(A, CurrentBit, b, lenb));
        if (++sub, ++CurrentBit == lena)
            break;
        while (!divide_gte(A, CurrentBit, b, lenb))
        {
            result[sub] = 0;
            if (++sub, ++CurrentBit == lena)
                break;
        }
    }
    delete[] A;
    return len;
}
int intx::unsign_mod(const int *a, const int lena, const int *b, const int lenb, int *&result)
{
    int len = lena;
    result = new int[len];
    memcpy(result, a, sizeof(int) * len);
    if (lena < lenb)
        return len;
    // Judge the first bit
    int CurrentBit = lenb - 1; // the current number on the consult
    if (!divide_gte(result, CurrentBit, b, lenb))
    {
        if (CurrentBit + 1 == len) // lena == lenb && a < b
            return len;
        else
            ++CurrentBit;
    }
    while (CurrentBit < len)
    {
        do
        {
            // minus
            int sub = CurrentBit;
            for (int i = lenb - 1; i >= 0; --sub, --i)
                if (result[sub] >= b[i])
                    result[sub] -= b[i];
                else
                {
                    result[sub] += 10 - b[i];
                    --result[sub - 1];
                }
            while (sub >= 0)
                if (result[sub] < 0)
                {
                    result[sub] += 10;
                    --result[sub - 1];
                    --sub;
                }
                else
                    break;
        } while (divide_gte(result, CurrentBit, b, lenb));
        while (++CurrentBit != len)
            if (divide_gte(result, CurrentBit, b, lenb))
                break;
    }
    int zero = 0;
    while (zero < len)
        if (result[zero] == 0)
            ++zero;
        else
            break;
    if (zero == len)
    {
        delete[] result;
        result = new int[1]{0};
        len = 1;
    }
    else if (zero != 0)
    {
        len -= zero;
        int *p = new int[len];
        memcpy(p, result + zero, sizeof(int) * len);
        delete[] result;
        result = p;
    }
    return len;
}
// constructor
intx::intx()
{
    sign = true;
    num = new int[1];
    num[0] = 0;
    len = 1;
}
intx::intx(const char *s)
{
    len = process_char(s, sign, num);
}
intx::intx(const std::string &str)
{
    const char *s = str.data();
    new (this) intx(s);
}
intx::intx(int n)
{
    if (n < 0)
        sign = false;
    else
        sign = true;
    if (n == 0)
    {
        len = 1;
        num = new int[1]{0};
        return;
    }
    len = 0;
    int N = n;
    while (n > 0)
    {
        n /= 10;
        ++len;
    }
    num = new int[len];
    for (int i = len; i > 0; --i)
    {
        num[i - 1] = N % 10;
        N /= 10;
    }
}
intx::intx(const intx &b)
{
    sign = b.sign;
    len = b.len;
    num = new int[len];
    memcpy(num, b.num, sizeof(int) * len);
}
// destructor
intx::~intx()
{
    delete[] num;
}

// calc
bool intx::operator==(const intx &b) const
{
    if (len != b.len)
        return false;
    else if (sign != b.sign)
        return false;
    else
    {
        for (int i = 0; i < len; ++i)
            if (num[i] != b.num[i])
                return false;
        return true;
    }
}
bool intx::operator>(const intx &b) const
{
    if (sign)
        if (b.sign)
            return unsign_gt(num, len, b.num, b.len);
        else
            return true;
    else if (b.sign)
        return false;
    else
        return !unsign_gt(num, len, b.num, b.len);
}
bool intx::operator>=(const intx &b) const
{
    if (sign)
        if (b.sign)
            return unsign_gte(num, len, b.num, b.len);
        else
            return true;
    else if (b.sign)
        return false;
    else
        return !unsign_gte(num, len, b.num, b.len);
}
bool intx::operator<(const intx &b) const
{
    return !(*this >= b);
}
bool intx::operator<=(const intx &b) const
{
    return !(*this > b);
}
intx intx::operator-() const
{
    intx b = *this;
    b.sign = !b.sign;
    return b;
}
intx intx::operator+(const intx &b) const
{
    intx sum;
    delete[] sum.num;
    if (sign)       // a >= 0
        if (b.sign) // a > 0 && b > 0
        {
            sum.sign = true;
            sum.len = unsign_plus(num, len, b.num, b.len, sum.num);
        }
        else if (unsign_gte(num, len, b.num, b.len)) // a > 0,b < 0,|a| >= |b|
        {
            sum.sign = true;
            sum.len = unsign_minus(num, len, b.num, b.len, sum.num);
        }
        else // a > 0,b < 0,|a| < |b|
        {
            sum.sign = false;
            sum.len = unsign_minus(b.num, b.len, num, len, sum.num);
        }
    else // a < 0
    {
        if (!b.sign) // a < 0, b < 0
        {
            sum.sign = false;
            sum.len = unsign_plus(num, len, b.num, b.len, sum.num);
        }
        else if (unsign_gte(b.num, b.len, num, len)) // a < 0,b > 0,|a| <= |b|
        {
            sum.sign = true;
            sum.len = unsign_minus(b.num, b.len, num, len, sum.num);
        }
        else // a < 0 b > 0 , |a| > |b|
        {
            sum.sign = false;
            sum.len = unsign_minus(num, len, b.num, b.len, sum.num);
        }
    }
    return sum;
}
intx intx::operator-(const intx &b) const
{
    return *this + (-b);
}
intx intx::operator*(const intx &b) const
{
    intx product;
    if (sign == b.sign)
        product.sign = true;
    else
        product.sign = false;
    delete[] product.num;
    product.len = unsgin_multiply(num, len, b.num, b.len, product.num);
    return product;
}
intx intx::operator/(const intx &b) const
{
    intx consult;
    if (sign == b.sign)
        consult.sign = true;
    else
        consult.sign = false;
    delete[] consult.num;
    consult.len = unsign_divide(num, len, b.num, b.len, consult.num);
    if (consult[0] == 0) // avoid "-0"
        consult.sign = true;
    return consult;
}
intx intx::operator%(const intx &b) const
{
    intx modulo;
    delete[] modulo.num;
    modulo.sign = sign;
    modulo.len = unsign_mod(num, len, b.num, b.len, modulo.num);
    return modulo;
}
// others
std::ostream &operator<<(std::ostream &os, const intx &a)
{
    if (!a.sign)
        os << '-';
    for (int i = 0; i < a.len; ++i)
        os << a.num[i];
    return os;
}
std::istream &operator>>(std::istream &is, intx &a)
{
    delete[] a.num;
    int max = 16;
    a.num = new int[max];
    // Judge sign
    char c;
    a.len = 0;
    c = getchar();
    if (c == '-')
        a.sign = false;
    else if (c == '+')
        a.sign = true;
    else if (c <= '9' && c >= '1') // the first num
    {
        a.num[a.len] = c - '0';
        ++a.len;
    }
    else
    {
        a.sign = true;
        a.num[a.len] = 0;
        ++a.len;
        return is;
    }
    // makesure the first bit is inputed
    if (a.len == 0)
    {
        c = getchar();
        if (c >= '1' && c <= '9')
        {
            a.num[a.len] = c - '0';
            ++a.len;
        }
        else
        {
            a.sign = true;
            a.num[a.len] = 0;
            ++a.len;
            return is;
        }
    }
    while (c = is.peek(), c >= '0' && c <= '9')
    {
        is >> c;
        a.num[a.len] = c - '0';
        if (++a.len == max)
        {
            max *= 2;
            int *temp = new int[max];
            memcpy(temp, a.num, sizeof(int) * a.len);
            delete[] a.num;
            a.num = temp;
        }
    }
    return is;
}
int &intx::operator[](const int sub) const
{
    return num[len - 1 - sub];
}
intx &intx::operator=(const intx &b)
{
    if (this == &b)
        return *this;
    else
    {
        len = b.len;
        sign = b.sign;
        delete[] num;
        num = new int[len];
        memcpy(num, b.num, sizeof(int) * len);
        return *this;
    }
}
intx &intx::operator=(const char *s)
{
    delete[] num;
    len = process_char(s, sign, num);
    return *this;
}
intx &intx::operator=(const std::string &str)
{
    delete[] num;
    len = process_char(str.data(), sign, num);
    return *this;
}

int n;
const int N = 30 + 5;
int a[N];

int main()
{
    scanf("%d ", &n);
    intx m;   // 高精度数的类型为intx
    cin >> m; // 读入高精度数
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    intx p = m + 2;            // 加减乘除 取余等运算 可直接实现
    int r = p.turnIntxToint(); // 若p在int范围内，可通过该函数转成int
}