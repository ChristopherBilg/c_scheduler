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
  const unsigned int SEED;
  const int INIT_TIME;
  const int FIN_TIME;
  const int ARRIVE_MIN;
  const int ARRIVE_MAX;
  const int QUIT_PROB;
  const int CPU_MIN;
  const int CPU_MAX;
  const int DISK1_MIN;
  const int DISK1_MAX;
  const int DISK2_MIN;
  const int DISK2_MAX;
};

struct Configuration read_config_file(char *filename);
void print_config_struct(struct Configuration config);
