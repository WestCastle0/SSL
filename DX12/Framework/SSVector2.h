#pragma once
#pragma pack(push, 4)

#include "../SSInclude.h"

namespace SSFramework
{
	class SSL_API SSVector2
	{
	public:
		SSVector2();
		SSVector2(float x, float y);

		static SSVector2 Normalized(const SSVector2& v);
		static float Dot(const SSVector2& v1, const SSVector2& v2);
		static SSVector2 Cross(const SSVector2& v);	//2D 유사외적.
		static const SSVector2 zero;

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
		friend SSVector2 operator * (float f, const SSVector2& v);
		friend SSVector2 operator / (float f, const SSVector2& v);

		SSVector2& operator += (const SSVector2& v);
		SSVector2& operator -= (const SSVector2& v);
		SSVector2& operator /= (float f);
		SSVector2& operator /= (const SSVector2& v);
		SSVector2& operator *= (float f);
		SSVector2& operator *= (const SSVector2& v);

		union
		{
			struct
			{
				float x, y;
			};
			float val[2];
		};
	};

	inline SSVector2 SSFramework::operator*(float f, const SSVector2& v)
	{
		return SSVector2(f * v.x, f * v.y);
	}

	inline SSVector2 SSFramework::operator/(float f, const SSVector2& v)
	{
		float inv = 1.0f / f;
		return SSVector2(inv * v.x, inv * v.y);
	}
}
#pragma pack(pop)