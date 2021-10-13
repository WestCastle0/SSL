#pragma once
#pragma pack(push, 4)

#include "../SSInclude.h"

namespace SSFramework
{
	class SSL_API SSVector3
	{
	public:
		SSVector3();
		SSVector3(float x, float y, float z);

		static SSVector3 Normalized(const SSVector3& v);
		static float Dot(const SSVector3& v1, const SSVector3& v2);
		static SSVector3 Cross(const SSVector3& v1, const SSVector3& v2);
		static const SSVector3 zero;

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
		friend SSVector3 operator * (float f, const SSVector3& v);

		SSVector3& operator += (const SSVector3& v);
		SSVector3& operator -= (const SSVector3& v);
		SSVector3& operator /= (float f);
		SSVector3& operator /= (const SSVector3& v);
		SSVector3& operator *= (float f);
		SSVector3& operator *= (const SSVector3& v);

		union
		{
			struct
			{
				float x, y, z;
			};
			float val[3];
		};
	};
}
#pragma pack(pop)