#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_EXPR_SIZE 100
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand, end }
precedence;
char expr[MAX_EXPR_SIZE];
int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0,-1 };
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0,-1 };

//링크드 리스트 선언
typedef struct Node {
	precedence data;
	struct Node* next;
}Node; 

//스택선언
typedef struct Stack
{
	Node* top;
} Stack;

Stack* stack;

precedence getToken(char* symbol, int* n);
void InitStack();
int IsEmpty();
void Push(precedence data);
precedence Pop();

//스택 시작함수
void InitStack()
{
	stack = (Stack*)malloc(sizeof(Stack));
	stack->top = NULL;
}

//스택 비었는지 확인
int IsEmpty()
{
	return stack->top == NULL;
}

//스택에 데이터 추가
void Push(precedence data)
{
	Node* now = (Node*)malloc(sizeof(Node));
	now->data = data;
	now->next = stack->top;
	stack->top = now;
}

//스택에서 데이터 꺼내기
precedence Pop()
{
	Node* now;
	precedence result;
	if (IsEmpty())
	{
		return eos;
	}
	now = stack->top;
	result = now->data;

	stack->top = now->next;
	free(now);
	return result;
}

// operator 출력함수(스택에서 꺼내면서 출력할 때 씁니다)
void Print_Operator(int n) {
	switch (n) {
	case 0: printf("( "); break;
	case 1: printf(") "); break;
	case 2: printf("+ "); break;
	case 3: printf("- "); break;
	case 4: printf("* "); break;
	case 5: printf("/ "); break;
	case 6: printf("%% "); break;
	case 7: printf("  "); break;
	}
}

//infix를 postfix로 바꾸기
void postfix() {
	char symbol;
	int n = 0;
	int top = 0;
	//마지막 나올때 알려주려고 eos 넣기
	Push(eos);
	precedence token;

	//토큰을 하나씩 읽으면서
	for (token = getToken(&symbol, &n); token != end; token = getToken(&symbol, &n)) {
		if (token == eos) {
			continue;
		}
		else if (token == operand) //숫자면 바로 꺼냄
			printf("%c ", symbol);
		else if (token == rparen) { //오른쪽 괄호면 왼쪽 괄호 나올때까지 계속 출력
			/* unstack tokens until left paranthesis */
			while (stack->top->data != lparen)
			{
				Print_Operator(Pop());
			}
			Pop(); //왼쪽 괄호는 그냥 출력없이 꺼내줌
		}
		else {
			//연산자 우선순위 파악해서 pop 출력
			while (isp[stack->top->data] >= icp[token])
			{
				Print_Operator(Pop());
			}
			//스택에 토큰 push
			Push(token);
		}
	}
	//이제 문자열 다 봤으면 스택에 남은거 다 출력해주기
	while ((token = Pop()) != eos) {
		Print_Operator(token);
	}
	printf("\n");
}

//토큰 얻는 함수
precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case ' ': return eos;
	case '\n': return end;
	default: return operand;
	}
}

//파일포인터로 txt파일 읽어서 expr 전역변수에 할당하기
void rExpr(FILE* fp) {
	fgets(expr, sizeof(expr), fp);
	printf("infix : %s", expr);
}
int main()
{
	InitStack();// 스택초기화
	FILE* fp = fopen("expr.txt", "r");
	if(fp==NULL) //에러 체크
		return 0;
	rExpr(fp);
	printf("postfix : ");
	postfix();
	return 0;
}
