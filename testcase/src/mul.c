#include "trap.h"

int main() {
	nemu_assert(3 * 5 == 15);
	nemu_assert(19689 * 55233 == 1087482537);
	nemu_assert(156648652 * 789965323ll == 123747002974694596ll);
	nemu_assert(-3 * 5 == -15);
	nemu_assert(-19689 * 55233 == -1087482537);
	nemu_assert(-156648652 * 789965323ll == -123747002974694596ll);
	nemu_assert(3 * -5 == -15);
	nemu_assert(19689 * -55233 == -1087482537);
	nemu_assert(156648652 * -789965323ll == -123747002974694596ll);
	nemu_assert(-3 * -5 == 15);
	nemu_assert(-19689 * -55233 == 1087482537);
	nemu_assert(-156648652 * -789965323ll == 123747002974694596ll);

	HIT_GOOD_TRAP;
	return 0;
}

