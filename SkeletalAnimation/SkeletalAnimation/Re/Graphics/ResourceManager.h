#pragma once
/// Code from ReEngine library
/// all rights belongs to Risist (Maciej Dominiak) (risistt@gmail.com)

#include <Re\Common\utility.h>
#include <string>
#include <unordered_map>

using namespace sf;
using namespace std;

using ResId = uint16;


/// class singelton responsible for resource managament
/// loades .res file (see script module) with definition of each resource to load
///

///	resource types :  
///		graphics	- images
///		font		- fonts
///		script		- preloaded scripts to speed up loading 
///

/// call function .deserialize() to load file with resource definition
/// definition of resource file goes as follow:
/// first line contains prepaths for each resource type:
///	<prepathGraphics =; prepathFont =; prepathScript =; prepathResource =; prepathPath =;>
/// prepath is a path of directory when the type of resource should be searched for
///		prepathGraphics =;
///		prepathFont =;
///		prepathResource =;	another resource loading file, used to split up resource definitions
///		prepathPath =;		cashed paths to some resources
///

/// then definition of each resource
///		<type =atlas; path =; textureId =; atlasId; >
///			path						- path to file from prepath
///			textureId, atlasId			- on which id save atlas and texture (whole sized one)
///		<type =textureSingle; textureId =; atlasId; posX =0; posY =0; width =atlasX; height =atlasY;> creates texture instance from given atlas
///			textureId					- on which id save texture
///			atlasId						- from which atlas to take graphical data
///			posX, posY, width, height	- bounds of texture
///		<type =textureGridX; textureFromId =; atlasId =; posX =0; posY =0; width =atlasX; height =atlasY;> Wip
///		<type =textureGridY; textureFromId =; atlasId =; posX =0; posY =0; width =atlasX; height =atlasY;> Wip
///		<type =script; id=; path =; > 
///			id							- on which id to save script string
///			path						- path (without prepath) of the file
///		<type =path; id=; path =; > 
///			id							- on which id to save path string
///			path						- path (without prepath) of the file
///		<type =font; id=; path =; > 
///			id							- on which id to save font
///			path						- path (without prepath) of the file
///		<type =resource; path =; > 
///			path - another file with resource definition to load

/// each resource definition has own macro to refer to data (eg. atlasInst[5], textureInst[i] ect. )


class ResourceManager : public Res::ISerialisable
{
public:
	ResourceManager();

	/// list of loaded textures
	std::unordered_map< ResId, Texture> atlases;
	
	/// struct to hold data about texture instance placed in atlas
	struct TextureInstance
	{
		ResId atlasId;
		Texture* getTexture() const;
		void set(sf::Sprite& inSp)
		{
			inSp.setTexture(*getTexture(), false);
			inSp.setTextureRect(bounds);
		}
		void set(sf::ConvexShape& inSp)
		{
			inSp.setTexture(getTexture(), false);
			inSp.setTextureRect(bounds);
		}
		void set(sf::CircleShape& inSp)
		{
			inSp.setTexture(getTexture(), false);
			inSp.setTextureRect(bounds);
		}
		void set(sf::RectangleShape& inSp)
		{
			inSp.setTexture(getTexture(), false);
			inSp.setTextureRect(bounds);
		}

 		sf::IntRect bounds;
	};
	std::unordered_map<ResId, TextureInstance> textures;


	std::unordered_map< ResId, Font> fonts;
	/// to faster load scripts many times in a row
	/// save script in memory, so disc operations is not needed
	std::unordered_map< ResId, string> cashedScript;
	/// for resources which can not be preloaded save paths to use in game
	std::unordered_map< ResId, string> paths;

	void createTexture(Texture& ts, const std::string& path);
	string createTranscription(const std::string& path);

	/// set color which shoud be treated as transparent
	static inline void setClTransparent(const Color& s)
	{
		clTransparent = s;
	}
	/// get color which shoud be treated as transparent
	static inline const Color& getClTransparent()
	{
		return clTransparent;
	}

	void clear();

private:
	static Image im;
	static Color clTransparent;

protected:
	virtual void serialiseF(std::ostream& file, Res::DataScriptSaver& saver) const override;
	virtual void deserialiseF(std::istream& file, Res::DataScriptLoader& loader) override;
};
extern ResourceManager res;



/// defines for easier usage
#define atlasInst res.atlases
#define tsInst res.textures
#define fontInst res.fonts
#define scriptInst res.cashedScript
#define pathInst res.paths


