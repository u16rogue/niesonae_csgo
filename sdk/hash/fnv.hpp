#pragma once

namespace sdk::hash
{
	using fnv64_t          = unsigned long long;
	using fnv32_t          = unsigned long;
	using fnv_contracted_t = unsigned long long;

	constexpr fnv64_t fnv64_offset = 0xcbf29ce484222325;
	constexpr fnv64_t fnv64_prime  = 0x00000100000001B3;

	constexpr fnv32_t fnv32_offset = 0x811c9dc5;
	constexpr fnv32_t fnv32_prime  = 0x01000193;

	template <typename T>
	constexpr fnv64_t fnv64(const T *data)
	{
		fnv64_t result = fnv64_offset;

		while (*data)
			result = (result * fnv64_prime) ^ *data++;

		return result;
	}
	
	template <typename T>
	constexpr fnv64_t fnv64(const T *data, size_t len)
	{
		fnv64_t result = fnv64_offset;

		while (*data && len-- > 0)
			result = (result * fnv64_prime) ^ *data++;

		return result;
	}

	template <typename T>
	constexpr fnv32_t fnv32(const T *data)
	{
		fnv32_t result = fnv32_offset;

		while (*data)
			result = (result * fnv32_prime) ^ *data++;

		return result;
	}
	
	template <typename T>
	constexpr fnv32_t fnv32(const T *data, size_t len)
	{
		fnv32_t result = fnv32_offset;

		while (*data && len-- > 0)
			result = (result * fnv32_prime) ^ *data++;

		return result;
	}

	template <typename T1, typename T2>
	constexpr fnv_contracted_t fnv_contracted(const T1 *data1, const T2 *data2)
	{
		return (static_cast<sdk::hash::fnv_contracted_t>(sdk::hash::fnv32(data1)) << 32) | sdk::hash::fnv32(data2);
	}
}

#define sdk_fnv64_cx(data) [] () -> sdk::hash::fnv64_t \
{ \
	constexpr sdk::hash::fnv64_t result = sdk::hash::fnv64(data);\
	return result; \
} ()

#define sdk_fnv32_cx(data) [] () -> sdk::hash::fnv32_t \
{ \
	constexpr sdk::hash::fnv32_t result = sdk::hash::fnv32(data); \
	return result; \
} ()

#define sdk_fnv_contracted_cx(data1, data2) [] () -> sdk::hash::fnv_contracted_t \
{ \
	constexpr sdk::hash::fnv_contracted_t result = sdk::hash::fnv_contracted(data1, data2); \
	return result; \
} ()

#define sdk_fnv_contracted_len_cx(name) [] () -> sdk::hash::fnv_contracted_t \
{ \
	constexpr sdk::hash::fnv_contracted_t result = ( (static_cast<sdk::hash::fnv_contracted_t>(sdk::hash::fnv32(name)) << 32 ) | static_cast<sdk::size32_t>(sizeof(name) - 1) ); \
	return result; \
} ()

#define sdk_fnv_contracted_hi(hashed) ( static_cast<sdk::hash::fnv32_t>(hashed >> 32) )
#define sdk_fnv_contracted_lo(hashed) ( static_cast<sdk::hash::fnv32_t>(hashed & 0xFFFFFFFF) )