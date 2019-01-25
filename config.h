#ifndef _HEADER_NAME_
#define _HEADER_NAME_
#endif

struct Config {
  char SEED[1024];
  char INIT_TIME[1024];
  char FIN_TIME[1024];
  char ARRIVE_MIN[1024];
  char ARRIVE_MAX[1024];
  char QUIT_PROB[1024];
  char CPU_MIN[1024];
  char CPU_MAX[1024];
  char DISK1_MIN[1024];
  char DISK1_MAX[1024];
  char DISK2_MIN[1024];
  char DISK2_MAX[1024];
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
