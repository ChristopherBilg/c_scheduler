#include <stdio.h>
#include "config.h"
#include "priority_queue.h"
#include "fifo_queue.h"

int main() {
  struct Configuration conf = read_config_file("CONFIG.ini");

  int current_time = conf.INIT_TIME;
  int job_number = 1;

  // Create and initialize all of the queues
  struct priority_queue p_queue = initialize_priority_queue(100000);
  push_to_priority_queue(&p_queue, current_time, "Simulation:", "STARTING");
  push_to_priority_queue(&p_queue, 0, "Job 1", "ARRIVED");
  push_to_priority_queue(&p_queue, conf.FIN_TIME, "Simulation:", "ENDING");

  // init. fifo_queue for cpu_queue, disk1_queue, and disk2_queue
  // Make fifo_queue my own instead of 3rd party
  struct Queue *cpu_queue = createQueue();
  struct Queue *disk1_queue = createQueue();
  struct Queue *disk2_queue = createQueue();
  
  // Make event enum Event

  // Main running loop
  while (current_time < conf.FIN_TIME) {
    break;
  }

  destroy_priority_queue(&p_queue);
  destroyQueue(cpu_queue);
  destroyQueue(disk1_queue);
  destroyQueue(disk2_queue);

  printf("Program finished successfully.\n");
  return 1;
}
