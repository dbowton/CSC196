#pragma once
#include "Base/Actor.h"

class Enemy : public dwb::Actor
{
public:
	Enemy(const dwb::Transform& transform, std::shared_ptr<dwb::Shape> shape, float speed, bool canShoot) : dwb::Actor{ transform, shape }, speed{ speed }, canShoot{ canShoot } {}

	void Update(float dt) override;
	void onCollision(Actor* actor) override;

private:
	float speed{ 300 };
	bool canShoot{ false };
	float fireTimer{ 0 };
	float fireRate{ 1 };
};