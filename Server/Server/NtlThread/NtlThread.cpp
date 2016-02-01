//***********************************************************************************
//
//	File		:	NtlThread.cpp
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


#include "StdAfx.h"
#include "NtlThread.h"
#include "NtlThreadException.h"
#include "NtlLog.h"

//---------------------------------------------------------------------------------------
// Key class ( Thread Ŭ���� ���ο� )
//---------------------------------------------------------------------------------------
class CThreadKey
{
public:
	CThreadKey()
	{
		m_dwKey = ::TlsAlloc();
		if( TLS_OUT_OF_INDEXES == m_dwKey )
		{
			THROW_THREAD_EXCEPTION( eTHREAD_ERR_TLS_KEY_CREATE, GetLastError() );
		}
	}

	~CThreadKey()
	{
		if (TLS_OUT_OF_INDEXES != m_dwKey)
		{
			::TlsFree(m_dwKey);

			m_dwKey = TLS_OUT_OF_INDEXES;
		}
	}

public:
	DWORD				GetKey() { return m_dwKey; }

private:

	DWORD				m_dwKey;
};


//---------------------------------------------------------------------------------------
// MainThread class  ( Thread Ŭ���� ���ο� ) Application�� ���� ������ ������ �����ϱ� ����
//---------------------------------------------------------------------------------------
class CMainRun : public CNtlRunObject
{
public:
	void Run() { /*MainRun�� ȣ����� ���ƾ� �Ѵ�.*/ };
};

class CMainThread : public CNtlThread
{
public:
	//- yoshiki : What if "new CMainRun" returns NULL?
	CMainThread() : CNtlThread(new CMainRun, "MainThread", true ) 
	{
		m_threadID = ::GetCurrentThreadId();
		Init();
	}
};

//---------------------------------------------------------------------------------------
// Helper class  ( Thread Ŭ���� ���ο� )
//---------------------------------------------------------------------------------------
class CThreadHelper
{
public:
	//- yoshiki : What if 1 or more of "new" operators return NULL?
	CThreadHelper()
	{
		CNtlThread::m_pThreadKey		= new CThreadKey;
		CNtlThreadFactory::m_pMutex		= new CNtlMutex;
		CNtlThreadFactory::m_pThreadList= new CNtlLinkList;
		CNtlThread::m_pMainThread		= new CMainThread;
	}

	virtual ~CThreadHelper()
	{
		CNtlThreadFactory::Shutdown();

		SAFE_DELETE( CNtlThread::m_pMainThread );
		SAFE_DELETE( CNtlThreadFactory::m_pMutex );
		SAFE_DELETE( CNtlThreadFactory::m_pThreadList );
		SAFE_DELETE( CNtlThread::m_pThreadKey );
	}
};


char * s_thread_status_string[CNtlThread::MAX_STATUS] = 
{
	"STATUS_NOT_RUNNING",		// �������� �ʴ� ���� ( �ʱ� ���� )
	"STATUS_PREPARING_TO_RUN",	// ���� �غ� ����
	"STATUS_RUNNING",			// ���� ����
	"STATUS_PAUSED",			// ���� ����
	"STATUS_DEAD",				// ���� ����
};

const char * CNtlThread::GetStatusString()
{
	if( m_status >= MAX_STATUS )
		return "Unknown Status";

	return s_thread_status_string[m_status];
}


//------------------------------------------------------
// static function declare
//------------------------------------------------------
/*static void ThreadCleanUp(void * arg)
{
	CNtlThread * pThread = (CNtlThread*) arg;
	pThread->CleanUp();
}*/

static unsigned __stdcall ThreadMain(void * arg)
{
	CNtlThread * pThread = (CNtlThread*) arg;
	pThread->Execute();

	return 0;
}


//---------------------------------------------------------------------------------------
// static variable declare
//---------------------------------------------------------------------------------------
CThreadHelper	threadHelper;
CThreadKey *	CNtlThread::m_pThreadKey = 0;
CNtlThread *	CNtlThread::m_pMainThread = 0;
CNtlLinkList *	CNtlThreadFactory::m_pThreadList = 0;
CNtlMutex *		CNtlThreadFactory::m_pMutex = 0;
bool			CNtlThreadFactory::m_bClosed = false;
//------------------------------------------------------


//------------------------------------------------------
// ������ Run�� ����Ǳ� ���� 1�� ȣ��
//------------------------------------------------------
void CNtlThread::Init()
{
	CNtlThreadFactory::Lock();

	m_status = eSTATUS_RUNNING;

	CNtlThreadFactory::Unlock();

	// Tls�� ���� (this ptr)
	if( !TlsSetValue( m_pThreadKey->GetKey(), (LPVOID) this ) )
	{
		THROW_THREAD_EXCEPTION( eTHREAD_ERR_TLS_SET_VALUE, GetLastError() );
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThread::Close()
{
	if( m_pRunObject )
	{
		m_pRunObject->Close();
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThread::CleanUp()
{
	CNtlThreadFactory::Lock();

	m_status = eSTATUS_DEAD;

	CNtlThreadFactory::Unlock();
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThread::Execute()
{
	Init();

	try
	{
		m_pRunObject->Run();
	}
	catch( CNtlThreadException e )
	{
		e.Dump();
	}
	catch(...)
	{				
	}

	CleanUp();
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThread::Start()
{
	m_hThread = (HANDLE) _beginthreadex(NULL, 0, ThreadMain, this, 0, &m_threadID);

	if( !m_hThread )
	{
		THROW_THREAD_EXCEPTION(eTHREAD_ERR_THREAD_CREATE, GetLastError());
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThread::Exit()
{
	CleanUp();
	_endthreadex(0);
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThread::Wait()
{
	//-- thread sleep

	m_event.Wait();

	//-- thread wakeup
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
int CNtlThread::Wait(unsigned int millisecs)
{
	//-- thread sleep

	int rc = m_event.Wait( millisecs );

	//-- thread wakeup

	return rc;
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThread::Notify(CNtlThread * pThread)
{
	pThread->m_event.Notify();
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThread::Join()
{
	int rc = ::WaitForSingleObject( m_hThread, INFINITE );
	if( WAIT_FAILED == rc )
	{
		THROW_THREAD_EXCEPTION( eTHREAD_ERR_THREAD_JOIN, GetLastError() );
	}
	else
	{
		::CloseHandle( m_hThread );
	}

	CNtlThreadFactory::Lock();

	// ��� ���� ����
	m_status = eSTATUS_NOT_RUNNING;

	CNtlThreadFactory::Unlock();
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
CNtlThread::CNtlThread(CNtlRunObject * pRunObject, const char * name, bool bAutoDelete)
{
	// ��� ���� ����
	m_status				= eSTATUS_NOT_RUNNING;

	m_bAutoDelete			= bAutoDelete;
	m_bSignaled				= false;
	m_strName				= name;

	m_pRunObject			= pRunObject;

	m_pRunObject->SetThread( this );

	// �ʱ�ȭ ����
	m_status				= eSTATUS_PREPARING_TO_RUN;	
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
CNtlThread::~CNtlThread()
{
	if( eSTATUS_NOT_RUNNING != m_status && this != CNtlThread::m_pMainThread  )
	{
	}

	if( m_bAutoDelete )
	{
		SAFE_DELETE( m_pRunObject );
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
CNtlThread * CNtlThread::GetCurrentThread()
{
	return (CNtlThread*) TlsGetValue( m_pThreadKey->GetKey() );
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
// Thread ������ �ΰ��� ���
// 1. ����ÿ��� �̻���� ���� ��� ����
// 2. ����ð� �ƴ� ��쿡�� ���� DEAD ������ THREAD�� ����
// ���ǻ���!! : GarbageCollect�� ��� Lock()�� �ǰ� ���´�.
//-----------------------------------------------------------------------------------
CNtlThreadFactory::CNtlThreadFactory()
{
}

//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
CNtlThreadFactory::~CNtlThreadFactory()
{
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThreadFactory::GarbageCollect(bool bShutDown)
{
	// ������ ����
	CNtlThread * pThread = (CNtlThread*) m_pThreadList->GetFirst();
	while( pThread )
	{
		if( pThread->IsAutoDelete() && 
			( bShutDown && !pThread->IsStatus( CNtlThread::eSTATUS_NOT_RUNNING ) ||
			 !bShutDown && pThread->IsStatus( CNtlThread::eSTATUS_DEAD ) ) )
		{
			Unlock();

			pThread->Join();
			
			Lock();

			pThread = (CNtlThread*) m_pThreadList->GetFirst();	// ó������ ������
			continue;
		}
		else
		{
			pThread = (CNtlThread*) pThread->GetNext();
		}
	}

	// ������ ����
	pThread = (CNtlThread*) m_pThreadList->GetFirst();
	while( pThread )
	{
		CNtlThread * pNext = (CNtlThread*) pThread->GetNext();
		if( pThread->IsStatus( CNtlThread::eSTATUS_NOT_RUNNING ) )
		{
			m_pThreadList->Remove( pThread );
			SAFE_DELETE( pThread );
		}

		pThread = pNext;
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThreadFactory::SingleGarbageCollect(CNtlThread* pGarbageThread)
{
	CNtlThread* pThread = (CNtlThread*)(m_pThreadList->GetFirst());
	while (NULL != pThread)
	{
		if (pGarbageThread == pThread)
		{
			if (false != pThread->IsStatus(CNtlThread::eSTATUS_NOT_RUNNING) ||
				false != pThread->IsStatus(CNtlThread::eSTATUS_PREPARING_TO_RUN))
			{
				m_pThreadList->Remove(pThread);
				SAFE_DELETE(pThread);
			}

			return;
		}

		pThread = (CNtlThread*) pThread->GetNext();
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
CNtlThread * CNtlThreadFactory::CreateThread(CNtlRunObject * pRunObject, const char * name, bool bAutoDelete)
{
	Lock();

	GarbageCollect();

	CNtlThread * pThread = new CNtlThread( pRunObject, name, bAutoDelete );
	if (NULL == pThread)
	{
		NTL_LOG_ASSERT("\"new CNtlThread( pRunObject, name, bAutoDelete )\" failed.");
		return NULL;
	}

	m_pThreadList->Append( pThread );

	Unlock();

	return pThread;
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThreadFactory::Shutdown()
{
	Lock();

	if( false == m_bClosed )
	{
		m_bClosed = true;

		// ������ ����
		CNtlThread * pThread = (CNtlThread*) m_pThreadList->GetFirst();
		while( pThread )
		{
			Unlock();

			pThread->Close();

			Lock();

			pThread = (CNtlThread*) pThread->GetNext();
		}
	}

	GarbageCollect( true );

	Unlock();
}



//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThreadFactory::CloseAll()
{
	Lock();

	if( false == m_bClosed )
	{
		m_bClosed = true;

		// ������ ����
		CNtlThread * pThread = (CNtlThread*) m_pThreadList->GetFirst();
		while( pThread )
		{
			Unlock();

			pThread->Close();

			Lock();

			pThread = (CNtlThread*) pThread->GetNext();
		}
	}

	Unlock();
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
void CNtlThreadFactory::JoinAll()
{
	Lock();

	// ������ ����
	CNtlThread * pThread = (CNtlThread*) m_pThreadList->GetFirst();
	while( pThread )
	{
		Unlock();

		pThread->Join();

		Lock();

		pThread = (CNtlThread*) pThread->GetNext();
	}

	Unlock();
}




#include <iostream>
using namespace std;
void CNtlThread::UnitTest()
{
	class CTestRun : public CNtlRunObject
	{
	public:

		CTestRun()
			:m_bRun(true) {}

		void Run()
		{
			while( m_bRun )
			{
				cout << "TestRun : " << this->GetName() << " : " << GetThread()->GetStatusString() << endl;

				Sleep( 33 );
			}
		}

		void SetRunFlag(bool bFlag) { m_bRun = bFlag; }

	private:

		bool volatile m_bRun;

	};

	try
	{
		CTestRun * pTestRun = new CTestRun;
		CNtlThread * pThread = CNtlThreadFactory::CreateThread( pTestRun, "Test Thread");

		pThread->Start();

		Sleep(100);

		pTestRun->SetRunFlag( false );

		pThread->Join();
	}
	catch( CNtlThreadException e )
	{
		e.Dump();
	}
	catch( ... )
	{
	}
}

