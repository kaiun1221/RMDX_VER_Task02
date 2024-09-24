#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void saveImage(const std::string& path, const cv::Mat& image) {
    cv::imwrite(path, image);
}

int main()
{
    cv::Mat image = cv::imread("/home/kaiun1221/RMDX/Task_02/opencv_project/resources/test_image.png");

    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    // 转化为灰度图
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/gray_image.png", grayImage);

    // 转化为 HSV 图片
    cv::Mat hsvImage;
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/hsv_image.png", hsvImage);

    // 应用均值滤波
    cv::Mat meanFiltered;
    cv::blur(image, meanFiltered, cv::Size(5, 5));
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/mean_filtered.png", meanFiltered);

    // 应用高斯滤波
    cv::Mat gaussianFiltered;
    cv::GaussianBlur(image, gaussianFiltered, cv::Size(5, 5), 0);
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/gaussian_filtered.png", gaussianFiltered);

    // 提取红色颜色区域 (HSV 方法)
    // 定义红色的低色调和高色调范围
    cv::Mat lowerRedMask, upperRedMask;
    cv::inRange(hsvImage, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowerRedMask);
    cv::inRange(hsvImage, cv::Scalar(170, 100, 100), cv::Scalar(180, 255, 255), upperRedMask);

    // 合并低色调和高色调的红色掩码
    cv::Mat redMask;
    cv::addWeighted(lowerRedMask, 1.0, upperRedMask, 1.0, 0.0, redMask);

    // 保存红色掩码图像
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/red_mask.png", redMask);

    // 寻找轮廓
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(redMask, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // 寻找图像中红色的 bounding box
    cv::Mat contourImage = image.clone();
    for (size_t i = 0; i < contours.size(); i++) {
        cv::Rect boundingBox = cv::boundingRect(contours[i]);
        cv::rectangle(contourImage, boundingBox, cv::Scalar(0, 255, 0), 2);
    }
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/contour_image.png", contourImage);

    // 计算轮廓的面积并输出
    for (size_t i = 0; i < contours.size(); i++) {
        double area = cv::contourArea(contours[i]);
        std::cout << "Contour " << i << " area: " << area << std::endl;
    }

    // 提取高亮颜色区域并进行图形学处理
    cv::Mat highLightMask;
    cv::threshold(grayImage, highLightMask, 200, 255, cv::THRESH_BINARY);
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/highlight_mask.png", highLightMask);

    // 膨胀
    cv::Mat dilated;
    cv::dilate(highLightMask, dilated, cv::Mat(), cv::Point(-1, -1), 2);
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/dilated.png", dilated);

    // 腐蚀
    cv::Mat eroded;
    cv::erode(dilated, eroded, cv::Mat(), cv::Point(-1, -1), 2);
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/eroded.png", eroded);

    // 漫水处理
    cv::Mat floodFillImage = eroded.clone();
    cv::floodFill(floodFillImage, cv::Point(0, 0), cv::Scalar(255));
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/flood_fill.png", floodFillImage);

    // 绘制任意圆形、方形和文字
    cv::Mat drawing = image.clone();
    cv::circle(drawing, cv::Point(100, 100), 50, cv::Scalar(255, 0, 0), 3);
    cv::rectangle(drawing, cv::Point(200, 200), cv::Point(300, 300), cv::Scalar(0, 255, 0), 3);
    cv::putText(drawing, "OpenCV", cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/drawing.png", drawing);

    // 绘制红色的外轮廓
    cv::Mat contourDrawing = image.clone();
    cv::drawContours(contourDrawing, contours, -1, cv::Scalar(0, 255, 0), 2);
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/contour_drawing.png", contourDrawing);

    // 绘制红色的 bounding box
    cv::Mat boundingBoxDrawing = image.clone();
    for (size_t i = 0; i < contours.size(); i++) {
        cv::Rect boundingBox = cv::boundingRect(contours[i]);
        cv::rectangle(boundingBoxDrawing, boundingBox, cv::Scalar(0, 255, 0), 2);
    }
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/bounding_box_drawing.png", boundingBoxDrawing);

    // 图像旋转 35 度
    cv::Mat rotatedImage;
    cv::Point2f center(image.cols / 2.0, image.rows / 2.0);
    cv::Mat rotMatrix = cv::getRotationMatrix2D(center, 35, 1.0);
    cv::warpAffine(image, rotatedImage, rotMatrix, image.size());
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/rotated_image.png", rotatedImage);

    // 图像裁剪为原图的左上角 1/4
    cv::Rect roi(0, 0, image.cols / 2, image.rows / 2);
    cv::Mat croppedImage = image(roi);
    saveImage("/home/kaiun1221/RMDX/Task_02/opencv_project/result/cropped_image.png", croppedImage);

    return 0;
}
