// #include <iostream>
#include "./include/image_algorithms.hpp"
#include "./include/Image.hpp"
#include <opencv2/opencv.hpp>
#include <cassert>
#include <chrono>

using namespace cv;

const char * IMAGE_PATH = "../Images/sample_1.jpg";

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    Image test{IMAGE_PATH};
    auto size_of_image = test.getSizeOfImage();
    std::cout << "Width: " << std::get<0>(size_of_image) << "\nHeight: " << std::get<1>(size_of_image) << "\n\n";
    Image resized_image{};
    Image croppedImage{};
    
    // Measuring performance of resize func
    auto resize_t1 = high_resolution_clock::now();
    test.resizeImage(resized_image, 800, 800);
    auto resize_t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_resize_mine = resize_t2 - resize_t1;
    std::cout << "My resize = " << ms_resize_mine.count() << "ms\n";
    
    Mat image = imread(IMAGE_PATH);
    Mat output;
    auto resize_CV_t1 = high_resolution_clock::now();
    resize(image, output, cv::Size(800, 800), 0, 0);
    auto resize_CV_t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_resize_CV = resize_CV_t2 - resize_CV_t1;
    std::cout << "OpenCV resize = " << ms_resize_CV.count() << "ms\n\n";

    auto crop_t1 = high_resolution_clock::now();
    test.crop(croppedImage, 400, 400, 800, 800);
    auto crop_t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_crop_mine = crop_t2 - crop_t1;
    std::cout << "My crop = " << ms_crop_mine.count() << "ms\n";

    auto crop_CV_t1 = high_resolution_clock::now();
    Mat cropped(image(cv::Rect(400, 400, 800, 800)));
    auto crop_CV_t2 = high_resolution_clock::now();
    duration<double, std::milli> ms_crop_CV = crop_CV_t2 - crop_CV_t1;
    std::cout << "CV crop = " << ms_crop_CV.count() << "ms\n";

    // resized_image.write("../Images/new.jpg");
    // croppedImage.write("../Images/cropped.jpg");

    // cv::imshow("cropped image ",cropped);
    // namedWindow("image",WINDOW_NORMAL);
    // namedWindow("output", 0);
    // resizeWindow("image", 1000,1000);
    // imshow("image", image);
    // imshow("output", output);
    // waitKey(0);
    // destroyWindow();
    return EXIT_SUCCESS;
}