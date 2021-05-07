#include "./math.h"

/* vec2 class member functions */
vec2::vec2() : e{ 0,0 } {}
vec2::vec2(float e0, float e1) : e{ e0,e1} {}
float vec2::x() const { return e[0]; }
float vec2::y() const { return e[1]; }
vec2 vec2::operator-() const { return vec2(-e[0], -e[1]); }
float vec2::operator[](int i) const { return e[i]; }
float& vec2::operator[](int i) { return e[i]; }
vec2& vec2::operator+=(const vec2 &v) { e[0] += v[0]; e[1] += v[1]; return *this; }
vec2& vec2::operator*=(const float t) { e[0] *= t; e[1] *= t;  return *this; }
vec2& vec2::operator/=(const float t) { return *this *= 1 / t; }
float vec2::norm_squared() const { return e[0] * e[0] + e[1] * e[1]; }
float vec2::norm() const { return sqrt(norm_squared()); }

/* vec2 related functions */
std::ostream& operator<<(std::ostream &out, const vec2 &v)
{
	return out << v.e[0] << ' ' << v.e[1] ;
}

vec2 operator+(const vec2 &u, const vec2 &v)
{
	return vec2(u.e[0] + v.e[0], u.e[1] + v.e[1]);
}

vec2 operator-(const vec2 &u, const vec2 &v)
{
	return vec2(u.e[0] - v.e[0], u.e[1] - v.e[1]);
}

vec2 operator*(const vec2 &u, const vec2 &v)
{
	return vec2(u.e[0] * v.e[0], u.e[1] * v.e[1]);
}

vec2 operator*(double t, const vec2 &v)
{
	return vec2(t*v.e[0], t*v.e[1]);
}

vec2 operator*(const vec2 &v, double t)
{
	return t * v;
}

vec2 operator/(vec2 v, double t)
{
	return (1 / t) * v;
}

/* vec3 class member functions */
vec3::vec3() : e{ 0,0,0 } {}
vec3::vec3(float e0, float e1, float e2) : e{ e0,e1,e2 } {}
float vec3::x() const { return e[0]; }
float vec3::y() const { return e[1]; }
float vec3::z() const { return e[2]; }
vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }
float vec3::operator[](int i) const { return e[i]; }
float& vec3::operator[](int i) { return e[i]; }
vec3& vec3::operator+=(const vec3 &v) { e[0] += v[0]; e[1] += v[1]; e[2] += v[2]; return *this; }
vec3& vec3::operator*=(const float t) { e[0] *= t; e[1] *= t; e[2] *= t; return *this; }
vec3& vec3::operator/=(const float t){	return *this *= 1 / t;}
float vec3::norm_squared() const{	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];}
float vec3::norm() const{	return sqrt(norm_squared());}
float vec3::sum() const {return e[0]+e[1]+e[2];}
/* vec3 related functions */
std::ostream& operator<<(std::ostream &out, const vec3 &v) 
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

vec3 operator+(const vec3 &u, const vec3 &v) 
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

vec3 operator-(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

vec3 operator*(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

vec3 operator*(double t, const vec3 &v)
{
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

vec3 operator*(const vec3 &v, double t)
{
	return t * v;
}

vec3 operator/(vec3 v, double t)
{
	return (1 / t) * v;
}

double dot(const vec3 &u, const vec3 &v)
{
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

vec3 cross(const vec3 &u, const vec3 &v) 
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

vec3 unit_vector(const vec3 &v)
{
	return v / v.norm();
}

vec3 cwise_product(const vec3& a, const vec3& b)
{
	return vec3(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
}

// vec3 dot_division(const vec3 &u, const vec3 &v){
// 	return vec3(u[0]/v[0],u[1]/v[1],u[2]/v[2]);
// }

/* vec4 class member functions */
vec4::vec4() : e{ 0,0,0,0 } {}
vec4::vec4(float e0, float e1, float e2, float e3) : e{ e0,e1,e2,e3 } {}
float vec4::x() const { return e[0]; }
float vec4::y() const { return e[1]; }
float vec4::z() const { return e[2]; }
float vec4::w() const { return e[3]; }
float vec4::operator[](int i) const { return e[i]; }
float& vec4::operator[](int i) { return e[i]; }
vec4& vec4::operator*=(const float t) { e[0] *= t; e[1] *= t; e[2] *= t; e[3] *= t; return *this; }
vec4& vec4::operator/=(const float t) { return *this *= 1 / t; }

/* vec4 related functions */

vec4 to_vec4(const vec3 &u, float w)
{
	return vec4(u[0], u[1], u[2], w);
}

std::ostream& operator<<(std::ostream &out, const vec4 &v)
{
	return out << v[0] << " " << v[1] << " " << v[2] << " " << v[3];
}

vec4 operator-(const vec4 &u, const vec4 &v)
{
	return vec4(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], u.e[3]-v.e[3]);
}

vec4 operator+(const vec4 &u, const vec4 &v)
{
	return vec4(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], u.e[3] + v.e[3]);
}

vec4 operator*(double t, const vec4 &v)
{
	return vec4(t*v.e[0], t*v.e[1], t*v.e[2],t*v.e[3]);
}

vec4 operator*(const vec4 &v, double t)
{
	return t * v;
}

/* mat3 class member functions */
mat3::mat3() {}
vec3 mat3::operator[](int i)const { return rows[i]; }
vec3& mat3::operator[](int i) { return rows[i]; }

/*
 * for matrix's determinant, adjoint, and inverse
 * ref: 3D Math Primer for Graphics and Game Development, 2nd Edition, Chapter 6
 */

static float mat3_determinant(const mat3 &m)
{
	float a = +m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
	float b = -m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);
	float c = +m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	return a + b + c;
}

static mat3 mat3_adjoint(const mat3 &m)
{
	mat3 adjoint;
	adjoint[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]);
	adjoint[0][1] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]);
	adjoint[0][2] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]);
	adjoint[1][0] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]);
	adjoint[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]);
	adjoint[1][2] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]);
	adjoint[2][0] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]);
	adjoint[2][1] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]);
	adjoint[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]);
	return adjoint;
}

mat3 mat3::identity()
{
	mat3 mat;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			mat[i][j] = (i == j);
	return mat;
}

mat3 mat3::transpose() const
{
	mat3 transpose;
	int i, j;
	for (i = 0; i < 3; i++) 
		for (j = 0; j < 3; j++) 
			transpose[i][j] = rows[j][i];
	return transpose;
}

mat3 mat3::inverse_transpose() const
{
	int i, j;
	mat3 inverse_transpose, adjoint;
	float determinant, inv_determinant;

	adjoint = mat3_adjoint(*this);
	determinant = mat3_determinant(*this);
	inv_determinant = 1 / determinant;

	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j)
			inverse_transpose[i][j] = adjoint[i][j] * inv_determinant;

	return inverse_transpose;
}

mat3 mat3::inverse() const
{
	return ((*this).inverse_transpose()).transpose();
}

std::ostream& operator<<(std::ostream &out, const mat3 &m)
{
	return out << m[0] << "\n" << m[1] << "\n" << m[2];
}

/* mat4 class member functions */
mat4::mat4() {}
vec4 mat4::operator[](int i)const {	return rows[i];}
vec4& mat4::operator[](int i) {	return rows[i];}

/*
 * for matrix's minor, cofactor, and adjoint
 * ref: 3D Math Primer for Graphics and Game Development, 2nd Edition, Chapter 6
 */

static float mat4_minor(mat4 m, int r, int c)
{
	mat3 cut_down;
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			int row = i < r ? i : i + 1;
			int col = j < c ? j : j + 1;
			cut_down[i][j] = m[row][col];
		}
	}
	return mat3_determinant(cut_down);
}

static float mat4_cofactor(mat4 m, int r, int c)
{
	float sign = (r + c) % 2 == 0 ? 1.0f : -1.0f;
	float minor = mat4_minor(m, r, c);
	return sign * minor;
}

static mat4 mat4_adjoint(mat4 m)
{
	mat4 adjoint;
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			adjoint[i][j] = mat4_cofactor(m, i, j);
	return adjoint;
}

mat4 mat4::identity()
{
	mat4 mat;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			mat[i][j] = (i == j);
	return mat;
}

mat4 mat4::transpose() const
{
	mat4 transpose;
	int i, j;
	for (i = 0; i < 4; i++) 
		for (j = 0; j < 4; j++) 
			transpose[i][j] = rows[j][i];
	return transpose;
}

mat4 mat4::inverse_transpose() const
{
	int i, j;
	float determinant, inv_determinant;
	mat4 adjoint, inverse_transpose;

	adjoint = mat4_adjoint(*this);
	determinant = 0;
	for (i = 0; i < 4; i++)
	{
		determinant += rows[0][i] * adjoint[0][i];
	}
	inv_determinant = 1 / determinant;

	for (i = 0; i < 4; i++) 
		for (j = 0; j < 4; j++) 
			inverse_transpose[i][j] = adjoint[i][j] * inv_determinant;

	return inverse_transpose;
}

mat4 mat4::inverse() const
{
	return ((*this).inverse_transpose()).transpose();
}

std::ostream& operator<<(std::ostream &out, const mat4 &m)
{
	return out << m[0] << "\n" << m[1] << "\n" << m[2] << "\n" << m[3];
}

vec4 operator*(const mat4 &m, const vec4 v)
{
	float product[4];
	int i;
	for (i = 0; i < 4; i++) 
	{
		float a = m[i][0] * v[0];
		float b = m[i][1] * v[1];
		float c = m[i][2] * v[2];
		float d = m[i][3] * v[3];
		product[i] = a + b + c + d;
	}
	return vec4(product[0], product[1], product[2], product[3]);
}

mat4 operator*(const mat4 &m1, const mat4 &m2)
{
	mat4 m;
	int i, j, k;
	for (i = 0; i < 4; i++) 
		for (j = 0; j < 4; j++) 
			for (k = 0; k < 4; k++) 
				m[i][j] += m1[i][k] * m2[k][j];
	return m;
}


//other utility functions
float float_clamp(float f, float min, float max) 
{
	return f < min ? min : (f > max ? max : f);
}

float float_max(float a, float b)
{
	return a > b ? a : b;
}

float float_min(float a, float b)
{
	return a < b ? a : b;
}

float float_lerp(float start, float end, float alpha)
{
	return start + (end - start) * alpha;
}

vec2 vec2_lerp(vec2& start, vec2& end, float alpha)
{
	return start + (end - start) * alpha;
}

vec3 vec3_lerp(vec3& start, vec3& end, float alpha)
{
	return start + (end - start) * alpha;
}

vec4 vec4_lerp(vec4& start, vec4& end, float alpha)
{
	return start + (end - start) * alpha;
}
