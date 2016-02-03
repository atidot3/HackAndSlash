//***********************************************************************************
//
//	File		:	NtlPacketSYS.h
//
//	Begin		:	2007-01-17
//
//	Copyright	:	�� NTL-Inc Co., Ltd
//
//	Author		:	Hyun Woo, Koo   ( zeroera@ntl-inc.com )
//
//	Desc		:	
//
//***********************************************************************************
#ifndef __NTLPACKETSYS_H__
#define __NTLPACKETSYS_H__
#pragma once


//------------------------------------------------------------------
// �ý��� opcode
//------------------------------------------------------------------
enum eOPCODE_SYS
{
	SYS_OPCODE_BEG = 0,
	SYS_ALIVE,
	SYS_PING,

	SYS_OPCODE_END_DUMMY,
	SYS_OPCODE_END = SYS_OPCODE_END_DUMMY - 1
};
//------------------------------------------------------------------

#endif