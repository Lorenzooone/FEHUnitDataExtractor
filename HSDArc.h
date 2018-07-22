
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

const int Xor_Str[]  = {
  0x81, 0x00, 0x80, 0xA4, 0x5A, 0x16, 0x6F, 0x78,
  0x57, 0x81, 0x2D, 0xF7, 0xFC, 0x66, 0x0F, 0x27,
  0x75, 0x35, 0xB4, 0x34, 0x10, 0xEE, 0xA2, 0xDB,
  0xCC, 0xE3, 0x35, 0x99, 0x43, 0x48, 0xD2, 0xBB,
  0x93, 0xC1};
const int Xor_Str_Size = 34;

int read_data(char data[], int position, int size);
long long int read_data_long(char data[], long long int position, int size);
hsdarc_buffer get_elements(char data[]);
std::string GetStringXorred(long long int ptr, char data[], const int Xor[], int XorSize);
int read_data_Xorred(char data[], int position, int size, const int Xor[], int XorPos);