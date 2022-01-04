# 4.1 개요

* **thread**

`스레드`는 CPU 이용의 기본 단위이다.

thread ID, program counter, register set, stack으로 구성되어 있다.

스레드는 같은 프로세스에 속한 다른 스레드와 코드, 데이터 섹션, 열린 파일이나 신호와 같은 운영체제 자원들을 공유한다.

프로세스가 다수의 제어 스레드를 가진다면, 프로세스는 동시에 하나 이상의 작업을 할 수 있다.

* **the benefits of multithreaded programming**

```
* responsiveness : 사용자에 대한 응답성이 증가한다.
* resource sharing : 스레드는 프로세스의 자원을 공유하기 때문에 더 편리하다.
* economy : 프로세스를 생성하는 것보다 경제적이다.
* scalability : multiprocessor architecture의 장점을 얻을 수 있다.
```

* * *

# 4.2 다중 코어 프로그래밍(multicore programming)

