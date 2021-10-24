#pragma once
#include "../SSInclude.h"
#include "SSVector3.h"
#include "SSMatrix3.h"
#include "SSMatrix4.h"
#include "SSLinearTransform3.h"

#pragma pack(push, 4)
namespace SSFramework
{
	class SSL_API SSAffineTransform3
	{
	public:
		SSAffineTransform3(const SSVector3& translate = SSVector3::zero);
		SSAffineTransform3(const SSLinearTransform3& linear, const SSVector3& translate = SSVector3::zero);
		SSAffineTransform3(const SSVector3& left, const SSVector3& up, const SSVector3& forward, const SSVector3& translate = SSVector3::zero);
		SSAffineTransform3(const float x, const float y, const float z);
		SSAffineTransform3(const SSMatrix4& m);

		SSAffineTransform3& Identity();
		bool IsIdentity() const;
		
		SSAffineTransform3& Translate(float x, float y, float z);
		SSAffineTransform3& Translate(const SSVector3& v);

		SSAffineTransform3& Inverse();
		SSAffineTransform3& Multiply(const SSLinearTransform3& lt);
		SSAffineTransform3& Multiply(const SSAffineTransform3& at);

		SSAffineTransform3& operator * (const SSLinearTransform3& lt) const;
		SSAffineTransform3& operator * (const SSAffineTransform3& at) const;
		SSAffineTransform3& operator *= (const SSLinearTransform3& lt);
		SSAffineTransform3& operator *= (const SSAffineTransform3& at);
		friend SSVector3 operator * (const SSVector3& v, const SSAffineTransform3& at);
		friend SSVector3& operator *= (SSVector3& v, const SSAffineTransform3& at);

		bool operator == (const SSAffineTransform3& at) const;
		bool operator != (const SSAffineTransform3& at) const;

		SSMatrix4 Matrix4() const;
		const SSMatrix3& Matrix3() const { return matrix3; }

		SSMatrix3 matrix3;
		SSVector3 translation;
	};

	inline SSVector3 operator * (const SSVector3& v, const SSAffineTransform3& at)
	{
		return v * at.Matrix3() + at.translation;
	}

	inline SSVector3& operator *= (SSVector3& v, const SSAffineTransform3& at)
	{
		v *= at.Matrix3();
		v += at.translation;
		return v;
	}
}
#pragma pack(pop)