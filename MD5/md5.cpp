#include"md5.h"
using namespace std;

//常数表T
const unsigned int T[64]=
{
	0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
	0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
	0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
	0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
	0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
	0x289b7ec6,0xeaa127fa,0xd4ef3085,0x4881d05, 0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
	0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
	0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
};
//压缩表每步左循环移位的位数
const int S[]=
{
	7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,	
	5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
	4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
	6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};
// 左移n位的函数
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
//F\G\H\I函数
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
//运用到F\G\H\I的轮函数
#define FF(a, b, c, d, x, s, t) { \
	(a) += F ((b), (c), (d)) + x + t; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define GG(a, b, c, d, x, s, t) { \
	(a) += G ((b), (c), (d)) + x + t; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define HH(a, b, c, d, x, s, t) { \
	(a) += H ((b), (c), (d)) + x + t; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}
#define II(a, b, c, d, x, s, t) { \
	(a) += I ((b), (c), (d)) + x + t; \
	(a) = ROTATE_LEFT ((a), (s)); \
	(a) += (b); \
}

const byte MD5::PADDING[64] = { 0x80 };

//构造函数
MD5::MD5(const string &str)   //字符串的方式读取消息
{
	count[0] = count[1] = 0;
	reg[0] = 0x67452301;   //A
	reg[1] = 0xefcdab89;   //B
	reg[2] = 0x98badcfe;   //C
	reg[3] = 0x10325476;   //D
	handle((const byte*)str.c_str(), str.length());
}
MD5::MD5(ifstream &in)      //打开文件的方式读取消息
{
	count[0] = count[1] = 0;
	reg[0] = 0x67452301;   //A
	reg[1] = 0xefcdab89;   //B
	reg[2] = 0x98badcfe;   //C
	reg[3] = 0x10325476;   //D
	if (!in)
		return;
	std::streamsize length;
	char buffer1[1024];
	while (!in.eof()) 
	{
		in.read(buffer1,1024);   //一次从文件中读入1024长度的消息到缓冲区
		length = in.gcount();
		if (length > 0)
			handle((const byte*)buffer1, length);
	}
	in.close();
}

//处理任意长度的消息
void MD5::handle(const byte *input, size_t length) 
{
	uint32 i, index, partLen;	
	//消息长度  /8  mod64
	index = (uint32)((count[0] >> 3) & 0x3f);
	//更新消息的长度
	if((count[0] += ((uint32)length << 3)) < ((uint32)length << 3))    //*8
		count[1]++;
	count[1] += ((uint32)length >> 29);
	partLen = 64 - index;   //要填充的长度

	if(length >= partLen)    //对于每个512比特的分组的处理  其中i为已处理完的长度 length为已填充的长度
	{
		memcpy(&buffer[index], input, partLen);
		CompressFunc(buffer);
		for (i = partLen; i + 63 < length; i += 64)
			CompressFunc(&input[i]);
		index = 0;
	} 
	else {i = 0;}       //有一组未满512比特，进行填充

	memcpy(&buffer[index], &input[i], length-i);
}

//MD5的压缩函数
void MD5::CompressFunc(const byte block[64]) 
{
	uint32 a = reg[0], b = reg[1], c = reg[2], d = reg[3], x[16], temp;
	for(size_t i=0, j=0; j<64; i++, j+=4) //把缓冲区64位（512比特）的消息转变为16个字（32比特/字）
	{	
		x[i] = ((uint32)block[j]) | (((uint32)block[j+1]) << 8) |
			(((uint32)block[j+2]) << 16) | (((uint32)block[j+3]) << 24);
	}
	for(int i=0;i<64;i++)    //压缩函数的4轮处理过程，每轮16步迭代运算
	{
		if(i<16){FF(a,b,c,d,x[i],S[i],T[i]);}   
		else if(i<32){GG(a,b,c,d,x[((i-16)*5+1)%16],S[i],T[i]);}
		else if(i<48){HH(a,b,c,d,x[((i-32)*3+5)%16],S[i],T[i]);}
		else{II(a,b,c,d,x[((i-48)*7)%16],S[i],T[i]);}
		temp=b;           //右循环一个字：交换寄存器中的值a→b,b→c,c→d,d→a
		b=a;
		a=d;
		d=c;
		c=temp;
	}      
	reg[0] += a;  //输入与输出的CVq相加
	reg[1] += b;
	reg[2] += c;
	reg[3] += d;
}


//把以litte-endian的方式存储的（32比特/字）的输入转变为length长的字节,即length*8比特
void MD5::ToByte(const uint32 *input, byte *output, size_t length) 
{
	for(size_t i=0, j=0; j<length; i++, j+=4) {
		output[j]= (byte)(input[i] & 0xff);
		output[j+1] = (byte)((input[i] >> 8) & 0xff);
		output[j+2] = (byte)((input[i] >> 16) & 0xff);
		output[j+3] = (byte)((input[i] >> 24) & 0xff);
	}
}
//生成md5码，并且以十六进制输出得到的md5码
void MD5::make() 
{
	byte bits[8];
	uint32 oldState[4],oldCount[2],index, padLen;
	memcpy(oldState, reg, 16); //保存现场
	memcpy(oldCount, count, 8);	

	//附加消息 以litte-endian的方式存储的 32比特*2个字的count->8字节bits->8*8=64比特
	ToByte(count, bits, 8);      

	//对消息进行填充mod 448（2^56）
	index = (uint32)((count[0] >> 3) & 0x3f);   //消息的长度 /8 mod64
	padLen = (index < 56) ? (56 - index) : (56 + 64 - index);    //要填充的长度
	handle(PADDING, padLen);   //填充
	
	//对附加消息的长度 进行填充
	handle(bits, 8);
	
	//把寄存器的内容存进digest中  
	//以litte-endian的方式存储的32比特*4个字的寄存器->16字节的message->8*16=128比特的message
	ToByte(reg, message, 16); 
	memcpy(reg, oldState, 16); //还原现场
	memcpy(count, oldCount, 8);
	
	//吧结果打印在屏幕上
	for(int i=0;i<16;i++)
		 printf("%02x",message[i]);
}
