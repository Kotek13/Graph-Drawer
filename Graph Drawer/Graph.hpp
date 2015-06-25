#include "Node.hpp"
#include "Edge.hpp"
#include <vector>
#pragma once

namespace GR
{
	class Graph : public sf::Drawable
	{
	public:
		Graph();

		~Graph();
	private:
		std::vector<Node*>* nodes;
		std::vector<Edge*>* edges;

	public:

		// Adds new Node
		Node* addNode();
		// Adds existing Node
		Node* addNode(Node* node);
		// Adds connection between 2 Nodes
		Edge* addConnection(Node* begining, Node* end);
		Edge* addConnection(Node* begining, Node* end,bool Directed);

		//void removeConnection(Edge*);
		void update();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};
}
