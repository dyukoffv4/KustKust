#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>
#include <string.h>

#include "Header.h"

int main(int argc, char* argv[]) {

	char* path_in, * path_out, * path_file, * mid;
	int rez, index, err_flag = 1, flag = 0, num = 0;
	char stat_path[] = "./out.bmp";

	int command[100];
	Component component[100];
	CutLines lines[100];
	Circle circle[100];

	opterr = 0;
	while (((rez = getopt_long(argc, argv, s_main_opt, main_opt, &index)) != -1)) {

		command[num] = 0;
		switch (rez) {

		case 'h':
			puts(help_main);
			break;

		case 's':
			err_flag *= opt_set_component(&command[num], &component[num], argc, argv);
			break;

		case 'x':
			err_flag *= opt_cut_file(&command[num], &lines[num], argc, argv);
			break;

		case 'c':
			err_flag *= opt_put_circle(&command[num], &circle[num], argc, argv);
			break;

		case 'i':
			if (optarg) path_in = optarg;
			break;

		case 'o':
			path_out = optarg;
			break;

		case 'f':
			if (optarg) print_info(optarg);
			else puts("Ошибка ввода исследуемого файла!");
			break;

		default:
			puts("Ошибка ввода!");
			break;
		}
		num++;
	}

	//-------------------------------------------------------------------------------------------------------------//

	if (!num) puts("Попробуйте вызвать -h или --help для получения информации о существующих командах.");

	for (int i = 0; i < num; i++) flag += command[i];

	if (!path_in && flag) {

		puts("Отсутствует путь изменяемого файла!");
		return 1;
	}

	if (!err_flag && flag) {

		while (1) {

			puts("Некоторые команды не могут быть выполнены.");
			puts("Все равно выполнить корректные команды и сохранить результат?");
			puts("Да - Y,y\tНет - N,n");

			char get = getchar();
			if ((get == 'n') || (get == 'N')) return 0;
			else if ((get != 'y') && (get != 'Y')) {

				puts("Неверная команда!");
				continue;
			}
			break;
		}
	}

	if (!path_out && flag) {

		puts("выходной файл: out.");
		path_out = stat_path;
	}

	//-------------------------------------------------------------------------------------------------------------//

	for (int i = 0; i < num; i++) {

		switch (command[i]) {

		case 1:
			puts("Устанавливаем новый цвет ...");
			if (!set_component(component[i], path_in, path_out)) path_in = path_out;
			break;

		case 2:
			puts("Рисуем окружность ...");
			if (!put_circle(circle[i], path_in, path_out)) path_in = path_out;
			break;

		case 3:
			puts("Разделяем файл ...");
			cut_file(lines[i], path_in, path_out);
			puts("После разделения следует указывать имя следующего изменяемого файла заново!");
			remove(path_in);
			break;
		}
	}

	return 0;
}