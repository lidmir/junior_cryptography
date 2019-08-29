#include <string>
#include <fstream>
using std::string;
using std::ifstream;

typedef unsigned char byte;
typedef unsigned int uint32;

class MD5 {
public:
	MD5(const string &str);
	MD5(ifstream &in);
	void make();  //生成md5码
	byte message[16];	//生成的128比特的消息摘要md5	
private:
	void handle(const byte *input, size_t length);  //处理任意长度的消息
	void CompressFunc(const byte block[64]);      //压缩函数
	void ToByte(const uint32 *input, byte *output, size_t length);   //把以litte-endian的方式存储的输入转变为length长的字节

	uint32 reg[4];	   //寄存器ABCD
	uint32 count[2];	//消息的长度 number of bits, modulo 2^64 (low-order word first) 
	byte buffer[64];	//512比特一组的消息缓存区
	static const byte PADDING[64];	//消息的填充缓冲区
	
	
};
