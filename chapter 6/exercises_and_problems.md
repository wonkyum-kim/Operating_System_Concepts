# 6.1

Disabling interrupts frequently can affect the system's clock in several ways.

Firstly, when interrupts are disabled, the processor cannot respond to external events, including clock ticks. This can cause the system clock to drift or lose accuracy, as the clock will not be updated as frequently as it should be.

Secondly, disabling interrupts can also affect the accuracy of time-sensitive operations, such as measuring the duration of a task or scheduling time-based events. Without accurate timing information, these operations may not function correctly.

To minimize the effects of disabling interrupts on the system clock, it is important to keep the time that interrupts are disabled as short as possible. This can be done by limiting the use of critical sections of code that require interrupts to be disabled and by optimizing code to reduce the time that interrupts are disabled.

Another approach to minimizing the effects of disabling interrupts is to use hardware timers or other devices that are not affected by interrupt disabling. These devices can be used to provide accurate timing information and to trigger time-sensitive operations, even when interrupts are disabled.

# 6.2

Busy waiting, also known as spin-waiting, is a technique in computer programming where a process repeatedly checks if a condition is true, without yielding the CPU to other processes. The process essentially "spins" or loops, checking the condition continuously, until it becomes true. This technique is used to wait for a resource to become available or for a task to complete.

In an operating system, there are several other kinds of waiting that can occur, including:

1. Sleep waiting: In this type of waiting, a process voluntarily gives up the CPU and waits for a specified period before resuming execution.

2. Blocked waiting: A process is blocked waiting for a resource that is currently unavailable. The operating system will put the process into a blocked state until the resource becomes available.

3. Interrupt waiting: A process is waiting for an interrupt to occur, which will signal that an event has happened or that a task has completed.

Busy waiting can be avoided altogether in some cases. One way to avoid busy waiting is to use sleep waiting, where a process can give up the CPU and wait for a specified period before resuming execution. Another approach is to use semaphores or other synchronization primitives to manage access to shared resources, allowing processes to wait in a blocked state until the resource becomes available.
