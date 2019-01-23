#ifndef _HEADER_NAME_
#define _HEADER_NAME_
#define BUFF 1024
#endif

struct Config {
  char SEED[BUFF];
  char INIT_TIME[BUFF];
  char FIN_TIME[BUFF];
  char ARRIVE_MIN[BUFF];
  char ARRIVE_MAX[BUFF];
  char QUIT_PROB[BUFF];
  char CPU_MIN[BUFF];
  char CPU_MAX[BUFF];
  char DISK1_MIN[BUFF];
  char DISK1_MAX[BUFF];
  char DISK2_MIN[BUFF];
  char DISK2_MAX[BUFF];
};

struct Configuration {
  unsigned int SEED;
  int INIT_TIME;
  int FIN_TIME;
  int ARRIVE_MIN;
  int ARRIVE_MAX;
  int QUIT_PROB;
  int CPU_MIN;
  int CPU_MAX;
  int DISK1_MIN;
  int DISK1_MAX;
  int DISK2_MIN;
  int DISK2_MAX;
};

struct Configuration read_config_file(char *filename);
void print_config_struct(struct Configuration config);
