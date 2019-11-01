#include "kernel.h"
#include "lib/utils.h"
#include "lib/mman.c"

void kernel_entry() {
	vga_init(WHITE,BLACK);
	puts("Hello World");
	//game_buf = malloc(2000);
	uint8_t x,y;
	for (x = 0; x < 80; x++) {
		for (y = 0; y < 25; y++) {
			game_buf[x][y] = 1;
		}
	}

	/*game_buf[5][6] = 1;
	game_buf[5][7] = 1;
	game_buf[5][8] = 1;

	game_buf[15][6] = 1;
	game_buf[15][7] = 1;
	game_buf[5][8] = 1;

	game_buf[25][6] = 1;
	game_buf[25][7] = 1;
	game_buf[25][8] = 1;

	game_buf[35][6] = 1;
	game_buf[35][7] = 1;
	game_buf[35][8] = 1;

	game_buf[45][6] = 1;
	game_buf[45][7] = 1;
	game_buf[45][8] = 1;*/

	return;
}

int neighbours(int x, int y) {
		// based on [x][y]
        int count = 0; 
        // behind
        if (x > 0 && y > 0) count += game_buf[x-1][y-1];
        if (x > 0) count += game_buf[x-1][y];
        if (x > 0 && y < 24) count += game_buf[x-1][y+1];
        
        // in line
        if (y > 0) count += game_buf[x][y-1];
        if (y < 24) count += game_buf[x][y+1];
        
        // in front
        if (x < 79 && y > 0) count += game_buf[x+1][y-1];
        if (x < 79) count += game_buf[x+1][y];
        if (x < 79 && y < 24) count += game_buf[x+1][y+1];
        
        return count;        
}

 void update_game() {
	 	uint8_t x,y;
        for (x = 0; x < 80; x++) {
            for (y = 0; y < 25; y++) {
				int res = neighbours(x,y);
                if (game_buf[x][y] == 0) {
                    if (res == 3) {
                        game_buf[x][y]=1;
                    }
                } else {
                    if (!(res&2)) {
                        game_buf[x][y]=0;
                    }
                }
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
