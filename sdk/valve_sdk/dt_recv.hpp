#pragma once

#include "dt_common.hpp"
#include "dt_recv.hpp"
#include "dt_recv_decoder.hpp"

namespace sdk::valve
{
	class RecvTable;
	class RecvProp;

	class CRecvProxyData
	{
	public:
		const RecvProp *m_pRecvProp;
		DVariant		m_Value;	
		int				m_iElement;	
		int				m_ObjectID;	
	};

	class RecvProp
	{
		using ArrayLengthRecvProxyFn  = void(*)(void *pStruct, int objectID, int currentArrayLength);           // typedef void (*ArrayLengthRecvProxyFn)( void *pStruct, int objectID, int currentArrayLength );
		using RecvVarProxyFn          = void(*)(const CRecvProxyData *pData, void *pStruct, void *pOut);        // typedef void (*RecvVarProxyFn)( const CRecvProxyData *pData, void *pStruct, void *pOut );
		using DataTableRecvVarProxyFn = void(*)(const RecvProp *pProp, void **pOut, void *pData, int objectID); // typedef void (*DataTableRecvVarProxyFn)(const RecvProp *pProp, void **pOut, void *pData, int objectID);

	public:

		char                    *m_pVarName;
		SendPropType			 m_RecvType;
		int						 m_Flags;
		int						 m_StringBufferSize;
		bool					 m_bInsideArray;
		const void              *m_pExtraData;
		RecvProp                *m_pArrayProp;
		ArrayLengthRecvProxyFn	 m_ArrayLengthProxy;
		RecvVarProxyFn			 m_ProxyFn;
		DataTableRecvVarProxyFn  m_DataTableProxyFn;
		RecvTable               *m_pDataTable;
		int						 m_Offset;
		int						 m_ElementStride;
		int						 m_nElements;
		const char              *m_pParentArrayPropName;
	};

	class RecvTable
	{
		using PropType = RecvProp;
	public:
		RecvProp       *m_pProps;
		int				m_nProps;
		CRecvDecoder   *m_pDecoder;
		char           *m_pNetTableName;
		bool			m_bInitialized;
		bool			m_bInMainList;
	};
}