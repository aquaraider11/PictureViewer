#include "stdafx.h"
#include "Helpers.h"
#include "Picture.h"
#include "FsHelpers.h"

namespace fs = std::experimental::filesystem;
bool ChangeHasHappened = false;


sf::Vector2i windowSize(1800, 900), windowCenter(windowSize / 2);
std::vector<Picture*> pictures;

void dataFetcherFunc(std::string input)
{
	std::string inputString = input;
	if (!fs::is_directory(inputString))
	{
		std::cout << inputString << " IS NOT DIR!!" << std::endl;
		inputString = getDirectory(inputString);
	}
	if (!fs::is_directory(inputString))
	{
		std::cout << inputString << " IS STILL NOT DIR!! exiting thread." << std::endl;
		return;
	}
	std::cout << "success, " << inputString << " is DIR" << std::endl;

	std::vector<std::string> files = getDirectoryContents(inputString);
	for (std::string file : files)
	{
		Picture* pic = new Picture();
		if (pic->texture.loadFromFile(file))
		{
			pic->texture.setSmooth(true);
			pic->prepare(&windowCenter, &windowSize);
			pictures.push_back(pic);
			ChangeHasHappened = true;
		}
	}

	std::cout << "All pictures processed, background thread stopped." << std::endl;
}

int main(int argc, char *argv[])
{
	int drawindex = 0;
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "Picture Viewer");
	window.setFramerateLimit(60);

	if (argc > 1)
	{
		std::string arg1 = argv[1];
		std::cout << argv[1] << std::endl;

		if (isImage(arg1))
		{
			std::thread dataFetcherThread(dataFetcherFunc, arg1);
			dataFetcherThread.detach();

			/*Picture* pic = new Picture();
			if (pic->texture.loadFromFile(arg1))
			{
				pic->texture.setSmooth(true);
				pic->prepare(&windowCenter, &windowSize);
				pictures.push_back(pic);
			}*/
		}

	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
				if (event.key.code == sf::Keyboard::A ||
					event.key.code == sf::Keyboard::Left)
					drawindex = changeIndex(drawindex, -1, pictures.size() - 1);
				else if (event.key.code == sf::Keyboard::D ||
					event.key.code == sf::Keyboard::Right)
					drawindex = changeIndex(drawindex, 1, pictures.size() - 1);
				
				ChangeHasHappened = true;
			}

			else if (event.type == sf::Event::Resized)
			{
				std::cout << "new width: " << event.size.width << std::endl;
				std::cout << "new height: " << event.size.height << std::endl;
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				windowSize = sf::Vector2i(event.size.width, event.size.height);
				windowCenter = windowSize / 2;
				window.setView(sf::View(visibleArea));

				// resize all pictures
				for (Picture* pic : pictures)
					pic->prepare(&windowCenter, &windowSize);

				ChangeHasHappened = true;
			}

		}
		if (ChangeHasHappened)
		{
			window.clear();
			window.draw(pictures[drawindex]->sprite);
			window.display();
			ChangeHasHappened = false;
		}
	}

	for (Picture* pic : pictures)
		delete pic;

	return 0;
}
