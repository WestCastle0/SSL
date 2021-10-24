#pragma once
#include "../SSInclude.h"
#include "SSVector3.h"
#include "SSMatrix3.h"
#include "SSMatrix4.h"

#pragma pack(push, 4)
namespace SSFramework
{
	class SSL_API SSLinearTransform3
	{
	public:
		SSLinearTransform3();
		//SSLinearTransform3(const SSQuaterion& q);
		//// not implemented yet..
		SSLinearTransform3(const float scaleX, const float scaleY, const float scaleZ);
		SSLinearTransform3(const SSVector3& axisX, const SSVector3& axisY, const SSVector3& axisZ);
		SSLinearTransform3(const SSMatrix3& m);

		SSLinearTransform3& Identity();
		bool IsIdentity() const;

		SSLinearTransform3& Scale(float x, float y, float z);
		SSLinearTransform3& Scale(const SSVector3& v);
		SSLinearTransform3& Scale(float s);
		SSLinearTransform3& RotateX(float angle);
		SSLinearTransform3& RotateY(float angle);
		SSLinearTransform3& RotateZ(float angle);
		SSLinearTransform3& Rotate(const SSVector3& axis, float angle);
		//SSLinearTransform3& Rotate(const SSQuaterion& q);
		//// not implemented yet..
		SSLinearTransform3& squeeze(const SSVector3& axis, float s);
		//// TODO

		SSLinearTransform3& Inverse();
		SSLinearTransform3& Multiply(const SSMatrix3& m);
		SSLinearTransform3& Multiply(const SSLinearTransform3& lt);

		SSLinearTransform3 operator * (const SSLinearTransform3& lt) const;
		SSLinearTransform3& operator *= (const SSLinearTransform3& lt);
		friend SSVector3 operator * (const SSVector3& v, const SSLinearTransform3& lt);
		friend SSVector3& operator *= (SSVector3& v, const SSLinearTransform3& lt);

		bool operator == (const SSLinearTransform3& lt) const;
		bool operator != (const SSLinearTransform3& lt) const;

		//bool Decompose(SSVector3& scale, SSQuaternion& rotate) const;
		//SSuaternion Rotation() const;
		//// not implemented yet..

		SSMatrix3& Matrix3() { return matrix3; }
		const SSMatrix3& Matrix3() const { return matrix3; }

		SSMatrix3 matrix3;
	};

	inline SSVector3 operator * (const SSVector3& v, const SSLinearTransform3& lt)
	{
		return v * lt.Matrix3();

		return v;
	}

	inline SSVector3& operator *= (SSVector3& v, const SSLinearTransform3& lt)
	{
		v *= lt.Matrix3();
		return v;
	}
}
#pragma pack(pop)