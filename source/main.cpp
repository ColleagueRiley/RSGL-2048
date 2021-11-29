#include "../include/RSGL/RSGL.hpp"
#include <pthread.h>
#define LENGTH 500
#define WIDTH 500
#define X 500
#define Y 500
#define rows 4
#define collums 4
struct piece{RSGL::rect r; RSGL::color c; int num; void draw();};
std::vector<std::vector<piece>> board;
bool fullBoard(){for(int y=0; y < board.size(); y++) for(int x=0; x < board.at(y).size(); x++) if (!board.at(y).at(x).num && board.at(y).at(x).num != 2048) return false; return true; }
bool running=true;
RSGL::window win("RSGL 2048",{X,Y,LENGTH,WIDTH},{200,200,200});
void sleep(float time){std::string cmd = "sleep " + std::to_string(time); system(cmd.data());}

void eventHandler(){
	win.checkEvents(); bool cnew=false;
	switch(win.event.type){
		case RSGL::quit: running =false;
		case RSGL::KeyReleased: 
			if (win.event.key == "Escape") running=false;
			else if (fullBoard()){}
			else if (win.event.key == "Up"){
				for (int y=board.size()-1; y > 0; y--) for (int x=0; x < board.at(y).size(); x++){ 
					if (board.at(y).at(x).num){
						if (!board.at(y-1).at(x).num){cnew=true; board.at(y-1).at(x).c =board.at(y).at(x).c; board.at(y-1).at(x).num =board.at(y).at(x).num;  board.at(y).at(x).num=0; board.at(y).at(x).c={255,255,255};}
						else if (board.at(y-1).at(x).num == board.at(y).at(x).num){cnew=true; board.at(y-1).at(x).num *=2; board.at(y).at(x).num=0; board.at(y).at(x).c={255,255,255};} 
					}
				} 
				if (cnew){ int x=rand() % collums, y=rand() % rows; while(board.at(x).at(y).num){x=rand() % collums, y=rand() % rows;}
				board.at(x).at(y).c ={255,248,0}; board.at(x).at(y).num=2;}  break;
			}
			else if (win.event.key == "Down"){
				for (int y=0; y < board.size()-1; y++) for (int x=0; x < board.at(y).size(); x++){ 
					if (board.at(y).at(x).num){
						if (!board.at(y+1).at(x).num){cnew=true; board.at(y+1).at(x).c =board.at(y).at(x).c; board.at(y+1).at(x).num =board.at(y).at(x).num;  board.at(y).at(x).num=0; board.at(y).at(x).c={255,255,255};}
						else if (board.at(y+1).at(x).num == board.at(y).at(x).num){cnew=true;  board.at(y+1).at(x).num *=2; board.at(y).at(x).num=0; board.at(y).at(x).c={255,255,255};} 
					}
				} 
				if (cnew){ int x=rand() % collums, y=rand() % rows; while(board.at(x).at(y).num){x=rand() % collums, y=rand() % rows;}
				board.at(x).at(y).c ={255,248,0}; board.at(x).at(y).num=2;}  break;
				break;
			}
			else if (win.event.key == "Left"){
				for (int y=0; y < board.size(); y++) for (int x=board.at(y).size()-1; x > 0; x--){ 
					if (board.at(y).at(x).num){
						if (!board.at(y).at(x-1).num){ cnew=true; board.at(y).at(x-1).c =board.at(y).at(x).c; board.at(y).at(x-1).num =board.at(y).at(x).num;  board.at(y).at(x).num=0; board.at(y).at(x).c={255,255,255};}
						else if (board.at(y).at(x-1).num == board.at(y).at(x).num){ cnew=true; board.at(y).at(x-1).num *=2; board.at(y).at(x).num=0; board.at(y).at(x).c={255,255,255};} 
					}
				} 
				if (cnew){ int x=rand() % collums, y=rand() % rows; while(board.at(x).at(y).num){x=rand() % collums, y=rand() % rows;}
				board.at(x).at(y).c ={255,248,0}; board.at(x).at(y).num=2;}  break;
				break;				
			}
			else if (win.event.key == "Right"){{
				for (int y=0; y < board.size(); y++) for (int x=0; x < board.at(y).size()-1; x++){ 
					if (board.at(y).at(x).num){
						if (!board.at(y).at(x+1).num){ cnew=true; board.at(y).at(x+1).c =board.at(y).at(x).c; board.at(y).at(x+1).num =board.at(y).at(x).num;  board.at(y).at(x).num=0; board.at(y).at(x).c={255,255,255};}
						else if (board.at(y).at(x+1).num == board.at(y).at(x).num){ cnew=true; board.at(y).at(x+1).num *=2; board.at(y).at(x).num=0; board.at(y).at(x).c={255,255,255};} 
					}
				} 
				if (cnew){ int x=rand() % collums, y=rand() % rows; while(board.at(x).at(y).num){x=rand() % collums, y=rand() % rows;}
				board.at(x).at(y).c ={255,248,0}; board.at(x).at(y).num=2;}  break;
				break;	
			}}
			else break;
		default: break;
	}
}

void piece::draw(){
	RSGL::drawRect(r,c);
	if (num){
		RSGL::drawText(std::to_string(num),{r.x - ((r.length)/3.36) ,r.y + (r.width/2),r.width/3},"res/fonts/SansPosterBold.ttf",{255,255,255});
	}
}


int main(){
	srand(time(NULL));
	for (int y=0; y < rows; y++){  board.insert(board.end(),{{}}); for (int x=0; x < collums; x++){ 
		board.at(board.size()-1).insert(board.at(board.size()-1).end(),{{(x+(LENGTH/100))+((LENGTH/collums)*x)+((LENGTH/125)*x),(y+(WIDTH/100))+((WIDTH/rows)*y)+((WIDTH/125)*y),(WIDTH-20)/rows},{255,255,255},0});}
	}
	for (int i=0; i<2; i++) {int x=rand() % collums, y=rand() % rows;  board.at(x).at(y).c ={255,248,0}; board.at(x).at(y).num=2;} 
	while (running){
		eventHandler(); win.clear();
		for (int y=0; y < board.size(); y++) for (int x=0; x < board.at(y).size(); x++) board.at(y).at(x).draw();
	} win.close();
}