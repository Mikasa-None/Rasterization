#include"./transform.h"
/* transformation functions */
mat4 mat4_translate(float tx, float ty, float tz)
{
	mat4 m = mat4::identity();
	m[0][3] = tx;
	m[1][3] = ty;
	m[2][3] = tz;
	return m;
}
mat4 mat4_scale(float sx, float sy, float sz)
{
	mat4 m = mat4::identity();
	m[0][0] = sx;
	m[1][1] = sy;
	m[2][2] = sz;
	return m;
}

/*
 * angle: the angle of rotation, in degrees
 *
 *  1  0  0  0
 *  0  c -s  0
 *  0  s  c  0
 *  0  0  0  1
 *
 */
mat4 mat4_rotate_x(float angle)
{
	mat4 m = mat4::identity();
	angle = angle / 180.0 * PI;
	float c = cos(angle);
	float s = sin(angle);
	m[1][1] = c;
	m[1][2] = -s;
	m[2][1] = s;
	m[2][2] = c;
	return m;

}

/*
 * angle: the angle of rotation, in degrees
 *
 *  c  0  s  0
 *  0  1  0  0
 * -s  0  c  0
 *  0  0  0  1
 *
 */
mat4 mat4_rotate_y(float angle)
{
	mat4 m = mat4::identity();
	angle = angle / 180.0 * PI;
	float c = cos(angle);
	float s = sin(angle);
	m[0][0] = c;
	m[0][2] = s;
	m[2][0] = -s;
	m[2][2] = c;
	return m;
}

/*
 * angle: the angle of rotation, in degrees
 *
 *  c -s  0  0
 *  s  c  0  0
 *  0  0  1  0
 *  0  0  0  1
 *
 */
mat4 mat4_rotate_z(float angle)
{
	mat4 m = mat4::identity();
	angle = angle / 180.0 * PI;
	float c = cos(angle);
	float s = sin(angle);
	m[0][0] = c;
	m[0][1] = -s;
	m[1][0] = s;
	m[1][1] = c;
	return m;
}

/*
 * eye: the position of the eye point
 * target: the position of the target point
 * up: the direction of the up vector
 *
 * x_axis.x  x_axis.y  x_axis.z  -dot(x_axis,eye)
 * y_axis.x  y_axis.y  y_axis.z  -dot(y_axis,eye)
 * z_axis.x  z_axis.y  z_axis.z  -dot(z_axis,eye)
 *        0         0         0                 1
 *
 * z_axis: normalize(eye-target), the backward vector
 * x_axis: normalize(cross(up,z_axis)), the right vector
 * y_axis: cross(z_axis,x_axis), the up vector
 *
 * see http://www.songho.ca/opengl/gl_camera.html
 */
mat4 mat4_lookat(vec3 eye, vec3 target, vec3 up)
{
	mat4 m = mat4::identity();

	vec3 z = unit_vector(eye - target);
	vec3 x = unit_vector(cross(up, z));
	vec3 y = unit_vector(cross(z, x));

	m[0][0] = x[0];
	m[0][1] = x[1];
	m[0][2] = x[2];

	m[1][0] = y[0];
	m[1][1] = y[1];
	m[1][2] = y[2];

	m[2][0] = z[0];
	m[2][1] = z[1];
	m[2][2] = z[2];

	m[0][3] = -dot(x, eye); //�൱��ԭ��Ҫλ�Ƶģ����µ�����ϵ����λ�ƶ��٣��и��ı�
	m[1][3] = -dot(y, eye);
	m[2][3] = -dot(z, eye);
	
	return m;
}

/*
 * left, right: the coordinates for the left and right clipping planes
 * bottom, top: the coordinates for the bottom and top clipping planes
 * near, far: the coordinates for the near and far clipping planes
 *
 * 2/(r-l)        0         0  -(r+l)/(r-l)
 *       0  2/(t-b)         0  -(t+b)/(t-b)
 *       0        0   2/(n-f)  -(f+n)/(n-f)
 *       0        0         0             1
 * see http://docs.gl/gl2/glOrtho
 *
 * note: opgenl map the near plane to -1, far plane to 1,
 *       but i map the near plane to 1, far plane to -1.
 *       And if near and far is positive it means the plane is behind viewer.
 */
mat4 mat4_ortho(float left, float right, float bottom, float top,
	float near, float far)
{
	float x_range = right - left;
	float y_range = top - bottom;
	float z_range = near - far;  //care the different 
	mat4 m = mat4::identity();
	m[0][0] = 2 / x_range;
	m[1][1] = 2 / y_range;
	m[2][2] = 2 / z_range;
	m[0][3] = -(left + right) / x_range;
	m[1][3] = -(bottom + top) / y_range;
	m[2][3] = -(near + far) / z_range;
	return m;
}

/*
 * fovy: the field of view angle in the y direction, in degrees
 * aspect: the aspect ratio, defined as width divided by height
 * near, far: the coordinates for the near and far clipping planes
 *
 * 1/(aspect*tan(fovy/2))              0             0           0
 *                      0  1/tan(fovy/2)             0           0
 *                      0              0  -(f+n)/(f-n)  -2fn/(f-n)
 *                      0              0            -1           0
 *
 * this is the same as
 *     float half_h = near * (float)tan(fovy / 2);
 *     float half_w = half_h * aspect;
 *     mat4_frustum(-half_w, half_w, -half_h, half_h, near, far);
 *
 * see http://www.songho.ca/opengl/gl_projectionmatrix.html
 *
 * note: my implementation is based on right-handed system, so it is a little different
 */
mat4 mat4_perspective(float fovy, float aspect, float near, float far)
{
	mat4 m = mat4::identity();
	fovy = fovy / 180.0 * PI;
	float t = fabs(near) * tan(fovy / 2);
	float r = aspect * t;

	m[0][0] = near / r;
	m[1][1] = near / t;
	m[2][2] = (near+far)/(near-far);
	m[2][3] = 2*near*far / (far-near);
	m[3][2] = 1;
	m[3][3] = 0;
	return m;
}


// mat4 mat4_viewport(float ViewportWidth, float ViewportHeight){
// 	mat4 m = mat4::identity();
// 	m[0][0] = ViewportWidth/2.0;
// 	m[1][0] = ViewportHeight/2.0;

// 	m[0][3] = ViewportWidth/2.0;
// 	m[1][3] = ViewportHeight/2.0;
// }