#include<iostream>
#include<string>
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


const int statGrowths[][13] = {
    {6, 8, 9, 11, 13, 14, 16, 18, 19, 21, 23, 24, 26},
    {7, 8, 10, 12, 14, 15, 17, 19, 21, 23, 25, 26, 28},
    {7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31},
    {8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 31, 33},
    {8, 10, 13, 15, 17, 19, 22, 24, 26, 28, 30, 33, 35}
};

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

stats_tuple GetLvl40Stats(stats_tuple lvl1, stats_tuple growths)
{
	stats_tuple stats=lvl1;
    stats.hp += statGrowths[4][growths.hp];
    stats.atk += statGrowths[4][growths.atk];
    stats.spd += statGrowths[4][growths.spd];
    stats.def += statGrowths[4][growths.def];
    stats.res += statGrowths[4][growths.res];
	return stats;
}

string actOnData(hsdarc_buffer buf, int num, const int Xor[], int XorSize, string (*a)(long long int ptr, char data[], const int Xor[], int XorSize))
{
	if(read_data_long(buf.data, buf.ptr_list[num], 8) == 0)
        return a(buf.ptr_list[num] + 8, buf.data, Xor, XorSize);
	return a(read_data_long(buf.data, buf.ptr_list[num], 8) + 0x20, buf.data, Xor_Str, Xor_Str_Size);
}

string GetSkillXor(hsdarc_buffer buf, long long int ptr, const int Xor[], int XorSize, string (*a)(long long int ptr, char data[], const int Xor[], int XorSize))
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
    string strbuf = actOnData(buf, num++, Xor_Str, Xor_Str_Size, GetStringXorred);
    cout<<"Internal Identifier: "<<strbuf<<endl;
    strbuf = actOnData(buf, num++, Xor_Str, Xor_Str_Size, GetStringXorred);
    cout<<"Romanized Identifier: "<<strbuf<<endl;
    strbuf = actOnData(buf, num++, Xor_Str, Xor_Str_Size, GetStringXorred);
    cout<<"Face Folder: "<<strbuf<<endl;
    strbuf = actOnData(buf, num, Xor_Str, Xor_Str_Size, GetStringXorred);
    cout<<"Face Folder no.2: "<<strbuf<<endl;
    int leg = read_data_long(buf.data, buf.ptr_list[num] + 0x8, 8);
    if(leg != 0) 
    {
        stats_tuple legendary_buffes = GetHeroStats(leg + 0x20, buf.data, Xor_Stats, 0);
        strbuf = PrintStats(legendary_buffes);
        cout<<"Legendary buffes: "<<strbuf<<endl;
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
    stats_tuple base_stats = GetHeroStats(buf.ptr_list[num] + 0x30, buf.data, Xor_Stats, 1);
    strbuf = PrintStats(base_stats);
    cout<<"5 Stars Level 1 Stats: "<<strbuf<<endl;
    stats_tuple hero_growths = GetHeroGrowths(buf.ptr_list[num] + 0x40, buf.data, Xor_Stats);
    strbuf = PrintStats(hero_growths);
    cout<<"Growth Points: "<<strbuf<<endl;
	stats_tuple level40stats = GetLvl40Stats(base_stats, hero_growths);
    strbuf = PrintStats(level40stats);
    cout<<"5 Stars Level 40 Stats: "<<strbuf<<endl;
    stats_tuple enemy_stats = GetHeroStats(buf.ptr_list[num] + 0x50, buf.data, Xor_Stats, 0);
    strbuf = PrintStats(enemy_stats);
    cout<<"Enemy Stats: "<<strbuf<<endl;
    char multiple=' ';
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
        }
        multiple='s';
    }
    cout<<"----------------------------------------------------------------------------------------------------"<<endl;
    return fnum;
}

stats_tuple GetHeroStats(long long int ptr, char data[], const int Xor[], int addition)
{
	stats_tuple stats;
    stats.hp = read_data_Xorred(data, ptr, 2, Xor, 0) + addition;
    stats.atk = read_data_Xorred(data, ptr + 2, 2, Xor, 2) + addition;
    stats.spd = read_data_Xorred(data, ptr + 4, 2, Xor, 4) + addition;
    stats.def = read_data_Xorred(data, ptr + 6, 2, Xor, 6) + addition;
    stats.res = read_data_Xorred(data, ptr + 8, 2, Xor, 8) + addition;
    stats.dummy1 = read_data_Xorred(data, ptr + 10, 2, Xor, 10) + addition;
    stats.dummy2 = read_data_Xorred(data, ptr + 12, 2, Xor, 12) + addition;
    stats.dummy3 = read_data_Xorred(data, ptr + 14, 2, Xor, 14) + addition;
	return stats;
}
stats_tuple GetHeroGrowths(long long int ptr, char data[], const int Xor[])
{
	stats_tuple stats;
    stats.hp = (read_data_Xorred(data, ptr, 2, Xor, 0) - 20) / 5;
    stats.atk = (read_data_Xorred(data, ptr + 2, 2, Xor, 2) - 20) / 5;
    stats.spd = (read_data_Xorred(data, ptr + 4, 2, Xor, 4) - 20) / 5;
    stats.def = (read_data_Xorred(data, ptr + 6, 2, Xor, 6) - 20) / 5;
    stats.res = (read_data_Xorred(data, ptr + 8, 2, Xor, 8) - 20) / 5;
    stats.dummy1 = (read_data_Xorred(data, ptr + 10, 2, Xor, 10) - 20) / 5;
    stats.dummy2 = (read_data_Xorred(data, ptr + 12, 2, Xor, 12) - 20) / 5;
    stats.dummy3 = (read_data_Xorred(data, ptr + 14, 2, Xor, 14) - 20) / 5;
	return stats;
}

string readShortInt(short int tmp, string String)
{
		if(tmp > 10000)
			String+=((tmp/10000)%10) + '0';
		if(tmp > 1000)
			String+=((tmp/1000)%10) + '0';
		if(tmp > 100)
			String+=((tmp/100)%10) + '0';
		if(tmp > 10)
			String+=((tmp/10)%10) + '0';
		String+=(tmp%10) + '0';
		return String;
}

string PrintStats(stats_tuple Stats)
{
	string String;
	String = readShortInt(Stats.hp, String);
	String += '|';
	String = readShortInt(Stats.atk, String);
	String += '|';
	String = readShortInt(Stats.spd, String);
	String += '|';
	String = readShortInt(Stats.def, String);
	String += '|';
	String = readShortInt(Stats.res, String);
	return String;
}

unsigned char GetFirstChar(hsdarc_buffer buf, int num)
{
	if(read_data_long(buf.data, buf.ptr_list[num], 8) == 0)
        return buf.data[buf.ptr_list[num]+8] ^ Xor_Str[0];
    return buf.data[read_data_long(buf.data, buf.ptr_list[num], 8) + 0x20] ^ Xor_Str[0];
}