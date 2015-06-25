#include <SFML\Graphics.hpp>

#pragma once
namespace GR
{
	class Node : public sf::CircleShape
	{
	public:
		Node();
		~Node();
	private:
		bool dynamicFillColor;
		// calculates and sets fill color
		void updateFillColor();
		// updates origin coordinates
		void updateOrigin();
	public:
		// sets dynamic fill color
		void setDynamicFillColor(bool flag = true);
		// updates origin coordinates and fill color if set to true
		void update();
	};
}
