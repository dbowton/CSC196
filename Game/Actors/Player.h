#pragma once
#include "Base/Actor.h"

class Player : public dwb::Actor 
{
public:
	Player(const dwb::Transform& transform, std::shared_ptr<dwb::Shape> shape, float speed);

	void Initialize() override;

	void Update(float dt) override;
	void onCollision(Actor* actor) override;


public:
	int getHealth() { return health; }

private:
	int health = 0;
	float fireTimer{ 0.5f };
	float fireRate{ .5f };
	float speed{ 300 };
	dwb::Vector2 velocity;
};