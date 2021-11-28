#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "deps/X11/Xlib.h"
#include "deps/X11/Xatom.h"
#include "deps/X11/cursorfont.h"
#include "deps/png++/image.hpp"                     


#define RSGLRGBTOHEX(r, g, b) ((r << 16) + (g << 8) + b)

namespace RSGL{
    const int KeyPressed=2;
    const int KeyReleased=3;
    const int MouseButtonPressed=4;
    const int MouseButtonReleased=5;
    const int MousePosChanged=6;
    const int quit = 33;
    const int dnd = 34;

    struct point{int x, y;};
    struct rect {int x, y , width, length; };
    struct circle{int x, y; int radius;};
    struct area{int width,length;};
    struct color{int r,g,b; float a=1.0;};

    int value(RSGL::rect r){return r.x+r.y+r.width+r.length;};
    int value(RSGL::circle c){return c.x+c.y+c.radius;};

    struct image{
      RSGL::rect r;
      RSGL::rect srcr = r; 
      const char* file; 
      std::vector<std::vector<int>> cords;
      XImage* image;
      png::image< png::rgba_pixel> img;
      Pixmap pixmap;
      GC gc;
      bool loaded = false;
    };


    struct drawable{
      private:
        struct Event{
          int type;
          int button;
          int x,y;
        };
      public:
        RSGL::rect r;
        Display* display;
        Event event;
        Drawable d;
        RSGL::color color;
        void loadArea(drawable& dsrc, RSGL::rect r, RSGL::point p);
    };

    struct pixmap : drawable{
        pixmap(){}
        pixmap(RSGL::drawable dr,RSGL::area a);
        private:
          XImage* data;
    };

    struct window : drawable{
      private:
        struct Event{
          int type;
          int button;
          int x,y;
          int keycode;
          std::string key;
          int ledState;
        };
        char keyboard[32];
      public:
        std::string name;
        RSGL::color color;
        RSGL::pixmap dbuffer; //double buffer
        Event event;

        int setColor(RSGL::color c);
        window(){}
        window(std::string,RSGL::rect, RSGL::color, bool resize = false);
        void checkEvents();
        bool isPressed(unsigned long key);
        bool isPressed(std::string key);
        void close();
        void clear();
    };
    
    window root;
    

    int CircleCollidePoint(RSGL::circle c, RSGL::point p);
    int CircleCollideRect(RSGL::circle c, RSGL::rect r);
    int CircleCollide(RSGL::circle cir1,RSGL::circle cir2);
    int RectCollidePoint(RSGL::rect r, RSGL::point p);
    int RectCollideRect(RSGL::rect r, RSGL::rect r2);
    int PointCollide(RSGL::point p, RSGL::point p2);
    int ImageCollideRect(RSGL::image img, RSGL::rect r);
    int ImageCollideCircle(RSGL::image img, RSGL::circle c);
    int ImageCollidePoint(RSGL::image img, RSGL::point p);
    int ImageCollideImage(RSGL::image img, RSGL::image img2);
  
    struct Text{
      RSGL::circle rect; 
      RSGL::color c;
      std::string text;
      const char* f;
      RSGL::window d=RSGL::root;
      Text(std::string txt, RSGL::circle r, const char* font, RSGL::color col, bool draw=true, RSGL::drawable d=RSGL::root);
      void draw();
      Text(){}
    };

    void drawText(std::string text, RSGL::circle r, const char* font, RSGL::color c, RSGL::drawable d=RSGL::root);

    bool isPressed(unsigned long key);
    int drawPoint(RSGL::point p, color c,RSGL::drawable win=root);

    
    void drawRect(RSGL::rect r,color c, bool fill=True,int stroke=1, int lineColor = 0, RSGL::color lineCol = {}, RSGL::drawable win=root);

    void* drawLine(RSGL::point p1, RSGL::point p2, RSGL::color c, int width=1);

    int drawCircle(RSGL::circle c, color col,bool fill=true,int stroke=1, int lineColor = 0, RSGL::color lineCol = {},RSGL::drawable win=root);

    void drawImage(std::string fileName, RSGL::rect r,bool resize=true,RSGL::drawable d=RSGL::root);

    std::vector<std::vector<RSGL::color>> resizeImage(std::vector<std::vector<RSGL::color>> image, RSGL::rect newSize, RSGL::rect ogsize);


    std::vector<std::string> fileDialog(std::string title,bool multiple=false,bool save=false, bool directory=false);
    void notifiy(std::string title, std::string content,std::string image="");
    void messageBox(std::string message, bool question=false,bool error=false);
#ifndef RSGLNAMESPACEEXTENTION
};
#endif

void* RSGL::drawLine(RSGL::point p1, RSGL::point p2, RSGL::color c, int width){
    int slope=0;
    if (p1.x > p2.x){
        int x3 = p2.x;
        p2.x = p1.x;
        p1.x = x3; 
    }
    if (p1.y > p2.y){
        int y3 = p2.y;
        p2.y = p1.y;
        p1.y = y3;
    }
    if (p1.x==p2.x && p1.y == p2.y){ RSGL::drawRect({p1.x,p1.y,width,width},c); return 0;}
    else if (!p2.y-p1.y && p2.x-p1.x){ RSGL::drawRect({p1.x,p1.y,1,abs(p1.x-p2.x)},c); return 0;}
    else if (!p2.x-p1.x && p2.y-p1.y){ RSGL::drawRect({p1.x,p1.y,abs(p1.y-p2.y),1},c); return 0;}
    else if ((p1.y-p2.y) && (p2.x-p1.x)) slope = (p2.y-p1.y)/(p2.x-p1.x);
    
    for (int x=0; x < (p2.x-p1.x); x++){
        RSGL::drawRect({p1.x+x,p1.y+(x*slope),1,width},c);
    } return NULL;
}