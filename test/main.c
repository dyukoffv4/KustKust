#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define P_LEN 200
#define G_LEN 100

int IND = 0;

int MinoFind(char*** result, char* goal, char* path) {
	
	int lenFile, i = 0;
	char fgoal[G_LEN];
	char fpath[P_LEN];
	char* fpgoal;
	FILE* file;
	DIR* dir = opendir(path);
	struct dirent* cur;
	
	while (cur = readdir(dir)) {
		
		lenFile = strlen(path);
			
		if (!strcmp(cur->d_name, "add")) {
			
			strcat(path, "/");
			strcat(path, cur->d_name);
			if (MinoFind(result, goal, path)) return 1;
			path[lenFile] = '\0';
		}
		
		if (!strcmp(cur->d_name, goal)) {
			
			strcat(path, "/");
			strcat(path, cur->d_name);
			file = fopen(path, "r");
			
			while (fscanf(file, "%c", &fgoal[i]) != EOF) i++;
			fgoal[i - 1] = '\0';
			fclose(file);
			
			if (!strcmp(fgoal, "Deadlock")) {
				
				closedir(dir);
				return 0;
			}
			
			if (!strcmp(fgoal, "Minotaur")) {
				
				(*result)[IND] = calloc(P_LEN, sizeof(char));
				strcpy((*result)[IND], path);
				IND++;
				*result = realloc(*result, (IND + 1) * sizeof(char*));
				closedir(dir);
				return 1;
			}
			
			fpgoal = strtok(fgoal, " \n");
			do {
				
				strcpy(fpath, "./root");
				fpgoal = strtok(NULL, " \n");
				
				if (MinoFind(result, fpgoal, fpath)) {
					
					(*result)[IND] = calloc(P_LEN, sizeof(char));
					strcpy((*result)[IND], path);
					IND++;
					*result = realloc(*result, (IND + 1) * sizeof(char*));
					return 1;
				}
				fpgoal = strtok(NULL, " \n");
				
			} while(fpgoal);
			
			path[lenFile] = '\0';
		}
	}
	
	closedir(dir);
	return 0;
}


int main(){
	
	char path[P_LEN] = "./root";
	char** result = calloc(1, sizeof(char*));
	char goal[G_LEN] = "file.txt";
	
	if (MinoFind(&result, goal, path)) {
	
		FILE *resFile = fopen("result.txt", "w");
		
		for(int i = IND - 1; i > -1; i--) fprintf(resFile, "%s\n", result[i]);
		fclose(resFile);
		
		for(int i = 0; i < IND; i++) free(result[i]);
		free(result);
	}
	
    return 0;
}