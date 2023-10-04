# 0. WSL2

WSL2를 설치하기 전에 먼저 반드시 윈도우 계정이 한글인지 확인해야 합니다.

한글은 인코딩 문제로 인해 경로를 입력할 때 문제가 발생하기 때문입니다.

윈도우 키를 누르면 왼쪽 아래에 계정 이름을 볼 수 있습니다.

만약 한글이라면 해결 방법은 두 가지가 있습니다.

1.  이름이 영어인 새로운 계정 만들기
2.  현재 계정 이름을 영어로 바꾸기

계정 이름을 영어로 바꾸는 방법은 [https://healthdevelop.tistory.com/entry/etc3](https://healthdevelop.tistory.com/entry/etc3) 여기서 확인할 수 있습니다.

자세한 설치와 설정 과정은 저의 [GitHub](https://github.com/wonkyum-kim/Operating_System_Concepts/blob/main/chapter%202/HowToCompileKernelModuleInWnidows.md)에 남겨두었습니다. (영어)

# 1. Kernel Modules Overview

`WSL2` 환경에서 `LKM(linux kernel module)`을 생성하고 불러오는 작업을 진행하였습니다.

현재 적재되어 있는 모든 커널 모듈의 목록은 `lsmod`를 통해 확인할 수 있습니다.

책에 있는 커널 모듈 `simple.c`를 살펴봅시다.

`printk()`는 커널에서 사용하는 `printf()` 이며 출력 결과는 커널 로그 버퍼로 보내지며 `dmesg` 명령어로 읽을 수 있습니다.

`printf()`와 다른 점은 우선순위 플래그를 명시할 수 있다는 것입니다.

예를 들어 `KERN_INFO`는 정보 메시지를 나타내는 우선순위 플래그입니다.

해당 커널 모듈을 컴파일 하려면 Makefile을 사용하여 다음 명령어를 입력합니다.

```shell
make
```

# 2. Loading and Removing Kernel Modules

`make`로 `simple.c`를 컴파일 하였다면 이제 `sudo insmod simple.ko`를 입력하여 커널을 적재할 수 있습니다.

적재가 제대로 되었는지 확인하기 위해 `lsmod`를 입력하여 `simple`을 확인해 볼 수 있습니다.

그리고 `dmesg`를 입력하여 커널 로그 버퍼를 확인해 볼 수도 있습니다.

불필요한 커널은 `sudo rmmod simple`를 입력하여 제거할 수 있습니다.

제거가 성공적으로 이루어졌는지 확인하기 위해 다시 `dmesg`를 입력하여 확인해봅니다.

커널 로그 버퍼는 빠르게 찰 수 있기 때문에 주기적으로 비워주는 것이 좋습니다.

```shell
sudo dmesg -c
```

# 3. The `/proc` File System

`/proc` 파일 시스템은 Linux 운영 체제에서 프로세스와 시스템 정보를 제공하기 위해 사용되는 가상 파일 시스템으로 커널 메모리에서만 존재합니다.

`hello.c`에서 다음을 입력하면 `Hello World`가 반환됩니다.

```shell
cat /proc/hello
```

`proc_read()` 함수를 살펴보면, `"Hello World\n"` 문자열은 커널 메모리에 있는 버퍼에 쓰이게 됩니다.

`/proc/hello`는 사용자 공간에서 접근할 수 있기 때문에 버퍼에 있는 문자열을 `copy_to_user()` 함수를 사용하여 사용자 공간에 복사합니다.

이 함수는 커널 메모리 버퍼에 있는 내용을 `usr_buf`에 복사합니다.

# 4. Makefile

WSL2에서 다음과 같이 Makefile을 작성할 수 있습니다.

```
obj-m += hello.o
all:
    make -C ../WSL2-Linux-Kernel M=`pwd` modules
clean:
    make -C ../WSL2-Linux-Kernel M=`pwd` clean
```

코드의 의미는 다음과 같습니다.

`"hello.o"`라는 객체 파일을 빌드할 커널 모듈 목록에 추가합니다.

그 다음으로 `make` 유틸리티를 사용하여 커널 모듈을 빌드하는데,

`-C` 플래그는 make 명령을 실행할 디렉터리를 나타내며

`M`은 현재 `Makefile`의 위치(pwd)를 나타냅니다.

modules는 빌드할 대상을 의미하고 clean은 제거할 대상을 의미합니다.

# 5. jiffies

`/proc/jiffies`을 만들고 현재 `jiffies`을 읽어보는 커널 모듈을 작성합니다.

https://github.com/wonkyum-kim/Operating_System_Concepts/blob/main/chapter%202/jiffies/jiffies.c

# 6.  seconds

`/proc/seconds`을 만들고 현재 경과된 시간(초)를 읽어보는 커널 모듈을 작성합니다.

현재 경과된 시간은 다음과 같이 구할 수 있습니다.

```
초 = jiffies / HZ 
```

https://github.com/wonkyum-kim/Operating_System_Concepts/blob/main/chapter%202/seconds/seconds.c
