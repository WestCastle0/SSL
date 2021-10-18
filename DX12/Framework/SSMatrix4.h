#pragma once
#pragma pack(push, 4)

#include "../SSInclude.h"

namespace SSFramework
{
	class SSVector4;
	class SSL_API SSMatrix4
	{
	public:
		SSMatrix4();
		SSMatrix4(const SSVector4& row1, const SSVector4& row2, 
				  const SSVector4& row3, const SSVector4& row4);
		SSMatrix4(float e11, float e12, float e13, float e14, 
				  float e21, float e22, float e23, float e24, 
				  float e31, float e32, float e33, float e34, 
				  float e41, float e42, float e43, float e44);
		
		static const SSMatrix4 identity;

		SSMatrix4& SetIdentity();
		bool IsIdentity() const;
		SSMatrix4& Transpose();
		SSMatrix4& Inverse(bool* result = nullptr, float* determinant = nullptr);
		SSMatrix4& Multiply(const SSMatrix4& m);
		float Determinant() const;

		SSMatrix4 InverseMatrix(bool* result = nullptr, float* determinant = nullptr) const;
		SSMatrix4 TransposeMatrix() const;

		bool operator == (const SSMatrix4& m) const;
		bool operator != (const SSMatrix4& m) const;

		SSMatrix4 operator + (const SSMatrix4& m) const;
		SSMatrix4 operator - (const SSMatrix4& m) const;
		SSMatrix4 operator * (const SSMatrix4& m) const;
		SSMatrix4 operator * (float f) const;
		SSMatrix4 operator / (float f) const;

		SSMatrix4& operator += (const SSMatrix4& m);
		SSMatrix4& operator -= (const SSMatrix4& m);
		SSMatrix4& operator *= (const SSMatrix4& m);
		SSMatrix4& operator *= (float f);
		SSMatrix4& operator /= (float f);

		friend SSMatrix4 operator * (float f, const SSMatrix4& m);
		friend SSMatrix4 operator / (float f, const SSMatrix4& m);

		SSVector4 Row1() const;
		SSVector4 Row2() const;
		SSVector4 Row3() const;
		SSVector4 Row4() const;
		SSVector4 Col1() const;
		SSVector4 Col2() const;
		SSVector4 Col3() const;
		SSVector4 Col4() const;

		union
		{
			struct
			{
				float _11, _12, _13, _14,
					  _21, _22, _23, _24,
					  _31, _32, _33, _34,
					  _41, _42, _43, _44;
			};
			struct
			{
				float m[4][4];
			};
			float val[16];
;		};
	};
}
#pragma pack(pop)