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
