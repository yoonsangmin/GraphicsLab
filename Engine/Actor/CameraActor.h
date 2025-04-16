#pragma once

#include "Actor.h"

namespace GraphicsEngine
{
	class CameraActor : public Actor
	{
	public:
		CameraActor();

		virtual void Tick(float deltaTime) override;

	private:
		void Move(float deltaTime);
		void Rotate(float deltaTime);
	};
}

