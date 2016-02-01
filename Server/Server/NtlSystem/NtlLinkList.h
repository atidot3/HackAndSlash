//***********************************************************************************
//
//	File		:	NtlLinkList.h
//
//	Begin		:	2005-11-30
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	Linked List
//
//***********************************************************************************

#pragma once


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
class CNtlLinkObject
{
public:

	CNtlLinkObject()
		:m_pPrev(NULL),m_pNext(NULL) {}

	virtual ~CNtlLinkObject() {}


public:

	//
	CNtlLinkObject *		GetNext() const { return m_pNext; }

	//
	void					SetNext(CNtlLinkObject * pNext) { m_pNext = pNext; }

	//
	CNtlLinkObject *		GetPrev() const { return m_pPrev; }

	//
	void					SetPrev(CNtlLinkObject * pPrev) { m_pPrev = pPrev; }


private:

	CNtlLinkObject *		m_pPrev;

	CNtlLinkObject *		m_pNext;
};


//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
class CNtlLinkList
{
public:

	CNtlLinkList(void)
		:m_pHead(NULL), m_pTail(NULL), m_iCount(0), m_iMaxCount(0) {}

	virtual ~CNtlLinkList(void) {}

public:

	// ����°�
	bool					IsEmpty() const { return m_iCount == 0; }

	// ���� ����Ʈ�� �ִ� ����
	int						GetCount() const { return m_iCount; }

	// ����Ʈ�� �ִ� ��� ����
	int						GetMaxCount() const { return m_iMaxCount; }

	// �� ó��
	CNtlLinkObject *		GetFirst() const { return m_pHead; }

	// �� ��
	CNtlLinkObject *		GetLast() const { return m_pTail; }


public:

	// �ǵڿ� �߰�
	void					Append(CNtlLinkObject * pLinkObject);

	// �Ǿտ� �߰�
	void					Prepend(CNtlLinkObject * pLinkObject);

	// ���ϴ� ��ġ �տ� �߰�
	void					InsertBefore(CNtlLinkObject * pBaseObject, CNtlLinkObject * pLinkObject);

	// ���ϴ� ��ġ �ڿ� �߰�
	void					InsertAfter(CNtlLinkObject * pBaseObject, CNtlLinkObject * pLinkObject);

	// �ϳ� ����
	void					Remove(CNtlLinkObject * pLinkObject);

	// ��� ����
	void					RemoveAll();

	//
	bool					Find(CNtlLinkObject * pBaseObject);



public:

	//
	CNtlLinkObject *		Pop(bool bFront = false);

	//
	void					Push(CNtlLinkObject * pLinkObject, bool bFront = true);

	//
	CNtlLinkObject *		PopFront();

	//
	CNtlLinkObject *		PopBack();

	//
	void					PushBack(CNtlLinkObject * pLinkObject) { Append(pLinkObject); }

	//
	void					PushFront(CNtlLinkObject * pLinkObject) { Prepend(pLinkObject); }



	// �׽�Ʈ�� ���� ����
	static void				UnitTest();


private:

	CNtlLinkObject *		m_pHead;

	CNtlLinkObject *		m_pTail;

	int						m_iCount;

	int						m_iMaxCount;

};


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
inline void CNtlLinkList::Append(CNtlLinkObject * pLinkObject)
{
	if( !m_pHead )
	{
		m_pHead = pLinkObject;
	}

	pLinkObject->SetPrev( m_pTail );

	if( m_pTail )
	{
		m_pTail->SetNext( pLinkObject );
	}

	m_pTail = pLinkObject;

	pLinkObject->SetNext( NULL );


	++m_iCount;

	if( m_iCount > m_iMaxCount)
	{
		m_iMaxCount = m_iCount;
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
inline void CNtlLinkList::Prepend(CNtlLinkObject * pLinkObject)
{
	if( !m_pTail )
	{
		m_pTail = pLinkObject;
	}

	pLinkObject->SetNext( m_pHead );

	if( m_pHead )
	{
		m_pHead->SetPrev( pLinkObject );
	}

	m_pHead = pLinkObject;

	pLinkObject->SetPrev( NULL );


	++m_iCount;

	if( m_iCount > m_iMaxCount)
	{
		m_iMaxCount = m_iCount;
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
inline void CNtlLinkList::InsertBefore(CNtlLinkObject * pBaseObject, CNtlLinkObject * pLinkObject)
{
	if( !pBaseObject )
	{
		Prepend( pLinkObject );
	}
	else
	{
		CNtlLinkObject * pPrev = pBaseObject->GetPrev();

		pLinkObject->SetNext( pBaseObject );
		pLinkObject->SetPrev( pPrev );
		pBaseObject->SetPrev( pLinkObject );

		if( !pPrev )
		{
			m_pHead = pLinkObject;
		}
		else
		{
			pPrev->SetNext( pLinkObject );
		}

		++m_iCount;

		if( m_iCount > m_iMaxCount)
		{
			m_iMaxCount = m_iCount;
		}
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
inline void CNtlLinkList::InsertAfter(CNtlLinkObject * pBaseObject, CNtlLinkObject * pLinkObject)
{
	if( !pBaseObject )
	{
		Append( pLinkObject );
	}
	else
	{
		CNtlLinkObject * pNext = pBaseObject->GetNext();

		pLinkObject->SetPrev( pBaseObject );
		pLinkObject->SetNext( pNext );
		pBaseObject->SetNext( pLinkObject );

		if( !pNext )
		{
			m_pTail = pLinkObject;
		}
		else
		{
			pNext->SetPrev( pLinkObject );
		}

		++m_iCount;

		if( m_iCount > m_iMaxCount)
		{
			m_iMaxCount = m_iCount;
		}
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
inline void CNtlLinkList::Remove(CNtlLinkObject * pLinkObject)
{
	CNtlLinkObject * pPrev = pLinkObject->GetPrev();
	CNtlLinkObject * pNext = pLinkObject->GetNext();

	if( pNext )
	{
		pNext->SetPrev( pPrev );
	}
	else
	{
		m_pTail = pPrev;
	}

	if( pPrev )
	{
		pPrev->SetNext( pNext );
	}
	else
	{
		m_pHead = pNext;
	}

	pLinkObject->SetPrev( NULL );
	pLinkObject->SetNext( NULL );

	--m_iCount;

}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
inline void CNtlLinkList::RemoveAll()
{
	while (m_iCount > 0)
	{
		Remove( m_pHead );
	}
}


//-----------------------------------------------------------------------------------
//		Purpose	:	�ӵ��� ����� �κп����� ����� ���� ��
//		Return	:
//-----------------------------------------------------------------------------------
inline bool CNtlLinkList::Find(CNtlLinkObject * pBaseObject)
{
	CNtlLinkObject * pObject = m_pHead;

	while( pObject )
	{
		if( pObject == pBaseObject )
		{
			return true;
		}

		pObject = pObject->GetNext();
	}

	return false;
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
inline CNtlLinkObject * CNtlLinkList::PopFront()
{
	CNtlLinkObject * pLinkObject = m_pHead;

	if( pLinkObject )
	{
		Remove( pLinkObject );
	}

	return pLinkObject;
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
inline CNtlLinkObject * CNtlLinkList::PopBack()
{
	CNtlLinkObject * pLinkObject = m_pTail;

	if( pLinkObject )
	{
		Remove( pLinkObject );
	}

	return pLinkObject;
}


//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
inline CNtlLinkObject * CNtlLinkList::Pop(bool bFront)
{
	return bFront ? PopFront() : PopBack();
}

//-----------------------------------------------------------------------------------
//		Purpose	:
//		Return	:
//-----------------------------------------------------------------------------------
inline void CNtlLinkList::Push(CNtlLinkObject * pLinkObject, bool bFront)
{
	return bFront ? Prepend(pLinkObject) : Append(pLinkObject);
}

