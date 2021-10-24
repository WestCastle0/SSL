#pragma once
#include "../SSInclude.h"
#include "SSVector2.h"
#include "SSMatrix2.h"
#include "SSMatrix3.h"
#include "SSLinearTransform2.h"

#pragma pack(push, 4)
namespace SSFramework
{
	class SSL_API SSAffineTransform2
	{
	public:
		SSAffineTransform2(const SSVector2& translate = SSVector2::zero);
		SSAffineTransform2(const SSLinearTransform2& linear, const SSVector2& translate = SSVector2::zero);
		SSAffineTransform2(const SSVector2& axisX, const SSVector2& axisY, const SSVector2& translate = SSVector2::zero);
		SSAffineTransform2(const float x, const float y);
		SSAffineTransform2(const SSMatrix3& m);

		SSAffineTransform2& Identity();
		bool IsIdentity() const;

		SSAffineTransform2& Translate(float x, float y);
		SSAffineTransform2& Translate(const SSVector2& v);

		SSAffineTransform2& Inverse();
		SSAffineTransform2& Multiply(const SSLinearTransform2& lt);
		SSAffineTransform2& Multiply(const SSAffineTransform2& at);

		SSAffineTransform2& operator * (const SSLinearTransform2& lt) const;
		SSAffineTransform2& operator * (const SSAffineTransform2& at) const;
		SSAffineTransform2& operator *= (const SSLinearTransform2& lt);
		SSAffineTransform2& operator *= (const SSAffineTransform2& at);
		friend SSVector2 operator * (const SSVector2& v, const SSAffineTransform2& at);
		friend SSVector2& operator *= (SSVector2& v, const SSAffineTransform2& at);

		bool operator == (const SSAffineTransform2& at) const;
		bool operator != (const SSAffineTransform2& at) const;

		SSMatrix3 Matrix3() const;
		const SSMatrix2& Matrix2() const { return matrix2; }

		SSMatrix2 matrix2;
		SSVector2 translation;
	};

	inline SSVector2 operator * (const SSVector2& v, const SSAffineTransform2& at)
	{
		return v * at.Matrix2() + at.translation;
	}

	inline SSVector2& operator *= (SSVector2& v, const SSAffineTransform2& at)
	{
		v *= at.Matrix2();
		v += at.translation;
		return v;
	}
}
#pragma pack(pop)