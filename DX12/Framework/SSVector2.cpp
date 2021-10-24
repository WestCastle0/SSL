#include "SSMath.h"
#include "SSVector2.h"
#include "SSMatrix2.h"
#include "SSMatrix3.h"

using namespace SSFramework;

const SSVector2 SSVector2::zero = SSVector2();
SSVector2::SSVector2():x(0), y(0) {}
SSVector2::SSVector2(float x, float y):x(x), y(y){}

SSVector2 SSVector2::Normalized(const SSVector2& v)
{
	float lengthSq = v.x * v.x + v.y * v.y;
	SSVector2 result;

	if (lengthSq > 0)
	{
		float lenInv = 1.0f / sqrtf(lengthSq);
		result.x *= lenInv;
		result.y *= lenInv;
	}

	return result;
}

float SSVector2::Dot(const SSVector2& v1, const SSVector2& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

SSVector2 SSVector2::Cross(const SSVector2& v)
{
	return SSVector2(-v.y, v.x);
}

float SSVector2::Length() const
{
	return sqrtf(x * x + y * y);
}

float SSVector2::LengthSq() const
{
	return x * x + y * y;
}

bool SSVector2::IsZero() const
{
	return x == 0.0f && y == 0.0f;
}

SSVector2& SSVector2::Transform(const SSMatrix2& m)
{
	SSVector2 v(x, y);
	this->x = (v.x * m._11) + (v.y * m._21);
	this->y = (v.x * m._12) + (v.y * m._22);
	return *this;
}

SSVector2& SSVector2::Transform(const SSMatrix3& m)
{
	SSVector2 v(x, y);
	this->x = (v.x * m._11) + (v.y * m._21);
	this->y = (v.x * m._12) + (v.y * m._22);
	float w = 1.0f / ((v.x * m._13) + (v.y * m._23) + m._33);

	this->x *= w;
	this->y *= w;
	return *this;

}

void SSVector2::Normalize()
{
	float lengthSq = x * x + y * y;
	if (lengthSq > 0)
	{
		float lenInv = 1.0f / sqrtf(lengthSq);
		x *= lenInv;
		y *= lenInv;
	}
}

bool SSVector2::operator==(const SSVector2& v) const
{
	return x==v.x && y==v.y;
}

bool SSVector2::operator!=(const SSVector2& v) const
{
	return x != v.x || y != v.y;
}

SSVector2 SSVector2::operator+(const SSVector2& v) const
{
	return SSVector2(x + v.x, y + v.y);
}

SSVector2 SSVector2::operator-(const SSVector2& v) const
{
	return SSVector2(x - v.x, y - v.y);
}

SSVector2 SSVector2::operator-() const
{
	return SSVector2(-x, -y);
}

SSVector2 SSVector2::operator/(float f) const
{
	float inv = 1.0f / f;
	return SSVector2(x * inv, y * inv);
}

SSVector2 SSVector2::operator/(const SSVector2& v) const
{
	return SSVector2(x / v.x, y / v.y);
}

SSVector2 SSVector2::operator*(float f) const
{
	return SSVector2(f * x, f * y);
}

SSVector2 SSVector2::operator*(const SSVector2& v) const
{
	return SSVector2(x * v.x, y * v.y);
}

SSVector2 SSVector2::operator*(const SSMatrix2& m) const
{
	return SSVector2(x, y).Transform(m);
}

SSVector2 SSVector2::operator*(const SSMatrix3& m) const
{
	return SSVector2(x, y).Transform(m);
}

SSVector2& SSVector2::operator+=(const SSVector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

SSVector2& SSVector2::operator-=(const SSVector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

SSVector2& SSVector2::operator/=(float f)
{
	float inv = 1.0f / f;
	x *= inv;
	y *= inv;
	return *this;
}

SSVector2& SSVector2::operator/=(const SSVector2& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

SSVector2& SSVector2::operator*=(float f)
{
	x *= f;
	y *= f;
	return *this;
}

SSVector2& SSVector2::operator*=(const SSVector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

SSVector2& SSVector2::operator*=(const SSMatrix2& m)
{
	return Transform(m);
}

SSVector2& SSVector2::operator*=(const SSMatrix3& m)
{
	return Transform(m);
}
