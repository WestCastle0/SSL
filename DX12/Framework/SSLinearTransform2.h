#pragma once
#include "../SSInclude.h"
#include "SSVector2.h"
#include "SSMatrix2.h"
#include "SSMatrix3.h"

#pragma pack(push, 4)
namespace SSFramework
{
	class SSL_API SSLinearTransform2
	{
	public:
		SSLinearTransform2();
		SSLinearTransform2(const float rotate);
		SSLinearTransform2(const float scaleX, const float scaleY);
		SSLinearTransform2(const SSVector2& axisX, const SSVector2& axisY);
		SSLinearTransform2(const SSMatrix2& m);

		SSLinearTransform2& Identity();
		bool IsIdentity() const;

		SSLinearTransform2& HorizontalShear(float s);
		SSLinearTransform2& VerticalShear(float s);
		SSLinearTransform2& HorizontalFlip();
		SSLinearTransform2& VerticalFilp();
		SSLinearTransform2& squeeze(float s);
		SSLinearTransform2& Scale(float x, float y);
		SSLinearTransform2& Scale(const SSVector2& v);
		SSLinearTransform2& Scale(float s);
		SSLinearTransform2& Rotate(float angle);

		SSLinearTransform2& Inverse();
		SSLinearTransform2& Multiply(const SSMatrix2& m);
		SSLinearTransform2& Multiply(const SSLinearTransform2& lt);

		SSLinearTransform2 operator * (const SSLinearTransform2& lt) const;
		SSLinearTransform2& operator *= (const SSLinearTransform2& lt);
		friend SSVector2 operator * (const SSVector2& v, const SSLinearTransform2& lt);
		friend SSVector2& operator *= (SSVector2& v, const SSLinearTransform2& lt);

		bool operator == (const SSLinearTransform2& lt) const;
		bool operator != (const SSLinearTransform2& lt) const;

		SSMatrix2& Matrix2() { return matrix2; }
		const SSMatrix2& Matrix2() const { return matrix2; }

		SSMatrix2 matrix2;
	};

	inline SSVector2 operator * (const SSVector2& v, const SSLinearTransform2& lt)
	{
		return v * lt.Matrix2();
	}

	inline SSVector2& operator *= (SSVector2& v, const SSLinearTransform2& lt)
	{
		v *= lt.Matrix2();
		return v;
	}
}
#pragma pack(pop)