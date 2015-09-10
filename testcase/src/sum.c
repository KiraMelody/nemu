#include "trap.h"

int main() {
	int i = 1, sum = 0;
	while(i <= 100) {
		sum += i;
		i ++;
	}

	nemu_assert(sum == 5050);
	HIT_GOOD_TRAP;

	return 0;
}
