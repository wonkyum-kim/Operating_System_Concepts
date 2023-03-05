# 5.1 

n!

# 5.2

The main difference between preemptive and nonpreemptive scheduling is that in preemptive scheduling, the CPU can be taken away from a process before it has completed its execution, while in nonpreemptive scheduling, the CPU is not taken away from a process until it has completed its execution or it enters into a waiting state. Preemptive scheduling is more flexible and allows for better response time, but it also incurs a higher overhead due to frequent context switching. Nonpreemptive scheduling is simpler and more predictable, but it can result in longer response times and can lead to resource utilization problems if a process monopolizes the CPU.

# 5.3

a. (8 + 11.6 + 12) / 3 = 10.53

b. (8 + 8 + 12.6) / 3 = 9.53

c. (1 + 5.6 + 14) / 3 = 6.87

# 5.6

Better response time for interactive processes: Interactive processes usually have higher priority and are placed in a higher-priority queue. With a shorter time quantum for the high-priority queue, interactive processes can be quickly scheduled and get a faster response time.

Prevention of starvation: Processes in lower-priority queues can be scheduled with longer time-quantum sizes, which ensures that they have enough time to complete their work. This approach prevents the starvation of low-priority processes, which could happen if they were always preempted by high-priority processes.

Improved throughput: Different types of processes have different resource requirements, and different time-quantum sizes can help optimize resource utilization. For example, I/O-bound processes may benefit from longer time quantums in the I/O queue, while CPU-bound processes may benefit from shorter time quantums in the CPU queue. By optimizing time-quantum sizes for each queue, the system can achieve higher throughput.
