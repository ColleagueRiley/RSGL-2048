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
std::vector<RSGL::color> colormap = {{255,255,255},{252,233,79},{138,226,52},{252,175,62},{114,159,207},{173,127,168},{193,125,17},{239,41,41},{184,150,0},{78,154,6},{206,92,0},{32,71,142}};

RSGL::Button b("New Game","/usr/share/fonts/TTF/SansPosterBold.ttf", {65,7,15}, {60,10,120,15},{255,0,0},{255,240,0});

void eventHandler(){ win.checkEvents(); b.checkEvents();
	bool cnew=false; int r;
	if (b.event==1){
		board = {};
		for (int y=0; y < rows; y++){  board.insert(board.end(),{{}}); for (int x=0; x < collums; x++){ 
			board.at(board.size()-1).insert(board.at(board.size()-1).end(),{{((x+5)+((LENGTH-(LENGTH/20))/100))+(((LENGTH-(LENGTH/20))/collums)*x)+(((LENGTH-(LENGTH/20))/125)*x),((y+40)+((WIDTH-(WIDTH/20))/100))+(((WIDTH-(WIDTH/20))/rows)*y)+(((WIDTH-(WIDTH/20))/125)*y),((LENGTH-(LENGTH/20))-20)/rows,((WIDTH-(WIDTH/20))-20)/rows}});}
		}
		for (int i=0; i<2; i++) {int x=rand() % collums, y=rand() % rows; int r=rand() % 100;  r=rand() % 100;  board.at(x).at(y).num=2; if (r >= 90) board.at(x).at(y).num=4; if (r >= 90) board.at(x).at(y).num=4;} 
	} 
	switch(win.event.type){
		case RSGL::quit: running =false; break;
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

int d(int num){if (num > 100 && num < 1000) return 4; else if (num > 100) return 9;  else if (num > 10) return 3.8; return 3.5;}
void piece::draw(){	
	RSGL::drawRoundRect(r, num ? colormap.at(log(num)/log(2)) : colormap.at(0) );		
	if (num) RSGL::drawText(std::to_string(num),{r.x+r.length/(d(num)) ,r.y+r.length/2,r.length/4},"/usr/share/fonts/TTF/SansPosterBold.ttf",{255,255,255});	
}
 
int main(){
	srand(time(NULL)); // random seed for making random numbers
	// generate the board
	for (int y=0; y < rows; y++){  board.insert(board.end(),{{}}); for (int x=0; x < collums; x++){ 
		board.at(board.size()-1).insert(board.at(board.size()-1).end(),{{
			((x+5)+((LENGTH-(LENGTH/20))/100))+(((LENGTH-(LENGTH/20))/collums)*x)+(((LENGTH-(LENGTH/20))/125)*x),
			((y+40)+((WIDTH-(WIDTH/20))/100))+(((WIDTH-(WIDTH/20))/rows)*y)+(((WIDTH-(WIDTH/20))/125)*y),((LENGTH-(LENGTH/20))-20)/rows,((WIDTH-(WIDTH/20))-20)/rows}});}
	}
	// add two random nums, randomly chosen to be 2 or 4 (with a higher change of it being 2)
	for (int i=0; i<2; i++) {int x=rand() % collums, y=rand() % rows; int r=rand() % 100;  r=rand() % 100;  board.at(x).at(y).num=2; if (r >= 90) board.at(x).at(y).num=4; if (r >= 90) board.at(x).at(y).num=4;} 
	while (running){
		eventHandler();
		for (int y=0; y < board.size(); y++) for (int x=0; x < board.at(y).size(); x++) board.at(y).at(x).draw();
		b.draw(); RSGL::drawRoundRect({60,10,120,15},{255,240,0},false);
		win.clear();
	} win.close();
}
