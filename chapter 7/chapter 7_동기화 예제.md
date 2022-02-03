# 7.1 고전적인 동기화 문제들

* **the bounded buffer problem**

소비자 생산자 문제에서 유한 버퍼를 가지고 있다면

소비자와 생산자는 다음과 같은 자료구조를 공유한다.

```
int n;
semaphore mutex = 1;
semaphore empty = n;
semaphore full = 0;
```

생산자 코드

```
while (true) {
  /* produce an item in next_produced */
  . . .
  wait(empty);
  wait(mutex);
  . . .
  /* add next_produced to the buffer */
  . . .
  signal(mutex);
  signal(full);
}
```

소비자 코드

```
while (true) {
  wait(full);
  wait(mutex);
  . . .
  /* remove an item from buffer to next_consumed */
  . . .
  signal(mutex);
  signal(empty);
  . . .
  /* consume the item in next_consumed */
  . . .
}
```

* **the readers-writers problem**

하나의 데이터베이스가 다수의 병행 프로세스간에 공유된다고 하자.

어떤 프로세스는 데이터베이스의 내용을 읽기만 하고, 어떤 프로세스는 쓰기만 한다.

이를 각각 `readers`와 `writers`라고 한다.

> the first readers-writers problem

단순히 writer가 기다린다고 해서, 어느 reader도 기다리게 해서는 안된다.

다시 말하면, 기다리는 reader가 없어야 writer가 진입할 수 있다.

```
semaphore rw_mutex = 1;
semaphore mutex = 1;
int read_count = 0;

// writer
while (true) {
  wait(rw_mutex);
  . . .
  /* writing is performed */
  . . .
  signal(rw_mutex)
}

// reader
while (true) {
  wait(mutex);
  read_count++;
  if (read_count == 1) {
    wait(rw_mutex);
  }
  signal(mutex);
  . . .
  /* reading is performed */
  . . .
  wait(mutex);
  read_count--;
  if (read_count == 0) {
    signal(rw_mutex);
  }
  signal(mutex);
}
```

> the second readers-writers problem

writer가 기다리고 있다면, reader들은 기다려야 한다.

* **the dining philosophers problem**

* * *

# 7.2 커널 안에서의 동기화

