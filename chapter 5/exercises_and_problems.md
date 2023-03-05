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

# 5.9

The main difference between PCS and SCS scheduling is that in PCS, the process itself determines when it should be scheduled, while in SCS, the operating system is responsible for making scheduling decisions.

# 5.10

- Process P1: (40 / 2) + 60 = 80
- Process P2: (18 / 2) + 60 = 69
- Process P3: (10 / 2) + 60 = 65

Therefore, the new priority order is P3 > P2 > P1.

The traditional UNIX scheduler lowers the relative priority of a CPU-bound process.

# 5.11

I/O-bound programs are more likely to have voluntary context switches because they spend most of their time waiting for input/output operations to complete, while CPU-bound programs are more likely to have non-voluntary context switches because they spend most of their time performing CPU-intensive computations.

# 5.12

a. CPU utilization and response time: In some cases, optimizing CPU utilization can result in longer response times for interactive applications. For example, if the CPU is busy executing long-running computational tasks, an interactive application may be starved for CPU time and may appear unresponsive to the user. On the other hand, prioritizing response time over CPU utilization may result in lower CPU utilization, as the CPU may spend more time idle waiting for input/output operations to complete.

b. Average turnaround time and maximum waiting time: The goal of minimizing average turnaround time conflicts with the goal of minimizing maximum waiting time. Minimizing average turnaround time requires that all processes be scheduled quickly and efficiently, but this may result in some processes waiting for longer periods of time. Minimizing maximum waiting time requires prioritizing processes that have been waiting the longest, but this may result in some processes having longer overall turnaround times.

c. I/O device utilization and CPU utilization: I/O device utilization and CPU utilization can conflict when multiple processes are contending for access to the same I/O device. If the CPU is idle while waiting for I/O operations to complete, this can result in lower CPU utilization. On the other hand, if the CPU is busy executing other tasks while waiting for I/O operations to complete, this can result in higher CPU utilization but may cause I/O operations to take longer to complete. In some cases, a trade-off must be made between optimizing I/O device utilization and CPU utilization. For example, using interrupt-driven I/O can help maximize I/O device utilization but may result in higher CPU utilization. Alternatively, using polling-based I/O can help minimize CPU utilization but may result in lower I/O device utilization.

# 5.37

1. Improved power efficiency: By using low-power cores for less demanding tasks, a mobile system can save power and extend battery life. High-performance cores can be used for more demanding tasks, but they can be turned off when not needed, reducing power consumption.

2. Better performance: A heterogeneous multiprocessing system can provide better performance than a system with only one type of processing core. The high-performance cores can handle more demanding tasks, while the low-power cores can handle background tasks, resulting in a smoother and more responsive user experience.

3. More flexibility: Different types of processing cores can be used for different types of tasks, allowing a mobile system to be optimized for specific workloads. For example, a system could use high-performance cores for gaming and low-power cores for background tasks.

4. Reduced cost: By using a combination of high-performance and low-power cores, a mobile system can achieve better performance without the need for expensive high-performance cores for every task.

5. Scalability: A heterogeneous multiprocessing system can be easily scaled to meet changing performance requirements. As the demands of mobile applications increase, additional high-performance or low-power cores can be added to the system.
