#pragma once
#include "../utils/math.h"

mat4 mat4_translate(float tx, float ty, float tz);
mat4 mat4_scale(float sx, float sy, float sz);
mat4 mat4_rotate_x(float angle);
mat4 mat4_rotate_y(float angle);
mat4 mat4_rotate_z(float angle);
mat4 mat4_lookat(vec3 eye, vec3 target, vec3 up);
mat4 mat4_ortho(float left, float right, float bottom, float top, float near, float far);
mat4 mat4_perspective(float fovy, float aspect, float near, float far);
//mat4 mat4_viewport(int ViewportWidth, int ViewportHeight);
