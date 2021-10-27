#include "gtest/gtest.h"
#include "Helper.h"

#include "Framework/SSVector2.h"
#include "SSVector2.h"
#include "SSVector3.h"
#include "SSVector4.h"

#include "SSMatrix2.h"
#include "SSMatrix3.h"
#include "SSMatrix4.h"

using namespace SSFramework;

TEST(Vector, Equal)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a, b, c;
        RendomObjectsWithValuesForEqualTest<V>(a, b, c);
        EXPECT_EQ(true, a == b);
        EXPECT_EQ(false, a == c);
    };
    body(SSVector2());
    body(SSVector3());
    body(SSVector4());
}

TEST(Vector, NotEqual)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a, b, c;
        RendomObjectsWithValuesForEqualTest<V>(a, b, c);
        EXPECT_EQ(false, a != b);
        EXPECT_EQ(true, a != c);
    };
    body(SSVector2());
    body(SSVector3());
    body(SSVector4());
}

TEST(Vector, Add)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RendomObjectWithValues<V>();
        V b = RendomObjectWithValues<V>();
        V r = SumEachValueOfObject<V>(a, b);
        EXPECT_EQ(r, a + b);
        a += b;
        EXPECT_EQ(r, a);
    };
    body(SSVector2());
    body(SSVector3());
    body(SSVector4());
}

TEST(Vector, Sub)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RendomObjectWithValues<V>();
        V b = RendomObjectWithValues<V>();
        V r = SubEachValueOfObject<V>(a, b);
        EXPECT_EQ(r, a - b);
        a -= b;
        EXPECT_EQ(r, a);
    };
    body(SSVector2());
    body(SSVector3());
    body(SSVector4());
}

TEST(Vector, ScalarMultiply)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RendomObjectWithValues<V>();
        float s = RendomFloat();
        V r = MulEachValueOfObject<V>(a, s);
        EXPECT_EQ(r, a * s);
        a *= s;
        EXPECT_EQ(r, a);
    };
    body(SSVector2());
    body(SSVector3());
    body(SSVector4());
}

TEST(Vector, Dot)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        V a = RendomObjectWithValues<V>();
        V b = RendomObjectWithValues<V>();
        int dimension = sizeof(a.val) / sizeof(a.val[0]);
        float r = 0.0f;
        for (int i = 0; i < dimension; ++i)
        {
            r += a.val[i] * b.val[i];
        }
        EXPECT_EQ(r, V::Dot(a, b));
    };
    body(SSVector2());
    body(SSVector3());
    body(SSVector4());
}

TEST(Vector, Cross)
{
    SSVector3 v1{ 1.f, 0.f, 0.f };
    SSVector3 v2{ 0.f, 1.f, 0.f };
    SSVector3 answer{0.f, 0.f, 1.f};
    EXPECT_EQ(answer, SSVector3::Cross(v1, v2));
}

TEST(Vector, MulMatrix)
{
    auto body = [](auto v, auto m)
    {
        using V = decltype(v);
        using M = decltype(m);
        v = RendomObjectWithValues<V>();
        m = RendomObjectWithValues<M>();
        int vDimension = sizeof(v.val) / sizeof(v.val[0]);
        int mDimension = sizeof(m.m[0]) / sizeof(m.m[0][0]);
        V r;
        for (int i = 0; i < vDimension; ++i)
        {
            for (int j = 0; j < mDimension; ++j)
            {
                r.val[i] += v.val[j] * m.m[j][i];
            }
        }
        EXPECT_EQ(r, v * m);
    };
    body(SSVector2(), SSMatrix2());
    body(SSVector3(), SSMatrix3());
    body(SSVector4(), SSMatrix4());
}

TEST(Vector, Length)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        v = RendomObjectWithValues<V>();
        int dimension = sizeof(v.val) / sizeof(v.val[0]);
        float r = 0.0f;
        for (int i = 0; i < dimension; ++i)
        {
            r += v.val[i] * v.val[i];
        }
        EXPECT_EQ(sqrtf(r), v.Length());
    };
    body(SSVector2());
    body(SSVector3());
    body(SSVector4());
}

TEST(Vector, LengthSq)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        v = RendomObjectWithValues<V>();
        int dimension = sizeof(v.val) / sizeof(v.val[0]);
        float r = 0.0f;
        for (int i = 0; i < dimension; ++i)
        {
            r += v.val[i] * v.val[i];
        }
        EXPECT_EQ(r, v.LengthSq());
    };
    body(SSVector2());
    body(SSVector3());
    body(SSVector4());
}

TEST(Vector, Normalize)
{
    auto body = [](auto v)
    {
        using V = decltype(v);
        v = RendomObjectWithValues<V>();
        V r = v;

        float lenSq = v.LengthSq();
        if (lenSq > 0.0f)
        {
            float lenInv = 1.0f / sqrt(lenSq);
            int vSize = sizeof(v.val) / sizeof(v.val[0]);
            for (int i = 0; i < vSize; ++i)
            {
                r.val[i] *= lenInv;
            }
        }

        EXPECT_EQ(r, V::Normalized(v));
    };
    body(SSVector2());
    body(SSVector3());
    body(SSVector4());
}
