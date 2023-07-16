#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include "headers/engine.hpp"
#include <map>

#include <stdlib.h>

class game{
private:
    //window
    const unsigned row{20}, column{10}, FPS{60};
    const int default_x{600}, default_y{720}, adj_size{3}, font_size{20}, buffer{8};
    const float resize_x{}, resize_y{}, cell_size{27};
    const sf::Vector2i cell_size_v{};
    sf::RectangleShape rect;   
    sf::RenderWindow window;
    sf::Font font;
    sf::Texture w_cube, b_back, b_intro, b_second;
    sf::Sprite cube_p, background, intro_p, second_cube;
    sf::Text pause_text, score_text, level_text, des_text, press_text;

    //game setting
    int flag{1},direction{};
    float speed {10};
    long score{}, level_n{}, old_level{};
    char rotate{' '},second_c{};
    enum class game_run{ON, GAMEOVER, STOP};
    game_run status{game_run::ON};
    std::map <int, sf::Color> cube_color{
    {1,sf::Color::Red},{2,sf::Color::Green},{3,sf::Color::Blue},
    {4,sf::Color::Yellow},{5,sf::Color::Cyan},{6,sf::Color::Magenta}};

    sf::Time TimeSinceLastMove {sf::Time::Zero};
    sf::Time TimePerFrame {sf::seconds(1.f/ speed)};
    sf::Clock clock ;
    std::vector<std::vector<short>> matrix; 
    std::unique_ptr<engine> tetris = std::make_unique<engine>(column, row);

public:
    game(unsigned x,unsigned y);
    ~game(){std::cout<<"GAME is Closed"<<std::endl;};

    void draw();
    bool draw_cube();
    void set_second();

    void g_event();
    bool move_event(sf::Event event);


    //the main loop would be in the run function
    void INTRO();
    void run();
    void play();

};

//game constructor
game::game(unsigned x, unsigned y)
    :resize_x{static_cast<float>(x/default_x)}, resize_y{static_cast<float>(y/default_y)}, 
    cell_size_v{static_cast<int>(cell_size * resize_x),static_cast<int>(cell_size * resize_y)},
    rect{sf::Vector2f(cell_size_v.x - 1, cell_size_v.y - 1)}{

    //window initialisation
    window.create(sf::VideoMode(x, y), "Tetris");
    window.setFramerateLimit(FPS);

    //font initialisation
    font.loadFromFile("font/Arial.ttf");
    score_text.setFillColor(sf::Color::White);
    score_text.setFont(font);
    score_text.setPosition(cell_size * 14, cell_size*2);
    score_text.setCharacterSize(font_size);

    level_text.setFillColor(sf::Color::White);
    level_text.setFont(font);
    level_text.setPosition(cell_size * 14, cell_size*3.5);
    level_text.setCharacterSize(font_size);

    des_text.setFillColor(sf::Color(60,60,60));
    des_text.setFont(font);
    des_text.setPosition(cell_size * 14, cell_size*5);
    des_text.setCharacterSize(font_size);
    des_text.setString("P: PAUSE\nR: RESUME\nG: RESTART");

    pause_text.setFillColor(sf::Color::White);
    pause_text.setFont(font);
    pause_text.setPosition(cell_size*column/2, cell_size*row/2);
    pause_text.setCharacterSize(font_size*2);
    pause_text.setString("PAUSE");

    press_text.setFillColor(sf::Color::White);
    press_text.setFont(font);
    press_text.setPosition((cell_size-adj_size)*column, cell_size*row);
    press_text.setCharacterSize(font_size);
    press_text.setString("< PRESS [S] >");

    //image initialisation
    if(!b_intro.loadFromFile("image/intro.png"))
        std::cerr<<"can't find intro image" << std::endl;
    intro_p.setTexture(b_intro);
    intro_p.setPosition(0,0);

    if(!b_back.loadFromFile("image/background.png"))
        std::cerr<<"can't find background image" << std::endl;
    background.setTexture(b_back);
    background.setPosition(0,0);

    if(!w_cube.loadFromFile("image/white.png"))
        std::cerr<<"can't find image" << std::endl;
    cube_p.setTexture(w_cube);
    cube_p.setScale(sf::Vector2f(cell_size_v.x/cube_p.getLocalBounds().width, cell_size_v.y/cube_p.getLocalBounds().height));
    second_cube.setPosition(cell_size*(column+4.5), cell_size*(row/2+2.5));
  }        

void game::set_second(){
    switch(second_c){
        case 'I': b_second.loadFromFile("image/I.png"); break;
        case 'O': b_second.loadFromFile("image/O.png"); break;
        case 'L': b_second.loadFromFile("image/L.png"); break;
        case 'l': b_second.loadFromFile("image/rL.png"); break;
        case 'Z': b_second.loadFromFile("image/Z.png"); break;
        case 'z': b_second.loadFromFile("image/rZ.png"); break;
        case 'T': b_second.loadFromFile("image/rZ.png"); break;

        default: break;
    }
    second_cube.setTexture(b_second);
}

//INTRO
void game::INTRO(){
    window.draw(intro_p);
    (flag > 100) ? flag = 1:flag++;
    if(flag > 20)
        window.draw(press_text);
    window.display();
}

//game actions
void game::play(){
    if (!tetris->action(direction, rotate))
        status = game_run::GAMEOVER;
    matrix = tetris->get_m();
    score = tetris->get_score();
    level_n = tetris->get_level(); 
    second_c = tetris->get_second();
    set_second();
    draw_cube();
    if(level_n > old_level){speed += 10;old_level = level_n;}
}

bool game::draw_cube(){
    for(int j = 8; j < matrix.size(); j++){ 
        for(int i = 0; i < matrix.at(j).size(); i++){    
            cube_p.setPosition((cell_size+adj_size)*(i+1),(j-buffer)*(cell_size+adj_size));
            if (matrix.at(j).at(i) > 0){
                cube_p.setColor(cube_color[matrix.at(j).at(i)]);
                window.draw(cube_p);}
        }
    }
    return true;
}        

void game::draw(){ 
    std::stringstream sc, lv;
   
    //draw image
    if((TimeSinceLastMove.asSeconds() >= TimePerFrame.asSeconds()) && flag == 0)
    {        
        window.clear();
        window.draw(background);

        switch(status){
            case game_run::ON: play();break;
            case game_run::STOP: window.draw(pause_text);break;
            case game_run::GAMEOVER: draw_cube();break;
            default:break;
        }

        //n update
        sc << "SCORE: " << score;
        score_text.setString(sc.str());
        lv << "LEVEL: " << level_n;
        level_text.setString(lv.str());

        window.draw(des_text);
        window.draw(score_text);
        window.draw(level_text);
        window.draw(second_cube);

        window.display();
        TimeSinceLastMove = sf::Time::Zero;
    }
    else if (flag > 0)
        INTRO();
} 

//move
bool game::move_event(sf::Event event){
    switch(event.key.code){
        case sf::Keyboard::Left:direction = -1;break;
        case sf::Keyboard::Right:direction = 1;break;
        case sf::Keyboard::Space:rotate = 'r';break;

        default:break;         
    }
    return true;
}        


//key event
void game::g_event(){
    sf::Event event;
    while (window.pollEvent(event))
    { 
        if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right) 
             || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            move_event(event);
        else{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && flag == 0 && status != game_run::GAMEOVER)
                status = game_run::ON;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && flag == 0 && status != game_run::GAMEOVER)
                status = game_run::STOP;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && flag == 0 && status == game_run::GAMEOVER){
                status = game_run::ON;    
                tetris = std::make_unique<engine>(column, row);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                flag = 0;}
    }
}        

//operate the game
void game::run(){
     while(window.isOpen())
    {
        sf::Time df = clock.restart();
        TimeSinceLastMove += df;
        TimePerFrame = sf::seconds(1.f/speed);
        
        //game update
        draw();
        g_event();
    }
}

int main(void){

    game gg(600, 720);
    gg.run();

    return 0;
} 




