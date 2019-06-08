/*
 * EditorState.cpp
 *
 *  Created on: Apr 27, 2019
 *      Author: nicop
 */

#include "EditorState.hpp"

EditorState::EditorState(StateData& stateData) :
		State(stateData)
{
	initVariables();
	initView();
	initKeybinds();
	initFonts();
	initText();
	initBackground();
	initTileMap();
	initPauseMenu();
	initGUI();
	initButtons();

	/*addEntry("New Game", Exploration::getInstance());
	addEntry("Load Game");
	addEntry("Options");
	addEntry("Exit");*/
}

EditorState::~EditorState() {/*
	instance = nullptr;
*/}

void EditorState::endState()
{
	std::cout << "Ending EditorState" << std::endl;
	ended = true;
}

void EditorState::update(const float& dt)
{
	updateInput(dt);
	updateMousePositions();

	if (!paused)
	{
		// Unpaused update
		tileMap->update(mousePosView);
		updateGUI();
		updateButtons();
		updateEditorInput();
	}
	else
	{
		// Paused update
		updatePauseMenu();
	}
}

void EditorState::updateMousePositions(std::shared_ptr<sf::View> view)
{
	State::updateMousePositions(view);

	if (tileMap->isActive())
	{
		if (mousePosView.x - tileMap->getPosition().x < 0)
		{
			mousePosGrid.x = 0;
		}
		else
		{
			mousePosGrid.x = static_cast<unsigned>(
					(mousePosView.x - tileMap->getPosition().x) / gridSize);
		}

		if (mousePosView.y - tileMap->getPosition().y < 0)
		{
			mousePosGrid.y = 0;
		}
		else
		{
			mousePosGrid.y = static_cast<unsigned>(
					(mousePosView.y - tileMap->getPosition().y) / gridSize);
		}

		if (mousePosGrid.x >= tileMap->getSize().x)
		{
			mousePosGrid.x = tileMap->getSize().x - 1;
		}
		if (mousePosGrid.y >= tileMap->getSize().y)
		{
			mousePosGrid.y = tileMap->getSize().y - 1;
		}
	}
}

void EditorState::updateInput(const float& dt)
{
	if (keybinds.at("CLOSE").isPressed())
	{
		// Key pressed
		if (!paused)
			pauseState();
		else
			unpauseState();
	}

	if (keybinds.at("TOGGLE_COLLISION").isPressed())
	{
		if (collision)
		{
			collision = false;
		}
		else
		{
			collision = true;
		}
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) &&
		keybinds.at("NEXT_TYPE").isPressed())
	{
		type = static_cast<Tile::Type>(static_cast<short>(type) + 1);

		if (type == Tile::Type::NumberOfTypes)
		{
			type = Tile::Type::Default;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) &&
		keybinds.at("NEXT_TYPE").isPressed())
	{
		type = static_cast<Tile::Type>(
				static_cast<short>(type) - 1);

		if (type == Tile::Type::Invalid)
		{
			type = static_cast<Tile::Type>(
					static_cast<short>(Tile::Type::NumberOfTypes) - 1);
		}
	}

	// Move view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		view.move(10.f, 0.f);
	}
}

void EditorState::updateEditorInput()
{
	if (textureSelector->isActive())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			// TODO: make textureSelector a class with a getSpriteIndex method
			tileMap->setSpriteIndex(sf::Vector2u(
					textureSelector->getTextureRect().left /
							tileMap->getSpriteSize(),
					textureSelector->getTextureRect().top /
							tileMap->getSpriteSize()));
		}
	}
	else if (tileMap->isActive())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			tileMap->addTile(mousePosGrid, 0, type, collision);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			tileMap->removeTile(mousePosGrid, 0);
		}
	}

	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (!textureSelector->getActive())
		{
			tileMap->selectNextTile();
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!textureSelector->getActive())
		{
			tileMap->selectPreviousTile();
		}
	}
	*/
}

void EditorState::updateGUI()
{
	if (!textureSelector->isActive())
	{
		selectorRect.setTexture(&tileMap->getTileset());
		// TODO: make textureSelector a class with a setSpriteIndex method
		selectorRect.setTextureRect(sf::IntRect(
				tileMap->getSpriteIndex().x * tileMap->getSpriteSize(),
				tileMap->getSpriteIndex().y * tileMap->getSpriteSize(),
				tileMap->getSpriteSize(),
				tileMap->getSpriteSize()));
		selectorRect.setPosition(
				mousePosGrid.x * gridSize +
						tileMap->getPosition().x,
				mousePosGrid.y * gridSize +
						tileMap->getPosition().y);
	}

	std::stringstream cursorString;
	cursorString <<
			mousePosView.x << ' ' << mousePosView.y << '\n' <<
			mousePosGrid.x << ' ' <<
			mousePosGrid.y << '\n' <<
			"Collision: " << collision << '\n' <<
			"Type: " << type << '\n';
	cursorText.setString(cursorString.str());
	cursorText.setPosition(mousePosView.x, mousePosView.y - 80.f);

	textureSelector->update(mousePosWindow);
}

void EditorState::updateButtons()
{
	/* Updates all the buttons in the state and handles their functionalities */
	for (auto &it : buttons)
	{
		it.second->update(mousePosView);
	}
}

void EditorState::updatePauseMenu()
{
	pauseMenu->update(mousePosView);

	if (pauseMenu->isButtonPressed("SAVE"))
	{
		tileMap->saveToFile("TestTileMap.txt");
	}

	if (pauseMenu->isButtonPressed("LOAD"))
	{
		tileMap->loadFromFile("TestTileMap.txt");
	}

	if (pauseMenu->isButtonPressed("QUIT"))
	{
		endState();
	}
}

void EditorState::render(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->setView(view);
	tileMap->render(target);

	target->setView(target->getDefaultView());
	renderGUI(target);
	renderButtons(target);

	if (paused)
	{
		// Pause menu render
		pauseMenu->render(window);
	}
}

void EditorState::renderGUI(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->draw(selectorRect);

	target->draw(sidebar);

	textureSelector->render(target);

	target->draw(cursorText);
}

void EditorState::renderButtons(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	for (auto &it : buttons)
	{
		it.second->render(target);
	}
}

// Initialization functions
void EditorState::initVariables()
{
	collision = false;
	type = Tile::Type::Default;

	/*textureRect = sf::IntRect(
			0,
			0,
			static_cast<int>(gridSize),
			static_cast<int>(gridSize));*/
}

void EditorState::initView()
{
	view.setSize(
			graphicsSettings->resolution.width,
			graphicsSettings->resolution.height);

	view.setCenter(
			graphicsSettings->resolution.width / 2,
			graphicsSettings->resolution.height / 2);
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/Keybinds/EditorState.ini");

	if (ifs.is_open())
	{
		std::string action, key;

		while (ifs >> action >> key)
		{
			keybinds[action].setCode((*supportedKeys)[key]);
		}
	}

	ifs.close();
}

void EditorState::initFonts()
{
	font = std::make_shared<sf::Font>();

	if (!font->loadFromFile("Fonts/Arial.ttf"))
	{
		throw "ERROR::EDITORSTATE::COULD_NOT_LOAD_FONT";
	}
}

void EditorState::initText()
{
	cursorText.setFont(*font);
	cursorText.setCharacterSize(16);
	cursorText.setFillColor(sf::Color::White);
}

void EditorState::initBackground()
{
}

void EditorState::initTileMap()
{
	tileMap.reset(new TileMap(
			sf::Vector2f(160, 10),
			sf::Vector2u(12, 8),
			stateData.gridSize,
			"Villages.png",
			32));
}

void EditorState::initPauseMenu()
{
	pauseMenu.reset(new gui::PauseMenu(window, font));

	pauseMenu->addButton("SAVE", 500.f, "Save");
	pauseMenu->addButton("LOAD", 600.f, "Load");
	pauseMenu->addButton("QUIT", 800.f, "Quit");
}

void EditorState::initGUI()
{
	selectorRect.setSize(sf::Vector2f(stateData.gridSize, stateData.gridSize));

	selectorRect.setFillColor(sf::Color(255, 255, 255, 150));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);

	textureSelector.reset(new gui::TextureSelector(
			sf::Vector2f(20.f, 50.f),
			sf::Vector2f(1536.f, 512.f),
			tileMap->getSpriteSize(),
			tileMap->getTileset(),
			font));

	sidebar.setSize(sf::Vector2f(
			150.f,
			static_cast<float>(graphicsSettings->resolution.height)));
	sidebar.setFillColor(sf::Color(100, 100, 100, 255));
	sidebar.setOutlineThickness(1.f);
	sidebar.setOutlineColor(sf::Color(130, 130, 130, 255));
}

void EditorState::initButtons()
{
}
