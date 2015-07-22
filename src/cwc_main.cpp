#include "clickwise.h"
#include "clocktalk.h"
#include <iostream>
#include <string>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main(int argc, void *argv)
{
	CtSymbols symbols;
	CwImage render(180,180);
	std::string buffer;
	std::cout << "Enter text for translation (\\q to quit)" << std::endl << ">";
	while (std::cin >> buffer, buffer != "\\q")
	{
		CtSymbolStream stream(&symbols);
		stream.Write(buffer.c_str());
		render.DrawStream(&stream);
		sf::RenderWindow window(sf::VideoMode(render.GetWidth(), render.GetHeight()), buffer);
		sf::Texture texture;
		unsigned char *img_buf = render.GetRGBAImage();
		if (!texture.loadFromMemory(img_buf, render.GetSize(), sf::IntRect(0, 0, render.GetWidth(), render.GetHeight())))
		{
			return EXIT_FAILURE;
		}
		delete[] img_buf;
		sf::Sprite sprite(texture);

		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear();
			window.draw(sprite);
		}
	}
}