#pragma once

#include "Base/Actor.h"

class Projectile : public dwb::Actor
{
public:
	Projectile(const dwb::Transform& transform, std::shared_ptr<dwb::Shape> shape, float speed) : dwb::Actor{ transform, shape }, speed{ speed } {}

	void Update(float dt) override;

private:
	float lifetime{ 2 };
	float speed{ 300 };
};