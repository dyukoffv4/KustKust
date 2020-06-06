#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define S_LEN 300
#define P_LEN 300
#define G_LEN 100
#define CUT " \n"

typedef struct part {
	struct part* next;
	char* str;
} part;

int pr_goal(char* path, part** element, char*** goals) {

	part* f_element;
	char ** f_goals;
	FILE* file;
	char source[S_LEN];
	char* tok;
	int i = 0;

	file = fopen(path, "r");
	while (fscanf(file, "%c", &source[i]) != EOF) i++;
	if (source[i - 1] == '\n') source[i - 1] = '\0';
	else source[i] = '\0';
	fclose(file);
	
	if (!strcmp(source, "Deadlock")) return -1;

	if (!strcmp(source, "Minotaur")) {

		f_element = malloc(sizeof(part));
		f_element->next = NULL;
		f_element->str = calloc(P_LEN, sizeof(char));
		strcpy(f_element->str, path);
		*element = f_element;
		return 0;
	}
	
	i = 0;
	f_goals = malloc(sizeof(char*));
	tok = strtok(source, CUT);
	do {

		tok = strtok(NULL, CUT);
		f_goals = realloc(f_goals, (i + 1) * sizeof(char*));
		f_goals[i] = calloc(G_LEN, sizeof(char));
		strcpy(f_goals[i], tok);
		i++;

	} while (tok = strtok(NULL, CUT));
	
	*goals = f_goals;

	return i;
}

part* MinoFind(char* goal, char* path) {
	
	part* element = NULL;
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
			flag = pr_goal(path, &element, &goals);

			switch (flag) {

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

				strcpy(f_path, "./r3");

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
			if (element = MinoFind(goal, path)) return element;
		}

		path[path_len] = '\0';
	}

	closedir(dir);
	
	return NULL;
}

int main() {

	FILE* file;
	char path[P_LEN] = "./r3";
	char goal[G_LEN] = "file.txt";
	part* head = MinoFind(goal, path);
	part* cur;

	if (head) {

		file = fopen("result.txt", "w");

		while (head) {

			fprintf(file, "%s\n", head->str);
			cur = head;
			head = head->next;
			free(cur->str);
			free(cur);
		}

		fclose(file);
	}

	return 0;
}
