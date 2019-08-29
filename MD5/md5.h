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
	void make();  //����md5��
	byte message[16];	//���ɵ�128���ص���ϢժҪmd5	
private:
	void handle(const byte *input, size_t length);  //�������ⳤ�ȵ���Ϣ
	void CompressFunc(const byte block[64]);      //ѹ������
	void ToByte(const uint32 *input, byte *output, size_t length);   //����litte-endian�ķ�ʽ�洢������ת��Ϊlength�����ֽ�

	uint32 reg[4];	   //�Ĵ���ABCD
	uint32 count[2];	//��Ϣ�ĳ��� number of bits, modulo 2^64 (low-order word first) 
	byte buffer[64];	//512����һ�����Ϣ������
	static const byte PADDING[64];	//��Ϣ����仺����
	
	
};
