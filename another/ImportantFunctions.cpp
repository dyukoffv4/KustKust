#include "ImportantFunctions.h"

void Heap::ItoS(char* num_str) {

	ItS_num++;
	int i = ItS_num;
	int num_len = 1;
	int sym;

	while (i > 9) {

		i = i / 10;
		num_len++;
	}

	num_str[num_len] = '\0';
	i = ItS_num;

	for (int j = (num_len - 1); j > -1; j--) {

		sym = i % 10;

		if (sym == 0) num_str[j] = '0';
		if (sym == 1) num_str[j] = '1';
		if (sym == 2) num_str[j] = '2';
		if (sym == 3) num_str[j] = '3';
		if (sym == 4) num_str[j] = '4';
		if (sym == 5) num_str[j] = '5';
		if (sym == 6) num_str[j] = '6';
		if (sym == 7) num_str[j] = '7';
		if (sym == 8) num_str[j] = '8';
		if (sym == 9) num_str[j] = '9';

		i = i / 10;
	}
}

int Heap::ItoS(int num, char* num_str) {

	int i = num;
	int num_len = 1;
	int sym;

	while (i > 9) {

		i = i / 10;
		num_len++;
	}

	num_str[num_len] = '\0';
	i = num;

	for (int j = (num_len - 1); j > -1; j--) {

		sym = i % 10;

		if (sym == 0) num_str[j] = '0';
		if (sym == 1) num_str[j] = '1';
		if (sym == 2) num_str[j] = '2';
		if (sym == 3) num_str[j] = '3';
		if (sym == 4) num_str[j] = '4';
		if (sym == 5) num_str[j] = '5';
		if (sym == 6) num_str[j] = '6';
		if (sym == 7) num_str[j] = '7';
		if (sym == 8) num_str[j] = '8';
		if (sym == 9) num_str[j] = '9';

		i = i / 10;
	}
	return 0;
}