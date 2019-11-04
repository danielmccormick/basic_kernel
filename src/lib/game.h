#include "utils.h"
typedef uint8_t game_buffer[80][25];
game_buffer game_buf;
game_buffer double_buf;

void clear_game_buffers() {
    uint8_t x,y;
	for (x = 0; x < 80; x++) {
		for (y = 0; y < 25; y++) {
			game_buf[x][y] = 0;
            double_buf[x][y] = 0;

		}
	}
}

void draw_penta_dec_on_x(uint8_t x) {
     //Penta-decathlons
  	game_buf[x-1][4] = 1;
  	game_buf[x][4] = 1;
  	game_buf[x+1][4] = 1;

    game_buf[x][5] = 1;
    game_buf[x][6] = 1;

  	game_buf[x-1][7] = 1;
  	game_buf[x][7] = 1;
  	game_buf[x+1][7] = 1;

  	game_buf[x-1][9] = 1;
  	game_buf[x][9] = 1;
  	game_buf[x+1][9] = 1;

  	game_buf[x-1][10] = 1;
  	game_buf[x][10] = 1;
  	game_buf[x+1][10] = 1;

    game_buf[x-1][12] = 1;
  	game_buf[x][12] = 1;
  	game_buf[x+1][12] = 1;

    game_buf[x][13] = 1;
    game_buf[x][14] = 1;

    game_buf[x-1][15] = 1;
  	game_buf[x][15] = 1;
  	game_buf[x+1][15] = 1;
}

void init_game() {
    clear_game_buffers();

    draw_penta_dec_on_x(6);
    draw_penta_dec_on_x(70);
}

int neighbours(int x, int y) {
        int count = 0; 
        if (x > 0 && y > 0 && game_buf[x-1][y-1]) { count++; } 
        if (x > 0 && game_buf[x-1][y]) { count++; }
        if (x > 0 && y < 24 && game_buf[x-1][y+1]) { count++; }
        
        if (y > 0 && game_buf[x][y-1]) { count++; }
        if (y < 24 && game_buf[x][y+1]) { count ++; }
        
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