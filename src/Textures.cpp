#include "Textures.h"
#include "Macros.h"
#include <exception>
//==================== Constructors & destructors section ====================
Textures::Textures() {
    m_backgrounds.clear();
    m_textures.clear();
    setBackgrounds();
    setObjects();
    m_font.loadFromFile("CooperBlackStd.otf");
}
//============================================================================
Textures& Textures::instance() {
    static Textures inst;
    return(inst);
}
//============================== gets section ================================
//============================================================================
const sf::Texture& Textures::getBackground(int wanted_background) {
    return (*m_backgrounds.find(wanted_background)->second);
}
//============================================================================
const sf::Texture& Textures::getTexture(int texture)const {
    return (*m_textures.find(texture)->second);
}
////============================================================================
const sf::Font& Textures::getFont() const {
    return m_font;
}
//============================== sets section ================================
void Textures::setBackgrounds() {
    std::unique_ptr<sf::Texture> texturesCreator;

    texturesCreator = std::make_unique<sf::Texture>();
    m_backgrounds.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (BOARD1, std::move(texturesCreator)));
    m_backgrounds[BOARD1]->loadFromFile(BOARD_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    m_backgrounds.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (BOARD2, std::move(texturesCreator)));
    m_backgrounds[BOARD2]->loadFromFile(BOARD_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    m_backgrounds.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (BOARD3, std::move(texturesCreator)));
    m_backgrounds[BOARD3]->loadFromFile(BOARD_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    m_backgrounds.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (BOARD4, std::move(texturesCreator)));
    m_backgrounds[BOARD4]->loadFromFile(BOARD_PATH);
}
//============================================================================
void Textures::setObjects() {
    std::unique_ptr<sf::Texture> texturesCreator;

    texturesCreator = std::make_unique<sf::Texture>();
    m_textures.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (int(BLACK), std::move(texturesCreator)));
    m_textures[BLACK]->loadFromFile(BLACK_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    m_textures.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (int(WHITE), std::move(texturesCreator)));
    m_textures[WHITE]->loadFromFile(WHITE_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    m_textures.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (NUM1, std::move(texturesCreator)));
    m_textures[NUM1]->loadFromFile(NUM1_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    m_textures.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (NUM2, std::move(texturesCreator)));
    m_textures[NUM2]->loadFromFile(NUM2_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    m_textures.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (NUM3, std::move(texturesCreator)));
    m_textures[NUM3]->loadFromFile(NUM3_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    m_textures.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (NUM4, std::move(texturesCreator)));
    m_textures[NUM4]->loadFromFile(NUM4_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    m_textures.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (NUM5, std::move(texturesCreator)));
    m_textures[NUM5]->loadFromFile(NUM5_PATH);

    texturesCreator = std::make_unique<sf::Texture>();
    m_textures.insert(std::pair<int, std::unique_ptr <sf::Texture>>
        (NUM6, std::move(texturesCreator)));
    m_textures[NUM6]->loadFromFile(NUM6_PATH);
}
