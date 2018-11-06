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

#ifndef SC_ACE_COMMON_H
#define SC_ACE_COMMON_H

#include "Common.h"
#include "DatabaseEnv.h"
#include "DatabaseEnvFwd.h"
#include "Errors.h"
#include "GameTime.h"
#include "Log.h"
#include <map>
#include <unordered_map>

struct AceConfig
{
    uint32 value;
    uint32 cost;
};

class TC_GAME_API AceMgr
{
    private:
        AceMgr();
        ~AceMgr();

    public:
        static AceMgr* instance();

        void LoadAceConfig();
        typedef std::unordered_map<std::string, AceConfig> AceConfigContainer;
        AceConfig const* GetAceConfig(std::string entry) const
        {
            AceConfigContainer::const_iterator itr = _aceConfigStore.find(entry);
            return itr != _aceConfigStore.end() ? &itr->second : nullptr;
        }
       
    private:
        AceConfigContainer _aceConfigStore;

};

#define sAceMgr AceMgr::instance()

#endif
