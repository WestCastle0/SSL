#include <algorithm>
#include "gtest/gtest.h"
#include "Helper.h"
#include "SSMatrix2.h"
#include "SSMatrix3.h"
#include "SSMatrix4.h"

using namespace SSFramework;

TEST(Matrix, Equal)
{
    auto body = [](auto m)
    {
        using M = decltype(m);
        M a, b, c;
        RendomObjectsWithValuesForEqualTest<M>(a, b, c);
        EXPECT_EQ(true, a == b);
        EXPECT_EQ(false, a == c);
    };
    body(SSMatrix2());
    body(SSMatrix3());
    body(SSMatrix4());
}

TEST(Matrix, NotEqual)
{
    auto body = [](auto m)
    {
        using M = decltype(m);
        M a, b, c;
        RendomObjectsWithValuesForEqualTest<M>(a, b, c);
        EXPECT_EQ(false, a != b);
        EXPECT_EQ(true, a != c);
    };
    body(SSMatrix2());
    body(SSMatrix3());
    body(SSMatrix4());
}

TEST(Matrix, Add)
{
    auto body = [](auto m)
    {
        using M = decltype(m);
        M a = RendomObjectWithValues<M>();
        M b = RendomObjectWithValues<M>();
        M r = SumEachValueOfObject<M>(a, b);
        EXPECT_EQ(r, a + b);
        a += b;
        EXPECT_EQ(r, a);
    };
    body(SSMatrix2());
    body(SSMatrix3());
    body(SSMatrix4());
}

TEST(Matrix, Sub)
{
    auto body = [](auto m)
    {
        using M = decltype(m);
        M a = RendomObjectWithValues<M>();
        M b = RendomObjectWithValues<M>();
        M r = SubEachValueOfObject<M>(a, b);
        EXPECT_EQ(r, a - b);
        a -= b;
        EXPECT_EQ(r, a);
    };
    body(SSMatrix2());
    body(SSMatrix3());
    body(SSMatrix4());
}

TEST(Matrix, ScalarMultiply)
{
    auto body = [](auto m)
    {
        using M = decltype(m);
        M a = RendomObjectWithValues<M>();
        float s = RendomFloat();
        M r = MulEachValueOfObject<M>(a, s);
        EXPECT_EQ(r, a * s);
        a *= s;
        EXPECT_EQ(r, a);
    };
    body(SSMatrix2());
    body(SSMatrix3());
    body(SSMatrix4());
}

TEST(Matrix, Multiply)
{
    auto body = [](auto m)
    {
        using M = decltype(m);
        M m1 = RendomObjectWithValues<M>();
        M m2 = RendomObjectWithValues<M>();
        int dimension = sizeof(m1.m[0]) / sizeof(m1.m[0][0]);
        M r;
        for (int i = 0; i < dimension; ++i)
        {
            for (int j = 0; j < dimension; ++j)
            {
                r.m[i][j] = 0.0f;
                for (int k = 0; k < dimension; ++k)
                {
                    r.m[i][j] += m1.m[i][k] * m2.m[k][j];
                }
                
            }
        }
        EXPECT_EQ(r, m1 * m2);
        m1 *= m2;
        EXPECT_EQ(r, m1);
    };
    body(SSMatrix2());
    body(SSMatrix3());
    body(SSMatrix4());
}

TEST(Matrix, Transpose)
{
    auto body = [](auto m)
    {
        using M = decltype(m);
        m = RendomObjectWithValues<M>();
        M r = m;
        int dimension = sizeof(m.m[0]) / sizeof(m.m[0][0]);
        for (int i = 0; i < dimension; ++i)
        {
            for (int j = i; j < dimension; ++j)
            {
                std::swap(m.m[i][j], m.m[j][i]);
            }
        }

        EXPECT_EQ(r, m.TransposeMatrix());
    };
    body(SSMatrix2());
    body(SSMatrix3());
    body(SSMatrix4());
}

TEST(Matrix, Inverse)
{
    auto body = [](auto m)
    {
        using M = decltype(m);
        m = RendomObjectWithValues<M>();
        auto r = m * m.InverseMatrix();
        int size = sizeof(m.val) / sizeof(m.val[0]);
        auto identity = M();
        for (int i = 0; i < size; ++i)
        {
            using elementType = std::remove_reference<decltype(m.val[i])>::type;
            EXPECT_EQ(true, ApproximatelyEqualAbsRel<elementType>(identity.val[i], 
                                                                  r.val[i], 
                                                                  1e-5f,
                                                                  1e-4f));
        }
    };
    body(SSMatrix2());
    body(SSMatrix3());
    body(SSMatrix4());
}

TEST(Matrix, Determinant)
{
    auto body = [](auto m)
    {
        // 어떤 행렬의 deteminant는 그 행렬의 전치행렬과 값이 같다.
        using M = decltype(m);
        m = RendomObjectWithValues<M>();
        M r = m.TransposeMatrix();
        EXPECT_EQ(true, ApproximatelyEqualAbsRel(r.Determinant(), 
                                                 m.Determinant(), 
                                                 1e-5f, 
                                                 1e-4f));
    };
    body(SSMatrix2());
    body(SSMatrix3());
    body(SSMatrix4());
}