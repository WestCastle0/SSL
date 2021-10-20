#include "SSMatrix2.h"
#include "SSVector2.h"

using namespace SSFramework;

const SSMatrix2 SSMatrix2::identity = SSMatrix2().SetIdentity();

SSMatrix2::SSMatrix2()
	:_11(1), _12(0),
	 _21(0), _22(1){}

SSMatrix2::SSMatrix2(const SSVector2& row1, const SSVector2& row2)
	:_11(row1.x), _12(row1.y),
	 _21(row2.x), _22(row2.y){}

SSMatrix2::SSMatrix2(float e11, float e12, float e21, float e22)
	:_11(e11), _12(e12),
	 _21(e21), _22(e22){}

SSMatrix2& SSMatrix2::SetIdentity()
{
	_11 = _22 = 1.0f;
	_12 = _21 = 0.0f;
	return *this;
}

bool SSMatrix2::IsIdentity() const
{
	return 
		_11 == 1.0f && _12 == 0.0f &&
		_21 == 0.0f && _22 == 1.0f;
}

SSMatrix2& SSMatrix2::Transpose()
{
	float temp = this->_12;
	this->_12 = this->_21;
	this->_21 = temp;
	return *this;
}


SSMatrix2& SSMatrix2::Multiply(const SSMatrix2& m)
{
	SSMatrix2 n(*this);
	this->_11 = (n._11 * m._11) + (n._12 * m._21);
	this->_12 = (n._11 * m._12) + (n._12 * m._22);
	this->_21 = (n._21 * m._11) + (n._22 * m._21);
	this->_22 = (n._21 * m._12) + (n._22 * m._22);
	return *this;
}

float SSMatrix2::Determinant() const
{
	return _11 * _22 - _12 * _21;
}

SSMatrix2 SSMatrix2::InverseMatrix(bool* r, float* d) const
{
	SSMatrix2 n;
	float det = Determinant();
	bool result = false;

	if (det != 0.0f)
	{
		float detInv = 1.0f / det;
		n._11 = _22 * detInv;
		n._12 = -1.0f * _12 * detInv;
		n._21 = -1.0f * _21 * detInv;
		n._22 = _11 * detInv;

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

SSMatrix2& SSMatrix2::Inverse(bool* r, float* d)
{
	bool b;
	SSMatrix2 n = this->InverseMatrix(&b, d);
	if (b)
		*this = n;
	if (r)
		*r = b;
	return *this;
}

SSMatrix2 SSMatrix2::TransposeMatrix() const
{
	SSMatrix2 n(*this);
	return n.Transpose();
}

bool SSMatrix2::operator==(const SSMatrix2& m) const
{
	return 
		this->_11 == m._11 && this->_12 == m._12 &&
		this->_21 == m._21 && this->_22 == m._22;
}

bool SSMatrix2::operator!=(const SSMatrix2& m) const
{
	return 
		this->_11 != m._11 || this->_12 != m._12 &&
		this->_21 != m._21 || this->_22 != m._22;
}

SSMatrix2 SSMatrix2::operator+(const SSMatrix2& m) const
{
	SSMatrix2 n;
	n._11 = this->_11 + m._11;
	n._12 = this->_12 + m._12;
	n._21 = this->_21 + m._21;
	n._22 = this->_22 + m._22;
	return n;
}

SSMatrix2 SSMatrix2::operator-(const SSMatrix2& m) const
{
	SSMatrix2 n;
	n._11 = this->_11 - m._11;
	n._12 = this->_12 - m._12;
	n._21 = this->_21 - m._21;
	n._22 = this->_22 - m._22;
	return n;
}

SSMatrix2 SSMatrix2::operator*(const SSMatrix2& m) const
{
	SSMatrix2 n;
	n._11 = (this->_11 * m._11) + (this->_12 * m._21);
	n._12 = (this->_11 * m._12) + (this->_12 * m._22);
	n._21 = (this->_21 * m._11) + (this->_22 * m._21);
	n._22 = (this->_21 * m._12) + (this->_22 * m._22);
	return n;
}

SSMatrix2 SSMatrix2::operator*(float f) const
{
	SSMatrix2 n;
	n._11 = this->_11 * f;
	n._12 = this->_12 * f;
	n._21 = this->_21 * f;
	n._22 = this->_22 * f;
	return n;
}

SSMatrix2 SSMatrix2::operator/(float f) const
{
	float inv = 1.0f / f;
	SSMatrix2 n;
	n._11 = this->_11 * inv;
	n._12 = this->_12 * inv;
	n._21 = this->_21 * inv;
	n._22 = this->_22 * inv;
	return n;
}

SSMatrix2& SSMatrix2::operator+=(const SSMatrix2& m)
{
	this->_11 += m._11;
	this->_12 += m._12;
	this->_21 += m._21;
	this->_22 += m._22;
	return *this;
}

SSMatrix2& SSMatrix2::operator-=(const SSMatrix2& m)
{
	this->_11 -= m._11;
	this->_12 -= m._12;
	this->_21 -= m._21;
	this->_22 -= m._22;
	return *this;
}

SSMatrix2& SSMatrix2::operator*=(const SSMatrix2& m)
{
	return this->Multiply(m);
}

SSMatrix2& SSMatrix2::operator*=(float f)
{
	this->_11 *= f;
	this->_12 *= f;
	this->_21 *= f;
	this->_22 *= f;
	return *this;
}

SSMatrix2& SSMatrix2::operator/=(float f)
{
	float inv = 1.0f / f;
	this->_11 *= inv;
	this->_12 *= inv;
	this->_21 *= inv;
	this->_22 *= inv;
	return *this;
}

SSMatrix2 SSFramework::operator*(float f, const SSMatrix2& m)
{
	return SSMatrix2(f * m._11, f * m._12, f * m._21, f * m._22);
}

SSMatrix2 SSFramework::operator/(float f, const SSMatrix2& m)
{
	float inv = 1.0f / f;
	return SSMatrix2(inv * m._11, inv * m._12, inv * m._21, inv * m._22);
}

SSVector2 SSMatrix2::Row1() const
{
	return SSVector2(_11, _12);
}

SSVector2 SSMatrix2::Row2() const
{
	return SSVector2(_21, _22);
}

SSVector2 SSMatrix2::Col1() const
{
	return SSVector2(_11, _21);
}

SSVector2 SSMatrix2::Col2() const
{
	return SSVector2(_12, _22);
}
