#include "SSAffineTransform3.h"

using namespace SSFramework;

SSAffineTransform3::SSAffineTransform3(const SSVector3& translate)
	: matrix3(SSMatrix3::identity)
	, translation(translate) {}

SSAffineTransform3::SSAffineTransform3(const SSLinearTransform3& linear, const SSVector3& translate)
	: matrix3(linear.Matrix3())
	, translation(translate) {}

SSAffineTransform3::SSAffineTransform3(const SSVector3& left, const SSVector3& up, const SSVector3& forward, const SSVector3& translate)
	: matrix3(left, up, forward)
	, translation(translate) {}

SSAffineTransform3::SSAffineTransform3(const float x, const float y, const float z)
	: matrix3(SSMatrix3::identity)
	, translation(x, y, z) {}

SSAffineTransform3::SSAffineTransform3(const SSMatrix4& m)
	: matrix3(
		m._11, m._12, m._13,
		m._21, m._22, m._23,
		m._31, m._32, m._33)
	, translation(m._41, m._42, m._43) {}

SSAffineTransform3& SSAffineTransform3::Identity()
{
	matrix3.SetIdentity();
	translation = SSVector3::zero;
	return *this;
}

bool SSAffineTransform3::IsIdentity() const
{
	if (translation.x == 0.0f && translation.y == 0.0f && translation.z == 0.0f)
		return matrix3.IsIdentity();
	return false;
}

SSAffineTransform3& SSAffineTransform3::Translate(float x, float y, float z)
{
	// AffineTransform Translate
	// ⎡ 1 0 0 0 ⎤
	// ⎢ 0 1 0 0 ⎥
	// ⎣ 0 0 1 0 ⎦
	// ⎣ X Y Z 1 ⎦

	translation.x += x;
	translation.y += y;
	translation.z += z;
	return *this;
}

SSAffineTransform3& SSAffineTransform3::Translate(const SSVector3& v)
{
	return Translate(v.x, v.y, v.z);
}

SSAffineTransform3& SSAffineTransform3::Inverse()
{
	matrix3.Inverse();
	translation = -translation * matrix3;
	return *this;
}

SSAffineTransform3& SSAffineTransform3::Multiply(const SSLinearTransform3& lt)
{
	translation *= lt.matrix3;
	matrix3 *= lt.matrix3;
	return *this;
}

SSAffineTransform3& SSAffineTransform3::Multiply(const SSAffineTransform3& at)
{
	translation = translation * at.matrix3 + at.translation;
	matrix3 *= at.matrix3;
	return *this;
}

SSAffineTransform3& SSAffineTransform3::operator*(const SSLinearTransform3& lt) const
{
	return SSAffineTransform3(*this).Multiply(lt);
}

SSAffineTransform3& SSAffineTransform3::operator*(const SSAffineTransform3& at) const
{
	return SSAffineTransform3(*this).Multiply(at);
}

SSAffineTransform3& SSAffineTransform3::operator*=(const SSLinearTransform3& lt)
{
	return Multiply(lt);
}

SSAffineTransform3& SSAffineTransform3::operator*=(const SSAffineTransform3& at)
{
	return Multiply(at);
}

bool SSAffineTransform3::operator==(const SSAffineTransform3& at) const
{
	if (translation == at.translation)
		return matrix3 == at.matrix3;
	return false;
}

bool SSAffineTransform3::operator!=(const SSAffineTransform3& at) const
{
	if (translation != at.translation)
		return true;
	return matrix3 != at.matrix3;
}

SSMatrix4 SSAffineTransform3::Matrix4() const
{
	return SSMatrix4(
		matrix3._11, matrix3._12, matrix3._13, 0.0f,
		matrix3._21, matrix3._22, matrix3._23, 0.0f,
		matrix3._31, matrix3._32, matrix3._33, 0.0f,
		translation.x, translation.y, translation.z, 1.0f);
}
