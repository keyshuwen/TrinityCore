/* ScriptData
Name: ace_vipscript
%Complete:
Comment: 
Category: vipscripts
EndScriptData */

#include "ScriptMgr.h"
#include "Chat.h"
#include "DBCStores.h"
#include "Log.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Pet.h"
#include "Player.h"
#include "RBAC.h"
#include "ReputationMgr.h"
#include "WorldSession.h"
#include "DatabaseEnv.h"
#include "World.h"
#include "Language.h"

class cs_ace_vip_extra : public PlayerScript
{
public:
    cs_ace_vip_extra() : PlayerScript("cs_ace_vip_extra") { }

    void OnGiveXP(Player* player, uint32& amount, Unit* /*victim*/)
    {
        amount += amount * player->m_xpRate;
    }

    void OnReputationChange(Player* player, uint32 /*factionId*/, int32& standing, bool /*incremental*/)
    {
        standing += standing * player->m_reputationRate;
    }

};

void AddSC_cs_ace_vip()
{
    new cs_ace_vip_extra();
}
