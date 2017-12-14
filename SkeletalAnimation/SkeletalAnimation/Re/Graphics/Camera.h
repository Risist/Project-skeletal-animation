/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#pragma once
#include <Re\Common\utility.h>
 
class Camera : public sf::View, public sf::RenderTexture
{
public:
	Camera();
	void create(const sf::Vector2f& size, const sf::Vector2f& center = sf::Vector2f());

	/// draw a shape onto camera
	void draw(const sf::Drawable& s, const RenderStates& states = sf::RenderStates::Default );

	/// display camera onto window
	void display(sf::RenderWindow& wnd, const RenderStates& states = RenderStates());
	
	/// set how much the view is scaled (sfml has no such a feature)
	void setScale(float32 s)
	{
		View::zoom(1 / lastScale);
		lastScale = s;
		View::zoom(lastScale);
	}
	/// get how much the view is scaled (sfml has no such a feature)
	float getScale()
	{
		return lastScale;
	}

	/// set brightness of camera [0,1]
	void setDarkness(float32 s)
	{
		assert(s >= 0.f && s <= 1.f);
		darkness = s;
	}
	/// add brightness of camera [-1,1]
	void addDarkness(float32 s)
	{
		darkness += s;
		darkness = clamp(darkness, 0.f, 1.f);
	}
	// get brightness of camera [0,1]
	float32 getDarkness()
	{
		return darkness;
	}

	/// set how much render is depended on previous frames [0,1]
	/// adds efect of "drunk" man  
	void setAlpha(float32 s)
	{
		assert(s >= 0.f && s <= 1.f);
		alpha = s;
	}
	/// add how much render is depended on previous frames [-1,1]
	/// adds efect of "drunk" man  
	void addAlpha(float32 s)
	{
		alpha += s;
		alpha = clamp(alpha, 0.f, 1.f);
	}
	/// get how much render is depended on previous frames [0,1]
	/// adds efect of "drunk" man  
	float32 getAlpha()
	{
		return alpha;
	}


	/// set color of background
	void setBackgroundColor(const Color& cl)
	{
		background = cl;
	}
	/// get color of background
	const Color& getBackgroundColor()
	{
		return background;
	}

public:
	/// overrided operators
	Angle getRotation() const { return Degree(View::getRotation()); }
	Vector2D getCenter() const { return sf::View::getCenter(); }

	void setRotation(Angle angle) { sf::View::setRotation(angle.asDegree()); }
	void setCenter(const Vector2D& s) { return sf::View::setCenter(s); }


public:
	/// camera shake
	/// supported versions: 
	///		push and back to the default
	///		rotate and back to the default

	void addPositionShake(Vector2D offsetForce)
	{
		positionShakeResource.addForce(offsetForce);
	}
	void addRotationShake(Angle angleForce)
	{
		rotationShakeResource.addForce(angleForce);
	}

	void setShakeBackFactors(float32 positionFactor, float32 positionForceFactor,
		float32 rotationFactor, float32 rotationForceFactor)
	{
		positionShakeResource.setResetValue( positionFactor);
		positionShakeResource.setResetForce(positionForceFactor);

		rotationShakeResource.setResetValue(rotationFactor);
		rotationShakeResource.setResetForce(rotationForceFactor);
	}


private:
	NewtonianResourceSimple<Vector2D> positionShakeResource;
	NewtonianResourceSimple<Angle> rotationShakeResource;
private:
	float32 darkness, ///< brightness of camera [0,1]
		alpha,		///< how much render is depended on previous frames [0,1]
		lastScale;	///< how much the view is scaled (sfml has no such a feature)


	
	// color using which the render texture will be cleared after displaying
	Color background;
};


extern Camera cam;