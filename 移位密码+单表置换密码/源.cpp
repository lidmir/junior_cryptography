#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
using namespace std;
//��λ�������
void encrypt()      
{	
	getchar();
	char *str=new char;
	cout<<"������Ҫ���ܵ����ݣ�";
	gets(str);
	int key;
	cout<<"������Ҫʹ�õ���Կ�����֣���";
	cin>>key;
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]>='a'&&str[i]<='z')
			str[i]=(str[i]+key-'a')%26+'a';
		else if(str[i]>='A'&&str[i]<='Z')
			str[i]=(str[i]+key-'A')%26+'A';
	}
	cout<<"���ģ�"<<str<<endl;
}
//��λ�������
void decode()        
{
	getchar();
	char *str=new char;
	cout<<"���������ģ�";
	gets(str);
	int key;
	cout<<"��������Կ��";
	cin>>key;
	cout<<"���ģ�";
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]>='a'&&str[i]<='z')
			str[i]=(str[i]-'a'+26-key)%26+'a';
		else if(str[i]>='A'&&str[i]<='Z')
			str[i]=(str[i]-'A'+26-key)%26+'A';
	}
	cout<<str<<endl;
}
//�������ƽ���λ����
void DecodeWithoutKey()        
{
	getchar();
	char *str=new char;
	cout<<"���������ģ�";
	gets(str);
	char *str1=new char;
	strcpy(str1,str);
	cout<<"���ܵ����ļ���Կ������£�"<<endl;
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
		cout<<"No."<<key<<"��"<<str1<<"    key:";
		cout<<key++<<endl;
	}
}
//�����û���������ĸ�Ƿ������û�����
bool CheckIfLetterIn(char key[],char letter,int count)   
{
	for(int j=0;j<=count;j++)
		if(key[j]==letter) return true;
	return false;
}
//�����û�����õ��û���
void GetTable(char key[26])      
{
	char *key1=new char;
	cout<<"��������Կ��";
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
	if(count<25)       //��û��
		for(int k=0;k<26&&count<26;k++)
			if(!CheckIfLetterIn(key,'A'+k,count))
				key[count++]='A'+k;
}
//����û���
void OutputTable(char*key)
{
	cout<<"�û���"<<endl;
	for(int i=0;i<26;i++)
		cout<<char('A'+i)<<"|";
	cout<<endl;
	for(int i=0;i<26;i++)
		cout<<key[i]<<"|";
}
//�����û��������
void UseTable()     
{
	getchar();
	char key[26];
	char *str=new char;
	cout<<"������Ҫ���ܵ����ݣ�";
	gets(str);
	GetTable(key);
	for(int i=0;str[i]!='\0';i++)
	{
		if(str[i]>='a'&&str[i]<='z')
			str[i]-=32;
		if(str[i]>='A'&&str[i]<='Z')
			str[i]=key[str[i]-'A'];	
	}
	cout<<"���ģ�"<<str<<endl;
}
//�����û��������
void DecodeTable()     
{
	getchar();
	char key1[26];
	char *str=new char;
	cout<<"���������ģ�";
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
	cout<<"���ģ�"<<str<<endl;
}
//ͳ���ļ������ݵ���ĸƵ��
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
	cout<<"�ı��е���ĸƵ�ʣ�"<<endl;
	for(int i=0;i<26;i++)
	{
		rate[i]=rate[i]/count*100;
		cout<<char('A'+i)<<":"<<rate[i]<<endl;
	}
	file1.close();
}
void main()
{
	cout<<"���ܱ�(��������1-5����,���������ַ��˳�����)��"<<endl<<"1��ʹ����λ�������"<<endl;
	cout<<"2��ʹ����Կ������λ����"<<endl<<"3�������Է�����λ������ܻ�õ�����"<<endl;
	cout<<"4��ʹ���û��������"<<endl<<"5��ʹ����Կ�����û�����"<<endl<<"---------------------"<<endl;
	int choose;
	do{
		cout<<"��ѡ��Ҫ���еĹ��ܣ�";
		cin>>choose;
		if(cin.fail())
			choose=0;
		else
		{
			switch(choose)
			{
			case 1:
				cout<<"----ʹ����λ�������----"<<endl;
				encrypt();
				cout<<"------------------------"<<endl;
				break;
			case 2:
				cout<<"----ʹ����Կ������λ����----"<<endl;
				decode();
				cout<<"----------------------------"<<endl;
				break;
			case 3:
				cout<<"----�����Է�����λ������ܻ�õ�����----"<<endl;
				DecodeWithoutKey();
				cout<<"----------------------------------------"<<endl;
				break;
			case 4:
				cout<<"----ʹ���û��������----"<<endl;
				UseTable();
				cout<<"------------------------"<<endl;
				break;
			case 5:
				cout<<"----ʹ����Կ�����û�����----"<<endl;
				DecodeTable();
				cout<<"----------------------------"<<endl;
				break;
			}
		}
	}while(choose>=1&&choose<=6);
	
	//ͳ���ļ�E:\test1.txt�е����ݵ���ĸƵ��
	//CheckRate();
}