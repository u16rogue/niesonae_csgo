#pragma once

namespace sdk::valve
{
	class IClientEntityList
	{
		class IClientEntity;

	private:

		virtual void pad_0(void) = 0;
		virtual void pad_1(void) = 0;
		virtual void pad_2(void) = 0;
	public:

		virtual IClientEntity *GetClientEntity(int entnum) = 0;
		virtual IClientEntity *GetClientEntityFromHandle(int entnum) = 0;
		virtual int NumberOfEntities(bool bIncludeNonNetworkable) = 0;
		virtual int GetHighestEntityIndex(void) = 0;
	private:

		virtual void pad_7(void) = 0;
		virtual void pad_8(void) = 0;
		virtual void pad_9(void) = 0;
	};
}