#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "BigInt.h"
#include "primer.h"
using namespace std;

//RabinMiller检测
bool RabinMiller(const BigInt& n)
{
	BigInt m,a,r;
	//找到令n-1=m*2^b的b和m,m为奇数
	unsigned int b=0,j;
	m=n-1;
	while(!m.IsOdd()){b++;m>>1;}
	//产生一个小于n-1的检测随机数a   2<=a<=n-2
	a.Randomsmall();
	r=PowerMode(a,m,n);
	//检测j=2至j<b轮
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
//产生一个素数
BigInt GeneratePrime()
{
	BigInt n;
	int i=0;
	while(i<5)
	{
		//产生一个待测素数
		SortPrime(n);
		i=0;
		//进行五轮RabinMiller测试
		for(;i<5;i++)
		{
			cout<<"进行第"<<i+1<<"轮RabinMiller测试"<<endl;
			if(!RabinMiller(n))
			{
				cout<<"测试失败!"<<endl;
				cout<<endl;
				break;
			}
		}
	}
	return n;
}
//求两个大数的最大公约数,采用辗转相除法
BigInt Gcd(const BigInt& m,const BigInt& n)
{
	if(n==0)
		return m;
	else
		return Gcd(n,m%n);
}
//用扩展欧几里德算法求乘法模逆
BigInt ExtendedGcd(const BigInt& a, const BigInt& b,BigInt& x, BigInt& y)
{
        BigInt t,d;   
        //如果一个操作数为零则无法进行除法运算
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
	cout<<"********随机产生p,q********"<<endl;
	cout<<endl;

	BigInt p=GeneratePrime();
	cout<<endl;
	cout<<"产生p:"<<endl;
	p.display();
	cout<<endl;

	BigInt q=GeneratePrime();
	cout<<endl;
	cout<<"产生q:"<<endl;
	q.display();
	cout<<endl;
	

	cout<<"********密钥生成********"<<endl;
	cout<<endl;
	cout<<"公钥e:"<<endl;
	BigInt t=(p-1)*(q-1);
	BigInt e,x,y,temp;
	while(1)
	{
		e.Random();
		//产生e使gcd(t,e)=1
		while(!(Gcd(e,t)==1))
			e.Random();
		temp=ExtendedGcd(e,t,x,y);
		temp=(e*x)%t;
		if(temp==1)
			break;
	}
	e.display();
	outfile<<"公钥e:"<<endl;
	outfile<<e;
	cout<<endl;
	
	cout<<"私钥d:"<<endl;	
	BigInt d=x;
	d.display();
	outfile<<"私钥d:"<<endl;
	outfile<<d;
	cout<<endl;

	cout<<"公钥n:"<<endl;
	BigInt n=p*q;
	n.display();
	outfile<<"公钥n:"<<endl;
	outfile<<n;
	cout<<endl;

	cout<<"********密钥检测********"<<endl;
	cout<<endl;
	cout<<"待检测的数据:"<<endl;	
	BigInt test;
	test.Random();
	test.display();
    outfile<<"原文:"<<endl;
	outfile<<test;
	cout<<endl;

	cout<<"加密后的密文:"<<endl;
	BigInt encrypt=PowerMode(test,d,n);
	encrypt.display();
    outfile<<"加密后的密文:"<<endl;
	outfile<<encrypt;
	cout<<endl;
	
	cout<<"解密后的明文:"<<endl;	
	BigInt decrypt=PowerMode(encrypt,e,n);
	decrypt.display();
    outfile<<"解密后的明文:"<<endl;
	outfile<<decrypt;
	cout<<endl;

	cout<<"结果存在RSA_final.txt中"<<endl;
}
