#pragma once
#include <functional>

template <class C>
class Getter
{
public:
	Getter(C* pValue) : Getter(pValue, [this]() { return *m_pValue; }) {}
	Getter(C* pValue, std::function<C()> get) { m_pValue = pValue; m_get = get; }

	operator C () const { return m_get(); }
private:
	C* m_pValue;
	std::function<C()> m_get;
};

template <class C>
class Setter
{
public:
	Setter(C* pValue) : Setter(pValue, [this](const C& value) { *m_pValue = value; }) {}
	Setter(C* pValue, std::function<void(const C&)> set) { m_pValue = pValue; m_set = set; }

	void operator=(const C& value) const { m_set(value); }
private:
	C* m_pValue;
	std::function<void(const C&)> m_set;
};

template <class C>
class GetSet
{
public:
	GetSet(C* pValue) : GetSet(pValue,
		[this]() { return *m_pValue; },
		[this](const C& value) { *m_pValue = value; })
	{
	}
	GetSet(C* pValue, std::function<C()> get, std::function<void(const C&)> set)
	{
		m_pValue = pValue;
		m_get = get;
		m_set = set;
	}

	operator const C& () const { return *m_pValue; }
	const C& operator=(const C& value) const { *m_pValue = value; return *m_pValue; }
private:
	C* m_pValue;
	std::function<C()> m_get;
	std::function<void(const C&)> m_set;
};
