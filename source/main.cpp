#include "../include/RSGL/RSGL.hpp"
#include <pthread.h>
#define LENGTH 500
#define WIDTH 500
#define X 500
#define Y 500
#define rows 4
#define collums 4
struct piece{RSGL::rect r; int num=0; void draw(); void drawCir();};
std::vector<std::vector<piece>> board;
bool fullBoard(){for(int y=0; y < board.size(); y++) for(int x=0; x < board.at(y).size(); x++) if (!board.at(y).at(x).num && board.at(y).at(x).num != 2048) return false; return true; }
bool running=true;
RSGL::window win("RSGL 2048",{X,Y,LENGTH,WIDTH},{200,200,200});
void sleep(float time){std::string cmd = "sleep " + std::to_string(time); system(cmd.data());}
std::map<int, RSGL::color> colormap = {{0,{255,255,255}},{2,{252,233,79}},{4,{138,226,52}},{8,{252,175,62}},{16,{114,159,207}},{32,{173,127,168}},{64,{193,125,17}},{128,{239,41,41}},{256,{184,150,0}},
{512,{78,154,6}},{1024,{206,92,0}},{2048,{32,71,142}}};

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
						if (!board.at(y-1).at(x).num){cnew=true;  board.at(y-1).at(x).num =board.at(y).at(x).num;  board.at(y).at(x).num=0;}
						else if (board.at(y-1).at(x).num == board.at(y).at(x).num){cnew=true; board.at(y-1).at(x).num *=2; board.at(y).at(x).num=0;} 
					}
				} 
				if (cnew){ int x=rand() % collums, y=rand() % rows; while(board.at(x).at(y).num){x=rand() % collums, y=rand() % rows;}
				 board.at(x).at(y).num=2;}  break;
			}
			else if (win.event.key == "Down"){
				for (int y=0; y < board.size()-1; y++) for (int x=0; x < board.at(y).size(); x++){ 
					if (board.at(y).at(x).num){
						if (!board.at(y+1).at(x).num){cnew=true;  board.at(y+1).at(x).num =board.at(y).at(x).num;  board.at(y).at(x).num=0;}
						else if (board.at(y+1).at(x).num == board.at(y).at(x).num){cnew=true;  board.at(y+1).at(x).num *=2; board.at(y).at(x).num=0;} 
					}
				} 
				if (cnew){ int x=rand() % collums, y=rand() % rows; while(board.at(x).at(y).num){x=rand() % collums, y=rand() % rows;}
				 board.at(x).at(y).num=2;}  break;
				break;
			}
			else if (win.event.key == "Left"){
				for (int y=0; y < board.size(); y++) for (int x=board.at(y).size()-1; x > 0; x--){ 
					if (board.at(y).at(x).num){
						if (!board.at(y).at(x-1).num){ cnew=true;  board.at(y).at(x-1).num =board.at(y).at(x).num;  board.at(y).at(x).num=0;}
						else if (board.at(y).at(x-1).num == board.at(y).at(x).num){ cnew=true; board.at(y).at(x-1).num *=2; board.at(y).at(x).num=0;} 
					}
				} 
				if (cnew){ int x=rand() % collums, y=rand() % rows; while(board.at(x).at(y).num){x=rand() % collums, y=rand() % rows;}
				 board.at(x).at(y).num=2;}  break;
				break;				
			}
			else if (win.event.key == "Right"){{
				for (int y=0; y < board.size(); y++) for (int x=0; x < board.at(y).size()-1; x++){ 
					if (board.at(y).at(x).num){
						if (!board.at(y).at(x+1).num){ cnew=true; board.at(y).at(x+1).num =board.at(y).at(x).num;  board.at(y).at(x).num=0;}
						else if (board.at(y).at(x+1).num == board.at(y).at(x).num){ cnew=true; board.at(y).at(x+1).num *=2; board.at(y).at(x).num=0;} 
					}
				} 
				if (cnew){ int x=rand() % collums, y=rand() % rows; while(board.at(x).at(y).num){x=rand() % collums, y=rand() % rows;}
				 board.at(x).at(y).num=2;}  break;
				break;	
			}}
			else break;
		default: break;
	}
}

void piece::draw(){
	RSGL::drawRect(r,colormap.at(num));		
	if (num) RSGL::drawText(std::to_string(num),{(int)(r.x - (r.length/3.36)),(int)(r.y + (r.width/2)), r.width/3},"res/fonts/SansPosterBold.ttf",{255,255,255});
}
void piece::drawCir(){
	RSGL::drawCircle({r.length+r.x+6,r.y+6,10},{200,200,200});
	RSGL::drawCircle({r.x+6,r.width+r.y+6,10},{200,200,200});
	RSGL::drawCircle({r.x+6,r.y+6,10},{200,200,200});
	RSGL::drawCircle({r.length+r.x+6,r.width+r.y+6,10},{200,200,200});
}

int main(){
	srand(time(NULL));
	for (int y=0; y < rows; y++){  board.insert(board.end(),{{}}); for (int x=0; x < collums; x++){ 
		board.at(board.size()-1).insert(board.at(board.size()-1).end(),{{(x+(LENGTH/100))+((LENGTH/collums)*x)+((LENGTH/125)*x),(y+(WIDTH/100))+((WIDTH/rows)*y)+((WIDTH/125)*y),(LENGTH-20)/rows,(WIDTH-20)/rows}});}
	}
	for (int i=0; i<2; i++) {int x=rand() % collums, y=rand() % rows;   board.at(x).at(y).num=2;} 
	while (running){
		eventHandler(); win.clear();
		for (int y=0; y < board.size(); y++) for (int x=0; x < board.at(y).size(); x++){ board.at(y).at(x).draw();  board.at(y).at(x).drawCir();}
	} win.close();
}