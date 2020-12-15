모든 문제는 Stack_Array.h, Stack_Link.h를 공유합니다.

앞의 include에서 주석처리에 따라 사용하는 헤더 파일이 바뀝니다.

#include "Stack_Array.h"
//#include "Stack_Link.h"

-> Stack_Array.h로 컴파일

//#include "Stack_Array.h"
#include "Stack_Link.h"

-> Stack_Link.h로 컴파일