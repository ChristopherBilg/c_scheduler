#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "main.h"
#include "config.h"
#include "random.h"
#include "processing.h"

int main() {
  struct Configuration conf = read_config_file("CONFIG.ini");
  srand(conf.SEED);

  int current_time = conf.INIT_TIME;
  int job_number = 1;

  // Create and initialize all of the queues
  struct priority_queue p_queue = initialize_priority_queue(100000);
  push_to_priority_queue(&p_queue, conf.INIT_TIME, 0, SIM_STARTING);
  push_to_priority_queue(&p_queue, 0, job_number, ARRIVED);
  push_to_priority_queue(&p_queue, conf.FIN_TIME, 0, SIM_ENDING);

  // Initialize fifo_queue for cpu_queue, disk1_queue, and disk2_queue
  // Make fifo_queue my own instead of 3rd party
  struct Queue *cpu_queue = createQueue();
  struct Queue *disk1_queue = createQueue();
  struct Queue *disk2_queue = createQueue();

  // States for cpu and disk1/disk2
  _Bool cpu_idle = true;
  _Bool disk1_idle = true;
  _Bool disk2_idle = true;
  
  // Make event enum Event
  enum EVENT current_event;

  // Main running loop
  while (true) {
    struct priority_node current_node = pop_from_priority_queue(&p_queue);
    current_event = current_node.event;
    switch (current_event) {
    case SIM_STARTING:
      current_time = conf.INIT_TIME;
      printf("Simulation starting at time: %d\n", current_time);
      break;
    case SIM_ENDING:
      printf("Simulation ending at time: %d\n", current_time);

      destroy_priority_queue(&p_queue);
      destroyQueue(cpu_queue);
      destroyQueue(disk1_queue);
      destroyQueue(disk2_queue);

      return 1;
    case ARRIVED:
      printf("Job #%d arrived at time: %d\n", current_node.job, current_time);
      enQueue(cpu_queue, current_node.job);

      int arrival_time = generate_int(conf.ARRIVE_MIN, conf.ARRIVE_MAX);
      current_time += arrival_time;
      job_number++;
      push_to_priority_queue(&p_queue, current_time, job_number, ARRIVED);
      
      break;
    case FINISHED:
      printf("Job #%d finished at time: %d\n", current_node.job, current_time);
      break;
    case CPU_ARRIVED:
      printf("Job #%d arrived at CPU at time: %d\n", current_node.job, current_time);
      int cpu_finish_time = generate_int(conf.CPU_MIN, conf.CPU_MAX);
      //current_time += cpu_finish_time;
      
      push_to_priority_queue(&p_queue, current_time + cpu_finish_time, current_node.job, CPU_FINISHED);
      break;
    case CPU_FINISHED:
      printf("Job #%d finished at CPU at time: %d\n", current_node.job, current_time);
      _Bool quit = probability_select(conf.QUIT_PROB);
      if (quit == true) {
        push_to_priority_queue(&p_queue, current_time, current_node.job, FINISHED);
      }
      else {
        if (disk1_queue->size < disk2_queue->size) {
          enQueue(disk1_queue, current_node.job);
        }
        else {
          enQueue(disk2_queue, current_node.job);
        }
      }
      cpu_idle = true;
      break;
    case DISK1_ARRIVED:
      printf("Job #%d arrived at Disk1 at time: %d\n", current_node.job, current_time);
      int disk1_finish_time = generate_int(conf.DISK1_MIN, conf.DISK1_MAX);
      //current_time += disk1_finish_time;

      push_to_priority_queue(&p_queue, current_time + disk1_finish_time, current_node.job, DISK1_FINISHED);
      enQueue(disk1_queue, current_node.job);
      break;
    case DISK1_FINISHED:
      printf("Job #%d finished at Disk1 at time: %d\n", current_node.job, current_time);
      disk1_idle = true;
      push_to_priority_queue(&p_queue, current_time, current_node.job, FINISHED);
      break;
    case DISK2_ARRIVED:
      printf("Job #%d arrived at Disk2 at time: %d\n", current_node.job, current_time);
      int disk2_finish_time = generate_int(conf.DISK2_MIN, conf.DISK2_MAX);
      //current_time += disk2_finish_time;

      push_to_priority_queue(&p_queue, current_time + disk2_finish_time, current_node.job, DISK2_FINISHED);
      enQueue(disk2_queue, current_node.job);
      break;
    case DISK2_FINISHED:
      printf("Job #%d finished at Disk2 at time: %d\n", current_node.job, current_time);
      disk2_idle = true;
      push_to_priority_queue(&p_queue, current_time, current_node.job, FINISHED);
      break;
    default:
      perror("Something went wrong and the switch statement defaulted.");
      exit(EXIT_FAILURE);
      break;
    }

    cpu_idle = process_cpu(cpu_queue, &p_queue, cpu_idle, current_time);
    disk1_idle = process_disk1(disk1_queue, &p_queue, disk1_idle, current_time);
    disk2_idle = process_disk2(disk2_queue, &p_queue, disk2_idle, current_time);
  }

  return 1;
}
