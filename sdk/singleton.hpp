#pragma once

namespace sdk
{
	template <typename T>
	class singleton
	{
	public:
		static T &instance() { return instance_; }

	private:
		static T instance_;
	};

	template <typename T>
	inline T singleton<T>::instance_;
}