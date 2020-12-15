Stack

Stack 구조를 구현하고 이를 이용하여 문제를 풀 것
- Stack_Array.h : 배열을 이용한 스택 헤더파일
- Stack_List.h : List 구조를 이용한 스택 헤더파일
- Convert.c : 입력받은 10진수를 2진수로 변환하여 출력하는 프로그램
- Reverse.c : 정수를 차례대로 입력받아 이를 역순으로 출력하는 프로그램
- Calculator.c : 답이 양의 정수인 임의의 식을 입력받아 결과값을 출력하는 프로그램

-------------------------------------------------------------------

모든 문제는 Stack_Array.h, Stack_Link.h를 공유합니다.

앞의 include에서 주석처리에 따라 사용하는 헤더 파일이 바뀝니다.

#include "Stack_Array.h"
//#include "Stack_Link.h"

-> Stack_Array.h로 컴파일

//#include "Stack_Array.h"
#include "Stack_Link.h"

-> Stack_Link.h로 컴파일
