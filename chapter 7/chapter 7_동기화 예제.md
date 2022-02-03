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

* **the dining philosophers problem**

* * *

# 7.2 커널 안에서의 동기화

