#include "Graph.hpp"

GR::Graph::Graph()
{
	this->nodes = new std::vector < Node* > ;
	this->edges = new std::vector < Edge* >;

}

GR::Graph::~Graph()
{}

// Adds new node
GR::Node* GR::Graph::addNode()
{
	this->nodes->push_back(new Node);
	return this->nodes->back();
}

// Adds existing Node
GR::Node* GR::Graph::addNode(GR::Node* node)
{
	this->nodes->push_back(node);
	return this->nodes->back();
}

// Adds connection between 2 Nodes
GR::Edge* GR::Graph::addConnection(GR::Node* begining, GR::Node* end)
{
	this->edges->push_back(new Edge(begining, end));
	return this->edges->back();
}

GR::Edge* GR::Graph::addConnection(Node* begining, Node* end, bool Directed)
{
	this->edges->push_back(new Edge(begining, end,Directed));
	return this->edges->back();
}

void GR::Graph::update()
{
	// Update nodes
	for (unsigned int i = 0; i < this->nodes->size(); i++)
	{
		(*(this->nodes))[i]->update();
	}
	// Update edges
	for (unsigned int i = 0; i < this->edges->size(); i++)
	{
		(*(this->edges))[i]->update();
	}
}

void GR::Graph::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw edges
	for (unsigned int i = 0; i < this->edges->size(); i++)
	{
		target.draw(*(*(this->edges))[i], states);
	}
	//Draw nodes
	for (unsigned int i = 0; i < this->nodes->size(); i++)
	{
		target.draw(*(*(this->nodes))[i], states);
	}
}