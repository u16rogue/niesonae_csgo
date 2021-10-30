#pragma once

#include <vector>
#include "control_base.hpp"

namespace sdk::gui
{
	namespace type_ids
	{
		constexpr gui::type_id canvas = 3;
	}

	class canvas : public control_base
	{
	public:
		struct style_enum
		{
			enum
			{
				NONE       = 0,
				OUTLINE    = 1 << 0,
				BACKGROUND = 1 << 1,
			};
		};

	public:
		canvas(const wchar_t *title_) : title(title_)
		{

		}

		bool init(float scale)
		{
			for (gui::control_base *control : this->child)
				if (!control->init(scale))
					return false;

			return true;
		}

		void render()
		{
			
		}

		bool update(gui::updateinfo_t *info)
		{
			return false;
		}

		sdk::gui::type_id get_control_type() { return gui::type_ids::canvas; }

	public:
		const wchar_t                    *title        = nullptr;
		std::vector<gui::control_base *>  child        = {};
		gui::style						  canvas_style = gui::canvas::style_enum::NONE;
	};
}