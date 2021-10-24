#pragma once
#pragma pack(push, 4)

#include "../SSInclude.h"

namespace SSFramework
{
	class SSMatrix4;
	class SSL_API SSVector4
	{
	public:
		SSVector4();
		SSVector4(float x, float y, float z, float w);

		static SSVector4 Normalized(const SSVector4& v);
		static float Dot(const SSVector4& v1, const SSVector4& v2);
		static const SSVector4 zero;

		SSVector4& Transform(const SSMatrix4& m);
		void Normalize();
		float Length() const;
		float LengthSq() const;
		bool IsZero() const;

		bool operator == (const SSVector4& v) const;
		bool operator != (const SSVector4& v) const;
		SSVector4 operator + (const SSVector4& v) const;
		SSVector4 operator - (const SSVector4& v) const;
		SSVector4 operator - () const;
		SSVector4 operator / (float f) const;
		SSVector4 operator / (const SSVector4& v) const;
		SSVector4 operator * (float f) const;
		SSVector4 operator * (const SSVector4& v) const; //Dot
		SSVector4 operator * (const SSMatrix4& m) const;
		friend SSVector4 operator * (float f, const SSVector4& v);
		friend SSVector4 operator / (float f, const SSVector4& v);

		SSVector4& operator += (const SSVector4& v);
		SSVector4& operator -= (const SSVector4& v);
		SSVector4& operator /= (float f);
		SSVector4& operator /= (const SSVector4& v);
		SSVector4& operator *= (float f);
		SSVector4& operator *= (const SSVector4& v);
		SSVector4& operator *= (const SSMatrix4& m);

		operator float* () { return val; }
		operator const float* () const { return val; }

		union
		{
			struct
			{
				float x, y, z, w;
			};
			float val[4];
		};
	};

	inline SSVector4 operator*(float f, const SSVector4& v)
	{
		return SSVector4(f * v.x, f * v.y, f * v.z, f * v.w);
	}

	inline SSVector4 operator/(float f, const SSVector4& v)
	{
		float inv = 1.0f / f;
		return SSVector4(inv * v.x, inv * v.y, inv * v.z, inv * v.w);
	}

}
#pragma pack(pop)