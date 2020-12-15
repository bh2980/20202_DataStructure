# 20202_Data_Structure
2020년 2학기에 수강한 자료구조(COME331002) 과목 코드 정리

### 200815 : C 프로그래밍 테스트 / 포인터
```
- 이름(이름, 성 순서), 나이, 성별을 입력받아 이를 출력하는 프로그램 작성
- stop을 입력하면 입력 중단
- 포인터 사용할 것

```
### 200902 : C 프로그래밍 테스트 / 포인터
```
- 2x10의 정수를 입력받아 이를 오름차순으로 정렬하는 프로그램을 작성
- 같은 숫자는 한번만 출력될 것
```
### 200909 : C 프로그래밍 테스트 / 구조체 및 동적할당
```
- 한 클래스의 학생들의 정보(성, 나아ㅣ)와 성적(수학, 영어, 역사)을 파일로 입력받고 
  구조체와 동적메모리 할당을 이용하여 저장한 후, 사용자의 요구에 따라 출력하는 프로그램을 작성
- 정렬의 기준은 모두 오름차순이나 성, 나이, 과목 성적을 선택하여 선택한 값을 기준으로 정렬할 것
```
### 200915 : Stack
```
- Stack_Array.h : 배열을 이용한 스택 헤더파일
- Stack_List.h : List 구조를 이용한 스택 헤더파일
- Convert.c : 입력받은 10진수를 2진수로 변환하여 출력하는 프로그램
- Reverse.c : 정수를 차례대로 입력받아 이를 역순으로 출력하는 프로그램
- Calculator.c : 답이 양의 정수이며 괄호, +, -, *, %로 이루어진 임의의 식을 입력받아 결과값을 출력하는 프로그램
```
### 200930 : 정렬 List
```
- List_Array.h : array를 통해 구현한 정렬 list 헤더파일
- List_Link.h : linked-lsit를 통해 구현한 정렬 list 헤더파일
- NumberOrder.c : 위 헤더파일을 이용하여 입력되는 정수에 대한 오름차순 정렬을 출력하는 프로그램
```
### 201006 : Queue
```
- Queue_array.h : array로 구현한 큐 구조 헤더파일
- Queue_Link : Linked list로 구현한 큐 구조 헤더파일
- BankSystem.c : 큐 구조를 구현한 은행의 손님 처리 프로그램
```
### 201012 : Stack을 이용한 2진수 변환 프로그램
```
Stack을 이용하여 10진수를 입력받아 2진수로 저장하는 프로그램

- Converter2.c : 10진수를 2진수로 변환하여 Stack에 저장하고 출력하는 프로그램
- Stack_Link.h : Linked List로 구현된 Stack 구조 헤더파일
```
### 201023 : Stack과 Queue를 이용한 10진수 8진수 변환 프로그램
```
####중간고사
Stack과 Queue를 사용하여 10진수를 8진수로 변환하는 프로그램
8진수 변환 시 Stack 구조를 사용하고 이를 Queue에 저장함
```
### 201107 : Graph
```
- Ad_Matrix.h : 행렬을 통해 그래프를 구현한 헤더파일
- Ad_List.h : Linked list를 통해 그래프를 구현한 헤더파일
- Ad_Matrix3.h : Ad_Matrix3.h에 가중치를 추가로 구현한 그래프 헤더파일
- Ad_Queue.h : Graph 구조에 사용되는 Queue 헤더파일
- graph.c : 파일로 입력받은 그래프에 대하여 DFT, BFT, shortest path,
            그리고 minimum spanning tree를 출력하는 프로그램

- test.txt : directed graph 입력파일
- test2.txt : 가중체가 포함된 undirected graph 입력파일
```
### 201109 : Binary Tree
```
- Binary_Tree.h : 이진 트리 구조를 구현한 헤더파일
- Tree_Queue.h : 이진 트리 구조에 필요한 Queue 구조 헤더 파일
- TreeOrder.c : 이진트리를 통해 입력받은 문자열을 DFT(preorder, inorder, postorder), BFT로 출력하는 프로그램
```
### 201122 : Search & Sort
```
- Binary_Search.h : 이진 탐색을 구현한 헤더파일.
- Hashed_Search.h : Hashed Search를 구현한 헤더파일
- SortWay.h : Selection Sort, Insertion Sort, Bubble Sort, Quick Sort, Merge Sort를 구현한 헤더파일
- 1_main.c : 파일로 입력받은 정수들에 대해서 원하는 정수가 있는지 여부를 알려주는 프로그램
- 2_main.c : 임의의 정수열을 입력받아 이를 오름차순으로 배열해주는 프로그램

- test.txt, test2.txt, test3.txt : 150개의 임의의 정수를 배열한 입력파일
```
### 201128 : Graph / Binary Search Tree
```
####기말고사
```
