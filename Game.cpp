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

void Game::innitWindow()
{
	this->videomode.height = 830;
	this->videomode.width = 1103;
	this->window = new RenderWindow(this->videomode, "Test game", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::innitFonts()
{
	this->font.loadFromFile("Fonts/FC SaveSpace Italic ver 1.01.ttf");
}

void Game::innitText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(Color::White);
	this->uiText.setString("NONE");
}

void Game::innitEnemy()
{
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(Vector2f(100.f, 100.f));
	this->enemy.setFillColor(Color::Blue);
	/*this->enemy.setOutlineColor(Color::Yellow);
	this->enemy.setOutlineThickness(1.f);*/
}

//public
Game::Game()
{
	this->initVariables();
	this->innitWindow();
	this->innitEnemy();
	this->innitFonts();
	this->innitText();
}

Game::~Game()
{
	delete this->window;
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

void Game::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		default:
			break;
		}
	}
}


void Game::updateMousePosition()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	stringstream ss;
	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->health;
	this->uiText.setString(ss.str());
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
	this->pollEvent();

	if (this->endGame == false)
	{
		//this->updateMousePosition();
		//this->updateText();
		//this->updateEnemies();
		this->player.update(this->window, deltaTime);
	}

	if (this->health <= 0)
	{
		this->endGame = true;
	}

}


void Game::renderText(RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::renderEnemies(RenderTarget& target)
{
	for (auto& e : this->enemies)
	{
		target.draw(e);
	}
}

void Game::render()
{
	this->window->clear();
	// draw game here
	//this->renderEnemies(*this->window);

	//this->renderText(*this->window);
	this->player.render(this->window);

	this->window->display();
}
