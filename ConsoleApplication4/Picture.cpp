#include "stdafx.h"
#include "Picture.h"
#include "Helpers.h"

void Picture::prepare(const sf::Vector2i* windowCenter, const sf::Vector2i* windowSize)
{
	sprite.setTexture(texture, true);

	setOriginCenter();
	setPositionWindowCenter(windowCenter);
	scale(windowSize);
}

void Picture::setOriginCenter()
{
	sprite.setOrigin(
		texture.getSize().x / 2,
		texture.getSize().y / 2
	);
}

void Picture::setPositionWindowCenter(const sf::Vector2i* windowCenter)
{
	sprite.setPosition(windowCenter->x, windowCenter->y);
}

void Picture::scale(const sf::Vector2i* windowSize)
{
	sf::Vector2i textureSize(texture.getSize());
	float factor = scaleToFit(&textureSize, windowSize);
	sprite.setScale(factor, factor);
}
