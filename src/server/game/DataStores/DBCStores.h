/*
 * Copyright (C) 2008-2015 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef TRINITY_DBCSTORES_H
#define TRINITY_DBCSTORES_H

#include "DBCStore.h"
#include "DBCStructure.h"
#include "DB2Structure.h"
#include "SharedDefines.h"

typedef std::list<uint32> SimpleFactionsList;
SimpleFactionsList const* GetFactionTeamList(uint32 faction);

char const* GetPetName(uint32 petfamily, uint32 dbclang);

int32 GetAreaFlagByAreaID(uint32 area_id);                  // -1 if not found
AreaTableEntry const* GetAreaEntryByAreaID(uint32 area_id);
AreaTableEntry const* GetAreaEntryByAreaFlagAndMap(uint32 area_flag, uint32 map_id);
uint32 GetAreaFlagByMapId(uint32 mapid);

char const* GetRaceName(uint8 race, uint8 locale);
char const* GetClassName(uint8 class_, uint8 locale);

WMOAreaTableEntry const* GetWMOAreaTableEntryByTripple(int32 rootid, int32 adtid, int32 groupid);

uint32 GetVirtualMapForMapAndZone(uint32 mapid, uint32 zoneId);

enum ContentLevels
{
    CONTENT_1_60    = 0,
    CONTENT_61_70   = 1,
    CONTENT_71_80   = 2,
    CONTENT_81_85   = 3,
    CONTENT_86_90   = 4,
    CONTENT_91_100  = 5,
    MAX_CONTENT
};

uint32 GetMaxLevelForExpansion(uint32 expansion);
uint32 GetExpansionForLevel(uint32 level);

ContentLevels GetContentLevelsForMapAndZone(uint32 mapid, uint32 zoneId);

bool IsTotemCategoryCompatibleWith(uint32 itemTotemCategoryId, uint32 requiredTotemCategoryId);

void Zone2MapCoordinates(float &x, float &y, uint32 zone);
void Map2ZoneCoordinates(float &x, float &y, uint32 zone);

typedef std::unordered_map<uint32, std::unordered_map<uint32, MapDifficultyEntry const*>> MapDifficultyMap;
MapDifficultyEntry const* GetDefaultMapDifficulty(uint32 mapId, Difficulty* difficulty = nullptr);
MapDifficultyEntry const* GetMapDifficultyData(uint32 mapId, Difficulty difficulty);
MapDifficultyEntry const* GetDownscaledMapDifficultyData(uint32 mapId, Difficulty &difficulty);

uint32 GetLiquidFlags(uint32 liquidType);

PvPDifficultyEntry const* GetBattlegroundBracketByLevel(uint32 mapid, uint32 level);
PvPDifficultyEntry const* GetBattlegroundBracketById(uint32 mapid, BattlegroundBracketId id);

CharSectionsEntry const* GetCharSectionEntry(uint8 race, CharSectionType genType, uint8 gender, uint8 type, uint8 color);

LFGDungeonEntry const* GetLFGDungeon(uint32 mapId, Difficulty difficulty);

uint32 GetDefaultMapLight(uint32 mapId);

typedef std::unordered_multimap<uint32, SkillRaceClassInfoEntry const*> SkillRaceClassInfoMap;
typedef std::pair<SkillRaceClassInfoMap::iterator, SkillRaceClassInfoMap::iterator> SkillRaceClassInfoBounds;
SkillRaceClassInfoEntry const* GetSkillRaceClassInfo(uint32 skill, uint8 race, uint8 class_);

typedef ChrSpecializationEntry const* ChrSpecializationByIndexArray[MAX_CLASSES][MAX_SPECIALIZATIONS];
typedef std::vector<TalentEntry const*> TalentsByPosition[MAX_CLASSES][MAX_TALENT_TIERS][MAX_TALENT_COLUMNS];
extern TalentsByPosition sTalentByPos;

template<class T>
class GameTable
{
public:
    GameTable(char const* format) : _storage(format), _gtEntry(nullptr) { }

    void SetGameTableEntry(GameTablesEntry const* gtEntry) { _gtEntry = gtEntry; }

    T const* EvaluateTable(uint32 row, uint32 column) const
    {
        ASSERT(row < _gtEntry->NumRows);
        ASSERT(column < _gtEntry->NumColumns);

        return _storage.LookupEntry(_gtEntry->NumRows * column + row);
    }

    char const* GetFormat() const { return _storage.GetFormat(); }
    uint32 GetFieldCount() const { return _storage.GetFieldCount(); }
    bool Load(char const* fileName) { return _storage.Load(fileName, nullptr); }

    uint32 GetTableRowCount() const { return _gtEntry->NumRows; }
    uint32 GetTableColumnCount() const { return _gtEntry->NumColumns; }

private:
    DBCStorage<T> _storage;
    GameTablesEntry const* _gtEntry;
};

extern DBCStorage <AchievementEntry>             sAchievementStore;
extern DBCStorage <AnimKitEntry>                 sAnimKitStore;
extern DBCStorage <AreaTableEntry>               sAreaStore;// recommend access using functions
extern DBCStorage <AreaTriggerEntry>             sAreaTriggerStore;
extern DBCStorage <ArmorLocationEntry>           sArmorLocationStore;
extern DBCStorage <BankBagSlotPricesEntry>       sBankBagSlotPricesStore;
extern DBCStorage <BannedAddOnsEntry>            sBannedAddOnsStore;
extern DBCStorage <BattlemasterListEntry>        sBattlemasterListStore;
extern DBCStorage <ChatChannelsEntry>            sChatChannelsStore;
extern DBCStorage <CharSectionsEntry>            sCharSectionsStore;
extern DBCStorage <CharTitlesEntry>              sCharTitlesStore;
extern DBCStorage <ChrClassesEntry>              sChrClassesStore;
extern DBCStorage <ChrRacesEntry>                sChrRacesStore;
extern DBCStorage <ChrSpecializationEntry>       sChrSpecializationStore;
extern ChrSpecializationByIndexArray             sChrSpecializationByIndexStore;
extern DBCStorage <CreatureDisplayInfoExtraEntry> sCreatureDisplayInfoExtraStore;
extern DBCStorage <CreatureFamilyEntry>          sCreatureFamilyStore;
extern DBCStorage <CreatureModelDataEntry>       sCreatureModelDataStore;
extern DBCStorage <CriteriaEntry>                sCriteriaStore;
extern DBCStorage <CriteriaTreeEntry>            sCriteriaTreeStore;
extern DBCStorage <DifficultyEntry>              sDifficultyStore;
extern DBCStorage <DungeonEncounterEntry>        sDungeonEncounterStore;
extern DBCStorage <DurabilityCostsEntry>         sDurabilityCostsStore;
extern DBCStorage <EmotesEntry>                  sEmotesStore;
extern DBCStorage <EmotesTextEntry>              sEmotesTextStore;
extern DBCStorage <FactionEntry>                 sFactionStore;
extern DBCStorage <FactionTemplateEntry>         sFactionTemplateStore;
extern DBCStorage <GameObjectDisplayInfoEntry>   sGameObjectDisplayInfoStore;
extern DBCStorage <GemPropertiesEntry>           sGemPropertiesStore;
extern DBCStorage <GlyphPropertiesEntry>         sGlyphPropertiesStore;

extern GameTable <GtBarberShopCostBaseEntry>    sGtBarberShopCostBaseStore;
extern GameTable <GtCombatRatingsEntry>         sGtCombatRatingsStore;
extern GameTable <GtChanceToMeleeCritBaseEntry> sGtChanceToMeleeCritBaseStore;
extern GameTable <GtChanceToMeleeCritEntry>     sGtChanceToMeleeCritStore;
extern GameTable <GtChanceToSpellCritBaseEntry> sGtChanceToSpellCritBaseStore;
extern GameTable <GtChanceToSpellCritEntry>     sGtChanceToSpellCritStore;
extern GameTable <GtItemSocketCostPerLevelEntry> sGtItemSocketCostPerLevelStore;
extern GameTable <GtNPCManaCostScalerEntry>     sGtNPCManaCostScalerStore;
extern GameTable <GtNpcTotalHpEntry>            sGtNpcTotalHpStore;
extern GameTable <GtNpcTotalHpExp1Entry>        sGtNpcTotalHpExp1Store;
extern GameTable <GtNpcTotalHpExp2Entry>        sGtNpcTotalHpExp2Store;
extern GameTable <GtNpcTotalHpExp3Entry>        sGtNpcTotalHpExp3Store;
extern GameTable <GtNpcTotalHpExp4Entry>        sGtNpcTotalHpExp4Store;
extern GameTable <GtNpcTotalHpExp5Entry>        sGtNpcTotalHpExp5Store;
extern GameTable <GtOCTLevelExperienceEntry>    sGtOCTLevelExperienceStore;
extern GameTable <gtOCTHpPerStaminaEntry>       sGtOCTHpPerStaminaStore;
extern GameTable <GtRegenMPPerSptEntry>         sGtRegenMPPerSptStore;
extern GameTable <GtSpellScalingEntry>          sGtSpellScalingStore;
extern GameTable <GtOCTBaseHPByClassEntry>      sGtOCTBaseHPByClassStore;
extern GameTable <GtOCTBaseMPByClassEntry>      sGtOCTBaseMPByClassStore;
extern DBCStorage <GuildColorBackgroundEntry>    sGuildColorBackgroundStore;
extern DBCStorage <GuildColorBorderEntry>        sGuildColorBorderStore;
extern DBCStorage <GuildColorEmblemEntry>        sGuildColorEmblemStore;
extern DBCStorage <ItemArmorQualityEntry>        sItemArmorQualityStore;
extern DBCStorage <ItemArmorShieldEntry>         sItemArmorShieldStore;
extern DBCStorage <ItemArmorTotalEntry>          sItemArmorTotalStore;
extern DBCStorage <ItemBagFamilyEntry>           sItemBagFamilyStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageAmmoStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageOneHandStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageOneHandCasterStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageRangedStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageThrownStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageTwoHandStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageTwoHandCasterStore;
extern DBCStorage <ItemDamageEntry>              sItemDamageWandStore;
extern DBCStorage <ItemSetEntry>                 sItemSetStore;
extern DBCStorage <ItemSetSpellEntry>            sItemSetSpellStore;
extern ItemSetSpellsStore                        sItemSetSpellsStore;
extern DBCStorage <LFGDungeonEntry>              sLFGDungeonStore;
extern DBCStorage <LiquidTypeEntry>              sLiquidTypeStore;
extern DBCStorage <LockEntry>                    sLockStore;
extern DBCStorage <MapEntry>                     sMapStore;
extern DBCStorage <MinorTalentEntry>             sMinorTalentStore;
extern DBCStorage <ModifierTreeEntry>            sModifierTreeStore;
extern DBCStorage <PhaseEntry>                   sPhaseStore;
extern MapDifficultyMap                          sMapDifficultyMap;
extern DBCStorage <MovieEntry>                   sMovieStore;
extern DBCStorage <PowerDisplayEntry>            sPowerDisplayStore;
extern DBCStorage <QuestFactionRewEntry>         sQuestFactionRewardStore;
extern DBCStorage <RandomPropertiesPointsEntry>  sRandomPropertiesPointsStore;
extern DBCStorage <SkillLineEntry>               sSkillLineStore;
extern DBCStorage <SkillLineAbilityEntry>        sSkillLineAbilityStore;
extern DBCStorage <SkillRaceClassInfoEntry>      sSkillRaceClassInfoStore;
extern SpellEffectScallingByEffectId             sSpellEffectScallingByEffectId;
extern DBCStorage <SpellCategoryEntry>           sSpellCategoryStore;
extern DBCStorage <SpellFocusObjectEntry>        sSpellFocusObjectStore;
extern DBCStorage <SpellItemEnchantmentEntry>    sSpellItemEnchantmentStore;
extern SpellCategoryStore                        sSpellsByCategoryStore;
extern PetFamilySpellsStore                      sPetFamilySpellsStore;
extern DBCStorage <SpellShapeshiftEntry>         sSpellShapeshiftStore;
extern DBCStorage <SpellShapeshiftFormEntry>     sSpellShapeshiftFormStore;
extern DBCStorage <SpellEntry>                   sSpellStore;
extern DBCStorage <SpellEffectScalingEntry>      sSpellEffectScalingStore;
extern DBCStorage <SpellAuraOptionsEntry>        sSpellAuraOptionsStore;
extern DBCStorage <SpellCategoriesEntry>         sSpellCategoriesStore;
extern DBCStorage <SpellCooldownsEntry>          sSpellCooldownsStore;
extern DBCStorage <SpellEffectEntry>             sSpellEffectStore;
extern DBCStorage <SpellEquippedItemsEntry>      sSpellEquippedItemsStore;
extern DBCStorage <SpellInterruptsEntry>         sSpellInterruptsStore;
extern DBCStorage <SpellLevelsEntry>             sSpellLevelsStore;
extern DBCStorage <SpellScalingEntry>            sSpellScalingStore;
extern DBCStorage <SpellTargetRestrictionsEntry> sSpellTargetRestrictionsStore;
//extern DBCStorage <StableSlotPricesEntry>        sStableSlotPricesStore;
extern DBCStorage <SummonPropertiesEntry>        sSummonPropertiesStore;
extern DBCStorage <TalentEntry>                  sTalentStore;
extern DBCStorage <VehicleEntry>                 sVehicleStore;
extern DBCStorage <VehicleSeatEntry>             sVehicleSeatStore;
extern DBCStorage <WMOAreaTableEntry>            sWMOAreaTableStore;
//extern DBCStorage <WorldMapAreaEntry>           sWorldMapAreaStore; -- use Zone2MapCoordinates and Map2ZoneCoordinates
extern DBCStorage <WorldSafeLocsEntry>           sWorldSafeLocsStore;

void LoadDBCStores(const std::string& dataPath);
void LoadGameTables(const std::string& dataPath);

#endif
