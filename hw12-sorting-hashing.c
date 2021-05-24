#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13  //배열의 최대 사이즈
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE  //해시 테이블의 최대 사이즈

//함수 리스트
int initialize(int **a);  //초기화 연산
int freeArray(int *a);  //배열의 메모리 해제 연산
void printArray(int *a);  //배열 출력 연산

int selectionSort(int *a);  //선택 정렬 연산
int insertionSort(int *a);  //삽입 정렬 연산
int bubbleSort(int *a);  //버블 정렬 연산
int shellSort(int *a);   //셸 정렬 연산
//재귀함수 기능으로 구현
int quickSort(int *a, int n);


//해시코드 생성 연산
int hashCode(int key);

//배열 a에 대한 해시 테이블을 만드는 연산
int hashing(int *a, int **ht);

//해시 테이블에서 key를 찾아 해시 테이블의 인덱스를 다시 리턴 하는 연산
int search(int *ht, int key);


int main()
{
	char command;
    printf("[----- [김현민]  [2018038088] -----]");
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
        printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	//배열이 null인 경우 메모리 할당
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  //할당된 메모리의 주소를 복사 --> 메인에서 배열을 제어 할수 있도록 함
	} else
		temp = *a;

	//랜덤값을 배열의 값으로 저장
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {  //배열 a에 값이 null인 경우
		printf("nothing to print.\n");
		return;
	}
    //배열 a에 값이 null이 아닌 경우
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전의 원소 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i;  //기준 위치 원소의 인덱스 i를 변수 minindex에 설정
		min = a[i];  //배열 a에 i번 원소의 인덱스 값을 min에 저장
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)  //i+1번 원소부터 마지막 원소까지 비교하면서 가장 작은 원소가 있는 위치의 값을 변수 min에 저장하고 mindex에 j값을 넣어줌
		{
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i];  //기존 위치와 가장 작은 원소가 있는 위치를 교환후 a[i]에 min값을 저장
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);   //정렬 후의 원소 출력
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전의 원소 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)   //1번 원소부터 시작하여 삽입 정렬을 마지막 원소까지 반복 수행
	{
		t = a[i];
		j = i;
		while (a[j-1] > t && j > 0)   //삽입 할 자리를 만들기 위하여
		{
			a[j] = a[j-1];  //삽입 할 자리 이후의 원소를 뒤로 이동
			j--;
		}
		a[j] = t;  //삽입 할 자리에 원소 저장 
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //정렬 후의 원소 출력

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전의 원소 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)  //0번 원소부터 시작하여 버블 정렬을 마지막 원소까지 반복 수행
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)  //0번 원소부터 시작하여 버블 정렬을 마지막 원소까지 반복 수행
		{
			if (a[j-1] > a[j])  //인접한 원소를 두 개 비교하여 자리를 교환 
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);  //정렬 후의 원소 출력

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);  //정렬 전의 원소 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)   //전체 범위의 1/2로 설정하고 h가 1보다 작아지면 반복 수행 종료
	{
		for (i = 0; i < h; i++)  //0번 원소부터 시작하여 간격 h가 i보다 작아질 때 까지 반복수행
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)   //간격 i+h만큼 떨어져 있는 원소들로 구성한 하나의 부분집합에 대해 마지막 원소까지 셸정렬을 수행
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);  //정렬 후의 원소 출력

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1];
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);  //v 원소보다 큰 원소를 찾을때 까지 i를 오른쪽으로 이동
			while(a[--j] > v);  //v 원소보다 작은 원소를 찾을때 까지 j를 왼쪽으로 이동

			if (i >= j) break;  //i가 j보다 크거나 같을 경우 더 이상 진행할 수 없으므로 i와 j 원소의 자리를 교환
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
        //i번째와 n-1번째 원소의 자리를 교환
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
        //분할 계산(퀵 정렬을 재귀 호출)
		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1)
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);

	if(ht[index] == key)
		return index;

	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}