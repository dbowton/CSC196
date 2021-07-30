#pragma once
#include "Engine.h"

class Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		GameOver,
	};

public:
	void Initialize();
	void Shutdown();

	void Update(float dt);
	void Draw(Core::Graphics& graphics);

private:
	void UpdateTitle(float dt);
	void UpdateLevelStart(float dt);
	void OnAddPoints(const dwb::Event& event);
	void OnPlayerDead(const dwb::Event& event);

public:
	std::unique_ptr<dwb::Engine> engine;
	std::unique_ptr<dwb::Scene> scene;

private:
	eState state = eState::Title;
	float stateTimer = 0.0f;
	int currentLevel = 0;
	int maxLevel = 3;

	void (Game::* stateFunction)(float) = nullptr;

	size_t score = 0;
	size_t lives = 0;
};