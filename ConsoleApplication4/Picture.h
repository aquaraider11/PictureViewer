#pragma once
#include "stdafx.h"

struct Picture
{
	sf::Texture texture;
	sf::Sprite sprite;
	void prepare(const sf::Vector2i*, const sf::Vector2i*);

private:
	void setOriginCenter();
	void setPositionWindowCenter(const sf::Vector2i*);
	void scale(const sf::Vector2i*);
};
