#ifndef __BMATH_H
#define __BMATH_H
#include "math.h"

// 数学常数和转换因子

#define EPSILON 1e-6f
#define PI 3.14159265358979323846f
#define DEG2RAD (PI / 180.0f)
#define RAD2DEG (180.0f / PI)


struct vec3 {
	// float x, y, z;
	union {
		struct {
			float x,y,z;
		};
		float v[3];
	};

	//构造函数

	inline vec3() : x(0), y(0), z(0) {}
	inline vec3(float x,float y,float z) : x(x), y(y), z(z) {}
	inline vec3(const float *v) : x(v[0]), y(v[1]), z(v[2]) {}
	inline vec3(const vec3 &v) : x(v.x), y(v.y), z(v.z) {}

	// 向量运算和比较的操作符重载

	inline int operator==(const vec3 &v);
	inline int operator!=(const vec3 &v);
	inline const vec3 operator*(float f) const;
	inline const vec3 operator/(float f) const;
	inline const vec3 operator+(const vec3 &v) const;
	inline const vec3 operator-() const;
	inline const vec3 operator-(const vec3 &v) const;
	inline vec3 &operator*=(float f);
	inline vec3 &operator/=(float f);
	inline vec3 &operator+=(const vec3 &v);
	inline vec3 &operator-=(const vec3 &v);
	inline float operator*(const vec3 &v) const;
	inline operator float*();
	inline operator const float*() const;
	inline float &operator[](int i);
	inline const float operator[](int i) const;
	inline float length() const;
	inline float normalize();
	inline vec3 normalize(const vec3& v);
	inline void cross(const vec3 &v1,const vec3 &v2);
};

// 判断两个 vec3 对象是否相等，考虑到浮点精度问题

inline int vec3::operator==(const vec3 &v) 
{ 
	return (fabs(x - v.x) < EPSILON && fabs(y - v.y) < EPSILON && fabs(z - v.z) < EPSILON); 
}

// 判断两个 vec3 对象是否不相等

inline int vec3::operator!=(const vec3 &v) 
{
	return !(*this == v); 
}

// 向量乘以标量

inline const vec3 vec3::operator*(float f) const 
{ 
	return vec3(x * f,y * f,z * f); 
}

// 向量除以标量

inline const vec3 vec3::operator/(float f) const 
{
	return vec3(x / f,y / f,z / f); 
}

// 向量加法

inline const vec3 vec3::operator+(const vec3 &v) const 
{ 
	return vec3(x + v.x,y + v.y,z + v.z); 
}

// 向量取反

inline const vec3 vec3::operator-() const 
{ 
	return vec3(-x,-y,-z); 
}

// 向量减法

inline const vec3 vec3::operator-(const vec3 &v) const 
{ 
	return vec3(x - v.x,y - v.y,z - v.z); 
}

// 向量乘以标量（赋值）

inline vec3 & vec3::operator*=(float f) 
{ 
	return *this = *this * f; 
}

// 向量除以标量（赋值）

inline vec3 & vec3::operator/=(float f) 
{ 
	return *this = *this / f; 
}

// 向量加法（赋值）

inline vec3 & vec3::operator+=(const vec3 &v) 
{ 
	return *this = *this + v; 
}

// 向量减法（赋值）

inline vec3 & vec3::operator-=(const vec3 &v) 
{ 
	return *this = *this - v; 
}

// 计算两个向量的点乘结果

inline float vec3::operator*(const vec3 &v) const 
{ 	
	return x * v.x + y * v.y + z * v.z; 
}

// 将向量转换为指向其第一个元素的指针

inline vec3::operator float*() 
{ 
	return (float*)&x; 
}

// 将向量转换为指向其第一个元素的常量指针

inline vec3::operator const float*() const 
{ 
	return (float*)&x; 
}

// 访问向量的元素

inline float & vec3::operator[](int i) 
{ 
	return ((float*)&x)[i]; 
}

// 访问向量的元素（常量版本）

inline const float vec3::operator[](int i) const 
{ 
	return ((float*)&x)[i]; 
}

// 计算向量的长度

inline float vec3::length() const 
{ 
	return sqrt(x * x + y * y + z * z); 
}

// 归一化向量并返回其原始长度

inline float vec3::normalize() 
{
	float inv,length = sqrt(x * x + y * y + z * z);
	if(length < EPSILON) return 0.0;
	inv = 1.0f / length;
	x *= inv;
	y *= inv;
	z *= inv;
	return length;

}

// 返回向量的归一化版本

inline vec3 normalize(const vec3& v)
{
    float invlen = 1.0f / v.length();
    return vec3(v.x*invlen, v.y*invlen, v.z*invlen);
}

// 计算两个向量的叉积，并将结果存储在此向量中

inline void vec3::cross(const vec3 &v1,const vec3 &v2) 
{
	x = v1.y * v2.z - v1.z * v2.y;
	y = v1.z * v2.x - v1.x * v2.z;
	z = v1.x * v2.y - v1.y * v2.x;
}

// 计算两个向量的叉积，并返回结果向量

inline vec3 cross(const vec3 &v1, const vec3& v2)
{
    return vec3(
         v1.y*v2.z - v2.y*v1.z,
         v1.z*v2.x - v1.x*v2.z,
         v1.x*v2.y - v1.y*v2.x
                );
}
#endif