#include "Player.h"
#include "Projectile.h"
#include "Math/MathUtils.h"
#include "Enemy.h"
#include <memory>

#include "Engine.h"

Player::Player(const dwb::Transform& transform, std::shared_ptr<dwb::Shape> shape, float speed) : dwb::Actor{ transform, shape }, speed{ speed } 
{
	health = 500;
}

void Player::Initialize()
{
	{
		std::unique_ptr exhaust = std::make_unique<Actor>();
		exhaust->transform.localPosition = { -4, 0 };
		exhaust->transform.localRotation = dwb::DegToRad(180);
		AddChild(std::move(exhaust));
	}

	{
		std::unique_ptr pewPoint = std::make_unique<Actor>();
		pewPoint->transform.localPosition = { 3, 3 };
		AddChild(std::move(pewPoint));

		pewPoint = std::make_unique<Actor>();
		pewPoint->transform.localPosition = { 3, -3 };
		AddChild(std::move(pewPoint));
	}
}

void Player::Update(float dt)
{
	Actor::Update(dt);
	//children[3]->transform.localRotation += 5 * dt;

	//move
	float thrust;
	if (Core::Input::IsPressed('W')) 
	{ 
		if (speed < 100) speed = 100;
		if (speed < 400) speed *= 1.01f;
	}
	else if (Core::Input::IsPressed('S') && speed > 250)
	{
		speed *= .9f;
	}
	else if(speed >= 400)
	{
		speed *= 0.99f;
	}
	thrust = speed;

	if (Core::Input::IsPressed('A')) transform.rotation -= (2 * dt);
	if (Core::Input::IsPressed('D')) transform.rotation += (2 * dt);


	if (Core::Input::IsPressed('R')) {
		transform.position.x = 400;
		transform.position.y = 300;
		speed = 300;
	}

	dwb::Vector2 acceleration;
	
	acceleration = (dwb::Vector2::Rotate(dwb::Vector2::right, transform.rotation) * thrust);
	//dwb::Vector2 gravity = (dwb::Vector2{ 400, 300 } - transform.position).Normalized() * 200;
	/*dwb::Vector2 gravity = dwb::Vector2::down * 50;
	acceleration += gravity;*/
	
	
	velocity += acceleration * dt;
	transform.position += velocity * dt;
	velocity *= .99f;

	transform.position.x = dwb::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = dwb::Wrap(transform.position.y, 0.0f, 600.0f);

	//fire
	fireTimer -= dt;
	if (fireTimer <= 0 && Core::Input::IsPressed(VK_SPACE))
	{
		fireTimer = fireRate;

		{
			dwb::Transform t = children[1]->transform;
			t.scale = 0.5f;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Shape>("Player_Projectile.txt"), 600.0f);
			projectile->tag = "Player";

			scene->addActor(std::move(projectile));

			speed *= 0.95f;
		}

		{
			dwb::Transform t = children[2]->transform;
			t.scale = 0.5f;

			std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(t, scene->engine->Get<dwb::ResourceSystem>()->Get<dwb::Shape>("Player_Projectile.txt"), 600.0f);
			projectile->tag = "Player";

			scene->addActor(std::move(projectile));

			speed *= 0.95f;
		}

		scene->engine->Get<dwb::AudioSystem>()->PlayAudio("Player_Fire");
	}

	std::vector<dwb::Color> colors = { dwb::Color::white, dwb::Color::blue, dwb::Color::red };

	scene->engine->Get<dwb::ParticleSystem>()->Create(children[0]->transform.position, 10, 1.0f, colors, 50, children[0]->transform.rotation, dwb::DegToRad(15));
}

void Player::onCollision(Actor* actor)
{
	if (dynamic_cast<Enemy*>(actor))
	{
		actor->destroy = true;

		scene->engine->Get<dwb::ParticleSystem>()->Create(transform.position, 200, 1, dwb::Color::red, 50);
		scene->engine->Get<dwb::AudioSystem>()->PlayAudio("explosion");
		scene->engine->Get<dwb::AudioSystem>()->PlayAudio("Enemy_Killed");

		health -= 200;
	}

	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Enemy")
	{
		actor->destroy = true;

		scene->engine->Get<dwb::ParticleSystem>()->Create(transform.position, 200, 1, dwb::Color::red, 50);
		scene->engine->Get<dwb::AudioSystem>()->PlayAudio("explosion");

		health -= 100;
	}

	if (health <= 0) {
		dwb::Event event;
		event.name = "PlayerDead";
		event.data = std::string("yes I am dead!");
		scene->engine->Get<dwb::EventSystem>()->Notify(event);

		health = 500;
	}
}