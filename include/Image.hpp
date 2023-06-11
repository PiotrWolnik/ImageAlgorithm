#pragma once
#include <iostream>
#include <exception>
#include <cstring>
#include <tuple>

enum class ImageType {
    PNG, JPG, BMP
};

class Image {
    std::uint8_t * data_{nullptr};
    int height_{0};
    int width_{0};
    int channels_{3};
public:
    Image() = default;
    Image(const char * filename);
    Image(Image const& image);
    Image(std::uint8_t * data, int width, int height, int channels);
    ~Image();
    void resizeImage(Image& image, std::uint16_t new_height, std::uint16_t new_width);
    void crop(Image & image, std::uint16_t x_coordinate, std::uint16_t y_coordinate, std::uint16_t width_of_crop, std::uint16_t height_of_crop);
    std::tuple<int, int> getSizeOfImage() const;
    bool write(const char * filename);
private:
    bool read(const char * filename);
    ImageType getFileType(const char* filename);
};
