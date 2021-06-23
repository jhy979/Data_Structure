#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct list {
	struct list* next;
	int val;
}list;
list* Newnode(int index) { // assign new node for making linked list
	list* New = (list*)malloc(sizeof(list));
	New->next = NULL;
	New->val = index;
	return New;
}
void Swapnode(list* A, list* B) { // swap node 
	int temp = A->val;
	A->val = B->val;
	B->val = temp;
	return;
}
void Insert(list* cur, int index) { // insert node to linked list 
	list* New = (list*)malloc(sizeof(list)); 
	New->val = index;
	New->next = cur->next; // insert after first node (not last position)
	cur->next = New;  
	return ;
}
void Delete(list* h, int find) {  // delete node in the linked list
	list* cur = h;
	if (cur == NULL){
		return ;
	}
	while (cur->next != NULL) {
		if (cur->next->val == find) {
			cur -> next = cur->next->next;
			return;
		}
		cur = cur->next;
	}
}
int main() {
	int min = 1e9; //minimum for min_distance
	int m, n, k, temp;
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	if (fp1 == NULL) { //deal with File error 
		printf("No such txt file.\n");
		return 0;
	}
	fscanf(fp1, "%d %d %d", &m, &n, &k); // input  m n k

	//make m*n array dynamically
	double** input = (double**)malloc(sizeof(double*) * m); 
	for (int i = 0; i < m; i++) {
		input[i] = (double*)malloc(sizeof(double) * n);
	}
	//get data
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			fscanf(fp1, "%lf", &input[i][j]);
		}
	}
	srand(1000);
	
	//make medoid points node
	list** medoid = (list**)malloc(sizeof(list*) * k);
	//make random medoids
	for (int i = 0; i < k; i++) {
		temp = rand() % m;
		medoid[i] = Newnode(temp);
	}
	int p = 0;
	double first_result = 0.0f;
	int medoid_index = 0;
	for (int i = 0; i < m; i++) {
		min = 1e9;
		for (p = 0; p < k; p++) {
			first_result = 0.0f;
			if (i == (*medoid[p]).val) {
				break;
			}
			for (int j = 0; j < n; j++) { //m data compare with k medoid
				first_result += (input[i][j] - input[(*medoid[p]).val][j]) * (input[i][j] - input[(*medoid[p]).val][j]);
			}
			if (min > first_result) { //choose closest k medoid point
				min = first_result;
				medoid_index = (*medoid[p]).val;
			}
		}
		if (p == k) {
			for (int a = 0; a < k; a++) {
				if (medoid_index == (*medoid[a]).val) {
					Insert(medoid[a], i); //insert into that medoid point 
					break;
				}
			}
		}
	}

	//check for the updated values
	int* prev_medoid = (int*)malloc(sizeof(int) * k);
	for (int i = 0; i < k; i++) {
		prev_medoid[i] = medoid[i]->val;
	}

	for (int c = 0; c < 1000; c++) { //max_iteration is 1000
		double tmp_result = 0.0;
		double min_dis = 1e9;
		int min_index = 0;
		for (int i = 0; i < k; i++) {
			list* medoid_point = medoid[i];
			min_dis = 1e9;
			while (medoid_point != NULL) { // medoid update in each cluster
				tmp_result = 0.0;
				for (int a = 0; a < m; a++) {
					for (int b = 0; b < n; b++) {
						tmp_result = (input[a][b] - input[medoid_point->val][b]) * (input[a][b] - input[medoid_point->val][b]);
					}
				}
				if (min_dis > tmp_result) {
					min_dis = tmp_result;
					min_index = medoid_point->val; // this is the new point
					Swapnode(medoid_point, medoid[i]);
				}
				medoid_point = medoid_point->next;
			}
		}

		double sec_result = 0.0f;
		double sec_min = 1e9;
		int sec_index = 0;
		int del_index = 0;
		for (int i = 0; i < k; i++) { 
			list* node_point = medoid[i]->next;
			while (node_point != NULL) {
				sec_min = 1e9;
				for (int a = 0; a < k; a++) { //check each cluster
					sec_result = 0.0f;
					for (int j = 0; j < n; j++) {
						sec_result += (input[node_point->val][j] - input[medoid[a]->val][j]) * (input[node_point->val][j] - input[medoid[a]->val][j]);
					}
					if (sec_min > sec_result) { //choose which medoid is closest
						sec_min = sec_result;
						sec_index = a;
						del_index = node_point->val;
					}
				}
				Delete(medoid[i], node_point->val); //delete in the original cluster
				Insert(medoid[sec_index], node_point->val); //insert in the new cluster
				node_point = node_point->next;
			}
		}

		for (int d = 0; d < k; d++) { //check if the medoids points are changed
			
			if (prev_medoid[d] != medoid[d]->val) {
				break;
			}
			else {
				if (d == k - 1) { // if current medoids and prev medoids are same, then print and finish the program
					for (int f = 0; f < k; f++) {
						fprintf(fp2,"%d\n", f);
						list* medoid_point = medoid[f];
						while (medoid_point != NULL) {
							fprintf(fp2,"[");
							for (int g = 0; g < n; g++) {
								if(g<n-1)
									fprintf(fp2,"%.8lf ",input[medoid_point->val][g]);
								else
									fprintf(fp2,"%.8lf", input[medoid_point->val][g]);
							}
							fprintf(fp2,"]\n");
							medoid_point = medoid_point->next;
						}
					}
					fclose(fp1);
					fclose(fp2);
					return 0;
				}
				continue;
			}
			
		}
		for (int i = 0; i < k; i++) { //update prev medoid as current medoid
			prev_medoid[i] = medoid[i]->val;
		}

	}
	 for (int f = 0; f < k; f++) {
		 fprintf(fp2,"%d\n", f);
		 list* medoid_point = medoid[f];
		 while (medoid_point != NULL) {
			 fprintf(fp2,"[");
			 for (int g = 0; g < n; g++) {
				 if(g<n-1)
					 fprintf(fp2,"%.8lf ",input[medoid_point->val][g]);
				 else
					 fprintf(fp2,"%.8lf", input[medoid_point->val][g]);
			 }
			 fprintf(fp2,"]\n");
			 medoid_point = medoid_point->next;
		 }
	 }
	 fclose(fp1);
	 fclose(fp2);
	return 0;
}
