/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
