output: main.o random.o config.o fifo_queue.o priority_queue.o processing.o
	gcc main.o random.o config.o fifo_queue.o priority_queue.o processing.o -o output -lm -g

main.o: main.c
	gcc main.c -c -lm -g

random.o: random.c
	gcc random.c -c -lm -g

config.o: config.c
	gcc config.c -c -lm -g

fifo_queue.o: fifo_queue.c
	gcc fifo_queue.c -c -lm -g

priority_queue.o: priority_queue.c
	gcc priority_queue.c -c -lm -g

processing.o: processing.c
	gcc processing.c -c -lm -g
