#include "Ball.h"

Ball::Ball(float x, float y, float radius, sf::Color color)
{
	shape = sf::CircleShape(radius);
	shape.setFillColor(color);
	shape.setOrigin(radius, radius);
	shape.setPosition(x, y);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::Black);
}


Ball::~Ball()
{
}

void Ball::SetPosition(float x, float y)
{
	shape.setPosition(sf::Vector2f(x,y));
}

void Ball::SetX(float x)
{
	shape.setPosition(sf::Vector2f(x, shape.getPosition().y));
}

void Ball::SetY(float y)
{
	shape.setPosition(sf::Vector2f(shape.getPosition().x, y));
}

void Ball::Translate(float x, float y)
{
	shape.setPosition(sf::Vector2f(shape.getPosition().x + x, shape.getPosition().y + y));
}