inline void addTileAtRandom(size_t tiles[4][4], int num);
inline bool tilesFull(size_t tiles[4][4]);
inline void moveTiles(size_t tiles[4][4], size_t x, size_t y, RSGL_point dir, RSGL_point pos);

inline size_t si_cstr_len(const char* string);

void addTileAtRandom(size_t tiles[4][4], int num) {
    if (tilesFull(tiles))
        return;

    RSGL_point p = RSGL_POINT(rand() % 4, rand() % 4);

    while (tiles[p.y][p.x]) 
        p = RSGL_POINT(rand() % 4, rand() % 4);

    tiles[p.y][p.x] = num;
}

bool tilesFull(size_t tiles[4][4]) {
    unsigned int x, y;
    for (y = 0; y < 4; y++)
        for (x = 0; x < 4; x++)
            if (!tiles[y][x])
                return false;
    return true;
}

void moveTiles(size_t tiles[4][4], size_t x, size_t y, RSGL_point dir, RSGL_point pos) {
    RSGL_point p = pos;
    size_t X = x;

    for (y; y < 4 && y >= 0; y += dir.y)
        for (x = X; x < 4 && x >= 0; x += dir.x) {
            while (tiles[y + pos.y][x + pos.x] == 0 && x + pos.x < 4) {
                tiles[y + pos.y][x + pos.x] = tiles[y + (pos.y - p.y)][x + (pos.x - p.x)];
                tiles[y + (pos.y - p.y)][x + (pos.x - p.x)] = 0;

                pos = RSGL_POINT(pos.x + p.x, pos.y + p.y);
            }

            if (tiles[y + pos.y][x + pos.x] == tiles[y + (pos.y - p.y)][x + (pos.x - p.x)]) {
                tiles[y + pos.y][x + pos.x] *= 2;
                tiles[y + (pos.y - p.y)][x + (pos.x - p.x)] = 0;
            } 

            pos = p;
        }
}

size_t si_cstr_len(const char* string) {
    char* str;
    for (str = (char*)string; *str; str++);
    size_t len = str - string;
}

char* si_u64_to_cstr(size_t num) {
	static char buffer[20 + 1]; /* NOTE(EimaMei): 20 chars is the maximum of numbers we can have in an u64. */
	char* cur_char = buffer;

	do {
		*cur_char++ = (num % 10) +'0';
		num /= 10;
	} while (num > 0);
	*cur_char = '\0';

	char* res = buffer;

	char* actual_str = res;

	char* a = actual_str;
    
    size_t len = si_cstr_len(res);

	char* b = actual_str + len - 1;
	len *= 0.5;

	while (len--) {
		do { typeof((*a)) tmp = (*a); (*a) = (*b); (*b) = tmp; } while (0);
		a++, b--;
	}

	res = actual_str;

	return res;
}