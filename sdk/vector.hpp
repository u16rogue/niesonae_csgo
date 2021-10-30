#pragma once

#include "types.hpp"

namespace sdk
{
	class vector
	{
	public:
		float x, y, z;

	public:
		void operator=(const vector &other)
		{
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
		}
	};

	class vector2d
	{
	public:
		float x, y;

	public:
		void operator=(const vector2d &other)
		{
			this->x = other.x;
			this->y = other.y;
		}
	};
}