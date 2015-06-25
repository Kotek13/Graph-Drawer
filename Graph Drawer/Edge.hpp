#include "Node.hpp"
#include <SFML\Graphics.hpp>
#pragma once
namespace GR
{
	class Edge : public sf::Drawable
	{
	public:
		Edge();
		Edge(Node *Begining, Node *End);
		Edge(Node *Begining, Node *End, bool directed);
		~Edge();
	private:
		bool directed;
		Node *begining, *end;
		sf::Vertex lineVertex[2];
		sf::Vertex arrowVertex[3];

	public:
		void setConnection(Node *Begining, Node *End, bool Directed = true);
		// Sets if edge is directed
		void setIfDirected(bool flag = false);
		// Draw edge
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		// Updates representation /Must be called before drawing to draw edge correctly  
		void update();
		// Changes Begining
		void setBegining(Node* Begining);
		// Chnages End
		void setEnd(Node* End);
	};
}

/*TO DO:
	better arrow colors;
*/