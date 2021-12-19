#include "../include/RSGL/RSGL.hpp"
#include <pthread.h>
int LENGTH =  500;
int WIDTH = 500;
#define X 500
#define Y 500
#define rows 4
#define collums 4
struct piece{RSGL::rect r; int num=0; void draw(); void drawCir();};
std::vector<std::vector<piece>> board;
bool fullBoard(){
	bool fb=true;
	for(int y=0; y < board.size(); y++){
		for(int x=0; x < board.at(y).size(); x++) 
			if (!board.at(y).at(x).num && board.at(y).at(x).num != 2048){fb=false; break;}
		if (!fb) break;
	}
	if (fb){
		for(int y=0; y < board.size(); y++){
			for(int x=0; x < board.at(y).size(); x++){
				if (board.size()  < y+1 && board.at(y+1).at(x).num == board.at(y).at(x).num || board.at(y).size()  < x+1 &&  board.at(y).at(x+1).num == board.at(y).at(x).num) return false;
			}  
		}
	} return fb;
}
bool running=true;
RSGL::window win("RSGL 2048",{X,Y,LENGTH,WIDTH},{200,200,200});
void sleep(float time){std::string cmd = "sleep " + std::to_string(time); system(cmd.data());}
std::map<int, RSGL::color> colormap = {{0,{255,255,255}},{2,{252,233,79}},{4,{138,226,52}},{8,{252,175,62}},{16,{114,159,207}},{32,{173,127,168}},{64,{193,125,17}},{128,{239,41,41}},{256,{184,150,0}},
{512,{78,154,6}},{1024,{206,92,0}},{2048,{32,71,142}}};


void eventHandler(){
	win.checkEvents(); bool cnew=false;
	if (!fullBoard()) win.clear();
	switch(win.event.type){
		case RSGL::quit: running =false;
		case RSGL::KeyReleased: 
			if (win.event.key == "Escape") running=false;
			else if (fullBoard()){}
			else if (win.event.key == "Up" || win.event.key == "W"){
				for (int y=board.size()-1; y > 0; y--) for (int x=0; x < board.at(y).size(); x++){ 
					if (board.at(y).at(x).num){
						if (!board.at(y-1).at(x).num){cnew=true;  board.at(y-1).at(x).num =board.at(y).at(x).num;  board.at(y).at(x).num=0;}
						else if (board.at(y-1).at(x).num == board.at(y).at(x).num){cnew=true; board.at(y-1).at(x).num *=2; board.at(y).at(x).num=0;} 
					}
				} 
				if (cnew){ int x=rand() % collums, y=rand() % rows; while(board.at(x).at(y).num){x=rand() % collums, y=rand() % rows;}
				 board.at(x).at(y).num=2;}  break;
			}
			else if (win.event.key == "Down" || win.event.key == "S" ){
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
			else if (win.event.key == "Left" || win.event.key == "A"){
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
			else if (win.event.key == "Right" || win.event.key == "D"){{
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
	if (num){ 
		int exp=0;
		if (num > 10 && num < 100) exp=1; if (num > 100 && num < 1000) exp=2; if (num > 1000) exp=3;
		RSGL::drawText(std::to_string(num),{(int)(r.x),(int)(r.y + (r.width/2)), r.width/3},"res/fonts/SansPosterBold.ttf",{255,255,255});
	}	
}
void piece::drawCir(){
	RSGL::drawCircle({r.x-((int)(LENGTH/230)),r.y-((int)(WIDTH/230)),(WIDTH+LENGTH)/50},{200,200,200}); // top left
	RSGL::drawCircle({r.x+((int)(LENGTH/60))+r.length,r.y-((int)(WIDTH/230)),(WIDTH+LENGTH)/50},{200,200,200}); // top right
	RSGL::drawCircle({r.x-((int)(LENGTH/230)),r.y+r.width+((int)(WIDTH/60)),(WIDTH+LENGTH)/50},{200,200,200}); //bottom left
	RSGL::drawCircle({r.x+r.length+((int)(LENGTH/60)),r.y+r.width+((int)(WIDTH/60)),(WIDTH+LENGTH)/50},{200,200,200}); //bottom right*/
}

int main(){
	srand(time(NULL));
	for (int y=0; y < rows; y++){  board.insert(board.end(),{{}}); for (int x=0; x < collums; x++){ 
		board.at(board.size()-1).insert(board.at(board.size()-1).end(),{{((x+5)+((LENGTH-(LENGTH/20))/100))+(((LENGTH-(LENGTH/20))/collums)*x)+(((LENGTH-(LENGTH/20))/125)*x),((y+5)+((WIDTH-(WIDTH/20))/100))+(((WIDTH-(WIDTH/20))/rows)*y)+(((WIDTH-(WIDTH/20))/125)*y),((LENGTH-(LENGTH/20))-20)/rows,((WIDTH-(WIDTH/20))-20)/rows}});}
	}
	for (int i=0; i<2; i++) {int x=rand() % collums, y=rand() % rows;   board.at(x).at(y).num=2;} 
	while (running){
		eventHandler();
		for (int y=0; y < board.size(); y++) for (int x=0; x < board.at(y).size(); x++){ board.at(y).at(x).draw();  board.at(y).at(x).drawCir();}
	} win.close();
}