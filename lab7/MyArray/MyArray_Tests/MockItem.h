#pragma once
#include <map>

class CMockItem
{
public:
	CMockItem()
	{
		ms_registry[this] = true;
	}

	CMockItem(const CMockItem &other)
	{
		ms_registry[this] = ms_registry.at(std::addressof(other));
	}

	CMockItem &operator =(const CMockItem &other)
	{
		ms_registry[this] = ms_registry.at(std::addressof(other));
		return *this;
	}

	~CMockItem()
	{
		ms_registry.erase(this);
	}

	bool IsRegistered()
	{
		return ms_registry.at(this);;
	}

private:
	static std::map<const CMockItem*, bool> ms_registry;
};