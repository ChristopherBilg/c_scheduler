#include <stdio.h>
#include "config.h"
#include "priority_queue.h"

int main() {
  struct Configuration conf = read_config_file("CONFIG.ini");

  int current_time = conf.INIT_TIME;

  // Create and initialize all of the queues
  struct priority_queue *p_queue = NULL;
  initialize_priority_queue(p_queue, 100000);
  //push_to_priority_queue(&p_queue, current_time, "Simulation starting");

  printf("Success!\n");
  
  return 1;
}
