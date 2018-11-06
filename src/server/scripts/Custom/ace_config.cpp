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
#include "ace_common.h"

class cs_ace_PrepareToPlay : public WorldScript
{
public:
    cs_ace_PrepareToPlay() : WorldScript("cs_ace_PrepareToPlay") { }

    void OnStartup() override
    {
        TC_LOG_INFO("server.loading", "=========================================================================================");
        TC_LOG_INFO("server.loading", "Loaded ACE Config...");
        sAceMgr->LoadAceConfig();

        TC_LOG_INFO("server.loading", "Now you ready to play.");
    }
};

class cs_ace_config : public PlayerScript
{
public:
    cs_ace_config() : PlayerScript("cs_ace_config") { }

    void OnLogin(Player* player, bool loginFirst)
    {
        // login hint
        AceConfig const* itr = sAceMgr->GetAceConfig("Player.login");
        if (itr)
        {
            if (loginFirst)
                sWorld->SendWorldText(LANG_ACE_PLAYER_LONGIN_FIRST, player->GetName().c_str());
            else
                sWorld->SendWorldText(LANG_ACE_PLAYER_LONGIN, player->GetName().c_str());
        }
    }
};

void AddSC_cs_ace_config()
{
    new cs_ace_PrepareToPlay();
    new cs_ace_config();
}
