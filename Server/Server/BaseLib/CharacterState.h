#pragma once

#include "NtlBitFlag.h"
#include "SharedType.h"
#include "Vector.h"
#include "Skill.h"
#include "NtlItem.h"
#include "NtlMovement.h"

//-----------------------------------------------------------------------------------
// Movement ( ĳ���� �̵� ) : ��ġ�̵�
//-----------------------------------------------------------------------------------
enum eMOVESTATE 
{
	MOVE_DISABLE,		// Move Disable
	MOVE_STOP,			// Stop
	MOVE_JUMP,			// Jump
	MOVE_F,				// Forward
	MOVE_B,				// Backward
	MOVE_L,				// Left
	MOVE_R,				// Right
	MOVE_TURN_L,		// Turning Left
	MOVE_TURN_R,		// Turning Right
	MOVE_RUN,			// Walk / Run
	MOVE_DASH,			// Dash
	MOVE_DESTMOVE,		// DestMove ( = Mouse Move )

	MAX_MOVESTATE
};


//-----------------------------------------------------------------------------------
// Movement ( ĳ���� �̵� ) : ��ġ�̵� �÷���
//-----------------------------------------------------------------------------------
enum eMOVE_FLAG
{
	MOVE_FLAG_DISABLE	= MAKE_BIT_FLAG( MOVE_DISABLE ),	// Move Disable
	MOVE_FLAG_STOP		= MAKE_BIT_FLAG( MOVE_STOP ),		// Stop
	MOVE_FLAG_JUMP		= MAKE_BIT_FLAG( MOVE_JUMP ),		// Jump
	MOVE_FLAG_F			= MAKE_BIT_FLAG( MOVE_F ),			// Forward
	MOVE_FLAG_B			= MAKE_BIT_FLAG( MOVE_B ),			// Backward
	MOVE_FLAG_L			= MAKE_BIT_FLAG( MOVE_L ),			// Left
	MOVE_FLAG_R			= MAKE_BIT_FLAG( MOVE_R ),			// Right
	MOVE_FLAG_TURN_L	= MAKE_BIT_FLAG( MOVE_TURN_L ),	// Turning Left
	MOVE_FLAG_TURN_R	= MAKE_BIT_FLAG( MOVE_TURN_R ),	// Turning Right
	MOVE_FLAG_RUN		= MAKE_BIT_FLAG( MOVE_RUN ),		// Walk / Run
	MOVE_FLAG_DASH		= MAKE_BIT_FLAG( MOVE_DASH ),		// Dash
	MOVE_FLAG_DESTMOVE	= MAKE_BIT_FLAG( MOVE_DESTMOVE ),	// DestMove ( = Mouse Move )

	MOVE_FLAG_F_L		= MOVE_FLAG_F & MOVE_FLAG_L,		// Forward + Left
	MOVE_FLAG_F_R		= MOVE_FLAG_F & MOVE_FLAG_R,		// Forward + Right
	MOVE_FLAG_B_L		= MOVE_FLAG_B & MOVE_FLAG_L,		// Backward + Left
	MOVE_FLAG_B_R		= MOVE_FLAG_B & MOVE_FLAG_R,		// Backward + Right
	MOVE_FLAG_F_TURN_L	= MOVE_FLAG_F & MOVE_FLAG_TURN_L,	// Forward + Turning Left
	MOVE_FLAG_F_TURN_R	= MOVE_FLAG_F & MOVE_FLAG_TURN_R,	// Forward + Turning Right
	MOVE_FLAG_B_TURN_L	= MOVE_FLAG_B & MOVE_FLAG_TURN_L,	// Backward + Turning Left
	MOVE_FLAG_B_TURN_R	= MOVE_FLAG_B & MOVE_FLAG_TURN_R,	// Backward + Turning Right
};


//-----------------------------------------------------------------------------------
// Character State
//-----------------------------------------------------------------------------------
enum eCHARSTATE
{
	CHARSTATE_SPAWNING,				// ������ ( ĳ���Ͱ� ���� �ɶ� )
	CHARSTATE_DESPAWNING,			// ������ ( ĳ���Ͱ� ���� �ɶ� )
	CHARSTATE_STANDING,				// ������
	CHARSTATE_SITTING,				// �ɾ� ����
	CHARSTATE_FAINTING,				// ������ ����
	CHARSTATE_CAMPING,				// ���� �����
	CHARSTATE_LEAVING,				// ���� ��

	CHARSTATE_MOVING,				// �Ϲ����� �ʵ� �̵� ( RUNNING, WALKING, JUMPING, DASHING ���� )
	CHARSTATE_DESTMOVE,				// ������ �̵�
	CHARSTATE_FOLLOWING,			// ���󰡱� �̵�
	CHARSTATE_FALLING,				// �������� ��
	CHARSTATE_DASH_PASSIVE,			// Passive dash �̵�
	CHARSTATE_TELEPORTING,			// �ڷ���Ʈ�� ( ĳ���Ͱ� ���� ������ �̵��� )
	CHARSTATE_SLIDING,				// �����̵� �ǰ� ����
	CHARSTATE_KNOCKDOWN,			// �˴ٿ� �ǰ� ����

	CHARSTATE_FOCUSING,				// ���� ����(RP ���ʽ� ��� �� �ʱ� �ܰ�)
	CHARSTATE_CASTING,				// ĳ������
	CHARSTATE_SKILL_AFFECTING,		// ��ų ������
	CHARSTATE_KEEPING_EFFECT,		// ��ų/������ ȿ�� ���� ����
	CHARSTATE_CASTING_ITEM,			// ������ ĳ���� ��

	CHARSTATE_STUNNED,				// Stun ����
	CHARSTATE_SLEEPING,				// �ڰ� ����
	CHARSTATE_PARALYZED,			// ���� ����

	CHARSTATE_HTB,					// HTB�� �����ϰ� ����
	CHARSTATE_SANDBAG,				// HTB�� ���ϰ� ����
	CHARSTATE_CHARGING,				// ���������
	CHARSTATE_GUARD,				// ���� ��� ����

	CHARSTATE_PRIVATESHOP,			// ���λ��� [7/16/2007 SGpro]
	CHARSTATE_DIRECT_PLAY,			// ĳ���� ���� ����
	CHARSTATE_OPERATING,			// ������Ʈ ���� ����
	CHARSTATE_RIDEON,				// Ż�Ϳ� Ÿ�ִ� ����
	CHARSTATE_TURNING,				// ȸ����
	//CHARSTATE_CHASING,				// ������
	//CHARSTATE_STONING,			// ���� �Ǿ� ����
	//CHARSTATE_SPRAWLING,			// ���� ����
	//CHARSTATE_FALLING,			// �̲�����������
	//CHARSTATE_SWIMMING,			// �����ϰ� ����
	//CHARSTATE_RUNNING,			// �޸��� ����
	//CHARSTATE_WALKING,			// �Ȱ� ����
	//CHARSTATE_JUMPING,			// �����ϰ� ����
	//CHARSTATE_HOVERING,			// �ξ��ϰ� ����
	//CHARSTATE_FLYING,				// ���� ����
	//CHARSTATE_CANDYING,			// ĵ��� �Ǿ� ����
	//CHARSTATE_FIGHTING,				// ������

	//CHARSTATE_CRAFTING,			// ������
	//CHARSTATE_LOOTING,			// ������
	//CHARSTATE_TRADING,			// ���������
	//CHARSTATE_SHOPPING,			// ������

	CHARSTATE_COUNT,
	INVALID_CHARSTATE = 0xFF

};


//-----------------------------------------------------------------------------------
// Character State Flag
//-----------------------------------------------------------------------------------
enum eCHARSTATE_FLAG
{
	CHARSTATE_FLAG_SPAWNING			= MAKE_BIT_FLAG( CHARSTATE_SPAWNING ),				// ������ ( ĳ���Ͱ� ���忡 ó�� ���� )
	CHARSTATE_FLAG_DESPAWNING		= MAKE_BIT_FLAG( CHARSTATE_DESPAWNING ),			// ������
	CHARSTATE_FLAG_STANDING			= MAKE_BIT_FLAG( CHARSTATE_STANDING ),				// ������
	CHARSTATE_FLAG_SITTING			= MAKE_BIT_FLAG( CHARSTATE_SITTING ),				// �ɾ� ����
	CHARSTATE_FLAG_FAINTING			= MAKE_BIT_FLAG( CHARSTATE_FAINTING ),				// ������ ����
	CHARSTATE_FLAG_CAMPING			= MAKE_BIT_FLAG( CHARSTATE_CAMPING ),				// ���� �����

	CHARSTATE_FLAG_MOVING			= MAKE_BIT_FLAG( CHARSTATE_MOVING ),				// �Ϲ����� �ʵ� �̵� ( RUNNING, WALKING, JUMPING, DASHING ���� )
	CHARSTATE_FLAG_DESTMOVE			= MAKE_BIT_FLAG( CHARSTATE_DESTMOVE ),				// ������ �̵�
	CHARSTATE_FLAG_FOLLOWING		= MAKE_BIT_FLAG( CHARSTATE_FOLLOWING ),			// ���󰡱� �̵�
	CHARSTATE_FLAG_FALLING			= MAKE_BIT_FLAG( CHARSTATE_FALLING ),				// �������� ��
	CHARSTATE_FLAG_DASH_PASSIVE		= MAKE_BIT_FLAG( CHARSTATE_DASH_PASSIVE ),			// Passive dash �̵�
	CHARSTATE_FLAG_TELEPORTING		= MAKE_BIT_FLAG( CHARSTATE_TELEPORTING ),			// �ڷ���Ʈ�� ( ĳ���Ͱ� ���� ������ �̵��Ͽ� ������ )
	CHARSTATE_FLAG_SLIDING			= MAKE_BIT_FLAG( CHARSTATE_SLIDING ),				// �����̵� �ǰ� ����
	CHARSTATE_FLAG_KNOCKDOWN		= MAKE_BIT_FLAG( CHARSTATE_KNOCKDOWN ),			// �˴ٿ� �ǰ� ����

	CHARSTATE_FLAG_FOCUSING			= MAKE_BIT_FLAG( CHARSTATE_FOCUSING ),				// ���� ����(RP ���ʽ� ��� �� �ʱ� �ܰ�)
	CHARSTATE_FLAG_CASTING			= MAKE_BIT_FLAG( CHARSTATE_CASTING ),				// ĳ������
	CHARSTATE_FLAG_SKILL_AFFECTING	= MAKE_BIT_FLAG( CHARSTATE_SKILL_AFFECTING ),		// ��ų ������
	CHARSTATE_FLAG_KEEPING_EFFECT	= MAKE_BIT_FLAG( CHARSTATE_KEEPING_EFFECT ),		// ��ų/������ ȿ�� ���� ����
	CHARSTATE_FLAG_CASTING_ITEM		= MAKE_BIT_FLAG( CHARSTATE_CASTING_ITEM ),			// ������ ĳ���� ��

	CHARSTATE_FLAG_STUNNED			= MAKE_BIT_FLAG( CHARSTATE_STUNNED ),				// Stun ����
	CHARSTATE_FLAG_SLEEPING			= MAKE_BIT_FLAG( CHARSTATE_SLEEPING ),				// �ڰ� ����
	CHARSTATE_FLAG_PARALYZED		= MAKE_BIT_FLAG( CHARSTATE_PARALYZED ),				// ���� ����

	CHARSTATE_FLAG_HTB				= MAKE_BIT_FLAG( CHARSTATE_HTB ),					// HTB�� �����ϰ� ����
	CHARSTATE_FLAG_SANDBAG			= MAKE_BIT_FLAG( CHARSTATE_SANDBAG ),				// HTB�� ���ϰ� ����
	CHARSTATE_FLAG_CHARGING			= MAKE_BIT_FLAG( CHARSTATE_CHARGING ),				// ���������
	CHARSTATE_FLAG_GUARD			= MAKE_BIT_FLAG( CHARSTATE_GUARD ),					// ������ ����

	CHARSTATE_FLAG_PRIVATESHOP		= MAKE_BIT_FLAG( CHARSTATE_PRIVATESHOP ),			// ���λ��� [7/16/2007 SGpro]
	CHARSTATE_FLAG_DIRECT_PLAY		= MAKE_BIT_FLAG( CHARSTATE_DIRECT_PLAY ),			// ���λ��� [7/16/2007 SGpro]
	CHARSTATE_FLAG_OPERATING		= MAKE_BIT_FLAG( CHARSTATE_OPERATING ),				// ���λ��� [7/16/2007 SGpro]
	CHARSTATE_FLAG_RIDEON			= MAKE_BIT_FLAG( CHARSTATE_RIDEON ),
	CHARSTATE_FLAG_TURNING			= MAKE_BIT_FLAG( CHARSTATE_TURNING ),

	CHARSTATE_FLAG_ALL				= 0xFFFFFFFF >> ( 32 - CHARSTATE_COUNT )
};


//-----------------------------------------------------------------------------------
// Aspect ( ĳ���� Ư�� ���� : ���ŵ� )�ߺ��Ұ� ����
//-----------------------------------------------------------------------------------
enum eASPECTSTATE
{
	ASPECTSTATE_SUPER_SAIYAN,		// ���� ���̾���
	ASPECTSTATE_PURE_MAJIN,			// ���� ����
	ASPECTSTATE_GREAT_NAMEK,		// �׷���Ʈ ����ũ��
	ASPECTSTATE_KAIOKEN,				// ��ձ�
	ASPECTSTATE_SPINNING_ATTACK,		// ȸ�� ����
	ASPECTSTATE_VEHICLE,			// Ż ��

	ASPECTSTATE_COUNT,
	ASPECTSTATE_INVALID = 0xFF
};


//-----------------------------------------------------------------------------------
// Condition, �ߺ����� ����
//-----------------------------------------------------------------------------------
enum eCHARCONDITION
{
	CHARCOND_INVISIBLE,				// ������ ����
	CHARCOND_HIDING_KI,				// �� �����
	CHARCOND_INVINCIBLE,			// ����
	CHARCOND_TAUNT,					// Ÿ�ٰ���
	CHARCOND_ATTACK_DISALLOW,		// ���ݺҰ�
	CHARCOND_TRANSPARENT,			// ���� (GM��)
	CHARCOND_CANT_BE_TARGETTED,		// Ÿ�ٵ��� ����
	CHARCOND_DIRECT_PLAY,			// ������ ( PC : Ŭ���̾�Ʈ �����϶�, NPC or MOB : ���� ������ �� �ʿ信 ���� )

	CHARCOND_BLEEDING,				// ����
	CHARCOND_POISON,				// ��
	CHARCOND_STOMACHACHE,			// ����
	CHARCOND_CONFUSED,				// ȥ��
	CHARCOND_TERROR,				// ����
	CHARCOND_BARRIER,				// ������ ����ȭ
	CHARCOND_DAMAGE_REFLECTION,		// ������ �ݻ�
	//CHARCOND_SLOW,				// ������

	CHARCOND_AFTEREFFECT,			// ���� ������
	CHARCOND_CHARGING_BLOCKED,		// �� ������ �Ұ�
	CHARCOND_FAKE_DEATH,			// ���� ô�ϱ�
	CHARCOND_NULLIFIED_DAMAGE,		// �������� ��ȿȭ��Ű��

	CHARCOND_MOB_ROLE,				// Mob ���� ���� NPC

	CHARCOND_CLICK_DISABLE,			// ĳ���� Ŭ�� ����
	CHARCOND_CLIENT_UI_DISABLE,		// Ŭ���̾�Ʈ���� ĳ���� ���� ui ��� ���� ( �޴� �� )

	CHARCONDITION_COUNT,
	INVALID_CHARCONDITION = 0xFF,

	CHARCOND_FIRST = CHARCOND_INVISIBLE,
	CHARCOND_LAST = CHARCONDITION_COUNT - 1,
};


//-----------------------------------------------------------------------------------
// Condition Flag, �ߺ����� ����
//-----------------------------------------------------------------------------------
enum eCHARCONDITION_FLAG
{
	CHARCOND_FLAG_INVISIBLE				= MAKE_BIT_FLAG( CHARCOND_INVISIBLE ),				// ������ ����
	CHARCOND_FLAG_HIDING_KI				= MAKE_BIT_FLAG( CHARCOND_HIDING_KI ),				// �� �����
	CHARCOND_FLAG_INVINCIBLE			= MAKE_BIT_FLAG( CHARCOND_INVINCIBLE ),				// ����
	CHARCOND_FLAG_TAUNT					= MAKE_BIT_FLAG( CHARCOND_TAUNT ),					// Ÿ�ٰ���
	CHARCOND_FLAG_ATTACK_DISALLOW		= MAKE_BIT_FLAG( CHARCOND_ATTACK_DISALLOW ),		// ���ݺҰ�
	CHARCOND_FLAG_TRANSPARENT			= MAKE_BIT_FLAG( CHARCOND_TRANSPARENT ),			// ���� (GM��)
	CHARCOND_FLAG_CANT_BE_TARGETTED		= MAKE_BIT_FLAG( CHARCOND_CANT_BE_TARGETTED ),		// Ÿ�ٵ��� ����
	CHARCOND_FLAG_DIRECT_PLAY			= MAKE_BIT_FLAG( CHARCOND_DIRECT_PLAY ),			// ������

	CHARCOND_FLAG_BLEEDING				= MAKE_BIT_FLAG( CHARCOND_BLEEDING ),				// ����
	CHARCOND_FLAG_POISON				= MAKE_BIT_FLAG( CHARCOND_POISON ),					// ��
	CHARCOND_FLAG_STOMACHACHE			= MAKE_BIT_FLAG( CHARCOND_STOMACHACHE ),			// ����
	CHARCOND_FLAG_CONFUSED				= MAKE_BIT_FLAG( CHARCOND_CONFUSED ),				// ȥ��
	CHARCOND_FLAG_TERROR				= MAKE_BIT_FLAG( CHARCOND_TERROR ),					// ����
	CHARCOND_FLAG_BARRIER				= MAKE_BIT_FLAG( CHARCOND_BARRIER ),				// ������ ����ȭ
	CHARCOND_FLAG_DAMAGE_REFLECTION		= MAKE_BIT_FLAG( CHARCOND_DAMAGE_REFLECTION ),		// ������ �ݻ�
//	CHARCOND_FLAG_SLOW					= MAKE_BIT_FLAG( CHARCOND_SLOW ),					// ������

	CHARCOND_FLAG_AFTEREFFECT			= MAKE_BIT_FLAG( CHARCOND_AFTEREFFECT ),			// ���� ������
	CHARCOND_FLAG_CHARGING_BLOCKED		= MAKE_BIT_FLAG( CHARCOND_CHARGING_BLOCKED ),		// �� ������ �Ұ�
	CHARCOND_FLAG_FAKE_DEATH			= MAKE_BIT_FLAG( CHARCOND_FAKE_DEATH ),				// ���� ô�ϱ�
	CHARCOND_FLAG_NULLIFIED_DAMAGE		= MAKE_BIT_FLAG( CHARCOND_NULLIFIED_DAMAGE ),		// �������� ��ȿȭ��Ű��

	CHARCOND_FLAG_MOB_ROLE				= MAKE_BIT_FLAG( CHARCOND_MOB_ROLE ),				// Mob ���� ���� NPC

	CHARCOND_FLAG_CLICK_DISABLE			= MAKE_BIT_FLAG( CHARCOND_CLICK_DISABLE ),			// �� �÷��װ� ���� ��ü ���� ����
	CHARCOND_FLAG_CLIENT_UI_DISABLE		= MAKE_BIT_FLAG( CHARCOND_CLIENT_UI_DISABLE ),		// �� �÷��װ� ���� ��ü UI ��� ����
};


//-----------------------------------------------------------------------------------
// Condition Flag, �ߺ����� ����
//-----------------------------------------------------------------------------------
enum eCHARLEAVING_TYPE
{
	CHARLEAVING_DISCONNECT,			// ������ ������
	CHARLEAVING_SERVER_CHANGE,		// �ٸ� ���� �������� �̵�
	CHARLEAVING_CHANNEL_CHANGE,		// �ٸ� ���� ä�η��� �̵�
	CHARLEAVING_CHARACTER_EXIT,		// ĳ���� ���� : Lobby�� �̵�
	CHARLEAVING_GAME_EXIT,			// ACCOUNT ���� : ���� ����
	CHARLEAVING_GAME_KICK,			// �ý��ۿ� ���� ����(KICK ��)

	INVALID_CHARLEAVING = INVALID_BYTE,
};


//-----------------------------------------------------------------------------------
// ���� ���� �Լ� ���� : 
//-----------------------------------------------------------------------------------
const char *				NtlGetCharStateString(BYTE byStateID);

const char *				NtlGetAspectStateString(BYTE byStateID);

const char *				NtlGetConditionStateString(BYTE byStateID);



//-----------------------------------------------------------------------------------
// ���� ���� ����ü
//-----------------------------------------------------------------------------------
#pragma pack(1)

//-----------------------------------------------------------------------------------
struct sCHARSTATE_SPAWNING
{
	BYTE								byTeleportType;		// eTELEPORT_TYPE
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_DESPAWNING
{
	BYTE								byTeleportType;		// eTELEPORT_TYPE
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_STANDING
{
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_SITTING
{
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_FAINTING
{
	BYTE			byReason; // eFAINT_REASON
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_CAMPING
{
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_LEAVING
{
	BYTE			byLeavingType;	// eCHARLEAVING_TYPE
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_MOVING
{
	DWORD			dwTimeStamp;
	BYTE			byMoveFlag;
	BYTE			byMoveDirection;
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_DESTMOVE
{
	DWORD			dwTimeStamp;
	BYTE			byMoveFlag;
	bool			bHaveSecondDestLoc;
	sVECTOR3		vSecondDestLoc;	// ������ �̵��϶� ������ ���� ��ǥ
	BYTE			byDestLocCount;
	sVECTOR3		avDestLoc[DBO_MAX_NEXT_DEST_LOC_COUNT];
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_FOLLOWING
{
	DWORD			dwTimeStamp;
	BYTE			byMoveFlag;
	HOBJECT			hTarget; // Ÿ�� ���󰡱��϶� ���� Ÿ�� �ڵ�
	float			fDistance; // Ÿ�� �տ��� ���� �Ÿ�
	BYTE			byMovementReason; // ���� or ��ų��� ���� FOLLOW�� ������ ����
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_FALLING
{
	BYTE			byMoveDirection;		// ENtlMovementDirection
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_DASH_PASSIVE
{
	DWORD			dwTimeStamp;
	BYTE			byMoveDirection;		// NTL_MOVE_DASH_F, NTL_MOVE_DASH_B and so on
	sVECTOR3		vDestLoc;
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_TELEPORTING
{
	BYTE								byTeleportType;		// eTELEPORT_TYPE
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_SLIDING
{
	sVECTOR3		vShift;
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_KNOCKDOWN
{
	sVECTOR3		vShift;
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_FOCUSING
{
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_CASTING
{
	TBLIDX			skillId;
	HOBJECT			hTarget;
	DWORD			dwCastingTime;
	DWORD			dwCastingTimeRemaining;
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_SKILL_AFFECTING
{
	TBLIDX			skillId;
	HOBJECT			hTarget;
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_KEEPING_EFFECT
{
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_CASTING_ITEM
{
	TBLIDX			itemTblidx;
	HOBJECT			hTarget;
	DWORD			dwCastingTime;
	DWORD			dwCastingTimeRemaining;
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_STUNNED
{
	BYTE			byStunType;		// eDBO_STUN_TYPE
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_SLEEPING
{
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_PARALYZED
{
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_HTB
{
	TBLIDX				HTBId;			// HTB ��ų ID
	HOBJECT				hTarget;		// HTB Ÿ�� �ڵ�
	BYTE				byStepCount;	// HTB ���� ����
	BYTE				byCurStep;		// ���� ����
	BYTE				byResultCount;	// HTB ��ų ��� ����
	sHTBSKILL_RESULT	aHTBSkillResult[NTL_HTB_MAX_SKILL_COUNT_IN_SET]; // HTB ��ų ���
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_SANDBAG
{
	
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_CHARGING
{
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_BLOCKING
{
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_PRIVATESHOP
{
	sSUMMARY_PRIVATESHOP_SHOP_DATA		sSummaryPrivateShopData;
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_DIRECT_PLAY
{
	BYTE				byDirectPlayType; // ���� Ÿ�� ( eDIRECT_PLAY_TYPE )
	TBLIDX				directTblidx; // ���� TBLIDX
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_OPERATING
{
	HOBJECT				hTargetObject; // Ÿ�� ������Ʈ �ڵ�
	DWORD				dwOperateTime; // ���� �ð�
	TBLIDX				directTblidx; // ���� TBLIDX
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_RIDEON
{
	HOBJECT				hTarget; // Ÿ�� �ڵ�
};
//-----------------------------------------------------------------------------------
struct sCHARSTATE_TURNING
{
	TBLIDX				directTblidx; // ���� TBLIDX
	sVECTOR3			vDestDir;
};
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
struct sASPECTSTATE_SUPER_SAIYAN
{
	BYTE				bySourceGrade;
};
//-----------------------------------------------------------------------------------
struct sASPECTSTATE_PURE_MAJIN
{
	BYTE				bySourceGrade;
};
//-----------------------------------------------------------------------------------
struct sASPECTSTATE_GREAT_NAMEK
{
	BYTE				bySourceGrade;
};
//-----------------------------------------------------------------------------------
struct sASPECTSTATE_KAIOKEN
{
	BYTE				bySourceGrade;
	BYTE				byRepeatingCount;
};
//-----------------------------------------------------------------------------------
struct sASPECTSTATE_SPINNING_ATTACK
{
};
//-----------------------------------------------------------------------------------
struct sASPECTSTATE_VEHICLE
{
	//HOBJECT	hVehicleItem;
	TBLIDX		idVehicleTblidx;
	bool		bIsEngineOn;
};
//-----------------------------------------------------------------------------------
#pragma pack()