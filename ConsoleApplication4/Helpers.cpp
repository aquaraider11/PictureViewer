#include "stdafx.h"

float scaleToFit(const sf::Vector2i* input, const sf::Vector2i* target)
{
	float widthRatio = (float)target->x / input->x;
	float heightRatio = (float)target->y / input->y;

	return std::min(widthRatio, heightRatio);
}

int changeIndex(int index, int offset, int max)
{
	index += offset;

	if (index < 0)
		index = max;
	else if (index >= max)
		index = 0;

	return index;
}
