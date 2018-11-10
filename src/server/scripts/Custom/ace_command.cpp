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
#include "ace_common.h"

class cs_ace_commandscript : public CommandScript
{
public:
    cs_ace_commandscript() : CommandScript("cs_ace_commandcript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> ReLoadAceConfigCommandTable =
        {
            { "aceConfig",    rbac::RBAC_PERM_COMMAND_ACE_RELOAD_ACECONFIG,              true, &HandleAceReaceConfigCommand,        "" },
            { "vipSystem",    rbac::RBAC_PERM_COMMAND_ACE_RELOAD_VIPSYSTEM,              true, &HandleAceVipSystemCommand,          "" },
        };

        static std::vector<ChatCommand> aceCommandTable =
        {
            { "jf",           rbac::RBAC_PERM_COMMAND_ACE_JF,                            true, &HandleAceAddjfCommand,              "" },
            { "vip",          rbac::RBAC_PERM_COMMAND_ACE_VIP,                           true, &HandleAceAddvipCommand,             "" },
            { "reLoad",       rbac::RBAC_PERM_COMMAND_ACE_RELOAD,                        true, nullptr,        "" , ReLoadAceConfigCommandTable },
        };
        static std::vector<ChatCommand> HandleAceCommandTable =
        {
            { "ace",          rbac::RBAC_PERM_COMMAND_ACE,                               true, nullptr,         "", aceCommandTable },
        };

        return HandleAceCommandTable;
    }
    static bool HandleAceReaceConfigCommand(ChatHandler* handler, char const* args)
    {
        TC_LOG_INFO("misc", "Re-Loading `_ace_config` Table!");
        sAceMgr->LoadAceConfig();
        handler->SendGlobalGMSysMessage("DB table `_ace_config` reloaded.");
        return true;
    }
    static bool HandleAceAddjfCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* target = handler->getSelectedPlayerOrSelf();
        if (!target)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            return true;
        }

        uint32 useramount = sAceMgr->Getjf(target->GetSession()->GetAccountId());
        int32 amount = atoi(args);
        int32 Accountjf = useramount + amount;
        if (Accountjf < 0)
            Accountjf = 0;

        sAceMgr->Addjf(target->GetSession()->GetAccountId(), amount);
        handler->PSendSysMessage(LANG_ACE_COMMAND_MODIFY_JF, target->GetName(), useramount, amount, Accountjf);
        return true;
    }
    static bool HandleAceVipSystemCommand(ChatHandler* handler, char const* args)
    {
        TC_LOG_INFO("misc", "Re-Loading `_ace_vip_system` Table!");
        sAceMgr->LoadAceVipSystem();
        handler->SendGlobalGMSysMessage("DB table `_ace_vip_system` reloaded.");
        return true;
    }
    static bool HandleAceAddvipCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* target = handler->getSelectedPlayerOrSelf();
        if (!target)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            return true;
        }

        uint32 amount = atoi(args);
        if (amount < 0)
            amount = 0;

        sAceMgr->SetVipLevel(target->GetSession()->GetAccountId(), amount);
        handler->PSendSysMessage(LANG_ACE_COMMAND_MODIFY_VIP, target->GetName(), amount);
        return true;
    }
};

void AddSC_cs_ace_command()
{
    new cs_ace_commandscript();
}
