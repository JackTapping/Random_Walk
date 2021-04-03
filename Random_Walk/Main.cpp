#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>

struct Pixel
{
	int x_location = 0;
	int y_location = 0;

	int red = 255;
	int green = 255;
	int blue = 255;
};

void MovePixel(Pixel &pixel, sf::Image &image, int hight, int width)
{
	bool atEdgeofScreen = true;

	while (atEdgeofScreen)
	{
		if (rand() % 2 == 0)
		{
			pixel.x_location++;
		}
		else
		{
			pixel.x_location--;
		}

		if (pixel.x_location <= 0 || pixel.x_location >= width)
		{
			atEdgeofScreen = true;

		}
		else
		{
			atEdgeofScreen = false;
		}

	}
	
	atEdgeofScreen = true;
	while (atEdgeofScreen)
	{
		if (rand() % 2 == 0)
		{
			pixel.y_location++;
		}
		else
		{
			pixel.y_location--;
		}

		if (pixel.y_location <= 0 || pixel.y_location >= hight)
		{
			atEdgeofScreen = true;
		}
		else
		{
			atEdgeofScreen = false;
		}

	}
	
	image.setPixel(pixel.x_location, pixel.y_location, sf::Color(pixel.red, pixel.green, pixel.blue));
}
void ChangeColor(int &firstColor, int &secondColor, int &thirdColor)
{
	if(firstColor != 0)
	{
		firstColor--;
	}
	else if(secondColor != 0)
	{
		secondColor--;
	}
	else
	{
		thirdColor--;
	}
}


int main()
{
	srand(time(NULL));

	int hight = 800;
	int width = 600;
	int timer = 0;

	sf::RenderWindow window(sf::VideoMode(hight, width), "Random Walk");
	window.setFramerateLimit(144);

	sf::Event ev;

	sf::Image image;
	image.create(width, hight);

	sf::Texture texture;
	sf::Sprite sprite;

	Pixel redPixel;
	Pixel bluePixel;
	Pixel greenPixel;

	redPixel.x_location = width / 2;
	redPixel.y_location = hight / 2;

	std::cout << hight << " || " << redPixel.y_location << "\n";
	std::cout << width << " || " << redPixel.x_location << "\n";

	greenPixel.x_location = width / 2;
	greenPixel.y_location = hight / 2;

	bluePixel.x_location = width / 2;
	bluePixel.y_location = hight / 2;

	//Main Loop 
	while (window.isOpen())
	{
		//polling
		while (window.pollEvent(ev))
		{
			if(ev.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if(greenPixel.green != 20)
		{
			MovePixel(redPixel, image, hight, width);
			MovePixel(greenPixel, image, hight, width);
			MovePixel(bluePixel, image, hight, width);
			texture.loadFromImage(image);
			sprite.setTexture(texture);

			window.clear();

			window.draw(sprite);

			window.display();

			if (timer > 500)
			{
				ChangeColor(redPixel.blue, redPixel.green, redPixel.red);
				ChangeColor(greenPixel.red, greenPixel.blue, greenPixel.green);
				ChangeColor(bluePixel.green, bluePixel.red, bluePixel.blue);

				timer = 0;
			}
			timer++;

		}
		
	}
	return 0;
}