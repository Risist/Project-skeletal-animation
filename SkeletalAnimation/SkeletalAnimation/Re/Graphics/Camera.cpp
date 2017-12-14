/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#include "Camera.h"

Camera cam;

Camera::Camera() : lastScale(1), darkness(1), alpha(1)
{
	setShakeBackFactors(0.9f, 0.9f, 0.9f, 0.9f);
}
void Camera::create(const sf::Vector2f& size, const sf::Vector2f& center)
{
	reset(sf::FloatRect(size, size));

	RenderTexture::create((unsigned int)size.x, (unsigned int)size.y);

	setCenter(center);
}

void Camera::draw(const sf::Drawable & s, const RenderStates & states)
{
	RenderTexture::draw(s,states);
}

void Camera::display(sf::RenderWindow& wnd, const RenderStates& states)
{
	/// temporary here, move to another function "update" when multiplay cameras will be used at once
	positionShakeResource.onUpdate(sf::seconds(1.f));
	rotationShakeResource.onUpdate(sf::seconds(1.f));

	auto v = getCenter();
	auto a = getRotation();
	setCenter(v + positionShakeResource.getValue());
	setRotation(a + rotationShakeResource.getValue());
	///

	RenderTexture::display();
	RenderTexture::setView(*this);

	sf::Sprite sprite(RenderTexture::getTexture());
	sprite.setColor(sf::Color(
		(sf::Uint8)(255 * darkness), 
		(sf::Uint8)(255 * darkness), 
		(sf::Uint8)(255 * darkness), 
		(sf::Uint8)(255 * alpha)));

	wnd.draw(sprite,states);
	RenderTexture::clear(background);

	///
	setCenter(v);
	setRotation(a);
	///
}