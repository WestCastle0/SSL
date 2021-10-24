#include <algorithm>
#include "gtest/gtest.h"
#include "Helper.h"
#include "SSMatrix3.h"
#include "SSMatrix4.h"
#include "SSAffineTransform2.h"
#include "SSAffineTransform3.h"

using namespace SSFramework;

TEST(AffineTransform, Equal)
{
    auto body = [](auto at, auto m)
    {
        using AT = decltype(at);
        using M = decltype(m);
        M a, b, c;
        RendomObjectsWithValuesForEqualTest<M>(a, b, c);
        AT a2(a);
        AT b2(a);
        AT c2(c);
        EXPECT_EQ(true, a2 == b2);
        EXPECT_EQ(false, a2 == c2);
    };
    body(SSAffineTransform2(), SSMatrix3());
    body(SSAffineTransform3(), SSMatrix4());
}

TEST(AffineTransform, NotEqual)
{
    auto body = [](auto at, auto m)
    {
        using AT = decltype(at);
        using M = decltype(m);
        M a, b, c;
        RendomObjectsWithValuesForEqualTest<M>(a, b, c);
        AT a2(a);
        AT b2(a);
        AT c2(c);
        EXPECT_EQ(false, a2 != b2);
        EXPECT_EQ(true, a2 != c2);
    };
    body(SSAffineTransform2(), SSMatrix3());
    body(SSAffineTransform3(), SSMatrix4());
}

TEST(AffineTransform, Translate)
{
    auto body = [](auto at, auto m, auto v)
    {
        using AT = decltype(at);
        using M = decltype(m);
        using V = decltype(v);
        m = RendomObjectWithValues<M>();
        v = RendomObjectWithValues<V>();
        at = AT(m);
        at.Translate(v);
        auto r = AT(m);

        int size = sizeof(r.translation.val) / sizeof(r.translation.val[0]);
        for (int i = 0; i < size; ++i)
        {
            r.translation.val[i] += v.val[i];
        }
        EXPECT_EQ(r, at);
    };
    body(SSAffineTransform2(), SSMatrix3(), SSVector2());
    body(SSAffineTransform3(), SSMatrix4(), SSVector3());
}
