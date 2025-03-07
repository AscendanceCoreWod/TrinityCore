/*
 * Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
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

#ifndef QuestPackets_h__
#define QuestPackets_h__

#include "Packet.h"
#include "QuestDef.h"
#include "ObjectGuid.h"
#include "ItemPackets.h"

namespace WorldPackets
{
    namespace Quest
    {
        class QuestGiverStatusQuery final : public ClientPacket
        {
        public:
            QuestGiverStatusQuery(WorldPacket&& packet) : ClientPacket(CMSG_QUEST_GIVER_STATUS_QUERY, std::move(packet)) { }

            void Read() override;

            ObjectGuid QuestGiverGUID;
        };

        // Empty packet, server replies with quest giver status of visible creatures
        class QuestGiverStatusMultipleQuery final : public ClientPacket
        {
        public:
            QuestGiverStatusMultipleQuery(WorldPacket&& packet) : ClientPacket(CMSG_QUEST_GIVER_STATUS_MULTIPLE_QUERY, std::move(packet)) { }

            void Read() override { }
        };

        struct QuestGiverInfo
        {
            QuestGiverInfo() { }
            QuestGiverInfo(ObjectGuid const& guid, uint32 status)
                : Guid(guid), Status(status) { }

            ObjectGuid Guid;
            uint32 Status = DIALOG_STATUS_NONE;
        };

        class QuestGiverStatus final : public ServerPacket
        {
        public:
            QuestGiverStatus() : ServerPacket(SMSG_QUEST_GIVER_STATUS, 22) { }

            WorldPacket const* Write() override;

            QuestGiverInfo QuestGiver;
        };

        class QuestGiverStatusMultiple final : public ServerPacket
        {
        public:
            QuestGiverStatusMultiple() : ServerPacket(SMSG_QUEST_GIVER_STATUS_MULTIPLE, 24) { }

            WorldPacket const* Write() override;

            std::vector<QuestGiverInfo> QuestGiver;
        };

        class QuestGiverHello final : public ClientPacket
        {
        public:
            QuestGiverHello(WorldPacket&& packet) : ClientPacket(CMSG_QUEST_GIVER_HELLO, std::move(packet)) { }

            void Read() override;

            ObjectGuid QuestGiverGUID;
        };

        class QueryQuestInfo final : public ClientPacket
        {
        public:
            QueryQuestInfo(WorldPacket&& packet) : ClientPacket(CMSG_QUERY_QUEST_INFO, std::move(packet)) { }

            void Read() override;

            ObjectGuid QuestGiver;
            int32 QuestID = 0;
        };

        struct QuestInfoChoiceItem
        {
            int32 ItemID = 0;
            int32 Quantity = 0;
            int32 DisplayID = 0;
        };

        struct QuestInfo
        {
            int32 QuestID                   = 0;
            int32 QuestType                 = 0; // Accepted values: 0, 1 or 2. 0 == IsAutoComplete() (skip objectives/details)
            int32 QuestLevel                = 0; // may be -1, static data, in other cases must be used dynamic level: Player::GetQuestLevel (0 is not known, but assuming this is no longer valid for quest intended for client)
            int32 QuestPackageID            = 0;
            int32 QuestMinLevel             = 0;
            int32 QuestSortID               = 0; // zone or sort to display in quest log
            int32 QuestInfoID               = 0;
            int32 SuggestedGroupNum         = 0;
            int32 RewardNextQuest           = 0; // client will request this quest from NPC, if not 0
            int32 RewardXPDifficulty        = 0; // used for calculating rewarded experience
            float RewardXPMultiplier        = 1.0f;
            int32 RewardMoney               = 0; // reward money (below max lvl)
            int32 RewardMoneyDifficulty     = 0;
            float RewardMoneyMultiplier     = 1.0f;
            int32 RewardBonusMoney          = 0;
            int32 RewardDisplaySpell        = 0; // reward spell, this spell will be displayed (icon)
            int32 RewardSpell               = 0;
            int32 RewardHonor               = 0;
            float RewardKillHonor           = 0.0f;
            int32 StartItem                 = 0;
            uint32 Flags                    = 0;
            uint32 FlagsEx                  = 0;
            int32 POIContinent              = 0;
            float POIx                      = 0.0f;
            float POIy                      = 0.0f;
            int32 POIPriority               = 0;
            int32 AllowableRaces            = -1;
            std::string LogTitle;
            std::string LogDescription;
            std::string QuestDescription;
            std::string AreaDescription;
            int32 RewardTitle               = 0; // new 2.4.0, player gets this title (id from CharTitles)
            int32 RewardTalents             = 0;
            int32 RewardArenaPoints         = 0;
            int32 RewardSkillLineID         = 0; // reward skill id
            int32 RewardNumSkillUps         = 0; // reward skill points
            int32 PortraitGiver             = 0; // quest giver entry ?
            int32 PortraitTurnIn            = 0; // quest turn in entry ?
            std::string PortraitGiverText;
            std::string PortraitGiverName;
            std::string PortraitTurnInText;
            std::string PortraitTurnInName;
            std::string QuestCompletionLog;
            int32 RewardFactionFlags        = 0; // rep mask (unsure on what it does)
            int32 AcceptedSoundKitID        = 0;
            int32 CompleteSoundKitID        = 0;
            int32 AreaGroupID               = 0;
            int32 TimeAllowed               = 0;
            std::vector<QuestObjective> Objectives;
            int32 RewardItems[QUEST_REWARD_ITEM_COUNT] = {};
            int32 RewardAmount[QUEST_REWARD_ITEM_COUNT] = {};
            int32 ItemDrop[QUEST_ITEM_DROP_COUNT] = {};
            int32 ItemDropQuantity[QUEST_ITEM_DROP_COUNT] = {};
            QuestInfoChoiceItem UnfilteredChoiceItems[QUEST_REWARD_CHOICES_COUNT];
            int32 RewardFactionID[QUEST_REWARD_REPUTATIONS_COUNT] = {};
            int32 RewardFactionValue[QUEST_REWARD_REPUTATIONS_COUNT] = {};
            int32 RewardFactionOverride[QUEST_REWARD_REPUTATIONS_COUNT] = {};
            int32 RewardCurrencyID[QUEST_REWARD_CURRENCY_COUNT] = {};
            int32 RewardCurrencyQty[QUEST_REWARD_CURRENCY_COUNT] = {};
        };

        class QueryQuestInfoResponse final : public ServerPacket
        {
        public:
            QueryQuestInfoResponse() : ServerPacket(SMSG_QUERY_QUEST_INFO_RESPONSE, 1200) { }

            WorldPacket const* Write() override;

            bool Allow = false;
            QuestInfo Info;
            uint32 QuestID = 0;
        };

        class QuestUpdateAddCredit final : public ServerPacket
        {
        public:
            QuestUpdateAddCredit() : ServerPacket(SMSG_QUEST_UPDATE_ADD_CREDIT, 16+4+4+2+2+1) { }

            WorldPacket const* Write() override;

            ObjectGuid VictimGUID;
            int32 ObjectID      = 0;
            int32 QuestID       = 0;
            uint16 Count        = 0;
            uint16 Required     = 0;
            uint8 ObjectiveType = 0;
        };

        struct QuestChoiceItem
        {
            int32 ItemID    = 0;
            int32 Quantity  = 0;
        };

        struct QuestRewards
        {
            int32 ChoiceItemCount           = 0;
            int32 ItemCount                 = 0;
            int32 Money                     = 0;
            int32 XP                        = 0;
            int32 Title                     = 0;
            int32 Talents                   = 0;
            int32 FactionFlags              = 0;
            int32 SpellCompletionDisplayID  = 0;
            int32 SpellCompletionID         = 0;
            int32 SkillLineID               = 0;
            int32 NumSkillUps               = 0;
            QuestChoiceItem ChoiceItems[QUEST_REWARD_CHOICES_COUNT];
            int32 ItemID[QUEST_REWARD_ITEM_COUNT] = {};
            int32 ItemQty[QUEST_REWARD_ITEM_COUNT] = {};
            int32 FactionID[QUEST_REWARD_REPUTATIONS_COUNT] = {};
            int32 FactionValue[QUEST_REWARD_REPUTATIONS_COUNT] = {};
            int32 FactionOverride[QUEST_REWARD_REPUTATIONS_COUNT] = {};
            int32 CurrencyID[QUEST_REWARD_CURRENCY_COUNT] = {};
            int32 CurrencyQty[QUEST_REWARD_CURRENCY_COUNT] = {};
        };

        struct QuestDescEmote
        {
            QuestDescEmote(int32 type = 0, uint32 delay = 0) : Type(type), Delay(delay) {}
            int32 Type;
            uint32 Delay;
        };

        struct QuestGiverOfferReward
        {
            ObjectGuid QuestGiverGUID;
            int32 QuestGiverCreatureID      = 0;
            int32 QuestID                   = 0;
            bool AutoLaunched               = false;
            int32 SuggestedPartyMembers     = 0;
            QuestRewards Rewards;
            std::vector<QuestDescEmote> Emotes;
            int32 QuestFlags[2]             = {}; // Flags and FlagsEx
        };

        class QuestGiverOfferRewardMessage final : public ServerPacket
        {
        public:
            QuestGiverOfferRewardMessage() : ServerPacket(SMSG_QUEST_GIVER_OFFER_REWARD_MESSAGE, 600) { }

            WorldPacket const* Write() override;

            int32 PortraitTurnIn = 0;
            int32 PortraitGiver = 0;
            std::string PortraitGiverText;
            std::string QuestTitle;
            std::string PortraitTurnInText;
            std::string PortraitGiverName;
            std::string RewardText;
            std::string PortraitTurnInName;
            QuestGiverOfferReward QuestData;
            int32 QuestPackageID = 0;
        };

        class QuestGiverChooseReward final : public ClientPacket
        {
        public:
            QuestGiverChooseReward(WorldPacket&& packet) : ClientPacket(CMSG_QUEST_GIVER_CHOOSE_REWARD, std::move(packet)) { }

            void Read() override;

            ObjectGuid QuestGiverGUID;
            int32 QuestID = 0;
            int32 ItemChoiceID = 0;
        };

        class QuestGiverQuestComplete final : public ServerPacket
        {
        public:
            QuestGiverQuestComplete() : ServerPacket(SMSG_QUEST_GIVER_QUEST_COMPLETE, 40) { }

            WorldPacket const* Write() override;

            bool UseQuestReward     = false;
            int32 SkillLineIDReward = 0;
            int32 MoneyReward       = 0;
            int32 NumSkillUpsReward = 0;
            int32 XPReward          = 0;
            int32 QuestID           = 0;
            int32 TalentReward      = 0;
            bool LaunchGossip       = 0;

            // Not in JAM struct
            WorldPackets::Item::ItemInstance ItemReward;
        };

        class QuestGiverCompleteQuest final : public ClientPacket
        {
        public:
            QuestGiverCompleteQuest(WorldPacket&& packet) : ClientPacket(CMSG_QUEST_GIVER_COMPLETE_QUEST, std::move(packet)) { }

            void Read() override;

            ObjectGuid QuestGiverGUID; // NPC / GameObject guid for normal quest completion. Player guid for self-completed quests
            int32 QuestID = 0;
            bool FromScript = false; // 0 - standart complete quest mode with npc, 1 - auto-complete mode
        };

        struct QuestObjectiveSimple
        {
            int32 ID        = 0;
            int32 ObjectID  = 0;
            int32 Amount    = 0;
            uint8 Type      = 0;
        };

        class QuestGiverQuestDetails final : public ServerPacket
        {
        public:
            QuestGiverQuestDetails() : ServerPacket(SMSG_QUEST_GIVER_QUEST_DETAILS, 1000) { }

            WorldPacket const* Write() override;

            ObjectGuid QuestGiverGUID;
            ObjectGuid InformUnit;
            int32 QuestID           = 0;
            int32 QuestPackageID    = 0;
            uint32 QuestFlags[2]    = {};
            int32 SuggestedPartyMembers = 0;
            QuestRewards Rewards;
            std::vector<QuestObjectiveSimple> Objectives;
            std::vector<QuestDescEmote> DescEmotes;
            std::vector<int32> LearnSpells;
            int32 PortraitTurnIn = 0;
            int32 PortraitGiver = 0;
            std::string PortraitTurnInText;
            std::string PortraitTurnInName;
            std::string PortraitGiverText;
            std::string PortraitGiverName;
            std::string QuestTitle;
            std::string LogDescription;
            std::string DescriptionText;
            bool DisplayPopup = false;
            bool StartCheat = false;
            bool AutoLaunched = false;
        };

        struct QuestObjectiveCollect
        {
            QuestObjectiveCollect(int32 objectID = 0, int32 amount = 0) : ObjectID(objectID), Amount(amount) { }
            int32 ObjectID;
            int32 Amount;
        };

        struct QuestCurrency
        {
            QuestCurrency(int32 currencyID = 0, int32 amount = 0) : CurrencyID(currencyID), Amount(amount) { }
            int32 CurrencyID;
            int32 Amount;
        };

        class QuestGiverRequestItems final : public ServerPacket
        {
        public:
            QuestGiverRequestItems() : ServerPacket(SMSG_QUEST_GIVER_REQUEST_ITEMS, 300) { }

            WorldPacket const* Write() override;

            ObjectGuid QuestGiverGUID;
            int32 QuestGiverCreatureID  = 0;
            int32 QuestID               = 0;
            int32 CompEmoteDelay        = 0;
            int32 CompEmoteType         = 0;
            bool AutoLaunched           = false;
            int32 SuggestPartyMembers   = 0;
            int32 MoneyToGet            = 0;
            std::vector<QuestObjectiveCollect> Collect;
            std::vector<QuestCurrency> Currency;
            int32 StatusFlags           = 0;
            uint32 QuestFlags[2]        = {};
            std::string QuestTitle;
            std::string CompletionText;
        };

        class QuestGiverRequestReward final : public ClientPacket
        {
        public:
            QuestGiverRequestReward(WorldPacket&& packet) : ClientPacket(CMSG_QUEST_GIVER_REQUEST_REWARD, std::move(packet)) { }

            void Read() override;

            ObjectGuid QuestGiverGUID;
            int32 QuestID = 0;
        };

        class QuestGiverQueryQuest final : public ClientPacket
        {
        public:
            QuestGiverQueryQuest(WorldPacket&& packet) : ClientPacket(CMSG_QUEST_GIVER_QUERY_QUEST, std::move(packet)) { }

            void Read() override;

            ObjectGuid QuestGiverGUID;
            int32 QuestID = 0;
            bool RespondToGiver = false;
        };

        class QuestGiverAcceptQuest final : public ClientPacket
        {
        public:
            QuestGiverAcceptQuest(WorldPacket&& packet) : ClientPacket(CMSG_QUEST_GIVER_ACCEPT_QUEST, std::move(packet)) { }

            void Read() override;

            ObjectGuid QuestGiverGUID;
            int32 QuestID = 0;
            bool StartCheat = false;
        };

        class QuestLogRemoveQuest final : public ClientPacket
        {
        public:
            QuestLogRemoveQuest(WorldPacket&& packet) : ClientPacket(CMSG_QUEST_LOG_REMOVE_QUEST, std::move(packet)) { }

            void Read() override;

            uint8 Entry = 0;
        };

        struct GossipTextData
        {
            GossipTextData(uint32 questID, uint32 questType, uint32 questLevel, uint32 questFlags, uint32 questFlagsEx, bool repeatable, std::string questTitle) :
                QuestID(questID), QuestType(questType), QuestLevel(questLevel), QuestFlags(questFlags), QuestFlagsEx(questFlagsEx), Repeatable(repeatable), QuestTitle(questTitle) { }
            uint32 QuestID;
            uint32 QuestType;
            uint32 QuestLevel;
            uint32 QuestFlags;
            uint32 QuestFlagsEx;
            bool Repeatable;
            std::string QuestTitle;
        };

        class QuestGiverQuestList final : public ServerPacket
        {
        public:
            QuestGiverQuestList() : ServerPacket(SMSG_QUEST_GIVER_QUEST_LIST_MESSAGE, 100) { }

            WorldPacket const* Write() override;

            ObjectGuid QuestGiverGUID;
            uint32 GreetEmoteDelay      = 0;
            uint32 GreetEmoteType       = 0;
            std::vector<GossipTextData> GossipTexts;
            std::string Greeting;
        };

        class QuestUpdateComplete final : public ServerPacket
        {
        public:
            QuestUpdateComplete() : ServerPacket(SMSG_QUEST_UPDATE_COMPLETE, 4) { }

            WorldPacket const* Write() override;

            int32 QuestID = 0;
        };

        class QuestConfirmAcceptResponse final : public ServerPacket
        {
        public:
            QuestConfirmAcceptResponse() : ServerPacket(SMSG_QUEST_CONFIRM_ACCEPT, 21) { }

            WorldPacket const* Write() override;

            ObjectGuid InitiatedBy;
            int32 QuestID = 0;
            std::string QuestTitle;
        };

        class QuestConfirmAccept final : public ClientPacket
        {
        public:
            QuestConfirmAccept(WorldPacket&& packet) : ClientPacket(CMSG_QUEST_CONFIRM_ACCEPT, std::move(packet)) { }

            void Read() override;

            int32 QuestID = 0;
        };
    }
}

ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::Quest::QuestRewards const& questRewards);
ByteBuffer& operator<<(ByteBuffer& data, WorldPackets::Quest::QuestGiverOfferReward const& offer);

#endif // QuestPackets_h__
