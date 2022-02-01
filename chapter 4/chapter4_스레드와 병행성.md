# 4.1 개요

* **thread**

`스레드`는 CPU 이용의 기본 단위이다.

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

* **programming challenges**

```
* identifying tasks : find areas can be divided into seperate tasks
* balance : ensure the tasks to perform equal to work of equal value
* data spliting : data must be divided to run on seperate cores
* data dependency : ensure that the excution of tasks is synchronized to accomodate the data dependency
* testing and debugging
```

* **types of parallelism**

`데이터 병렬 실행`과 `태스크 병렬 실행`이 존재한다.

* * *

# 4.3 다중 스레드 모델(multithreading models)

`user threads`와 `kernel threads`가 존재한다.

* **many-to-one model**

user threads를 하나의 kernel thread로 연결한다.

현재는 쓰이고 있지 않다.

* **one-to-one model**

각 user thread가 각 kernel thread로 연결한다.

단점은 user thread를 만들려면 kernel thread를 만들어야 한다는 것이다.

* **many-to-many model**

여러개의 user threads가 같거나 작은 수의 kernel threads와 연결된다.

또한 하나의 user thread가 하나의 kernel thread에만 연결되도록 하는 것도 허용한다. 이를 `two-level model`이라고 한다.

* * *

# 4.4 스레드 라이브러리(threads library)

* **asynchronous threading**

부모가 자식 스레드를 생성한 이후 서로 병행적으로 실행된다.

스레드 사이의 데이터 공유는 거의 없다.

* **synchronous threading**

부모 스레드가 하나 이상의 자식 스레드를 생성하고 모두 종료할 때까지 기다렸다가 실행한다.

자식 스레드들은 병행하게 실행하지만, 부모는 모든 자식이 끝나야 실행한다.

동기 스레딩은 상당한 양의 데이터 공유를 수반한다.

```
POSIX pthreads
Windows threads
Java threads
```

* * *

# 4.5 암묵적 스레딩(implicit threading)

다중 코어 시스템에서 다중 스레드를 설계하는 것이 매우 어렵기 때문에 `컴파일러`와 `런타임 라이브러리`에게 넘겨준다.

이를 `암묵적 스레딩`이라고 한다.

* **thread pools**

프로세스를 시작할 때 일정한 수의 스레드를 미리 풀로 만들어두는 것이다.

* **fork & join**

메인 부모 스레드가 자식을 생성(fork)한 다음 자식의 종료를 기다린 후 join하고 그 시점부터 자식의 결과를 확인

암묵적 스레딩에서도 활용된다.

* **OpenMP**

C/C++ 또는 fortran으로 작성된 API와 컴파일러 디렉티브의 
