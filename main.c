#include <stdio.h>
#include "main.h"
#include "config.h"
#include "priority_queue.h"
#include "fifo_queue.h"

int main() {
  struct Configuration conf = read_config_file("CONFIG.ini");

  int current_time = 0;
  int job_number = 1;

  // Create and initialize all of the queues
  struct priority_queue p_queue = initialize_priority_queue(100000);
  push_to_priority_queue(&p_queue, current_time, 0, SIM_STARTING);
  push_to_priority_queue(&p_queue, 0, job_number, ARRIVED);
  push_to_priority_queue(&p_queue, conf.FIN_TIME, 0, SIM_ENDING);

  // init. fifo_queue for cpu_queue, disk1_queue, and disk2_queue
  // Make fifo_queue my own instead of 3rd party
  struct Queue *cpu_queue = createQueue();
  struct Queue *disk1_queue = createQueue();
  struct Queue *disk2_queue = createQueue();
  
  // Make event enum Event
  enum EVENT current_event;

  // Pop the starting event to begin the simulation
  pop_from_priority_queue(&p_queue);
  current_event = SIM_STARTING;
  current_time = 0;

  // Main running loop
  while (current_time < conf.FIN_TIME) {
    struct priority_node current_node = pop_from_priority_queue(&p_queue);
    current_event = current_node.event;
    switch (current_event) {
    case SIM_STARTING:
      break;
    case SIM_ENDING:
      break;
    case ARRIVED:
      break;
    case FINISHED:
      break;
    case CPU_ARRIVED:
      break;
    case CPU_FINISHED:
      break;
    case DISK1_ARRIVED:
      break;
    case DISK1_FINISHED:
      break;
    case DISK2_ARRIVED:
      break;
    case DISK2_FINISHED:
      break;
    default:
      break;
    }

    break;
  }

  destroy_priority_queue(&p_queue);
  destroyQueue(cpu_queue);
  destroyQueue(disk1_queue);
  destroyQueue(disk2_queue);

  printf("Program finished successfully.\n");
  return 1;
}
