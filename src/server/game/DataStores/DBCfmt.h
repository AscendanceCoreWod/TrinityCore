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

#ifndef TRINITY_DBCSFRM_H
#define TRINITY_DBCSFRM_H

// x - skip<uint32>, X - skip<uint8>, s - char*, f - float, i - uint32, b - uint8, d - index (not included)
// n - index (included), l - uint64, p - field present in sql dbc, a - field absent in sql dbc

char const Achievementfmt[] = "niixsxiixixxiii";
const std::string CustomAchievementfmt = "pppaaaapapaapp";
const std::string CustomAchievementIndex = "ID";
char const AnimKitfmt[] = "nxxx";
char const AreaTableEntryfmt[] = "iiiniixxxxxxisiiiiixxxxxxxxxx";
char const AreaTriggerEntryfmt[] = "nifffxxxfffffxxxx";
char const ArmorLocationfmt[] = "nfffff";
char const BankBagSlotPricesEntryfmt[] = "ni";
char const BannedAddOnsfmt[] = "nxxxxxxxxxx";
char const BattlemasterListEntryfmt[] = "niiiiiiiiiiiiiiiiixsiiiixxxxxxx";
char const CharSectionsEntryfmt[] = "diiixxxiii";
char const CharTitlesEntryfmt[] = "nxssix";
char const ChatChannelsEntryfmt[] = "nixsx";
char const ChrClassesEntryfmt[] = "nixsxxxixiiiiixxxxx";
char const ChrRacesEntryfmt[] = "niixiixxxxxxiisxxxxxxxxxxxxxxxxxxxxxxxxx";
char const ChrSpecializationEntryfmt[] = "nxiiiiiiiiixxxii";
char const CreatureDisplayInfoExtrafmt[] = "dixxxxxxxxxxxxxxxxxxxx";
char const CreatureFamilyfmt[] = "nfifiiiiixsx";
char const CreatureModelDatafmt[] = "nixxxxxxxxxxxxxffxxxxxxxxxxxxxxxxx";
char const Criteriafmt[] = "niiiiiiiixii";
char const CriteriaTreefmt[] = "niliixxx";
char const DifficultyFmt[] = "niiiixiixxxxix";
char const DungeonEncounterfmt[] = "niiixsxxx";
char const DurabilityCostsfmt[] = "niiiiiiiiiiiiiiiiiiiiiiiiiiiii";
char const EmotesEntryfmt[] = "nxxiiixx";
char const EmotesTextEntryfmt[] = "nxixxxxxxxxxxxxxxxx";
char const FactionEntryfmt[] = "niiiiiiiiiiiiiiiiiiffixsxixx";
char const FactionTemplateEntryfmt[] = "niiiiiiiiiiiii";
char const GameObjectDisplayInfofmt[] = "nixxxxxxxxxxffffffxxx";
char const GemPropertiesEntryfmt[] = "nixxii";
char const GlyphPropertiesfmt[] = "niiix";
char const GtBarberShopCostBasefmt[] = "xf";
char const GtCombatRatingsfmt[] = "xf";
char const GtOCTHpPerStaminafmt[] = "df";
char const GtOCTLevelExperiencefmt[] = "xf";
char const GtChanceToMeleeCritBasefmt[] = "xf";
char const GtChanceToMeleeCritfmt[] = "xf";
char const GtChanceToSpellCritBasefmt[] = "xf";
char const GtChanceToSpellCritfmt[] = "xf";
char const GtItemSocketCostPerLevelfmt[] = "xf";
char const GtNPCManaCostScalerfmt[] = "xf";
char const GtNpcTotalHpfmt[] = "xf";
char const GtNpcTotalHpExp1fmt[] = "xf";
char const GtNpcTotalHpExp2fmt[] = "xf";
char const GtNpcTotalHpExp3fmt[] = "xf";
char const GtNpcTotalHpExp4fmt[] = "xf";
char const GtNpcTotalHpExp5fmt[] = "xf";
char const GtOCTRegenHPfmt[] = "f";
//char const GtOCTRegenMPfmt[] = "f";
char const GtRegenMPPerSptfmt[] = "xf";
char const GtSpellScalingfmt[] = "df";
char const GtOCTBaseHPByClassfmt[] = "df";
char const GtOCTBaseMPByClassfmt[] = "df";
char const GuildColorBackgroundfmt[] = "nXXX";
char const GuildColorBorderfmt[] = "nXXX";
char const GuildColorEmblemfmt[] = "nXXX";
char const ItemBagFamilyfmt[] = "nx";
char const ItemArmorQualityfmt[] = "nfffffffi";
char const ItemArmorShieldfmt[] = "nifffffff";
char const ItemArmorTotalfmt[] = "niffff";
char const ItemDamagefmt[] = "nfffffffi";
char const ItemSetEntryfmt[] = "nsiiiiiiiiiiiiiiiiiii";
char const ItemSetSpellEntryfmt[] = "niiii";
char const LFGDungeonEntryfmt[] = "nsiiixxiiiixxixixxxxxxxxxxxxxx";
char const LightEntryfmt[] = "nifffxxxxxxxxxx";
char const LiquidTypefmt[] = "nxxixixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
char const LockEntryfmt[] = "niiiiiiiiiiiiiiiiiiiiiiiixxxxxxxx";
char const MapEntryfmt[] = "nxiixxsixxixiffxiiiiix";
char const MapDifficultyEntryfmt[] = "diisiiii";
char const MinorTalentEntryfmt[] = "niii";
char const MovieEntryfmt[] = "nxxxx";
char const ModifierTreefmt[] = "niiiiii";
char const NumTalentsAtLevelfmt[] = "df";
char const PhaseEntryfmt[] = "ni";
char const QuestFactionRewardfmt[] = "niiiiiiiiii";
char const PowerDisplayfmt[] = "nixXXX";
char const PvPDifficultyfmt[] = "diiii";
char const RandomPropertiesPointsfmt[] = "niiiiiiiiiiiiiii";
char const SkillLinefmt[] = "nisxixixx";
char const SkillLineAbilityfmt[] = "niiiiiiiiiiii";
char const SkillRaceClassInfofmt[] = "diiiiiii";
char const SpellCategoriesEntryfmt[] = "diiiiiiiii";
char const SpellCategoryfmt[] = "nixxii";
char const SpellEffectEntryfmt[] =            "iiifiiiffiiiiiifiifiiiiifiiiiif";
const std::string CustomSpellEffectEntryfmt = "ppppppppppppppappppppppppp";
const std::string CustomSpellEffectEntryIndex = "Id";
char const SpellEntryfmt[] = "nsxxxiiiiiiiiiiiiiiiiiii";
const std::string CustomSpellEntryfmt = "ppppppppppppppapaaaaaaaaapaaaaaapapppaapppaaapa";
const std::string CustomSpellEntryIndex = "Id";
char const SpellEffectScalingfmt[] = "nfffi";
char const SpellFocusObjectfmt[] = "nx";
char const SpellItemEnchantmentfmt[] = "niiiiiiiiiixiiiiiiiiiiifff";
char const SpellScalingEntryfmt[] = "niiiifiii";
char const SpellTargetRestrictionsEntryfmt[] = "niiffiiii";
char const SpellInterruptsEntryfmt[] = "diiiiiii";
char const SpellEquippedItemsEntryfmt[] = "diiiii";
char const SpellAuraOptionsEntryfmt[] = "niiiiiiii";
char const SpellCooldownsEntryfmt[] = "diiiii";
char const SpellLevelsEntryfmt[] = "diiiii";
char const SpellShapeshiftEntryfmt[] = "niiiix";
char const SpellShapeshiftFormfmt[] = "nxxiixiiiiiiiiiiiiixx";
char const StableSlotPricesfmt[] = "ni";
char const SummonPropertiesfmt[] = "niiiii";
char const TalentEntryfmt[] = "niiiiiiiiix";
char const VehicleEntryfmt[] = "niiffffiiiiiiiifffffffffffffffxxxxfifiiii";
char const VehicleSeatEntryfmt[] = "niiffffffffffiiiiiifffffffiiifffiiiiiiiffiiiiffffffffffffiiiiiiiii";
char const WMOAreaTableEntryfmt[] = "niiixxxxxiixxxx";
char const WorldMapAreaEntryfmt[] = "xinxffffixxxxx";
char const WorldSafeLocsEntryfmt[] = "niffffx";

#endif
