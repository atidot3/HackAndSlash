#ifndef CCLIENTSESSION_
# define CCLIENTSESSION_

#pragma once

#include "../Server/GameServer.h"
#include "Client.h"
#include <mutex>
#include "NtlSfx.h"
#include "../Game/Groupe/Groupe.h"
#include "../Game/Session/Session.h"
#include "NtlPacketEncoder_RandKey.h"
#include "../CharacterManager/CharacterManager.h"
#include "mysqlconn_wrapper.h"

enum AUTH_SESSION;
class Client;
class CAuthServer;
class CharacterManager;


#endif