#include "game-common.h"
#include "x86.h"

void init_timer();
int syscall(int id, ...);

void add_irq_handle(int irq, void *handler) {
	syscall(0, irq, handler);
}

void
game_init(void) {
	init_timer();

	add_irq_handle(0, timer_event);

	Log("game start!");

	main_loop();

	assert(0); /* main_loop是死循环，永远无法返回这里 */
}
