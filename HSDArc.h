
struct hsdarc_buffer {
    int archive_size;
    int ptr_list_offset;
    int ptr_list_length;
    int _offset1;
    int _offset2;
    int _unknown1;
    long long int tag;
    char* data; /* archive_size - 0x20 - ptr_list_length * 0x8 */
    long long int* ptr_list;
};

struct XorArray
{
    const int* array;
	int size;
};

int read_data(char data[], int position, int size);
long long int read_data_long(char data[], long long int position, int size);
hsdarc_buffer get_elements(char data[]);
std::string GetStringXorred(long long int ptr, char data[], const int Xor[], int XorSize);