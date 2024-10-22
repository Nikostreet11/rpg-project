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
	initBindings();
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
	updateMousePositions(tileMapView);

	if (!paused)
	{
		// Unpaused update
		updateGUI();
		updateButtons();
		updateEditorInput(dt);

		updateMousePositions(tileMapView);
		tileMap->update(mousePosView);
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
		if (mousePosView.x < 0)
		{
			mousePosGrid.x = 0;
		}
		else
		{
			mousePosGrid.x = static_cast<unsigned>(
					mousePosView.x / gridSize);
		}

		if (mousePosView.y < 0)
		{
			mousePosGrid.y = 0;
		}
		else
		{
			mousePosGrid.y = static_cast<unsigned>(
					mousePosView.y / gridSize);
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
	if (keybinds.at("PAUSE").isPressed())
	{
		// Key pressed
		if (!paused)
			pauseState();
		else
			unpauseState();
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	if (textureSelector->isActive())
	{
		if (mousebinds.at("SELECT_TILE").isPressed())
		{
			// TODO: make textureSelector a class with a getSpriteIndex method
			tileMap->setSpriteIndex(sf::Vector2u(
					textureSelector->getTextureRect().left /
							tileMap->getSpriteSize(),
					textureSelector->getTextureRect().top /
							tileMap->getSpriteSize()));
		}
	}
	else if (tileMap->isActive()
			&& !sidebar.getGlobalBounds().contains(
					static_cast<sf::Vector2f>(mousePosWindow)))
	{
		if (keybinds["ALTERNATE_INPUT"].isHold())
		{
			if (mousebinds.at("ADD_TILE").isHold())
			{
				tileMap->addBaseTile(mousePosGrid, type, closeness, crossable);
			}

			if (mousebinds.at("REMOVE_TILE").isHold())
			{
				tileMap->removeTile(mousePosGrid);
			}

			if (keybinds.at("NEXT_TYPE").isPressed())
			{
				tileMap->setBaseTileDangerous(mousePosGrid);
			}
		}
		else
		{
			if (mousebinds.at("ADD_TILE").isPressed())
			{
				tileMap->addTile(mousePosGrid, type, closeness, crossable);
			}

			if (mousebinds.at("REMOVE_TILE").isPressed())
			{
				tileMap->removeTile(mousePosGrid);
			}

			if (keybinds.at("NEXT_TYPE").isPressed())
			{
				type = static_cast<Tile::Type>(static_cast<short>(type) + 1);

				if (type == Tile::NumberOfTypes)
				{
					type = Tile::Default;
				}
			}
		}
	}

	/*
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) &&
		keybinds.at("NEXT_TYPE").isPressed())
	{
		type = static_cast<Tile::Type>(
				static_cast<short>(type) - 1);

		if (type == Tile::Invalid)
		{
			type = static_cast<Tile::Type>(
					static_cast<short>(Tile::NumberOfTypes) - 1);
		}
	}
	*/

	if (keybinds.at("NEXT_CLOSENESS").isPressed())
	{
		if (closeness == Tile::Closeness::Background)
		{
			closeness = Tile::Closeness::Foreground;
		}
		else
		{
			closeness = Tile::Closeness::Background;
		}
	}


	if (keybinds.at("TOGGLE_COLLISION").isPressed())
	{
		if (crossable)
		{
			crossable = false;
		}
		else
		{
			crossable = true;
		}
	}

	// Move view
	if (keybinds.at("MOVE_CAMERA_UP").isHold())
	{
		tileMapView->move(0.f, -std::round(cameraSpeed * dt));
	}

	if (keybinds.at("MOVE_CAMERA_LEFT").isHold())
	{
		tileMapView->move(-std::round(cameraSpeed * dt), 0.f);
	}

	if (keybinds.at("MOVE_CAMERA_DOWN").isHold())
	{
		tileMapView->move(0.f, std::round(cameraSpeed * dt));
	}

	if (keybinds.at("MOVE_CAMERA_RIGHT").isHold())
	{
		tileMapView->move(std::round(cameraSpeed * dt), 0.f);
	}
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
				mousePosGrid.x * gridSize,
				mousePosGrid.y * gridSize);
	}

	std::stringstream cursorString;
	cursorString <<
			mousePosView.x << ' ' << mousePosView.y << '\n' <<
			mousePosGrid.x << ' ' <<
			mousePosGrid.y << '\n' <<
			"Type: " << Tile::to_string(type) << '\n' <<
			"Closeness: " << Tile::to_string(closeness) << '\n' <<
			"Crossable: " << std::boolalpha << crossable << '\n';

	cursorText.setString(cursorString.str());
	cursorText.setPosition(mousePosView.x, mousePosView.y - 80.f);

	textureSelector->update(mousePosWindow);
}

void EditorState::updateButtons()
{
	/* Updates all the buttons in the state and handles their functionalities */
	for (auto &it : buttons)
	{
		it.second->update(mousePosWindow);
	}
}

void EditorState::updatePauseMenu()
{
	pauseMenu->update(mousePosWindow);

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

	target->setView(*tileMapView);
	tileMap->render(*target, Tile::Closeness::Background);
	tileMap->render(*target, Tile::Closeness::Foreground);

	renderGUI(target);
	renderButtons(target);

	if (paused)
	{
		// Pause menu render
		target->setView(target->getDefaultView());
		pauseMenu->render(*target);
	}
}

void EditorState::renderGUI(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->setView(*tileMapView);
	target->draw(selectorRect);

	target->setView(target->getDefaultView());
	target->draw(sidebar);
	textureSelector->render(*target);

	target->setView(*tileMapView);
	target->draw(cursorText);
}

void EditorState::renderButtons(std::shared_ptr<sf::RenderTarget> target)
{
	if (!target)
		target = window;

	target->setView(target->getDefaultView());

	for (auto &it : buttons)
	{
		it.second->render(*target);
	}
}

// Initialization functions
void EditorState::initVariables()
{
	cameraSpeed = 500.f;

	type = Tile::Type::Default;
	closeness = Tile::Closeness::Background;
	crossable = true;
}

void EditorState::initView()
{
	tileMapView = std::make_shared<sf::View>();

	tileMapView->setSize(
			graphicsSettings->resolution.width,
			graphicsSettings->resolution.height);

	tileMapView->setCenter(
			graphicsSettings->resolution.width / 2,
			graphicsSettings->resolution.height / 2);
}

void EditorState::initBindings()
{
	std::ifstream ifs;

	ifs.open("Config/Keybinds/EditorState.ini");

	if (ifs.is_open())
	{
		std::string action, key;

		while (ifs >> action >> key)
		{
			keybinds[action].setType(InputButton::Type::keyboardKey);
			keybinds[action].setCode((*supportedKeys)[key]);
		}
	}

	ifs.close();

	ifs.open("Config/Mousebinds/EditorState.ini");

	if (ifs.is_open())
	{
		std::string action, button;

		while (ifs >> action >> button)
		{
			mousebinds[action].setType(InputButton::Type::mouseButton);
			mousebinds[action].setCode((*supportedMouseButtons)[button]);
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
	tileMap.reset(new DefaultMap(
			sf::Vector2u(12, 8), 3,
			stateData.gridSize,
			"Villages.png",
			32,
			textures,
			font));

	tileMap->setEditorMode(true);
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
