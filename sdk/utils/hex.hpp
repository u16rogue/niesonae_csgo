#pragma once

namespace sdk
{
	namespace err
	{
		extern const char *hexchar_runtime_error;
	}

    constexpr sdk::byte_t hexchar_to_byte(const char &hex)
    {
        if (hex >= 'A' && hex <= 'F')
            return (hex - 'A') + 10;
        else if (hex >= '0' && hex <= '9')
            return hex - '0';
        else
            throw err::hexchar_runtime_error;
    }
}