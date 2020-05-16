#include "Header.h"

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

int cut_file(CutLines lines, char* path_in, char* path_out) {

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
	if (read_file(&BFH, &BIH, &BM, path)) return;
	for (int i = 0; i < BIH.height; i++) free(BM[i]);
	free(BM);

	printf("signature:			\t%x\n", BFH.signature);
	printf("filesize:			\t%x\n", BFH.filesize);
	printf("reserved1:			\t%x\n", BFH.reserved1);
	printf("reserved2:			\t%x\n", BFH.reserved2);

	printf("headerSize:			\t%x\n", BIH.headerSize);
	printf("width:				\t%x\n", BIH.width);
	printf("height:				\t%x\n", BIH.height);
	printf("planes:				\t%x\n", BIH.planes);
	printf("bitsPerPixel:		\t%x\n", BIH.bitsPerPixel);
	printf("compression:		\t%x\n", BIH.compression);
	printf("imageSize:			\t%x\n", BIH.imageSize);
	printf("xPixelsPerMeter:	\t%x\n", BIH.xPixelsPerMeter);
	printf("yPixelsPerMeter:	\t%x\n", BIH.yPixelsPerMeter);
	printf("colorsInColorTable:	\t%x\n", BIH.colorsInColorTable);
	printf("importantColorCount:\t%x\n", BIH.importantColorCount);
}