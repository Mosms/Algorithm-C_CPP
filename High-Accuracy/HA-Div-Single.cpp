
#include <iostream>
#include <algorithm>
using namespace std;
string div(string &a, int b, int &res)
{
    string r;
    int d = 0;
    if (a == "0")
        return a;
    for (int i = 0; i < a.size(); i++)
    {
        r += (d * 10 + a[i] - '0') / b + '0';
        d = (d * 10 + (a[i] - '0')) % b;
    }
    res = d;
    int p = 0;
    for (int i = 0; i < r.size(); i++)
        if (r[i] != '0' || i == r.size() - 1)
        {
            p = i;
            break;
        }
    return r.substr(p);
}
int main()
{
    string a;
    int b, res;
    while (cin >> a >> b)
    {
        cout << div(a, b, res) << endl;
        cout << res << endl;
    }
    return 0;
}
