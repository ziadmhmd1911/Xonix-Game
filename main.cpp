#include<SFML/Graphics.hpp>
#include<iostream>
#include<time.h>

using namespace std;
using namespace sf;

const int width = 40;
const int height = 25;
const int res = 18;

int graph[width][height];

bool game = true;

float timer = 0;
float delay = 0.07;

struct sPlayer {
	int x = width / 2;
	int y = 0;
	int dx = 0;
	int dy = 0;

	Texture t1;
};
sPlayer p;

void motion() {
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		p.dx = 0;
		p.dy = -1;
	}if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		p.dx = 0;
		p.dy = 1;
	}if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		p.dx = 1;
		p.dy = 0;
	}if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		p.dx = -1;
		p.dy = 0;
	}
}

int main() {

	RenderWindow window(VideoMode(width * res, height * res), "Xonix");

	p.t1.loadFromFile("images/tiles.png");
	Sprite player(p.t1);

	while (game)
	{

		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				if (i == 0 || j == 0 || i == width - 1 || j == height - 1)
				{
					graph[i][j] = 1;
				}
			}
		}

		Clock clock;
		while (window.isOpen())
		{
			float time = clock.getElapsedTime().asSeconds();
			clock.restart();
			timer += time;

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == event.Closed) {
					window.close();
				}
			}

			motion();
			if (timer > delay)
			{
				p.x += p.dx;
				p.y += p.dy;

				if (p.x < 0)
				{
					p.x = 0;
				}
				if (p.x > width - 1)
				{
					p.x = width - 1;
				}
				if (p.y < 0)
				{
					p.y = 0;
				}
				if (p.y > height - 1)
				{
					p.y = height - 1;
				}
				if (graph[p.x][p.y] == 2)
				{
					game = false;
				}
				if (graph[p.x][p.y] == 0)
				{
					graph[p.x][p.y] = 2;
				}

				timer = 0;
			}

			window.clear();

			for (int i = 0; i < width; i++)
			{
				for (int j = 0; j < height; j++)
				{
					if (graph[i][j] == 0)
					{
						continue;
					}if (graph[i][j] == 1)
					{
						player.setTextureRect(IntRect(72, 0, res, res));
					}
					player.setPosition(i * res, j * res);
					window.draw(player);
				}
			}

			player.setTextureRect(IntRect(36, 0, res, res));
			player.setPosition(p.x * res, p.y * res);
			window.draw(player);

			window.display();
		}
	}

	return 0;
}
