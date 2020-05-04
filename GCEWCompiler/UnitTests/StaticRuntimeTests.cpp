#include "pch.h"

TEST(StaticRuntime, EmptyTest) {
	TEST_COMPILER(EmptyTest, int main() {});
}