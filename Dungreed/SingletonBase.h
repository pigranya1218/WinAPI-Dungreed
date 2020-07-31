#pragma once

template <typename T>
class SingletonBase
{
protected:
	static T* singleton;

	SingletonBase() {}
	~SingletonBase() {}
public:
	static T* getSingleton();
	void releaseSingleton();
};

template <typename T>
T* SingletonBase<T>::singleton = 0;

template<typename T>
inline T * SingletonBase<T>::getSingleton()
{
	if (!singleton) singleton = new T;

	return singleton;
}

template<typename T>
inline void SingletonBase<T>::releaseSingleton()
{
	if (singleton)
	{
		delete singleton;
		singleton = nullptr;
	}
}
