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
#include "RBAC.h"
#include "ReputationMgr.h"
#include "WorldSession.h"
#include "DatabaseEnv.h"
#include "World.h"
#include "Language.h"
#include "Chat.h"
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
        TC_LOG_INFO("server.loading", "Loaded Ace Vip System...");
        sAceMgr->LoadAceVipSystem();

        TC_LOG_INFO("server.loading", "Now you ready to play.");
    }
};

class cs_ace_config : public PlayerScript
{
public:
    cs_ace_config() : PlayerScript("cs_ace_config") { }

    void OnLogin(Player* player, bool loginFirst) override
    {
        AceConfig const* itr;

        //vip login
        player->m_vipLevel = sAceMgr->GetVipLevel(player->GetSession()->GetAccountId());
        player->m_title = "";
        player->m_nameColor = "";
        player->m_chatColor = "";
        player->m_addAutojf = 0;
        player->m_lootRate = 0.0f;
        player->m_healthRate = 0.0f;
        player->m_dmgRate = 0.0f;
        player->m_cureRate = 0.0f;
        player->m_xpRate = 0.0f;
        player->m_reputationRate = 0.0f;
        player->m_adduppro = 0.0f;
        player->m_vipAura = 0;
        player->m_talent = 0;

        std::string description;
        uint32 extra_talent = 0;
        itr = sAceMgr->GetAceConfig("Player.vipSystem");
        AceVipSystem const* vipitr = sAceMgr->GetAceVipSystem(player->m_vipLevel);
        if (vipitr && itr && itr->value == 1)
        {
            player->m_title = vipitr->title;
            player->m_nameColor = vipitr->nameColor;
            player->m_chatColor = vipitr->chatColor;
            player->m_addAutojf = vipitr->addAutojf;
            player->m_lootRate = vipitr->lootRate;
            player->m_healthRate = vipitr->healthRate;
            player->m_dmgRate = vipitr->dmgRate;
            player->m_cureRate = vipitr->cureRate;
            player->m_xpRate = vipitr->xpRate;
            player->m_reputationRate = vipitr->reputationRate;
            player->m_adduppro = vipitr->adduppro;
            player->m_vipAura = vipitr->aura;
            player->m_talent = vipitr->talent;
            description = vipitr->description;

            //Reset Health
            if (player->m_healthRate)
            {
                player->UpdateAllStats();
                player->SetHealth(player->GetMaxHealth());
            }
        }

        //Talent
        extra_talent = player->m_talent;
        extra_talent += player->m_extra_talent;

        //Init extra Talent
        if (extra_talent)
            player->InitTalentForLevel();

        //Init Aura
        sAceMgr->ResetVipAura(player);
        if (player->m_vipAura)
            player->AddAura(player->m_vipAura, player);

        // login hint
        itr = sAceMgr->GetAceConfig("Player.login");
        if (itr && itr->value >= 1)
        {
            if (player->m_nameColor.empty())
                player->m_nameColor = "cFFFF00CC";

            std::string name = "|";
            name += player->m_nameColor;
            name += player->GetName();
            name += "|r";

            std::string title = player->m_title;

            std::string raceName = player->GetSession()->GetTrinityString(LANG_COMMAND_GRAVEYARD_HORDE);   //horde
            if (player->GetTeam() == ALLIANCE)
                raceName = player->GetSession()->GetTrinityString(LANG_COMMAND_GRAVEYARD_ALLIANCE);        //alliance

            switch (itr->value)
            {
                case 1:     //First
                {
                    if (!loginFirst)
                        break;

                    if (itr->cost == 1)
                        sWorld->SendWorldText(LANG_ACE_PLAYER_LONGIN_FIRST, title.c_str(), name.c_str(), raceName.c_str());
                    else
                        sWorld->SendWorldText(LANG_ACE_PLAYER_LONGIN_FIRST, name.c_str(), title.c_str(), raceName.c_str());
                    break;
                }
                case 2:    
                {
                    if (loginFirst)
                        break;
  
                    if (itr->cost == 1)
                        sWorld->SendWorldText(LANG_ACE_PLAYER_LONGIN, title.c_str(), name.c_str(), raceName.c_str());
                    else
                        sWorld->SendWorldText(LANG_ACE_PLAYER_LONGIN, name.c_str(), title.c_str(), raceName.c_str());

                    break;
                }
                case 3:   //all
                {
                    if (loginFirst)
                    {
                        if (itr->cost == 1)
                            sWorld->SendWorldText(LANG_ACE_PLAYER_LONGIN_FIRST, title.c_str(), name.c_str(), raceName.c_str());
                        else
                            sWorld->SendWorldText(LANG_ACE_PLAYER_LONGIN_FIRST, name.c_str(), title.c_str(), raceName.c_str());
                    }
                    else
                    {
                        if (itr->cost == 1)
                            sWorld->SendWorldText(LANG_ACE_PLAYER_LONGIN, title.c_str(), name.c_str(), raceName.c_str());
                        else
                            sWorld->SendWorldText(LANG_ACE_PLAYER_LONGIN, name.c_str(), title.c_str(), raceName.c_str());
                    }

                    break;
                }
            default:
                break;
            }
        }

        //vip description
        if (!description.empty())
            ChatHandler(player->GetSession()).SendSysMessage(description.c_str());
    }
};

class cs_ace_ActionLogin : public AccountScript
{
public:
    cs_ace_ActionLogin() : AccountScript("cs_ace_ActionLogin") { }

    void OnAccountLogin(uint32 accountId) override
    {
        sAceMgr->SetAccountExtra(accountId);
    }
};

void AddSC_cs_ace_config()
{
    new cs_ace_PrepareToPlay();
    new cs_ace_config();
    new cs_ace_ActionLogin();
}
