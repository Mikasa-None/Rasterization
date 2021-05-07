#include "./rasterizer.h"



// static vec3 compute_barycentric2D(float x, float y, const vec3* v) 
// {
// 	float c1 = (x*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*y + v[1].x()*v[2].y() - v[2].x()*v[1].y()) / (v[0].x()*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*v[0].y() + v[1].x()*v[2].y() - v[2].x()*v[1].y());
// 	float c2 = (x*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*y + v[2].x()*v[0].y() - v[0].x()*v[2].y()) / (v[1].x()*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*v[1].y() + v[2].x()*v[0].y() - v[0].x()*v[2].y());
// 	return vec3(c1, c2, 1 - c1 - c2);
// }

vec3 compute_barycentric2D(float x, float y, const vec3& v1, const vec3& v2,const vec3& v3) 
{
	float c1 = (x*(v2.y() - v3.y()) + (v3.x() - v2.x())*y + v2.x()*v3.y() - v3.x()*v2.y()) / (v1.x()*(v2.y() - v3.y()) + (v3.x() - v2.x())*v1.y() + v2.x()*v3.y() - v3.x()*v2.y());
	float c2 = (x*(v3.y() - v1.y()) + (v1.x() - v3.x())*y + v3.x()*v1.y() - v1.x()*v3.y()) / (v2.x()*(v3.y() - v1.y()) + (v1.x() - v3.x())*v2.y() + v3.x()*v1.y() - v1.x()*v3.y());
	return vec3(c1, c2, 1 - c1 - c2);
}


// static bool insideTriangle(int x, int y, const Vector4f* _v){
//     Vector3f v[3];
//     for(int i=0;i<3;i++)
//         v[i] = {_v[i].x(),_v[i].y(), 1.0};
//     Vector3f f0,f1,f2;
//     f0 = v[1].cross(v[0]);
//     f1 = v[2].cross(v[1]);
//     f2 = v[0].cross(v[2]);
//     Vector3f p(x,y,1.);
//     if((p.dot(f0)*f0.dot(v[2])>0) && (p.dot(f1)*f1.dot(v[0])>0) && (p.dot(f2)*f2.dot(v[1])>0))
//         return true;
//     return false;
// }

int is_inside_triangle(float alpha, float beta, float gamma)
{
	int flag = 0;
	// here epsilon is to alleviate precision bug
	if (alpha > -EPSILON && beta > -EPSILON && gamma > -EPSILON)
		flag = 1;

	return flag;
}