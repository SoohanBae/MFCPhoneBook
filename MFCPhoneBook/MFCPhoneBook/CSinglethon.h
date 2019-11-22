#pragma once
#include <memory>

template < typename T >

class CSingleton
{
public:
	CSingleton() = default;

	virtual ~CSingleton() = default;

	static void CreateClass()
	{
		if (NULL == m_pMgr)
		{
			m_pMgr = new T;
		}
	}

	static void DestroyWnd()
	{
		if (m_pMgr)
		{
			m_pMgr->DestroyWindow();
			delete m_pMgr;
			m_pMgr = NULL;
		}
	}

	static void DestroyClass()
	{
		if (m_pMgr)
		{
			delete m_pMgr;
			m_pMgr = NULL;
		}
	}

	static T* GetMgr()
	{
		return m_pMgr;
	}

private:
	static T* m_pMgr;
};

template < typename T >

T* CSingleton< T >::m_pMgr = NULL;