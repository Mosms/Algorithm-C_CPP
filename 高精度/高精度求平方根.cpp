/*
设数的长度为n，则需二分log(2,10^n)次即n*log(2,10) 约等于n*3.3，由于数的长度为n，朴素高精度乘法复杂度为o(n^2)。故朴素算法求解高精度平方根复杂度为O(n^3)
当然，你也可以用FFT优化下高精度乘法。
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int L=2015;
string add(string a,string b)//只限两个非负整数相加
{
    string ans;
    int na[L]={0},nb[L]={0};
    int la=a.size(),lb=b.size();
    for(int i=0;i<la;i++) na[la-1-i]=a[i]-'0';
    for(int i=0;i<lb;i++) nb[lb-1-i]=b[i]-'0';
    int lmax=la>lb?la:lb;
    for(int i=0;i<lmax;i++) na[i]+=nb[i],na[i+1]+=na[i]/10,na[i]%=10;
    if(na[lmax]) lmax++;
    for(int i=lmax-1;i>=0;i--) ans+=na[i]+'0';
    return ans;
}
string sub(string a,string b)//只限大的非负整数减小的非负整数
{
    string ans;
    int na[L]={0},nb[L]={0};
    int la=a.size(),lb=b.size();
    for(int i=0;i<la;i++) na[la-1-i]=a[i]-'0';
    for(int i=0;i<lb;i++) nb[lb-1-i]=b[i]-'0';
    int lmax=la>lb?la:lb;
    for(int i=0;i<lmax;i++)
    {
        na[i]-=nb[i];
        if(na[i]<0) na[i]+=10,na[i+1]--;
    }
    while(!na[--lmax]&&lmax>0)  ;lmax++;
    for(int i=lmax-1;i>=0;i--) ans+=na[i]+'0';
    return ans;
}
string mul(string a,string b)//高精度乘法a,b,均为非负整数
{
    string s;
    int na[L],nb[L],nc[L],La=a.size(),Lb=b.size();//na存储被乘数，nb存储乘数，nc存储积
    fill(na,na+L,0);fill(nb,nb+L,0);fill(nc,nc+L,0);//将na,nb,nc都置为0
    for(int i=La-1;i>=0;i--) na[La-i]=a[i]-'0';//将字符串表示的大整形数转成i整形数组表示的大整形数
    for(int i=Lb-1;i>=0;i--) nb[Lb-i]=b[i]-'0';
    for(int i=1;i<=La;i++)
        for(int j=1;j<=Lb;j++)
        nc[i+j-1]+=na[i]*nb[j];//a的第i位乘以b的第j位为积的第i+j-1位（先不考虑进位）
    for(int i=1;i<=La+Lb;i++)
        nc[i+1]+=nc[i]/10,nc[i]%=10;//统一处理进位
    if(nc[La+Lb]) s+=nc[La+Lb]+'0';//判断第i+j位上的数字是不是0
    for(int i=La+Lb-1;i>=1;i--)
        s+=nc[i]+'0';//将整形数组转成字符串
    return s;
}
int sub(int *a,int *b,int La,int Lb)
{
    if(La<Lb) return -1;//如果a小于b，则返回-1
    if(La==Lb)
    {
        for(int i=La-1;i>=0;i--)
            if(a[i]>b[i]) break;
            else if(a[i]<b[i]) return -1;//如果a小于b，则返回-1

    }
    for(int i=0;i<La;i++)//高精度减法
    {
        a[i]-=b[i];
        if(a[i]<0) a[i]+=10,a[i+1]--;
    }
    for(int i=La-1;i>=0;i--)
        if(a[i]) return i+1;//返回差的位数
    return 0;//返回差的位数

}
string div(string n1,string n2,int nn)//n1,n2是字符串表示的被除数，除数,nn是选择返回商还是余数
{
    string s,v;//s存商,v存余数
     int a[L],b[L],r[L],La=n1.size(),Lb=n2.size(),i,tp=La;//a，b是整形数组表示被除数，除数，tp保存被除数的长度
     fill(a,a+L,0);fill(b,b+L,0);fill(r,r+L,0);//数组元素都置为0
     for(i=La-1;i>=0;i--) a[La-1-i]=n1[i]-'0';
     for(i=Lb-1;i>=0;i--) b[Lb-1-i]=n2[i]-'0';
     if(La<Lb || (La==Lb && n1<n2)) {
            //cout<<0<<endl;
     return n1;}//如果a<b,则商为0，余数为被除数
     int t=La-Lb;//除被数和除数的位数之差
     for(int i=La-1;i>=0;i--)//将除数扩大10^t倍
        if(i>=t) b[i]=b[i-t];
        else b[i]=0;
     Lb=La;
     for(int j=0;j<=t;j++)
     {
         int temp;
         while((temp=sub(a,b+j,La,Lb-j))>=0)//如果被除数比除数大继续减
         {
             La=temp;
             r[t-j]++;
         }
     }
     for(i=0;i<L-10;i++) r[i+1]+=r[i]/10,r[i]%=10;//统一处理进位
     while(!r[i]) i--;//将整形数组表示的商转化成字符串表示的
     while(i>=0) s+=r[i--]+'0';
     //cout<<s<<endl;
     i=tp;
     while(!a[i]) i--;//将整形数组表示的余数转化成字符串表示的</span>
     while(i>=0) v+=a[i--]+'0';
     if(v.empty()) v="0";
     //cout<<v<<endl;
     if(nn==1) return s;
     if(nn==2) return v;
}
bool cmp(string a,string b)
{
    if(a.size()<b.size()) return 1;//a小于等于b返回真
    if(a.size()==b.size()&&a<=b) return 1;
    return 0;
}
string BigInterSqrt(string n)
{
    string l="1",r=n,mid,ans;
    while(cmp(l,r))
    {
        mid=div(add(l,r),"2",1);
        if(cmp(mul(mid,mid),n)) ans=mid,l=add(mid,"1");
        else r=sub(mid,"1");
    }
    return ans;
}
string DeletePreZero(string s)
{
    int i;
    for(i=0;i<s.size();i++)
        if(s[i]!='0') break;
    return s.substr(i);
}
int main()
{
    string n;
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n;
        n=DeletePreZero(n);
        cout<<BigInterSqrt(n)<<endl;
    }
    return 0;
}

