#include "Edge.hpp"
#include <cmath>

#ifdef _DEBUG
#include <iostream>
#endif

GR::Edge::Edge()
{
	this->begining = NULL;
	this->end = NULL;
	this->directed = true;
}

GR::Edge::Edge(GR::Node *Beginign, GR::Node *End)
{
	this->directed = true;
	this->begining = Beginign;
	this->end = End;
}

GR::Edge::Edge(GR::Node *Begining, GR::Node *End, bool directed)
{
	this->begining = Begining;
	this->end = End;
	this->directed = directed;
}

GR::Edge::~Edge()
{
	//delete this->begining;
	//delete this->end;
	//delete[] this->lineVertex;
}

//Sets connection
void GR::Edge::setConnection(GR::Node *Begining, GR::Node *End, bool Directed)
{
	this->directed = Directed;
	delete this->begining;
	this->begining = Begining;
	delete this->end;
	this->end = End;
}

// Sets if edge is directed
void GR::Edge::setIfDirected(bool flag)
{
	directed = flag;
}

// Draw edge
void GR::Edge::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->lineVertex,2,sf::Lines);
	if (this->directed)
		target.draw(this->arrowVertex, 3, sf::Triangles);
}

// Updates representation /Must be called before drawing to draw edge correctly
void GR::Edge::update()
{
	/*
	A - begining
	B - end
	P - start of line at begining node
	K - end of line at end node (also peek of arrow)
	T - begining of arrow
	S1, S2 - Peeks of arrow
	*/
	//pitagoras
	auto getDist = [](sf::Vector2f A, sf::Vector2f B){return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y)); };
	float procentage = 0.8f, //procentage of line covered by arrow
		maxDist = 5, // max arrow length
		AB = getDist(this->begining->getPosition(), this->end->getPosition()); // distance between centers of nodes 
	sf::Vector2f P(this->begining->getRadius() / AB*this->end->getPosition().x + (1 - this->begining->getRadius() / AB)*this->begining->getPosition().x,
				   this->begining->getRadius() / AB*this->end->getPosition().y + (1 - this->begining->getRadius() / AB)*this->begining->getPosition().y),
		K((1 - this->end->getRadius() / AB)*this->end->getPosition().x + (this->end->getRadius() / AB)*this->begining->getPosition().x,
		  (1 - this->end->getRadius() / AB)*this->end->getPosition().y + (this->end->getRadius() / AB)*this->begining->getPosition().y);
	float PK=getDist(P,K),
		l = std::min(getDist(P, K)*procentage, maxDist); //length of arrow
	sf::Vector2f T((1 - l / PK)*K.x + l / PK*P.x, (1 - l / PK)*K.y + l / PK*P.y),
		S1(T.x-K.y+T.y,T.y+K.x-T.x), 
		S2(T.x+K.y-T.y,T.y-K.x+T.x);

	sf::Color arrowColor((sf::Uint8)std::max((sf::Uint8)(this->begining->getOutlineColor().r + (int)((float)((float)this->begining->getOutlineColor().r - (float)this->end->getOutlineColor().r) *(l / PK))), (sf::Uint8)0),
		(sf::Uint8)std::max((sf::Uint8)(this->begining->getOutlineColor().g + (int)((float)((float)this->begining->getOutlineColor().g - (float)this->end->getOutlineColor().g) *(l / PK))), (sf::Uint8)0),
		(sf::Uint8)std::max((sf::Uint8)(this->begining->getOutlineColor().b + (int)((float)((float)this->begining->getOutlineColor().b - (float)this->end->getOutlineColor().b) *(l / PK))), (sf::Uint8)0));

	this->lineVertex[0] = sf::Vertex(P,this->begining->getOutlineColor());
	this->lineVertex[1] = sf::Vertex(K,this->end->getOutlineColor());

	this->arrowVertex[0] = sf::Vertex(K, this->end->getOutlineColor());
	this->arrowVertex[1] = sf::Vertex(S1, arrowColor);
	this->arrowVertex[2] = sf::Vertex(S2, arrowColor);
}

// Changes Begining
void GR::Edge::setBegining(GR::Node* Begining)
{
	this->begining = Begining;
}

// Chnages End
void GR::Edge::setEnd(GR::Node* End)
{
	this->end = End;
}