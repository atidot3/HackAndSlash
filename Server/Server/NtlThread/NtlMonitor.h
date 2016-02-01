//***********************************************************************************
//
//	File		:	NtlMonitor.h
//
//	Begin		:	2005-11-30
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	Mutex(mutual exclusion)�� Event (signal and wait) Ư¡ ���� ����ȭ ��ü ȹ�濡 ���� ���� ������ �Ѵ�.
//
//***********************************************************************************

#ifndef __NTLMONITOR_H__
#define __NTLMONITOR_H__

#include "NtlLinkList.h"
#include "NtlMutex.h"

class CNtlThread;
class CNtlMonitor
{
public:
	CNtlMonitor(void);

	virtual ~CNtlMonitor(void);


private:

	CNtlMonitor(const CNtlMonitor &);

	CNtlMonitor & operator=(const CNtlMonitor &);


	void					Reset();


public:


	void					Lock();

	void					Unlock();

	bool					TryLock();

	void					Wait();

	bool					Wait(unsigned int millisecs);

	void					Notify();

	void					NotifyAll();


protected:

	void					Grant();


private:

	CNtlMutex				m_mutex;

	CNtlThread *			m_pOwner;

	int						m_nLockCount;

	CNtlLinkList			m_waitList; // ���� wait ���� ������ ����Ʈ

	CNtlLinkList			m_readyList; // ���� ������ ȹ���� ���� ����ϴ� ������ ����Ʈ

};

#endif // __NTLMONITOR_H__
