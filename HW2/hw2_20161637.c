#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

char failure[1024];
void func_fail(char* pat) {
	int n = strlen(pat);
	int i = -1, j = 0;

	failure[0] = -1;
	while (j < n) { //패턴 길이동안 반복
		if (i == -1)
			failure[++j] = ++i; //첫 시작
		else if (i >= 0 && pat[i] == pat[j])
			failure[++j] = ++i; //패턴이 맞으면 갱신

		else i = failure[i]; // 패턴 매칭 실패 시 
	}
}

int pmatch(char* str, char* pat) {
	int i = 0, j = 0;
	int lens = strlen(str);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) { //비교할 문자열 있으면
		if (str[i] == pat[j]) { //일치했을 경우
			i++;
			j++;
		}
		else if (j == 0) // 일치하지 않았지만 패턴 시작부분일 경우
			i++;
		else
			j = failure[j - 1] + 1; //일치하지 않았을 경우
	}
	return ((j == lenp) ? (i - lenp) : -1);
}
int main() {
	char str[1024];
	char pat[1024];
	scanf("%s", str);
	scanf("%s", pat);

	func_fail(pat); //failure function 만들기
	printf("%d\n", pmatch(str, pat)); //pmatch로 패턴 위치 파악 

	return 0;
}