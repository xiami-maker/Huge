#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define TRUE  1
#define FALSE 0
#define LEN  100

typedef unsigned char boolean;

typedef struct HUGE {
	boolean sign;
	int *num;
	int count;
	int pointLocation;
}HUGE;

void initFile(char *name);
void leaveFile(char *name,HUGE *hu);
void outputFile(HUGE hu);
HUGE addFile(HUGE huOne,HUGE huTwo);
int *formNewHugeArray(HUGE huOne,int bigCount,int smallCount);
int addEveryBitExceptHead(int one,int two,int *carry); 
HUGE MutilyFile(HUGE hunumberOne,HUGE hunumberTwo);

HUGE MutilyFile(HUGE hunumberOne,HUGE hunumberTwo) {
	HUGE hu = {0};
	int bigCount = 0;
	int i = 0;
	int j = 0;
	int *arr = 0;

	bigCount = (hunumberOne.count + 3) / 4 + (hunumberTwo.count + 3) / 4;
	hu.num = (int *)calloc(sizeof(int),bigCount);
	arr = (int *)calloc(sizeof(int),bigCount);
	for (i = (hunumberOne.count + 3) / 4 - 1;i >= 0;i--) {
		for (j = (hunumberTwo.count + 3) / 4 - 1;j >= 0 ;j--) {
			arr[ ((hunumberOne.count + 3) / 4 - 1 - i) + ((hunumberTwo.count + 3) / 4 - 1 - j)] += hunumberOne.num[i] * hunumberTwo.num[j]; 
		}
	}
	for (i = 0;i < bigCount;i++) {
		arr[i + 1] += arr[i] / 10000;
		arr[i] = arr[i] % 10000;
	}
	for (i = 0,j = bigCount - 1;i < bigCount / 2;i++,j--) {
		hu.num[j] = arr[i];
		hu.num[i] = arr[j];
	}
	if (bigCount % 2) {
		hu.num[bigCount / 2] = arr[bigCount / 2];
	}
	hu.sign = hunumberOne.sign ^ hunumberTwo.sign;
	hu.count = bigCount * 4;
	return hu;
}


int addEveryBitExceptHead(int one,int two,int *carry) {
	 int sum = 0;

	sum = one + two + *carry;
	if (sum > 9999) {
		sum = sum % 10000;
		*carry = 1;
		return sum;
	} else {
		*carry = 0;
		return sum;
	}
}

int *formNewHugeArray(HUGE huOne,int bigCount,int smallCount) {
	int *arr = 0;
	int i = 0;
	int j = 0;

	arr = (int *)calloc(sizeof(int),(bigCount + 3) / 4 + 1 + (smallCount + 3) / 4);

	if (huOne.sign) {
		for (i = (bigCount + 3) / 4,j = (huOne.count + 3) / 4 - 1;j >= 0;j--,i--) {
			arr[i] =9999 - huOne.num[j] ;
		}
		for (;i >= 0;i--) {
			arr[i] = 9999;
		}
		for (i = (bigCount + 3) / 4 + 1;i <= (bigCount + 3) / 4 + (smallCount + 3) / 4;i++) {
			if (i - (bigCount + 3) / 4 <= (huOne.count + 3) / 4 - (huOne.pointLocation + 3) / 4){
				arr[i] = 9999 - huOne.num[i];
			} else {
				arr[i] = 0;
			}
		}
	} else {
		for (i = (bigCount + 3) / 4,j = (huOne.count + 3) / 4 - 1;j >= 0;j--,i--) {
			arr[i] = huOne.num[j] ;
		}
		for (i = (bigCount + 3) / 4 + 1;i <= (bigCount + 3) / 4 + (smallCount + 3) / 4;i++) {
			if (i - (bigCount + 3) / 4 <= (huOne.count + 3) / 4 - (huOne.pointLocation + 3) / 4){
				arr[i] = huOne.num[j] ;
			}
		}
	}
	return arr;
}


HUGE addFile(HUGE huOne,HUGE huTwo) {
	int bigCount = 0;
	int smallCount = 0;
	HUGE hu = {0};
	int *arrOne = 0;
	int *arrTwo = 0;
	int carry = 0;
	int i = 0;
	int k = 0;

	bigCount = huOne.pointLocation > huTwo.pointLocation ? huOne.pointLocation : huTwo.pointLocation;
	smallCount = huOne.count - huOne.pointLocation > huTwo.count - huTwo.pointLocation ? huOne.count - huOne.pointLocation : huTwo.count - huTwo.pointLocation; 
	hu.num = (int *) calloc(sizeof(int),(bigCount + 3) / 4 + 1 + (smallCount + 3) / 4);
	arrOne = formNewHugeArray(huOne,bigCount,smallCount);
	arrTwo = formNewHugeArray(huTwo,bigCount,smallCount);
	for (i = (bigCount + 3) / 4 + (smallCount + 3) / 4,k = (bigCount + 3) / 4 + (smallCount + 3) / 4; i >= 0;k--,i--) {
		hu.num[k] = addEveryBitExceptHead(arrOne[i],arrTwo[i],&carry);
	} 
	hu.sign = carry ^ huOne.sign ^ huTwo.sign;
	if (hu.sign == 0) {
		for (i = (bigCount + 3) / 4 + (smallCount + 3) / 4;i >= 0;i--) {
			hu.num[i] = addEveryBitExceptHead(hu.num[i],0,&carry);
		}
	} else {
		for (i = (bigCount + 3) / 4 + (smallCount + 3) / 4;i >= 0;i--) {
			hu.num[i] = addEveryBitExceptHead(hu.num[i],0,&carry);
		}
		for (i = (bigCount + 3) / 4 + (smallCount + 3) / 4;i >= 0;i--) {
			hu.num[i] = 9999 - hu.num[i];
		}
	}
	hu.count = bigCount + 4;
	hu.pointLocation = bigCount;
	return hu;
}

void outputFile(HUGE hu) {
	int i = 0;

	for(i = 0;!hu.num[i];i++) {
		;
	}
	if (hu.sign) {
		printf("-%d ",hu.num[i]);
	} else {
		printf("%d ",hu.num[i]);
	}
	for (i = i + 1;i < (hu.count + 3) / 4;i++) {
		printf("%04d ",hu.num[i] );
	}
	printf("\n");
}

void leaveFile(char *name,HUGE *hu) {
	FILE *q;
	char one;
	int arr[LEN] = {0};
	int i = 0;
	int j = 0;
	int number = 0;

	q = fopen(name,"r");
	one = fgetc(q);
	if(one == '-') {
		hu->sign = 1;
	} else {
		hu->sign = 0;
	}
	rewind(q);
	one = fgetc(q);
	while (one <= '0' || one > '9') {
		one = fgetc(q);
	}
	hu->count++;
	arr[i] = one - 48;
	one = fgetc(q);
	while(!feof(q)) {
		if (one >= '0' && one <= '9') {
			i++;
			arr[i] = one - 48;
			hu->count++;
		}
		if (one == '.') {
			hu->pointLocation = hu->count;
		}
		one = fgetc(q);
	}
	hu->num = (int *)calloc(sizeof(int),(hu->count + 3) / 4);
	number = hu->count % 4;
	if (number == 0) {
		for (i = 0,j = 0;i < hu->count;i = i + 4,j++) {
			hu->num[j] = arr[i] * 1000 + arr[i + 1] * 100 + arr[i + 2] * 10 + arr[i + 3]; 
		}
	}
	else {
		for (i = 0;i < number;i++) {
			hu->num[0] = hu->num[0] * 10 + arr[i];	
		}
		for (i = number,j = 1;i < hu->count;i = i + 4,j++) {
			hu->num[j] = arr[i] * 1000 + arr[i + 1] * 100 + arr[i + 2] * 10 + arr[i + 3]; 
		}
		
	}
	if (hu->pointLocation == 0) {
		hu->pointLocation = hu->count;
	}
 	printf("%d\n",hu->pointLocation );
	fclose(q);
}

void initFile(char *name) {
	FILE *p;
	char s[LEN] = {0};

	p = fopen(name,"w");
	gets(s);
	fwrite(s,strlen(s),1,p);

	fclose(p);
}

int main() {
	HUGE hugeOne = {0};
	HUGE hugeTwo = {0};
	char *nameOne = "newOne.txt";
	char *nameTwo = "newTwo.txt";
	HUGE hu = {0};

	printf("初请输入字符串\n");
	initFile(nameOne);  
	leaveFile(nameOne,&hugeOne);
	outputFile(hugeOne);
	printf("初请输入字符串\n");
	initFile(nameTwo);
	leaveFile(nameTwo,&hugeTwo);
	outputFile(hugeTwo);
	hu = MutilyFile(hugeOne,hugeTwo);
	//hu = addFile(hugeOne,hugeTwo);
	printf("输出字符串\n");
	outputFile(hu);

	return 0;
}

