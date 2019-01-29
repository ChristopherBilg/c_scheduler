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

  // Utilizations Statistics
  int cpu_time_busy = 0;
  int disk1_time_busy = 0;
  int disk2_time_busy = 0;

  // Response Time Statistics
  int cpu_max_response_time = 0;
  int disk1_max_response_time = 0;
  int disk2_max_response_time = 0;
  
  // Make event enum Event
  enum EVENT current_event;

  // Statistics variables
  int num_finished = 0;

  // Main running loop
  print_config_struct(conf);
  while (1) {
    struct priority_node current_node = pop_from_priority_queue(&p_queue);
    current_event = current_node.event;
    switch (current_event) {
    case SIM_STARTING:
      current_time = conf.INIT_TIME;
      printf("Simulation starting at time: %d\n", current_time);
      break;
    case SIM_ENDING:
      printf("Simulation ending at time: %d with %d jobs finished completely\n", current_node.priority, num_finished);
      printf("Statistics:\n");
      printf("\tEvent Priority Queue Max Size: %d\n", p_queue.statistics_max_size);
      printf("\tPriority Queue Average Size: %d/%d\n", p_queue.length, p_queue.statistics_average_size_total);
      
      printf("\n\tCPU FIFO Queue Max Size: %d\n", cpu_queue->statistics_max_size);
      printf("\tCPU FIFO Queue Average Size: %d/%d\n", cpu_queue->size, cpu_queue->statistics_average_size_total);
      printf("\tCPU Utilization: %d/%d\n", cpu_time_busy, conf.FIN_TIME-conf.INIT_TIME);
      printf("\tCPU Max Response Time: %d\n", cpu_max_response_time);
      
      printf("\n\tDisk1 FIFO Queue Max Size: %d\n", disk1_queue->statistics_max_size);
      printf("\tDisk1 FIFO Queue Average Size: %d/%d\n", disk1_queue->size, disk1_queue->statistics_average_size_total);
      printf("\tDisk1 Utilization: %d/%d\n", disk1_time_busy, conf.FIN_TIME-conf.INIT_TIME);
      printf("\tDisk1 Max Response Time: %d\n", disk1_max_response_time);
      
      printf("\n\tDisk2 FIFO Queue Max Size: %d\n", disk2_queue->statistics_max_size);
      printf("\tDisk2 FIFO Queue Average Size: %d/%d\n", disk2_queue->size, disk2_queue->statistics_average_size_total);
      printf("\tDisk2 Utilization: %d/%d\n", disk2_time_busy, conf.FIN_TIME-conf.INIT_TIME);
      printf("\tDisk2 Max Response Time: %d\n", disk2_max_response_time);
      
      destroy_priority_queue(&p_queue);
      destroyQueue(cpu_queue);
      destroyQueue(disk1_queue);
      destroyQueue(disk2_queue);

      return 1;
    case ARRIVED:
      printf("Job #%d arrived at time: %d\n", current_node.job, current_node.priority);
      enQueue(cpu_queue, current_node.job);

      int arrival_time = generate_int(conf.ARRIVE_MIN, conf.ARRIVE_MAX);
      current_time += arrival_time;
      job_number++;
      push_to_priority_queue(&p_queue, current_time, job_number, ARRIVED);
      
      break;
    case FINISHED:
      printf("Job #%d finished at time: %d\n", current_node.job, current_node.priority);
      num_finished++;
      break;
    case CPU_ARRIVED:
      printf("Job #%d arrived at CPU at time: %d\n", current_node.job, current_node.priority);
      int cpu_finish_time = generate_int(conf.CPU_MIN, conf.CPU_MAX);

      // Statistics
      cpu_time_busy += cpu_finish_time;
      if (cpu_max_response_time < cpu_finish_time)
        cpu_max_response_time = cpu_finish_time;
      
      push_to_priority_queue(&p_queue, current_node.priority + cpu_finish_time, current_node.job, CPU_FINISHED);
      break;
    case CPU_FINISHED:
      printf("Job #%d finished at CPU at time: %d\n", current_node.job, current_node.priority);
      _Bool quit = probability_select(conf.QUIT_PROB);
      if (quit == true) {
        push_to_priority_queue(&p_queue, current_node.priority, current_node.job, FINISHED);
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
      printf("Job #%d arrived at Disk1 at time: %d\n", current_node.job, current_node.priority);
      int disk1_finish_time = generate_int(conf.DISK1_MIN, conf.DISK1_MAX);

      // Statistics
      disk1_time_busy += disk1_finish_time;
      if (disk1_max_response_time < disk1_finish_time)
        disk1_max_response_time = disk1_finish_time;

      push_to_priority_queue(&p_queue, current_node.priority + disk1_finish_time, current_node.job, DISK1_FINISHED);
      enQueue(disk1_queue, current_node.job);
      break;
    case DISK1_FINISHED:
      printf("Job #%d finished at Disk1 at time: %d\n", current_node.job, current_node.priority);
      disk1_idle = true;
      push_to_priority_queue(&p_queue, current_node.priority, current_node.job, FINISHED);
      break;
    case DISK2_ARRIVED:
      printf("Job #%d arrived at Disk2 at time: %d\n", current_node.job, current_node.priority);
      int disk2_finish_time = generate_int(conf.DISK2_MIN, conf.DISK2_MAX);

      // Statistics
      disk2_time_busy += disk2_finish_time;
      if (disk2_max_response_time < disk2_finish_time)
        disk2_max_response_time = disk2_finish_time;

      push_to_priority_queue(&p_queue, current_node.priority + disk2_finish_time, current_node.job, DISK2_FINISHED);
      enQueue(disk2_queue, current_node.job);
      break;
    case DISK2_FINISHED:
      printf("Job #%d finished at Disk2 at time: %d\n", current_node.job, current_node.priority);
      disk2_idle = true;
      push_to_priority_queue(&p_queue, current_node.priority, current_node.job, FINISHED);
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
