#pragma once
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


		SSLinearTransform2& Rotate(float angle);

		SSMatrix2& Matrix2() { return matrix2; }
		const SSMatrix2& Matrix2() const { return matrix2; }

		SSMatrix2 matrix2;
	};
}
#pragma pack(pop)