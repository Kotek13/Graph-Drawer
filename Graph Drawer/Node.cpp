#ifdef _DEBUG
#include <iostream>
#endif

#include "Node.hpp"
#include <SFML\Graphics\CircleShape.hpp>

GR::Node::Node()
{
	this->setPosition(0, 0);
	this->setRadius(2);
	this->dynamicFillColor = false;
	this->setFillColor(sf::Color::White);
	this->setOutlineThickness(1);
	this->setOutlineColor(sf::Color::Black);
	this->update();
}

GR::Node::~Node()
{

}


// calculates and sets fill color
void GR::Node::updateFillColor()
{
	if (this->dynamicFillColor != true)
		return;
	Node node(*this);
	float multiplier=0.8f;
	sf::Color color = this->getOutlineColor();
	color.r = (sf::Uint8)((float)(255 - color.r) * multiplier + (float)color.r);
	color.g = (sf::Uint8)((float)(255 - color.g) * multiplier + (float)color.g);
	color.b = (sf::Uint8)((float)(255 - color.b) * multiplier + (float)color.b);
	this->setFillColor(color);
}

// sets dynamic fill color
void GR::Node::setDynamicFillColor(bool flag)
{
	this->dynamicFillColor = flag;
}

// updates origin coordinates
void GR::Node::updateOrigin()
{
	this->setOrigin(sf::Vector2f(this->getRadius(),this->getRadius()));
}

// updates origin coordinates and fill color if set to true
void GR::Node::update()
{
	this->updateFillColor();
	this->updateOrigin();
}