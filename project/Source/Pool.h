#pragma once
#include <vector>
#include <functional>

template<class C>
class Pool
{
public:
	struct PoolObject
	{
		C* object;
		size_t index;
		bool inUse;
	};

	Pool(size_t size);
	~Pool();
	PoolObject Create();
	void InvokeOnAll(std::function<void(const PoolObject&)> func)
	{
		for (auto& obj : m_objects)
		{
			if (obj.inUse)
			{
				func(obj);
			}
		}
	}
private:
	std::vector<PoolObject> m_objects;
	size_t m_index;
};

template<class C>
inline Pool<C>::Pool(size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		PoolObject obj;
		obj.object = new C();
		obj.index = i;
		obj.inUse = false;
		m_objects.push_back(obj);
	}
	m_index = 0;
}

template<class C>
inline Pool<C>::~Pool()
{
	for (auto& obj : m_objects)
	{
		delete obj.object;
	}
	m_objects.clear();
}

template<class C>
inline typename Pool<C>::PoolObject Pool<C>::Create()
{
	if (m_index >= m_objects.size())
	{
		m_index = 0;
	}

	if (m_objects[m_index].inUse)
	{
		for (size_t i = 1; i < m_objects.size(); i++)
		{
			size_t idx = (m_index + i) % m_objects.size();

			if (!m_objects[idx].inUse)
			{
				m_index = idx;
				break;
			}
		}
	}

	m_objects[m_index].inUse = true;
	return m_objects[m_index++];
}
