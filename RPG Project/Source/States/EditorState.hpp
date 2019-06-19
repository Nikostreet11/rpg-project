/*
 * EditorState.hpp
 *
 *  Created on: Apr 27, 2019
 *      Author: nicop
 */

#ifndef STATES_EDITORSTATE_HPP_
#define STATES_EDITORSTATE_HPP_

#include "State.hpp"

#include "..\Map\TileMap.hpp"
#include "..\GUI\Button.hpp"
#include "..\GUI\PauseMenu.hpp"
#include "..\GUI\TextureSelector.hpp"

class EditorState :
		public State
{
public:
	// Static functions

	// Constructor / Destructor
	explicit EditorState(StateData& stateData);
	virtual ~EditorState();

	// Functions
	virtual void endState();

	virtual void update(const float& dt);
	virtual void updateMousePositions(
			std::shared_ptr<sf::View> view = nullptr) override;
	virtual void updateInput(const float& dt);
	virtual void updateEditorInput(const float& dt);
	virtual void updateGUI();
	virtual void updateButtons();
	virtual void updatePauseMenu();
	virtual void render(std::shared_ptr<sf::RenderTarget> target = nullptr);
	virtual void renderGUI(std::shared_ptr<sf::RenderTarget> target = nullptr);
	virtual void renderButtons(std::shared_ptr<sf::RenderTarget> target = nullptr);

protected:
	// Initialization functions
	void initVariables();
	void initView();
	virtual void initBindings();
	void initFonts();
	void initText();
	void initBackground();
	void initTileMap();
	void initPauseMenu();
	void initGUI();
	void initButtons();

	// Resources
	std::shared_ptr<sf::View> tileMapView;
	std::shared_ptr<sf::Font> font;
	std::unique_ptr<TileMap> tileMap;
	std::unique_ptr<gui::PauseMenu> pauseMenu;
	std::map<std::string, std::unique_ptr<gui::Button>> buttons;
	std::unique_ptr<gui::TextureSelector> textureSelector;
	sf::Text cursorText;
	sf::RectangleShape selectorRect;
	sf::RectangleShape sidebar;

	// Variables
	sf::Vector2u mousePosGrid;

	float cameraSpeed;

	bool crossable;
	Tile::Type type;
};

#endif /* STATES_EDITORSTATE_HPP_ */
