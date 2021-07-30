#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"

void Game::Initialize()
{
	engine = std::make_unique<dwb::Engine>();
	engine->StartUp();
	scene = std::make_unique<dwb::Scene>();
	scene->engine = engine.get();

	engine->Get<dwb::AudioSystem>()->AddAudio("explosion", "explosion.wav");
	engine->Get<dwb::AudioSystem>()->AddAudio("Enemy_Killed", "Enemy_Killed.wav");
	engine->Get<dwb::AudioSystem>()->AddAudio("Player_Fire", "Player_Fire.wav");

	//stateFunction = &Game::UpdateTitle;

	engine->Get<dwb::EventSystem>()->Subscribe("AddPoints", std::bind(&Game::OnAddPoints, this, std::placeholders::_1));
	engine->Get<dwb::EventSystem>()->Subscribe("PlayerDead", std::bind(&Game::OnPlayerDead, this, std::placeholders::_1));
}

void Game::Shutdown()
{
	scene->removeAllActors();
	engine->ShutDown();
}

void Game::Update(float dt)
{
	stateTimer += dt;

	switch (state)
	{
	case Game::eState::Title:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			state = eState::StartGame;
		}
		break;
	case Game::eState::StartGame:
		score = 0;
		lives = 3;

		//Player	
		scene->addActor(std::make_unique<Player>(dwb::Transform{ dwb::Vector2{400.0f, 300.0f}, 0.0f, 5.0f }, engine->Get<dwb::ResourceSystem>()->Get<dwb::Shape>("Player_Body.txt"), 250.0f));


		state = eState::StartLevel;
		break;
	case Game::eState::StartLevel:
	{
		currentLevel++;
		UpdateLevelStart(dt);
		state = eState::Game;
		break;
	}
		break;
	case Game::eState::Game:
		
		if (scene->getActors<Enemy>().size() == 0 && currentLevel >= maxLevel)
		{
			state = eState::GameOver;
		}
		else if(scene->getActors<Enemy>().size() == 0)
		{
			state = eState::StartLevel;
		}
		break;
	case Game::eState::GameOver:
		break;
	default:
		break;
	}

	engine->Update(dt);
	scene->Update(dt);
}

void Game::Draw(Core::Graphics& graphics)
{
	switch (state)
	{
	case Game::eState::Title:
		graphics.SetColor(dwb::Color::red);
		graphics.DrawString(360, 300 + static_cast<int>(std::sin(stateTimer * 4) * 10), "GAME: The Game");

		graphics.SetColor(dwb::Color::green);
		graphics.DrawString(340, 360, "Press SPACE to Begin");
		break;
	case Game::eState::StartGame:
		break;
	case Game::eState::StartLevel:
		break;
	case Game::eState::Game:
		break;
	case Game::eState::GameOver:

		if (scene->getActors<Enemy>().size() == 0)
		{
			graphics.SetColor(dwb::Color::green);
			graphics.DrawString(340, 360, "VICTORY");
		}
		else
		{
			graphics.SetColor(dwb::Color::red);
			graphics.DrawString(340, 360, "Game Over :(");

			if(scene->getActor<Player>()) scene->getActor<Player>()->destroy = true;

		}
		break;
	default:
		break;
	}

	graphics.SetColor(dwb::Color::white);
	graphics.DrawString(30, 20, ("Level: " + std::to_string(currentLevel) + " / " + std::to_string(maxLevel)).c_str());
	graphics.DrawString(30, 35, ("Score: " + std::to_string(score)).c_str());

	if (scene->getActor<Player>())
	{
		graphics.DrawString(700, 20, ("Health: " + std::to_string(scene->getActor<Player>()->getHealth())).c_str());
	}
	graphics.DrawString(700, 35, ("Lives: " + std::to_string(lives)).c_str());

	scene->Draw(graphics);
	engine->Draw(graphics);
}

void Game::UpdateTitle(float dt)
{
	if (Core::Input::IsPressed(VK_SPACE))
	{
		stateFunction = &Game::UpdateLevelStart;
	}
}

void Game::UpdateLevelStart(float dt)
{		
	//Shooty Enemies
	for (int i = 0; i < 1 * (currentLevel + 1); i++)
	{
		scene->addActor(std::make_unique<Enemy>(dwb::Transform{ dwb::Vector2{dwb::RandomRange(0.0f, 800.0f), dwb::RandomRange(0.0f, 300.0f)}, dwb::RandomRange(0.0f, 800.0f), 4.0f }, engine->Get<dwb::ResourceSystem>()->Get<dwb::Shape>("Enemy_Shooter_Body.txt"), 100.0f, true));
	}
		
	//Non-Shooty Enemies
	for (int i = 0; i < 2 * (currentLevel + 1); i++)
	{
		scene->addActor(std::make_unique<Enemy>(dwb::Transform{ dwb::Vector2{dwb::RandomRange(0.0f, 800.0f), dwb::RandomRange(0.0f, 300.0f)}, dwb::RandomRange(0.0f, 800.0f), 4.0f }, engine->Get<dwb::ResourceSystem>()->Get<dwb::Shape>("Enemy_Body.txt"), 150.0f, false));
	}
}

void Game::OnAddPoints(const dwb::Event& event)
{
	score += std::get<int>(event.data);
}

void Game::OnPlayerDead(const dwb::Event& event)
{
	if (lives >= 1)
	{
		lives--;
	}

	std::cout << lives << std::endl;
	
	if (lives <= 0)
	{
		state = eState::GameOver;
	}
}