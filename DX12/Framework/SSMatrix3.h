#pragma once
#pragma pack(push, 4)

#include "../SSInclude.h"

namespace SSFramework
{
	class SSVector3;
	class SSL_API SSMatrix3
	{
	public:
		SSMatrix3();
		SSMatrix3(const SSVector3& row1, const SSVector3& row2, const SSVector3& row3);
		SSMatrix3(float e11, float e12, float e13, 
				  float e21, float e22, float e23, 
				  float e31, float e32, float e33);
		
		static const SSMatrix3 identity;

		SSMatrix3& SetIdentity();
		bool IsIdentity() const;
		SSMatrix3& Transpose();
		SSMatrix3& Inverse(bool* result = nullptr, float* determinant = nullptr);
		SSMatrix3& Multiply(const SSMatrix3& m);
		float Determinant() const;

		SSMatrix3 InverseMatrix(bool* result = nullptr, float* determinant = nullptr) const;
		SSMatrix3 TransposeMatrix() const;

		bool operator == (const SSMatrix3& m) const;
		bool operator != (const SSMatrix3& m) const;

		SSMatrix3 operator + (const SSMatrix3& m) const;
		SSMatrix3 operator - (const SSMatrix3& m) const;
		SSMatrix3 operator * (const SSMatrix3& m) const;
		SSMatrix3 operator * (float f) const;
		SSMatrix3 operator / (float f) const;

		SSMatrix3& operator += (const SSMatrix3& m);
		SSMatrix3& operator -= (const SSMatrix3& m);
		SSMatrix3& operator *= (const SSMatrix3& m);
		SSMatrix3& operator *= (float f);
		SSMatrix3& operator /= (float f);

		friend SSMatrix3 operator * (float f, const SSMatrix3& m);
		friend SSMatrix3 operator / (float f, const SSMatrix3& m);

		SSVector3 Row1() const;
		SSVector3 Row2() const;
		SSVector3 Row3() const;
		SSVector3 Col1() const;
		SSVector3 Col2() const;
		SSVector3 Col3() const;

		union
		{
			struct
			{
				float _11, _12, _13,
					  _21, _22, _23,
					  _31, _32, _33;
			};
			struct
			{
				float m[3][3];
			};
			float val[9];
;		};
	};

	inline SSMatrix3 operator*(float f, const SSMatrix3& m)
	{
		SSMatrix3 n;
		n.val[0x0] = f * m.val[0x0];
		n.val[0x1] = f * m.val[0x1];
		n.val[0x2] = f * m.val[0x2];
		n.val[0x3] = f * m.val[0x3];
		n.val[0x4] = f * m.val[0x4];
		n.val[0x5] = f * m.val[0x5];
		n.val[0x6] = f * m.val[0x6];
		n.val[0x7] = f * m.val[0x7];
		n.val[0x8] = f * m.val[0x8];
		return n;
	}

	inline SSMatrix3 operator/(float f, const SSMatrix3& m)
	{
		SSMatrix3 n;
		float inv = 1.0f / f;
		n.val[0x0] = inv * m.val[0x0];
		n.val[0x1] = inv * m.val[0x1];
		n.val[0x2] = inv * m.val[0x2];
		n.val[0x3] = inv * m.val[0x3];
		n.val[0x4] = inv * m.val[0x4];
		n.val[0x5] = inv * m.val[0x5];
		n.val[0x6] = inv * m.val[0x6];
		n.val[0x7] = inv * m.val[0x7];
		n.val[0x8] = inv * m.val[0x8];
		return n;
	}

}
#pragma pack(pop)