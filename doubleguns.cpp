#include "doubleguns.h"

namespace dblgnuns
{
    static int wep = 0;
    static int camo = 0;
    static int reticle = 0;
    static int attach1 = 0;
    static int attach2 = 0;
    static int attach3 = 0;
    static int attach4 = 0;
    static int attach5 = 0;
    static int attach6 = 0;
    static int attach7 = 0;
    static int attach8 = 0;
    static int attach9 = 0;
    static int attach10 = 0;
    static int sticker1 = 0;
    static int sticker2 = 0;
    static int sticker3 = 0;
    static int sticker4 = 0;
    static int charm = 0;
    static int lootid = 0;
    static int variantid = 0;


    void doublegunsget(int slot,int game)
    {
        char context[255];
        char context2[255];
        char state[255];
        char state2[255];
        int navStringCount;
        int navStringCount2;
        char* navStrings[16]{};
        char* navStrings2[16]{};
        const char* mode = "";
        const char* mode2 = "";

        if (game == 2)
        {
            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
        }
        else if (game == 0)
        {
            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
        }
        else if (game == 1)
        {
            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
        }
        else if (game == 3)
        {
            mode = xorstr_("ddl/mp/privateloadouts.ddl");
            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
        }

        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
        DDL_GetRootState((__int64)state, ddl_file);
        char buffer[200];


        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.weapon"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            wep = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }

        DDL_GetRootState((__int64)state, ddl_file);
        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.camo"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            camo = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);
        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.reticle"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            reticle = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);
        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.attachmentSetup.0.attachment"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            attach1 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);
        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.attachmentSetup.1.attachment"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            attach2 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);
        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.attachmentSetup.2.attachment"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            attach3 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);
        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.attachmentSetup.3.attachment"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            attach4 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.attachmentSetup.4.attachment"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            attach5 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.attachmentSetup.5.attachment"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            attach6 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.attachmentSetup.6.attachment"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            attach7 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.attachmentSetup.7.attachment"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            attach8 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.attachmentSetup.8.attachment"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            attach9 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.attachmentSetup.9.attachment"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            attach10 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.sticker.0"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            sticker1 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.sticker.1"), slot);
        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
        {
            sticker2 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.sticker.2"), slot);
        ParseShitt(buffer, (const char**)navStrings2, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings2))
        {
            sticker3 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.sticker.3"), slot);
        ParseShitt(buffer, (const char**)navStrings2, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings2))
        {
            sticker4 = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.cosmeticAttachment"), slot);
        ParseShitt(buffer, (const char**)navStrings2, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings2))
        {
            charm = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.lootItemID"), slot);
        ParseShitt(buffer, (const char**)navStrings2, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings2))
        {
            lootid = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
        DDL_GetRootState((__int64)state, ddl_file);

        memset(buffer, 0, 200);
        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.weaponSetups.0.variantID"), slot);
        ParseShitt(buffer, (const char**)navStrings2, 16, &navStringCount);
        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings2))
        {
            variantid = DDL_GetInt((__int64*)&state, (__int64*)&context);

        }
    }

    void dblgunsset(int slot,int game)
    {
        char context2[255];
        char state2[255];
        int navStringCount2;
        char* navStrings2[16]{};
        const char* mode2 = "";

        if (game == 2)
        {
            mode2 = xorstr_("ddl/mp/rankedloadouts.ddl");
            CL_PlayerData_GetDDLBufferr((__int64)context2, 0, 0, 3);
        }
        else if (game == 0)
        {
            mode2 = xorstr_("ddl/mp/wzrankedloadouts.ddl");
            CL_PlayerData_GetDDLBufferr((__int64)context2, 0, 0, 5);
        }
        else if (game == 1)
        {
            mode2 = xorstr_("ddl/mp/wzprivateloadouts.ddl");
            CL_PlayerData_GetDDLBufferr((__int64)context2, 0, 0, 6);
        }
        else if (game == 3)
        {
            mode2 = xorstr_("ddl/mp/privateloadouts.ddl");
            CL_PlayerData_GetDDLBufferr((__int64)context2, 0, 0, 4);
        }

        __int64 ddl_file2 = Com_DDL_LoadAssett((__int64)mode2);
        DDL_GetRootState((__int64)state2, ddl_file2);
        char buffer2[200];
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.weapon"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, wep);
        }

        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.camo"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, camo);

        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.reticle"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, reticle);

        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.attachmentSetup.0.attachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, attach1);

        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.attachmentSetup.1.attachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, attach2);

        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.attachmentSetup.2.attachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, attach3);

        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.attachmentSetup.3.attachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, 0);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.attachmentSetup.4.attachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, attach5);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.attachmentSetup.5.attachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, attach6);

        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.attachmentSetup.6.attachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, attach7);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.attachmentSetup.7.attachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, attach8);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.attachmentSetup.8.attachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, attach9);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.attachmentSetup.9.attachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, attach10);

        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.sticker.0"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, sticker1);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.sticker.1"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, sticker2);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.sticker.2"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, sticker3);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.sticker.3"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, sticker4);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.cosmeticAttachment"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, charm);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.lootItemID"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, lootid);
        }
        DDL_GetRootState((__int64)state2, ddl_file2);
        memset(buffer2, 0, 200);
        sprintf_s(buffer2, xorstr_("squadMembers.loadouts.%i.weaponSetups.1.variantID"), slot);
        ParseShitt(buffer2, (const char**)navStrings2, 16, &navStringCount2);
        if (DDL_MoveToPathh((__int64*)&state2, (__int64*)&state2, navStringCount2, (const char**)navStrings2))
        {
            DDL_SetInt2((__int64*)&state2, (__int64*)&context2, variantid);
        }
    }
}