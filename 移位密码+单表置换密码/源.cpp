#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
//移位密码加密
void encrypt()      
{	
	getchar();
	char *str=new char;
	cout<<"请输入要加密的内容：";
	gets(str);
	int key;
	cout<<"请输入要使用的密钥（数字）：";
	cin>>key;
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]>='a'&&str[i]<='z')
			str[i]=(str[i]+key-'a')%26+'a';
		else if(str[i]>='A'&&str[i]<='Z')
			str[i]=(str[i]+key-'A')%26+'A';
	}
	cout<<"密文："<<str<<endl;
}
//移位密码解密
void decode()        
{
	getchar();
	char *str=new char;
	cout<<"请输入密文：";
	gets(str);
	int key;
	cout<<"请输入密钥：";
	cin>>key;
	cout<<"明文：";
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]>='a'&&str[i]<='z')
			str[i]=(str[i]-'a'+26-key)%26+'a';
		else if(str[i]>='A'&&str[i]<='Z')
			str[i]=(str[i]-'A'+26-key)%26+'A';
	}
	cout<<str<<endl;
}
//无密码破解移位密码
void DecodeWithoutKey()        
{
	getchar();
	char *str=new char;
	cout<<"请输入密文：";
	gets(str);
	char *str1=new char;
	strcpy(str1,str);
	cout<<"可能的明文及密钥穷举如下："<<endl;
	int key=1;
	while(key<26)
	{
		for(int i=0;str[i]!='\0';i++)
		{
			if(str[i]>='a'&&str[i]<='z')
				str1[i]=(str[i]-'a'+26-key)%26+'a';
			else if(str[i]>='A'&&str[i]<='Z')
				str1[i]=(str[i]-'A'+26-key)%26+'A';
		}
		cout<<"No."<<key<<"："<<str1<<"    key:";
		cout<<key++<<endl;
	}
}
//单表置换密码检查字母是否已在置换表中
bool CheckIfLetterIn(char key[],char letter,int count)   
{
	for(int j=0;j<=count;j++)
		if(key[j]==letter) return true;
	return false;
}
//单表置换密码得到置换表
void GetTable(char key[26])      
{
	char *key1=new char;
	cout<<"请输入密钥：";
	gets(key1);
	int count=0;
	for(int i=0;key1[i]!='\0'&&count<26;i++)
	{
		if(key1[i]>='a'&&key1[i]<='z')
			key1[i]-=32;
		if(key1[i]>='A'&&key1[i]<='Z')
		{
			if(!CheckIfLetterIn(key,key1[i],count))
				key[count++]=key1[i];	
		}
	}
	if(count<25)       //表没满
		for(int k=0;k<26&&count<26;k++)
			if(!CheckIfLetterIn(key,'A'+k,count))
				key[count++]='A'+k;
}
//输出置换表
void OutputTable(char*key)
{
	cout<<"置换表："<<endl;
	for(int i=0;i<26;i++)
		cout<<char('A'+i)<<"|";
	cout<<endl;
	for(int i=0;i<26;i++)
		cout<<key[i]<<"|";
}
//单表置换密码加密
void UseTable()     
{
	getchar();
	char key[26];
	char *str=new char;
	cout<<"请输入要加密的内容：";
	gets(str);
	GetTable(key);
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]>='a'&&str[i]<='z')
			str[i]-=32;
		if(str[i]>='A'&&str[i]<='Z')
			str[i]=key[str[i]-'A'];	
	}
	cout<<"密文："<<str<<endl;
}
//单表置换密码解密
void DecodeTable()     
{
	getchar();
	char key1[26];
	char *str=new char;
	cout<<"请输入密文：";
	gets(str);
	GetTable(key1);
	char key2[26];
	for(int i=0;i<26;i++)
		key2[key1[i]-'A']='A'+i;
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]>='a'&&str[i]<='z')
			str[i]-=32;
		if(str[i]>='A'&&str[i]<='Z')
			str[i]=key2[str[i]-'A'];	
	}
	cout<<"明文："<<str<<endl;
}
//统计文件中内容的字母频率
void CheckRate()       
{
	float rate[26];
	for(int i=0;i<26;i++)
		rate[i]=0;
	int count=0;
	ifstream file1;
	file1.open("E:\\test1.txt");
	char temp;
	int j=0;
	for(int i=1;!file1.eof();i++)
	{
		file1>>temp;
		if(temp>='A'&&temp<='Z')
		{
			j=temp-'A';
			rate[j]++;
			count++;
		}
	}
	cout<<"文本中的字母频率："<<endl;
	for(int i=0;i<26;i++)
	{
		rate[i]=rate[i]/count*100;
		cout<<char('A'+i)<<":"<<rate[i]<<endl;
	}
	file1.close();
}
void main()
{
	cout<<"功能表(输入数字1-5进入,输入其他字符退出程序)："<<endl<<"1、使用移位密码加密"<<endl;
	cout<<"2、使用密钥解密移位密码"<<endl<<"3、攻击对方用移位密码加密获得的密文"<<endl;
	cout<<"4、使用置换密码加密"<<endl<<"5、使用密钥解密置换密码"<<endl<<"---------------------"<<endl;
	int choose;
	do{
		cout<<"请选择要进行的功能：";
		cin>>choose;
		if(cin.fail())
			choose=0;
		else
		{
			switch(choose)
			{
			case 1:
				cout<<"----使用移位密码加密----"<<endl;
				encrypt();
				cout<<"------------------------"<<endl;
				break;
			case 2:
				cout<<"----使用密钥解密移位密码----"<<endl;
				decode();
				cout<<"----------------------------"<<endl;
				break;
			case 3:
				cout<<"----攻击对方用移位密码加密获得的密文----"<<endl;
				DecodeWithoutKey();
				cout<<"----------------------------------------"<<endl;
				break;
			case 4:
				cout<<"----使用置换密码加密----"<<endl;
				UseTable();
				cout<<"------------------------"<<endl;
				break;
			case 5:
				cout<<"----使用密钥解密置换密码----"<<endl;
				DecodeTable();
				cout<<"----------------------------"<<endl;
				break;
			}
		}
	}while(choose>=1&&choose<=6);
	
	//统计文件E:\test1.txt中的内容的字母频率
	//CheckRate();
}