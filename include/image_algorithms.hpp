#pragma once

#include <iostream>

#define TARGET_WIDTH 800
#define TARGET_HEIGHT 800

void resizePixels(unsigned char * source_image, unsigned char * target_image, std::size_t source_width, std::size_t source_height);