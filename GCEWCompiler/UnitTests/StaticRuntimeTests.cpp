#include "pch.h"

TEST(StaticRuntime, EmptyTest) {
	TEST_COMPILER(EmptyTest, void main() {});
}

TEST(StaticRuntime, InitTest) {
	TEST_COMPILER(InitTest, void main() {
		int i = 10;
	});
}

TEST(StaticRuntime, SimpleOperationTest) {
	TEST_COMPILER(SimpleOperationTest, void main() {
		int a = 5;
		int b = 10;
		int c = 1;
		c = a + b;
		c = a - b;
		c = a / b;
		c = a * b;
	});
}

TEST(StaticRuntime, ForTest) {
	TEST_COMPILER(ForTest, void main() {
		int sum = 0;
		for (int i = 0; i < 10; i = i + 1) {
			sum = sum + i;
		}
	});
}

TEST(StaticRuntime, WhileTest) {
	TEST_COMPILER(WhileTest, void main() {
		int sum = 0;
		int i = 0;
		while (i < 10) {
			sum = sum + i;
			i = i + 1
		}
	});
}

TEST(StaticRuntime, IfTest) {
	TEST_COMPILER(IfTest, void main() {
		int i = 0;
		if (i == 0) {
			i = 42;
		}
	});
}

TEST(StaticRuntime, IfElseTest) {
	TEST_COMPILER(IfElseTest, void main() {
		int i = 0;
		if (i == 0) {
			i = 42;
		}
		else {
			i = -42;
		}
	});
}