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

  // Average Size and Average Response Time for each Server Component (Statistics)
  int total_cpu_response_time = 0;
  int total_disk1_response_time = 0;
  int total_disk2_response_time = 0;

  // Statistics for average size of each queue
  int event_queue_summation = 1;
  int event_queue_increments = 1;
  int cpu_queue_summation = 0;
  int cpu_queue_increments = 0;
  int disk1_queue_summation = 0;
  int disk1_queue_increments = 0;
  int disk2_queue_summation = 0;
  int disk2_queue_increments = 0;

  // Throughput Statistics of each Server Component
  int cpu_jobs_began = 0;
  int disk1_jobs_began = 0;
  int disk2_jobs_began = 0;
  int cpu_jobs_completed = 0;
  int disk1_jobs_completed = 0;
  int disk2_jobs_completed = 0;
  
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
      printf("\tPriority Queue Average Size: %d/%d\n", event_queue_summation, event_queue_increments);
      
      printf("\n\tCPU FIFO Queue Max Size: %d\n", cpu_queue->statistics_max_size);
      printf("\tCPU FIFO Queue Average Size: %d/%d\n", cpu_queue_summation, cpu_queue_increments);
      printf("\tCPU Utilization: %d/%d\n", cpu_time_busy, conf.FIN_TIME-conf.INIT_TIME);
      printf("\tCPU Max Response Time: %d\n", cpu_max_response_time);
      printf("\tCPU Average Response Time: %d/%d\n", total_cpu_response_time, cpu_jobs_began);
      printf("\tCPU Throughput: %d/%d\n", cpu_jobs_completed, cpu_time_busy);
      
      printf("\n\tDisk1 FIFO Queue Max Size: %d\n", disk1_queue->statistics_max_size);
      printf("\tDisk1 FIFO Queue Average Size: %d/%d\n", disk1_queue_summation, disk1_queue_increments);
      printf("\tDisk1 Utilization: %d/%d\n", disk1_time_busy, conf.FIN_TIME-conf.INIT_TIME);
      printf("\tDisk1 Max Response Time: %d\n", disk1_max_response_time);
      printf("\tDisk1 Average Response Time: %d/%d\n", total_disk1_response_time, disk1_jobs_began);
      printf("\tDisk1 Throughput: %d/%d\n", disk1_jobs_completed, disk1_time_busy);
      
      printf("\n\tDisk2 FIFO Queue Max Size: %d\n", disk2_queue->statistics_max_size);
      printf("\tDisk2 FIFO Queue Average Size: %d/%d\n", disk2_queue_summation, disk2_queue_increments);
      printf("\tDisk2 Utilization: %d/%d\n", disk2_time_busy, conf.FIN_TIME-conf.INIT_TIME);
      printf("\tDisk2 Max Response Time: %d\n", disk2_max_response_time);
      printf("\tDisk2 Average Response Time: %d/%d\n", total_disk2_response_time, disk2_jobs_began);
      printf("\tDisk2 Throughput: %d/%d\n", disk2_jobs_completed, disk2_time_busy);
      
      destroy_priority_queue(&p_queue);
      destroyQueue(cpu_queue);
      destroyQueue(disk1_queue);
      destroyQueue(disk2_queue);

      runTests();

      return 1;
    case ARRIVED:
      printf("Job #%d arrived at time: %d\n", current_node.job, current_node.priority);
      enQueue(cpu_queue, current_node.job);

      int arrival_time = generate_int(conf.ARRIVE_MIN, conf.ARRIVE_MAX);
      current_time += arrival_time;
      job_number++;
      push_to_priority_queue(&p_queue, current_time, job_number, ARRIVED);
      event_queue_summation += p_queue.length;
      event_queue_increments++;
      
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
      total_cpu_response_time += cpu_finish_time;
      cpu_jobs_began++;

      cpu_queue_summation += cpu_queue->size;
      cpu_queue_increments++;
      
      push_to_priority_queue(&p_queue, current_node.priority + cpu_finish_time, current_node.job, CPU_FINISHED);
      break;
    case CPU_FINISHED:
      printf("Job #%d finished at CPU at time: %d\n", current_node.job, current_node.priority);
      _Bool quit = probability_select(10);
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
      cpu_jobs_completed++;
      
      break;
    case DISK1_ARRIVED:
      printf("Job #%d arrived at Disk1 at time: %d\n", current_node.job, current_node.priority);
      int disk1_finish_time = generate_int(conf.DISK1_MIN, conf.DISK1_MAX);

      // Statistics
      disk1_time_busy += disk1_finish_time;
      if (disk1_max_response_time < disk1_finish_time)
        disk1_max_response_time = disk1_finish_time;
      total_disk1_response_time += disk1_finish_time;
      disk1_jobs_began++;

      disk1_queue_summation += disk1_queue->size;
      disk1_queue_increments++;

      push_to_priority_queue(&p_queue, current_node.priority + disk1_finish_time, current_node.job, DISK1_FINISHED);
      //enQueue(disk1_queue, current_node.job);
      break;
    case DISK1_FINISHED:
      printf("Job #%d finished at Disk1 at time: %d\n", current_node.job, current_node.priority);
      disk1_idle = true;
      //push_to_priority_queue(&p_queue, current_node.priority, current_node.job, ARRIVED);
      enQueue(cpu_queue, current_node.job);

      disk1_jobs_completed++;
      break;
    case DISK2_ARRIVED:
      printf("Job #%d arrived at Disk2 at time: %d\n", current_node.job, current_node.priority);
      int disk2_finish_time = generate_int(conf.DISK2_MIN, conf.DISK2_MAX);

      // Statistics
      disk2_time_busy += disk2_finish_time;
      if (disk2_max_response_time < disk2_finish_time)
        disk2_max_response_time = disk2_finish_time;
      total_disk2_response_time += disk2_finish_time;
      disk2_jobs_began++;

      disk2_queue_summation += disk2_queue->size;
      disk2_queue_increments++;

      push_to_priority_queue(&p_queue, current_node.priority + disk2_finish_time, current_node.job, DISK2_FINISHED);
      //enQueue(disk2_queue, current_node.job);
      break;
    case DISK2_FINISHED:
      printf("Job #%d finished at Disk2 at time: %d\n", current_node.job, current_node.priority);
      disk2_idle = true;
      //push_to_priority_queue(&p_queue, current_node.priority, current_node.job, ARRIVED);
      enQueue(cpu_queue, current_node.job);

      disk2_jobs_completed++;
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

void runTests() {
  struct priority_queue queue = initialize_priority_queue(100);

  printf("\nPushing 4 items into priority queue, in random order\n");
  push_to_priority_queue(&queue, generate_int(0, 500), 0, FINISHED);
  push_to_priority_queue(&queue, generate_int(0, 500), 0, ARRIVED);
  push_to_priority_queue(&queue, generate_int(0, 500), 0, SIM_ENDING);
  push_to_priority_queue(&queue, generate_int(0, 500), 0, SIM_STARTING);

  printf("Popped from priority queue, priority number %d was popped\n", pop_from_priority_queue(&queue).priority);
  printf("Popped from priority queue, priority number %d was popped\n", pop_from_priority_queue(&queue).priority);
  printf("Popped from priority queue, priority number %d was popped\n", pop_from_priority_queue(&queue).priority);
  printf("Popped from priority queue, priority number %d was popped\n", pop_from_priority_queue(&queue).priority);

  int counter = 0;
  int iterations = 1000;
  int ideal_prob = 20;
  for (int i=0; i<iterations; i++) {
    _Bool pass = probability_select(ideal_prob);
    if (pass == true)
      counter++;
  }
  printf("\nProbability true (hopefully close to %d%%): %d/%d\n", ideal_prob, counter, iterations);
  
  return;
}
