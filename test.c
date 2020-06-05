#include <stdio.h>
#include <string.h>

int main() {

	FILE* file = fopen("C:\\Users\\Lenovo\\Desktop\\main.c", "r");
	char buffer[5000];
	int i = 0;

	while (fscanf(file, "%c", &buffer[i]) == 1) i++;
	puts(buffer);
	return 0;
}