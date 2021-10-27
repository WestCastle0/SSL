#include "SSVector4.h"
#include "SSMatrix4.h"
#include "SSMath.h"

using namespace SSFramework;

const SSVector4 SSVector4::zero = SSVector4();
SSVector4::SSVector4() :x(0), y(0), z(0), w(0) {}
SSVector4::SSVector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

SSVector4 SSVector4::Normalized(const SSVector4& v)
{
	float lengthSq = v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
	SSVector4 result;

	if (lengthSq > 0)
	{
		float lenInv = 1.0f / sqrtf(lengthSq);
		result.x *= lenInv;
		result.y *= lenInv;
		result.z *= lenInv;
		result.w *= lenInv;
	}

	return result;
}

float SSVector4::Dot(const SSVector4& v1, const SSVector4& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

float SSVector4::Length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

float SSVector4::LengthSq() const
{
	return x * x + y * y + z * z + w * w;
}

bool SSVector4::IsZero() const
{
	return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
}

SSVector4& SSVector4::Transform(const SSMatrix4& m)
{
	SSVector4 v(x, y, z, w);
	this->x = (v.x * m._11) + (v.y * m._21) + (v.z * m._31) + (v.w * m._41);
	this->y = (v.x * m._12) + (v.y * m._22) + (v.z * m._32) + (v.w * m._42);
	this->z = (v.x * m._13) + (v.y * m._23) + (v.z * m._33) + (v.w * m._43);
	this->w = (v.x * m._14) + (v.y * m._24) + (v.z * m._34) + (v.w * m._44);
	return *this;
}

void SSVector4::Normalize()
{
	float lengthSq = x * x + y * y + z * z + w * w;
	if (lengthSq > 0)
	{
		float lenInv = 1.0f / sqrtf(lengthSq);
		x *= lenInv;
		y *= lenInv;
		z *= lenInv;
		w *= lenInv;
	}
}

bool SSVector4::operator==(const SSVector4& v) const
{
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool SSVector4::operator!=(const SSVector4& v) const
{
	return x != v.x || y != v.y || z != v.z || w != v.w;
}

SSVector4 SSVector4::operator+(const SSVector4& v) const
{
	return SSVector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

SSVector4 SSVector4::operator-(const SSVector4& v) const
{
	return SSVector4(x - v.x, y - v.y, z - v.z, w - v.w);
}

SSVector4 SSVector4::operator-() const
{
	return SSVector4(-x, -y, -z, -w);
}

SSVector4 SSVector4::operator/(float f) const
{
	float inv = 1.0f / f;
	return SSVector4(x * inv, y * inv, z * inv, w * inv);
}

SSVector4 SSVector4::operator/(const SSVector4& v) const
{
	return SSVector4(x / v.x, y / v.y, z / v.z, w / v.w);
}

SSVector4 SSVector4::operator*(float f) const
{
	return SSVector4(f * x, f * y, f * z, f * w);
}

SSVector4 SSVector4::operator*(const SSVector4& v) const
{
	return SSVector4(x * v.x, y * v.y, z * v.z, w * v.w);
}

SSVector4 SSVector4::operator*(const SSMatrix4& m) const
{
	return SSVector4(*this).Transform(m);
}

SSVector4& SSVector4::operator+=(const SSVector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

SSVector4& SSVector4::operator-=(const SSVector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

SSVector4& SSVector4::operator/=(float f)
{
	float inv = 1.0f / f;
	x *= inv;
	y *= inv;
	z *= inv;
	w *= inv;
	return *this;
}

SSVector4& SSVector4::operator/=(const SSVector4& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}

SSVector4& SSVector4::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}

SSVector4& SSVector4::operator*=(const SSVector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

SSVector4& SSVector4::operator*=(const SSMatrix4& m)
{
	return Transform(m);
}
