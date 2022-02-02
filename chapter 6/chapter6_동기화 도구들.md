# 6.1 배경

* **data inconsistency**

생산자와 소비자 코드는 개별적으로 올바르게 동작할지라도, 병행적(concurrently)로 실행하면 올바르게 동작하지 않는다.

왜냐하면 기계어 수준에서 볼 때 중간에 문맥교환이 일어나면 다른 결과가 나오게 되기 때문이다.

* **race condition**

몇개의 프로세스가 같은 데이터를 병행적으로 접근하거나 조작한다면, 실행 결과는 접근이 발생한 순서에 따라 다르다.

`경쟁 상황`을 방지하기 위해서 어느 시점에서 하나의 프로세스만이 공유 데이터를 조작하도록 해야한다.

* * *

# 6.2 임계구역 문제(the critical section problem)

* **critical section**

n개의 프로세스가 있는 시스템에서 각 프로세스는 `임계 구역`이라고 부르는 코드를 포함하고 있고,

그 안에서는 적어도 하나 이상의 다른 프로세스와 공유하는 데이터에 접근하고 갱신할 수 있다.

이 시스템에서는 한 프로세스가 자신의 임계구역에서 수행하는 동안에는 다른 프로세스들은 그 구역에 들어갈 수 없다.

각 프로세스는 자신의 임계구역으로 진입하려면 진입허가를 요청해야 하는데, 이러한 부분을 `진입 구역(entry section)`이라고 한다.

임계 구역 뒤에는 `퇴출 구역(exit section)`이 따라온다.

그리고 코드의 나머지 부분을 `나머지 구역(remainder section)`이라고 한다.

```
// 임계 구역 문제 해결을 위한 요구조건

1. 상호 배제(mutual exclusion) : 한 프로세스가 자기의 임계 구역에서 실행된다면, 다른 프로세스들은 그들 자신의 임계 구역에서 실행될 수 없다.
2. 진행(progress) : 자신의 임계 구역에서 실행되는 프로세스가 없으면, 나머지 구역에서 실행중이지 않은 프로세스들 중에서만 그 임계 구역으로 진입할 수 있는지 결정할 수 있다.
3. 한정된 대기(bounded waiting) : 프로세스가 임계 구역에 진입하려는 요청을 한 뒤에, 다른 프로세스들이 임계 구역에 진입하도록 허용되는 횟수에 한계가 있어야 한다.
```

* * *

# 6.3 Peterson의 해결안

현대 컴퓨터 구조가 `load`와 `store`와 같은 기본적인 기계어를 수행하는 방식 때문에 올바르게 실행된다고 보장할 수 없다.

하지만 `Peterson's solution`은 알고리즘적으로 임계 구역 문제를 해결하는 좋은 방법을 제시한다.

```
int turn;
bool flag[2];

while (true) {
  flag[i] = true;
  turn = j;
  
  while (flag[j] && turn == j) {  // j가 임계영역에서 실행되고 있는지 체크한다.
  }
  
  /* critical section */
  
  flag[i] = false;
  
  /* remainder section */
}
```

* * *

# 6.4 동기화를 위한 하드웨어 지원(Hardware Support for Synchronization)

* **memory barriers**

* **hardware instructions**

`test_and_set()`과 `compare_and_swap()`를 지원한다.

* **atomic variables**

일반적으로 `compare_and_set()` 명령어는 `원자적 변수`를 구축하는데 사용된다.

* * *

# 6.5 Mutex locks

임계구역 문제에 대한 하드웨어 기반 해결책은 복잡하므로 사용하기 힘드므로, `mutex lock`이라는 것을 사용한다.

`mutex`라는 용어는 `mutual exclusion`의 축약한 것이다.

프로세스는 임계구역에 들어가기 전에 반드시 락을 획득해야 하고, 빠져나올 때 반환해야 한다.

* **pthread_mutex_lock()**

```
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

아래와 같이 쓸 수 있다.

```
pthread_mutex_t lock;
pthread_mutex_lock(&lock);
x = x + 1;    // 임계영역 코드
pthread_mutex_unlock(&lock);
```

`pthread_mutex_lock()`이 호출되었을 때, 다른 어떤 스레드도 락을 가지고 있지 않다면 이 쓰레드가 락을 얻어서 임계 영역에 진입한다.

만약 다른 스레드가 락을 가지고 있다면, 락 획득을 시도하는 스레드는 락을 얻을 때까지 리턴하지 않는다.

* **pthread_mutex_init()**

```
int rc = pthread_mutex_init(&lock, NULL);
assert(rc == 0);  // 성공했는지 확인
```

* **pthread_mutex_destory()**

락 사용이 끝났다면 호출한다.

* **available**

mutex lock은 `available`이라는 변수를 가지는데, 락이 사용 가능한지 나타낸다.

사용가능하다면 `aquire()` 함수가 락을 획득하고 `release()` 함수가 락을 반환한다.

```
aquire() {
  while (!available) {
    /* busy state */
  }
  available = false;
}

release() {
  available = true;
}

// mutex lock을 사용한 방법

while (true) {
  /* aquire lock */
  
  critical section
  
  /* release lock */
  
  remainder section
}
```

* **busy waiting**

프로세스가 임계구역에 있는 동안 임계구역에 들어가기 원하는 다른 프로세스들은 `aquire()`함수를 무한히 호출하게 된다.

이것은 하나의 CPU코어가 여러 프로세스에서 공유되는 multiprogramming 시스템에서 문제가 된다.

* **spin lock**

위에서 설명한 락을 `spin lock`이라고 한다.

스핀 락은 프로세스가 락을 기다려야 하므로 문맥교환이 일어나지 않는다.

* * *

# 6.6 세마포(semaphores)

세마포 S는 정수 변수로서, 두 개의 원자적 연산인 `wait()`와 `signal()`로만 접근할 수 있다.

```
wait(S) {
  while (S <= 0) {
    // busy wait
  }
  S--;
}

signal(S) {
  S++;
}
```

* **counting semaphore**

S의 값이 제한이 없다.

* **binary semaphore**

S값은 0과 1로만 가능하다.

* **세마포의 다른 구현**

위에서 정의한 wait()와 signal()을 다시 정의해보자

프로세스가 wait()연산을 실행하고 세마포 값이 양수가 아닌 것을 발견한다면, 프로세스가 바쁜 대기를 하는 대신에

자신을 일시중지 시키고 대기 큐에 넣어 대기 상태로 전환한다.

일시 중지된 프로세스는 다른 프로세스가 signal() 연산을 실행하면 waikup() 연산에 의해 재시작 된다.

이때 프로세스의 상태를 대기에서 준비상태로 변경한다. 그리고 프로세스는 준비 큐에 넣어진다.

* * *

# 6.7 모니터(monitors)

* * *

# 6.8 라이브니스(liveness)




