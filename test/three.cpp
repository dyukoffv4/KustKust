#include "Header.h"

int opt_set_component(int* command, Component* component, int argc, char* argv[]) {

	int rez, index, err_flag = 1, flag = 1;

	for (int i = 0; i < 2; i++) {

		if (!flag) break;
		if ((rez = getopt_long(argc, argv, s_color_opt, color_opt, &index)) == -1) break;

		switch (rez) {

		case 'h':
			puts(help_color);
			flag = 0;
			break;

		case 'c':
			if (optarg) {
				if ((*optarg != 'g') && (*optarg != 'r') && (*optarg != 'b')) {

					puts("Неверный компонент!");
					flag = 0;
					err_flag = 0;
					optind--;
					break;
				}
				else component->index = *optarg;
			}
			break;

		case 'm':
			component->value = 255;
			break;

		case 'n':
			component->value = 0;
			break;

		default:
			flag = 0;
			err_flag = 0;
			puts("Ошибка ввода при установке значения компонента!");
			optind--;
			break;
		}
	}
	if (flag) *command = 1;

	return err_flag;
}

int opt_put_circle(int* command, Circle* circle, int argc, char* argv[]) {

	char targets[] = ".,{}[]()";
	char* mid;
	int rez, index, err_flag = 1, flag = 1;

	circle->f_flag = 0;

	for (int i = 0; i < 4; i++) {

		if (!flag) break;
		if ((rez = getopt_long(argc, argv, s_circ_opt, circ_opt, &index)) == -1) break;

		switch (rez) {

		case 'h':
			flag = 0;
			puts(help_circ);
			break;

		case 'c':

			for (int j = 0; j < 2; j++) {

				if (!flag) break;
				if ((rez = getopt_long(argc, argv, s_corn_circ_opt, corn_circ_opt, &index)) == -1) break;

				switch (rez) {

				case 'h':
					puts(help_corn_circ);
					flag = 0;
					break;

				case 'f':
					circle->x1 = atoi(strtok(optarg, targets));
					if (mid = strtok(NULL, targets)) circle->y1 = atoi(mid);
					break;

				case 's':
					circle->x2 = atoi(strtok(optarg, targets));
					if (mid = strtok(NULL, targets)) circle->y2 = atoi(mid);
					break;

				default:
					flag = 0;
					err_flag = 0;
					puts("Ошибка ввода при создании окружности!");
					optind--;
					break;
				}
			}
			break;

		case 'r':

			circle->x2 = 0;

			for (int j = 0; j < 2; j++) {

				if (!flag) break;
				if ((rez = getopt_long(argc, argv, s_rad_circ_opt, rad_circ_opt, &index)) == -1) break;

				switch (rez) {

				case 'h':
					puts(help_rad_circ);
					flag = 0;
					break;

				case 'r':
					circle->rad_b = atoi(optarg);
					break;

				case 'c':
					circle->x0 = atoi(strtok(optarg, targets));
					if (mid = strtok(NULL, targets)) circle->y0 = atoi(mid);
					break;

				default:
					flag = 0;
					err_flag = 0;
					puts("Ошибка ввода при создании окружности!");
					optind--;
					break;
				}
			}
			break;

		case 'w':
			circle->width = atoi(optarg) - 1;
			break;

		case 'l':
			circle->l_color.r = atoi(strtok(optarg, targets));
			if (mid = strtok(NULL, targets)) circle->l_color.g = atoi(mid);
			if (mid = strtok(NULL, targets)) circle->l_color.b = atoi(mid);
			break;

		case 'f':
			circle->f_flag = 1;
			circle->f_color.r = atoi(strtok(optarg, targets));
			if (mid = strtok(NULL, targets)) circle->f_color.g = atoi(mid);
			if (mid = strtok(NULL, targets)) circle->f_color.b = atoi(mid);
			break;

		default:
			if (i != 3) {
				flag = 0;
				err_flag = 0;
				puts("Ошибка ввода при создании окружности!");
			}
			optind--;
			break;
		}
	}
	if (flag) *command = 2;

	return err_flag;
}

int opt_cut_file(int* command, CutLines* lines, int argc, char* argv[]) {

	int rez, index, err_flag = 1, flag = 1;

	for (int i = 0; i < 2; i++) {

		if (!flag) break;
		if ((rez = getopt_long(argc, argv, s_cut_opt, cut_opt, &index)) == -1) break;

		switch (rez) {

		case 'h':
			flag = 0;
			puts(help_cut);
			break;

		case 'x':
			lines->x_num = atoi(optarg);
			break;

		case 'y':
			lines->y_num = atoi(optarg);
			break;

		default:
			flag = 0;
			err_flag = 0;
			puts("Ошибка ввода при разделении файла!");
			optind--;
			break;
		}
	}

	if (flag) {
		if (lines->x_num * lines->y_num > 1000) {

			puts("Превышение количества максимальных разделений!");
			err_flag = 0;
		}
		else *command = 3;
	}

	return err_flag;
}