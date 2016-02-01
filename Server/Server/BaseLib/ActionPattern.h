#pragma once
//-- include ------------------------------------------------------------------------
#include "SharedType.h"
//-----------------------------------------------------------------------------------

#define BOTAP_IDLE1_SECOND ( 500 )				// �ð� ���� : 0.5��
#define BOTAP_IDLE2_SECOND ( 1000 )				// �ð� ���� : 1�� [12/13/2007 SGpro]

typedef TBLIDX ACTIONPATTERNTBLIDX;
typedef BYTE ACTIONPATTERNID;   //eACTIONPATTERNID�� ����

typedef BYTE ACTIONPATTERN_FIELDSIZE; //���̺� ����Ǿ� �ִ� Pattern�� ���� ����
typedef BYTE ACTIONPATTERN_FIELD;
#define INVALID_ACTIONPATTERN_FIELD (-1)

//typedef BYTE ACTIONPATTERN_RECORDSIZE; //���̺� ����Ǿ� �ִ� Pattern�� ���� ����
//typedef BYTE ACTIONPATTERN_RECORD;

enum eACTIONPATTERNID
{
	 BOTAP_MOVE = 0		//Move ��Ŷ�� ����
	,BOTAP_IDLE1		//0.5��¥��
	,BOTAP_IDLE2		//1��¥��
	,BOTAP_MIDLE1
	,BOTAP_MIDLE2

	,COUNT_ACTIONPATTERNID
	,INVALID_ACTIONPATTERNID = -1
};

enum eACTIONPATTERN_LIMIT
{
	 MAX_SAVECOUNT_ACTIONPATTERN_FIELD	= 64	//�Ѱ��� Pattern�� ���� �� �ִ� Action�� �ִ� �ʵ� ��	
	,MAX_SAVECOUNT_ACTIONPATTERN_RECORD = 100	//���̺� ������ �� �ִ� �ִ� ���ڵ�
};