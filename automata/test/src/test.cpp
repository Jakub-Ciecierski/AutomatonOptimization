#include <gtest/gtest.h>

// It is not a mistake to include source files in unit tests
#include "console.cpp"

TEST(MathTest, TwoPlusTwoEqualsFour) {
	EXPECT_EQ(2 + 2, 4);
}

TEST(MathTest2, TwoPlusTwoEqualsFour2) {
	EXPECT_EQ(2 + 2, 4);
}

TEST(MyTest, isBigTrue) {
	int number = 101;

	EXPECT_EQ(isBig(number), true);
}

TEST(MyTest, isBigFalse) {
	int number = 99;

	EXPECT_EQ(isBig(number), false);
}
