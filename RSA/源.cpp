#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "BigInt.h"
#include "primer.h"
using namespace std;

//RabinMiller���
bool RabinMiller(const BigInt& n)
{
	BigInt m,a,r;
	//�ҵ���n-1=m*2^b��b��m,mΪ����
	unsigned int b=0,j;
	m=n-1;
	while(!m.IsOdd()){b++;m>>1;}
	//����һ��С��n-1�ļ�������a   2<=a<=n-2
	a.Randomsmall();
	r=PowerMode(a,m,n);
	//���j=2��j<b��
	if((!(r==1))&&(!(r==(n-1))))
	{
		j=1;
		while((j<=b-1)&&(!(r==(n-1))))
		{
			r=(r*r)%n;
			if(r==1)
				return false;
			j++;
		}
		if(!(r==(n-1)))
			return false;
	}
	return true;
}
//����һ������
BigInt GeneratePrime()
{
	BigInt n;
	int i=0;
	while(i<5)
	{
		//����һ����������
		SortPrime(n);
		i=0;
		//��������RabinMiller����
		for(;i<5;i++)
		{
			cout<<"���е�"<<i+1<<"��RabinMiller����"<<endl;
			if(!RabinMiller(n))
			{
				cout<<"����ʧ��!"<<endl;
				cout<<endl;
				break;
			}
		}
	}
	return n;
}
//���������������Լ��,����շת�����
BigInt Gcd(const BigInt& m,const BigInt& n)
{
	if(n==0)
		return m;
	else
		return Gcd(n,m%n);
}
//����չŷ������㷨��˷�ģ��
BigInt ExtendedGcd(const BigInt& a, const BigInt& b,BigInt& x, BigInt& y)
{
        BigInt t,d;   
        //���һ��������Ϊ�����޷����г�������
		if(b==0)   
		{
			x=1;
			y=0;
			return a;
		} 
        d=ExtendedGcd(b,a%b,x,y);   
        t=x;   
        x=y;   
        y=t-((a/b)*y);   
        return d;   
}
void main()
{
	srand((unsigned)time(NULL));
	ofstream outfile("RSA_final.txt");
	cout<<"********�������p,q********"<<endl;
	cout<<endl;

	BigInt p=GeneratePrime();
	cout<<endl;
	cout<<"����p:"<<endl;
	p.display();
	cout<<endl;

	BigInt q=GeneratePrime();
	cout<<endl;
	cout<<"����q:"<<endl;
	q.display();
	cout<<endl;
	

	cout<<"********��Կ����********"<<endl;
	cout<<endl;
	cout<<"��Կe:"<<endl;
	BigInt t=(p-1)*(q-1);
	BigInt e,x,y,temp;
	while(1)
	{
		e.Random();
		//����eʹgcd(t,e)=1
		while(!(Gcd(e,t)==1))
			e.Random();
		temp=ExtendedGcd(e,t,x,y);
		temp=(e*x)%t;
		if(temp==1)
			break;
	}
	e.display();
	outfile<<"��Կe:"<<endl;
	outfile<<e;
	cout<<endl;
	
	cout<<"˽Կd:"<<endl;	
	BigInt d=x;
	d.display();
	outfile<<"˽Կd:"<<endl;
	outfile<<d;
	cout<<endl;

	cout<<"��Կn:"<<endl;
	BigInt n=p*q;
	n.display();
	outfile<<"��Կn:"<<endl;
	outfile<<n;
	cout<<endl;

	cout<<"********��Կ���********"<<endl;
	cout<<endl;
	cout<<"����������:"<<endl;	
	BigInt test;
	test.Random();
	test.display();
    outfile<<"ԭ��:"<<endl;
	outfile<<test;
	cout<<endl;

	cout<<"���ܺ������:"<<endl;
	BigInt encrypt=PowerMode(test,d,n);
	encrypt.display();
    outfile<<"���ܺ������:"<<endl;
	outfile<<encrypt;
	cout<<endl;
	
	cout<<"���ܺ������:"<<endl;	
	BigInt decrypt=PowerMode(encrypt,e,n);
	decrypt.display();
    outfile<<"���ܺ������:"<<endl;
	outfile<<decrypt;
	cout<<endl;

	cout<<"�������RSA_final.txt��"<<endl;
}
