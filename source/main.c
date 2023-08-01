#define RSGL_IMPLEMENTATION
#define RSGL_NO_AUDIO
#include "RSGL.h"
#include "util.h"

int main() {
    RSGL_window* window = RSGL_createWindow("RSGL-2048", RSGL_RECT(0, 0, 500, 500), RGFW_CENTER);

    RGFW_registerJoystick(window, 0);

    init:

    size_t tiles[4][4] = {
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0},
                        {0, 0, 0, 0}
                        };

    RSGL_color colors[] = {
                                {255, 255, 255, 255},
                                {252, 233, 79, 255},
                                {138, 226, 52, 255},
                                {252, 175, 62, 255},
                                {114, 159, 207, 255},
                                {173, 127, 168, 255},
                                {193, 125, 17, 255},
                                {239, 41, 41, 255},
                                {184, 150, 0, 255},
                                {78, 154, 6, 255},
                                {206, 92, 0, 255},
                                {32, 71, 142, 255}
                            };


    unsigned int tileW = (window->r.w - 40) / 4;
    
    srand(time(NULL));

    int i, x, y;
    for (i = 0; i < 2; i++)
        addTileAtRandom(tiles,  ((rand() % 10) == 3) ? 4 : 2);

    int font =  RSGL_loadFont("SansPosterBold.ttf");

    RSGL_button b = {"", RSGL_RECT(3, 3, RSGL_textWidth("Reset", font, 15, 5) * 2, 15)};

    while (true) {
        while (RSGL_window_checkEvent(window)) {
            switch (window->event.type) {
                case RGFW_quit:
                    goto quit;
                default:
                    break;
            }

            RSGL_button_update(&b, window->event);
            if (b.s == RSGL_pressed || RGFW_isPressedI(window, RGFW_Return) || RGFW_isPressedJS(window, 0, RGFW_JS_START))
                goto init;

            if (tilesNotFull(tiles) == false)
                continue;

            if ((RGFW_isPressedI(window, RGFW_Up) || RGFW_isPressedI(window, RGFW_W)) || RGFW_isPressedJS(window, 0, RGFW_JS_UP))
                moveTiles(tiles, 0, 1, RSGL_POINT(1, 1), RSGL_POINT(0, -1));
            else if ((RGFW_isPressedI(window, RGFW_Left) || RGFW_isPressedI(window, RGFW_A)) || RGFW_isPressedJS(window, 0, RGFW_JS_LEFT)) 
                moveTiles(tiles, 1, 0, RSGL_POINT(1, 1), RSGL_POINT(-1, 0));
            else if ((RGFW_isPressedI(window, RGFW_Right) || RGFW_isPressedI(window, RGFW_D)) || RGFW_isPressedJS(window, 0, RGFW_JS_RIGHT))
                moveTiles(tiles, 3, 0, RSGL_POINT(-1, 1), RSGL_POINT(1, 0));
            else if ((RGFW_isPressedI(window, RGFW_Down) || RGFW_isPressedI(window, RGFW_S)) || RGFW_isPressedJS(window, 0, RGFW_JS_DOWN))
                moveTiles(tiles, 0, 2, RSGL_POINT(1, -1), RSGL_POINT(0, 1));
            else continue;
         
            addTileAtRandom(tiles, 2);
        }


        for (y = 0; y < 4; y++)
            for (x = 0; x < 4; x++) {
                RSGL_color color = colors[
                                    tiles[y][x] ? 
                                        ((int)(log(tiles[y][x]) / log(2))) 
                                    : 0];

                RSGL_rect tileR = {15 + ((x * tileW) + 3 * x), 20 + ((y * tileW) + 3 * y), tileW, tileW};
                RSGL_drawRoundRect(tileR, RSGL_POINT(15, 15), color);


                if (tiles[y][x] == 0)
                    continue;

                char* textStr = si_u64_to_cstr(tiles[y][x]);
                size_t len = si_cstr_len(textStr);
                int textSize= (tileR.w / 3);
                RSGL_circle textC = {tileR.x + ((tileR.w + textSize) / 3.25) - (len * tileR.w / 15), tileR.y + ((tileR.w + textSize)/ 3.25), tileR.w / 3};

                RSGL_drawText(textStr, font, textC, RSGL_RGB(255, 255, 255));
            }
        
        RSGL_drawRoundRect(b.r, RSGL_POINT(15, 15), RSGL_RGB(255, 0, 0));
        RSGL_drawText("Reset", font, RSGL_CIRCLE(5, 3, 15), RSGL_RGB(255, 255, 255));

        RSGL_window_clear(window, RSGL_RGB(200, 200, 200));
    }

    quit:

    RSGL_window_close(window);
}