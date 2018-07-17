struct hero_info {
  long long int unknown;
  int id_num;  
  int sort_value;
  unsigned char weapon_type;
  unsigned char tome_element;
  unsigned char move_type;
  unsigned char series;
  bool special_hero;
  bool permanent_hero;
  unsigned char base_vector_id;
  bool refresher;
  unsigned char dummy1;
};

struct stats_tuple {
  short int hp, atk, spd, def, res, dummy1, dummy2, dummy3;
};

struct legendary_info {
  stats_tuple bonus_effect;
  unsigned char element;
};

struct hero_definition {
  unsigned char* id_tag;
  unsigned char* roman;
  unsigned char* face_name;
  unsigned char* face_name2;
  legendary_info legendary;
  hero_info info;
  stats_tuple base_stats;
  stats_tuple growth_rates;
  stats_tuple max_stats;
  unsigned char* skills[5][14];
};

int GetHero(hsdarc_buffer buf, int num);
stats_tuple GetHeroStats(long long int ptr, char data[], const int Xor[], int addition);
std::string actOnData(hsdarc_buffer buf, int num, const int Xor[], int XorSize, std::string (*a)(long long int ptr, char data[], const int Xor[], int XorSize));
stats_tuple GetHeroGrowths(long long int ptr, char data[], const int Xor[]);
unsigned char GetFirstChar(hsdarc_buffer buf, int num);
std::string PrintStats(stats_tuple Stats);