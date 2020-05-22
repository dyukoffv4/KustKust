#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#pragma pack(push, 1)

typedef struct
{
	unsigned short signature;
	unsigned int filesize;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int pixelArrOffset;
} BitmapFileHeader;

typedef struct
{
	unsigned int headerSize;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bitsPerPixel;
	unsigned int compression;
	unsigned int imageSize;
	unsigned int xPixelsPerMeter;
	unsigned int yPixelsPerMeter;
	unsigned int colorsInColorTable;
	unsigned int importantColorCount;
} BitmapInfoHeader;

typedef struct
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
} BGR;

typedef struct
{
	int x1;
	int y1;
	int x2;
	int y2;
	int x_to;
	int y_to;
} RECT;

typedef struct
{
	int x_num;
	int y_num;
} CutLines;

typedef struct
{
	char index;
	int value;
} Component;

typedef struct
{
	int x0;
	int y0;
	int rad_b;
	int x1;
	int y1;
	int x2;
	int y2;
	int width;
	BGR l_color;
	int f_flag;
	BGR f_color;
} Circle;

#pragma pack(pop)

//-----------------------------------------------------------------------------------------------------------------//

const char* s_circ_opt = "hcrw:l:f:";
const char* s_corn_circ_opt = "hf:s:";
const char* s_rad_circ_opt = "hr:c:";
const char* s_cut_opt = "hx:y:";
const char* s_color_opt = "hc:mn";
const char* s_main_opt = "hxsci:o:f:r";
const char* s_rect_opt = "hf:s:t:";
	
const struct option main_opt[] = {
		{"help", 0, NULL, 'h'},
		{"cut_file", 0, NULL, 'x'},	
		{"set_component", 0, NULL, 's'},
		{"put_circle", 0, NULL, 'c'},
		{"input_file", 1, NULL, 'i'},
		{"output_file", 1, NULL, 'o'},
		{"file_info", 1, NULL, 'f'},
		{"put_rectangle", 0, NULL, 'r'},
		{NULL, 0, NULL, 0}
};
const struct option rect_opt[] = {
		{"help", 0, NULL, 'h'},
		{"first", 1, NULL, 'f'},
		{"second", 1, NULL, 's'},
		{"to_corner", 1, NULL, 't'}
};
const struct option circ_opt[] = {
		{"help", 0, NULL, 'h'},
		{"by_corners", 0, NULL, 'c'},
		{"by_radius", 0, NULL, 'r'},
		{"width", 1, NULL, 'w'},
		{"line_color", 1, NULL, 'l'},
		{"fill", 1, NULL, 'f'},
		{NULL, 0, NULL, 0}
};
const struct option rad_circ_opt[] = {
		{"help", 0, NULL, 'h'},
		{"radius", 1, NULL, 'r'},
		{"center", 1, NULL, 'c'},
		{NULL, 0, NULL, 0}
};
const struct option corn_circ_opt[] = {
		{"help", 0, NULL, 'h'},
		{"first", 1, NULL, 'f'},	
		{"second", 1, NULL, 's'},
		{NULL, 0, NULL, 0}
};
const struct option cut_opt[] = {
		{"help", 0, NULL, 'h'},
		{"Xnumber", 1, NULL, 'x'},	
		{"Ynumber", 1, NULL, 'y'},
		{NULL, 0, NULL, 0}
};
const struct option color_opt[] = {
		{"help", 0, NULL, 'h'},
		{"Colorcomp", 1, NULL, 'c'},	
		{"max", 0, NULL, 'm'},
		{"min", 0, NULL, 'n'},
		{NULL, 0, NULL, 0}
};

//-----------------------------------------------------------------------------------------------------------------//

const char help_main[] 	= "Справочная информация по K\n\n-h --help\t\tПолучение справочной информации по K\n-s --set_component\tИзменение значения компонента цвета изображения\n-c --put_circle\t\tРисование окружности\n-x --cut_file\t\tНарезка файла\n-i --input_file\t\tВвод изменяемого файла\n-o --output_file \tВвод выходного файла\n-f --file_info\t\tПолучение информации о файле\n\nКоманда не может принять более 100 команд";
const char help_cut[] 	= "Справочная информация по -x\n\n-h --help\t\tПолучение справочной информации по -x\n-x --Xnumber\t\tПолучение числа разделений по горизонтали\n-y --Ynumber\t\tПолучение числа разделений по вертикали\n";
const char help_color[] = "Справочная информация по -s\n\n-h --help\t\tПолучение справочной информации по -s\n-c --component\t\tУстановка изменяемого компонента\n-m --max\t\tУстановка максимального значения компонента цвета\n-n --min\t\tУстановка минимального значения компонента цвета\n";
const char help_circ[] 	= "Справочная информация по -c\n\n-h --help\t\tПолучение справочной информации по -c\n-c --by_corners\t\tРисование круга через координаты углов\n-r --by_radius\t\tРисование окружности через координаты центра и радиус\n-w --width\t\tПолучение ширины линии окружности\n-l --line_color\t\tПолучение цвета линии окружности\n-f --fill\t\tПолучения цвета заливки окружности\n";
const char help_corn_circ[] = "Справочная информация по -c-c\n\n-h --help\t\tПолучение справочной информации по -c-c\n-f --first\t\tВвод координат первого угла\n-s --second\t\tВвод координат второго угла\n";
const char help_rad_circ[] 	= "Справочная информация по -c-r\n\n-h --help\t\tПолучение справочной информации по -c-r\n-c --center\t\tВвод координат центра окружности\n-r --radius\t\tВвод радиуса\n";

//-----------------------------------------------------------------------------------------------------------------//

char* itoa(int number) {

	int i = number;
	int num_len = 1;
	int sym;

	while (i > 9) {

		i = i / 10;
		num_len++;
	}

	char* num_str = (char*)calloc(num_len + 1, sizeof(char));
	num_str[num_len] = '\0';
	i = number;

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

	return num_str;
}

int read_file(BitmapFileHeader* f_BFH, BitmapInfoHeader* f_BIH, BGR*** f_BM, char* path_in) {

	FILE* file_in = fopen(path_in, "rb");
	if (!path_in) { puts("Неверно указан путь файла!"); return 1; }

	fread(f_BFH, 1, sizeof(BitmapFileHeader), file_in);
	if ((f_BFH->signature != 19778) || (f_BFH->reserved1 != 0) || (f_BFH->reserved2 != 0)) {

		puts("Файл не поддерживается!");
		return 1;
	}

	fread(f_BIH, 1, sizeof(BitmapInfoHeader), file_in);
	if ((f_BIH->headerSize != 40) || (f_BIH->bitsPerPixel != 24) || (f_BIH->colorsInColorTable != 0) || (f_BIH->importantColorCount != 0)) {

		puts("Файл не поддерживается!");
		return 1;
	}

	int H = f_BIH->height;
	int W = f_BIH->width;

	*f_BM = (BGR**)malloc(H * sizeof(BGR*));

	for (int i = 0; i < H; i++) {

		(*f_BM)[i] = (BGR*)malloc(W * sizeof(BGR) + (4 - (W * 3) % 4) % 4);
		fread((*f_BM)[i], 1, W * sizeof(BGR) + (4 - (W * 3) % 4) % 4, file_in);
	}

	fclose(file_in);
	return 0;
}

int cut_the_crap(CutLines lines, char* path_in, char* path_out) {

	BitmapFileHeader BFH;
	BitmapInfoHeader BIH;
	BGR** BM;

	if (read_file(&BFH, &BIH, &BM, path_in)) return 1;

	char path[200];
	char* ind;
	FILE* file;
	int old_H = BIH.height;

	if (lines.x_num == 0) lines.x_num = 1;
	if (lines.y_num == 0) lines.y_num = 1;

	BIH.width = BIH.width / lines.x_num;
	BIH.height = BIH.height / lines.y_num;

	int W = BIH.width;
	int H = BIH.height;

	for (int i = 0; i < lines.y_num; i++) {
		for (int j = 0; j < lines.x_num; j++) {

			ind = itoa(10 * i + j);
			
			strcpy(path, path_out);
			strtok(path, ".");
			strcat(path, ind); strcat(path, ".bmp");
			free(ind);

			if (!(file = fopen(path, "wb"))) return 1;

			fwrite(&BFH, 1, sizeof(BitmapFileHeader), file);
			fwrite(&BIH, 1, sizeof(BitmapInfoHeader), file);
			for (int k = i * H; k < (i + 1) * H; k++) {
				for (int l = j * W; l < (j + 1) * W; l++) fwrite(&BM[k][l], 1, sizeof(BGR), file);
				fwrite("\0", 1, (4 - (W * 3) % 4) % 4, file);
			}

			fclose(file);
		}
	}

	for (int i = 0; i < old_H; i++) free(BM[i]);
	free(BM);

	return 0;
}

int set_component(Component new_color, char* path_in, char* path_out) {

	BitmapFileHeader BFH;
	BitmapInfoHeader BIH;
	BGR** BM;

	if (read_file(&BFH, &BIH, &BM, path_in)) return 1;

	char ind = new_color.index;
	int val = new_color.value;

	int H = BIH.height;
	int W = BIH.width;

	FILE* file;
	if (!(file = fopen(path_out, "wb"))) return 1;

	fwrite(&BFH, 1, sizeof(BitmapFileHeader), file);
	fwrite(&BIH, 1, sizeof(BitmapInfoHeader), file);
	
	for (int i = 0; i < H; i++) {
		
		for (int j = 0; j < W; j++) {

			switch (ind) {
			case 'r':
				BM[i][j].r = val;
				break;

			case 'g':
				BM[i][j].g = val;
				break;

			case 'b':
				BM[i][j].b = val;
				break;
			}
		}
		fwrite(BM[i], 1, W * sizeof(BGR) + (4 - (W * 3) % 4) % 4, file);
	}
	fclose(file);

	for (int i = 0; i < H; i++) free(BM[i]);
	free(BM);

	return 0;
}

int put_circle(Circle circle, char* path_in, char* path_out) {
	
	BitmapFileHeader BFH;
	BitmapInfoHeader BIH;
	BGR** BM;

	if (read_file(&BFH, &BIH, &BM, path_in)) return 1;

	int x0, y0, rad_b, rad_s;
	BGR l_color;
	BGR f_color;

	int H = BIH.height;
	int W = BIH.width;

	if (circle.x2) {

		x0 = (circle.x1 + circle.x2) / 2;
		y0 = (circle.y1 + circle.y2) / 2;
		rad_b = x0 - circle.x1;
		rad_s = rad_b - circle.width;
		l_color = circle.l_color;
		if (circle.f_flag) f_color = circle.f_color;
	}
	else {

		x0 = circle.x0;
		y0 = circle.y0;
		rad_b = circle.rad_b;
		rad_s = rad_b - circle.width;
		l_color = circle.l_color;
		if (circle.f_flag) f_color = circle.f_color;
	}

	FILE* file;
	if (!(file = fopen(path_out, "wb"))) return 1;

	fwrite(&BFH, 1, sizeof(BitmapFileHeader), file);
	fwrite(&BIH, 1, sizeof(BitmapInfoHeader), file);

	for (int i = 0; i < H; i++) {

		for (int j = 0; j < W; j++) {

			if ((circle.f_flag) && ((x0 - j) * (x0 - j) + (y0 - i) * (y0 - i) - rad_b * rad_b < 0)) BM[i][j] = f_color;
			if (((x0 - j) * (x0 - j) + (y0 - i) * (y0 - i) - rad_b * rad_b < rad_b) && ((x0 - j) * (x0 - j) + (y0 - i) * (y0 - i) - rad_s * rad_s > -rad_s)) BM[i][j] = l_color;
		}
		fwrite(BM[i], 1, W * sizeof(BGR) + (4 - (W * 3) % 4) % 4, file);
	}
	fclose(file);

	for (int i = 0; i < H; i++) free(BM[i]);
	free(BM);

	return 0;
}

void print_info(char* path) {
	
	BitmapFileHeader BFH;
	BitmapInfoHeader BIH;
	BGR** BM;
	if(read_file(&BFH, &BIH, &BM, path)) return;
	for (int i = 0; i < BIH.height; i++) free(BM[i]);
	free(BM);
	
	printf("signature:      \t%x (%hu)\n", BFH.signature, BFH.signature);
	printf("filesize:       \t%x (%u)\n", BFH.filesize, BFH.filesize);
	printf("reserved1:      \t%x (%hu)\n", BFH.reserved1, BFH.reserved1);
	printf("reserved2:      \t%x (%hu)\n", BFH.reserved2, BFH.reserved2);
	printf("pixelArrOffset: \t%x (%u)\n", BFH.pixelArrOffset, BFH.pixelArrOffset);
	
	printf("headerSize:     \t%x (%u)\n", BIH.headerSize, BIH.headerSize);
	printf("width:          \t%x (%u)\n", BIH.width, BIH.width);
	printf("height:         \t%x (%u)\n", BIH.height, BIH.height);
	printf("planes:         \t%x (%hu)\n", BIH.planes, BIH.planes);
	printf("bitsPerPixel:   \t%x (%hu)\n", BIH.bitsPerPixel, BIH.bitsPerPixel);
	printf("compression:    \t%x (%u)\n", BIH.compression, BIH.compression);
	printf("imageSize:      \t%x (%u)\n", BIH.imageSize, BIH.imageSize);
	printf("xPixelsPerMeter:\t%x (%u)\n", BIH.xPixelsPerMeter, BIH.xPixelsPerMeter);
	printf("yPixelsPerMeter:\t%x (%u)\n", BIH.yPixelsPerMeter, BIH.yPixelsPerMeter);
	printf("colorsInColorTable:\t%x (%u)\n", BIH.colorsInColorTable, BIH.colorsInColorTable);
	printf("importantColorCount:\t%x (%u)\n", BIH.importantColorCount, BIH.importantColorCount);
}

int put_rectangle(RECT rectangle, char* path_in, char* path_out) {
	
	BitmapFileHeader BFH;
	BitmapInfoHeader BIH;
	BGR** BM;

	if (read_file(&BFH, &BIH, &BM, path_in)) return 1;
	
	int x1 = rectangle.x1;
	int x2 = rectangle.x2;
	int y1 = rectangle.y1;
	int y2 = rectangle.y2;
	int x_to = rectangle.x_to;
	int y_to = rectangle.y_to;
	
	int H = BIH.height;
	int W = BIH.width;
	
	if ((x1 < 0) || (x1 > W) || (y1 < 0) || (y1 > H) || (x2 < 0) || (x2 > W) || (y2 < 0) || (y2 > H) || (x_to < 0) || (x_to > W) || (y_to < 0) || (y_to > H)) return 1;
	
	BGR** new_BM = malloc((y2-y1) * sizeof(BGR*));

	for (int i = 0; i < (y2 - y1); i++) (new_BM)[i] = (BGR*)malloc((x2 - x1) * sizeof(BGR));

	FILE* file;
	if (!(file = fopen(path_out, "wb"))) return 1;

	fwrite(&BFH, 1, sizeof(BitmapFileHeader), file);
	fwrite(&BIH, 1, sizeof(BitmapInfoHeader), file);
	
	for (int i = 0; i < (y2 - y1); i++) {
		for (int j = 0; j < (x2 - x1); j++) {
			
			new_BM[i][j] = BM[i + y1][j + x1];
		}
	}
	
	for (int i = 0; i < (y2 - y1); i++) {
		for (int j = 0; j < (x2 - x1); j++) {
			
			if ((i + y_to < H) && (j + x_to < W)) BM[i + y_to][j + x_to] = new_BM[i][j];
		}
	}
	
	for (int i = 0; i < H; i++) {
		
		fwrite(BM[i], 1, W * sizeof(BGR), file);
	}
	
	fclose(file);
	
	for (int i = 0; i < H; i++) free(BM[i]);
	free(BM);
	
	return 0;
	
}

int opt_component(int* command, Component* component, int argc, char* argv[]) {
	
	int rez, index, err_flag = 1, flag = 1;
				
	for(int i = 0; i < 2; i++) {	
					
		if (!flag) break;
		if ((rez = getopt_long(argc, argv, s_color_opt, color_opt, &index)) == -1) break;
					
		switch(rez) {
			
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

int opt_rectangle(int* command, RECT* rectangle, int argc, char* argv[]) {

	char targets[] = ".,{}[]()";
	char* mid;
	int rez, index, err_flag = 1, flag = 1;
				
	for(int i = 0; i < 3; i++) {	
					
		if (!flag) break;
		if ((rez = getopt_long(argc, argv, s_rect_opt, rect_opt, &index)) == -1) break;
					
		switch(rez) {
			
			case 'h':
				flag = 0;
				break;
			
			case 'f':
				rectangle->x1 = atoi(strtok(optarg, targets));
				if (mid = strtok(NULL, targets)) rectangle->y1 = atoi(mid);
				break;
			
			case 's':
				rectangle->x2 = atoi(strtok(optarg, targets));
				if (mid = strtok(NULL, targets)) rectangle->y2 = atoi(mid);
				break;
				
			case 't':
				rectangle->x_to = atoi(strtok(optarg, targets));
				if (mid = strtok(NULL, targets)) rectangle->y_to = atoi(mid);
				break;
				
			default:
				flag = 0;
				err_flag = 0;
				puts("Ошибка ввода!");
				optind--;
				break;
		}
	}
	if (flag) *command = 4;
	
	return err_flag;
}

int opt_circle(int* command, Circle* circle, int argc, char* argv[]) {
	
	char targets[] = ".,{}[]()";
	char* mid;
	int rez, index, err_flag = 1, flag = 1;
	
	circle->f_flag = 0;
	
	for(int i = 0; i < 4; i++) {
		
		if (!flag) break;
		if ((rez = getopt_long(argc, argv, s_circ_opt, circ_opt, &index)) == -1) break;
		
		switch(rez) {
		
			case 'h':
				flag = 0;
				puts(help_circ);
				break;
			
			case 'c':
				
				for(int j = 0; j < 2; j++) {	
					
					if (!flag) break;
					if ((rez = getopt_long(argc, argv, s_corn_circ_opt, corn_circ_opt, &index)) == -1) break;
					
					switch(rez) {
						
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
				
				for(int j = 0; j < 2; j++) {	
				
					if (!flag) break;
					if ((rez = getopt_long(argc, argv, s_rad_circ_opt, rad_circ_opt, &index)) == -1) break;
					
					switch(rez) {
								
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

int opt_cut(int* command, CutLines* lines, int argc, char* argv[]) {
	
	int rez, index, err_flag = 1, flag = 1;
				
	for(int i = 0; i < 2; i++) {	
		
		if (!flag) break;
		if ((rez = getopt_long(argc, argv, s_cut_opt, cut_opt, &index)) == -1) break;
		
		switch(rez) {
			
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

//-----------------------------------------------------------------------------------------------------------------//

int main(int argc, char* argv[]) {
	
	char *path_in, *path_out, *path_file, *mid;
	int rez, index, err_flag = 1, flag = 0, num = 0;
	char stat_path[] = "./out.bmp";
	
	int command[100];
	Component component[100];
	CutLines lines[100];
	Circle circle[100];
	RECT rectangle[100];
	
	opterr = 0;
	while(((rez = getopt_long(argc, argv, s_main_opt, main_opt, &index)) != -1)) {
		
		command[num] = 0;
		switch (rez) {
		
			case 'h':
				puts(help_main);
				break;
		
			case 's':
				err_flag *= opt_component(&command[num], &component[num], argc, argv);
				break;
			
			case 'x':
				err_flag *= opt_cut(&command[num], &lines[num], argc, argv);
				break;
			
			case 'c':
				err_flag *= opt_circle(&command[num], &circle[num], argc, argv);
				break;
				
			case 'r':
				err_flag *= opt_rectangle(&command[num], &rectangle[num], argc, argv);
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
	
	for(int i = 0; i < num; i++) flag += command[i];
	
	if (!path_in && flag) {
		
		puts("Отсутствует путь изменяемого файла!");
		return 1;
	}
	
	if (!err_flag && flag) {
		
		while(1) {
		
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
				cut_the_crap(lines[i], path_in, path_out);
				break;
			
			case 4:
				//puts
				if (!put_rectangle(rectangle[i], path_in, path_out)) path_in = path_out;
				break;
		}
	}
	
	return 0;
}
