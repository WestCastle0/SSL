#include "SSLinearTransform2.h"
#include "SSMath.h"

using namespace SSFramework;

SSLinearTransform2::SSLinearTransform2()
	: matrix2(SSMatrix2::identity){}

SSLinearTransform2::SSLinearTransform2(const float rotate)
	: matrix2(SSMatrix2::identity)
	{ Rotate(rotate); }

SSLinearTransform2::SSLinearTransform2(const float scaleX, const float scaleY)
	: matrix2(scaleX, 0.0f, 0.0f, scaleY){}

SSLinearTransform2::SSLinearTransform2(const SSVector2& axisX, const SSVector2& axisY)
	: matrix2(axisX, axisY) {}

SSLinearTransform2::SSLinearTransform2(const SSMatrix2& m)
	: matrix2(m) {}

SSLinearTransform2& SSLinearTransform2::Identity()
{
	matrix2.SetIdentity();
	return *this;
}

bool SSLinearTransform2::IsIdentity() const
{
	return matrix2.IsIdentity();
}

SSLinearTransform2& SSLinearTransform2::HorizontalShear(float s)
{
	// Horizontal Shear
	// ⎡ 1  S ⎤
	// ⎣ 0  1 ⎦
	matrix2._12 += matrix2._11 * s;
	matrix2._22 += matrix2._21 * s;
	return *this;
}

SSLinearTransform2& SSLinearTransform2::VerticalShear(float s)
{
	// Vertical Shear
	// ⎡ 1  0 ⎤
	// ⎣ S  1 ⎦
	matrix2._11 += matrix2._12 * s;
	matrix2._21 += matrix2._22 * s;
	return *this;
}

SSLinearTransform2& SSLinearTransform2::HorizontalFlip()
{
	// Horizontal filp
	// ⎡-1  0 ⎤
	// ⎣ 0  1 ⎦
	matrix2._11 *= -1.0f;
	matrix2._21 *= -1.0f;
	return *this;
}

SSLinearTransform2& SSLinearTransform2::VerticalFilp()
{
	// Vertival filp
	// ⎡ 1  0 ⎤
	// ⎣ 0 -1 ⎦
	matrix2._12 *= -1.0f;
	matrix2._22 *= -1.0f;
	return *this;
}

SSLinearTransform2& SSLinearTransform2::squeeze(float s)
{
	// Squeeze
	// ⎡ S  0  ⎤
	// ⎣ 0 1/S ⎦
	float inv = 1.0f / s;
	matrix2._11 *= s;
	matrix2._12 *= inv;
	matrix2._21 *= s;
	matrix2._22 *= inv;
	return *this;
}

SSLinearTransform2& SSLinearTransform2::Scale(float x, float y)
{
	// Scale
	// ⎡ X  0 ⎤
	// ⎣ 0  Y ⎦
	matrix2._11 *= x;
	matrix2._12 *= y;
	matrix2._21 *= x;
	matrix2._22 *= y;
	return *this;
}

SSLinearTransform2& SSLinearTransform2::Scale(const SSVector2& v)
{
	return Scale(v.x, v.y);
}

SSLinearTransform2& SSLinearTransform2::Scale(float s)
{
	return Scale(s, s);
}

SSLinearTransform2& SSLinearTransform2::Rotate(float angle)
{
	// Rotate
	// ⎡  cos  sin ⎤
	// ⎣ -sin  cos ⎦
	float cos = cosf(angle);
	float sin = sinf(angle);

	SSMatrix2 n(cos, sin, 
				-sin, cos);
	matrix2.Multiply(n);
	return *this;
}

SSLinearTransform2& SSLinearTransform2::Inverse()
{
	matrix2.Inverse();
	return *this;
}

SSLinearTransform2& SSLinearTransform2::Multiply(const SSMatrix2& m)
{
	matrix2.Multiply(m);
	return *this;
}

SSLinearTransform2& SSLinearTransform2::Multiply(const SSLinearTransform2& lt)
{
	matrix2.Multiply(lt.matrix2);
	return *this;
}

SSLinearTransform2 SSLinearTransform2::operator*(const SSLinearTransform2& lt) const
{
	return SSLinearTransform2(matrix2 * lt.matrix2);
}

SSLinearTransform2& SSLinearTransform2::operator*=(const SSLinearTransform2& lt)
{
	matrix2 *= lt.matrix2;
	return *this;
}

bool SSLinearTransform2::operator==(const SSLinearTransform2& lt) const
{
	return matrix2 == lt.matrix2;
}

bool SSLinearTransform2::operator!=(const SSLinearTransform2& lt) const
{
	return matrix2 != lt.matrix2;
}
