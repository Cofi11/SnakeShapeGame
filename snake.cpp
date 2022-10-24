#include "snake.h";


void Game::InitVariables(){
	this->window= NULL;
	
	
	zmica.length=3;
	zmica.direction=2;
	zmica.prevdirection=2;
	zmica.block=28;
	zmica.snake[0].x=570;
	zmica.snake[0].y=420;
	for(int i=1 ; i < zmica.length ; i++){
		zmica.snake[i].x=zmica.snake[i-1].x-zmica.block;
		zmica.snake[i].y=zmica.snake[i-1].y;
	}
	
	
	oblik.duzina=4;
	
	
	blockSnake.setSize(sf::Vector2f(zmica.block, zmica.block));
    blockSnake.setFillColor(sf::Color(200,150,42,255));
    blockSnake.setOutlineThickness(2);
    blockSnake.setOutlineColor(sf::Color::Yellow);
    
    
    blockShape1.setSize(sf::Vector2f(zmica.block, zmica.block));
    blockShape1.setFillColor(sf::Color(151,44,221,155));
    blockShape1.setOutlineThickness(2);
    blockShape1.setOutlineColor(sf::Color::Black);
    
    blockShape2.setSize(sf::Vector2f(zmica.block, zmica.block));
    blockShape2.setFillColor(sf::Color(221,44,151,155));
    blockShape2.setOutlineThickness(2);
    blockShape2.setOutlineColor(sf::Color::Black);
    
	
	
	if(!grass.loadFromFile("public/Texture1Grass.png"))std::cout<<"Nema teksture";
	if(!zmijica.loadFromFile("public/zmijica.png"))std::cout<<"Nema teksture";
	if(!oci.loadFromFile("public/eyes.png"))std::cout<<"Nema teksture";
	if(!hrana.loadFromFile("public/jabucica.png"))std::cout<<"Nema teksture";	
	if(!ples.loadFromFile("public/ples.jpg"))std::cout<<"Nema teksture";
	
	
	
	if(!font.loadFromFile("public/arial.ttf"))std::cout<<"Nema fonta";
	
	//Text
		std::stringstream ss;
		ss<<"Length: "<<zmica.length;
		score.setString(ss.str());
		score.setFont(font);
		score.setCharacterSize(20);
		//score.setColor();
		std::stringstream ss1;
		ss1<<"Level: "<<level;
		nivo.setString(ss1.str());
		nivo.setFont(font);
		nivo.setCharacterSize(20);
		nivo.setPosition(0,25);
		
	
	
	//OVDE TI JE HRANA da znas
		food.setTexture(hrana);
	
		sf::Vector2u TextureSize;
		TextureSize=hrana.getSize();
	
		float scaleX=(float) zmica.block / TextureSize.x;
		float scaleY=(float) zmica.block / TextureSize.y;
	
		food.setScale(scaleX,scaleY);
	
	
	zmija.setTexture(zmijica);
	zmija.setPosition(sf::Vector2f(0.f,zmija.getLocalBounds().height));
	zmija.setScale(-1,1);
	
	
	dugme.setSize(sf::Vector2f(200.f,140.f));
	dugme.setPosition(500.f,550.f);
	dugme.setFillColor(sf::Color(142,142,142,255));
	dugme.setOutlineThickness(5.f);
	dugme.setOutlineColor(sf::Color::Red);
	
	
	if(!pesma.openFromFile("public/F-skraceno.ogg"))std::cout<<"Nema pesme";
	pesma.setVolume(10.f);
	
	inGame=false;
	pojedena=true;
	
	rast=0;
	level=0;
}

void Game::InitWindow(){
	this->window = new sf::RenderWindow (sf::VideoMode(1200.f,900.f),"SNAKE Game", sf::Style::Titlebar | sf::Style::Close);
	window -> setFramerateLimit(60);
}

Game::Game(){
	InitVariables();
	InitWindow();
	srand(time(NULL));
}

Game::~Game(){
	delete this->window;
}


const bool Game::running () const{
	return window->isOpen();
}

const bool Game::gameStart() const{
	return inGame;
}

const bool Game::Ziv() const{
	if(zmica.direction == 0){
   		if(zmica.snake[0].y  >= window->getSize().y) return false;
	}
   	if(zmica.direction == 1){
   		if(zmica.snake[0].x < 0)return false;
	}
	if(zmica.direction == 2){
		if(zmica.snake[0].x  >= window->getSize().x)return false;
	}
	if(zmica.direction == 3){
		if(zmica.snake[0].y < 0)return false;
	}
	
	for(int i=1 ; i< zmica.length ; i++){
		if(zmica.snake[0].x == zmica.snake[i].x && zmica.snake[0].y == zmica.snake[i].y)return false;
	}
	
	return true;
}

const bool Game::LevelUp() const{
	bool moze1=true, moze2=true;
	
	if(zmica.length != oblik.duzina)return false;
	
	int n=zmica.length;
	
	if(zmica.snake[0].x != oblik.shape[0].x || zmica.snake[0].y != oblik.shape[0].y)moze1 = false;
	else if(zmica.snake[n-1].x != oblik.shape[n-1].x || zmica.snake[n-1].y != oblik.shape[n-1].y)moze1 = false;
	if(zmica.snake[0].x != oblik.shape[n-1].x || zmica.snake[0].y != oblik.shape[n-1].y)moze2 = false;
	else if(zmica.snake[n-1].x != oblik.shape[0].x || zmica.snake[n-1].y != oblik.shape[0].y)moze2 = false;
	
	if(!moze1 && !moze2)return false;
	
	int p=2;
	for(int i=1 ; i<zmica.length-1 ; i++){
		for(int j=1 ; j<zmica.length-1 ; j++){
			if(zmica.snake[i].x == oblik.shape[j].x && zmica.snake[i].y == oblik.shape[j].y){
				p++;
				break;
			}
		}
	}
	if(p!=n)return false;
	return true;
	
	/*for(int i=0 ; i<zmica.length ; i++){
		if(zmica.snake[i].x != oblik.shape[i].x || zmica.snake[i].y != oblik.shape[i].y)moze1 = false;
	}
	for(int i=0 ; i<zmica.length ; i++){
		if(zmica.snake[i].x != oblik.shape[zmica.length-1-i].x || zmica.snake[i].y != oblik.shape[zmica.length-1-i].y)moze2 = false;
	}
	if(!moze1 && !moze2)return false;
	return true;   */
	
}


sf::Sprite Game::grassBackground(){
	sf::Sprite background;
	background.setTexture(grass);
	
	sf::Vector2u TextureSize;
	TextureSize=grass.getSize();
	sf::Vector2u WindowSize;
	WindowSize=window->getSize();
	
	float scaleX=(float) WindowSize.x/TextureSize.x;
	float scaleY=(float) WindowSize.y/TextureSize.y;
	
	background.setScale(scaleX,scaleY);
	background.setColor(sf::Color(0,255,0,169));
	return background;
}



void Game::Movement()
{	
		for(int i = zmica.length-rast; i > 0; --i)
	   	{	
	       	zmica.snake[i].x = zmica.snake[i-1].x;
	       	zmica.snake[i].y = zmica.snake[i-1].y;
	   	}
	
   		if(zmica.direction == 0){
   			zmica.snake[0].y += 30;
		}
   		if(zmica.direction == 1){
   			zmica.snake[0].x -= 30;
		}
		if(zmica.direction == 2){
			zmica.snake[0].x += 30;
		}
		if(zmica.direction == 3){
			zmica.snake[0].y -= 30;
		}
	rast=0;
}

void Game::SpawnFood()
{
//	srand(time(NULL));
    int x1,y1,i=0;
    while(true){
	    x1 = rand() % 40;
	    x1*=30;
	    y1 = rand() % 30;
	    y1*=30;
	    while((x1!=zmica.snake[i].x || y1!=zmica.snake[i].y) && i<zmica.length) i++;
	    if(i==zmica.length){
	        food.setPosition(x1,y1);
	        pojedena=false;
	        break;
		}
	    else i=0;
	}
}

/*void Game::SpawnShape()
{
	while(true){
    int x1, y1, smer, presmer = 2, i = 1;
    int br=0;
    bool opet = false;
    x1 = rand() % 20 + 10;
    y1 = rand() % 16 + 7;
    x1 *= 30;
    y1 *= 30; 
    oblik.shape[0].x = x1;
    oblik.shape[0].y = y1;
    while(i < oblik.duzina)
    {
        smer = rand() % 6;
        if(smer==4 || smer==5)smer=presmer;
        if(smer + presmer == 3) continue;
        switch (smer)
        {
            case 0:
            	if(y1 + 30 >= window->getSize().y){
            		br++;
            		continue;
				}
			 	y1 += 30;
				for(int j=0 ; j<i ; j++){
        			if(oblik.shape[j].x == x1 && oblik.shape[j].y == y1){
        			opet = true;
        			y1-=30;
        			break;
					}
				} 
				break;
            case 1:
            	if(x1 - 30 < 0){
            		br++;
            		continue;
            	}
				x1 -= 30;
				for(int j=0 ; j<i ; j++){
        			if(oblik.shape[j].x == x1 && oblik.shape[j].y == y1){
        			opet = true;
        			x1+=30;
        			break;
					}
				}
				break;
            case 2:
            	if(x1 + 30 >= window->getSize().x){
            		br++;
            		continue;
				}
				x1 += 30;
				for(int j=0 ; j<i ; j++){
        			if(oblik.shape[j].x == x1 && oblik.shape[j].y == y1){
        			opet = true;
        			x1-=30;
        			break;
					}
				}
				break;
            case 3:
            	if(y1 - 30 < 0){
            		br++;
            		continue;
				}
				y1 -= 30;
				for(int j=0 ; j<i ; j++){
        			if(oblik.shape[j].x == x1 && oblik.shape[j].y == y1){
        			opet = true;
        			y1+=30;
        			break;
					}
				}
				break; 
        }
		if(opet){
			br++;
			opet=false;
			continue;
		}
		if(br>100){
			break;
		}	
        presmer = smer;
        oblik.shape[i].x = x1;
        oblik.shape[i].y = y1;
        i++;
        br=0;
    }
    if(i==oblik.duzina)break;
	}
	level++;
}*/

void Game::SpawnShape()
{
    int x1, y1, smer, presmer = 2, i = 1;
    int br=0;
    bool opet = false;
    x1 = rand() % 20 + 10;
    y1 = rand() % 16 + 7;
    x1 *= 30;
    y1 *= 30; 
    oblik.shape[0].x = x1;
    oblik.shape[0].y = y1;
    while(i < oblik.duzina)
    {
        smer = rand() % 6;
        if(smer==4 || smer==5)smer=presmer;
        if(smer + presmer == 3) continue;
        switch (smer)
        {
            case 0:
            	if(y1 + 30 >= window->getSize().y){
            		opet=true;
            		break;
				}
			 	y1 += 30;
				for(int j=0 ; j<i ; j++){
        			if(oblik.shape[j].x == x1 && oblik.shape[j].y == y1){
        			opet = true;
        			y1-=30;
        			break;
					}
				} 
				break;
            case 1:
            	if(x1 - 30 < 0){
            		opet=true;
            		break;
            	}
				x1 -= 30;
				for(int j=0 ; j<i ; j++){
        			if(oblik.shape[j].x == x1 && oblik.shape[j].y == y1){
        			opet = true;
        			x1+=30;
        			break;
					}
				}
				break;
            case 2:
            	if(x1 + 30 >= window->getSize().x){
            		opet=true;
            		break;
				}
				x1 += 30;
				for(int j=0 ; j<i ; j++){
        			if(oblik.shape[j].x == x1 && oblik.shape[j].y == y1){
        			opet = true;
        			x1-=30;
        			break;
					}
				}
				break;
            case 3:
            	if(y1 - 30 < 0){
            		opet=true;
            		break;
				}
				y1 -= 30;
				for(int j=0 ; j<i ; j++){
        			if(oblik.shape[j].x == x1 && oblik.shape[j].y == y1){
        			opet = true;
        			y1+=30;
        			break;
					}
				}
				break; 
        }
        if(br>100){
			SpawnShape();
			return;
		}
		if(opet){
			br++;
			opet=false;
			continue;
		}
        presmer = smer;
        oblik.shape[i].x = x1;
        oblik.shape[i].y = y1;
        i++;
        br=0;
    }
    level++;
}


void Game::PauseGame(){
	sf::Event ev;
	bool pauza=true;
	
	while(pauza){
		while (window->pollEvent(ev))
        {
        	if (ev.type == sf::Event::Closed)
                window->close();
            if (ev.type == sf::Event::KeyReleased)break;
        }
        while (window->pollEvent(ev))
        {
        	if (ev.type == sf::Event::Closed)
                window->close();
            if (ev.type == sf::Event::KeyPressed)return;
        }
	}
}

void Game::EndGame(){
	inGame = false;
	zmica.length=3;
	zmica.direction=2;
	zmica.prevdirection=2;
	zmica.block=28;
	zmica.snake[0].x=570;
	zmica.snake[0].y=420;
	for(int i=1 ; i < zmica.length ; i++){
		zmica.snake[i].x=zmica.snake[i-1].x-zmica.block;
		zmica.snake[i].y=zmica.snake[i-1].y;
	}
	oblik.duzina=4;
	level=0;
	
	sf::Sprite crnci;
	crnci.setTexture(ples);
	
	sf::Text text;
	text.setFont(font);
	text.setString("GAME OVER");
	text.setCharacterSize(169);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width/2 , text.getLocalBounds().top + text.getLocalBounds().height/2);
	text.setPosition(window->getSize().x/2,window->getSize().y*2/3);

	
	sf::Vector2u TextureSize;
	TextureSize=ples.getSize();
	
	float scaleX=(float)  window->getSize().x / TextureSize.x;
	float scaleY=(float)  window->getSize().y / TextureSize.y;
	
	crnci.setScale(scaleX,scaleY);
	
	pesma.play();
	sf::Time tMax,t;
	sf::Clock c;
	tMax = pesma.getDuration();
	t=c.restart();
	while(t<tMax){
		t=c.getElapsedTime();
		window->clear();
		window->draw(crnci);
		window->draw(text);
		window->display();
	}
}


void Game::Intro(){
	sf::Text Naslov("SNAKE GAME",font);
	Naslov.setCharacterSize(169);
	Naslov.setStyle(sf::Text::Bold);
	Naslov.setColor(sf::Color::Red);
	Naslov.setOrigin(Naslov.getLocalBounds().left+Naslov.getLocalBounds().width/2,Naslov.getLocalBounds().top+Naslov.getLocalBounds().height/2);
	Naslov.setPosition(window->getSize().x/2,window->getSize().y/2);
	
	sf::Text play("PLAY",font);
	play.setCharacterSize(69);
	play.setColor(sf::Color::Red);
	play.setOrigin(play.getLocalBounds().left+play.getLocalBounds().width/2,play.getLocalBounds().top+play.getLocalBounds().height/2);
	play.setPosition(dugme.getPosition().x+dugme.getSize().x/2,dugme.getPosition().y+dugme.getSize().y/2);
	
	
    while  (window->pollEvent(event)){
        if (event.type == sf::Event::Closed) 
            window->close();
    }
    updateMousePos();
    if(zmija.getPosition().x<=750.f){
    	zmija.move(3.f,0.f);
    }
    else{
    	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
    		if(dugme.getGlobalBounds().contains(MousePosView)){
    			inGame=true;
			}
		}
	}
    window->clear();
    window->draw(grassBackground());
    window->draw(Naslov);
    window->draw(zmija);
    if(zmija.getPosition().x>750.f){
    	window->draw(dugme);
    	window->draw(play);
	}
	window->display();
	if(inGame){
		zmija.setTexture(zmijica);
		zmija.setPosition(sf::Vector2f(751.f,zmija.getLocalBounds().height));
		zmija.setScale(-1,1);
	
	
		dugme.setSize(sf::Vector2f(200.f,140.f));
		dugme.setPosition(500.f,550.f);
		dugme.setFillColor(sf::Color(142,142,142,255));
		dugme.setOutlineThickness(5.f);
		dugme.setOutlineColor(sf::Color::Red);
	}
    //std::cout<<"Mouse position: "<<sf::Mouse::getPosition(*this->window).x<<" "<<sf::Mouse::getPosition(*this->window).y<<std::endl;
}

void Game::updateMousePos(){
	MousePosWin=sf::Mouse::getPosition(*this->window);
	MousePosView=this->window->mapPixelToCoords(MousePosWin);
}

void Game::EventPolling(){
	while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            else if (event.type == sf::Event::KeyPressed){
            	if(event.key.code == sf::Keyboard::Escape)PauseGame();
			}
        }
}

void Game::update(){
    sf::Time t;
    sf::Time tMax = sf::milliseconds(150);
    sf::Clock c;
    t=c.restart();
    
    bool kliknuolisidugmebrale = false;
	
	while(t < tMax){
		t=c.getElapsedTime();
		if(!kliknuolisidugmebrale){
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
    			if(zmica.direction!=2){
    				zmica.prevdirection=zmica.direction;
	    			zmica.direction = 1;
	    		}
	    		kliknuolisidugmebrale = true;
			}
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
    			if(zmica.direction!=1){
    				zmica.prevdirection=zmica.direction;
	    			zmica.direction = 2;
	    		}
	    		kliknuolisidugmebrale = true;
			}	
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    			if(zmica.direction!=0){
    				zmica.prevdirection=zmica.direction;
    				zmica.direction = 3;
    			}
    			kliknuolisidugmebrale = true;
			}
    		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    			if(zmica.direction!=3){
    				zmica.prevdirection=zmica.direction;
		   		 	zmica.direction = 0;
			    }
			    kliknuolisidugmebrale = true;
			}
		}
	}
	if(level==0)SpawnShape();
	else if(LevelUp()){
		int l=rand()%3+1;
		oblik.duzina+=l;
		SpawnShape();
	}
	Movement();
	if(zmica.length != oblik.duzina){	
		if(pojedena){
			SpawnFood();
			pojedena=false;
		}
		else{
			if(zmica.snake[0].x == food.getPosition().x && zmica.snake[0].y == food.getPosition().y){
				pojedena = true;
				rast=1;
				zmica.length++;
				zmica.snake[zmica.length-1] = zmica.snake[zmica.length-2];
			}
		}
	}
	std::stringstream ss;
	ss<<"Length: "<<zmica.length;
	score.setString(ss.str());
	
	std::stringstream ss1;
	ss1<<"Level: "<<level;
	nivo.setString(ss1.str());
}


void Game::render(){
	window->clear();
	window->draw(grassBackground());
	if(zmica.length != oblik.duzina)window->draw(food);
	
	blockShape1.setPosition(oblik.shape[0].x,oblik.shape[0].y);
	window->draw(blockShape1);
	for(int i=1 ; i<oblik.duzina-1 ; i++){
		blockShape2.setPosition(oblik.shape[i].x,oblik.shape[i].y);
		window->draw(blockShape2);
	}
	blockShape1.setPosition(oblik.shape[oblik.duzina-1].x,oblik.shape[oblik.duzina-1].y);
	window->draw(blockShape1);
	
	sf::Texture* pokazivac = &oci;
	blockSnake.setPosition(zmica.snake[0].x,zmica.snake[0].y);
	blockSnake.setTexture(pokazivac);
    window->draw(blockSnake);
    blockSnake.setTexture(NULL);
		for(int i = 1; i < zmica.length; i++)
        {
        	blockSnake.setPosition(zmica.snake[i].x,zmica.snake[i].y);
            window->draw(blockSnake);
        }
    window->draw(score);
    window->draw(nivo);
    window->display();
}
