/*
�㷨˼�룺���ã����̣��߾��ȼ�����
�㷨���Ӷȣ�o(n^2)
*/
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int L=110;
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
int main()
{
    string a,b;
    while(cin>>a>>b) cout<<div(a,b,1)<<endl;
    return 0;
}
