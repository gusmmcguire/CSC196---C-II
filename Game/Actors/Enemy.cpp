#include "Enemy.h"
#include "Player.h"
#include "Projectile.h"
#include "Engine.h"

void Enemy::Update(float dt) {
	Actor::Update(dt);

	//Fire();

	gme::Vector2 acceleration;
	acceleration = gme::Vector2::Rotate(gme::Vector2::right, transform.rotation) * speed;

	velocity += acceleration * dt;

	if (transform.position.y > 500.0f || transform.position.y < 100.0f || transform.position.x > 700.0f || transform.position.x < 200.0f) {
		velocity = -velocity;
		transform.rotation += gme::Pi;
		Fire();
	}
	transform.position +=  velocity;
	velocity *= .93f;


	transform.position.x = gme::Clamp(transform.position.x, 0.0f, 800.0f);
	transform.position.y = gme::Clamp(transform.position.y, 0.0f, 600.0f);

}

void Enemy::Fire()
{
	std::shared_ptr<gme::Shape> shape = std::make_shared<gme::Shape>();
	shape->Load("bullet.txt");
	gme::Transform t = transform;
	t.scale = 0.5f;
	std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(transform, shape, 1000.0f);
	projectile->tag = "Enemy";
	scene->AddActor(std::move(projectile));
}

void Enemy::OnCollision(Actor* actor){
	if (dynamic_cast<Projectile*>(actor) && actor->tag == "Player") {
		scene->engine->Get<gme::AudioSystem>()->PlayAudio("explosion");
		scene->engine->Get<gme::ParticleSystem>()->Create(transform.position, 200, 1, gme::Color::orange, 50);
		destroy = true;
		actor->destroy = true;
	}
}

