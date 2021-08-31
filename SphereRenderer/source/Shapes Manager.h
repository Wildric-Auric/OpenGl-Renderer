#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


unsigned char* loadImage(const char* a, int* b, int* c, int* d, int e) {
	stbi_set_flip_vertically_on_load(true);
	unsigned char* value = stbi_load(a, b, c, d, e);
	//stbi_image_free(value);
	return value;

}


