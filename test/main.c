#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define S_LEN 300
#define P_LEN 300
#define G_LEN 100
#define CUT " \n"

typedef struct A {
	A* next;
	char* str;
} part;

int pr_goal(char* path, part* element, char*** goals) {

	FILE* file;
	char source[S_LEN];
	char* tok;
	int i = 0;

	file = fopen(path, "r");
	fgets(source, S_LEN, file);
	fclose(file);

	if (!strcmp(source, "Deadlock")) return -1;

	if (!strcmp(source, "Minotaur")) {

		element = malloc(sizeof(part));
		element->next = NULL;
		element->str = calloc(P_LEN, sizeof(char));
		strcpy(element->str, path);
		return 0;
	}

	*goals = malloc(sizeof(char*));

	tok = strtok(source, CUT);
	do {

		tok = strtok(NULL, CUT);
		*goals = realloc(*goals, (i + 1) * sizeof(char*));
		*goals[i] = calloc(G_LEN, sizeof(char));
		i++;

	} while (tok = strtok(NULL, CUT));

	return i;
}

part* MinoFind(char* goal, char* path) {

	part* element;
	FILE* file;
	DIR* dir = opendir(path);
	struct dirent* cur;
	int path_len, flag;
	char* f_path;
	char** goals;

	while (cur = readdir(dir)) {

		path_len = strlen(path);

		if (!strcmp(cur->d_name, goal)) {

			strcat(path, "/");
			strcat(path, cur->d_name);

			switch (flag = pr_goal(path, element, &goals)) {

			case 0:
				return element;

			case -1:
				return NULL;

			default:
				break;
			}

			f_path = calloc(P_LEN, sizeof(char));
			element = malloc(sizeof(part));

			for (int i = 0; i < flag; i++) {

				strcpy(f_path, "./root");

				if (element->next = MinoFind(goals[i], f_path)) {

					element->str = calloc(P_LEN, sizeof(char));
					strcpy(element->str, path);
					
					for (int j = 0; j < flag; j++) free(goals[j]);
					free(goals);
					free(f_path);
					closedir(dir);
					return element;
				}
			}

			for (int j = 0; j < flag; j++) free(goals[j]);
			free(goals);
			free(f_path);
			free(element);
		}
		else if ((cur->d_type == DT_DIR) && (strcmp(cur->d_name, ".")) && (strcmp(cur->d_name, ".."))) {

			strcat(path, "/");
			strcat(path, cur->d_name);
			return MinoFind(goal, path);
		}

		path[path_len] = '\0';
	}

	closedir(dir);
	return NULL;
}

int main() {

	FILE* file;
	char path[P_LEN] = "./root";
	char goal[G_LEN] = "file.txt";
	part* head = MinoFind(goal, path);
	part* cur;

	if (head) {

		cur = head;
		file = fopen("result.txt", "w");

		while (cur) {

			fprintf(file, "%s\n", cur->str);
			cur = cur->next;
		}

		fclose(file);
	}

	return 0;
}