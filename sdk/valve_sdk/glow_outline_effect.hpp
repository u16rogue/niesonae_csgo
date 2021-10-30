#pragma once

#include <sdk/color.hpp>
#include <sdk/types.hpp>
#include <sdk/vector.hpp>
#include <sdk/angle.hpp>
#include "utlvector.hpp"
#include "c_baseentity.hpp"

namespace sdk::valve
{
	enum class GlowRenderStyle
	{
		GLOWRENDERSTYLE_DEFAULT = 0,
		GLOWRENDERSTYLE_RIMGLOW3D,
		GLOWRENDERSTYLE_EDGE_HIGHLIGHT,
		GLOWRENDERSTYLE_EDGE_HIGHLIGHT_PULSE,
		GLOWRENDERSTYLE_COUNT,
	};

	struct GlowColor
	{

		GlowColor(float r_, float g_, float b_) : r(r_), g(g_), b(b_), a(1.f) {}
		GlowColor(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) {}

		float r, g, b, a;

		void operator=(sdk::color &other)
		{
			this->r = static_cast<float>(other.r);
			this->g = static_cast<float>(other.g);
			this->b = static_cast<float>(other.b);
			this->a = static_cast<float>(other.a);
		}
	};

	class CGlowObjectManager
	{
	public:
		struct GlowObjectDefinition
		{
			sdk::valve::C_BaseEntity *m_pEntity;
			GlowColor                 m_vGlowColor;
			//float                     m_flGlowAlpha;
			bool                      m_bGlowAlphaCappedByRenderAlpha;
			float                     m_flGlowAlphaFunctionOfMaxVelocity;
			float                     m_flGlowAlphaMax;
			float                     m_flGlowPulseOverdrive;
			bool                      m_bRenderWhenOccluded;
			bool                      m_bRenderWhenUnoccluded;
			bool                      m_bFullBloomRender;
			int                       m_nFullBloomStencilTestValue;
			GlowRenderStyle           m_nRenderStyle;
			int                       m_nSplitScreenSlot;
			int                       m_nNextFreeSlot;

			static const int END_OF_FREE_LIST = -1;
			static const int ENTRY_IN_USE     = -2;
		};

		struct GlowBoxDefinition
		{
			sdk::vector m_vPosition;
			sdk::angle  m_angOrientation;
			sdk::vector m_vMins;
			sdk::vector m_vMaxs;
			float       m_flBirthTimeIndex;
			float       m_flTerminationTimeIndex;
			sdk::color  m_colColor;
		};

		sdk::valve::CUtlVector<GlowObjectDefinition> m_GlowObjectDefinitions;
		int                                          m_nFirstFreeSlot;
		sdk::valve::CUtlVector<GlowBoxDefinition>    m_GlowBoxDefinitions;
	};
}
