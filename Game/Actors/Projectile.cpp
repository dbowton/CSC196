#include "Projectile.h"
#include "Math/MathUtils.h"
#include "Engine.h"

void Projectile::Update(float dt)
{
	Actor::Update(dt);

	lifetime -= dt;
	destroy = (lifetime <= 0);

	transform.position += (dwb::Vector2::Rotate(dwb::Vector2::right, transform.rotation) * speed) * dt;
	transform.position.x = dwb::Wrap(transform.position.x, 0.0f, 800.0f);
	transform.position.y = dwb::Wrap(transform.position.y, 0.0f, 600.0f);

	std::vector<dwb::Color> colors = { dwb::Color::white, dwb::Color::red, dwb::Color::green, dwb::Color::blue, dwb::Color::magenta, dwb::Color::cyan, dwb::Color::orange, dwb::Color::yellow };
	scene->engine->Get<dwb::ParticleSystem>()->Create(transform.position, 15, .5f, colors[dwb::RandomRangeInt(0, colors.size())], 150);
}