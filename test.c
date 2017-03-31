#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

void umjul(int freq, FILE *inFile, FILE *outFile);
void ujul(int freq, FILE *inFile, FILE *outFile);
void umjulAccess(FILE *inFile);
void ujulAccess(FILE *inFile);

int hangulFlag = FALSE;
int str[1024] = { 0, };

int main(int argc, char *argv[])
{
	int option = 0;
	int option2 = 0;
	int freq;
	FILE *inFile;
	FILE *outFile;
	
	while (1) {
		printf("1. 음절 빈도조사 2.어절 빈도조사 3. 특정 빈도 access 4. 종료 : ");
		scanf("%d", &option);

		switch (option) {
		case 1:
			printf("Enter frequency : ");
			scanf("%d", &freq);

			inFile = fopen("input.txt", "r");
			outFile = fopen("output.txt", "w");

			if (inFile == NULL || outFile == NULL)
				fprintf(stderr, "FILE ERROR");

			umjul(freq, inFile, outFile);

			fclose(inFile);
			fclose(outFile);

			system("wordcount.exe output.txt");

			break;
		case 2:
			printf("Enter frequency : ");
			scanf("%d", &freq);

			inFile = fopen("input.txt", "r");
			outFile = fopen("output.txt", "w");

			if (inFile == NULL || outFile == NULL)
				fprintf(stderr, "FILE ERROR");

			ujul(freq, inFile, outFile);

			fclose(inFile);
			fclose(outFile);

			system("wordcount.exe output.txt");

			break;
		case 3:
			printf("1. 음절 선택 2. 어절 선택 :");
			scanf("%d", &option2);
			
			inFile = fopen("out.txt", "r");
			
			if (option2 == 1) {
				umjulAccess(inFile);
			}else if (option2 == 2) {

			}
			break;
		case 4:
			return 0;
		default:
			puts("잘못된 선택.");
			return 0;
		};
	}
}

void umjul(int freq, FILE *inFile, FILE *outFile) 
{
	int i;
	int count = freq;
	int character;
	int filePointer = 0;
	int index = 0;

	do {
		character = fgetc(inFile);
		if (character == '\n' || character == '\r' || character == ' ') {
			if (count == freq) {
				fseek(inFile, ++filePointer, SEEK_SET);
				continue;
			}
			character = fgetc(inFile);
		}

		if (character & 0x80) {
			if (count == freq)
				hangulFlag = TRUE;

			str[index++] = character;
			character = fgetc(inFile);
		}

		str[index++] = character;
		count--;

		if (!count && character != EOF) {
			for (i = 0; i < index; i++) {
				fprintf(outFile, "%c", str[i]);
			}
			fprintf(outFile, "\n");

			if (hangulFlag)		filePointer += 2;
			else				filePointer += 1;

			fseek(inFile, filePointer, SEEK_SET);
			hangulFlag = FALSE;
			index = 0;
			count = freq;
		}
	} while (character != EOF);
}

void ujul(int freq, FILE *inFile, FILE *outFile)
{
	int i;
	int count = freq;
	int character;
	int filePointer = 0;
	int index = 0;

	do {
		character = fgetc(inFile);

		if (character == EOF) {
			count--;
		}else if (character & 0x80) {
			if (count == freq)
				filePointer += 2;

			str[index++] = character;
			character = fgetc(inFile);
			str[index++] = character;
		}else {
			if (count == freq)	
				filePointer += 1;

			if (character == '\n' || character == '\r' || character == '\n\r' || character == ' ') {
				if (index == 0)
					continue;

				count--;
				if (count)
					str[index++] = ' ';
			}else {
				str[index++] = character;
			}
		}

		if (!count) {
			for (i = 0; i < index; i++) {
				fprintf(outFile, "%c", str[i]);
			}
			fprintf(outFile, "\n");

			fseek(inFile, filePointer, SEEK_SET);
			index = 0;
			count = freq;
		}
	} while (character != EOF);
}

void umjulAccess(FILE *inFile) {
	char string[256];
	int len=0;
	int i;

	printf("어절 입력 : ");
	scanf("%s", string);

	for (i = 0; i < strlen(string); i++) {
		if (string[i] & 0x80) {
			i++;
		}
		len++;
	}

	printf("%d\n", len);
	
}

void ujulAccess(FILE *inFile) {

}