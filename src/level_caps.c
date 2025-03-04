#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "level_caps.h"
#include "pokemon.h"


u32 GetCurrentLevelCap(void)
{
    static const u32 sLevelCapFlagMap[][2] =
    {
        {FLAG_RIVAL1,           6}, //Rival 1 Cap
        {FLAG_RED1,            13}, //Red 1 Cap
        {FLAG_BADGE01_GET,     16}, //Roxanne Cap
        {FLAG_BADGE02_GET,     20}, //Brawly Cap
        {FLAG_MUSEUM,          23}, //Oceanic Museum Cap
        {FLAG_RIVAL2,          26}, //Rival 2 Cap
        {FLAG_BADGE03_GET,     29}, //Wattson Cap
        {FLAG_CTB,             34}, //Cool Trainer Brooke Cap
        {FLAG_RED2,            38}, //Red 2 Cap
        {FLAG_MAXIE1,          43}, //Maxie 1 Cap
        {FLAG_BADGE04_GET,     46}, //Flannery Cap
        {FLAG_BADGE05_GET,     50}, //Norman Cap
        {FLAG_WINSTITUTE,      56}, //Weather Institute Cap
        {FLAG_RIVAL3,          57}, //Rival 3 Cap
        {FLAG_BADGE06_GET,     60}, //Winona Cap
        {FLAG_RIVAL4,          65}, //Rival 4 Cap
        {FLAG_MTPYRE,          68}, //Mt. Pyre Cap
        {FLAG_MAXIE2,          72}, //Maxie 2 Cap
        {FLAG_MATT,            75}, //Matt Cap
        {FLAG_BADGE07_GET,     78}, //Tate & Liza Cap
        {FLAG_SPACETAG,        80}, //Space Tag Cap
        {FLAG_ARCHIE,          84}, //Archie Cap
        {FLAG_BADGE08_GET,     88}, //Wallace Cap
        {FLAG_WALLY,           94}, //Wally Cap
        {FLAG_VITO,            97}, //Winstrate Vito Cap
        {FLAG_E4,              99}, //Elite 4 Cap
        {FLAG_IS_CHAMPION,    100}, //Post-Game Cap
    };

    u32 i;

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp))
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
        }
        else
        {
            return expValue;
        }
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown))
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}
