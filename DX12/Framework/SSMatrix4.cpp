#include "SSMatrix4.h"
#include "SSVector4.h"

using namespace SSFramework;

const SSMatrix4 SSMatrix4::identity = SSMatrix4().SetIdentity();

SSMatrix4::SSMatrix4()
	:_11(1), _12(0), _13(0), _14(0),
	 _21(0), _22(1), _23(0), _24(0),
	 _31(0), _32(0), _33(1), _34(0), 
	 _41(0), _42(0), _43(0), _44(1){}

SSMatrix4::SSMatrix4(const SSVector4& row1, const SSVector4& row2, const SSVector4& row3, const SSVector4& row4)
	:_11(row1.x), _12(row1.y), _13(row1.z), _14(row1.w),
	 _21(row2.x), _22(row2.y), _23(row2.z), _24(row2.w), 
	 _31(row3.x), _32(row3.y), _33(row3.z), _34(row3.w), 
	 _41(row4.x), _42(row4.y), _43(row4.z), _44(row4.w){}

SSMatrix4::SSMatrix4(
	float e11, float e12, float e13, float e14,
	float e21, float e22, float e23, float e24,
	float e31, float e32, float e33, float e34,
	float e41, float e42, float e43, float e44)
	:_11(e11), _12(e12), _13(e13), _14(e14),
	 _21(e21), _22(e22), _23(e23), _24(e24), 
	 _31(e31), _32(e32), _33(e33), _34(e34), 
	 _41(e41), _42(e42), _43(e43), _44(e44){}

SSMatrix4& SSMatrix4::SetIdentity()
{
	_11 = _22 = _33 = _44 = 1.0f;
	_12 = _13 = _14 = 0.0f;
	_21 = _23 = _24 = 0.0f;
	_31 = _32 = _34 = 0.0f;
	_41 = _42 = _43 = 0.0f;
	return *this;
}

bool SSMatrix4::IsIdentity() const
{
	return 
		_11 == 1.0f && _12 == 0.0f && _13 == 0.0f && _14 == 0.0f &&
		_21 == 0.0f && _22 == 1.0f && _23 == 0.0f && _24 == 0.0f &&
		_31 == 0.0f && _32 == 0.0f && _33 == 1.0f && _34 == 0.0f &&
		_41 == 0.0f && _42 == 0.0f && _43 == 0.0f && _44 == 1.0f;
}

SSMatrix4& SSMatrix4::Transpose()
{
	SSMatrix4 n(*this);

	this->_12 = n._21;
	this->_13 = n._31;
	this->_14 = n._41;
				
	this->_21 = n._12;
	this->_23 = n._32;
	this->_24 = n._42;
				
	this->_31 = n._13;
	this->_32 = n._23;
	this->_34 = n._43;
				
	this->_41 = n._14;
	this->_42 = n._24;
	this->_43 = n._34;

	return *this;
}


SSMatrix4& SSMatrix4::Multiply(const SSMatrix4& m)
{
	SSMatrix4 n(*this);
	this->_11 = (n._11 * m._11) + (n._12 * m._21) + (n._13 * m._31) + (n._14 * m._41);
	this->_12 = (n._11 * m._12) + (n._12 * m._22) + (n._13 * m._32) + (n._14 * m._42);
	this->_13 = (n._11 * m._13) + (n._12 * m._23) + (n._13 * m._33) + (n._14 * m._43);
	this->_14 = (n._11 * m._14) + (n._12 * m._24) + (n._13 * m._34) + (n._14 * m._44);
	this->_21 = (n._21 * m._11) + (n._22 * m._21) + (n._23 * m._31) + (n._24 * m._41);
	this->_22 = (n._21 * m._12) + (n._22 * m._22) + (n._23 * m._32) + (n._24 * m._42);
	this->_23 = (n._21 * m._13) + (n._22 * m._23) + (n._23 * m._33) + (n._24 * m._43);
	this->_24 = (n._21 * m._14) + (n._22 * m._24) + (n._23 * m._34) + (n._24 * m._44);
	this->_31 = (n._31 * m._11) + (n._32 * m._21) + (n._33 * m._31) + (n._34 * m._41);
	this->_32 = (n._31 * m._12) + (n._32 * m._22) + (n._33 * m._32) + (n._34 * m._42);
	this->_33 = (n._31 * m._13) + (n._32 * m._23) + (n._33 * m._33) + (n._34 * m._43);
	this->_34 = (n._31 * m._14) + (n._32 * m._24) + (n._33 * m._34) + (n._34 * m._44);
	this->_41 = (n._41 * m._11) + (n._42 * m._21) + (n._43 * m._31) + (n._44 * m._41);
	this->_42 = (n._41 * m._12) + (n._42 * m._22) + (n._43 * m._32) + (n._44 * m._42);
	this->_43 = (n._41 * m._13) + (n._42 * m._23) + (n._43 * m._33) + (n._44 * m._43);
	this->_44 = (n._41 * m._14) + (n._42 * m._24) + (n._43 * m._34) + (n._44 * m._44);
	return *this;
}

float SSMatrix4::Determinant() const
{
	return 
		(_14 * _23 * _32 * _41) - (_13 * _24 * _32 * _41) - (_14 * _22 * _33 * _41) + (_12 * _24 * _33 * _41) + 
		(_13 * _22 * _34 * _41) - (_12 * _23 * _34 * _41) - (_14 * _23 * _31 * _42) + (_13 * _24 * _31 * _42) + 
		(_14 * _21 * _33 * _42) - (_11 * _24 * _33 * _42) - (_13 * _21 * _34 * _42) + (_11 * _23 * _34 * _42) +
		(_14 * _22 * _31 * _43) - (_12 * _24 * _31 * _43) - (_14 * _21 * _32 * _43) + (_11 * _24 * _32 * _43) + 
		(_12 * _21 * _34 * _43) - (_11 * _22 * _34 * _43) - (_13 * _22 * _31 * _44) + (_12 * _23 * _31 * _44) + 
		(_13 * _21 * _32 * _44) - (_11 * _23 * _32 * _44) - (_12 * _21 * _33 * _44) + (_11 * _22 * _33 * _44);
}

SSMatrix4 SSMatrix4::InverseMatrix(bool* r, float* d) const
{
	SSMatrix4 n;
	float det = Determinant();
	bool result = false;

	if (det != 0.0f)
	{
		float detInv = 1.0f / det;
		n._11 = ((_23 * _34 * _42) - (_24 * _33 * _42) + (_24 * _32 * _43) - (_22 * _34 * _43) - (_23 * _32 * _44) + (_22 * _33 * _44)) * detInv;
		n._12 = ((_14 * _33 * _42) - (_13 * _34 * _42) - (_14 * _32 * _43) + (_12 * _34 * _43) + (_13 * _32 * _44) - (_12 * _33 * _44)) * detInv;
		n._13 = ((_13 * _24 * _42) - (_14 * _23 * _42) + (_14 * _22 * _43) - (_12 * _24 * _43) - (_13 * _22 * _44) + (_12 * _23 * _44)) * detInv;
		n._14 = ((_14 * _23 * _32) - (_13 * _24 * _32) - (_14 * _22 * _33) + (_12 * _24 * _33) + (_13 * _22 * _34) - (_12 * _23 * _34)) * detInv;
		n._21 = ((_24 * _33 * _41) - (_23 * _34 * _41) - (_24 * _31 * _43) + (_21 * _34 * _43) + (_23 * _31 * _44) - (_21 * _33 * _44)) * detInv;
		n._22 = ((_13 * _34 * _41) - (_14 * _33 * _41) + (_14 * _31 * _43) - (_11 * _34 * _43) - (_13 * _31 * _44) + (_11 * _33 * _44)) * detInv;
		n._23 = ((_14 * _23 * _41) - (_13 * _24 * _41) - (_14 * _21 * _43) + (_11 * _24 * _43) + (_13 * _21 * _44) - (_11 * _23 * _44)) * detInv;
		n._24 = ((_13 * _24 * _31) - (_14 * _23 * _31) + (_14 * _21 * _33) - (_11 * _24 * _33) - (_13 * _21 * _34) + (_11 * _23 * _34)) * detInv;
		n._31 = ((_22 * _34 * _41) - (_24 * _32 * _41) + (_24 * _31 * _42) - (_21 * _34 * _42) - (_22 * _31 * _44) + (_21 * _32 * _44)) * detInv;
		n._32 = ((_14 * _32 * _41) - (_12 * _34 * _41) - (_14 * _31 * _42) + (_11 * _34 * _42) + (_12 * _31 * _44) - (_11 * _32 * _44)) * detInv;
		n._33 = ((_12 * _24 * _41) - (_14 * _22 * _41) + (_14 * _21 * _42) - (_11 * _24 * _42) - (_12 * _21 * _44) + (_11 * _22 * _44)) * detInv;
		n._34 = ((_14 * _22 * _31) - (_12 * _24 * _31) - (_14 * _21 * _32) + (_11 * _24 * _32) + (_12 * _21 * _34) - (_11 * _22 * _34)) * detInv;
		n._41 = ((_23 * _32 * _41) - (_22 * _33 * _41) - (_23 * _31 * _42) + (_21 * _33 * _42) + (_22 * _31 * _43) - (_21 * _32 * _43)) * detInv;
		n._42 = ((_12 * _33 * _41) - (_13 * _32 * _41) + (_13 * _31 * _42) - (_11 * _33 * _42) - (_12 * _31 * _43) + (_11 * _32 * _43)) * detInv;
		n._43 = ((_13 * _22 * _41) - (_12 * _23 * _41) - (_13 * _21 * _42) + (_11 * _23 * _42) + (_12 * _21 * _43) - (_11 * _22 * _43)) * detInv;
		n._44 = ((_12 * _23 * _31) - (_13 * _22 * _31) + (_13 * _21 * _32) - (_11 * _23 * _32) - (_12 * _21 * _33) + (_11 * _22 * _33)) * detInv;

		result = true;
		if (d)
			*d = det;
	}
	else
		n.SetIdentity();

	if (r)
		*r = result;

	return n;
}

SSMatrix4& SSMatrix4::Inverse(bool* r, float* d)
{
	bool b;
	SSMatrix4 n = this->InverseMatrix(&b, d);
	if (b)
		*this = n;
	if (r)
		*r = b;
	return *this;
}

SSMatrix4 SSMatrix4::TransposeMatrix() const
{
	SSMatrix4 n(*this);
	return n.Transpose();
}

bool SSMatrix4::operator==(const SSMatrix4& m) const
{
	return 
		this->val[0x0] == m.val[0x0] &&
		this->val[0x1] == m.val[0x1] &&
		this->val[0x2] == m.val[0x2] &&
		this->val[0x3] == m.val[0x3] &&
		this->val[0x4] == m.val[0x4] &&
		this->val[0x5] == m.val[0x5] &&
		this->val[0x6] == m.val[0x6] &&
		this->val[0x7] == m.val[0x7] &&
		this->val[0x8] == m.val[0x8] &&
		this->val[0x9] == m.val[0x9] &&
		this->val[0xa] == m.val[0xa] &&
		this->val[0xb] == m.val[0xb] &&
		this->val[0xc] == m.val[0xc] &&
		this->val[0xd] == m.val[0xd] &&
		this->val[0xe] == m.val[0xe] &&
		this->val[0xf] == m.val[0xf];
}

bool SSMatrix4::operator!=(const SSMatrix4& m) const
{
	return 
		this->val[0x0] != m.val[0x0] ||
		this->val[0x1] != m.val[0x1] ||
		this->val[0x2] != m.val[0x2] ||
		this->val[0x3] != m.val[0x3] ||
		this->val[0x4] != m.val[0x4] ||
		this->val[0x5] != m.val[0x5] ||
		this->val[0x6] != m.val[0x6] ||
		this->val[0x7] != m.val[0x7] ||
		this->val[0x8] != m.val[0x8] ||
		this->val[0x9] != m.val[0x9] ||
		this->val[0xa] != m.val[0xa] ||
		this->val[0xb] != m.val[0xb] ||
		this->val[0xc] != m.val[0xc] ||
		this->val[0xd] != m.val[0xd] ||
		this->val[0xe] != m.val[0xe] ||
		this->val[0xf] != m.val[0xf];
}

SSMatrix4 SSMatrix4::operator+(const SSMatrix4& m) const
{
	SSMatrix4 n;
	n.val[0x0] = this->val[0x0] + m.val[0x0];
	n.val[0x1] = this->val[0x1] + m.val[0x1];
	n.val[0x2] = this->val[0x2] + m.val[0x2];
	n.val[0x3] = this->val[0x3] + m.val[0x3];
	n.val[0x4] = this->val[0x4] + m.val[0x4];
	n.val[0x5] = this->val[0x5] + m.val[0x5];
	n.val[0x6] = this->val[0x6] + m.val[0x6];
	n.val[0x7] = this->val[0x7] + m.val[0x7];
	n.val[0x8] = this->val[0x8] + m.val[0x8];
	n.val[0x9] = this->val[0x9] + m.val[0x9];
	n.val[0xa] = this->val[0xa] + m.val[0xa];
	n.val[0xb] = this->val[0xb] + m.val[0xb];
	n.val[0xc] = this->val[0xc] + m.val[0xc];
	n.val[0xd] = this->val[0xd] + m.val[0xd];
	n.val[0xe] = this->val[0xe] + m.val[0xe];
	n.val[0xf] = this->val[0xf] + m.val[0xf];
	return n;
}

SSMatrix4 SSMatrix4::operator-(const SSMatrix4& m) const
{
	SSMatrix4 n;
	n.val[0x0] = this->val[0x0] - m.val[0x0];
	n.val[0x1] = this->val[0x1] - m.val[0x1];
	n.val[0x2] = this->val[0x2] - m.val[0x2];
	n.val[0x3] = this->val[0x3] - m.val[0x3];
	n.val[0x4] = this->val[0x4] - m.val[0x4];
	n.val[0x5] = this->val[0x5] - m.val[0x5];
	n.val[0x6] = this->val[0x6] - m.val[0x6];
	n.val[0x7] = this->val[0x7] - m.val[0x7];
	n.val[0x8] = this->val[0x8] - m.val[0x8];
	n.val[0x9] = this->val[0x9] - m.val[0x9];
	n.val[0xa] = this->val[0xa] - m.val[0xa];
	n.val[0xb] = this->val[0xb] - m.val[0xb];
	n.val[0xc] = this->val[0xc] - m.val[0xc];
	n.val[0xd] = this->val[0xd] - m.val[0xd];
	n.val[0xe] = this->val[0xe] - m.val[0xe];
	n.val[0xf] = this->val[0xf] - m.val[0xf];
	return n;
}

SSMatrix4 SSMatrix4::operator*(const SSMatrix4& m) const
{
	SSMatrix4 n;
	n._11 = (_11 * m._11) + (_12 * m._21) + (_13 * m._31) + (_14 * m._41);
	n._12 = (_11 * m._12) + (_12 * m._22) + (_13 * m._32) + (_14 * m._42);
	n._13 = (_11 * m._13) + (_12 * m._23) + (_13 * m._33) + (_14 * m._43);
	n._14 = (_11 * m._14) + (_12 * m._24) + (_13 * m._34) + (_14 * m._44);
	n._21 = (_21 * m._11) + (_22 * m._21) + (_23 * m._31) + (_24 * m._41);
	n._22 = (_21 * m._12) + (_22 * m._22) + (_23 * m._32) + (_24 * m._42);
	n._23 = (_21 * m._13) + (_22 * m._23) + (_23 * m._33) + (_24 * m._43);
	n._24 = (_21 * m._14) + (_22 * m._24) + (_23 * m._34) + (_24 * m._44);
	n._31 = (_31 * m._11) + (_32 * m._21) + (_33 * m._31) + (_34 * m._41);
	n._32 = (_31 * m._12) + (_32 * m._22) + (_33 * m._32) + (_34 * m._42);
	n._33 = (_31 * m._13) + (_32 * m._23) + (_33 * m._33) + (_34 * m._43);
	n._34 = (_31 * m._14) + (_32 * m._24) + (_33 * m._34) + (_34 * m._44);
	n._41 = (_41 * m._11) + (_42 * m._21) + (_43 * m._31) + (_44 * m._41);
	n._42 = (_41 * m._12) + (_42 * m._22) + (_43 * m._32) + (_44 * m._42);
	n._43 = (_41 * m._13) + (_42 * m._23) + (_43 * m._33) + (_44 * m._43);
	n._44 = (_41 * m._14) + (_42 * m._24) + (_43 * m._34) + (_44 * m._44);
	return n;
}

SSMatrix4 SSMatrix4::operator*(float f) const
{
	SSMatrix4 n;
	n.val[0x0] = this->val[0x0] * f;
	n.val[0x1] = this->val[0x1] * f;
	n.val[0x2] = this->val[0x2] * f;
	n.val[0x3] = this->val[0x3] * f;
	n.val[0x4] = this->val[0x4] * f;
	n.val[0x5] = this->val[0x5] * f;
	n.val[0x6] = this->val[0x6] * f;
	n.val[0x7] = this->val[0x7] * f;
	n.val[0x8] = this->val[0x8] * f;
	n.val[0x9] = this->val[0x9] * f;
	n.val[0xa] = this->val[0xa] * f;
	n.val[0xb] = this->val[0xb] * f;
	n.val[0xc] = this->val[0xc] * f;
	n.val[0xd] = this->val[0xd] * f;
	n.val[0xe] = this->val[0xe] * f;
	n.val[0xf] = this->val[0xf] * f;
	return n;
}

SSMatrix4 SSMatrix4::operator/(float f) const
{
	float inv = 1.0f / f;
	SSMatrix4 n;
	n.val[0x0] = this->val[0x0] * inv;
	n.val[0x1] = this->val[0x1] * inv;
	n.val[0x2] = this->val[0x2] * inv;
	n.val[0x3] = this->val[0x3] * inv;
	n.val[0x4] = this->val[0x4] * inv;
	n.val[0x5] = this->val[0x5] * inv;
	n.val[0x6] = this->val[0x6] * inv;
	n.val[0x7] = this->val[0x7] * inv;
	n.val[0x8] = this->val[0x8] * inv;
	n.val[0x9] = this->val[0x9] * inv;
	n.val[0xa] = this->val[0xa] * inv;
	n.val[0xb] = this->val[0xb] * inv;
	n.val[0xc] = this->val[0xc] * inv;
	n.val[0xd] = this->val[0xd] * inv;
	n.val[0xe] = this->val[0xe] * inv;
	n.val[0xf] = this->val[0xf] * inv;
	return n;
}

SSMatrix4& SSMatrix4::operator+=(const SSMatrix4& m)
{
	this->val[0x0] += m.val[0x0];
	this->val[0x1] += m.val[0x1];
	this->val[0x2] += m.val[0x2];
	this->val[0x3] += m.val[0x3];
	this->val[0x4] += m.val[0x4];
	this->val[0x5] += m.val[0x5];
	this->val[0x6] += m.val[0x6];
	this->val[0x7] += m.val[0x7];
	this->val[0x8] += m.val[0x8];
	this->val[0x9] += m.val[0x9];
	this->val[0xa] += m.val[0xa];
	this->val[0xb] += m.val[0xb];
	this->val[0xc] += m.val[0xc];
	this->val[0xd] += m.val[0xd];
	this->val[0xe] += m.val[0xe];
	this->val[0xf] += m.val[0xf];
	return *this;
}

SSMatrix4& SSMatrix4::operator-=(const SSMatrix4& m)
{
	this->val[0x0] -= m.val[0x0];
	this->val[0x1] -= m.val[0x1];
	this->val[0x2] -= m.val[0x2];
	this->val[0x3] -= m.val[0x3];
	this->val[0x4] -= m.val[0x4];
	this->val[0x5] -= m.val[0x5];
	this->val[0x6] -= m.val[0x6];
	this->val[0x7] -= m.val[0x7];
	this->val[0x8] -= m.val[0x8];
	this->val[0x9] -= m.val[0x9];
	this->val[0xa] -= m.val[0xa];
	this->val[0xb] -= m.val[0xb];
	this->val[0xc] -= m.val[0xc];
	this->val[0xd] -= m.val[0xd];
	this->val[0xe] -= m.val[0xe];
	this->val[0xf] -= m.val[0xf];
	return *this;
}

SSMatrix4& SSMatrix4::operator*=(const SSMatrix4& m)
{
	return this->Multiply(m);
}

SSMatrix4& SSMatrix4::operator*=(float f)
{
	this->val[0x0] *= f;
	this->val[0x1] *= f;
	this->val[0x2] *= f;
	this->val[0x3] *= f;
	this->val[0x4] *= f;
	this->val[0x5] *= f;
	this->val[0x6] *= f;
	this->val[0x7] *= f;
	this->val[0x8] *= f;
	this->val[0x9] *= f;
	this->val[0xa] *= f;
	this->val[0xb] *= f;
	this->val[0xc] *= f;
	this->val[0xd] *= f;
	this->val[0xe] *= f;
	this->val[0xf] *= f;
	return *this;
}

SSMatrix4& SSMatrix4::operator/=(float f)
{
	float inv = 1.0f / f;
	this->val[0x0] *= inv;
	this->val[0x1] *= inv;
	this->val[0x2] *= inv;
	this->val[0x3] *= inv;
	this->val[0x4] *= inv;
	this->val[0x5] *= inv;
	this->val[0x6] *= inv;
	this->val[0x7] *= inv;
	this->val[0x8] *= inv;
	this->val[0x9] *= inv;
	this->val[0xa] *= inv;
	this->val[0xb] *= inv;
	this->val[0xc] *= inv;
	this->val[0xd] *= inv;
	this->val[0xe] *= inv;
	this->val[0xf] *= inv;
	return *this;
}

SSVector4 SSMatrix4::Row1() const
{
	return SSVector4(_11, _12, _13, _14);
}

SSVector4 SSMatrix4::Row2() const
{
	return SSVector4(_21, _22, _23, _24);
}

SSVector4 SSMatrix4::Row3() const
{
	return SSVector4(_31, _32, _33, _34);
}

SSVector4 SSMatrix4::Row4() const
{
	return SSVector4(_41, _42, _43, _44);
}

SSVector4 SSMatrix4::Col1() const
{
	return SSVector4(_11, _21, _31, _41);
}

SSVector4 SSMatrix4::Col2() const
{
	return SSVector4(_12, _22, _32, _42);
}

SSVector4 SSMatrix4::Col3() const
{
	return SSVector4(_13, _23, _33, _43);
}

SSVector4 SSMatrix4::Col4() const
{
	return SSVector4(_14, _24, _34, _44);
}
