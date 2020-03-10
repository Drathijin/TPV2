#pragma once
#include "ecs.h"
#include "Entity.h"
#include "ImageComponent.h"
#include "ObjectPool.h"
#include "Singleton.h"
#include "LifeTime.h"
#include "Transform.h"


class AsteroidsPool : public Singleton<AsteroidsPool> {
	friend Singleton<AsteroidsPool>;
public:
	virtual ~AsteroidsPool() {
	}

	template<typename ...Targs>
	inline static Entity* construct(Targs&&...args) {
		return AsteroidsPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p) {
		AsteroidsPool::instance()->destroy_(p);
	}

	inline Entity* construct_(double x, double y, double w, double h, double r, Uint32 generations=3) {
		Entity* e = pool_.getObj();
		if (e != nullptr) {
			e->setActive(true);
			Transform* tr = e->getComponent<Transform>(ecs::Transform);
			tr->position_.set(x, y);
			tr->width_ = w;
			tr->height_ = w;
			tr->rotation_ = r;

			AsteroidLifeTime* at = e->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime);
			at->generations_ = generations;
		}
		return e;
	}

	inline void destroy_(Entity* p) {
		pool_.relObj(p);
	}

private:
	AsteroidsPool() :
		AsteroidsPool(10) {
	}
	AsteroidsPool(std::size_t n) :
		pool_(n) {
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<AsteroidLifeTime>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Asteroid));
		}
	}

	ObjectPool<Entity> pool_;
};

