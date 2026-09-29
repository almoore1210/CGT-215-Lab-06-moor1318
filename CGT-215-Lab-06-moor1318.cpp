// CGT-215-Lab-06-moor1318.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp> 

using namespace sf; 
using namespace std; 

int main() {
	string background = "images1/backgrounds/winter.png";
	string foreground = "images1/characters/yoda.png";

	Texture backgroundTex;
	if (!backgroundTex.loadFromFile(background)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}

	Texture foregroundTex;
	if (!foregroundTex.loadFromFile(foreground)) {
		cout << "Couldn't Load Image" << endl;
		exit(1);
	}

	Image backgroundImage;
	backgroundImage = backgroundTex.copyToImage();

	Image foregroundImage;
	foregroundImage = foregroundTex.copyToImage();

	//go through each pixel
	Vector2u sz = foregroundImage.getSize();

	for (int y = 0; y < sz.y; y++) {
		for (int x = 0; x < sz.x; x++) {

			Color pixel = foregroundImage.getPixel(x, y);

			//if green, make it transparent
			if (pixel.g > 180 &&
				pixel.r < 80 &&
				pixel.b < 80) {

				pixel.a = 0;
				foregroundImage.setPixel(x, y, pixel);
			}
		}
	}

	//create sprites
	Sprite backgroundSprite;
	Texture backgroundTexture;
	backgroundTexture.loadFromImage(backgroundImage);
	backgroundSprite.setTexture(backgroundTexture);

	Sprite yodaSprite;
	Texture yodaTexture;
	yodaTexture.loadFromImage(foregroundImage);
	yodaSprite.setTexture(yodaTexture);

	//create a window
	RenderWindow window(VideoMode(1024, 768), "Here's the output");

	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		//winter backrgound first
		window.draw(backgroundSprite);

		//then yoda
		window.draw(yodaSprite);

		window.display();
	}

	return 0;
}
