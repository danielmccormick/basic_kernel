#include "kernel.h"
#include "lib/utils.h"
#include "lib/mman.c"

uint8_t game_buf[80][25];
uint8_t double_buf[80][25];

void kernel_entry() {
	vga_init(WHITE,BLACK);
	puts("Hello World");
	//game_buf = malloc(2000);
	uint8_t x,y;
	for (x = 0; x < 80; x++) {
		for (y = 0; y < 25; y++) {
			game_buf[x][y] = 0;
			double_buf[x][y] = 0;
		}
	}

	game_buf[5][3] = 1;
	game_buf[5][4] = 1;
	game_buf[5][5] = 1;
	game_buf[5][6] = 1;
	game_buf[5][7] = 1;
	game_buf[5][8] = 1;

	game_buf[15][6] = 1;
	game_buf[15][7] = 1;
	game_buf[15][8] = 1;

	game_buf[25][6] = 1;
	game_buf[25][7] = 1;
	game_buf[25][8] = 1;

	game_buf[35][6] = 1;
	game_buf[35][7] = 1;
	game_buf[35][8] = 1;

	game_buf[45][6] = 1;
	game_buf[45][7] = 1;
	game_buf[45][8] = 1;

	return;
}

int neighbours(int x, int y) {
		// based on [x][y]
        int count = 0; 
        // behind
        if (x > 0 && y > 0 && game_buf[x-1][y-1]) { count++; } 
        if (x > 0 && game_buf[x-1][y]) { count++; }
        if (x > 0 && y < 24 && game_buf[x-1][y+1]) { count++; }
        
        // in line
        if (y > 0 && game_buf[x][y-1]) { count++; }
        if (y < 24 && game_buf[x][y+1]) { count ++; }
        
        // in front
        if (x < 79 && y > 0 && game_buf[x+1][y-1]) { count ++; }
        if (x < 79 && game_buf[x+1][y]) { count ++; } 
        if (x < 79 && y < 24 && game_buf[x+1][y+1] ) { count ++; }
        
        return count;        
}

 void update_game() {
	 	uint8_t x,y;
        for (x = 0; x < 80; x++) {
            for (y = 0; y < 25; y++) {
				int res = neighbours(x,y);
                if (game_buf[x][y] == 0) {
                    if (res == 3) {
                        double_buf[x][y] = 1;
                    } else {
						double_buf[x][y] = 0;
					}
                } else {
                    if (res != 2 && res != 3) {
                        double_buf[x][y] = 0;
                    } else {
						double_buf[x][y] = 1;
					}
                }
            }
        }
		 for (x = 0; x < 80; x++) {
            for (y = 0; y < 25; y++) {
				game_buf[x][y] = double_buf[x][y];
			}
		 }
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
