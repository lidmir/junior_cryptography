#include"md5.h"
using namespace std;

//������T
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
//ѹ����ÿ����ѭ����λ��λ��
const int S[]=
{
	7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,	
	5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
	4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
	6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
};
// ����nλ�ĺ���
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))
//F\G\H\I����
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
//���õ�F\G\H\I���ֺ���
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

//���캯��
MD5::MD5(const string &str)   //�ַ����ķ�ʽ��ȡ��Ϣ
{
	count[0] = count[1] = 0;
	reg[0] = 0x67452301;   //A
	reg[1] = 0xefcdab89;   //B
	reg[2] = 0x98badcfe;   //C
	reg[3] = 0x10325476;   //D
	handle((const byte*)str.c_str(), str.length());
}
MD5::MD5(ifstream &in)      //���ļ��ķ�ʽ��ȡ��Ϣ
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
		in.read(buffer1,1024);   //һ�δ��ļ��ж���1024���ȵ���Ϣ��������
		length = in.gcount();
		if (length > 0)
			handle((const byte*)buffer1, length);
	}
	in.close();
}

//�������ⳤ�ȵ���Ϣ
void MD5::handle(const byte *input, size_t length) 
{
	uint32 i, index, partLen;	
	//��Ϣ����  /8  mod64
	index = (uint32)((count[0] >> 3) & 0x3f);
	//������Ϣ�ĳ���
	if((count[0] += ((uint32)length << 3)) < ((uint32)length << 3))    //*8
		count[1]++;
	count[1] += ((uint32)length >> 29);
	partLen = 64 - index;   //Ҫ���ĳ���

	if(length >= partLen)    //����ÿ��512���صķ���Ĵ���  ����iΪ�Ѵ�����ĳ��� lengthΪ�����ĳ���
	{
		memcpy(&buffer[index], input, partLen);
		CompressFunc(buffer);
		for (i = partLen; i + 63 < length; i += 64)
			CompressFunc(&input[i]);
		index = 0;
	} 
	else {i = 0;}       //��һ��δ��512���أ��������

	memcpy(&buffer[index], &input[i], length-i);
}

//MD5��ѹ������
void MD5::CompressFunc(const byte block[64]) 
{
	uint32 a = reg[0], b = reg[1], c = reg[2], d = reg[3], x[16], temp;
	for(size_t i=0, j=0; j<64; i++, j+=4) //�ѻ�����64λ��512���أ�����Ϣת��Ϊ16���֣�32����/�֣�
	{	
		x[i] = ((uint32)block[j]) | (((uint32)block[j+1]) << 8) |
			(((uint32)block[j+2]) << 16) | (((uint32)block[j+3]) << 24);
	}
	for(int i=0;i<64;i++)    //ѹ��������4�ִ�����̣�ÿ��16����������
	{
		if(i<16){FF(a,b,c,d,x[i],S[i],T[i]);}   
		else if(i<32){GG(a,b,c,d,x[((i-16)*5+1)%16],S[i],T[i]);}
		else if(i<48){HH(a,b,c,d,x[((i-32)*3+5)%16],S[i],T[i]);}
		else{II(a,b,c,d,x[((i-48)*7)%16],S[i],T[i]);}
		temp=b;           //��ѭ��һ���֣������Ĵ����е�ֵa��b,b��c,c��d,d��a
		b=a;
		a=d;
		d=c;
		c=temp;
	}      
	reg[0] += a;  //�����������CVq���
	reg[1] += b;
	reg[2] += c;
	reg[3] += d;
}


//����litte-endian�ķ�ʽ�洢�ģ�32����/�֣�������ת��Ϊlength�����ֽ�,��length*8����
void MD5::ToByte(const uint32 *input, byte *output, size_t length) 
{
	for(size_t i=0, j=0; j<length; i++, j+=4) {
		output[j]= (byte)(input[i] & 0xff);
		output[j+1] = (byte)((input[i] >> 8) & 0xff);
		output[j+2] = (byte)((input[i] >> 16) & 0xff);
		output[j+3] = (byte)((input[i] >> 24) & 0xff);
	}
}
//����md5�룬������ʮ����������õ���md5��
void MD5::make() 
{
	byte bits[8];
	uint32 oldState[4],oldCount[2],index, padLen;
	memcpy(oldState, reg, 16); //�����ֳ�
	memcpy(oldCount, count, 8);	

	//������Ϣ ��litte-endian�ķ�ʽ�洢�� 32����*2���ֵ�count->8�ֽ�bits->8*8=64����
	ToByte(count, bits, 8);      

	//����Ϣ�������mod 448��2^56��
	index = (uint32)((count[0] >> 3) & 0x3f);   //��Ϣ�ĳ��� /8 mod64
	padLen = (index < 56) ? (56 - index) : (56 + 64 - index);    //Ҫ���ĳ���
	handle(PADDING, padLen);   //���
	
	//�Ը�����Ϣ�ĳ��� �������
	handle(bits, 8);
	
	//�ѼĴ��������ݴ��digest��  
	//��litte-endian�ķ�ʽ�洢��32����*4���ֵļĴ���->16�ֽڵ�message->8*16=128���ص�message
	ToByte(reg, message, 16); 
	memcpy(reg, oldState, 16); //��ԭ�ֳ�
	memcpy(count, oldCount, 8);
	
	//�ɽ����ӡ����Ļ��
	for(int i=0;i<16;i++)
		 printf("%02x",message[i]);
}
