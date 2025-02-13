#pragma once

#include "MassiveObject2D.h"
#include "pch.h"

namespace Motor
{
	class Planet2D : public MassiveObject2D
	{
	protected:
		const double m_Radius;

	public:
		Planet2D(double mass, Vec2<int> center, double radius, Vec2<double> initial_speed = Vec2<double>(0, 0), Vec2<double> initial_acceleration = Vec2<double>(0, 0));
		Planet2D(const Planet2D& planet);
		//Planet2D(Planet2D&& planet);

		~Planet2D();

		void Update(float ts) override;
		void OnRender() const override;

	private:
		// private methods
	};
}
