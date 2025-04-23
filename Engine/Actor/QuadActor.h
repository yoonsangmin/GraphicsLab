#pragma once

#include "Actor.h"

namespace GraphicsEngine
{
	class QuadActor : public Actor
	{
	public:
		QuadActor();
		~QuadActor() = default;

		virtual void Tick(float deltaTime) override;
	};
}
