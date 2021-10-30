#pragma once

#include <d3dx9.h>
#include "color.hpp"

namespace sdk
{
	#define sdk_flag_dx9_vertex_ut (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
	struct vertex_ut_t
	{
		float x, y, z, w;
		sdk::color color;
	};

	#define sdk_flag_dx9_vertex_wt (D3DFVF_XYZ | D3DFVF_DIFFUSE)
	struct vertex_wt_t
	{
		float x, y, z;
		sdk::color color;
	};
}