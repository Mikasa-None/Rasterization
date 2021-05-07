#pragma once
#include "../utils/math.h"
#include<vector>


//static vec3 compute_barycentric2D(float x, float y, const vec3* v);

int is_inside_triangle(float alpha, float beta, float gamma);

vec3 compute_barycentric2D(float x, float y, const vec3& v1, const vec3& v2,const vec3& v3);