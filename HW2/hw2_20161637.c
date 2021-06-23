#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

char failure[1024];
void func_fail(char* pat) {
	int n = strlen(pat);
	int i = -1, j = 0;

	failure[0] = -1;
	while (j < n) { //���� ���̵��� �ݺ�
		if (i == -1)
			failure[++j] = ++i; //ù ����
		else if (i >= 0 && pat[i] == pat[j])
			failure[++j] = ++i; //������ ������ ����

		else i = failure[i]; // ���� ��Ī ���� �� 
	}
}

int pmatch(char* str, char* pat) {
	int i = 0, j = 0;
	int lens = strlen(str);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) { //���� ���ڿ� ������
		if (str[i] == pat[j]) { //��ġ���� ���
			i++;
			j++;
		}
		else if (j == 0) // ��ġ���� �ʾ����� ���� ���ۺκ��� ���
			i++;
		else
			j = failure[j - 1] + 1; //��ġ���� �ʾ��� ���
	}
	return ((j == lenp) ? (i - lenp) : -1);
}
int main() {
	char str[1024];
	char pat[1024];
	scanf("%s", str);
	scanf("%s", pat);

	func_fail(pat); //failure function �����
	printf("%d\n", pmatch(str, pat)); //pmatch�� ���� ��ġ �ľ� 

	return 0;
}