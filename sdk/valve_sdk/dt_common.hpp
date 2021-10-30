#pragma once

#include <sdk/types.hpp>

namespace sdk::valve
{
	typedef enum
	{
		DPT_Int = 0,
		DPT_Float,
		DPT_Vector,
		DPT_VectorXY,
		DPT_String,
		DPT_Array,
		DPT_DataTable,
		DPT_Int64,
		DPT_NUMSendPropTypes
	} SendPropType;
	
	class DVariant
	{
	public:
		union
		{
			float        m_Float;
			long	     m_Int;
			char        *m_pString;
			void        *m_pData;
			float	     m_Vector[3];
			sdk::int64_t m_Int64;
		};

		SendPropType	 m_Type;
	};
}