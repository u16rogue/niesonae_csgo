#pragma once

#include "types.hpp"

namespace sdk
{
	class angle
	{
	public:
		float yaw, pitch, roll;

	public:
		void operator=(const angle &other)
		{
			this->yaw   = other.yaw;
			this->pitch = other.pitch;
			this->roll  = other.roll;
		}
	};
}