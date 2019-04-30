/*
 * GraphicEngine.cpp
 *
 *  Created on: Jul 25, 2018
 *      Author: nicop
 */

#include "GraphicEngine.h"

#include "BattleState.h"
#include "Human.h"
#include "Map.h"
#include "Party.h"

#include "graphics/InnerWindow.hpp"
#include "TileType.h"
#include "BattleBackground.h"
#include "Texture.h"

#include <typeinfo>

#include "Graphics/Dialogue.hpp"

GraphicEngine::GraphicEngine(int resX, int resY) :
		camera(resX, resY),
		resolutionX(resX), resolutionY(resY),
		tileWidth(64), tileHeight(64),
		charWidth(60), charHeight(70),
		window(sf::VideoMode(resolutionX, resolutionY), "Role Game Project"),
		graphics((int) Texture::numberOfTextures) {
	loadTextures();
	loadFonts();
}

GraphicEngine::~GraphicEngine() {}

void GraphicEngine::drawMainMenu(MainMenuState* mainMenu) {
	window.clear(sf::Color::White);

	sf::Sprite* sprite;

	sprite = &graphics.at((int) Texture::menu_background)->sprite;
	sprite->setTextureRect(sf::IntRect(0, 0, 1598, 898));
	sprite->setScale((float) resolutionX / 1598, (float) resolutionY / 898);
	sprite->setPosition(sf::Vector2f(0, 0));
	window.draw(*sprite);

	sf::Text text;
	text.setFont(arial);
	text.setCharacterSize(resolutionY / 14);
	text.setFillColor(sf::Color(190, 190, 190));
	text.setStyle(sf::Text::Bold);
	text.setPosition(50, 120);

	/*for (int count = 0; count < mainMenu->getLenght(); count++) {
		if (mainMenu->getActiveEntry() == count) {
			text.setStyle(sf::Text::Bold | sf::Text::Underlined);
		}
		text.setString(mainMenu->getEntryName(count));
		window.draw(text);

		text.setStyle(sf::Text::Bold);
		text.move(0, 50);
	}*/
}

void GraphicEngine::drawExploration(Exploration& exploration) {
	const Map& map = exploration.getMap();
	const Party& party = exploration.getParty();

	camera.setX(party.getHero(0)->getPosX() * tileWidth - (camera.getWidth() - tileWidth) / 2);
	camera.setY(party.getHero(0)->getPosY() * tileHeight - (camera.getHeight() - tileWidth) / 2);

	for (int y = 0; y < map.getHeight(); y++) {
		for (int x = 0; x < map.getWidth(); x++) {
			if (isVisible(x, y)) {
				drawTile(x * tileWidth - camera.getX(),
						y * tileHeight - camera.getY(),
						map.getTile(x, y));
			}
		}
	}

	for (int position = party.getSize() - 1; position >= 0; position--) {
		drawCharacter(party.getHero(position));
	}
}

void GraphicEngine::drawBattle(Battle& battle) {
	//draw battle background
	if (loadSpriteInfo(BattleBackground::grassland)) {
		drawSprite(0, 0, resolutionX, resolutionY);
	}
	else {
		drawNullSprite(0, 0, resolutionX, resolutionY);
	}

	// draw dialogue window
	InnerWindow dialogueWindow(sf::Vector2f(resolutionX, resolutionY * 1/4));
	Dialogue dialogue(30, "Some wild enemies appeared!");
	dialogue.setPosition(sf::Vector2f(30, 30));
	dialogueWindow.addChild(dialogue);
	dialogueWindow.setPosition(sf::Vector2f(resolutionX * 0, resolutionY * 3/4));
	window.draw(dialogueWindow);

	// draw battle characters
	sf::Vector2f start(resolutionX * 2. / 3., resolutionY * 1. / 4.);
	sf::Vector2f step(resolutionX * 1. / 30., resolutionY * 1. / 10.);

	for (int index = 0; index < (int) battle.getParty().size(); index++) {
		drawBattleCharacter(
				start.x + index * step.x,
				start.y + index * step.y,
				battle.getParty().at(index));
	}

	for (int index = 0; index < (int) battle.getFoes().size(); index++) {
		drawBattleCharacter(
				resolutionX - start.x - 64 - index * step.x,
				start.y + index * step.y,
				battle.getFoes().at(index));
	}
}

sf::RenderWindow& GraphicEngine::getWindow() {
	return window;
}

sf::Sprite& GraphicEngine::getSprite(Battle::Background background) const {
	GraphicsInfo* graphicsInfoPtr;
	sf::Vector2i absolute, relative, offset, step, size;
	relative.x = -1;
	relative.y = -1;

	switch (background) {
	case Battle::Background::none:
		graphicsInfoPtr = graphics.at((int) Texture::nullTexture);
		absolute.x = 0; size.x = resolutionX;
		absolute.y = 0; size.y = resolutionY;
		break;
	case Battle::Background::grassland:
		graphicsInfoPtr = graphics.at((int) Texture::battle_backgrounds);
		relative.x = 0; offset.x = 2; step.x = 4; size.x = 512;
		relative.y = 0; offset.y = 2; step.y = 4; size.y = 312;
		break;
	// TODO: other cases
	default:
		graphicsInfoPtr = graphics.at((int) Texture::nullTexture);
		absolute.x = 0; size.x = window.getSize().x;
		absolute.y = 0; size.y = window.getSize().y;
		break;
	}

	if(relative != sf::Vector2i(-1, -1)) {
		absolute.x = offset.x + relative.x * (step.x + size.x);
		absolute.y = offset.y + relative.y * (step.y + size.y);
	}

	sf::Sprite& sprite = graphicsInfoPtr->sprite;
	sprite.setTextureRect(sf::IntRect(absolute, size));
	return sprite;
}

sf::Sprite& GraphicEngine::getSprite(const Character& character) const {
	GraphicsInfo* graphicsInfoPtr;
	sf::Vector2i absolute, relative, offset, step, size;
	relative.x = -1;
	relative.y = -1;

	if (typeid(character) == typeid(Human)) {
		graphicsInfoPtr = graphics.at((int) Texture::battle_warrior);
		relative.x = 0; offset.x = 8; step.x = 0; size.x = 64;
		relative.y = 0; offset.y = 8; step.y = 0; size.y = 64;
	}
	else if (typeid(character) == typeid(Foe)) {
		graphicsInfoPtr = graphics.at((int) Texture::battle_foes);
		relative.x = 4; offset.x = 0; step.x = 2; size.x = 64;
		relative.y = 0; offset.y = 0; step.y = 2; size.y = 64;
	}
	else {
		graphicsInfoPtr = graphics.at((int) Texture::nullTexture);
		absolute.x = 0; size.x = window.getSize().x;
		absolute.y = 0; size.y = window.getSize().y;
	}

	if(relative != sf::Vector2i(-1, -1)) {
		absolute.x = offset.x + relative.x * (step.x + size.x);
		absolute.y = offset.y + relative.y * (step.y + size.y);
	}

	sf::Sprite& sprite = graphicsInfoPtr->sprite;
	sprite.setTextureRect(sf::IntRect(absolute, size));
	return sprite;
}

bool GraphicEngine::loadFonts() {
	if (!arial.loadFromFile("fonts/arial.ttf")) {
			std::cout << "Error while loading the font" << std::endl;
			return false;
		}
	return true;
}

bool GraphicEngine::loadTextures() {
	for (int count = 0; count < (int) Texture::numberOfTextures; count++) {
		graphics.at(count) = new GraphicsInfo();
	}

	// saving the paths
	graphics.at((int) Texture::nullTexture)->path = "";
	graphics.at((int) Texture::villages)->path = "images/exploring/tilesets/PSP - Final Fantasy 4 The Complete Collection - Villages.png";
	graphics.at((int) Texture::exploringCharacters)->path = "images/exploring/characters/PSP - Final Fantasy 1 - Playable Characters.png";
	graphics.at((int) Texture::menu_background)->path = "images/main_menu/background.png";
	graphics.at((int) Texture::battle_backgrounds)->path = "images/battle/backgrounds/PSP - Final Fantasy 1 - Battle Backgrounds.png";
	graphics.at((int) Texture::battle_warrior)->path = "images/battle/characters/warrior.png";
	graphics.at((int) Texture::battle_foes)->path = "images/battle/enemies/foes.png";

	// loading the textures
	graphics.at((int) Texture::nullTexture)->texture.create(resolutionX, resolutionY);
	for (int index = 1; index < (int) Texture::numberOfTextures; index++)
		if (!graphics.at(index)->texture.loadFromFile(graphics.at(index)->path)) {
			std::cout << "Error while loading the textures" << std::endl;
			return false;
		}

	// linking the sprites to the textures
	for (int index = 0; index < (int) Texture::numberOfTextures; index++)
		graphics.at(index)->sprite.setTexture(graphics.at(index)->texture);
	return true;
}

bool GraphicEngine::loadSpriteInfo(const Tile& tile) {
	Texture texture;
	int posX, relativeX = -1, offsetX = 0, width,
		posY, relativeY = -1, offsetY = 0, height;

	switch (tile.getTileType()) {
	case TileType::grass:
		texture = Texture::villages;
		relativeX = 3; width = 32;
		relativeY = 0; height = 32;
		break;
	case TileType::bush:
		texture = Texture::villages;
		relativeX = 0; width = 32;
		relativeY = 1; height = 32;
		break;
	case TileType::tree:
		texture = Texture::villages;
		relativeX = 9; width = 32;
		relativeY = 0; height = 32;
		break;
	case TileType::root:
		texture = Texture::villages;
		relativeX = 9; width = 32;
		relativeY = 1; height = 32;
		break;
	// TODO: other cases
	default:
		return false;
	}

	if (relativeX != -1) {
		setSpritePosition(posX, relativeX, width, offsetX);
	}
	if (relativeY != -1) {
		setSpritePosition(posY, relativeY, height, offsetY);
	}

	spriteInfo.update(texture, posX, posY, width, height);
	return true;
}

// TODO: remove, deprecated
bool GraphicEngine::loadSpriteInfo(const BattleBackground& background) {
	Texture texture;
	int posX, relativeX, offsetX = 0, width,
		posY, relativeY, offsetY = 0, height;

	switch (background) {
	case BattleBackground::grassland:
		texture = Texture::battle_backgrounds;
		relativeX = 0; offsetX = 8; width = 500;
		relativeY = 0; offsetY = 8; height = 300;
		break;
	// TODO: other cases
	default:
		return false;
	}
	if (relativeX != -1) {
		setSpritePosition(posX, relativeX, width, offsetX);
	}
	if (relativeY != -1) {
		setSpritePosition(posY, relativeY, height, offsetY);
	}

	spriteInfo.update(texture, posX, posY, width, height);
	return true;
}

// TODO: remove, deprecated
bool GraphicEngine::loadSpriteInfo(Character* character, const CharacterBattleState& state) {
	Texture texture;
	int posX, relativeX, offsetX = 0, width,
		posY, relativeY, offsetY = 0, height;

	Human* human = dynamic_cast<Human*>(character);
	Foe* foe = dynamic_cast<Foe*>(character);
	if (human) {
		texture = Texture::battle_warrior;
		switch (state) {
		case CharacterBattleState::idle:
			relativeX = 0; offsetX = 8; width = 72;
			relativeY = 0; offsetY = 8; height = 72;
			break;
		// TODO: other cases
		default:
			return false;
		}
	}
	else if (foe) {
		texture = Texture::battle_foes;
		relativeX = 4; offsetX = 0; width = 66;
		relativeY = 0; offsetY = 0; height = 70;
	}

	if (relativeX != -1) {
		setSpritePosition(posX, relativeX, width, offsetX);
	}
	if (relativeY != -1) {
		setSpritePosition(posY, relativeY, height, offsetY);
	}

	spriteInfo.update(texture, posX, posY, width, height);
	return true;
}

void GraphicEngine::setSpritePosition(int& absolute, int relative, int step, int offset) {
	absolute = relative * step + offset;
}

void GraphicEngine::drawTile(int posX, int posY, const Tile& tile) {
	if (loadSpriteInfo(tile)) {
		drawSprite(posX, posY, tileWidth, tileHeight);
	}
	else {
		drawNullSprite(posX, posY, tileWidth, tileHeight);
	}
}

void GraphicEngine::drawCharacter(Character* character) {
	int x = character->getPosX();
	int y = character->getPosY();

	// TODO: save variables as class members
	int charX = 0;
	int charY = 0;
	int charWidth = 36;
	int charHeight = 36;

	Human* human = dynamic_cast<Human*>(character);
	if (human) {
		sf::Sprite& sprite = graphics.at((int) Texture::exploringCharacters)->sprite;
		sprite.setTextureRect(sf::IntRect(
				charX, charY,
				charWidth, charHeight));
		sprite.setPosition(sf::Vector2f(
				x * tileWidth - camera.getX(),
				y * tileHeight - camera.getY()));
		sprite.setScale((float) tileWidth / charWidth,
				(float) tileHeight / charHeight);
		window.draw(sprite);
	}
}

void GraphicEngine::drawBattleCharacter(int posX, int posY, Character* character) {
	if (loadSpriteInfo(character, CharacterBattleState::idle)) {
		drawSprite(posX, posY, charWidth, charHeight);
	}
	else {
		drawNullSprite(posX, posY, charWidth, charHeight);
	}
}

void GraphicEngine::drawSprite(int posX, int posY, int width, int height) {
	sf::Sprite& sprite = graphics.at((int) spriteInfo.getTexture())->sprite;
	sprite.setTextureRect(sf::IntRect(spriteInfo.getPosX(), spriteInfo.getPosY(),
			spriteInfo.getWidth(), spriteInfo.getHeight()));
	sprite.setPosition(sf::Vector2f(posX, posY));
	sprite.setScale((float) width / spriteInfo.getWidth(),
			(float) height / spriteInfo.getHeight());
	window.draw(sprite);
}

void GraphicEngine::drawNullSprite(int posX, int posY, int width, int height) {
	sf::RectangleShape rectangle(sf::Vector2f(width, height));
	rectangle.setFillColor(sf::Color::White);
	rectangle.setPosition(sf::Vector2f(posX, posY));
	window.draw(rectangle);
}

bool GraphicEngine::isVisible(int x, int y) {
	if (camera.getX() <= (x + 1) * tileWidth &&
			x * tileWidth <= camera.getX() + camera.getWidth() &&
			camera.getY() <= (y + 1) * tileHeight &&
			y * tileHeight <= camera.getY() + camera.getHeight()) {
		return true;
	}
	else {
		return false;
	}
}

const sf::Font& GraphicEngine::getArial() const {
	return arial;
}
