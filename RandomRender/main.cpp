
#include"./utils/math.h"

#include "./scene/object.h"
#include "./render/camera.h"
#include "./render/light.h"
#include "./render/shader.h"
#include "./render/render.h"
#include "./scene/texture.h"


#include<iostream>
#include<string>

int main(){
    //load object
    //::string objFilePath="../scene/obj/cube/cube.obj";
    std::string objFilePath="../scene/obj/spot/spot_triangulated_good.obj";
    Object obj(objFilePath);
    Texture tex("../scene/obj/spot/spot_texture.png");
    obj.SetTexture(&tex);


    //set viewport size and Img size
    int ImgWidth=800;
    int ImgHeight=800;
    int ViewportWidth=ImgWidth;
    int ViewportHeight=ImgHeight;

    //set obj pose:  scale rotate translation
    vec3 modelScale(1.0,1.0,1.0);
    vec3 modelRotate(0,0,0);
    vec3 modelTranslate(0,0,0);

    //set camera 
    //cube
    // const vec3 eye(3, 2, 4);
    // const vec3 up(0, 1, 0);
    // const vec3 target(0, 0, 0);
    const vec3 eye(3, 2, -4);
    const vec3 up(0, 1, 0);
    const vec3 target(0, 0, 0);
    Camera camera(eye,target,up);

    //shader
    //PhongShader phongshader(obj,camera);
    //PhongShader* phongshader=new PhongShader(&obj,&camera);
    //PhongShader phongshader(&obj,&camera);
    //phongshader.UpdateMatrix(modelScale,modelRotate,modelTranslate,ViewportWidth,ViewportHeight);
    //Shader& shader=phongshader;


    Shader shader(obj,camera);
    shader.UpdateMatrix(modelScale,modelRotate,modelTranslate,ViewportWidth,ViewportHeight);
    //render
    Render render(ImgWidth,ImgHeight);
    render.render_rasterizer(shader);
    //render.render_rasterizer(phongshader);
    std::string outputImgSavePath="../result/test.png";
    render.SaveOutputImg(outputImgSavePath);
    
    return 0;
}
