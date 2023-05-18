/*
�����ĳ���Ϊn���������log(2,10^n)�μ�n*log(2,10) Լ����n*3.3���������ĳ���Ϊn�����ظ߾��ȳ˷����Ӷ�Ϊo(n^2)���������㷨���߾���ƽ�������Ӷ�ΪO(n^3)
��Ȼ����Ҳ������FFT�Ż��¸߾��ȳ˷���
*/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int L=2015;
string add(string a,string b)//ֻ�������Ǹ��������
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
string sub(string a,string b)//ֻ�޴�ķǸ�������С�ķǸ�����
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
string mul(string a,string b)//�߾��ȳ˷�a,b,��Ϊ�Ǹ�����
{
    string s;
    int na[L],nb[L],nc[L],La=a.size(),Lb=b.size();//na�洢��������nb�洢������nc�洢��
    fill(na,na+L,0);fill(nb,nb+L,0);fill(nc,nc+L,0);//��na,nb,nc����Ϊ0
    for(int i=La-1;i>=0;i--) na[La-i]=a[i]-'0';//���ַ�����ʾ�Ĵ�������ת��i���������ʾ�Ĵ�������
    for(int i=Lb-1;i>=0;i--) nb[Lb-i]=b[i]-'0';
    for(int i=1;i<=La;i++)
        for(int j=1;j<=Lb;j++)
        nc[i+j-1]+=na[i]*nb[j];//a�ĵ�iλ����b�ĵ�jλΪ���ĵ�i+j-1λ���Ȳ����ǽ�λ��
    for(int i=1;i<=La+Lb;i++)
        nc[i+1]+=nc[i]/10,nc[i]%=10;//ͳһ�����λ
    if(nc[La+Lb]) s+=nc[La+Lb]+'0';//�жϵ�i+jλ�ϵ������ǲ���0
    for(int i=La+Lb-1;i>=1;i--)
        s+=nc[i]+'0';//����������ת���ַ���
    return s;
}
int sub(int *a,int *b,int La,int Lb)
{
    if(La<Lb) return -1;//���aС��b���򷵻�-1
    if(La==Lb)
    {
        for(int i=La-1;i>=0;i--)
            if(a[i]>b[i]) break;
            else if(a[i]<b[i]) return -1;//���aС��b���򷵻�-1

    }
    for(int i=0;i<La;i++)//�߾��ȼ���
    {
        a[i]-=b[i];
        if(a[i]<0) a[i]+=10,a[i+1]--;
    }
    for(int i=La-1;i>=0;i--)
        if(a[i]) return i+1;//���ز��λ��
    return 0;//���ز��λ��

}
string div(string n1,string n2,int nn)//n1,n2���ַ�����ʾ�ı�����������,nn��ѡ�񷵻��̻�������
{
    string s,v;//s����,v������
     int a[L],b[L],r[L],La=n1.size(),Lb=n2.size(),i,tp=La;//a��b�����������ʾ��������������tp���汻�����ĳ���
     fill(a,a+L,0);fill(b,b+L,0);fill(r,r+L,0);//����Ԫ�ض���Ϊ0
     for(i=La-1;i>=0;i--) a[La-1-i]=n1[i]-'0';
     for(i=Lb-1;i>=0;i--) b[Lb-1-i]=n2[i]-'0';
     if(La<Lb || (La==Lb && n1<n2)) {
            //cout<<0<<endl;
     return n1;}//���a<b,����Ϊ0������Ϊ������
     int t=La-Lb;//�������ͳ�����λ��֮��
     for(int i=La-1;i>=0;i--)//����������10^t��
        if(i>=t) b[i]=b[i-t];
        else b[i]=0;
     Lb=La;
     for(int j=0;j<=t;j++)
     {
         int temp;
         while((temp=sub(a,b+j,La,Lb-j))>=0)//����������ȳ����������
         {
             La=temp;
             r[t-j]++;
         }
     }
     for(i=0;i<L-10;i++) r[i+1]+=r[i]/10,r[i]%=10;//ͳһ�����λ
     while(!r[i]) i--;//�����������ʾ����ת�����ַ�����ʾ��
     while(i>=0) s+=r[i--]+'0';
     //cout<<s<<endl;
     i=tp;
     while(!a[i]) i--;//�����������ʾ������ת�����ַ�����ʾ��</span>
     while(i>=0) v+=a[i--]+'0';
     if(v.empty()) v="0";
     //cout<<v<<endl;
     if(nn==1) return s;
     if(nn==2) return v;
}
bool cmp(string a,string b)
{
    if(a.size()<b.size()) return 1;//aС�ڵ���b������
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

