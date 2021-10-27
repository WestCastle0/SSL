#include "SSAffineTransform2.h"

using namespace SSFramework;

SSAffineTransform2::SSAffineTransform2(const SSVector2& translate)
	: matrix2(SSMatrix2::identity)
	, translation(translate) {}

SSAffineTransform2::SSAffineTransform2(const SSLinearTransform2& linear, const SSVector2& translate)
	: matrix2(linear.Matrix2())
	, translation(translate) {}

SSAffineTransform2::SSAffineTransform2(const SSVector2& axisX, const SSVector2& axisY, const SSVector2& translate)
	: matrix2(axisX, axisY)
	, translation(translate) {}

SSAffineTransform2::SSAffineTransform2(const float x, const float y)
	: matrix2(SSMatrix2::identity)
	, translation(x, y) {}

SSAffineTransform2::SSAffineTransform2(const SSMatrix3& m)
	: matrix2(
		m._11, m._12,
		m._21, m._22)
	, translation(m._31, m._32) {}

SSAffineTransform2& SSAffineTransform2::Identity()
{
	matrix2.SetIdentity();
	translation = SSVector2::zero;
	return *this;
}

bool SSAffineTransform2::IsIdentity() const
{
	if (translation.x == 0.0f && translation.y == 0.0f)
		return matrix2.IsIdentity();
	return false;
}

SSAffineTransform2& SSAffineTransform2::Translate(float x, float y)
{
	// AffineTransform Translate
	// ⎡ 1 0 0 ⎤
	// ⎢ 0 1 0 ⎥
	// ⎣ X Y 1 ⎦

	translation.x += x;
	translation.y += y;
	return *this;
}

SSAffineTransform2& SSAffineTransform2::Translate(const SSVector2& v)
{
	return Translate(v.x, v.y);
}

SSAffineTransform2& SSAffineTransform2::Inverse()
{
	matrix2.Inverse();
	translation = -translation * matrix2;
	return *this;
}

SSAffineTransform2& SSAffineTransform2::Multiply(const SSLinearTransform2& lt)
{
	translation *= lt.matrix2;
	matrix2 *= lt.matrix2;
	return *this;
}

SSAffineTransform2& SSAffineTransform2::Multiply(const SSAffineTransform2& at)
{
	translation = translation * at.matrix2 + at.translation;
	matrix2 *= at.matrix2;
	return *this;
}

SSAffineTransform2& SSAffineTransform2::operator*(const SSLinearTransform2& lt) const
{
	return SSAffineTransform2(*this).Multiply(lt);
}

SSAffineTransform2& SSAffineTransform2::operator*(const SSAffineTransform2& at) const
{
	return SSAffineTransform2(*this).Multiply(at);
}

SSAffineTransform2& SSAffineTransform2::operator*=(const SSLinearTransform2& lt)
{
	return Multiply(lt);
}

SSAffineTransform2& SSAffineTransform2::operator*=(const SSAffineTransform2& at)
{
	return Multiply(at);
}

bool SSAffineTransform2::operator==(const SSAffineTransform2& at) const
{
	if (translation == at.translation)
		return matrix2 == at.matrix2;
	return false;
}

bool SSAffineTransform2::operator!=(const SSAffineTransform2& at) const
{
	if (translation != at.translation)
		return true;
	return matrix2 != at.matrix2;
}

SSMatrix3 SSAffineTransform2::Matrix3() const
{
	return SSMatrix3(
		matrix2._11, matrix2._12, 0.0f,
		matrix2._21, matrix2._22, 0.0f,
		translation.x, translation.y, 1.0f);
}
