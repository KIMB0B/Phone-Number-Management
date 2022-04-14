#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

typedef struct {
	char name[10];
	char tel[20];
}INFO;
int main() {
	FILE* telt = NULL;
	FILE* bCount = NULL;

	INFO man[100];
	int cnt = 0, pick;
	char searchname[10], deletename[10], printname[10], printtel[20];
	while (1) {
		system("cls");

		fopen_s(&bCount, "count.txt", "rb");
		fscanf(bCount, "%d", &cnt);
		fclose(bCount);

		fopen_s(&telt, "tel.txt", "rt");
		for (int i = 0; i < cnt; i++) {
			fgets(man[i].name, sizeof(man[i].name), telt);
			man[i].name[strlen(man[i].name) - 1] = 0;
			fgets(man[i].tel, sizeof(man[i].tel), telt);
			man[i].tel[strlen(man[i].tel) - 1] = 0;
		}
		fclose(telt);

		puts("----------------");
		puts("|*****MENU*****|");
		puts("|1. Insert     |");
		puts("|2. Delete     |");
		puts("|3. Search     |");
		puts("|4. Print All  |");
		puts("|5. Exit       |");
		puts("----------------");
		printf("Choose the item : ");
		scanf("%d", &pick);
		getchar();

		if (pick == 1) {
			fopen_s(&telt, "tel.txt", "at");
			puts("\n[Insert]");

			printf("Input Name : ");
			fgets(man[cnt].name, sizeof(man[cnt].name), stdin);
			fputs(man[cnt].name, telt);
			man[cnt].name[strlen(man[cnt].name) - 1] = 0;

			printf("Input Tel Number : ");
			fgets(man[cnt].tel, sizeof(man[cnt].tel), stdin);
			fputs(man[cnt].tel, telt);
			man[cnt].tel[strlen(man[cnt].tel) - 1] = 0;
			fclose(telt);

			cnt++;
			fopen_s(&bCount, "count.txt", "wb");
			fprintf(bCount, "%d", cnt);
			fclose(bCount);
		}
		else if (pick == 2) {
			puts("\n[Delete]");
			printf("Input Name : ");
			fgets(deletename, sizeof(deletename), stdin);
			deletename[strlen(deletename) - 1] = 0;
			int DoDel = 0;
			for (int i = 0; i < cnt; i++) {
				if (strcmp(deletename, man[i].name) == 0) {
					for (int j = i; j < cnt - 1; j++) {
						strcpy(man[j].name, man[j+1].name);
						strcpy(man[j].tel, man[j+1].tel);
					}

					cnt--;
					fopen_s(&bCount, "count.txt", "wb");
					fprintf(bCount, "%d", cnt);
					fclose(bCount);

					fopen_s(&telt, "tel.txt", "wt");
					for (int k = 0; k < cnt; k++) {
						fputs(man[k].name, telt);
						fputc('\n', telt);
						fputs(man[k].tel, telt);
						fputc('\n', telt);
					}
					fclose(telt);

					printf("\n%s has been deleted\n", deletename);
					DoDel++;
				}
			}
			if (DoDel == 0) {
				printf("\n%s is not in here\n", deletename);
			}
			getchar();
		}
		else if (pick == 3) {
			puts("\n[Search]");
			printf("Input Name : ");
			fgets(searchname, sizeof(searchname), stdin);
			searchname[strlen(searchname) - 1] = 0;
			int DoSearch = 0;
			for (int i = 0; i < cnt; i++) {
				if (strcmp(man[i].name, searchname) == 0) {
					printf("\n%s's Tel : %s\n",man[i].name, man[i].tel);
					DoSearch++;
				}
			}
			if (DoSearch == 0) {
				printf("\n%s is not in here\n", searchname);
			}
			getchar();
		}
		else if (pick == 4) {
			puts("\n[Print All Data]");

			for (int i = 0; i < cnt; i++) {
				printf("Name : %s      Tel : %s\n\n", man[i].name, man[i].tel);
			}
			getchar();
		}
		else if (pick == 5) {
			puts("\nBye Bye~");
			Sleep(500);
			break;
		}
		else {
			puts("\nYou typed the wrong numer.\n");
			getchar();
		}
	}
}
