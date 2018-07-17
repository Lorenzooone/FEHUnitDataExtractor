#include<iostream>
#include"HSDArc.h"
#include"charDataExtract.h"
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #include <Windows.h>
#endif
using namespace std;

//Const declarations
const int Xor_Str[]  = {
  0x81, 0x00, 0x80, 0xA4, 0x5A, 0x16, 0x6F, 0x78,
  0x57, 0x81, 0x2D, 0xF7, 0xFC, 0x66, 0x0F, 0x27,
  0x75, 0x35, 0xB4, 0x34, 0x10, 0xEE, 0xA2, 0xDB,
  0xCC, 0xE3, 0x35, 0x99, 0x43, 0x48, 0xD2, 0xBB,
  0x93, 0xC1};
const int Xor_Str_Size = 34;
const int Xor_Stats[] = {
  0x32, 0xD6, 0xA0, 0x14, 0x5E, 0xA5, 0x66, 0x85,
  0xE5, 0xAE, 0x57, 0x64, 0x1A, 0x29, 0x59, 0x05};
const int Xor_Stats_Size = 10;
const int Xor_Info[] = {
  0x06, 0x35, 0x2A, 0x43, 0xA0, 0xC7, 0x02, 0xFF,
  0xBD};
const int Xor_Info_Size = 9;
const int Xor_Element[] = {
  0x05};
const int Xor_Element_Size = 1;
const int Xor_Id[] = {
  0x18, 0x4E, 0x6E, 0x5F};
const int Xor_Id_Size = 4;
const int Xor_Sort[] = {
  0x9B, 0x34, 0x80, 0x2A};
const int Xor_Sort_Size = 4;
const int Xor_Weap[] = {
  0x06};
const int Xor_Weap_Size = 1;
const int Xor_Tome[] = {
  0x35};
const int Xor_Tome_Size = 1;
const int Xor_Move[] = {
  0x2A};
const int Xor_Move_Size = 1;
const int Xor_Series[] = {
  0x43};
const int Xor_Series_Size = 1;
const int Xor_Special[] = {
  0xA0};
const int Xor_Special_Size = 1;
const int Xor_Permanent[] = {
  0xC7};
const int Xor_Permanent_Size = 1;
const int Xor_BVid[] = {
  0x02};
const int Xor_BVid_Size = 1;
const int Xor_Refresher[] = {
  0xFF};
const int Xor_Refresher_Size = 1;
const int Xor_Dummy1[] = {
  0xBD};
const int Xor_Dummy1_Size = 1;

const unsigned char Skills[][20] = {"Default Weapon: ", "Default Assist: ", "Default Special: ", "Unknown: ", "Unknown: ", "Unknown: ", "Unlocked Weapon: ", "Unlocked Assist: ",
  "Unlocked Special: ", "Passive A: ", "Passive B: ", "Passive C: ", "Unknown: ", "Unknown: "};
const unsigned char Legendary[][6] = {"Fire", "Water", "Wind", "Earth"};
const unsigned char Weapons[][20] = {"Red Sword", "Blue Lance", "Green Axe", "Red Bow", "Blue Bow", "Green Bow", "Colorless Bow",  "Colorless Dagger", "Red Tome",
  "Blue Tome", "Green Tome", "Colorless Staff", "Red Breath", "Blue Breath", "Green Breath", "Colorless Breath"};
const unsigned char Tome_Elem[][8] = {"None", "Fire", "Thunder", "Wind", "Light", "Dark"};
const unsigned char Movement[][10] = {"Infantry", "Armored", "Cavalry", "Flying"};
const unsigned char Series[][105] = {"Heroes", "Shadow Dragon and the Blade of Light / Mystery of the Emblem / Shadow Dragon / New Mystery of the Emblem",
  "Gaiden / Echoes", "Genealogy of the Holy War", "Thracia 776", "The Binding Blade", "The Blazing Blade", "The Sacred Stones", "Path of Radiance", "Radiant Dawn", "Awakening", "Fates"};

//--------------------------------
int read_data_Xorred(char data[], int position, int size, const int Xor[], int XorPos)
{
    int read=0;
	for(int i=0; i<size; i++)
		read+=((((unsigned char)data[position+i])^Xor[XorPos+i])<<(i*8));
	return read;
}
unsigned char* actOnData(hsdarc_buffer buf, int num, const int Xor[], int XorSize, unsigned char* (*a)(long long int ptr, char data[], const int Xor[], int XorSize))
{
	if(read_data_long(buf.data, buf.ptr_list[num], 8) == 0)
        return a(buf.ptr_list[num] + 8, buf.data, Xor, XorSize);
	return a(read_data_long(buf.data, buf.ptr_list[num], 8) + 0x20, buf.data, Xor_Str, Xor_Str_Size);
}
unsigned char* GetSkillXor(hsdarc_buffer buf, long long int ptr, const int Xor[], int XorSize, unsigned char* (*a)(long long int ptr, char data[], const int Xor[], int XorSize))
{
	if(read_data_long(buf.data, ptr, 8) == 0)
        return a(ptr, buf.data, Xor, XorSize);
	return a(read_data_long(buf.data, ptr, 8) + 0x20, buf.data, Xor_Str, Xor_Str_Size);
}

int GetHero(hsdarc_buffer buf, int num)
{
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        SetConsoleOutputCP(CP_UTF8);
    #endif
	unsigned char* strbuf = actOnData(buf, num++, Xor_Str, Xor_Str_Size, GetStringXorred);
	cout<<"Internal Identifier: "<<strbuf<<endl;
	delete(strbuf);
	strbuf = actOnData(buf, num++, Xor_Str, Xor_Str_Size, GetStringXorred);
	cout<<"Romanized Identifier: "<<strbuf<<endl;
	delete(strbuf);
	strbuf = actOnData(buf, num++, Xor_Str, Xor_Str_Size, GetStringXorred);
	cout<<"Face Folder: "<<strbuf<<endl;
	delete(strbuf);
	strbuf = actOnData(buf, num, Xor_Str, Xor_Str_Size, GetStringXorred);
	cout<<"Face Folder no.2: "<<strbuf<<endl;
	delete(strbuf);
	int leg = read_data_long(buf.data, buf.ptr_list[num] + 0x8, 8);
	if(leg != 0) 
	{
        strbuf =GetHeroStats(leg + 0x20, buf.data, Xor_Stats, Xor_Stats_Size, 0);
		cout<<"Legendary buffes: "<<strbuf<<endl;
		delete(strbuf);
		leg = buf.data[leg + 0x30] ^ Xor_Element[0];
		cout<<"Element: "<<Legendary[leg-1]<<endl;
	}
	cout<<"ID: "<<read_data_Xorred(buf.data, buf.ptr_list[num] + 0x18, Xor_Id_Size, Xor_Id, 0)<<endl;
	cout<<"Sort Value: "<<read_data_Xorred(buf.data, buf.ptr_list[num] + 0x1C, Xor_Sort_Size, Xor_Sort, 0)<<endl;
	cout<<"Weapon: "<<Weapons[read_data_Xorred(buf.data, buf.ptr_list[num] + 0x20, Xor_Weap_Size, Xor_Weap, 0)]<<endl;
	cout<<"Tome Element: "<<Tome_Elem[read_data_Xorred(buf.data, buf.ptr_list[num] + 0x21, Xor_Tome_Size, Xor_Tome, 0)]<<endl;
	cout<<"Movement Type: "<<Movement[read_data_Xorred(buf.data, buf.ptr_list[num] + 0x22, Xor_Move_Size, Xor_Move, 0)]<<endl;
	cout<<"Series: "<<Series[read_data_Xorred(buf.data, buf.ptr_list[num] + 0x23, Xor_Series_Size, Xor_Series, 0)]<<endl;
	if(read_data_Xorred(buf.data, buf.ptr_list[num] + 0x24, Xor_Special_Size, Xor_Special, 0) != 0)
		cout<<"Special Hero"<<endl;
	else
		cout<<"Normal Hero"<<endl;
	if(read_data_Xorred(buf.data, buf.ptr_list[num] + 0x25, Xor_Permanent_Size, Xor_Permanent, 0) != 0)
		cout<<"Permanent Hero"<<endl;
	else
		cout<<"Sendable Home Hero"<<endl;
	cout<<"BVID: "<<read_data_Xorred(buf.data, buf.ptr_list[num] + 0x26, Xor_BVid_Size, Xor_BVid, 0)<<endl;
	if(read_data_Xorred(buf.data, buf.ptr_list[num] + 0x27, Xor_Refresher_Size, Xor_Refresher, 0) != 0)
		cout<<"Singer / Dancer"<<endl;
	else
		cout<<"Not Singer / Dancer"<<endl;
	strbuf = GetHeroStats(buf.ptr_list[num] + 0x30, buf.data, Xor_Stats, Xor_Stats_Size, 1);
	cout<<"5 Star Level 1 Stats: "<<strbuf<<endl;
	delete(strbuf);
	strbuf = GetHeroGrowths(buf.ptr_list[num] + 0x40, buf.data, Xor_Stats, Xor_Stats_Size);
	cout<<"Growth Points: "<<strbuf<<endl;
	delete(strbuf);
	strbuf = GetHeroStats(buf.ptr_list[num] + 0x50, buf.data, Xor_Stats, Xor_Stats_Size, 0);
	cout<<"Enemy Stats: "<<strbuf<<endl;
	delete(strbuf);
	char multiple='\0';
	int fnum=num+1;
	for(int i=0; i<5; i++)
	{
		cout<<"------------------------------------------ "<<i+1<<" Star"<<multiple<<" Skills ------------------------------------------"<<endl;
		for(int j=0; j<14; j++)
		{
			strbuf = GetSkillXor(buf, buf.ptr_list[num] + 0x60 + (((i*14)+j)*8), Xor_Str, Xor_Str_Size, GetStringXorred);
			cout<<Skills[j]<<strbuf<<endl;
			if(strbuf[0]!='\0')
				fnum++;
			delete(strbuf);
		}
		multiple='s';
	}
	cout<<"----------------------------------------------------------------------------------------------------"<<endl;
	return fnum;
}

unsigned char* GetHeroStats(long long int ptr, char data[], const int Xor[], int XorSize, int addition)
{
	unsigned char* String = new unsigned char[(XorSize*6)+1];
	int i, tmp, pos=0;
	for(i=0; i<XorSize; i+=2)
    {
		tmp = read_data_Xorred(data, ptr + i, 2, Xor, i) + addition;
		if(tmp > 10000)
			String[pos++]=((tmp/10000)%10) + '0';
		if(tmp > 1000)
			String[pos++]=((tmp/1000)%10) + '0';
		if(tmp > 100)
			String[pos++]=((tmp/100)%10) + '0';
		if(tmp > 10)
			String[pos++]=((tmp/10)%10) + '0';
		String[pos++]=(tmp%10) + '0';
		if(i!=8)
			String[pos++]='|';
	}
	String[pos]='\0';
	return String;
}
unsigned char* GetHeroGrowths(long long int ptr, char data[], const int Xor[], int XorSize)
{
	unsigned char* String = new unsigned char[(XorSize*6)+1];
	int i, tmp, pos=0;
	for(i=0; i<XorSize; i+=2)
    {
		tmp = (read_data_Xorred(data, ptr + i, 2, Xor, i) - 20) /5;
		if(tmp > 10000)
			String[pos++]=((tmp/10000)%10) + '0';
		if(tmp > 1000)
			String[pos++]=((tmp/1000)%10) + '0';
		if(tmp > 100)
			String[pos++]=((tmp/100)%10) + '0';
		if(tmp > 10)
			String[pos++]=((tmp/10)%10) + '0';
		String[pos++]=(tmp%10) + '0';
		if(i!=8)
			String[pos++]='|';
	}
	String[pos]='\0';
	return String;
}


unsigned char GetFirstChar(hsdarc_buffer buf, int num)
{
	if(read_data_long(buf.data, buf.ptr_list[num], 8) == 0)
        return buf.data[buf.ptr_list[num]+8] ^ Xor_Str[0];
    return buf.data[read_data_long(buf.data, buf.ptr_list[num], 8) + 0x20] ^ Xor_Str[0];
}