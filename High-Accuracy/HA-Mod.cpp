/*
�㷨˼�룺����(a+b)%c=a%c+b%c��
�㷨���Ӷȣ�o(n)
*/
#include<iostream>
#include<algorithm>
using namespace std;
int mod(string a,int b)//�߾���a���Ե�����b
{
    int d=0;
    for(int i=0;i<a.size();i++) d=(d*10+(a[i]-'0'))%b;//�������
    return d;
}
int main()
{
    string a;
    int b;
    while(cin>>a>>b)
    {
        cout<<mod(a,b)<<endl;
    }
    return 0;
}
