#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/Image.hpp"
#include "../include/stb_image.h"
#include "../include/stb_image_write.h"

Image::Image(const char * filename) {
    if (read(filename)) {
        std::cout << "Filename " << filename << " was read successfully!\n";
    } else {
        throw std::runtime_error("Unable to open the file!\n");
    }
}

Image::Image(std::uint8_t * data, int height, int width, int channels) : height_{height}, width_{width}, channels_{channels} {
    if (data) {
        memcpy(data_, data, width_*height_*channels_);
    }
}

Image::Image(Image const& image) : width_{image.width_}, height_{image.height_}, channels_{image.channels_} {
    memcpy(data_, image.data_, width_*height_*channels_);
}

Image::~Image() {
    stbi_image_free(data_);
}

void Image::resizeImage(Image& image, std::uint16_t new_width, std::uint16_t new_height) {
    std::uint8_t *resizedImage = (std::uint8_t*) malloc(sizeof(std::uint8_t)*800*900*3);
    float x_ratio = (float)new_width / width_;
	float y_ratio = (float)new_height / height_;
	uint16_t sx, sy;

	for(uint16_t y = 0;y < new_height; ++y) {
		sy = (uint16_t)(y / y_ratio);
		for(uint16_t x = 0;x < new_width; ++x) {
			sx = (uint16_t)(x / x_ratio);
			memcpy(&resizedImage[(x + y * new_width) * channels_], &data_[(sx + sy * width_) * channels_], channels_);
		}
	}
    image.width_ = new_width;
	image.height_ = new_height;
	if (image.data_)
        stbi_image_free(image.data_);
	image.data_ = resizedImage;
    resizedImage = nullptr;
}


void Image::crop(Image & image, std::uint16_t x_coordinate, std::uint16_t y_coordinate, std::uint16_t width_of_crop, std::uint16_t height_of_crop) {
    std::uint8_t* croppedImage =  (std::uint8_t*) malloc(sizeof(std::uint8_t)*width_of_crop*height_of_crop*channels_);

	for(uint16_t y = 0;y < height_of_crop;++y) {
		if(y + y_coordinate >= height_) {break;}
		for(uint16_t x = 0;x < width_of_crop;++x) {
			if(x + x_coordinate >= width_) {break;}
			memcpy(&croppedImage[(x + y * width_of_crop) * channels_], &data_[(x + x_coordinate + (y + y_coordinate) * width_) * channels_], channels_);
		}
	}
    image.width_ = width_of_crop;
	image.height_ = height_of_crop;
	if (image.data_)
        stbi_image_free(image.data_);
	image.data_ = croppedImage;
    croppedImage = nullptr;
}

std::tuple<int, int> Image::getSizeOfImage() const {
    return {this->width_, this->height_};
}

bool Image::read(const char * filename) {
    // The return value from an image loader is an 'unsigned char *'
    data_ = stbi_load(filename, &width_, &height_, 0, 0);
    return data_ != nullptr;
}

bool Image::write(const char* filename) {
	ImageType type = getFileType(filename);
	int success;
  switch (type) {
    case ImageType::PNG:
      success = stbi_write_png(filename, width_, height_, channels_, data_, width_*channels_);
      break;
    case ImageType::BMP:
      success = stbi_write_bmp(filename, width_, height_, channels_, data_);
      break;
    case ImageType::JPG:
      success = stbi_write_jpg(filename, width_, height_, channels_, data_, 100);
      break;
  }
  return success != 0;
}

ImageType Image::getFileType(const char* filename) {
	const char* ext = strrchr(filename, '.');
	if(ext != nullptr) {
		if(strcmp(ext, ".png") == 0) {
			return ImageType::PNG;
		}
		else if(strcmp(ext, ".jpg") == 0) {
			return ImageType::JPG;
		}
		else if(strcmp(ext, ".bmp") == 0) {
			return ImageType::BMP;
		}
	}
	return ImageType::PNG;
}

void Image::another_resize_algorithm(Image& image, std::uint8_t *picture, int height, int width) {
    auto newWidth = 1000;
    auto newHeight = 1000;
    // Get a new buuffer to interpolate into
    std::uint8_t* new_pic = new std::uint8_t[newWidth * newHeight * 3];

    double scaleWidth =  (double)newWidth / (double)width;
    double scaleHeight = (double)newHeight / (double)height;

    for(int cy = 0; cy < newHeight; cy++)
    {
        for(int cx = 0; cx < newWidth; cx++)
        {
            int pixel = (cy * (newWidth *3)) + (cx*3);
            int nearestMatch =  (((int)(cy / scaleHeight) * (width *3)) + ((int)(cx / scaleWidth) *3) );
            
            new_pic[pixel    ] =  picture[nearestMatch    ];
            new_pic[pixel + 1] =  picture[nearestMatch + 1];
            new_pic[pixel + 2] =  picture[nearestMatch + 2];
        }
    }
	image.width_ = newWidth;
	image.height_ = newHeight;
	if (image.data_)
        stbi_image_free(image.data_);
	image.data_ = new_pic;
    new_pic = nullptr;
}