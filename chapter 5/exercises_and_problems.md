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

# 5.13

The BTV scheduler can ensure that higher-priority threads receive more attention from the CPU than lower-priority threads by assigning a greater number of lottery tickets to the higher-priority threads. When a scheduling decision is made, the lottery ticket chosen at random is more likely to belong to a higher-priority thread than a lower-priority thread, resulting in higher-priority threads being executed more frequently.

# 5.14

Option 1: Each processing core has its own run queue
```
Advantages:

The run queue for each core can be optimized for that specific core's performance characteristics, such as cache size and memory bandwidth.
There is no contention for access to the run queue between processing cores, which can improve scalability and reduce synchronization overhead.
The run queue can be assigned to a specific core, allowing the scheduler to manage the workloads of each core independently.

Disadvantages:

Processes may be imbalanced across cores, leading to uneven utilization and performance degradation.
Moving processes between run queues can add overhead to the scheduling process.
Inter-core communication may be required to balance workloads across cores, which can incur additional overhead.
```

Option 2: A single run queue is shared by all processing cores
```
Advantages:

Load balancing across cores can be achieved automatically by scheduling processes to the core with the lightest workload.
There is only one run queue to maintain, reducing the overhead of synchronization and memory management.
Processes can be migrated between cores more easily, allowing for more efficient utilization of resources.

Disadvantages:

Contentions for access to the run queue can occur, which can limit scalability and lead to performance degradation.
The run queue may not be optimized for the performance characteristics of any one core.
Inter-core communication may be required to manage access to the run queue, which can incur additional overhead.
```

# 5.15

a. α = 0 and τ0 = 100 milliseconds

If α = 0, then τn+1 = τn, and recent history has no effect (current conditions are assumed to be transient).

b. α = 0.99 and τ0 = 10 milliseconds

If α = 1, then τn+1 = tn, and only the most recent CPU burst matters (history is assumed to be old and irrelevant).

# 5.16

The regressive round-robin scheduler is designed to favor CPU-bound processes over I/O-bound processes. This is because the scheduler increases the time quantum of a process that uses its entire time quantum (i.e., completes its CPU burst without blocking for I/O), and boosts its priority level. In contrast, if a process blocks for I/O before using its entire time quantum, its time quantum is reduced, but its priority remains the same.

# 5.19

The nice value is a parameter that affects the priority of a process in the scheduling queue. A higher nice value indicates a lower priority, while a lower nice value indicates a higher priority. In general, allowing any user to assign a process a nice value >= 0 is considered safe, as it only lowers the priority of the process and does not affect the overall system performance.

However, allowing users to assign nice values < 0 can potentially impact the performance and stability of the system. Setting a process to a negative nice value gives it a higher priority, which means it will have more access to the CPU resources and can potentially starve other processes of CPU time. This can lead to degraded system performance and stability, as other processes may become unresponsive or fail to complete their tasks on time.

To prevent this from happening, some systems limit the ability to assign nice values < 0 to the root user (or administrator). This ensures that only privileged users who have the necessary expertise and responsibility can modify the priority of processes in the system, and helps prevent unintentional or malicious behavior that could impact the overall system performance and stability.

# 5.20

b, d

# 5.37

1. Improved power efficiency: By using low-power cores for less demanding tasks, a mobile system can save power and extend battery life. High-performance cores can be used for more demanding tasks, but they can be turned off when not needed, reducing power consumption.

2. Better performance: A heterogeneous multiprocessing system can provide better performance than a system with only one type of processing core. The high-performance cores can handle more demanding tasks, while the low-power cores can handle background tasks, resulting in a smoother and more responsive user experience.

3. More flexibility: Different types of processing cores can be used for different types of tasks, allowing a mobile system to be optimized for specific workloads. For example, a system could use high-performance cores for gaming and low-power cores for background tasks.

4. Reduced cost: By using a combination of high-performance and low-power cores, a mobile system can achieve better performance without the need for expensive high-performance cores for every task.

5. Scalability: A heterogeneous multiprocessing system can be easily scaled to meet changing performance requirements. As the demands of mobile applications increase, additional high-performance or low-power cores can be added to the system.
