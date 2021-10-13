#pragma once
#pragma pack(push, 4)

#include "../SSInclude.h"

namespace SSFramework
{
	class SSL_API SSVector4
	{
	public:
		SSVector4();
		SSVector4(float x, float y, float z, float w);

		static SSVector4 Normalized(const SSVector4& v);
		static float Dot(const SSVector4& v1, const SSVector4& v2);
		static const SSVector4 zero;

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
		friend SSVector4 operator * (float f, const SSVector4& v);

		SSVector4& operator += (const SSVector4& v);
		SSVector4& operator -= (const SSVector4& v);
		SSVector4& operator /= (float f);
		SSVector4& operator /= (const SSVector4& v);
		SSVector4& operator *= (float f);
		SSVector4& operator *= (const SSVector4& v);

		union
		{
			struct
			{
				float x, y, z, w;
			};
			float val[4];
		};
	};
}
#pragma pack(pop)