#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Graph.hpp"
#include <Windows.h>
#include <functional>

#ifdef _DEBUG
#include <iostream>
#endif

sf::Mutex graphMutex;
sf::RenderWindow *window;

void drawingLoop(GR::Graph *graph,bool* canStart)
{
	while (*canStart == false)
		Sleep(100);
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

void doTheWindow(bool* canStart)
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	window = new sf::RenderWindow(sf::VideoMode(400, 400), "Graph twerks!", sf::Style::Close|sf::Style::Titlebar, settings);
	window->setFramerateLimit(30);
	window->setActive(false);
	*canStart = true;
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}
	}

}

#ifdef _DEBUG
#include <iostream>
int main()
#else
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
#endif
{
	bool* canStart = new bool(false);
	sf::Thread windowThread(std::bind(&doTheWindow,canStart));
	windowThread.launch();
	GR::Graph* graph = new GR::Graph;
	sf::Thread drawingThread(std::bind(&drawingLoop, graph, canStart));
	drawingThread.launch();

	sf::Lock graphLock(graphMutex);
	GR::Node *node1 = graph->addNode(), *node2 = graph->addNode();
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
	GR::Edge* edge = graph->addConnection(node1, node2,false);
	graphLock.~Lock();

	return 0;
}

