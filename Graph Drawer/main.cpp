//This is a sample demo program which uses the library.
//It is not a part of library

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Graph.hpp"
#include <Windows.h>
#include <functional>
#include <math.h>

#ifdef _DEBUG
#include <iostream>
#endif

#define PI 3.14159265358979323846f

sf::Mutex graphMutex;
sf::Mutex dataMutex;
sf::RenderWindow *window;

// Draws the graph to the window
void drawingLoop(GR::Graph *graph,bool* canStart)
{
	while (true)
	{
		sf::Lock lock(dataMutex);
		if (*canStart == true)
		{
			lock.~Lock();
			break;
		}
		lock.~Lock();
		Sleep(100);
	}
#ifdef _DEBUG
	int frames = 0;
	sf::Clock clock;
#endif
	while (window->isOpen())
	{
		window->clear(sf::Color::White);
		sf::Lock graphLock(graphMutex);
		graph->update();
		window->draw(*graph);
		graphLock.~Lock();
		window->display();
#ifdef _DEBUG
		frames++;
		sf::Time time = clock.getElapsedTime();
		if (time>sf::seconds(1))
		{
			std::cerr << frames << "/" << time.asSeconds() <<" fps"<< std::endl;
			frames = 0;
			clock.restart();
		}
#endif
	}
}

// Copes with starting window and it's events 
void doTheWindow(bool* canStart,bool* shutdown)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	window = new sf::RenderWindow(sf::VideoMode(400, 400), "Graph twerks!", sf::Style::Close|sf::Style::Titlebar, settings);
	window->setFramerateLimit(30);
	window->setActive(false);
	sf::Lock lock(dataMutex);
	*canStart = true;
	lock.~Lock();
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				sf::Lock lock(dataMutex);
				*shutdown = true;
				lock.~Lock();
				return;
			}
		}
	}

}

// Sets up a predifined graph 
void setupGraph(GR::Graph *graph)
{
	sf::Lock graphLock(graphMutex);

	GR::Node *node1 = graph->addNode(),
		*node2 = graph->addNode(),
		*node3 = graph->addNode(),
		*node4 = graph->addNode(),
		*node5 = graph->addNode(),
		*node6 = graph->addNode();

	node1->setPosition(70, 10);
	node1->setDynamicFillColor(true);
	node1->setOutlineColor(sf::Color::Red);
	node1->setRadius(2);
	node1->setOutlineThickness(1.0f);

	node2->setPosition(170, 40);
	node2->setDynamicFillColor(true);
	node2->setOutlineColor(sf::Color::Green);
	node2->setRadius(2);
	node2->setOutlineThickness(1.0f);

	node3->setPosition(230, 40);
	node3->setDynamicFillColor(true);
	node3->setOutlineColor(sf::Color::Blue);
	node3->setRadius(10);
	node3->setOutlineThickness(3.0f);

	node4->setPosition(10, 100);
	node4->setDynamicFillColor(true);
	node4->setOutlineColor(sf::Color::Black);
	node4->setRadius(4);
	node4->setOutlineThickness(1.0f);

	node5->setPosition(200, 300);
	node5->setDynamicFillColor(true);
	node5->setOutlineColor(sf::Color(255, 165, 0));
	node5->setRadius(20);
	node5->setOutlineThickness(1.0f);

	node6->setPosition(200, 390);
	node6->setDynamicFillColor(true);
	node6->setOutlineColor(sf::Color(150,75,0));
	node6->setRadius(5);
	node6->setOutlineThickness(1.0f);

	graph->addConnection(node1, node2, true);
	graph->addConnection(node1, node3, false);
	graph->addConnection(node1, node4, false);
	graph->addConnection(node1, node5, true);
	graph->addConnection(node1, node6, true);
	graph->addConnection(node2, node3, false);
	graph->addConnection(node2, node4, true);
	graph->addConnection(node2, node5, false);
	graph->addConnection(node2, node6, true);
	graph->addConnection(node4, node3, true);
	graph->addConnection(node3, node5, true);
	graph->addConnection(node3, node6, true);
	graph->addConnection(node4, node5, false);
	graph->addConnection(node4, node6, true);
	graph->addConnection(node5, node6, true);

	graphLock.~Lock();
}

// moveNode1-5 moves nodes1-5 around a predefined track
void moveNode1(GR::Node* node,int stepTick)
{
	const sf::Int32 stepCount = 90;
	sf::Lock graphLock(graphMutex);
	if (stepTick % stepCount < 30)
		node->move(1.f, 0.f);
	else if (stepTick % stepCount < 60)
		node->move(0.f, 1.f);
	else if (stepTick % stepCount < 90)
		node->move(-1.f, -1.f);
	graphLock.~Lock();
}
void moveNode2(GR::Node* node, int stepTick)
{
	const sf::Int32 stepCount = 90;
	sf::Lock graphLock(graphMutex);
	if (stepTick % stepCount < 30)
		node->move(-1.f, 0.f);
	else if (stepTick % stepCount < 60)
		node->move(0.f, -1.f);
	else if (stepTick % stepCount < 90)
		node->move(1.f, 1.f);
	graphLock.~Lock();
}
void moveNode3(GR::Node* node, int stepTick)
{
	const sf::Int32 stepCount = 90;
	sf::Lock graphLock(graphMutex);
	if (stepTick % stepCount < 15)
		node->move(1.f, 0.f);
	else if (stepTick % stepCount < 30)
		node->move(2.f, 1.f);
	else if (stepTick % stepCount < 45)
		node->move(-1.f, 0.f);
	else if (stepTick % stepCount < 60)
		node->move(0.f, -1.f);
	else if (stepTick % stepCount < 75)
		node->move(-1.f, 0.f);
	else if (stepTick % stepCount < 90)
		node->move(-1.f, 0.f);
	graphLock.~Lock();
}
void moveNode4(GR::Node* node, int stepTick)
{
	const sf::Int32 stepCount = 90;
	sf::Lock graphLock(graphMutex);
	if (stepTick % stepCount < 30)
		node->move(1.f, 0.f);
	else if (stepTick % stepCount < 60)
		node->move(0.f, 1.f);
	else if (stepTick % stepCount < 90)
		node->move(-1.f, -1.f);
	graphLock.~Lock();
}
void moveNode5(GR::Node* node, int stepTick)
{
	const sf::Int32 stepCount = 180;
	sf::Lock graphLock(graphMutex);
	if (stepTick % stepCount < 20)
		node->move(-4.f, -12.f);
	else if (stepTick % stepCount < 180)
		node->move(.5f, 1.5f);
	graphLock.~Lock();
}
void moveNode6(GR::Node* node, int stepTick)
{
	const sf::Int32 stepCount = 600;
	const float radius = 190;
	sf::Vector2f prevPos,nextPos;
	
	prevPos.x = radius * sin(float(stepTick%stepCount) / float(stepCount) * 2.f * PI);
	prevPos.y = radius * cos(float(stepTick%stepCount) / float(stepCount) * 2.f * PI);
	
	nextPos.x = radius * sin(float((stepTick + 1) % stepCount) / float(stepCount) * 2.f * PI);
	nextPos.y = radius * cos(float((stepTick + 1) % stepCount) / float(stepCount) * 2.f * PI);
	
	sf::Lock graphLock(graphMutex);
	node->move(nextPos - prevPos);
	graphLock.~Lock();
}

// Runs moveNode1-5 in a loop
void moveNodes(GR::Graph* graph,bool* canStart,bool* shutdown)
{
	while (true)
	{
		sf::Lock lock(dataMutex);
		if (*canStart == true)
		{
			lock.~Lock();
			break;
		}
		lock.~Lock();
		Sleep(100);
	}
	int stepTick = 0;
	while (true)
	{	
		sf::Lock lock(dataMutex);
		if (*shutdown == true)
		{
			lock.~Lock();
			return;
		}
		lock.~Lock();
		moveNode1(graph->getNode(0), stepTick);
		moveNode2(graph->getNode(1), stepTick);
		moveNode3(graph->getNode(2), stepTick);
		moveNode4(graph->getNode(3), stepTick);
		moveNode5(graph->getNode(4), stepTick);
		moveNode6(graph->getNode(5), stepTick);
		Sleep(20);
		stepTick++;
	}
}


// main function
#ifdef _DEBUG
#include <iostream>
int main()
#else
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
#endif
{
	bool* canStart = new bool(false);
	bool* shutdown = new bool(false);
	sf::Thread windowThread(std::bind(&doTheWindow,canStart,shutdown));
	windowThread.launch();
	GR::Graph* graph = new GR::Graph;
	sf::Thread drawingThread(std::bind(&drawingLoop, graph, canStart));
	drawingThread.launch();

	setupGraph(graph);
	sf::Thread nodeMovingThread(std::bind(moveNodes, graph, canStart, shutdown));
	nodeMovingThread.launch();
	
	drawingThread.wait();
	windowThread.wait();
	nodeMovingThread.wait();

	return 0;
}

