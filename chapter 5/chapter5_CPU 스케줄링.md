# 5.1 기본 개념

* **CPU-I/O burst cycle**

프로세스 실행은 CPU 실행과 I/O 대기의 사이클로 구성된다.

프로세스는 이들 두 상태를 교대로 왔다 갔다 한다.

* **CPU scheduler**

CPU가 쉴 때마다, 운영체제는 ready queue에 있는 프로세스 중에서 하나를 선택해 실행하는데, `CPU 스케줄러`에 의해 수행된다.

* **preempitive and nonpreemptive scheduling**

CPU 스케줄링 결정은 네 가지 상황에서 발생할 수 있다.

```
1. when a process switches from the running to waiting state.
2. when a process switches from the running to ready state.
3. when a process switches from the waiting to ready state.
4. when a process terminates.
```

1과 4의 경우, 선택의 여지가 없이 새로운 프로세스가 반드시 실행되어야 한다. (nonpreemptive)

2와 3의 경우 선택의 여지가 있다. (preemptive)

* **nonpreeemptive**

비선점 스케줄링에서는 일단 CPU가 한 프로세스에 할당되면 프로세스가 종료하든지, 또는 대기 상태로 전환해 CPU를 방출할 때까지 점유한다.

* **preemptive**

프로세스는 CPU 스케줄러에 의해 우선할 수 있다.

* **dispatcher**

`디스패처`는 CPU 스케줄러가 선택한 프로세스에 CPU코어의 제어권을 주는 모듈이다.

디스패처는 모든 프로세스의 문맥 교환 시 호출되므로 가능한 한 빨리 수행되어야 한다.

디스패처가 하나의 프로세스를 중지하고 다른 프로세스의 수행을 시작하는데까지 소요되는 시간을 `dispatcher latency`라고 한다.

* * *

# 5.2 스케줄링 기준(scheduling criteria)

* CPU utilixtion : to keep the CPU as busy as possible.
* throughput : the number of process completed per time unit.
* turnaround time : from the time of submission to the time of completion.
* waiting time : the sum of periods spend waiting in the ready queue.
* response time : the time it takes to start responding.

* * *

# 5.3 스케줄링 알고리즘

CPU 스케줄링은 준비 큐에 있는 어느 프로세스에 CPU 코어를 할당할 것인지를 결정하는 문제를 다룬다.

* **FCFS(first-come, first-served scheduling)**

일반적인 queue 구조로 실행한다. (nonpreemptive)

* **SJF(shortest job first)**

CPU가 이용가능해지면, 가장 작은 CPU 버스트길이를 가진 프로세스를 실행한다.

하지만 다음 CPU 버스트의 길이를 알 수 없기 때문에 구현할 수 없다.

따라서 SJF 스케줄링과 근사한 방법을 사용한다.





