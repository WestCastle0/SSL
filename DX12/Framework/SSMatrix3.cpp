#include "SSMatrix3.h"
#include "SSVector3.h"

using namespace SSFramework;

const SSMatrix3 SSMatrix3::identity = SSMatrix3().SetIdentity();

SSMatrix3::SSMatrix3()
	:_11(1), _12(0), _13(0),
	 _21(0), _22(1), _23(0), 
	 _31(0), _32(0), _33(1){}

SSMatrix3::SSMatrix3(const SSVector3& row1, const SSVector3& row2, const SSVector3& row3)
	: _11(row1.x), _12(row1.y), _13(row1.z),
	  _21(row2.x), _22(row2.y), _23(row2.z),
	  _31(row3.x), _32(row3.y), _33(row3.z){}

SSMatrix3::SSMatrix3(
	float e11, float e12, float e13,
	float e21, float e22, float e23,
	float e31, float e32, float e33)
	:_11(e11), _12(e12), _13(e13),
	 _21(e21), _22(e22), _23(e23),
	 _31(e31), _32(e32), _33(e33){}

SSMatrix3& SSMatrix3::SetIdentity()
{
	_11 = _22 = _33 = 1.0f;
	_12 = _13 = 0.0f;
	_21 = _23 = 0.0f;
	_31 = _32 = 0.0f;
	return *this;
}

bool SSMatrix3::IsIdentity() const
{
	return 
		_11 == 1.0f && _12 == 0.0f && _13 == 0.0f &&
		_21 == 0.0f && _22 == 1.0f && _23 == 0.0f &&
		_31 == 0.0f && _32 == 0.0f && _33 == 1.0f;
}

SSMatrix3& SSMatrix3::Transpose()
{
	SSMatrix3 n(*this);

	this->_12 = n._21;
	this->_13 = n._31;
				
	this->_21 = n._12;
	this->_23 = n._32;
				
	this->_31 = n._13;
	this->_32 = n._23;

	return *this;
}


SSMatrix3& SSMatrix3::Multiply(const SSMatrix3& m)
{
	SSMatrix3 n(*this);
	this->_11 = (n._11 * m._11) + (n._12 * m._21) + (n._13 * m._31);
	this->_12 = (n._11 * m._12) + (n._12 * m._22) + (n._13 * m._32);
	this->_13 = (n._11 * m._13) + (n._12 * m._23) + (n._13 * m._33);
	this->_21 = (n._21 * m._11) + (n._22 * m._21) + (n._23 * m._31);
	this->_22 = (n._21 * m._12) + (n._22 * m._22) + (n._23 * m._32);
	this->_23 = (n._21 * m._13) + (n._22 * m._23) + (n._23 * m._33);
	this->_31 = (n._31 * m._11) + (n._32 * m._21) + (n._33 * m._31);
	this->_32 = (n._31 * m._12) + (n._32 * m._22) + (n._33 * m._32);
	this->_33 = (n._31 * m._13) + (n._32 * m._23) + (n._33 * m._33);
	return *this;
}

float SSMatrix3::Determinant() const
{
	return 
		(_11 * _22 * _33) - (_11 * _23 * _32) - 
		(_12 * _21 * _33) + (_12 * _23 * _31) + 
		(_13 * _21 * _32) - (_13 * _22 * _31);
}

SSMatrix3 SSMatrix3::InverseMatrix(bool* r, float* d) const
{
	SSMatrix3 n;
	float det = Determinant();
	bool result = false;

	if (det != 0.0f)
	{
		float detInv = 1.0f / det;
		n._11 = (_22 * _33 - _23 * _32) * detInv;
		n._12 = (_13 * _32 - _12 * _33) * detInv;
		n._13 = (_12 * _23 - _13 * _22) * detInv;
		n._21 = (_23 * _31 - _21 * _33) * detInv;
		n._22 = (_11 * _33 - _13 * _31) * detInv;
		n._23 = (_13 * _21 - _11 * _23) * detInv;
		n._31 = (_21 * _32 - _22 * _31) * detInv;
		n._32 = (_12 * _31 - _11 * _32) * detInv;
		n._33 = (_11 * _22 - _12 * _21) * detInv;
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

SSMatrix3& SSMatrix3::Inverse(bool* r, float* d)
{
	bool b;
	SSMatrix3 n = this->InverseMatrix(&b, d);
	if (b)
		*this = n;
	if (r)
		*r = b;
	return *this;
}

SSMatrix3 SSMatrix3::TransposeMatrix() const
{
	SSMatrix3 n(*this);
	return n.Transpose();
}

bool SSMatrix3::operator==(const SSMatrix3& m) const
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
		this->val[0x8] == m.val[0x8];
}

bool SSMatrix3::operator!=(const SSMatrix3& m) const
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
		this->val[0x8] != m.val[0x8];
}

SSMatrix3 SSMatrix3::operator+(const SSMatrix3& m) const
{
	SSMatrix3 n;
	n.val[0x0] = this->val[0x0] + m.val[0x0];
	n.val[0x1] = this->val[0x1] + m.val[0x1];
	n.val[0x2] = this->val[0x2] + m.val[0x2];
	n.val[0x3] = this->val[0x3] + m.val[0x3];
	n.val[0x4] = this->val[0x4] + m.val[0x4];
	n.val[0x5] = this->val[0x5] + m.val[0x5];
	n.val[0x6] = this->val[0x6] + m.val[0x6];
	n.val[0x7] = this->val[0x7] + m.val[0x7];
	n.val[0x8] = this->val[0x8] + m.val[0x8];
	return n;
}

SSMatrix3 SSMatrix3::operator-(const SSMatrix3& m) const
{
	SSMatrix3 n;
	n.val[0x0] = this->val[0x0] - m.val[0x0];
	n.val[0x1] = this->val[0x1] - m.val[0x1];
	n.val[0x2] = this->val[0x2] - m.val[0x2];
	n.val[0x3] = this->val[0x3] - m.val[0x3];
	n.val[0x4] = this->val[0x4] - m.val[0x4];
	n.val[0x5] = this->val[0x5] - m.val[0x5];
	n.val[0x6] = this->val[0x6] - m.val[0x6];
	n.val[0x7] = this->val[0x7] - m.val[0x7];
	n.val[0x8] = this->val[0x8] - m.val[0x8];
	return n;
}

SSMatrix3 SSMatrix3::operator*(const SSMatrix3& m) const
{
	SSMatrix3 n;
	n._11 = (_11 * m._11) + (_12 * m._21) + (_13 * m._31);
	n._12 = (_11 * m._12) + (_12 * m._22) + (_13 * m._32);
	n._13 = (_11 * m._13) + (_12 * m._23) + (_13 * m._33);
	n._21 = (_21 * m._11) + (_22 * m._21) + (_23 * m._31);
	n._22 = (_21 * m._12) + (_22 * m._22) + (_23 * m._32);
	n._23 = (_21 * m._13) + (_22 * m._23) + (_23 * m._33);
	n._31 = (_31 * m._11) + (_32 * m._21) + (_33 * m._31);
	n._32 = (_31 * m._12) + (_32 * m._22) + (_33 * m._32);
	n._33 = (_31 * m._13) + (_32 * m._23) + (_33 * m._33);
	return n;
}

SSMatrix3 SSMatrix3::operator*(float f) const
{
	SSMatrix3 n;
	n.val[0x0] = this->val[0x0] * f;
	n.val[0x1] = this->val[0x1] * f;
	n.val[0x2] = this->val[0x2] * f;
	n.val[0x3] = this->val[0x3] * f;
	n.val[0x4] = this->val[0x4] * f;
	n.val[0x5] = this->val[0x5] * f;
	n.val[0x6] = this->val[0x6] * f;
	n.val[0x7] = this->val[0x7] * f;
	n.val[0x8] = this->val[0x8] * f;
	return n;
}

SSMatrix3 SSMatrix3::operator/(float f) const
{
	float inv = 1.0f / f;
	SSMatrix3 n;
	n.val[0x0] = this->val[0x0] * inv;
	n.val[0x1] = this->val[0x1] * inv;
	n.val[0x2] = this->val[0x2] * inv;
	n.val[0x3] = this->val[0x3] * inv;
	n.val[0x4] = this->val[0x4] * inv;
	n.val[0x5] = this->val[0x5] * inv;
	n.val[0x6] = this->val[0x6] * inv;
	n.val[0x7] = this->val[0x7] * inv;
	n.val[0x8] = this->val[0x8] * inv;
	return n;
}

SSMatrix3& SSMatrix3::operator+=(const SSMatrix3& m)
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
	return *this;
}

SSMatrix3& SSMatrix3::operator-=(const SSMatrix3& m)
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
	return *this;
}

SSMatrix3& SSMatrix3::operator*=(const SSMatrix3& m)
{
	return this->Multiply(m);
}

SSMatrix3& SSMatrix3::operator*=(float f)
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
	return *this;
}

SSMatrix3& SSMatrix3::operator/=(float f)
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
	return *this;
}

SSVector3 SSMatrix3::Row1() const
{
	return SSVector3(_11, _12, _13);
}

SSVector3 SSMatrix3::Row2() const
{
	return SSVector3(_21, _22, _23);
}

SSVector3 SSMatrix3::Row3() const
{
	return SSVector3(_31, _32, _33);
}

SSVector3 SSMatrix3::Col1() const
{
	return SSVector3(_11, _21, _31);
}

SSVector3 SSMatrix3::Col2() const
{
	return SSVector3(_12, _22, _32);
}

SSVector3 SSMatrix3::Col3() const
{
	return SSVector3(_13, _23, _33);
}

