#pragma once
#pragma once
#include "ecs.h"
#include "Entity.h"
#include "ImageComponent.h"
#include "ObjectPool.h"
#include "Singleton.h"
#include "LifeTime.h"
#include "Transform.h"


class BulletsPool : public Singleton<BulletsPool> {
	friend Singleton<BulletsPool>;
public:
	virtual ~BulletsPool() {
	}

	template<typename ...Targs>
	inline static Entity* construct(Targs&&...args) {
		return BulletsPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p) {
		BulletsPool::instance()->destroy_(p);
	}

	inline Entity* construct_(double x, double y, double w, double h, double r) {
		Entity* e = pool_.getObj();
		if (e != nullptr) {
			e->setActive(true);
			Transform* tr = e->getComponent<Transform>(ecs::Transform);
			tr->position_.set(x, y);
			tr->width_ = w;
			tr->height_ = w;
			tr->rotation_ = r;
			tr->velocity_ = Vector2D(0, -1).rotate(r) * 5;
		}
		return e;
	}

	inline void destroy_(Entity* p) {
		pool_.relObj(p);
	}

private:
	BulletsPool() :
		BulletsPool(10) {
	}
	BulletsPool(std::size_t n) :
		pool_(n) {
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Bullet));
		}
	}

	ObjectPool<Entity> pool_;
};

