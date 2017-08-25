#pragma once

class VisibleGameObject
{
public:
	// Member functions
	VisibleGameObject(); // default constructor
	virtual ~VisibleGameObject(); // destructor

	// Keyword virtual applied to a member function tells compiler to use
	// a derived version of the member function instead of the pointer type
	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow& window);
	virtual void SetPosition(float x, float y);

private:
	// Member variables
	sf::Sprite _sprite;
	sf::Texture _texture;
	std::string _filename; // name of file loaded into _texture
	bool _isLoaded; // true when texture data has been loaded
};