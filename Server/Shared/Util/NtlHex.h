#pragma once
//***********************************************************************************
//
//	File		:	Utils.h
//
//	Begin		:	2006-03-24
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:
//
//	Desc		:	
//
//***********************************************************************************

bool				WideCharToHex(WCHAR* pwszString, DWORD dwBufferSize, char* pszBuffer);

bool				HexToWideChar(char* pszHex, DWORD dwBufferSize, WCHAR* pwszBuffer);

// --------------------------------------------------------------------------------
// StreamToHex
//
// ����� terminating null('\0')�� ���Դϴ�.
// A terminating null character('\0') will be added to the result.
// --------------------------------------------------------------------------------
// HexToStream
//
// Stream���� terminating null�� ������ �����Ƿ� ����� '\0'�� ������ �ʽ��ϴ�.
// '\0' will NOT be added to the result since stream isn't supposed to have terminating null.
// --------------------------------------------------------------------------------
// by YOSHIKI(2007-02-28)
// --------------------------------------------------------------------------------
bool				StreamToHex(BYTE* pbyStream, DWORD dwStreamLength, char* pszBuffer, DWORD dwBufferSize);

bool				HexToStream(char* pszHex, BYTE* pbyBuffer, DWORD dwBufferSize);


char				ValueToCharacter(BYTE byValue);

BYTE				CharacterToValue(char chCharacter);