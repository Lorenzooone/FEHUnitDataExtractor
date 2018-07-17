#include<iostream>
#include<fstream>
#include"HSDArc.h"
#include"charDataExtract.h"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <Windows.h>
#endif

using namespace std;

int main(int argc, char *argv[])
{
    if(argc < 2)
        return -1;
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        SetConsoleOutputCP(CP_UTF8);
    #endif
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