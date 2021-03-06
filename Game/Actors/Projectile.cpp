#include "Projectile.h"
#include "Engine.h"

void Projectile::Initialize() {
	std::unique_ptr locator = std::make_unique<Actor>();
	locator->transform.localPosition = gme::Vector2{ -6,0 };
	addChild(std::move(locator));
}

void Projectile::Update(float dt) {
	Actor::Update(dt);

	lifetime -= dt;
	destroy = (lifetime <= 0) || (transform.position.x >= 800.0f) || (transform.position.y >= 600.0f) || (transform.position.x <= 0.0f) || (transform.position.y <= 0.0f);

	transform.position += gme::Vector2::Rotate(gme::Vector2::right, transform.rotation) * speed * dt;
	transform.position.x = gme::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gme::Clamp(transform.position.y, 0.0f, 600.0f);

	std::vector<gme::Color> colors{ gme::Color::white, gme::Color::red, gme::Color::green,gme::Color::blue, gme::Color::purple, gme::Color::cyan,gme::Color::orange,gme::Color::yellow };
	scene->engine->Get<gme::ParticleSystem>()->Create(children[0]->transform.position, 2, 0.25, colors, 75, children[0]->transform.rotation, gme::DegToRad(30));

	//scene->engine->Get<gme::ParticleSystem>()->Create(transform.position, 10, .5f, colors[gme::RandomRangeInt(0, colors.size())], 10);
}

void Projectile::OnCollisionBox(Actor* actor) {
	destroy = true;
}