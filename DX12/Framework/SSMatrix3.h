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
}
#pragma pack(pop)