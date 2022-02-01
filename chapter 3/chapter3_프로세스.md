# 3.1 프로세스 개념 

* **process**

`프로세스`란 실행 중인 프로그램을 말한다.

디스크 또는 SSD에 있는 프로그램을 실행하기 위해서 운영체제는 첫 번째로 `프로그램 코드`와 `정적 데이터`를 메모리에 탑재한다.

코드와 데이터가 메모리에 탑재된 후, 운영체제는 `스택`과 `힙`을 위한 메모리를 할당한다.

그리고 운영체제는 입출력과 관계된 초기화 작업을 수행한다.

```
// 프로세스 메모리 배치

* argc, argv
* 스택 : 함수를 호출할 때 임시로 데이터를 저장
* 힙 : 프로그램 실행중에 동적으로 할당되는 메모리
* 데이터 : 초기화된 데이터와 초기화되지 않은 데이터
* 텍스트 : 코드
```

* **process state**

프로세스는 실행되면서 `state`가 변한다.

```
* 생성(new)
* 실행(running) : 프로세스가 명령어를 실행하는 중이다.
* 대기(waiting) : 입출력등을 기다리는 동안 프로세스의 수행을 중단
* 준비(ready) : 운영체제가 다른 프로세스를 실행하는 등의 이유로 대기
* 종료(terminated)
```

* **process control block(PCB)**

각 프로세스는 운영체제에서 `프로세스 제어 블록(process control block, PCB)`에 의해 표현된다.

```
* process state
* program counter
* CPU registers
* CPU scheduling information
* memory management information
* accounting information
* I/O status information
```

* * *

# 3.2 프로세스 스케줄링

`multiprogramming`의 목적은 CPU를 최대한 이용하기 위해 항상 어떤 프로세스가 실행되도록 하기 위함이다.

`time sharing`의 목적은 각 프로그램이 실행되는 동안 user가 각각의 프로그램과 상호작용 할 수 있도록 프로세스들 사이에서 CPU코어를 자주 교체하기 위함이다.

* **process scheduler**

`프로세스 스케줄러`는 CPU에서 실행할 수 있는 프로세스 중에서 하나의 프로세스를 선택하는 것이다.

각 CPU 코어는 한 번에 하나의 프로세스를 실행할 수 있다.

프로세스가 시스템에 들어가면 `ready queue`에 들어가서 준비 상태가 되어 CPU 코어에서 실행되기를 기다린다.

I/O 완료와 같은 특정 이벤트가 발생하기를 기다리는 프로세스는 `wait queue`에 삽입된다.

`CPU 스케줄러`의 역할은 ready queue에 있는 프로세스 중에서 하나를 선택하여 CPU 코어를 할당하는 것이다.

* **context switch**

프로세스의 `context`는 PCB에 의해 표현된다.

interrupt가 발생하면, 시스템은 실행중인 프로세스의 현재 context를 저장하고, 나중에 다시 실행될 때 그 context를 복구한다.

CPU 코어를 다른 프로세스로 교환하려면 이전의 프로세스의 상태를 보관하고 새로운 프로세스의 보관된 상태를 복구하는 작업이 필요한데, 이를 `context switch`라고 한다.

* * *

# 3.3 프로세스에 대한 연산

* **pid**

실행되는 동안 프로세스는 여러 개의 새로운 프로세스들을 생성 할 수 있다.

생성하는 프로세스를 `부모 프로세스`라고 하고 새로운 프로세스를 `자식 프로세스`라고 한다.

운영체제는 `프로세스 식별자(pid)`를 사용하여 프로세스를 구분하는데 보통 정수 값이다.

* **fork()**

`UNIX`에서 각 프로세스는 `fork()`로 생성된다. 새로운 프로세스는 원래 프로세스의 주소 공간의 `복사본`으로 구성된다.

`fork()`로부터 부모 프로세스는 생성된 자식 프로세스의 pid값을 반환받고, 자식 프로세스는 0을 반환받는다.

자신의 pid는 `getpid()`로 알 수 있다.

* **exec()**

`fork()` 시스템 콜 다음에 두 프로세스 중 한 프로세스가 `exec()` 시스템 콜을 사용하여 자신의 메모리 공간을 새로운 프로그램으로 교체할 수 있다.

* **wait()**

부모는 `wait()` 시스템 콜로 자식 프로세스가 끝나기를 기다릴 수 있다.

자식 프로세스가 끝나면, 부모 프로세스는 wait() 호출로부터 재개하여, `exit()` 시스템 콜을 사용하여 끝낸다.

* **exit()**

프로세스가 `exit()` 시스템 콜을 사용하여 운영체제에 지신의 삭제를 요청하면 종료한다.

이 시점에서, 프로세스는 자신을 기다리고 있는 부모 프로세스에(wait 시스템 콜을 통해) 상태 값을 반환할 수 있다.

부모는 아래와 같은 이유들로 자식 중 하나의 실행을 종료할 수 있다.

```
1. 자식이 자신에게 할당된 자원을 초과하여 사용할 때
2. 자식에게 할당된 태스크가 더 이상 필요 없을 때
3. 부모가 exit 하는데, 운영체제가 부모가 exit한 후에 자식이 실행을 계속 하는 것을 허용하지 않는 경우
```

`zombie process` : a process that has terminated, but whose parent has not yet called wait()

`orphan process` : a process that has a parent process who did not invoke wait() and instead terminated.

* * *

# 3.4 프로세스 간 통신

`cooperating processes`는 데이터를 서로 교환할 수있는 `IPC(interprocess communication)` 기법이 필요하다.

`IPC`에는 기본적으로 `shared memory`와 `message passing`의 두 가지 모델이 있다.

* * *

# 3.5 공유 메모리 시스템에서의 프로세스 간 통신

* **shared memory**

공유 메모리 영역은 공유 메모리 세그먼트를 생성하는 프로세스의 주소 공간에 위치한다.

이 공유 메모리 세그먼트를 이용하여 통신하고자 하는 다른 프로세스들은 이 세그먼트를 자신의 주소 공간에 추가해야 한다.

일반적으로 운영체제는 한 프로세스가 다른 프로세스의 메모리에 접근하는 것을 금지하지만, 공유 메모리는 둘 이상의 프로세스가 접근할 수 있다.

데이터의 형식과 위치는 프로세스에 의해 결정되며 운영체제가 관리하지 않는다.

* **producer-consumer problem**

`생산자 프로세스(producer process)`는 정보를 생산하고, `소비자 프로세스(consumer process)`는 정보를 소비한다.

일반적으로 서버를 생산자로 클라이언트를 소비자로 생각할 수 있다.

생산자 - 소비자문제의 해결책 중 하나는 공유 메모리를 사용하는 것이다.

* **buffer**

생산자와 소비자 프로세스가 동시에 실행되도록 하려면, 생산자가 정보를 채워 넣고 소비자가 소모할 수 있는 항목들의 버퍼가 필요하다.

이 버퍼는 생산자와 소비자가 공유하는 메모리 영역에 존재하게 된다.

> `무한 버퍼(unbounede buffer)`
>  
>  버퍼의 크기에 한계가 없다. 버퍼가 비어있으면 소비자는 대기해야 하지만, 생산자는 항상 새로운 항목을 생산가능하다.

> `유한 버퍼(bounded buffer)` 
> 
> 버퍼의 크기가 고정되어 있다고 가정한다. 버퍼가 비어 있으면 소비자가 대기해야 하고, 모든 버퍼가 채워져 있으면 생산자가 대기한다. 

```
/* 
 * in : 다음으로 비어있는 위치
 * out : 첫 번째로 채워져 있는 위치
 * in == out 이면 버퍼가 비어있고
 * ((in + 1) % BUFFER_SIZE) == out 이며 버퍼가 가득 차 있다.
 */
 
# define BUFFER_SIZE 10

typedef struct {
  ...
} item;

item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
```

```
item next_produced;
while (true) {
  /* produce an item in next_produced */
  
  while (((in + 1) % BUFFER_SIZE) == out ) {
    // do nothing
  }
  
  buffer[in] = next_produced;
  in = (in + 1) % BUFFER_SIZE);
}

item next_consumed;
while (true) {
  
  while (in == out) {
    // do nothing
  }
  
  next_consumed = buffer[out];
  out = (out + 1) % BUFFER_SIZE;
  
  /* consume the item in next_consumed */
}
```

* * *

# 3.6 메세지 전달 시스템에서의 프로세스간 통신

* **message passing**

`메세지 전달 방식`은 동일한 주소 공간을 공유하지 않고도 프로세스들이 통신을 하고, 동기화 할 수 있게 한다.

* **communication link**

프로세스 P와 Q가 통신을 원하면, 서로 메세지를 주고 받을 수 있는 `통신 연결`이 필요하다.

```
* 직접 또는 간접 통신
* 동기식 또는 비동기식 통신
* 자동 또는 명시적 버퍼링
```

* **direct communication**

통신을 원하는 각 프로세스는 통신의 수신자 또는 송신자의 이름을 명시해야 한다.

직접 통신은 송신자와 수신자 프로세스 모두 이름을 알아야 하는 `대칭 통신`과 송신자만 수신자 이름을 알면 되는 `비대칭 통신`으로 구분된다.

직접 통신은 다음의 특성을 가진다.

1. 통신을 원하는 프로세스들은 연결이 자동으로 구축된다. (상대방의 신원만 알면 가능)
2. 연결은 정확히 두 프로세스 사이에만 연관된다.
3. 두 프로세스 사이에 정확히 하나의 연결만 존재해야 한다.

* **indirect communication**

메세지들은 `mailbox` 또는 `port`로 송신되고 수신된다.

`mailbox(port)`는 프로세스에 의해 메세지가 넣어지고, 제거될 수 있는 객체라고도 볼 수 있다.

`send(A, message)` : 메세지를 메일박스 A로 전송한다.

`receive(A, message)` : 메세지를 메일박스 A로부터 수신한다.

`간접 통신`은 다음의 특성을 가진다.

1. 한 쌍의 프로세스들 사이의 연결은 공유 메일박스를 가질 때만 구축된다.
2. 연결은 두 개 이상의 프로세스들과 연관될 수 있다.
3. 통신하는 프로세스들 사이에는 다수의 연결이 존재할 수 있고, 각 연결은 하나의 메일박스에 대응된다.

메일박스는 한 프로세스 또는 운영체제에 의해 소유될 수 있다.

* **synchronization**

`blocking send`

송신하는 프로세스는 메시지가 프로세스 또는 메일박스에 수신될 때까지 봉쇄됨.

`nonblocking send`

송신하는 프로세스가 메세지를 보내고 작업을 재개.

`blocking receive`

메세지가 이용 가능할 때까지 수신하는 프로세스가 봉쇄됨.

`nonblocking receive`

수신하는 프로세스가 유효한 메세지 또는 NULL을 받는다.

* **buffering**

`zero capacity`

큐의 길이가 0이기 때문에 송신 프로세스는 수신 프로세스가 메세지를 수신할 때까지 기다려야 한다.

`bounded capacity`

큐의 길이가 유한하다. 즉, n개의 메세지를 넣을 수 있다.

n개가 넘어간다면, 송신자는 큐가 이용 가능할 때까지 봉쇄된다.

`unbounded capacity`

큐의 길이가 무한하다. 송신자는 봉쇄되지 않는다.

* * *

# 3.7 IPC 시스템의 사례

* **POSIX shared memory**

POSIX 공유 메모리는 `memory-mapped files`를 사용하여 구현된다.

memory-mapped files는 공유 메모리의 특정 영역을 파일과 연관시킨다.

프로세스는 `shm_open()` 시스템 콜을 사용하여 공유 메모리 객체를 생성해야 한다.

```
// name : 공유 메모리 객체의 이름을 지정.
// O_CREAT : 객체가 존재하지 않으면 생성
// O_RDWR : 객체가 읽기와 쓰기가 가능한 상태로 열림
// 0666 : 공유 메모리 객체에 파일 접근 허가권을 부여

fd = shm_open(name, O_CREAT | O_RDWR, 0666);
```

객체가 설정되면 `ftruncate()`함수를 사용하여 객체의 크기를 바이트 단위로 설정한다.

```
// 객체의 크기를 4096바이트로 설정한다.

ftruncate(fd, 4096);
```

`mmap()` 함수는 공유 메모리 객체에 접근할 때 사용될 memory-mapped file의 포인터를 반환한다.

* **pipes**

`파이프`는 두 프로세스가 통신할 수 있게 하는 전달자이다.

```
// Four issues of pipe implementaion

1. unidirectional or bidirectional?
2. in the case of bidirectional, half duplex or full duplex?
3. relationship such as parent-child
4. can the pipes communicate over a network?
```

* **ordinary pipes**

`일반 파이프`는 파이프를 생성한 프로세스 이외에는 접근할 수 없다.

단방향 통신만 지원하며 만일 양방향 통신이 필요하다면 두 개의 파이프를 사용해야 한다.

부모 프로세스가 파이프를 생성하고 `fork()`로 생성한 자식 프로세스와 통신하기 위해 사용한다.

* **named pipes**

`지명 파이프`는 양방향 통신이 가능하며 부모-자식 관계도 필요하지 않는다.

통신 프로세스가 종료하더라도 지명 파이프는 계속 존재할 수 있다.

* * *

# 3.8 클라이언트 서버 환경에서 통신

* **socket**

`소켓`은 통신의 `endpoint`를 의미한다.

두 프로세스가 네트워크상에서 통신을 하려면 양 프로세스마다 하나씩, 총 두개의 소켓이 필요하다.

각 소켓은 `IP주소`와 `포트 번호`를 연결하여 구분한다.

```
// Java는 세 가지 종류의 소켓을 제공한다.

1. Socket class : connection-oriented(TCP)
2. DatagramSocket class : connectionless(UDP)
3. MulticastSocket class : multiple recipients
```



