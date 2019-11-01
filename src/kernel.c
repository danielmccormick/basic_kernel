#include "kernel.h"
#include "lib/utils.h"
#include "lib/mman.c"

uint8_t big_stack_buf[2000];

void kernel_entry() {
	vga_init(WHITE,BLACK);
	puts("Hello World");
	game_buf = big_stack_buf;
	memset(game_buf,1,2000);
	puts("Wohoohoo! Finished");
	return;
}

void update_game() {
	uint8_t x,y;
	for (x = 0; x < 80; x++) {
		for (y = 0; y < 25; y++) {
			size_t idx = 80*y+x;
			game_buf[idx] = !game_buf[idx];
		}
	}
	return;
}

void game_of_life() {
	update_game();
	uint8_t x,y;
	size_t idx;
	for (x = 0; x < 80; x++) {
		for (y = 0; y < 25; y++) {
			idx = 80*y+x;
			if (game_buf[idx]) {
				draw_unit_box(x,y,WHITE);
			} else {
				draw_unit_box(x,y,BLACK);
			}
		}
	}
	sleep_n_cycles(10000000);
}
