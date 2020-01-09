#define _CRT_SECURE_NO_WARNINGS
#include <Stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int i = 0, k =1;
FILE *fp=NULL;
int win = 0, lose = 0, draw = 0;
int doing();
void main() {

	printf("GAME START! \n");
	while(k<4){ //동적할당으로 바꿔야 함
		doing();//가위바위보함수	
		if (k == 1) {
			fp = fopen("c:/test/data.txt", "w");
			fprintf(fp, "%d회 결과: %d승 %d패 %d무 \n\n", k, win, lose, draw);
			fclose(fp);
		}
		else {
			fp = fopen("c:/test/data.txt", "a");
			fprintf(fp, "%d회 결과: %d승 %d패 %d무 \n\n", k, win, lose, draw);
			fclose(fp);
		}
		k++;
		
	}
}
int doing() {
	int com[10], user[10];
	srand((int)time(NULL));
	for (i = 0; i < 10; i++) {
		com[i] = rand() % 3 + 1;
		printf("1.가위 2.바위 3.보 \n");
		scanf("%d", &user[i]);
		if (com[i] == user[i])
			draw++;
		else if ((com[i] == 1 && user[i] == 2) || (com[i] == 2 && user[i] == 3) || (com[i] == 3 && user[i] == 1))
			win++;
		else
			lose++;
	}
	return win, lose, draw;
		
		
}