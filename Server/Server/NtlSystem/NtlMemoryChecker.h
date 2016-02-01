//***********************************************************************************
//
//	File		:	MemoryLeakChecker.h
//
//	Begin		:	2007-01-12
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	
//
//***********************************************************************************

#pragma once


/*----------------------------------------------------------------------------------
  [1/12/2007 zeroera] 
-----------------------------------------------------------------------------------
 �޸� ���� üũ �� ���� üũ�� Ű�� �Ǹ� ����� ������尡 �����Ƿ�
 �޸� ���� üũ�� ���� �������� ������� ����
-----------------------------------------------------------------------------------*/

#define __MEMORY_LEAK_CHECK__



#if defined(__MEMORY_LEAK_CHECK__) && defined(_MSC_VER) && defined (_DEBUG) // For Windows Debug

#define _CRTDBG_MAP_ALLOC // For memory leak check
#include <windows.h>
#include <crtdbg.h> // Include CRTDBG.H after all other headers

#if !defined (_CONSOLE)
	#include <cstdlib> // for Consol Application
#endif


#ifdef NEW_INLINE
	#undef NEW_INLINE
#endif
#define NEW_INLINE new( _NORMAL_BLOCK, __FILE__, __LINE__ )

#ifdef new
	#undef new
#endif
#define new NEW_INLINE



class CNtlMemoryChecker
{
public:

	CNtlMemoryChecker()
	{
		// CrtDbg Flag
		_CrtSetDbgFlag(	_CRTDBG_ALLOC_MEM_DF | // ����� �� �Ҵ��� Ȱ��ȭ �ϰ� ��� �����ڸ� ����Ѵ� ( ����Ʈ�� Ȱ��ȭ �Ǿ� �ִ� )
						_CRTDBG_CHECK_ALWAYS_DF | // �Ҵ�� �Ҵ� ���� ��û�� ���� ������ ��� �޸𸮸� �˻��ϰ� �����Ѵ�. ( �������Ʈ�� ��������Ʈ�� �˷��ش� )
						//_CRTDBG_CHECK_CRT_DF | // CRT ���̺귯���� ������ �޸� �Ҵ���� �����Ѵ�. ( ���� Ű�� �ʴ´� )
						_CRTDBG_DELAY_FREE_MEM_DF | // ��¥ �޸� ���� ��� �Ҵ�� ��ϰ� ���� �� ����Ʈ�� �����Ѵ�. ( ������ �� �׼��� Ž�� )
						_CRTDBG_LEAK_CHECK_DF // ���α׷� ����� �޸� ������ �˻��Ѵ�. ( MFC ������ ���� )
						);

#if defined (_CONSOLE)
		// Send all reports to STDOUT
		_CrtSetReportMode( _CRT_WARN,   
			_CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG );
		_CrtSetReportFile( _CRT_WARN,   
			_CRTDBG_FILE_STDERR );

		_CrtSetReportMode( _CRT_ERROR,  
			_CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG  );
		_CrtSetReportFile( _CRT_ERROR,  
			_CRTDBG_FILE_STDERR );

		_CrtSetReportMode( _CRT_ASSERT, 
			_CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG  );
		_CrtSetReportFile( _CRT_ASSERT, 
			_CRTDBG_FILE_STDERR );
#else

		_CrtSetReportMode( _CRT_WARN,   
			_CRTDBG_MODE_DEBUG  );
		_CrtSetReportMode( _CRT_ERROR,  
			_CRTDBG_MODE_DEBUG  );
		_CrtSetReportMode( _CRT_ASSERT, 
			_CRTDBG_MODE_DEBUG  );
#endif

	}
	

public:

	void				Test()
	{
		TCHAR * pNew1 = new TCHAR[20];
		TCHAR * pNew2 = new TCHAR[200];
		//void * pMalloc3 = malloc(10);

		memset( pNew1, 0xAA, sizeof(TCHAR) * 20 );
		memset( pNew2, 0xFF, sizeof(TCHAR) * 200 );

		//memcpy( pNew1, pNew2, sizeof(TCHAR) * 30 );
		//	_ASSERT( _CrtCheckMemory() );


		//delete[] pNew1;
		//delete[] pNew2;
	}
};

static CNtlMemoryChecker __sMemoryLeakChecker;


#endif // defined(_MSC_VER) && defined (_DEBUG)
