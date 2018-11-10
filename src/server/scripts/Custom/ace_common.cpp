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

#include "ace_common.h"
#include "QueryPackets.h"

AceMgr::AceMgr()
{
}

AceMgr* AceMgr::instance()
{
    static AceMgr instance;
    return &instance;
}

AceMgr::~AceMgr()
{
}

void AceMgr::LoadAceConfig()
{
    uint32 oldMSTime = getMSTime();

    // For reload case
    _aceConfigStore.clear();

    QueryResult result = WorldDatabase.Query("SELECT entry, value, cost FROM _ace_config");

    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 ACE Config. DB table `_ace_config` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        std::string entry = fields[0].GetString();
        AceConfig itr;
        itr.value = fields[1].GetUInt32();
        itr.cost = fields[2].GetUInt32();

        //insert
        _aceConfigStore[entry] = itr;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u ACE Config in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

void AceMgr::SetAccountExtra(uint32 accountId)
{
    QueryResult result = LoginDatabase.PQuery("SELECT id FROM _ace_account_Extra WHERE id = %u", accountId);
    if (!result)
        LoginDatabase.PExecute("INSERT INTO _ace_account_Extra(id, jf) VALUES(%u, 0)", accountId);
}

uint32 AceMgr::Getjf(uint32 accountId) const
{
    QueryResult result = LoginDatabase.PQuery("SELECT jf FROM _ace_account_Extra WHERE id = %u", accountId);
    return (result) ? (*result)[0].GetUInt32() : 0;
}

void AceMgr::Addjf(uint32 accountId, int32 value)
{
    int32 Accountjf = Getjf(accountId);
    int32 amount = Accountjf + value;
    if (amount > 0)
    {
        LoginDatabase.PExecute("UPDATE _ace_account_Extra SET jf = %u WHERE id = %u", amount, accountId);
    }
}
void AceMgr::LoadAceVipSystem()
{
    uint32 oldMSTime = getMSTime();

    // For reload case
    _aceVipSystemStore.clear();

    QueryResult result = WorldDatabase.Query("SELECT entry, title, nameColor, chatColor, reqItem, jfCost, everyDayItem, addAutojf, lootRate, healthRate, dmgRate, cureRate, xpRate, reputationRate, adduppro, aura, talent, description FROM _ace_vip_system");

    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 Ace Vip System. DB table `_ace_vip_system` is empty.");
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 entry = fields[0].GetUInt32();
        AceVipSystem itr;
        itr.title = fields[1].GetString();
        itr.nameColor = fields[2].GetString();
        itr.chatColor = fields[3].GetString();
        itr.reqItem= fields[4].GetUInt32();
        itr.jfCost = fields[5].GetUInt32();
        itr.everyDayItem = fields[6].GetUInt32();
        itr.addAutojf = fields[7].GetUInt32();
        itr.lootRate = fields[8].GetFloat();
        itr.healthRate = fields[9].GetFloat();
        itr.dmgRate = fields[10].GetFloat();
        itr.cureRate = fields[11].GetFloat();
        itr.xpRate = fields[12].GetFloat();
        itr.reputationRate = fields[13].GetFloat();
        itr.adduppro = fields[14].GetFloat();
        itr.aura = fields[15].GetUInt32();
        itr.talent = fields[16].GetUInt32();
        itr.description = fields[17].GetString();

        //insert
        _aceVipSystemStore[entry] = itr;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u Ace Vip System in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}

uint32 AceMgr::GetVipLevel(uint32 accountId) const
{
    QueryResult result = LoginDatabase.PQuery("SELECT viplevel FROM _ace_account_Extra WHERE id = %u", accountId);
    return (result) ? (*result)[0].GetUInt32() : 0;
}

void AceMgr::SetVipLevel(uint32 accountId, uint32 value)
{
    LoginDatabase.PExecute("UPDATE _ace_account_Extra SET viplevel = %u WHERE id = %u", value, accountId);
}

void AceMgr::ResetVipAura(Player* player)
{
    if (_aceVipSystemStore.empty())
        return;

    //For
    AceVipSystemContainer::const_iterator itr = _aceVipSystemStore.begin();
    while (itr != _aceVipSystemStore.end())
    {
        if (&itr->second && itr->second.aura && player->HasAura(itr->second.aura))
            player->RemoveAurasDueToSpell(itr->second.aura);
        ++itr;
    }

}
