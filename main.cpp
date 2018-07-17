#include<iostream>
#include<fstream>
#include"HSDArc.h"
#include"charDataExtract.h"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 2)
        return -1;
    for(int i=1; i < argc; i++)
    {
        ifstream file (argv[i], ios::in|ios::binary|ios::ate);

        if (!file.is_open())
            break;
        int size=file.tellg();
        char* memblock = new char[size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();
        hsdarc_buffer buf=get_elements(memblock);
		for(int i=1; i<buf.ptr_list_length;)
        {
			unsigned char tmp = GetFirstChar(buf, i);
			if(tmp=='P')
				i=GetHero(buf, i);
			else
				i++;
        }
		delete(memblock);
    }
    return 0;
}