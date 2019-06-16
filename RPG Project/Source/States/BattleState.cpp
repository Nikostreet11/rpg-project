/*
 * BattleState.cpp
 *
 *  Created on: Jun 16, 2019
 *      Author: Nikostreet11
 */

#include "BattleState.hpp"

BattleState::BattleState(StateData& stateData) :
		State(stateData)
{
}

BattleState::~BattleState()
{
}

void BattleState::endState()
{
}

void BattleState::update(const float& dt)
{
}

void BattleState::updateInput(const float& dt)
{
}

void BattleState::updatePlayerInput(const float& dt)
{
}

void BattleState::updatePauseMenu()
{
}

void BattleState::render(std::shared_ptr<sf::RenderTarget> target)
{
}

void BattleState::initDeferredRendering()
{
}

void BattleState::initKeybinds()
{
}

void BattleState::initFonts()
{
}

void BattleState::initTextures()
{
}

void BattleState::initPlayers()
{
}

void BattleState::initPauseMenu()
{
}
