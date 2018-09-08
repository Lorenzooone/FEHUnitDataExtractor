#include<string>
#include"HSDArc.h"

using namespace std;

const int offset = 0x20; //HSDArc's header data

int read_data(char data[], int position, int size)
{
    int shifts=0;
    int read=0;
	for(int i=0; i<size; i++)
		read+=(((unsigned char)data[position+i])<<(i*8));
	return read;
}

long long int read_data_long(char data[], long long int position, int size)
{
    int shifts=0;
    long long int read=0;
	for(int i=0; i<size; i++)
		read+=(((unsigned char)data[position+i])<<(i*8));
	return read;
}

hsdarc_buffer get_elements(char data[])
{
    hsdarc_buffer buf;
    buf.archive_size=read_data(data, 0, 4);
    buf.ptr_list_offset=read_data(data, 4, 4) + offset;
    buf.ptr_list_length=read_data(data, 8, 4);
	buf.ptr_list = new long long int[buf.ptr_list_length];
	buf.data = data;
    for(int i=0; i<buf.ptr_list_length; i++)
    {
        buf.ptr_list[i]=read_data_long(data, buf.ptr_list_offset + (i*8), 8) + offset;
    }
	return buf;
}

string GetStringXorred(long long int ptr, char data[], const int Xor[], int XorSize)
{
	string String;
	for(int i=0; data[ptr+i]!=0; i++)
    {
		String += data[ptr+i] ^ Xor[i%XorSize];
	}
	return String;
}

int read_data_Xorred(char data[], int position, int size, const int Xor[], int XorPos)
{
    int read=0;
	for(int i=0; i<size; i++)
		read+=((((unsigned char)data[position+i])^Xor[XorPos+i])<<(i*8));
	return read;
}

long long int read_long_data_Xorred(char data[], int position, int size, const int Xor[], int XorPos)
{
    long long int read=0;
	for(int i=0; i<size; i++)
		read+=((((unsigned char)data[position+i])^Xor[XorPos+i])<<(i*8));
	return read;
}