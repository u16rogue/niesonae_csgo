#pragma once

#define sdk_flag_use_vertex_rhw

#include <d3dx9.h>
#include <sdk/color.hpp>

#include <sdk/vertex.hpp>

#define sdk_gui_get_x(value) (static_cast<float>(static_cast<short>(value & 0xFFFF)))
#define sdk_gui_get_y(value) (static_cast<float>(static_cast<short>(value >> 16   )))

#ifdef sdk_flag_use_vertex_rhw
	namespace sdk::gui { using vertex_t = sdk::vertex_ut_t; }
	#define sdk_gui_make_vertex(x, y, color) { x, y, 0.f, 1.f, color }
#else
	namespace sdk::gui { using vertex_t = sdk::vertex_wt_t; }
	#define sdk_gui_make_vertex(x, y, color) { x, y, 0.f, color }
#endif

#define sdk_gui_make_tlist_square(x, y, width, height, color) \
	sdk_gui_make_vertex(x, y, color), \
	sdk_gui_make_vertex(x, y + height, color), \
	sdk_gui_make_vertex(x + width, y + height, color), \
	sdk_gui_make_vertex(x, y, color), \
	sdk_gui_make_vertex(x + width, y, color), \
	sdk_gui_make_vertex(x + width, y + height, color)

#define sdk_gui_vertex_count_tlist(vertices) (sizeof(vertices) / sizeof(sdk::gui::vertex_t) / 3)

namespace sdk::gui
{
	using style          = unsigned long;
	using type_id        = unsigned long;
	using contracted_pos = unsigned long long;

	struct updateinfo_t
	{
		sdk::uint32_t message;
		sdk::uint32_t argument;
	};

	struct pos2d_t
	{
		pos2d_t() : x(0.f), y(0.f) {}
		pos2d_t(float x_, float y_) : x(x_), y(y_) {}
		pos2d_t(sdk::uint32_t contracted32) : x(sdk_gui_get_x(contracted32)), y(sdk_gui_get_y(contracted32)) {}

		float x { 0.f }, y { 0.f };
	};

	struct size2d_t
	{
		size2d_t() : width(0.f), height(0.f) {}
		size2d_t(float width_, float height_) : width(width_), height(height_) {}
		size2d_t(unsigned long contracted32) : width(static_cast<float>(contracted32 >> 16)), height(static_cast<float>(contracted32 & 0xFFFF)) {}

		float width, height;
	};

	namespace type_ids
	{
		constexpr gui::type_id control_base = 0;
		constexpr gui::type_id same_line    = 1;
		constexpr gui::type_id next_line    = 2;
	}

	class control_base
	{
	public:
		control_base() = default;
		control_base(float x_, float y_, float z_, float width_, float height_) : position(gui::pos2d_t(x_, y_)), size(gui::size2d_t(width_, height_)) {}
		control_base(gui::pos2d_t pos_, gui::size2d_t size_) : position(pos_), size(size_) {}
		control_base(sdk::gui::control_base **focus_ptr_custom) : focus_ptr_group(focus_ptr_custom) {}

	public:
		void set_focus()
		{
			*this->focus_ptr_group = this;
		}

		bool is_focused()
		{
			return *this->focus_ptr_group == this;
		}

	public:
		virtual bool init(float scale)               { return true; }
		virtual void render()                        { return; }
		virtual bool update(gui::updateinfo_t *info) { return false; }
		virtual sdk::gui::type_id get_control_type() { return gui::type_ids::control_base; };
		
	public:
		bool active  = true;
		bool visible = true;

		gui::pos2d_t  position;
		gui::size2d_t size;
		
		sdk::color color_primary;
		sdk::color color_primary_variant;

		sdk::color color_secondary;
		sdk::color color_secondary_variant;

		sdk::color color_border;

		gui::type_id type_id = gui::type_ids::control_base;
		
		gui::control_base *parent = nullptr;

		private: inline static float  default_alpha_multiplier = 1.f;
		public:  float               *alpha_multiplier_group   = &default_alpha_multiplier;

		// allows the control to have a different focus group. eg. controls on a different window, override this pointer to set a different focus group
		private: inline static sdk::gui::control_base *default_focus_ptr = nullptr;
		public:	 sdk::gui::control_base              **focus_ptr_group   = &default_focus_ptr;
		
	public:
		inline static IDirect3DDevice9 *rdevice = nullptr;
		inline static LPD3DXSPRITE      rsprite = nullptr;
	};
}