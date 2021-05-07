#pragma once
#include "../utils/math.h"

class Light{
    public:

        Light(const vec3& _position, const vec3& _intensity):position(_position),intensity(_intensity){};
        vec3 position;
        vec3 intensity;
        
};