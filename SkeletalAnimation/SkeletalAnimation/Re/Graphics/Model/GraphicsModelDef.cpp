#include <Re\Graphics\Model\GraphicsModelDef.h>

namespace Graphics
{
	const ModelDef ModelDef::default(Vector2D(), Angle::zero, Color_f(255.f, 255.f, 255.f, 255.f),  Vector2D(1,1), Angle::zero );
	const ModelDef ModelDef::zero(Vector2D(), Angle::zero, Color_f(), Vector2D(), Angle::zero);

	ModelDef::ModelDef(const Vector2D & _position, Angle _rot, Color_f _color, const Vector2D & _scale, Angle _rotAround)
		: position(_position), rotation(_rot), color(_color), scale(_scale), mineRotation(_rotAround)
	{
	}

	
	ModelDef ModelDef::operator+(const ModelDef & other)  const
	{
		ModelDef def;
		def.position = position + other.position;
		def.rotation = rotation + other.rotation;
		def.mineRotation = mineRotation + other.mineRotation;
		def.scale = scale + other.scale;
		def.color = color + other.color;
		return def;
	}
	ModelDef ModelDef::operator-(const ModelDef & other) const
	{
		ModelDef def;
		def.position = position - other.position;
		def.rotation = rotation - other.rotation;
		def.mineRotation = mineRotation - other.mineRotation;
		def.scale = scale - other.scale;
		def.color = color - other.color;
		return def;
	}
	ModelDef ModelDef::operator*(float32 other) const
	{
		ModelDef def;
		def.position = position * other;
		def.rotation = rotation * other;
		def.mineRotation = mineRotation * other;
		def.scale = scale * other;
		def.color = color * other;
		return def;
	}
	ModelDef ModelDef::operator/(float32 other) const
	{
		assert(other != 0);
		ModelDef def;
		def.position = position / other;
		def.rotation = rotation / other;
		def.mineRotation = mineRotation / other;
		def.scale = scale / other;
		def.color = color / other;
		return def;
	}
	void ModelDef::operator+=(const ModelDef & other)
	{
		position += other.position;
		rotation += other.rotation;
		mineRotation += other.mineRotation;
		scale += other.scale;
		color += other.color;
	}
	void ModelDef::operator-=(const ModelDef & other)
	{
		position -= other.position;
		rotation -= other.rotation;
		mineRotation -= other.mineRotation;
		scale -= other.scale;
		color -= other.color;
	}
	void ModelDef::operator*=(float32 other)
	{
		position *= other;
		rotation *= other;
		mineRotation *= other;
		scale *= other;
		color *= other;
	}
	void ModelDef::operator/=(float32 other)
	{
		assert(other != 0);
		position /= other;
		rotation /= other;
		mineRotation /= other;
		scale /= other;
		color /= other;
	}
	void ModelDef::serialiseF(std::ostream & file, Res::DataScriptSaver & saver) const
	{
		saver.save("posX", position.x, ModelDef::default.position.x);
		saver.save("posY", position.y, ModelDef::default.position.y);

		saver.save("scaleX", scale.x, ModelDef::default.scale.x);
		saver.save("scaleY", scale.y, ModelDef::default.scale.y);

		saver.save("rot", rotation.asDegree(), ModelDef::default.rotation.asDegree());
		saver.save("mineRot", mineRotation.asDegree(), ModelDef::default.mineRotation.asDegree() );
		
		saver.save("clR", color.r, ModelDef::default.color.r);
		saver.save("clG", color.g, ModelDef::default.color.g);
		saver.save("clB", color.b, ModelDef::default.color.b);
		saver.save("clA", color.a, ModelDef::default.color.a);
	}
	void ModelDef::deserialiseF(std::istream & file, Res::DataScriptLoader & loader)
	{
		position.x = loader.load("posX", ModelDef::default.position.x);
		position.y = loader.load("posY", ModelDef::default.position.y);

		scale.x = loader.load("scaleX", ModelDef::default.scale.x);
		scale.y = loader.load("scaleY", ModelDef::default.scale.y);

		rotation = Degree(loader.load("rot", ModelDef::default.rotation.asDegree()) );
		mineRotation = Degree(loader.load("mineRot", ModelDef::default.mineRotation.asDegree()) );
		
		color.r = loader.load("clR", ModelDef::default.color.r);
		color.g = loader.load("clG", ModelDef::default.color.g);
		color.b = loader.load("clB", ModelDef::default.color.b);
		color.a = loader.load("clA", ModelDef::default.color.a);
	}
}