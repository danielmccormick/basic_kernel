#include "kernel.h"
#include "lib/utils.h"
#include "lib/mman.c"
#include "lib/game.h"

void kernel_entry() {
	vga_init(WHITE,BLACK);
	puts("Hello World");
	init_game();
	return;
}

void render_game_buf() {
	uint8_t x,y;
	for (x = 0; x < 80; x++) {
		for (y = 0; y < 25; y++) {
			if (game_buf[x][y]) {
				draw_unit_box(x,y,WHITE);
			} else {
				draw_unit_box(x,y,BLACK);
			}
		}
	}
}

void game_of_life() {
	render_game_buf();
	sleep_n_cycles(10000000);
	update_game();
}
