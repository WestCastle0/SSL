#pragma once
#pragma pack(push, 4)

#include "../SSInclude.h"

namespace SSFramework
{
	class SSMatrix2;
	class SSMatrix3;
	class SSL_API SSVector2
	{
	public:
		SSVector2();
		SSVector2(float x, float y);

		static SSVector2 Normalized(const SSVector2& v);
		static float Dot(const SSVector2& v1, const SSVector2& v2);
		static SSVector2 Cross(const SSVector2& v);	//2D 유사외적.
		static const SSVector2 zero;

		SSVector2& Transform(const SSMatrix2& m);
		SSVector2& Transform(const SSMatrix3& m);
		void Normalize();
		float Length() const;
		float LengthSq() const;
		bool IsZero() const;

		bool operator == (const SSVector2& v) const;
		bool operator != (const SSVector2& v) const;
		SSVector2 operator + (const SSVector2& v) const;
		SSVector2 operator - (const SSVector2& v) const;
		SSVector2 operator - () const;
		SSVector2 operator / (float f) const;
		SSVector2 operator / (const SSVector2& v) const;
		SSVector2 operator * (float f) const;
		SSVector2 operator * (const SSVector2& v) const; //Dot
		SSVector2 operator * (const SSMatrix2& m) const;
		SSVector2 operator * (const SSMatrix3& m) const;
		friend SSVector2 operator * (float f, const SSVector2& v);
		friend SSVector2 operator / (float f, const SSVector2& v);

		SSVector2& operator += (const SSVector2& v);
		SSVector2& operator -= (const SSVector2& v);
		SSVector2& operator /= (float f);
		SSVector2& operator /= (const SSVector2& v);
		SSVector2& operator *= (float f);
		SSVector2& operator *= (const SSVector2& v);
		SSVector2& operator *= (const SSMatrix2& m);
		SSVector2& operator *= (const SSMatrix3& m);

		operator float* () { return val; }
		operator const float* () const { return val; }

		union
		{
			struct
			{
				float x, y;
			};
			float val[2];
		};
	};

	inline SSVector2 operator*(float f, const SSVector2& v)
	{
		return SSVector2(f * v.x, f * v.y);
	}

	inline SSVector2 operator/(float f, const SSVector2& v)
	{
		float inv = 1.0f / f;
		return SSVector2(inv * v.x, inv * v.y);
	}
}
#pragma pack(pop)