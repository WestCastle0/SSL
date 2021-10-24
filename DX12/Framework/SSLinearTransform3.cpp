#include "SSMath.h"
#include "SSLinearTransform3.h"

using namespace SSFramework;

SSLinearTransform3::SSLinearTransform3()
	: matrix3(SSMatrix3::identity) {}

//SSLinearTransform3::SSLinearTransform3(const SSQuaternion& q)
//	: matrix3(q.Matrix3()) {}

SSLinearTransform3::SSLinearTransform3(const float scaleX, const float scaleY, const float scaleZ)
	: matrix3(
		scaleX, 0.0f, 0.0f, 
		0.0f, scaleY, 0.0f,
		0.0f, 0.0f, scaleZ) {}

SSLinearTransform3::SSLinearTransform3(const SSVector3& axisX, const SSVector3& axisY, const SSVector3& axisZ)
	: matrix3(axisX, axisY, axisZ) {}

SSLinearTransform3::SSLinearTransform3(const SSMatrix3& m)
	: matrix3(m) {}

SSLinearTransform3& SSLinearTransform3::Identity()
{
	matrix3.SetIdentity();
	return *this;
}

bool SSLinearTransform3::IsIdentity() const
{
	return matrix3.IsIdentity();
}

SSLinearTransform3& SSLinearTransform3::Scale(float x, float y, float z)
{
	// Scale
	// ⎡ X 0 0 ⎤
	// ⎢ 0 Y 0 ⎥
	// ⎣ 0 0 Z ⎦
	matrix3._11 *= x; matrix3._12 *= y; matrix3._13 *= z;
	matrix3._21 *= x; matrix3._22 *= y; matrix3._23 *= z;
	matrix3._31 *= x; matrix3._32 *= y; matrix3._33 *= z;
	return *this;
}

SSLinearTransform3& SSLinearTransform3::Scale(const SSVector3& v)
{
	return Scale(v.x, v.y, v.z);
}

SSLinearTransform3& SSLinearTransform3::Scale(float s)
{
	return Scale(s, s, s);
}

SSLinearTransform3& SSFramework::SSLinearTransform3::RotateX(float angle)
{
	// X - Axis
	// ⎡ 1   0   0  ⎤
	// ⎢ 0  cos sin ⎥
	// ⎣ 0 -sin cos ⎦
	float cos = cosf(angle);
	float sin = sinf(angle);

	SSMatrix3 n;
	n.SetIdentity();
	n._22 = cos; n._23 = sin;
	n._32 = -sin; n._33 = cos;
	matrix3.Multiply(n);
	return *this;
}

SSLinearTransform3& SSFramework::SSLinearTransform3::RotateY(float angle)
{
	// Y - Axis
	// ⎡ cos 0 -sin ⎤
	// ⎢  0  1   0  ⎥
	// ⎣ sin 0  cos ⎦
	float cos = cosf(angle);
	float sin = sinf(angle);

	SSMatrix3 n;
	n.SetIdentity();
	n._11 = cos; n._13 = -sin;
	n._31 = sin; n._33 = cos;
	matrix3.Multiply(n);
	return *this;
}

SSLinearTransform3& SSFramework::SSLinearTransform3::RotateZ(float angle)
{
	// Z - Axis
	// ⎡ cos sin 0 ⎤
	// ⎢-sin cos 0 ⎥
	// ⎣  0   0  1 ⎦
	float cos = cosf(angle);
	float sin = sinf(angle);

	SSMatrix3 n;
	n.SetIdentity();
	n._11 = cos; n._12 = sin;
	n._21 = -sin; n._22 = cos;
	matrix3.Multiply(n);
	return *this;
}

SSLinearTransform3& SSLinearTransform3::Rotate(const SSVector3& axis, float angle)
{
	if (angle == 0.0f)
		return *this;
	float cos = cosf(angle);
	float sin = sinf(angle);

	SSVector3 n = axis;
	n.Normalize();

	SSLinearTransform3 lt;
	lt.Identity();
	lt.matrix3._11 = cos + n.x * n.x * (1 - cos);
	lt.matrix3._12 = n.x * n.y * (1 - cos) - n.z * sin;
	lt.matrix3._13 = n.x * n.z * (1 - cos) + n.y * sin;
	lt.matrix3._21 = n.y * n.x * (1 - cos) + n.z * sin;
	lt.matrix3._22 = cos + n.y * n.y * (1 - cos);
	lt.matrix3._23 = n.y * n.z * (1 - cos) - n.x * sin;
	lt.matrix3._31 = n.z * n.x * (1 - cos) - n.y * sin;
	lt.matrix3._32 = n.z * n.y * (1 - cos) - n.x * sin;
	lt.matrix3._33 = cos + n.z * n.z * (1 - cos);

	return Multiply(lt);

	//matrix3.Multiply(SSQuaternion(axis, r).Matrix3());
	//return *this;
}

SSLinearTransform3& SSLinearTransform3::squeeze(const SSVector3& axis, float s)
{
	//// generalization formula
	return *this;
}

SSLinearTransform3& SSLinearTransform3::Inverse()
{
	matrix3.Inverse();
	return *this;
}

SSLinearTransform3& SSLinearTransform3::Multiply(const SSMatrix3& m)
{
	matrix3.Multiply(m);
	return *this;
}

SSLinearTransform3& SSLinearTransform3::Multiply(const SSLinearTransform3& lt)
{
	matrix3.Multiply(lt.matrix3);
	return *this;
}

SSLinearTransform3 SSLinearTransform3::operator*(const SSLinearTransform3& lt) const
{
	return SSLinearTransform3(matrix3 * lt.matrix3);
}

SSLinearTransform3& SSLinearTransform3::operator*=(const SSLinearTransform3& lt)
{
	matrix3 *= lt.matrix3;
	return *this;
}

bool SSLinearTransform3::operator==(const SSLinearTransform3& lt) const
{
	return matrix3 == lt.matrix3;
}

bool SSLinearTransform3::operator!=(const SSLinearTransform3& lt) const
{
	return matrix3 != lt.matrix3;
}
