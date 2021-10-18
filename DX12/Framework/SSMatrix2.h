#pragma once
#pragma pack(push, 4)

#include "../SSInclude.h"

namespace SSFramework
{
	class SSVector2;
	class SSL_API SSMatrix2
	{
	public:
		SSMatrix2();
		SSMatrix2(const SSVector2& row1, const SSVector2& row2);
		SSMatrix2(float e11, float e12, 
				  float e21, float e22);
		
		static const SSMatrix2 identity;

		SSMatrix2& SetIdentity();
		bool IsIdentity() const;
		SSMatrix2& Transpose();
		SSMatrix2& Inverse(bool* result = nullptr, float* determinant = nullptr);
		SSMatrix2& Multiply(const SSMatrix2& m);
		float Determinant() const;

		SSMatrix2 InverseMatrix(bool* result = nullptr, float* determinant = nullptr) const;
		SSMatrix2 TransposeMatrix() const;

		bool operator == (const SSMatrix2& m) const;
		bool operator != (const SSMatrix2& m) const;

		SSMatrix2 operator + (const SSMatrix2& m) const;
		SSMatrix2 operator - (const SSMatrix2& m) const;
		SSMatrix2 operator * (const SSMatrix2& m) const;
		SSMatrix2 operator * (float f) const;
		SSMatrix2 operator / (float f) const;

		SSMatrix2& operator += (const SSMatrix2& m);
		SSMatrix2& operator -= (const SSMatrix2& m);
		SSMatrix2& operator *= (const SSMatrix2& m);
		SSMatrix2& operator *= (float f);
		SSMatrix2& operator /= (float f);

		friend SSMatrix2 operator * (float f, const SSMatrix2& m);
		friend SSMatrix2 operator / (float f, const SSMatrix2& m);

		SSVector2 Row1() const;
		SSVector2 Row2() const;
		SSVector2 Col1() const;
		SSVector2 Col2() const;

		union
		{
			struct
			{
				float _11, _12,
					  _21, _22;
			};
			struct
			{
				float m[2][2];
			};
			float val[4];
;		};
	};
}
#pragma pack(pop)