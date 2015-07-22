#include "clickwise.h"
#include "clocktalk.h"
#include <iostream>
#include <string>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main(int argc, void *argv)
{
	CtSymbols symbols;
	CwImage *render = new CwPng(180,180);
	std::string buffer;
	sf::Texture texture;
	std::cout << "Enter text for translation (\\q to quit)" << std::endl << ">";
	char buf[128];
	while (std::cin.getline(buf, 128), buffer = std::string(buf), buffer != "")
	{
		CtSymbolStream stream(&symbols);
		stream.Write(buffer.c_str());
		render->DrawStream(&stream);
		unsigned int w = render->GetWidth();
		unsigned int h = render->GetHeight();
		sf::RenderWindow window(sf::VideoMode(w, h, 32), buffer.c_str());
		
		if (!texture.create(w, h))
		{
			return EXIT_FAILURE;
		}
		void *img_buf = (unsigned char*)render->GetEncodedImage();
		render->SaveToFile((buffer + ".png").c_str());
		texture.loadFromMemory(img_buf, render->GetSize() * 4);
		
		sf::Sprite sprite(texture);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear(sf::Color(128,128,128,255));
			window.draw(sprite);
			window.display();
		}
		delete[] img_buf;
	}
	return 0;
}