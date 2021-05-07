#pragma once
#include "../utils/global.h"
#include "../utils/math.h"
#include <opencv2/opencv.hpp>

class Texture{
private:
    cv::Mat image_data;

public:
    Texture(const std::string& name)
    {
        image_data = cv::imread(name,1);
        //cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        cv::cvtColor(image_data, image_data, cv::COLOR_BGR2RGB);
        width = image_data.cols;
        height = image_data.rows;
        std::cout<<"texture:width "<<width<<" height "<<height<<std::endl;
    }

    int width, height;

    vec3 getColor(float u, float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return vec3(color[0], color[1], color[2]);
    }

};
