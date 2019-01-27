#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

struct Configuration read_config_file(char *filename) {
  struct Config configuration = {};
  FILE *file = fopen(filename, "r+");

  if (file != NULL) {
    char line[1024];
    int i = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
      char *cfline;
      cfline = strstr((char *)line, "=");
      cfline = cfline + strlen("=");

      if (i == 0) {
        memcpy(configuration.SEED, cfline, strlen(cfline));
      }
      else if (i == 1) {
        memcpy(configuration.INIT_TIME, cfline, strlen(cfline));
      }
      else if (i == 2) {
        memcpy(configuration.FIN_TIME, cfline, strlen(cfline));
      }
      else if (i == 3) {
        memcpy(configuration.ARRIVE_MIN, cfline, strlen(cfline));
      }
      else if (i == 4) {
        memcpy(configuration.ARRIVE_MAX, cfline, strlen(cfline));
      }
      else if (i == 5) {
        memcpy(configuration.QUIT_PROB, cfline, strlen(cfline));
      }
      else if (i == 6) {
        memcpy(configuration.CPU_MIN, cfline, strlen(cfline));
      }
      else if (i == 7) {
        memcpy(configuration.CPU_MAX, cfline, strlen(cfline));
      }
      else if (i == 8) {
        memcpy(configuration.DISK1_MIN, cfline, strlen(cfline));
      }
      else if (i == 9) {
        memcpy(configuration.DISK1_MAX, cfline, strlen(cfline));
      }
      else if (i == 10) {
        memcpy(configuration.DISK2_MIN, cfline, strlen(cfline));
      }
      else if (i == 11) {
        memcpy(configuration.DISK2_MAX, cfline, strlen(cfline));
      }

      i++;
    }
    
    fclose(file);
  }

  struct Configuration conf = {};
  conf.SEED = atoi(configuration.SEED);
  conf.INIT_TIME = atoi(configuration.INIT_TIME);
  conf.FIN_TIME = atoi(configuration.FIN_TIME);
  conf.ARRIVE_MIN = atoi(configuration.ARRIVE_MIN);
  conf.ARRIVE_MAX = atoi(configuration.ARRIVE_MAX);
  conf.QUIT_PROB = atoi(configuration.QUIT_PROB);
  conf.CPU_MIN = atoi(configuration.CPU_MIN);
  conf.CPU_MAX = atoi(configuration.CPU_MAX);
  conf.DISK1_MIN = atoi(configuration.DISK1_MIN);
  conf.DISK1_MAX = atoi(configuration.DISK1_MAX);
  conf.DISK2_MIN = atoi(configuration.DISK2_MIN);
  conf.DISK2_MAX = atoi(configuration.DISK2_MAX);
  
  return conf;
}

void print_config_struct(struct Configuration config) {
  printf("SEED: %d\n", config.SEED);
  printf("INIT_TIME: %d\n", config.INIT_TIME);
  printf("FIN_TIME: %d\n", config.FIN_TIME);
  printf("ARRIVE_MIN: %d\n", config.ARRIVE_MIN);
  printf("ARRIVE_MAX: %d\n", config.ARRIVE_MAX);
  printf("QUIT_PROB: %d\n", config.QUIT_PROB);
  printf("CPU_MIN: %d\n", config.CPU_MIN);
  printf("CPU_MAX: %d\n", config.CPU_MAX);
  printf("DISK1_MIN: %d\n", config.DISK1_MIN);
  printf("DISK1_MAX: %d\n", config.DISK1_MAX);
  printf("DISK2_MIN: %d\n", config.DISK2_MIN);
  printf("DISK2_MAX: %d\n", config.DISK2_MAX);
}
