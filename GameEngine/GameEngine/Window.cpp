#include "Window.h"
#include <SFML/Graphics.hpp>

Window::Window(const int width, const int height, const std::string title, const bool fullscreen)
{
	sf::VideoMode mode;
	mode.height = height;
	mode.width = width;
	int style = fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	m_Window = new sf::RenderWindow(mode, title, style);
	m_GameView = new sf::View();
	m_UIView = new sf::View();

	const sf::View& currentView = m_Window->getView();
	m_GameView->setCenter(currentView.getCenter());
	m_GameView->setSize(currentView.getSize());
	m_UIView->setCenter(currentView.getCenter());
	m_UIView->setSize(currentView.getSize());
}

Window::~Window()
{
	delete m_UIView;
	delete m_GameView;
	delete m_Window;
}

bool Window::Update()
{
	sf::Event event;
	while (m_Window->pollEvent(event))
	{
		//close window if close event was send (clicking X on title bar)
		if (event.type == sf::Event::Closed)
		{
			return false;
		}
		else if (event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			//m_GameView->setSize(event.size.width, event.size.height);
		}
	}

	return true;
}

void Window::BeginDraw()
{
	m_Window->clear(sf::Color::Black);
}

void Window::EndDraw()
{
	m_Window->display();
}

void Window::Draw(const sf::Sprite* sprite)
{
	m_Window->setView(*m_GameView);
	m_Window->draw(*sprite);
}

void Window::Draw(const sf::Text* text)
{
	m_Window->setView(*m_UIView);
	m_Window->draw(*text);
}

void Window::Draw(const sf::VertexArray* vertexArray, const sf::Texture* texture)
{
	m_Window->setView(*m_GameView);
	m_Window->draw(*vertexArray, texture);
}

void Window::SetViewCenter(float X, float Y)
{
	m_GameView->setCenter(sf::Vector2f(X, Y));
}

void Window::GetViewPosition(float& X, float& Y)
{
	X = m_GameView->getCenter().x - m_Window->getSize().x / 2;
	Y = m_GameView->getCenter().y - m_Window->getSize().y / 2;
}