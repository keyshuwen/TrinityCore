/* ScriptData
Name: ace_vipscript
%Complete:
Comment: 
Category: vipscripts
EndScriptData */

#include "ScriptMgr.h"
#include "Chat.h"
#include "Log.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "RBAC.h"
#include "WorldSession.h"
#include "World.h"
#include "Language.h"
#include "ace_common.h"

std::string GetNameLink(Player* player, bool type)
{
    char* sIcon = "";

    if (type)
    {
        switch (player->getRace())
        {
        case RACE_HUMAN:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Human_Male:16:16:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Human_Female:16:16:1:-3|t";
            break;
        }
        case RACE_ORC:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Orc_Male:16:16:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Orc_Female:16:16:1:-3|t";
            break;
        }
        case RACE_DWARF:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Dwarf_Male:16:16:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Dwarf_Female:16:16:1:-3|t";
            break;
        }
        case RACE_NIGHTELF:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Nightelf_Male:16:16:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Nightelf_Female:16:16:1:-3|t";
            break;
        }
        case RACE_UNDEAD_PLAYER:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Undead_Male:16:16:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Undead_Female:16:16:1:-3|t";
            break;
        }
        case RACE_GNOME:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Gnome_Male:16:16:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Gnome_Female:16:16:1:-3|t";
            break;
        }
        case RACE_TROLL:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Troll_Male:16:16:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Troll_Female:16:16:1:-3|t";
            break;
        }
        case RACE_BLOODELF:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Bloodelf_Male:16:16:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Bloodelf_Female:16:16:1:-3|t";
            break;
        }
        case RACE_DRAENEI:
        {
            if (player->getGender() == 0)
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Draenei_Male:16:16:1:-3|t";
            else
                sIcon = "|TInterface\\ICONS\\Achievement_Character_Draenei_Female:16:16:1:-3|t";
            break;
        }

        default:
            break;
        }

    }
    else
    {
        switch (player->getClass())
        {
            case CLASS_WARRIOR:
                sIcon = "|TInterface\\ICONS\\INV_Sword_27:16:16:1:-3|t";
                break;
            case CLASS_PALADIN:
                sIcon = "|TInterface\\ICONS\\INV_Hammer_01:16:16:1:-3|t";
                break;
            case CLASS_HUNTER:
                sIcon = "|TInterface\\ICONS\\INV_Weapon_Bow_07:16:16:1:-3|t";
                break;
            case CLASS_ROGUE:
                sIcon = "|TInterface\\ICONS\\INV_ThrowingKnife_04:16:16:1:-3|t";
                break;
            case CLASS_PRIEST:
                sIcon = "|TInterface\\ICONS\\INV_Staff_30:16:16:1:-3|t";
                break;
            case CLASS_DEATH_KNIGHT:
                sIcon = "|TInterface\\ICONS\\Spell_Deathknight_ClassIcon:16:16:1:-3|t";
                break;
            case CLASS_SHAMAN:
                sIcon = "|TInterface\\ICONS\\Spell_Nature_BloodLust:16:16:1:-3|t";
                break;
            case CLASS_MAGE:
                sIcon = "|TInterface\\ICONS\\INV_Staff_13:16:16:1:-3|t";
                break;
            case CLASS_WARLOCK:
                sIcon = "|TInterface\\ICONS\\Spell_Nature_FaerieFire:16:16:1:-3|t";
                break;
            case CLASS_DRUID:
                sIcon = "|TInterface\\ICONS\\Ability_Druid_Maul:16:16:1:-3|t";
                break;
            default:
                break;
        }
    }
    return sIcon;
}

class cs_ace_world_chat : public CommandScript
{
public:
    cs_ace_world_chat() : CommandScript("cs_ace_world_chat") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> HandleWorldChatCommandTable =
        {
            { "sj",  rbac::RBAC_PERM_COMMAND_ACE_WORLD_CHAT,      true,    &HandleWorldChatCommand,     "" },
            { "zy",  rbac::RBAC_PERM_COMMAND_ACE_FACTION_CHAT,    true,    &HandleFactionChatCommand,   "" },
        };
        return HandleWorldChatCommandTable;
    }

    static bool HandleWorldChatCommand(ChatHandler* handler, const char* args)
    {
        if (!args)
            return false;

        AceConfig const* itr = sAceMgr->GetAceConfig("Player.world.chat");
        if (!itr || itr->value == 0)
            return false;

        Player * player = handler->GetSession()->GetPlayer();

        //check Cost
        uint32 checkCost = 0;
        if (itr->cost)
        {
            if (itr->value == 2 || itr->value == 5)
            {
                checkCost = sAceMgr->Getjf(player->GetSession()->GetAccountId());
                if (checkCost < itr->cost)
                    return false;
            }
            else
            {    //item cost
                if (itr->value == 3 || itr->value == 6)
                {
                    checkCost = itr->cost;
                    if (!player->HasItemCount(checkCost, 1))
                        return false;
                }
                else
                {
                    checkCost = player->GetMoney();
                    if (checkCost < itr->cost)
                        return false;
                }
            }
        }

        std::string CostjfString = player->GetSession()->GetTrinityString(LANG_ACE_PLAYER_COST_JF);
        std::string sIcon = GetNameLink(player, true);
        std::string title = player->m_title;
        std::string name = "|";
        name += player->m_nameColor;
        name += player->GetName();
        name += "|r";

        std::string msg = "|";
        msg += player->m_chatColor;
        msg += args;
        msg += "|r";

        switch (itr->value)
        {
            case 1:
            {
                sWorld->SendWorldText(LANG_ACE_PLAYER_WORLD_CHAT, sIcon.c_str(), name.c_str(), title.c_str(), msg.c_str());
                if (checkCost)
                    player->ModifyMoney(-int32(itr->cost));
                break;
            }
            case 2:
            {
                sWorld->SendWorldText(LANG_ACE_PLAYER_WORLD_CHAT, sIcon.c_str(), name.c_str(), title.c_str(), msg.c_str());
                if (checkCost)
                {
                    sAceMgr->Addjf(player->GetSession()->GetAccountId(), -int32(itr->cost));
                    player->GetSession()->SendNotification(CostjfString.c_str(), itr->cost);
                }   
                break;
            }
            case 3:
            {
                sWorld->SendWorldText(LANG_ACE_PLAYER_WORLD_CHAT, sIcon.c_str(), name.c_str(), title.c_str(), msg.c_str());
                if (checkCost)
                    player->DestroyItemCount(itr->cost, 1, true);
                break;
            }
            case 4:
            {
                sWorld->SendWorldText(LANG_ACE_PLAYER_WORLD_CHAT, sIcon.c_str(), title.c_str(), name.c_str(), msg.c_str());
                if (checkCost)
                    player->ModifyMoney(-int32(itr->cost));
                break;
            }
            case 5:
            {
                sWorld->SendWorldText(LANG_ACE_PLAYER_WORLD_CHAT, sIcon.c_str(), title.c_str(), name.c_str(), msg.c_str());
                if (checkCost)
                {
                    sAceMgr->Addjf(player->GetSession()->GetAccountId(), -int32(itr->cost));
                    player->GetSession()->SendNotification(CostjfString.c_str(), itr->cost);
                }
                break;
            }
            case 6:
            {
                sWorld->SendWorldText(LANG_ACE_PLAYER_WORLD_CHAT, sIcon.c_str(), title.c_str(), name.c_str(), msg.c_str());
                if (checkCost)
                    player->DestroyItemCount(itr->cost, 1, true);
                break;
            }
            default:
                sWorld->SendWorldText(LANG_ACE_PLAYER_WORLD_CHAT, sIcon.c_str(), name.c_str(), title.c_str(), msg.c_str());
                if (checkCost)
                    player->ModifyMoney(-int32(itr->cost));
                break;
        }

        return true;
    }

    static bool HandleFactionChatCommand(ChatHandler* handler, const char* args)
    {
        if (!args)
            return false;

        AceConfig const* itr = sAceMgr->GetAceConfig("Player.world.Facttion.chat");
        if (!itr || itr->value == 0)
            return false;

        Player * player = handler->GetSession()->GetPlayer();

        //check Cost
        uint32 checkCost = 0;
        if (itr->cost)
        {
            if (itr->value == 2 || itr->value == 5)
            {
                checkCost = sAceMgr->Getjf(player->GetSession()->GetAccountId());
                if (checkCost < itr->cost)
                    return false;
            }
            else
            {    //item cost
                if (itr->value == 3 || itr->value == 6)
                {
                    checkCost = itr->cost;
                    if (!player->HasItemCount(checkCost, 1))
                        return false;
                }
                else
                {
                    checkCost = player->GetMoney();
                    if (checkCost < itr->cost)
                        return false;
                }
            }
        }

        std::string CostjfString = player->GetSession()->GetTrinityString(LANG_ACE_PLAYER_COST_JF);
        std::string sIcon = GetNameLink(player, false);
        std::string title = player->m_title;
        std::string name = "|";
        name += player->m_nameColor;
        name += player->GetName();
        name += "|r";

        std::string msg = "|";
        msg += player->m_chatColor;
        msg += args;
        msg += "|r";

        switch (itr->value)
        {
            case 1:
            {
                sWorld->SendFactionText(LANG_ACE_PLAYER_FACTION_CHAT, player->GetTeam(), sIcon.c_str(), name.c_str(), title.c_str(), msg.c_str());
                if (checkCost)
                    player->ModifyMoney(-int32(itr->cost));
                break;
            }
            case 2:
            {
                sWorld->SendFactionText(LANG_ACE_PLAYER_FACTION_CHAT, player->GetTeam(), sIcon.c_str(), name.c_str(), title.c_str(), msg.c_str());
                if (checkCost)
                {
                    sAceMgr->Addjf(player->GetSession()->GetAccountId(), -int32(itr->cost));
                    player->GetSession()->SendNotification(CostjfString.c_str(), itr->cost);
                }
                break;
            }
            case 3:
            {
                sWorld->SendFactionText(LANG_ACE_PLAYER_FACTION_CHAT, player->GetTeam(), sIcon.c_str(), name.c_str(), title.c_str(), msg.c_str());
                if (checkCost)
                    player->DestroyItemCount(itr->cost, 1, true);
                break;
            }
            case 4:
            {
                sWorld->SendFactionText(LANG_ACE_PLAYER_FACTION_CHAT, player->GetTeam(), sIcon.c_str(), title.c_str(), name.c_str(), msg.c_str());
                if (checkCost)
                    player->ModifyMoney(-int32(itr->cost));
                break;
            }
            case 5:
            {
                sWorld->SendFactionText(LANG_ACE_PLAYER_FACTION_CHAT, player->GetTeam(), sIcon.c_str(), title.c_str(), name.c_str(), msg.c_str());
                if (checkCost)
                {
                    sAceMgr->Addjf(player->GetSession()->GetAccountId(), -int32(itr->cost));
                    player->GetSession()->SendNotification(CostjfString.c_str(), itr->cost);
                }
                break;
            }
            case 6:
            {
                sWorld->SendFactionText(LANG_ACE_PLAYER_FACTION_CHAT, player->GetTeam(), sIcon.c_str(), title.c_str(), name.c_str(), msg.c_str());
                if (checkCost)
                    player->DestroyItemCount(itr->cost, 1, true);
                break;
            }
            default:
                sWorld->SendFactionText(LANG_ACE_PLAYER_FACTION_CHAT, player->GetTeam(), sIcon.c_str(), name.c_str(), title.c_str(), msg.c_str());
                if (checkCost)
                    player->ModifyMoney(-int32(itr->cost));
                break;
        }

        return true;
    }
};

void AddSC_cs_ace_world_chat()
{
    new cs_ace_world_chat();
}
