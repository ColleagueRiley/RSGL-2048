#include "../include/RSGL/RSGL.hpp"

#define LENGTH 500
#define WIDTH 500
#define X 500
#define Y 500
#define rows 4
#define collums 4

struct peice{RSGL::rect r; RSGL::color c; int num;};
std::vector<std::vector<peice>> board;

bool running=true;
RSGL::window win("2048",{X,Y,LENGTH,WIDTH},{200,200,200});

int main(){
	srand(time(NULL));
	for (int y=0; y < rows; y++){  board.insert(board.end(),{{}}); for (int x=0; x < collums; x++){ 
		board.at(board.size()-1).insert(board.at(board.size()-1).end(),{{(x+5)+((LENGTH/collums)*x),(y+5)+((WIDTH/rows)*y),(LENGTH-20)/collums,(WIDTH-20)/rows},{255,255,255},0});}
	}
	for (int i=0; i<2; i++) {int x=rand() % collums, y=rand() % rows;  board.at(x).at(y).c ={255,248,0}; board.at(x).at(y).num=2;} 
	while (running){
		win.checkEvents(); win.clear();
		if (win.event.type == RSGL::quit) running=false;
		for (int y=0; y < board.size(); y++) for (int x=0; x < board.at(y).size(); x++){ 
			if (board.at(y).at(x).num) 
			RSGL::drawText(std::to_string(board.at(y).at(x).num),{0,0,board.at(y).at(x).r.width/2},"res/fonts/SansPosterBold.ttf",{255,255,255});
			// RSGL::drawRect(board.at(y).at(x).r,board.at(y).at(x).c);
		}
	} win.close();
}
