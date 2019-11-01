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
	return;
}

int neighbours(int x, int y) {
		const uint8_t **board = game_buf;
        // based on [x][y]
        int count = 0; 
        // behind
        if (x > 0 && y > 0) count += board[x-1][y-1];
        if (x > 0) count += board[x-1][y];
        if (x > 0 && y < 24) count += board[x-1][y+1];
        
        // in line
        if (y > 0) count += board[x][y-1];
        if (y < 24) count += board[x][y+1];
        
        // in front
        if (x < 79 && y > 0) count += board[x+1][y-1];
        if (x < 79) count += board[x+1][y];
        if (x < 79 && y < 24) count += board[x+1][y+1];
        
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
	update_game();
	render_game_buf();
	sleep_n_cycles(10000000);
}
