#include "Game.h"

using namespace sf;

// private functions
void Game::initializeVariables()
{
	this->window = nullptr;

    this->endGame = false;
    this->points = 0;
    this->enemySpawnTimerMax = 20.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    
    this->maxEnemies = 8;
    this->mouseHeld = false;
    this->health = 12;
}

void Game::initializeWindow()
{
	this->videomode.height = 700;
    this->videomode.width = 600;


	this->window = new RenderWindow(this->videomode, "First Game", Style::Titlebar| Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initializeFonts()
{
    if (this->font.loadFromFile("Fonts/Lora-italic-VariableFont_wght.ttf"))
    {
        std::cout << "Error HAHA JK!::Failed to load FONTS!" << "\n";
    }
}

void Game::initTexts()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(12);
    this->uiText.setFillColor(Color::White);
    this->uiText.setOutlineColor(Color::Blue);
    this->uiText.setString("None");
}

void Game::initializeEnemies()
{
    this->enemy.setPosition(50.f,50.f);
    this->enemy.setSize(Vector2f(100.f, 100.f));
    this->enemy.setScale(Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(Color::Red);
    this->enemy.setOutlineColor(Color::Green);
    this->enemy.setOutlineThickness(1.f);





}


// constructors and destructors
Game::Game()
{
	this->initializeVariables();
	this->initializeWindow();
    this->initializeFonts();
    this->initTexts();
    


    this->initializeEnemies();


}

Game::~Game()
{
	delete this->window;



}


// Accesors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}




// Functions


void Game::spawnEnemy()
{
    /*
    to spawn an enemy, were going to spawn enemies and set their color and positions randomly
    - sets a random position (diff)
    - sets a random color
    - Adds enemy to the vector


    */

    this->enemy.setPosition( // where to spawn the enemy - Window.x size - enemy's size
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
        //static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
    ); // this way they are always spawning in the screen

    
    
    //Randomize enemy type
    int type = rand() % 6;

    switch (type)
    {
    case 0:
        this->enemy.setSize(Vector2f(30.f, 30.f));
        this->enemy.setFillColor(Color::Red);
        break;

    case 1:
        this->enemy.setSize(Vector2f(40.f, 40.f));
        this->enemy.setFillColor(Color::Transparent);
        break;

    case 2:
        this->enemy.setSize(Vector2f(50.f, 50.f));
        this->enemy.setFillColor(Color::Magenta);
        break;


    case 3:
        this->enemy.setSize(Vector2f(80.f, 80.f));
        this->enemy.setFillColor(Color::Cyan);
        break;


    case 4:
        this->enemy.setSize(Vector2f(90.f, 90.f));
        this->enemy.setFillColor(Color::Yellow);
        break;
    default:
    
        this->enemy.setSize(Vector2f(120.f, 120.f));
        this->enemy.setFillColor(Color::Green);
        break;
        


    }

    
    
    // static cast turns a value into a float. (rand) function only takes int so were turning data into int putting it in rand and turning them in float 

   // this->enemy.setFillColor(Color::Green);


    // spawn the enemy
    this->enemies.push_back(this->enemy);

    // remove enemies when off screen end of screen

}

void Game::pollEvents()
{


    while (this->window->pollEvent(this->ev)) // save whatever is input (keyboard or mouse) into ev.
    {
        switch (this->ev.type) // what type of input is it
        {

        case Event::Closed: // first state that when closed, it is closed
            this->window->close();
            break;
        case Event::KeyPressed: // and then mention what key to close with
            if (this->ev.key.code == Keyboard::Escape)
                this->window->close();
            break;

        }


    }

}

void Game::updateMousePositions()
{
    // void return void
    // updates the mouse positions
    // updates the window mouse position relative to window <vector 2i>

    this->mousePosWindow = Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

}

void Game::updateEnemies()
    /*
    updates the enemy spawn timer and spawns enemies when the total amount of enemies is smaller than the max.
    
    moves the enemies downwards.
    
    removes the enemies at the edge of the screen  // left to do
    */

{       // updating the timer for enemy spawning
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {

            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;

    }
    // move and update enemiues
    

    //for (auto& e : this->enemies)
    for (int i =0; i<this->enemies.size(); i++)
    {

        bool deleted = false; // createdd a bool so only delete once in the loop
        //e.move(0.f, 3.f);
        this->enemies[i].move(0.f, 5.f);

        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            
            this->enemies.erase(this->enemies.begin() + i); // checking if they are below the screen
            //use points
            this->health -= 3;
            std::cout << "health: " << this->health << "\n";
            

        }



        


    }

    //check if clicked upon attacking/;/
    


    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {

                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) //within screen?
                {
                    



                    // gain points
                    if (this->enemies[i].getFillColor() == Color::Magenta)
                        this->points += 2;
                        this->health += 0;
                    
                    if (this->enemies[i].getFillColor() == Color::Yellow) 
                        this->points += 4;
                        this->health += 0;
                    

                    if (this->enemies[i].getFillColor() == Color::Cyan)
                        this->points += 5;
                        this->health += 1;

                    if (this->enemies[i].getFillColor() == Color::Red)
                        this->points += 10;
                        this->health += 2;

                    if (this->enemies[i].getFillColor() == Color::Transparent)
                        this->points += 12;
                        this->health += 2;

                    std::cout << "points: " << this->points << "\n";



                    // delete the loop
                    deleted = true;  // createdd a bool so only delete once in the loop
                    this->enemies.erase(this->enemies.begin() + i);
                }

            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }

    /*
    // if the enemy is past the bottom of the screen
    if (this->enemies[i].getPosition().y > this->window->getSize().y)
    {
        deleted = true;

        //use points
        

    }

    // final delete enemy
    if (deleted) {
        

        */
}

void Game::renderEnemies(RenderTarget& target)
{
    // rendering the enemies
    for (auto& e : this->enemies)
    {
        target.draw(e);

    }
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Points: " << this->points<<"\n" << "Health: "<<this->health << "\n";

    this->uiText.setString(ss.str());
}

void Game::renderText(RenderTarget& target)
{
    target.draw(this->uiText);

}

void Game::update() // updating the game after every input and stuff
{

    this->pollEvents();
    if (this->endGame == false)
    {
        this->updateMousePositions();
        this->updateText();

        this->updateEnemies();
    }

    if (this->health <= 0) {
        
        this->endGame = true;
    }
    /*

    //update mouse position

    //relative to screen
    std::cout << "Mouse Pos of Screen: " << Mouse::getPosition().x << " " << Mouse::getPosition().y << "\n";

    //relative to window
    std::cout << "Mouse Pos of window: "
        << Mouse::getPosition(*this->window).x << " " << Mouse::getPosition(*this->window).y << "\n";
        */

}

void Game::render() // rendering the things (seeing stuff) (visual representation)
{

    /*
    * 
    return void 
     
    clear old frame
    render objects
    display frame in window


    render game objects
    */

    this->window->clear();

    // draw game objects

    this->renderEnemies(*this->window);

    this->renderText(*this->window);
    
    //this->window->display();
    this->window->display(); 
}


// Functions here
