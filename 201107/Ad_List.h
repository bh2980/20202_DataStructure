#include <stdio.h>
#include <stdlib.h>
#include "Ad_Queue.h"

/*
Vertex List를 먼저 만들까?
아니면 Vertex List를 만들면서 연결할까 (이거)

graph 구조체
vertex 개수
vertex List 주소 = 루트노드
방향

Vertex List Node
좌 값 우

좌 : 노드 리스트
우 : 연결된 노드

Adjency List Node
값 가중치(X) next
*/

typedef char Element;

typedef struct ad {
	Element value;
	struct ad* next;
}adListNode;

typedef struct ve {
	struct ve* vlistnext;
	Element value;
	adListNode* adnext;
	int processed;
}vListNode;

typedef struct {
	int vNum;
	vListNode* vList;
	Element root;
	short direct;
}Graph;

void addNode(Element to, Element add, Graph* pGraph);

Graph* createGraph(short direct, Element root) {
	Graph* pGraph = (Graph*)calloc(1, sizeof(Graph));
	if (!pGraph) {
		printf("malloc failed\n");
		return NULL;
	}

	pGraph->direct = direct;
	pGraph->root = root;

	return pGraph;
}

Graph* createFileGraph(short direct) {
	char ch, add;

	char filename[100];
	printf("File name if a graph : ");
	gets(filename);

	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Open Filed\n");
		return 0;
	}

	ch = getc(fp);//root 설정

	Graph* pGraph = createGraph(direct, ch);
	getc(fp);

	int cn = fscanf(fp, "%c %c\n", &ch, &add);

	while (cn > 0) {//노드 입력
		addNode(ch, add, pGraph);
		cn = fscanf(fp, "%c %c\n", &ch, &add);
	}

	fclose(fp);

	return pGraph;
}

vListNode* searchVertex(Element data, vListNode* root) {
	if (!root) {
		return NULL;
	}

	if (root->value == data) {
		return root;
	}

	return searchVertex(data, root->vlistnext);
}

adListNode* searchAdjency(Element data, vListNode* root) {
	adListNode* tmp = root->adnext;

	while (tmp) {
		if (tmp->value == data) {
			break;
		}
		tmp = tmp->next;
	}

	return tmp;
}

void addNode(Element to, Element add, Graph* pGraph) {
	//vertex list 추가

	if (isNullGraph(pGraph)) {
		vListNode* newNode = (vListNode*)calloc(1, sizeof(vListNode));
		if (!newNode) {
			printf("malloc failed\n");
			return;
		}

		newNode->value = to;

		newNode->vlistnext = pGraph->vList;
		pGraph->vList = newNode;
		pGraph->vNum++;
	}
	else {//그래프안에 뭐가 있다면
		if (!searchVertex(to, pGraph->vList)) {//vertex에 to가 없다면
			vListNode* newNode = (vListNode*)calloc(1, sizeof(vListNode));
			if (!newNode) {
				printf("malloc failed\n");
				return;
			}

			newNode->value = to;

			newNode->vlistnext = pGraph->vList;
			pGraph->vList = newNode;
			pGraph->vNum++;
		}

		if (!searchVertex(add, pGraph->vList)) {//vertex에 add가 없다면
			vListNode* newNode = (vListNode*)calloc(1, sizeof(vListNode));
			if (!newNode) {
				printf("malloc failed\n");
				return;
			}

			newNode->value = add;

			newNode->vlistnext = pGraph->vList;
			pGraph->vList = newNode;
			pGraph->vNum++;
		}
	}

	//adjenct list 추가
	//모든 to 존재

	vListNode* tmp = searchVertex(to, pGraph->vList);
	if (!searchAdjency(add, tmp)) {//to에 add가 없다면
		adListNode* newNode = (adListNode*)calloc(1, sizeof(adListNode));
		if (!newNode) {
			printf("malloc failed\n");
			return;
		}

		newNode->value = add;

		newNode->next = tmp->adnext;
		tmp->adnext = newNode;
	}

	return;
}

int isNullGraph(Graph* pGraph) {
	if (!pGraph->vNum) return 1;
	else return 0;
}

void ordervList(Graph* pGraph) {
	vListNode* tmp = pGraph->vList;

	for (int i = 0; i < pGraph->vNum; i++) {
		tmp = pGraph->vList;
		for (int j = 1; j < pGraph->vNum - i; j++) {
			if (tmp->value > tmp->vlistnext->value) {
				Element etmp = tmp->value;
				int epro = tmp->processed;
				adListNode* adtmp = tmp->adnext;

				tmp->value = tmp->vlistnext->value;
				tmp->processed = tmp->vlistnext->processed;
				tmp->adnext = tmp->vlistnext->adnext;

				tmp->vlistnext->value = etmp;
				tmp->vlistnext->processed = epro;
				tmp->vlistnext->adnext = adtmp;
			}

			tmp = tmp->vlistnext;
		}
	}

	return;
}

void whatTheGraph(Graph* pGraph) {
	//너는 완벽함.
	ordervList(pGraph);

	vListNode* tmp = pGraph->vList;

	while (tmp) {
		printf("%c : ", tmp->value);
		adListNode* tmp2 = tmp->adnext;
		while (tmp2) {
			printf("%c ", tmp2->value);
			tmp2 = tmp2->next;
		}
		tmp = tmp->vlistnext;
		printf("\n");
	}

	printf("\n");

	return;
}

void resetPrecessGraph(Graph* pGraph) {
	vListNode* tmp = pGraph->vList;

	while (tmp) {
		tmp->processed = 0;
		tmp = tmp->vlistnext;
	}

	return;
}

void depthFirstTraversal(vListNode* root) {
	if (!root) {
		return;
	}

	if (!root->processed) {
		printf("%c ", root->value);
		root->processed = 1;
	}

	adListNode* tmp = root->adnext;

	while (tmp) {//tmp가 NULL아 아닌 동안
		depthFirstTraversal(searchVertex(tmp->value, root));
		tmp = tmp->next;
	}

	return;
}

void dftGraph(Graph* pGraph) {
	//root에서 시작해서
	//adjecny list를 따라가면서 있을 때 마다 같은 이름의 vlistnode 호출
	//만약 adjencylist next가 NULL이라면 return

	depthFirstTraversal(searchVertex(pGraph->root, pGraph->vList));

	resetPrecessGraph(pGraph);
}

void bftGraph(Graph* pGraph) {
	Queue* tmp = CreateQueue(100);

	EnQ(tmp, pGraph->root);

	while (!IsNullQ(tmp)) {
		vListNode* tmp2 = searchVertex(DeQ(tmp), pGraph->vList);//꺼낸 글자와 같은 vertexNode를 찾는다.

		if (!tmp2->processed) {
			printf("%c ", tmp2->value);
			tmp2->processed = 1;
		}

		adListNode* tmp3 = tmp2->adnext;//그 verTexNode의 adnex를 훑는다.
		while (tmp3) {
			EnQ(tmp, tmp3->value);//훑으면서 EeQ한다.
			tmp3 = tmp3->next;
		}
	}

	resetPrecessGraph(pGraph);

	//큐에는 글자가 들어감.
	//DeQ하면서 꺼낸 값과 같은 vertexListNode를 찾는다
	//이 노드에서 adjencylist를 끝까지 훑으면서 모든 value값 EnQ
	//꺼낼 때 꺼낸 value 값이랑 같은 vertex에 있는 adjecylist를 훑으면서 모든 value값 EnQ
}

void deleteNode(Element e, Graph* pGraph) {
	//Vertex를 찾아서 제거

	if (e == pGraph->root) {//root vertex 삭제시 root값을 root값에 연계되어있는 값으로 바꿔줌.
		if (searchVertex(pGraph->root, pGraph->vList)->adnext)
			pGraph->root = searchVertex(pGraph->root, pGraph->vList)->adnext->value;

		if (pGraph->root == e) pGraph->root = pGraph->vList->vlistnext->value;
		//그래도 e랑 같다면 그냥 vList 그다음의 값을 넣어줌.
	}

	vListNode* prenode = NULL;
	vListNode* tmp = pGraph->vList;

	while (tmp) {
		if (tmp->value == e) {
			break;
		}

		prenode = tmp;
		tmp = tmp->vlistnext;
	}

	while (tmp->adnext) {//딸린거 삭제
		adListNode* tmp2 = tmp->adnext;
		tmp->adnext = tmp2->next;
		free(tmp2);
	}

	if (!prenode) {//제일 첫 노드
		prenode = pGraph->vList;
		pGraph->vList = prenode->vlistnext;
		free(prenode);
	}
	else {//첫노드 아님
		prenode->vlistnext = tmp->vlistnext;
		free(tmp);
	}

	pGraph->vNum--;

	//adjency list에서 찾아서 삭제

	tmp = pGraph->vList;

	while (tmp) {

		adListNode* tmp3 = tmp->adnext;
		adListNode* pre2 = NULL;

		while (tmp3) {
			if (tmp3->value == e) {
				break;
			}
			pre2 = tmp3;
			tmp3 = tmp3->next;
		}

		if (tmp3 != NULL) {
			if (!pre2) {//첫 노드 = pre2 = NULL
				pre2 = tmp->adnext;
				tmp->adnext = pre2->next;
				free(pre2);
			}
			else {
				pre2->next = tmp3->next;
				free(tmp3);
			}
		}

		tmp = tmp->vlistnext;
	}

	return;
}

void destroyGraph(Graph* pGraph) {
	while (pGraph->vList) {
		while (pGraph->vList->adnext) {
			adListNode* tmp2 = pGraph->vList->adnext;
			pGraph->vList->adnext = tmp2->next;
			free(tmp2);
		}
		vListNode* tmp = pGraph->vList;
		pGraph->vList = tmp->vlistnext;
		free(tmp);
	}

	return;
}