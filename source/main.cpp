#include <RSGL/RSGL.hpp>
#include <math.h>
#include <pthread.h>
int LENGTH =  500-40;
int WIDTH = 500-40;
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
				if (board.size() > y+1 && board.at(y+1).at(x).num == board.at(y).at(x).num || board.at(y).size()  > x+1 &&  board.at(y).at(x+1).num == board.at(y).at(x).num) return false;
			}  
		}
	} return fb;
}
bool running=true;
RSGL::window win("RSGL 2048",{X,Y,LENGTH,WIDTH+40},{200,200,200});
void sleep(float time){std::string cmd = "sleep " + std::to_string(time); system(cmd.data());}
std::vector<RSGL::color> colormap = {{255,255,255},{252,233,79},{138,226,52},{252,175,62},{114,159,207},{173,127,168},{193,125,17},{239,41,41},{184,150,0},{78,154,6},{206,92,0},{32,71,142}};


void eventHandler(){
	int r;
	win.checkEvents(); bool cnew=false;
	switch(win.event.type){
		case RSGL::quit: running =false;
		case RSGL::MouseButtonReleased:
			if (RSGL::RectCollidePoint({60,10,120,15},{win.event.x,win.event.y})){
				board = {};
				for (int y=0; y < rows; y++){  board.insert(board.end(),{{}}); for (int x=0; x < collums; x++){ 
					board.at(board.size()-1).insert(board.at(board.size()-1).end(),{{((x+5)+((LENGTH-(LENGTH/20))/100))+(((LENGTH-(LENGTH/20))/collums)*x)+(((LENGTH-(LENGTH/20))/125)*x),((y+40)+((WIDTH-(WIDTH/20))/100))+(((WIDTH-(WIDTH/20))/rows)*y)+(((WIDTH-(WIDTH/20))/125)*y),((LENGTH-(LENGTH/20))-20)/rows,((WIDTH-(WIDTH/20))-20)/rows}});}
				}
				for (int i=0; i<2; i++) {int x=rand() % collums, y=rand() % rows; int r=rand() % 100;  r=rand() % 100;  board.at(x).at(y).num=2; if (r >= 90) board.at(x).at(y).num=4; if (r >= 90) board.at(x).at(y).num=4;} 
			}
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
				 r=rand() % 100;  board.at(x).at(y).num=2; if (r >= 90) board.at(x).at(y).num=4;}  break;
			}
			else if (win.event.key == "Down" || win.event.key == "S" ){
				for (int y=0; y < board.size()-1; y++) for (int x=0; x < board.at(y).size(); x++){ 
					if (board.at(y).at(x).num){
						if (!board.at(y+1).at(x).num){cnew=true;  board.at(y+1).at(x).num =board.at(y).at(x).num;  board.at(y).at(x).num=0;}
						else if (board.at(y+1).at(x).num == board.at(y).at(x).num){cnew=true;  board.at(y+1).at(x).num *=2; board.at(y).at(x).num=0;} 
					}
				} 
				if (cnew){ int x=rand() % collums, y=rand() % rows; while(board.at(x).at(y).num){x=rand() % collums, y=rand() % rows;}
				 r=rand() % 100;  board.at(x).at(y).num=2; if (r >= 90) board.at(x).at(y).num=4;}  break;
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
				 r=rand() % 100;  board.at(x).at(y).num=2; if (r >= 90) board.at(x).at(y).num=4;}  break;
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
				 r=rand() % 100;  board.at(x).at(y).num=2; if (r >= 90) board.at(x).at(y).num=4;}  break;
				break;	
			}}
			else break;
		default: break;
	}
}

int d(int num){if (num >= 100 && num < 1000) return 1; else if (num >= 100) return 2; return 0;}

void piece::draw(){	
	
	if (num){ 
		RSGL::drawRect(r,colormap.at(log(num)/log(2)));		
		RSGL::drawText(std::to_string(num),{r.x+25 - (15*d(num)),r.y+35,r.width/3},"/usr/share/fonts/SansPosterBold.ttf",{255,255,255});
	} else RSGL::drawRect(r,colormap.at(0));		
	drawCir();
}
void piece::drawCir(){
	RSGL::drawCircle({r.x-(r.width/10),r.y-(r.length/10),(WIDTH+LENGTH)/50},{200,200,200}); // top left
	
	RSGL::drawCircle({r.width+r.x,r.y-(r.length/10),(WIDTH+LENGTH)/50},{200,200,200}); // top right
	
	RSGL::drawCircle({r.width+r.x - 8 ,r.length+r.y -(r.width/12),(WIDTH+LENGTH)/50},{200,200,200}); //bottom right
	RSGL::drawCircle({r.x-(r.width/10) ,r.length+r.y -(r.width/12),(WIDTH+LENGTH)/50},{200,200,200}); //bottom left
}
 
int main(){
	srand(time(NULL));
	for (int y=0; y < rows; y++){  board.insert(board.end(),{{}}); for (int x=0; x < collums; x++){ 
		board.at(board.size()-1).insert(board.at(board.size()-1).end(),{{
			((x+5)+((LENGTH-(LENGTH/20))/100))+(((LENGTH-(LENGTH/20))/collums)*x)+(((LENGTH-(LENGTH/20))/125)*x),
			((y+40)+((WIDTH-(WIDTH/20))/100))+(((WIDTH-(WIDTH/20))/rows)*y)+(((WIDTH-(WIDTH/20))/125)*y),((LENGTH-(LENGTH/20))-20)/rows,((WIDTH-(WIDTH/20))-20)/rows}});}
	}
	for (int i=0; i<2; i++) {int x=rand() % collums, y=rand() % rows; int r=rand() % 100;  r=rand() % 100;  board.at(x).at(y).num=2; if (r >= 90) board.at(x).at(y).num=4; if (r >= 90) board.at(x).at(y).num=4;} 
	while (running){
		eventHandler();
		for (int y=0; y < board.size(); y++) for (int x=0; x < board.at(y).size(); x++) board.at(y).at(x).draw();
		RSGL::drawRect({60,10,120,15},{255,240,0}); RSGL::drawText("New Game", {60,10,15},"/usr/share/fonts/SansPosterBold.ttf",{255,0,0}); 
		win.clear();
	} win.close();
}
