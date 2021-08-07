//============================ include section ===============================
#pragma once
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Macros.h"
/*============================================================================*/
class Textures
{
	//========================== public section ==============================
public:
	static Textures& instance();
	//============================ gets section ===============================
	const sf::Texture& getBackground(int);
	const sf::Texture& getTexture(int)const;
	const sf::Font& getFont() const;
	//========================= private section ===============================
private:
	//========================= members section ===============================
	std::unordered_map<int, std::unique_ptr <sf::Texture>> m_textures;
	std::unordered_map<int, std::unique_ptr <sf::Texture>> m_backgrounds;
	sf::Font m_font;
	//================= constructors and destructors section =================
	Textures();
	//============================ sets section ===============================
	void setBackgrounds();
	void setObjects();
};