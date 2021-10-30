#pragma once

#include <array>
#include <sdk/types.hpp>
#include <sdk/winternal/environment.hpp>
#include <sdk/utils/hex.hpp>

namespace sdk::sig
{
    struct cache_section
    {
        sdk::byte_t value { 0x0 };
        bool        mask { false };
    };
    
    template <sdk::size_t pattern_count>
    constexpr std::array<sdk::sig::cache_section, pattern_count> cache(const char *signature)
    {
        std::array<sdk::sig::cache_section, pattern_count> cache { };
        
        for (int idx = 0; idx < pattern_count; idx++)
        {
            if (signature[idx * 3] == '?')
                continue;

            cache[idx].value = (hexchar_to_byte(signature[idx * 3]) << 4 ) | hexchar_to_byte(signature[idx * 3 + 1]);
            cache[idx].mask  = true;
        }
    
        return cache;
    }

    template <typename T>
    T *scan(sdk::ptr_t base, sdk::size32_t size, sdk::sig::cache_section *cached_sig, sdk::size_t pattern_count)
    {
        sdk::ptr_t current = base;
        sdk::ptr_t end = base + size;

        while (current <= end)
        {
            for (sdk::size_t idx = 0; idx < pattern_count; idx++)
            {
                if (cached_sig[idx].mask == false)
                    continue;

                if (cached_sig[idx].value != static_cast<sdk::byte_t>(current[idx]))
                    break;

                if (idx == pattern_count - 1)
                    return reinterpret_cast<T *>(current);
            }

            if (++current + pattern_count > end)
                return nullptr;
        }

        return nullptr;
    }

    template <typename T>
    T *scan(sdk::env::structs::PLDR_DATA_TABLE_ENTRY ldr, sdk::sig::cache_section *cached_sig, sdk::size_t pattern_count)
    {
        return sdk::sig::scan<T>(ldr->DllBase, ldr->SizeOfImage, cached_sig, pattern_count);
    }
}

#define sdk_sig_cache_cx(pattern) [] () -> std::array<sdk::sig::cache_section, sizeof(pattern) / 3> \
{ \
    static_assert((sizeof(pattern) % 3) == 0, "Invalid pattern count!"); \
    constexpr std::array<sdk::sig::cache_section, sizeof(pattern) / 3> result = sdk::sig::cache<sizeof(pattern) / 3>(pattern); \
    return result; \
} ()

#define sdk_sig_cache_as_arg_cx(pattern) sdk_sig_cache_cx(pattern).data(), sizeof(pattern) / 3