#include "InputHelper.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>

bool InputHelper::IsMousePressed(MouseButton button)
{
	return sf::Mouse::isButtonPressed((sf::Mouse::Button)button);
}

bool InputHelper::IsKeyPressed(Key key)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key)key);
}

void InputHelper::GetCursorPosition(const Engine* engine, float& X, float& Y)
{
	const std::shared_ptr<Window>& window = engine->GetWindow();
	const sf::RenderWindow* renderWindow = window->GetWindow();

	sf::Vector2i position = sf::Mouse::getPosition(*renderWindow);

	float viewX, viewY = 0.f;
	window->GetViewPosition(viewX, viewY);
	
	X = position.x + viewX;
	Y = position.y + viewY;
}
