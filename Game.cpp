#include "Game.h"
//private
void Game::initVariables()
{
	this->window = nullptr;

	this->endGame = false;
	this->points = 0;
	this->enemySpawnTimerMax = 20.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
	this->health = 10;
}

void Game::innitFonts()
{
	if (!this->font.loadFromFile("SMpixxo.ttf"))
	{
		std::cout << "ERROR::GAME::INITFONTS::COULD NOT LOAD SMpixxo.ttf" << "\n";
	}
}


void Game::innitText()
{
	//Gui texe innit
	this->guiText.setFont(this->font);
	this->guiText.setCharacterSize(48);
	this->guiText.setFillColor(Color::White);
	this->guiText.setPosition(20, 20);
}

void Game::innitEnemy()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(Vector2f(100.f, 100.f));
	this->enemy.setFillColor(Color::Blue);
	/*this->enemy.setOutlineColor(Color::Yellow);
	this->enemy.setOutlineThickness(1.f);*/
}

void Game::innitBg()
{
	texture.loadFromFile("top down.png");
	bg.setTexture(texture);
	texture2.loadFromFile("wallF.png");
	bg2.setTexture(texture2);
}

//public
Game::Game(RenderWindow* window)
{
	this->initVariables();
	this->window = window;
	this->innitEnemy();
	this->innitFonts();
	this->innitText();
	this->innitBg();
	
}
int Game::getPoint()
	{
		return this->points;
	}
Game::~Game()
{
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

void Game::spawnEnemy()
{
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	int type = rand() % 5;
	switch (type)
	{
	case 0:
		this->enemy.setFillColor(Color::Magenta);
		this->enemy.setSize(Vector2f(10.f, 10.f));
		break;
	case 1:
		this->enemy.setFillColor(Color::Yellow);
		this->enemy.setSize(Vector2f(30.f, 30.f));
		break;
	case 2:
		this->enemy.setFillColor(Color::Cyan);
		this->enemy.setSize(Vector2f(50.f, 50.f));
		break;
	case 3:
		this->enemy.setFillColor(Color::Blue);
		this->enemy.setSize(Vector2f(70.f, 70.f));
		break;
	case 4:
		this->enemy.setFillColor(Color::Red);
		this->enemy.setSize(Vector2f(90.f, 90.f));
		break;
	default:
		this->enemy.setFillColor(Color::Green);
		this->enemy.setSize(Vector2f(100.f, 100.f));
		break;
	}

	this->enemies.push_back(this->enemy);
}

void Game::updateMousePosition()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

/*void Game::updateText()
{
	stringstream ss;
	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health;
	this->guiText.setString(ss.str());
}
*/
void Game::updateGui()
{
	std::stringstream ss;
	ss <<" Points: " << this->points;
	this->guiText.setString(ss.str());
	/*this->guiText.setString("Point: ");*/
}

void Game::setPoint(int point) 
{
	this->points = point;
}

void Game::updateEnemies()
{
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}
	for (int i = 0; i < this->enemies.size(); i++)
	{
		this->enemies[i].move(0.f, 5.f);
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
		}
	}

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (int i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					if (this->enemies[i].getFillColor() == Color::Magenta)
						this->points += 10;
					else if (this->enemies[i].getFillColor() == Color::Yellow)
						this->points += 7;
					else if (this->enemies[i].getFillColor() == Color::Cyan)
						this->points += 5;
					else if (this->enemies[i].getFillColor() == Color::Blue)
						this->points += 3;
					else if (this->enemies[i].getFillColor() == Color::Red)
						this->points += 1;
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::updateMap()
{

}

void Game::update()
{
	deltaTime = clock.restart().asSeconds();

	//this->updateMousePosition();
	//this->updateText();
	this->player.update(this->window, deltaTime);

	this->collision();
	//this->updateCollision();
	this->updateGui();
}

void Game::collision()
{
	if (player.getPosition().y + player.getGlobalBounds().height > window->getSize().y)
	{
		player.resetVelocityY();
		player.setPosition(player.getPosition().x,window->getSize().y - player.getGlobalBounds().height);
	}

	//Coin
	for (int i = 0; i < player.coins.size(); i++)
	{	
		if(player.coins[i].decay <= 0) {

			player.coins.erase(player.coins.begin() + i);
			break;
		}
		if (player.getGlobalBounds().intersects(player.coins[i].getGlobalBounds()))
		{
			//cout << coin.size()<<endl;
			player.coins.erase(player.coins.begin() + i);
			this->points=points+10;
			break;
		}
	}
}

/*void Game::updateCollision()
{
	this->points++;
}*/


void Game::renderText(RenderTarget& target)
{
	target.draw(this->guiText);
}

void Game::renderEnemies(RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::renderGui(RenderTarget& target)
{
	target.draw(this->guiText);
}

void Game::render()
{
	this->renderEnemies(*this->window);
	this->window->draw(bg);
	this->player.render(this->window);
	this->window->draw(bg2);
	this->renderText(*this->window);
	this->renderGui(*this->window);
}
