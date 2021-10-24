#pragma once
#pragma pack(push, 4)

#include "../SSInclude.h"

namespace SSFramework
{
	class SSMatrix3;
	class SSMatrix4;
	class SSL_API SSVector3
	{
	public:
		SSVector3();
		SSVector3(float x, float y, float z);

		static SSVector3 Normalized(const SSVector3& v);
		static float Dot(const SSVector3& v1, const SSVector3& v2);
		static SSVector3 Cross(const SSVector3& v1, const SSVector3& v2);
		static const SSVector3 zero;

		SSVector3& Transform(const SSMatrix3& m);
		SSVector3& Transform(const SSMatrix4& m);
		void Normalize();
		float Length() const;
		float LengthSq() const;
		bool IsZero() const;

		bool operator == (const SSVector3& v) const;
		bool operator != (const SSVector3& v) const;
		SSVector3 operator + (const SSVector3& v) const;
		SSVector3 operator - (const SSVector3& v) const;
		SSVector3 operator - () const;
		SSVector3 operator / (float f) const;
		SSVector3 operator / (const SSVector3& v) const;
		SSVector3 operator * (float f) const;
		SSVector3 operator * (const SSVector3& v) const; //Dot
		SSVector3 operator * (const SSMatrix3& m) const;
		SSVector3 operator * (const SSMatrix4& m) const;
		friend SSVector3 operator * (float f, const SSVector3& v);
		friend SSVector3 operator / (float f, const SSVector3& v);

		SSVector3& operator += (const SSVector3& v);
		SSVector3& operator -= (const SSVector3& v);
		SSVector3& operator /= (float f);
		SSVector3& operator /= (const SSVector3& v);
		SSVector3& operator *= (float f);
		SSVector3& operator *= (const SSVector3& v);
		SSVector3& operator *= (const SSMatrix3& m);
		SSVector3& operator *= (const SSMatrix4& m);

		operator float* () { return val; }
		operator const float* () const { return val; }

		union
		{
			struct
			{
				float x, y, z;
			};
			float val[3];
		};
	};

	inline SSVector3 operator*(float f, const SSVector3& v)
	{
		return SSVector3(f * v.x, f * v.y, f * v.z);
	}

	inline SSVector3 operator/(float f, const SSVector3& v)
	{
		float inv = 1.0f / f;
		return SSVector3(inv * v.x, inv * v.y, inv * v.z);
	}

}
#pragma pack(pop)