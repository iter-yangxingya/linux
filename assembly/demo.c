#include <stdio.h>

void function1() {
	int j;
	for (int i = 0; i < 100000; i++)
		j += i;
}
void function2() {
	int j;
	function1();
	for (int i = 0; i < 200000; i++)
		j = i;
}

int main() {
	for (int i = 0; i < 100; i++)
		function1();

	for (int i = 0; i < 50000; i++)
		function2();

	return 0;
}
