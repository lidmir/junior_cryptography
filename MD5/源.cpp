#include"md5.h"
#include <iostream>
using namespace std;
//测试数据
struct md5_test_statics
{
	int num;
    char *msg;
    unsigned char hash[16];
}tests[] = {
    { 0,"",
      { 0xd4, 0x1d, 0x8c, 0xd9, 0x8f, 0x00, 0xb2, 0x04, 
        0xe9, 0x80, 0x09, 0x98, 0xec, 0xf8, 0x42, 0x7e } },
    { 1,"a",
      {0x0c, 0xc1, 0x75, 0xb9, 0xc0, 0xf1, 0xb6, 0xa8, 
       0x31, 0xc3, 0x99, 0xe2, 0x69, 0x77, 0x26, 0x61 } },
    { 2,"abc",
      { 0x90, 0x01, 0x50, 0x98, 0x3c, 0xd2, 0x4f, 0xb0, 
        0xd6, 0x96, 0x3f, 0x7d, 0x28, 0xe1, 0x7f, 0x72 } },
    { 3,"message digest", 
      { 0xf9, 0x6b, 0x69, 0x7d, 0x7c, 0xb7, 0x93, 0x8d, 
        0x52, 0x5a, 0x2f, 0x31, 0xaa, 0xf1, 0x61, 0xd0 } }, 
    { 4,"abcdefghijklmnopqrstuvwxyz",
      { 0xc3, 0xfc, 0xd3, 0xd7, 0x61, 0x92, 0xe4, 0x00, 
        0x7d, 0xfb, 0x49, 0x6c, 0xca, 0x67, 0xe1, 0x3b } },
    { 5,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
      { 0xd1, 0x74, 0xab, 0x98, 0xd2, 0x77, 0xd9, 0xf5, 
        0xa5, 0x61, 0x1c, 0x2c, 0x9f, 0x41, 0x9d, 0x9f } },
    { 6,"12345678901234567890123456789012345678901234567890123456789012345678901234567890",
      { 0x57, 0xed, 0xf4, 0xa2, 0x2b, 0xe3, 0xc9, 0x55, 
        0xac, 0x49, 0xda, 0x2e, 0x21, 0x07, 0xb6, 0x7a } },
};
int statistics(char out[16],char out1[16])  //雪崩效应中统计改变位数的函数
{
	int str[128],str1[128];
	for(int i=0;i<16;i++)
	{
		for(int j=0;j<8;j++)
		{
			str[i*8+j]=(out[i]>>(7-j))&1;
			str1[i*8+j]=(out1[i]>>(7-j))&1;
		}
	}
	for(int i=0;i<128;i++)
		cout<<str1[i];
	cout<<endl;
	int count=0;
	for(int i=0;i<128;i++)
	{
		if(str[i]^str1[i])
			count++;
	}
	return count;
}
void main() 
{
	cout<<"从测试数据中读消息："<<endl<<"从请输入要测试数据的序号（0-6）：";
	int num;
	cin>>num;
	if(0<=num<6)
	{
		MD5 md5(tests[num].msg);
		cout << "MD5(\"" << tests[num].msg << "\") ： " <<endl;
		md5.make() ;
		cout<< endl;
	}
	else
		cout<<"测试数据编号输入错误"<<endl;
	
	/*
	//雪崩测试
	float avg=0;
    MD5 md("how are you today");
	md.make() ;
	cout<< endl;
	char out[16];
	memcpy(out,md.message,16);
	for(int i=0;i<8;i++)
	{
		MD5 md1(ifstream("D:\\test.txt"));
		md1.make();
		cout<<endl;
		char out1[16];
		memcpy(out1,md1.message,16);
		int cc=statistics(out,out1);
		cout<<cc<<endl;
		avg+=cc;	
		system("pause");
	}
	avg=avg/8;
	cout<<avg<<endl;
	system("pause");
	*/
}
