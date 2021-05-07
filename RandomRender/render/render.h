#pragma once

#include "./camera.h"
#include "./shader.h"
#include "../scene/object.h"
#include "./light.h"
#include "rasterizer.h"
#include<vector>
#include<string>
#include <opencv2/opencv.hpp>


class Render{
    public:
        int ImgWidth;
        int ImgHeight;
   
        //std::vector<unsigned char> framebuffer;
        //std::vector<float> framebuffer;
        std::vector<cv::Vec3f> framebuffer;
        std::vector<float> zbuffer;

        Render(int _ImgWidth,int _ImgHeight)//,int _ImgChannels)
            :ImgWidth(_ImgWidth),ImgHeight(_ImgHeight)//,ImgChannels(_ImgChannels)
        {
            framebuffer.resize(ImgWidth*ImgHeight);
            zbuffer.resize(ImgWidth*ImgHeight);
            std::fill(framebuffer.begin(), framebuffer.end(), cv::Vec3f(0,0,0));
            std::fill(zbuffer.begin(), zbuffer.end(), std::numeric_limits<float>::infinity());
        }

        
        void render_rasterizer(Shader& shader);
        //void render_rasterizer(PhongShader& shader);

        void rasterizer_triangle(VertexAttriForShader* trivertex,Shader& shader, 
                        std::vector<cv::Vec3f>& framebuffer,std::vector<float>& zbuffer);
        // void rasterizer_triangle(VertexAttriForShader* trivertex,PhongShader& shader, 
        //         std::vector<float>& framebuffer,std::vector<float>& zbuffer);

        bool SaveOutputImg(const std::string& ImgSavePath);


        //index
        int get_index(int x, int y);
        void set_color(float x, float y, const vec3& color);

        



};

