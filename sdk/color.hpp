#pragma once

#include <math.h>
#include "types.hpp"
#include "math_cx.hpp"
#include "utils/hex.hpp"

namespace sdk
{
	using color_raw = unsigned long;

	union color
	{
		
		color() : r(0), g(0), b(0), a(255) {}
		color(sdk::color_raw raw_) : raw(raw_) {}
		color(sdk::byte_t r_, sdk::byte_t g_, sdk::byte_t b_) : r(r_), g(g_), b(b_), a(255) {}
		color(sdk::byte_t r_, sdk::byte_t g_, sdk::byte_t b_, sdk::byte_t a_) : r(r_), g(g_), b(b_), a(a_) {}

		struct
		{
			sdk::byte_t b;
			sdk::byte_t g;
			sdk::byte_t r;
			sdk::byte_t a;
		};

		color operator%(float alpha_multiplier)
		{
			return sdk::color(this->r, this->g, this->b, static_cast<sdk::byte_t>(this->a * alpha_multiplier));
		}

		color operator*(float rgba_multiplier)
		{

		}

		sdk::color_raw raw;

		template <typename T>
		inline static sdk::color rrgb(T clock, float rate = .0005f)
		{
			float clock_rate = clock * rate;
			return sdk::color
			(
				static_cast<sdk::byte_t>((sinf(clock_rate)                        * .5f + .5f) * 255),
				static_cast<sdk::byte_t>((sinf(clock_rate + 2 * sdk::mcx::pi / 3) * .5f + .5f) * 255),
				static_cast<sdk::byte_t>((sinf(clock_rate + 4 * sdk::mcx::pi / 3) * .5f + .5f) * 255)
			);
		}

		template <typename T>
		inline static sdk::color rrgba(T clock, float rate = .0005f, float rate_alp = 0.005f)
		{
			float clock_rate = clock * rate;

			return sdk::color
			(
				static_cast<sdk::byte_t>((sinf(clock_rate)                          * .5f + .5f) * 255),
				static_cast<sdk::byte_t>((sinf(clock_rate   + 2 * sdk::mcx::pi / 3) * .5f + .5f) * 255),
				static_cast<sdk::byte_t>((sinf(clock_rate   + 4 * sdk::mcx::pi / 3) * .5f + .5f) * 255),
				static_cast<sdk::byte_t>((sinf(clock * rate_alp + sdk::mcx::pi / 3) * .5f + .5f) * 255)
			);
		}
	};
}