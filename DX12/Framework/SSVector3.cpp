#include "SSMath.h"
#include "SSVector3.h"

using namespace SSFramework;

const SSVector3 SSVector3::zero = SSVector3();
SSVector3::SSVector3() :x(0), y(0), z(0) {}
SSVector3::SSVector3(float x, float y, float z) : x(x), y(y), z(z) {}

SSVector3 SSVector3::Normalized(const SSVector3& v)
{
	float lengthSq = v.x * v.x + v.y * v.y + v.z * v.z;
	SSVector3 result;

	if (lengthSq > 0)
	{
		float lenInv = 1.0f / sqrtf(lengthSq);
		result.x *= lenInv;
		result.y *= lenInv;
		result.z *= lenInv;
	}

	return result;
}

float SSVector3::Dot(const SSVector3& v1, const SSVector3& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

SSVector3 SSVector3::Cross(const SSVector3& v1, const SSVector3& v2)
{
	return {v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x};
}

float SSVector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);
}

float SSVector3::LengthSq() const
{
	return x * x + y * y + z * z;
}

bool SSVector3::IsZero() const
{
	return x == 0.0f && y == 0.0f && z == 0.0f;
}

void SSVector3::Normalize()
{
	float lengthSq = x * x + y * y + z * z;
	if (lengthSq > 0)
	{
		float lenInv = 1.0f / sqrtf(lengthSq);
		x *= lenInv;
		y *= lenInv;
		z *= lenInv;
	}
}

bool SSVector3::operator==(const SSVector3& v) const
{
	return x == v.x && y == v.y && z == v.z;
}

bool SSVector3::operator!=(const SSVector3& v) const
{
	return x != v.x || y != v.y || z != v.z;
}

SSVector3 SSVector3::operator+(const SSVector3& v) const
{
	return SSVector3(x + v.x, y + v.y, z + v.z);
}

SSVector3 SSVector3::operator-(const SSVector3& v) const
{
	return SSVector3(x - v.x, y - v.y, z - v.z);
}

SSVector3 SSVector3::operator-() const
{
	return SSVector3(-x, -y, -z);
}

SSVector3 SSVector3::operator/(float f) const
{
	float inv = 1.0f / f;
	return SSVector3(x * inv, y * inv, z * inv);
}

SSVector3 SSVector3::operator/(const SSVector3& v) const
{
	return SSVector3(x / v.x, y / v.y, z / v.z);
}

SSVector3 SSVector3::operator*(float f) const
{
	return SSVector3(f * x, f * y, f * z);
}

SSVector3 SSVector3::operator*(const SSVector3& v) const
{
	return SSVector3(x * v.x, y * v.y, z * v.z);
}

SSVector3 SSFramework::operator*(float f, const SSVector3& v)
{
	return SSVector3(f * v.x, f * v.y, f * v.z);
}

SSVector3& SSVector3::operator+=(const SSVector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

SSVector3& SSVector3::operator-=(const SSVector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

SSVector3& SSVector3::operator/=(float f)
{
	float inv = 1.0f / f;
	x *= inv;
	y *= inv;
	z *= inv;
	return *this;
}

SSVector3& SSVector3::operator/=(const SSVector3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

SSVector3& SSVector3::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

SSVector3& SSVector3::operator*=(const SSVector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}
