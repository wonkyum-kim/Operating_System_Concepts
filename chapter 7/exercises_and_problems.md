## 7.1

Spinlocks are useful for multiprocessor systems where a thread can run in a busy loop (for a short period of time) rather than incurring the overhead of being put in a sleep queue. 

Mutexes are useful for locking resources. 

Semaphores and condition variables are more appropriate tools for synchronization when a resource must be held for a long period of time, since spinning is inefficient for a long duration.

## 7.3 

Use `acuire(mutex)` and `release()` rather than `wait(mutex)` and `signal(mutex)`.

## 7.4

If all philosophers simultaneously pick up their left forks, when they turn to pick up their right forks they will realize they are unavailable, and will block while waiting for it to become available.

## 7.6

10 - 8 + 1 + 1 + 6 - 3 = 7
