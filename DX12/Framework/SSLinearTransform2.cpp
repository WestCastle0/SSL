#include "SSMath.h"
#include "SSLinearTransform2.h"

using namespace SSFramework;

SSLinearTransform2::SSLinearTransform2()
	: matrix2(SSMatrix2::identity){}

SSLinearTransform2::SSLinearTransform2(const float rotate)
	: matrix2(SSMatrix2::identity)
{
	Rotate(rotate);
}

SSLinearTransform2::SSLinearTransform2(const float scaleX, const float scaleY)
{
}

SSLinearTransform2::SSLinearTransform2(const SSVector2& axisX, const SSVector2& axisY)
{
}

SSLinearTransform2::SSLinearTransform2(const SSMatrix2& m)
{
}

SSLinearTransform2& SSLinearTransform2::Rotate(float angle)
{
	float cos = cosf(angle);
	float sin = sinf(angle);

	SSMatrix2 n(cos, sin, 
				-sin, cos);
	// TODO: 여기에 return 문을 삽입합니다.
}
