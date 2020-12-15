#include <stdio.h>
#include <stdlib.h>
#include "Ad_Queue.h"

/*
Vertex List�� ���� �����?
�ƴϸ� Vertex List�� ����鼭 �����ұ� (�̰�)

graph ����ü
vertex ����
vertex List �ּ� = ��Ʈ���
����

Vertex List Node
�� �� ��

�� : ��� ����Ʈ
�� : ����� ���

Adjency List Node
�� ����ġ(X) next
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

	ch = getc(fp);//root ����

	Graph* pGraph = createGraph(direct, ch);
	getc(fp);

	int cn = fscanf(fp, "%c %c\n", &ch, &add);

	while (cn > 0) {//��� �Է�
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
	//vertex list �߰�

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
	else {//�׷����ȿ� ���� �ִٸ�
		if (!searchVertex(to, pGraph->vList)) {//vertex�� to�� ���ٸ�
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

		if (!searchVertex(add, pGraph->vList)) {//vertex�� add�� ���ٸ�
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

	//adjenct list �߰�
	//��� to ����

	vListNode* tmp = searchVertex(to, pGraph->vList);
	if (!searchAdjency(add, tmp)) {//to�� add�� ���ٸ�
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
	//�ʴ� �Ϻ���.
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

	while (tmp) {//tmp�� NULL�� �ƴ� ����
		depthFirstTraversal(searchVertex(tmp->value, root));
		tmp = tmp->next;
	}

	return;
}

void dftGraph(Graph* pGraph) {
	//root���� �����ؼ�
	//adjecny list�� ���󰡸鼭 ���� �� ���� ���� �̸��� vlistnode ȣ��
	//���� adjencylist next�� NULL�̶�� return

	depthFirstTraversal(searchVertex(pGraph->root, pGraph->vList));

	resetPrecessGraph(pGraph);
}

void bftGraph(Graph* pGraph) {
	Queue* tmp = CreateQueue(100);

	EnQ(tmp, pGraph->root);

	while (!IsNullQ(tmp)) {
		vListNode* tmp2 = searchVertex(DeQ(tmp), pGraph->vList);//���� ���ڿ� ���� vertexNode�� ã�´�.

		if (!tmp2->processed) {
			printf("%c ", tmp2->value);
			tmp2->processed = 1;
		}

		adListNode* tmp3 = tmp2->adnext;//�� verTexNode�� adnex�� �ȴ´�.
		while (tmp3) {
			EnQ(tmp, tmp3->value);//�����鼭 EeQ�Ѵ�.
			tmp3 = tmp3->next;
		}
	}

	resetPrecessGraph(pGraph);

	//ť���� ���ڰ� ��.
	//DeQ�ϸ鼭 ���� ���� ���� vertexListNode�� ã�´�
	//�� ��忡�� adjencylist�� ������ �����鼭 ��� value�� EnQ
	//���� �� ���� value ���̶� ���� vertex�� �ִ� adjecylist�� �����鼭 ��� value�� EnQ
}

void deleteNode(Element e, Graph* pGraph) {
	//Vertex�� ã�Ƽ� ����

	if (e == pGraph->root) {//root vertex ������ root���� root���� ����Ǿ��ִ� ������ �ٲ���.
		if (searchVertex(pGraph->root, pGraph->vList)->adnext)
			pGraph->root = searchVertex(pGraph->root, pGraph->vList)->adnext->value;

		if (pGraph->root == e) pGraph->root = pGraph->vList->vlistnext->value;
		//�׷��� e�� ���ٸ� �׳� vList �״����� ���� �־���.
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

	while (tmp->adnext) {//������ ����
		adListNode* tmp2 = tmp->adnext;
		tmp->adnext = tmp2->next;
		free(tmp2);
	}

	if (!prenode) {//���� ù ���
		prenode = pGraph->vList;
		pGraph->vList = prenode->vlistnext;
		free(prenode);
	}
	else {//ù��� �ƴ�
		prenode->vlistnext = tmp->vlistnext;
		free(tmp);
	}

	pGraph->vNum--;

	//adjency list���� ã�Ƽ� ����

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
			if (!pre2) {//ù ��� = pre2 = NULL
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