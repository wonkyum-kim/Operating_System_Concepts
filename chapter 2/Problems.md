# 2.1

시스템 콜의 목적은 실행 중인 프로그램(사용자 공간)과 운영 체제(커널 공간) 간의 인터페이스를 제공하는 것입니다.
# 2.2

명령 인터프리터는 사용자나 명령 파일에서 명령을 읽고 일반적으로 하나 이상의 시스템 콜로 변환하여 실행합니다.

명령 해석기는 변경될 수 있으므로 일반적으로 커널의 일부가 아닙니다.

# 2.3

fork(), exec(), and wait()

# 2.4

시스템 프로그램의 목적은 프로그램 개발 및 실행을 위한 편리한 환경을 제공하는 것입니다.

# 2.5

계층형 접근 방식의 주요 장점은 구성 및 디버깅이 단순하다는 것입니다.

그러나 계층화된 접근 방식은 성능 오버헤드, 경직성, 기능 중복 및 계층 경계 정의 문제를 초래할 수 있습니다.

# 2.7 

임베디드 시스템과 같은 특정 장치의 경우 파일 시스템이 포함된 디스크를 해당 장치에 사용하지 못할 수 있습니다.

이 상황에서는 운영 체제를 펌웨어에 저장해야 합니다.

# 2.8

Windows와 세 가지 Linux 배포판을 모두 실행하려는 시스템을 생각해 보세요.

각 운영 체제는 디스크에 저장됩니다.

시스템 부팅 중에 부트 매니저가 부팅할 운영 체제를 결정합니다.

즉, 처음에 운영 체제로 부팅하는 대신 시스템 시작 중에 부트 매니저가 먼저 실행됩니다.

일반적으로 부트 매니저는 시스템 시작 중에 인식되도록 하드 디스크의 특정 위치에 저장되어야 합니다.

부트 매니저는 사용자에게 부팅할 시스템을 선택할 수 있는 기회를 제공하는 경우가 많습니다. 

또한 부트 매니저는 일반적으로 사용자가 선택 항목을 선택하지 않은 경우 기본 운영 체제로 부팅하도록 설계되었습니다.

부팅할 운영 체제를 선택한 후 부트스트랩 프로그램은 다음 작업을 수행해야 합니다.

- 커널 프로그램이 포함된 파일을 메모리에 로드합니다.
- 진단을 실행하여 머신 상태를 확인합니다(메모리 및 CPU 검사 및 장치 검색).
- CPU 레지스터부터 장치 컨트롤러 및 주 메모리의 내용까지 시스템의 모든 측면을 초기화합니다.
- 운영 체제를 시작하고 루트 파일 시스템을 마운트합니다.

# 2.10

1. 레지스터에 직접 전달
2. 메모리 내의 블록이나 테이블에 저장하고 주소를 레지스터에 전달
3. 스택에 전달

# 2.20

LKM을 사용하면 변경이 발생할 때마다 커널을 다시 컴파일 할 필요가 없습니다.