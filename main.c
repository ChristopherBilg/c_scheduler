#include <stdio.h>
#include "config.h"
#include "priority_queue.h"

int main() {
  struct Configuration conf = read_config_file("CONFIG.ini");

  int current_time = conf.INIT_TIME;

  // Create and initialize all of the queues
  struct priority_queue p_queue = initialize_priority_queue(100000);
  push_to_priority_queue(&p_queue, current_time, "Simulation starting");
  push_to_priority_queue(&p_queue, 0, "Job 1 arrived");
  push_to_priority_queue(&p_queue, conf.FIN_TIME, "Simulation ending");

  // Main running loop
  while (current_time < conf.FIN_TIME) {
    break;
  }

  destroy_priority_queue(&p_queue);
  return 1;
}
