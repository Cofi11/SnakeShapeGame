#include "snake.h"
int WinMain() {
    Game g;
    while (g.running())
    { 
    	if(!(g.gameStart()))
       	 	g.Intro();
       	else{
       		if(g.Ziv()){
       			g.EventPolling();
       			
       			g.update();   
       			
       			g.render();
       		}
       		else g.EndGame();
		}      
    }
    
	return 0;
}
