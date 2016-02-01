//***********************************************************************************
//
//	File		:	NtlThread.h
//
//	Begin		:	2005-11-30
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	NTL Thread Class
//
//***********************************************************************************

#ifndef __NTLTHREAD_H__
#define __NTLTHREAD_H__

#include "NtlLinkList.h"
#include "NtlString.h"
#include "NtlEvent.h"
#include "NtlMutex.h"


class CThreadKey;
class CThreadHelper;

//---------------------------------------------------------------------------------------
// CNtlRunObject : ������ ���� ��ü Ŭ����
//---------------------------------------------------------------------------------------
class CNtlRunObject
{
friend class CNtlThread;

public:

	CNtlRunObject()
		:m_arg(0), m_pOwner(0), m_bRunning(true) {}

	virtual ~CNtlRunObject() {}


public:

	// ������ ���α׷��� �� �Լ��� Override�Ͽ� Application Logic�� �ۼ�
	virtual void			Run() {}

	//
	virtual void			Close() { m_bRunning = false; }


public:

	// ������ �۾� ���� �� ������ ���� ���ҽ� ����
	void					Terminate();

	//
	void *					GetArg() const { return m_arg; }

	//
	void 					SetArg(void * arg) { m_arg = arg; }

	// ���� ������ ��ȯ
	CNtlThread *			GetThread() const { return m_pOwner; }

	// unconditional wait
	void					Wait();

	// conditional wait
	int						Wait(unsigned int millisecs);

	// ���� �����带 ����
	void					Exit();

	// ���� �������� �̸��� ��ȯ�Ѵ�
	const char *			GetName() const;

	//
	bool					IsRunnable() { return m_bRunning; }

	//
	void					SetRunnable(bool bRunning) { m_bRunning = bRunning; }


private:

	// ���� ������
	void					SetThread(CNtlThread * pOwner) { m_pOwner = pOwner; }


protected:

	void *					m_arg;

private:

	CNtlThread *			m_pOwner;

	bool					m_bRunning;

};


//---------------------------------------------------------------------------------------
// CNtlThread : ������ ��ü Ŭ����
//---------------------------------------------------------------------------------------
class CNtlThread : public CNtlLinkObject
{
friend class CThreadkey;
friend class CThreadHelper;
friend class CNtlThreadFactory;

public:

	// ������ ����
	enum STATUS
	{
		eSTATUS_NOT_RUNNING = 0,	// �������� �ʴ� ���� ( �ʱ� ���� )
		eSTATUS_PREPARING_TO_RUN,	// ���� �غ� ����
		eSTATUS_RUNNING,			// ���� ����
		eSTATUS_PAUSED,				// ���� ����
		eSTATUS_DEAD,				// ���� ����

		MAX_STATUS,
	};


public:

	// AutoDelete�� ��� RunObject�� �ݵ�� Heap�� �����ϰ� ����� ������ ��. 
	CNtlThread(CNtlRunObject * pRunObject, const char * name = "Unknown Thread", bool bAutoDelete = false);

	virtual ~CNtlThread(void);


private:

	CNtlThread(const CNtlThread &);

	void operator=(const CNtlThread &);


public:

	// Thread�� �����ϱ����� �ܺο��� ȣ��Ǿ� �ϴ� �Լ�
	void					Close();

public:

	// Thread ����
	void					CleanUp();

	// ���� Thread Loop���� ȣ��Ǵ� �Լ�, ���������� Runnable�� run�� ȣ���Ѵ�
	void					Execute();


public:

	// �ʱ�ȭ
	void					Init();

	// Get Next Thread ( in Current Linked List )
	CNtlThread *			GetNextThread() const { return (CNtlThread*) this->GetNext(); }

	// conditional wait
	void					Wait();

	// unconditional wait
	int						Wait(unsigned int millisecs);

	// Thread�� �����Ų��
	void					Exit();

	// ȣ���ڴ� Thread�� ����ɶ����� ����ȴ�
	void					Join();

	// ������ �����ڿ� �ݵ�� ȣ���Ͽ��� �����Ѵ�. ( ���� Thread ���� )
	void					Start();

	// Thread�̸� ��ȯ
	const char *			GetName() { return m_strName.c_str(); }

	// Thread�� ����� Runnable ��ü ��ȯ
	CNtlRunObject *			GetRunObject() { return m_pRunObject; }

	// attribute ����
	void					SetArg(void *arg) { m_pRunObject->SetArg(arg); }

	// attribute ��ȯ
	void *					GetArg() { return m_pRunObject->GetArg(); }

	//
	bool					IsAutoDelete() { return m_bAutoDelete; }

	// ����üũ
	bool					IsStatus(STATUS status) { return status == m_status; }

	//
	const char *			GetStatusString();

	//
	void					SetSignaled(bool bSignaled) { m_bSignaled = bSignaled; }

	//
	bool					IsSignaled() { return m_bSignaled; }




	// �ش�Ǵ� Thread�� �ñ׳��� ������ ( static )
	static void				Notify(CNtlThread * pThread);

	// ���� Thread�� ��ȯ�Ѵ� ( static )
	static CNtlThread *		GetCurrentThread();

	// Main Thread�� ��ȯ�Ѵ�
	static CNtlThread *		GetMainThread() { return m_pMainThread; }

	//
	static void				UnitTest();
	

protected:


	CNtlString				m_strName;

	STATUS					m_status;


	HANDLE					m_hThread;

	unsigned				m_threadID;

	CNtlEvent				m_event;

	bool					m_bSignaled;

	bool					m_bAutoDelete;

	CNtlRunObject *			m_pRunObject;


protected:

	static CThreadKey *		m_pThreadKey;

	static CNtlThread *		m_pMainThread;
};



//---------------------------------------------------------------------------------------
// NtlThreadFactory : ������ ���� �� �Ҹ� ó���� ����ϴ� Factory Ŭ����
//---------------------------------------------------------------------------------------
class CNtlThreadFactory
{
friend class CNtlThread;
friend class CThreadHelper;	// Ŭ���� ���ο�
friend class CNtlRunObject;

public:

	CNtlThreadFactory();

	virtual ~CNtlThreadFactory();


protected:


	static void				Lock() { m_pMutex->Lock(); }

	static void				Unlock() { m_pMutex->Unlock(); }

	static void				GarbageCollect(bool bShutDown = false);

	static void				SingleGarbageCollect(CNtlThread* pThread);


public:

	static void				Shutdown();

	static void				CloseAll();

	static void				JoinAll();

	static CNtlThread *		CreateThread(CNtlRunObject * pRunObject, const char * name = "Unnamed Thread", bool bAutoDelete = false);


protected:

	static CNtlLinkList *	m_pThreadList;

	static CNtlMutex *		m_pMutex;

	static bool				m_bClosed;

};


inline void CNtlRunObject::Wait()
{
	m_pOwner->Wait();
}

inline void CNtlRunObject::Terminate()
{
	Close();

	if (false != GetThread()->IsStatus(CNtlThread::eSTATUS_RUNNING) ||
		false != GetThread()->IsStatus(CNtlThread::eSTATUS_PAUSED) ||
		false != GetThread()->IsStatus(CNtlThread::eSTATUS_DEAD))
	{
		GetThread()->Join();
	}

	CNtlThreadFactory::Lock();
	CNtlThreadFactory::SingleGarbageCollect(GetThread());
	CNtlThreadFactory::Unlock();
}

inline int CNtlRunObject::Wait(unsigned int millisecs)
{
	return m_pOwner->Wait( millisecs );
}

inline void CNtlRunObject::Exit()
{
	m_pOwner->Exit();
}

inline const char * CNtlRunObject::GetName() const
{
	return m_pOwner->GetName();
}


#endif // __NTLTHREAD_H__

