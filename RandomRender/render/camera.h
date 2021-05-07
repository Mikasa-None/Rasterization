#pragma once

#include"../utils/math.h"

class Camera{
    public:
        Camera();
        Camera(const vec3& _eye,const vec3& _target,const vec3& _up):eye(_eye),target(_target),up(_up){};
        const vec3 eye;
        const vec3 target;
        const vec3 up;

};