#pragma once

#define sdk_get_vfunc(type, base, index) (reinterpret_cast<type***>(base)[0][static_cast<int>(index)])