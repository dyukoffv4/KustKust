#include<regex.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>


char* get_str() {

	int i = 0;
	int b = 5;
	char* fstr = calloc(b, sizeof(char));
	if (!fstr) return NULL;

	while (1) {

		if (b == i + 1) {

			b += 5;
			if (!(fstr = realloc(fstr, b * sizeof(char)))) return NULL;
		}

		fstr[i] = getchar();

		if ((fstr[i] == '\n') || (strcmp(fstr, "Fin.") == 0)) {

			if (i + 2 < b) realloc(fstr, (i + 2) * sizeof(char));
			fstr[i + 1] = '\0';
			return fstr;
		}

		i++;
	}
}


char** get_txt(int* fnum) {

	int i = 0;
	char** ftxt = calloc(1, sizeof(char*));
	if (!ftxt) return NULL;

	while (1) {

		if (!(ftxt[i] = get_str())) return NULL;

		if (strcmp(ftxt[i], "Fin.") == 0) {

			*fnum = i + 1;
			return ftxt;
		}

		if (!(ftxt = realloc(ftxt, (i + 2) * sizeof(char*)))) return NULL;

		i++;
	}
}

 
int main() {

	int num = 0;
	char** txt = get_txt(&num);
	if (!txt) return 0;

	char* nc_template = "([a-z]:\\/\\/)?(www\\.)?(([a-z0-9]+\\.)+[a-z0-9]+)(\\/[a-z0-9]+)*/(\\w+\\.[a-z0-9]+)";
	regex_t c_template;
	size_t group_num = 7;
	regmatch_t groups[group_num];

	if (regcomp(&c_template, nc_template, REG_EXTENDED)) return 0;

	for (int i = 0; i < num; i++) {

		if (regexec(&c_template, txt[i], group_num, groups, 0) == 0) {

			for (int j = groups[3].rm_so; j < groups[3].rm_eo; j++) printf("%c", txt[i][j]);
			printf(" - ");
			for (int j = groups[6].rm_so; j < groups[6].rm_eo; j++) printf("%c", txt[i][j]);
			printf("\n");
		}
	}

	regfree(&c_template);
	for (int i = 0; i < num; i++) free(txt[i]);
	free(txt);

	return 0;
}