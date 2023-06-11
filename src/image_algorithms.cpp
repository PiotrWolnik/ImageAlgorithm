#include "../include/image_algorithms.hpp"

void resizePixels(unsigned char * source_image, unsigned char * target_image, std::size_t source_width, std::size_t source_height) {
    auto x_ratio = (unsigned char)((source_width << 1)/TARGET_WIDTH)+1;
    int y_ratio = (unsigned char)((source_height << 1)/TARGET_HEIGHT)+1;

    // std::cout << x_ratio << std::endl;
    // std::cout << y_ratio << std::endl;

    int x, y;
    for (auto i = 0; i < TARGET_HEIGHT; ++i) {
        for (auto j = 0; j < TARGET_WIDTH; ++j) {
            x = ((j*x_ratio)>>1);
            y = ((i*y_ratio)>>1);
            std::cout << "x " << x << std::endl;
            std::cout << "y " << y << std::endl;
            target_image[(i*TARGET_WIDTH)+j] = source_image[(y*source_width)+x];
        }
    }

    // return target_image;
}