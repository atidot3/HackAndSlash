//***********************************************************************************
//
//	File		:	NtlMutex.h
//
//	Begin		:	2005-11-30
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	Mutex ����ȭ ������Ʈ Ŭ����
//
//***********************************************************************************

#ifndef __NTLMUTEX_H__
#define __NTLMUTEX_H__

// Mutex Class
class CNtlMutex
{
public:
	CNtlMutex(DWORD dwSpinCount = 4000);

	virtual ~CNtlMutex();

	void				Lock();

	void				Unlock();

	CRITICAL_SECTION *	GetRealMutex();

private:

	CRITICAL_SECTION	m_mutex;
};

// Mutex helper class ( ����� �ڵ� ���� )
class CNtlAutoMutex
{
public:
	CNtlAutoMutex(CNtlMutex * pMutex);

	virtual ~CNtlAutoMutex(void);


	void				Lock();

	void				Unlock();

private:

	CNtlMutex *			m_pMutex;

	bool				m_bLocked;
};


inline CNtlMutex::CNtlMutex(DWORD dwSpinCount)
{
	::InitializeCriticalSectionAndSpinCount( &m_mutex, dwSpinCount );
}

inline CNtlMutex::~CNtlMutex()
{
	::DeleteCriticalSection( &m_mutex );
}

inline void CNtlMutex::Lock()
{
	::EnterCriticalSection( &m_mutex );
}

inline void CNtlMutex::Unlock()
{
	::LeaveCriticalSection( &m_mutex );
}

inline CRITICAL_SECTION * CNtlMutex::GetRealMutex()
{
	return &m_mutex;
}


inline CNtlAutoMutex::CNtlAutoMutex(CNtlMutex *pMutex)
:m_pMutex( pMutex ), m_bLocked( false )
{
}

inline CNtlAutoMutex::~CNtlAutoMutex()
{
	Unlock();
}

inline void CNtlAutoMutex::Lock()
{
	if( !m_bLocked )
	{
		m_pMutex->Lock();
		m_bLocked = true;
	}
}

inline void CNtlAutoMutex::Unlock()
{
	if( m_bLocked )
	{
		m_bLocked = false;
		m_pMutex->Unlock();
	}
}

#endif // __NTLMUTEX_H__
