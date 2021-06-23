#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
typedef enum { head, entry } tagfield;
typedef struct matrix_node* matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
} entry_node;
typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		entry_node entry;
	} u;
} matrix_node;

matrix_pointer hdnode[MAX_SIZE];
matrix_pointer new_node();
matrix_pointer mread(FILE*);
void mwrite(matrix_pointer);
void merase(matrix_pointer*);  
int main()
{
	FILE* fp1, * fp2;
	fp1 = fopen("A.txt", "r");
	fp2 = fopen("B.txt", "r");
	//file open error 체크
	if (fp1 == NULL || fp2 == NULL) {
		printf("Check file A.txt or B.txt!");
		return 0;
	}
	matrix_pointer a, b;
	a = mread(fp1);
	b = mread(fp2);
	mwrite(a);
	mwrite(b);
	merase(&a);
	merase(&b);
	mwrite(a);
	mwrite(b);
	return 0;
}
//node 새로 할당 받기
matrix_pointer new_node() {
	matrix_pointer temp = (matrix_pointer)malloc(sizeof(matrix_node));
	temp->down = NULL;
	temp->right = NULL;
	return temp;
}
//.txt파일로부터 매트릭스 정보를 linked list 형태로 변환하여 저장하기
matrix_pointer mread(FILE* fp)
{
	int num_rows, num_cols, num_heads, i;
	int row, col, value, current_row;
	int temp_row=0, temp_col=0,res;
	matrix_pointer temp, last, node;
	fscanf(fp, "%d %d", &num_rows, &num_cols); //행렬 사이즈 정보 받기
	num_heads = (num_cols > num_rows) ? num_cols : num_rows; //row와 col 둘 중 큰 값으로 돌릴예정
	node = new_node();
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols; 
		if (!num_heads) node->right = node; //사이즈가 없는 경우로 자기 자신을 가리키도록 설정
		else {
			for (i = 0; i < num_heads; i++) {
				//head설정해주기
				temp = new_node();
				hdnode[i] = temp; hdnode[i]->tag = head; 
				hdnode[i]->right = temp; hdnode[i]->u.next = temp;
			}
			current_row = 0; last = hdnode[0];
			while(fscanf(fp, "%d", &res)!=EOF) {//나머지 .txt 파일을 읽어들이는 동안 
				row = temp_row;
				col = temp_col;
				if (res == 0) { //원소가 0인경우 skip해주며 temp_row와 temp_col을 설정함
					temp_col++;
					if (temp_col == num_cols) {
						temp_row++;
						temp_col = 0;
					}
					continue;
				}
				else { //원소가 value가 있으면 value값 대입해주고 
					value = res;
					temp_col++;
					if (temp_col == num_cols) {
						temp_row++;
						temp_col = 0;
					}
				}
				if (row > current_row) {//구조 만들어주기
					last->right = hdnode[current_row];
					current_row = row; last = hdnode[row];
				}
				//row col value넣고 노드를 생성/삽입
				temp = new_node(); temp->tag = entry;
				temp->u.entry.row = row; temp->u.entry.col = col;
				temp->u.entry.value = value; last->right = temp; last = temp;
				hdnode[col]->u.next->down = temp;
				hdnode[col]->u.next = temp;
			}
			// close last row
			last->right = hdnode[current_row];
			// close all column lists
			for (i = 0; i < num_cols; i++)
				hdnode[i]->u.next->down = hdnode[i];
			// link all head nodes together
			for (i = 0; i < num_heads - 1; i++)
				hdnode[i]->u.next = hdnode[i + 1];
			hdnode[num_heads - 1]->u.next = node;
			node->right = hdnode[0];
		}
	return node;
}
void mwrite(matrix_pointer node)
{
	int i;
	int temp_row=0, temp_col=0;
	if (node == NULL) //빈 노드일 경우
	{
		printf("Empty node! \n");
		return;
	}
	matrix_pointer temp, head = node->right;
	printf("  %d x %d matrix\n\n",node->u.entry.row, node->u.entry.col);
	for (i = 0; i < node->u.entry.row; i++) { //row 쭉 돌면서 
		temp_col = 0;
		for (temp = head->right; temp != head; temp = temp->right) {
			while (1) {
				//linked list값을 보고 해당 row와 col 직전까지는 0을 출력
				if (temp_col++!= temp->u.entry.col) { 
					printf("  0 "); 
				}
				else { //값이 있는 위치에서는 value 출력
					printf("%3d ", temp->u.entry.value);
					break;
				}
			}
		}
		//value 출력 후 나머지 비어있는 원소들에 0 출력 
		for (int j = temp_col; j < node->u.entry.col; j++) {
			printf("  0 ");
		}
		head = head->u.next; // 다음줄로
		printf("\n");
	}
	printf("\n\n");

	return ;
}

void merase(matrix_pointer* node)
{
		if((*node)==NULL){
			printf("Already NULL\n");
			return ;
		}
	int i, num_heads;
	matrix_pointer x, y, head = (*node)->right;
	//
	for (i = 0; i < (*node)->u.entry.row; i++) { //row 기준으로 돌면서 삭제 
		y = head->right;
		while (y != head) {
			x = y; y = y->right; free(x);
		}
		x = head; head = head->u.next; free(x); //헤드노드까지 삭제 
	}
	// 남아있는 헤드 삭제
	y = head;
	while (y != *node) {
		x = y; y = y->u.next; free(x);
	}
	free(*node); *node = NULL;
	printf("Erase Compelete!\n");
	return;
}
