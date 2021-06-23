#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_Distance 10000000

int main() {
	//파일오픈
	FILE* fp1 = fopen("data.txt", "r");
	FILE* fp2 = fopen("test.txt", "r");
	FILE* fp3 = fopen("output.txt", "w");
	
	//파일오픈 에러체크
	if (fp1 == NULL || fp2 == NULL) {
		printf("No data.txt or test.txt\n");
		return 0;
	}

	int data_m, test_m,n;
	//data.txt로부터 데이터 읽어서 2차원 배열에 할당
	fscanf(fp1,"%d %d",&data_m,&n);
	float** data= (float**)malloc(sizeof(float*)* data_m);
	for (int i = 0; i < data_m; i++) {
		data[i] = (float*)malloc(sizeof(float)*n);
	}
	int* data_class = (int*)malloc(sizeof(int)* data_m);
	for (int i = 0; i < data_m; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(fp1, "%f ",&data[i][j]);
		}
		fscanf(fp1, "%d",&data_class[i]);

	}
	//test.txt로부터 데이터 읽어서 2차원 배열에 할당
	fscanf(fp2, "%d", &test_m);
	float** test = (float**)malloc(sizeof(float*) * test_m);
	for (int i = 0; i < test_m; i++) {
		test[i] = (float*)malloc(sizeof(float) * n);
	}
	for (int i = 0; i < test_m; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(fp2,"%f ",&test[i][j]);
		}
	}
	//L2거리를 저장할 result 배열 할당
	float** result = (float**)malloc(sizeof(float*) * data_m);
	for (int i = 0; i < data_m; i++) {
		result[i] = (float*)malloc(sizeof(float) * 2);
		result[i][1] = (float)data_class[i];
	}
	
	//L2거리 저장하기
	for (int i = 0; i < test_m; i++) {
		float sum = 0;
		for (int j = 0; j < data_m; j++) {
			sum = 0;
			for (int k = 0; k < n; k++) { //L2 거리 저장
				sum += (test[i][k] - data[j][k]) * (test[i][k] - data[j][k]);
			}
			result[j][0] = sqrt(sum);
		}

		float L2[5][3]; //L2거리가 가장 작은 5개 즉 KNN에서 가까운 점 5개를 뽑을 데이터를 넣을 배열
		for (int a = 0; a < 5; a++) {
			L2[a][2] = 0; // 나중에 Inverse_L2에서 이 클래스가 이미 계산된 클래스인지를 판별할 방문체크 컬럼
			float min = result[0][0];
			float min_class = result[0][1];
			int index = 0;
			for (int b = 0; b < data_m; b++) {
				if (min > result[b][0]) {
					min = result[b][0];
					min_class = result[b][1];
					index = (int)b;
				}
			}
			result[index][0] = MAX_Distance;
			L2[a][0] = 1.0 / min; //L2를 계산을 위해 1/L2로 저장하기
			L2[a][1] = min_class;// 그에 맞는 클래스도 같이 저장
		}
		
		float Inverse_L2[5][2]; // 1/L2를 더해서 weight를 저장할 배열 생성
		for (int a = 0; a < 5; a++) { //초기화
			Inverse_L2[a][0] = 0.0;
			Inverse_L2[a][1] = -1.0;
		}
		for (int a = 0; a < 5; a++) { //5개의 최소 L2에 대하여
			float class = L2[a][1];
			float sum = L2[a][0];
			float check = L2[a][2];
			if (check == 1) //이미 앞에서 계산된 클래스라면  skip
				continue;
			for (int b = a+1; b < 5; b++) {
				if (class == L2[b][1]) { //같은 클래스끼리는 1/L2합해주기
					sum += L2[b][0];
					L2[b][2] = 1;
				}
			}
			Inverse_L2[a][0] = sum;
			Inverse_L2[a][1] = class;
		}

		float real_class = 0.0;
		float real_max = -1;
		for (int a = 0; a < 5; a++) { //1/L2를 클래스 별로 합한 결과 중 그 값이 최대인 클래스를 반환
			if (real_max < Inverse_L2[a][0]) {
				real_max = Inverse_L2[a][0];
				real_class = Inverse_L2[a][1];
			}
				
		}
		fprintf(fp3,"%d\n",(int)real_class); //파일에 써주기 
	}

	
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	return 0;
}
