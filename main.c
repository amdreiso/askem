#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define COLOR_BLACK 			"\033[30m"
#define COLOR_RED 				"\033[31m"
#define COLOR_GREEN 			"\033[32m"
#define COLOR_YELLOW 			"\033[33m"
#define COLOR_BLUE 				"\033[34m"
#define COLOR_MAGENTA 			"\033[35m"
#define COLOR_CYAN 				"\033[36m"
#define COLOR_WHITE 			"\033[37m"
#define COLOR_BRIGHT_BLACK 		"\033[90m"
#define COLOR_BRIGHT_RED 		"\033[91m"
#define COLOR_BRIGHT_GREEN 		"\033[92m"
#define COLOR_BRIGHT_YELLOW 	"\033[93m"
#define COLOR_BRIGHT_BLUE 		"\033[94m"
#define COLOR_BRIGHT_MAGENTA 	"\033[95m"
#define COLOR_BRIGHT_CYAN 		"\033[96m"
#define COLOR_BRIGHT_WHITE 		"\033[97m"
#define COLOR_RESET				"\033[0m"

int main(int argc, char **argv)
{
	int width, height, channels;
	char ch;
	bool ascii = false;

	if (argc < 2) {
		printf("Usage: askii <filename> <char?>\n");
		return 1;
	}

	char *path = argv[1];
	char **flags = {};

	if (argc > 2) {
		for (size_t i = 3; i < argc; i++) {
			if (strcmp(argv[i], "--ascii") == 0) {
				ascii = true;
			}
		}

		if (ascii == true) {
			int num = atoi(argv[2]);
			ch = (unsigned char)num;
		} else {
			ch = argv[2][0];
		}
	}

	unsigned char *img = stbi_load(path, &width, &height, &channels, 0);

	if (img == NULL) {
		printf("Failed to load image\n");
		return 1;
	}

	for (size_t y = 0; y < height; y++) {
		for (size_t x = 0; x < width; x++) {
			int index = (y * width + x) * channels;

			unsigned char r = img[index];
			unsigned char g = img[index + 1];
			unsigned char b = img[index + 2];

			if (r == 0 && g == 0 && b == 0) {
				printf("  ");
				continue;
			}

			if (ascii) {
				printf("\033[38;2;%d;%d;%dm%c%c%s", r, g, b, ch, ch, COLOR_RESET);
			} else {
				printf("\033[38;2;%d;%d;%dm%c%c%s", r, g, b, ch, ch, COLOR_RESET);
			}
		}
		printf("\n");
	}
	
    stbi_image_free(img);

	return 0;
}

