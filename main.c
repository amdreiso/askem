#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define COLOR_RESET	"\033[0m"

int main(int argc, char **argv)
{
	int width, height, channels;
	char *ch = "█";
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
			int x = (int)strtol(argv[2], NULL, 16);
			x = 0x25A3;
			char code[256];
			printf("%c\n", (char)x);
			snprintf(code, sizeof code, "%c", (char)x);
			ch = code;
		} else {
			ch = argv[2];
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

			printf("\033[38;2;%d;%d;%dm%s%s%s", r, g, b, ch, ch, COLOR_RESET);
		}
		printf("\n");
	}
	
    stbi_image_free(img);

	return 0;
}

