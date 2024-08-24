#include "dllmain.h"
#include <sys/stat.h>
#include "xor.h"
#include <atlstr.h>
#include "skcrypt.hpp"
#include <future>
#include <string>
#include <shlobj.h>
//#include "sdk.h"
HANDLE hMainThread = NULL;
uint64_t BASEIMAGE = reinterpret_cast<uint64_t>(GetModuleHandleA(NULL));

float crosshair_col[3] = { 255.f / 255.f, 255.f , 255.f };
float screenX = GetSystemMetrics(SM_CXSCREEN);
int screenY = GetSystemMetrics(SM_CYSCREEN);

ImColor crosshaircolor = ImColor(0.f, 0.f, 255.f, 255.f);

bool is_key_down(int vk_key)
{
	return ((GetAsyncKeyState(vk_key) & 0x8000) ? 1 : 0);
}

void draw_line(const ImVec2& from, const ImVec2& to, C_Color color, float thickness)
{
	ImGui::GetBackgroundDrawList()->AddLine(from, to, color.GetU32(), thickness);
}

void Log_(const char* fmt, ...) {
	char		text[4096];
	va_list		ap;
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	std::ofstream logfile(xorstr_("C:\\logs\\put.logs"), std::ios::app);
	if (logfile.is_open() && text)	logfile << text << std::endl;
	logfile.close();
}

bool IsPathExist(const std::string& s)
{
	struct stat buffer;
	return (stat(s.c_str(), &buffer) == 0);
}

void getOffsets()
{
	if (var->procID)
	{
		bool debug = false;

		var->Offest.unlock_offsets                            = utility::PatternScanEx(var->hProc, var->baseModule + 0x6000000, 0x1F00000, xorstr_("\x48\x8D\x05\x00\x00\x00\x00\x44\x8B\xCB\x44\x8B\xC7\x48\x89\x44\x24"), xorstr_("xxx????xxxxxxxxxx")) - var->baseModule;
		var->Offest.ddl_getdllbuffer                          = utility::PatternScanEx(var->hProc, var->baseModule + 0x3000000, 0x2F00000, xorstr_("\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x48\x8B\xE9\x49\x63\xF8\x41\x8B\xC9\x48\x63\xF2\x41\x8B\xD9\xE8\x00\x00\x00\x00"), xorstr_("xxxx?xxxx?xxxx?xxxxxxxxxxxxxxxxxxxxx????")) - var->baseModule;
		var->Offest.ddl_movetoname                            = utility::FindOffset(var->hProc, var->baseModule + 0x4000000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x84\xC0\x74\x22\x48\x8D\x54\x24\x40"), xorstr_("x????xxxxxxxxx"), 1, 5, 0);
		var->Offest.ddl_movetopath                            = utility::PatternScanEx(var->hProc, var->baseModule + 0x6500000, 0xF00000, "\x48\x89\x74\x24\x00\x48\x89\x7C\x24\x00\x41\x56\x48\x83\xEC\x20\x4D\x8B\xF1\x48\x8B\xFA\x48\x85\xC9", "xxxx?xxxx?xxxxxxxxxxxxxxx") - var->baseModule;
		var->Offest.ddl_getint                                = utility::PatternScanExCustom(var->hProc, var->baseModule + 0x6500000, 0xF00000, "\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xFA\x48\x8B\xD9\x48\x85\xD2\x74\x7F\x48\x8B\x42\x10\x48\x85\xC0\x74\x76", "xxxx?xxxxxxxxxxxxxxxxxxxxxxxxx", 2) - var->baseModule;
		var->Offest.a_parse                                   = utility::PatternScanEx(var->hProc, var->baseModule + 0x02D00000, 0xF00000, "\x40\x55\x56\x41\x54\x41\x56\x41\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x44\x24\x00\x45\x33\xF6\x4D\x8B\xF9\x45\x89\x31", "xxxxxxxxxxxx????xxx????xxxxxxx?xxxxxxxxx") - var->baseModule;
		var->Offest.clantag_offset                            = utility::PatternScanEx(var->hProc, var->baseModule + 0x3C00000, 0xF00000, "\x40\x53\x48\x83\xEC\x30\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x44\x24\x00\x4C\x8B\xCA\x41\xB8\x00\x00\x00\x00\x8B\x15\x00\x00\x00\x00\x8B\xD9", "xxxxxxxxx????xxxxxxx?xxxxx????xx????xx") - var->baseModule;
		var->Offest.ddl_setint                                = utility::FindOffset(var->hProc, var->baseModule + 0x3000000, 0x3F00000, xorstr_("\x44\x8B\xC0\x48\x8D\x55\xB7\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00"), xorstr_("xxxxxxxxxxx?x????"), 1, 5, 12);
		var->Offest.ddl_setstring                             = utility::PatternScanEx(var->hProc, var->baseModule + 0x6400000, 0x1F00000, "\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x30\x49\x8B\xF0\x48\x8B\xFA\x48\x8B\xD9\x48\x85\xD2\x0F\x84\x00\x00\x00\x00\x48\x8B\x42\x10\x48\x85\xC0\x0F\x84\x00\x00\x00\x00", "xxxx?xxxx?xxxxxxxxxxxxxxxxxxx????xxxxxxxxx????") - var->baseModule;
		var->Offest.ddl_loadasset                             = utility::FindOffset(var->hProc, var->baseModule + 0x3000000, 0x2F00000, xorstr_("\xe8\x00\x00\x00\x00\x48\x8b\x00\x4c\x8d\x4c\x24\x00\x33\xc0\x48\x8d\x0d\x00\x00\x00\x00"), xorstr_("x????xx?xxxx?xxxxx????"), 1, 5, 0);
		var->Offest.ddl_getrootstate                          = utility::FindOffset(var->hProc, var->baseModule + 0x2000000, 0x2F00000, xorstr_("\xe8\x00\x00\x00\x00\x8b\x0d\x00\x00\x00\x00\x0f\x10\x00"), xorstr_("x????xx????xx?"), 1, 5, 0);
		var->Offest.Com_DDL_CreateContext                     = utility::FindOffset(var->hProc, var->baseModule + 0x2700000, 0x1F00000, xorstr_("\x48\x89\x5C\x24\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x57\x41\x56\x41\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\xDA\x48\x8B\xF9\x33\xD2\xE8\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x80\x3D\x00\x00\x00\x00\x00"), "xxxx?xxxx?xxxx?xxxxxxxx????xxxxxxxxx????xxx????xxx????xx?????", 1, 5, 0x158);
		var->Offest.DDL_GetType                               = utility::PatternScanEx(var->hProc, var->baseModule + 0x6500000, 0xF00000, "\x48\x85\xC9\x74\x0D\x48\x8B\x41\x10\x48\x85\xC0\x74\x04\x8B\x40\x14\xC3\xB8\x00\x00\x00\x00\xC3", "xxxxxxxxxxxxxxxxxxx????x") - var->baseModule;
		var->Offest.NavigateBlueprintDDL                      = utility::FindOffset(var->hProc, var->baseModule + 0x2400000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x84\xC0\x0F\x84\x00\x00\x00\x00\x48\x8D\x4C\x24\x00\xE8\x00\x00\x00\x00\x83\xF8\x04\x74\x7E"), "x????xxxx????xxxx?x????xxxxx", 1, 5, 0);
		var->Offest.DDL_SetEnum                               = utility::PatternScanEx(var->hProc, var->baseModule + 0x6400000, 0x1F00000, "\x48\x89\x5C\x24\x0000\x57\x48\x83\xEC\x20\x48\x8B\xFA\x48\x8B\xD9\x33\xD2\x49\x8B\xC8\xE8", "xxxx?xxxxxxxxxxxxxxxxx") - var->baseModule;
		var->Offest.sendPlayerEvent                           = utility::PatternScanEx(var->hProc, var->baseModule + 0x1700000, 0x1F00000, "\x40\x55\x56\x57\x41\x56\x48\x83\xEC\x78\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x44\x24\x00\x0F\x57\xC0\x48\x8D\x3D\x00\x00\x00\x00", "xxxxxxxxxxxxx????xxxxxxx?xxxxxx????") - var->baseModule;
		var->Offest.OnlineChatManger_GetInstance              = utility::FindOffset(var->hProc, var->baseModule + 0x3400000, 0x1F00000, "\xE8\x00\x00\x00\x00\x8B\xD3\x48\x8B\xCE\x48\x8B\xF8\xE8\x00\x00\x00\x00\x48\x8D\x4C\x24\x00\x48\x8B\xD8\xE8\x00\x00\x00\x00", "x????xxxxxxxxx????xxxx?xxxx????", 1, 5, 0);
		var->Offest.ShowToastNotificationAfterUserJoinedParty = utility::PatternScanEx(var->hProc, var->baseModule + 0x2000000, 0x2000000, "\xCC\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x20\x4C\x8B\x05\x00\x00\x00\x00\x33", "xxxxx?xxxxxxxx????x") - var->baseModule;
		var->Offest.StringTable_GetAsset                      = utility::FindOffset(var->hProc, var->baseModule + 0x2000000, 0x3000000, xorstr_("\xE8\x00\x00\x00\x00\x48\x8B\x4C\x24\x00\xE8\x00\x00\x00\x00\x33\xFF"), xorstr_("x????xxxx?x????xx"), 1, 5, 0);
		var->Offest.uploadbps                                 = utility::FindOffset(var->hProc, var->baseModule + 0x2200000, 0x2F00000, xorstr_("\x48\x8D\x05\x00\x00\x00\x00\xC6\x04\x01\x01\x48\x8B\xCB\xE8\x00\x00\x00\x00\x85\xC0\x79\x0F\x48\x8D\x15\x00\x00\x00\x00"), xorstr_("xxx????xxxxxxxx????xxxxxxx????"), 3, 7, 0);
		var->Offest.notsure                                   = utility::FindOffset(var->hProc, var->baseModule + 0x2200000, 0x2F00000, xorstr_("\x4C\x8D\x35\x00\x00\x00\x00\x48\x8B\xE8\x49\x8D\x8E\x00\x00\x00\x00\x48\x03\xCE\xE8\x00\x00\x00\x00\x84\xC0"), xorstr_("xxx????xxxxxx????xxxx????xx"), 3, 7, 0);
		var->Offest.Dvar_FindVarByName                        = utility::FindOffset(var->hProc, var->baseModule + 0x5A00000, 0x2000000, xorstr_("\xE8\x00\x00\x00\x00\x48\x8B\xD8\x48\x85\xC0\x75\x04\x33"), xorstr_("x????xxxxxxxxx"), 0, 4, 1);
		var->Offest.Dvar_SetBoolInternal                      = utility::FindOffset(var->hProc, var->baseModule + 0x2000000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x80\x3D\x00\x00\x00\x00\x00\x4C\x8D\x35\x00\x00\x00\x00\x74\x43\x33\xD2\xF7\x05\x00\x00\x00\x00\x00\x00\x00\x00\x76\x2E"), xorstr_("x????xx?????xxx????xxxxxx????????xx"), 1, 5, 0);
		var->Offest.Dvar_SetInt_Internal                      = utility::PatternScanEx(var->hProc, var->baseModule + 0x3000000, 0x1F00000, xorstr_("\x40\x53\x48\x81\xEC\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x84\x24\x00\x00\x00\x00\x0F\xB6\x41\x09\x48\x8B\xD9"), xorstr_("xxxxx????xxx????xxxxxxx????xxxxxxx")) - var->baseModule;
		var->Offest.Dvar_SetFloat_Internal                    = utility::FindOffset(var->hProc, var->baseModule + 0x5900000, 0x1F00000, xorstr_("\xE8\x00\x00\x00\x00\x45\x0F\x2E\xC8"), xorstr_("x????xxxx"), 1, 5, 0);
		var->Offest.ShowToastNotificationAfterUserLeftParty   = utility::PatternScanEx(var->hProc, var->baseModule + 0x2000000, 0x2000000, "\x48\x89\x6c\x24\x00\x4c\x89\x44\x24\x00\x56\x57\x41\x56", "xxxx?xxxx?xxxx") - var->baseModule;
		var->Offest.chamOffset                                = utility::PatternScanEx(var->hProc, var->baseModule + 0x5900000, 0x1A00000, xorstr_("\x48\x83\xEC\x58\x83\x3D\x00\x00\x00\x00\x00\xF3\x0F\x10\x84\x24\x00\x00\x00\x00\x74\x34\x33\xC0\x89\x44\x24\x40"), xorstr_("xxxxxx?????xxxxx????xxxxxxxx")) - var->baseModule;
		var->Offest.playerCountOffset                         = utility::FindOffset(var->hProc, var->baseModule + 0x2000000, 0xF00000, xorstr_("\x83\x3d\x00\x00\x00\x00\x00\x41\xbe"), "xx?????xx", 2, 6, 0) + 1;
		var->Offest.inGameOffset                              = var->Offest.playerCountOffset + 0x04;
		var->Offest.gamemode                                  = utility::FindOffset(var->hProc, var->baseModule + 0x2700000, 0x1F00000, xorstr_("\x44\x8b\x00\x00\x00\x00\x00\xc6\x44\x24\x00\x00\xc6\x44\x24\x00\x00"), xorstr_("xx?????xxx??xxx???"), 3, 7, 0);
		var->Offest.wepStructOffset                           = utility::FindOffset(var->hProc, var->baseModule + 0x1800000, 0x2A00000, xorstr_("\x33\xD2\x48\x8D\x0D\x00\x00\x00\x00\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x33\xD2\x48\x8D\x0D\x00\x00\x00\x00\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x33\xD2\x48\x8D\x0D\x00\x00\x00\x00\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\xE8\x00\x00\x00\x00"), xorstr_("xxxxx????xx????x????xxxxx????xx????x????xxxxx????xx????x????x????"), 3, 7, 2);
		var->Offest.initDDLState                              = utility::FindOffset(var->hProc, var->baseModule + 0x3000000, 0x3F00000, xorstr_("\xE8\x00\x00\x00\x00\x48\x63\x05\x00\x00\x00\x00\x4C\x8D\x8C\x24"), xorstr_("x????xxx????xxxx"), 1, 5, 0);
		uintptr_t temp_scan                                   = utility::PatternScanEx(var->hProc, var->baseModule + 0x2000000, 0x2F00000, xorstr_("\x74\x00\xFF\x00\x0F\xB7\x00\x3B\x00\x74\x00\x00\x8D"), xorstr_("x?x?xx?x?x??x")) + 0xA;
		var->Offest.end_bytes                                 = temp_scan + *(char*)temp_scan + 3 - var->baseModule;
		var->Offest.ingame                                    = utility::FindOffset(var->hProc, var->baseModule + 0x2400000, 0x1F00000, xorstr_("\x80\x3D\x00\x00\x00\x00\x00\x75\x5E\xC6\x05"), xorstr_("xx?????xxxx"), 2, 7, 0);
		var->Offest.jmp_rbx = utility::PatternScanEx(var->hProc, var->baseModule + 0x600000, 0x1F00000, xorstr_("\xFF\x23"), xorstr_("xx"));
		//SCAN(var->Offest.logonstatus, var->baseModule + 0x3ED13F3, 0x1AD13F3, "E8 ? ? ? ? 83 F8 02 0F 84 ? ? ? ? 48 89", getaddr(), false, true);



		SCAN(var->Offest.A_CG_GetViewFovBySpace, 0x5900000, 0x1A00000, ("E8 ?? ?? ?? ?? F3 0F 10 00 48 83 C4 38 C3"), resolve(Scanner::OP_CALL), false, debug);
		SCAN(var->Offest.A_CG_StartShellShock, 0x3000000, 0x2A00000, ("41 81 F9 ?? ?? ?? ?? 48 89 91 ?? ?? ?? ?? B8"), getaddr(), false, debug);

		if (!var->steam)
		{
			/*SCAN(var->Offest.LUI_luaVM, 0x100000, 0x1A00000, ("E8 ?? ?? ?? ?? E8 ?? ?? ?? ?? 4C 8B 05"), add(0xA).resolve(Scanner::OP_MOV), true, debug);
			SCAN(var->Offest.LUI_BeginEvent, 0x100000, 0x1A00000, ("E8 ?? ?? ?? ?? 84 C0 0F 84 ?? ?? ?? ?? 4C 8B 05 ?? ?? ?? ?? 48 8D 0D"), resolve(Scanner::OP_CALL), true, debug);
			SCAN(var->Offest.LUI_BeginTable, 0x100000, 0x1A00000, ("E8 ?? ?? ?? ?? 4C 8B 05 ?? ?? ?? ?? 48 8D 15 ?? ?? ?? ?? 48 8D 0D"), resolve(Scanner::OP_CALL), true, debug);
			SCAN(var->Offest.LUI_SetTableBool, 0x100000, 0x1A00000, ("E8 ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 7C 24 ?? 48 8B 5C 24"), resolve(Scanner::OP_CALL), true, debug);
			SCAN(var->Offest.LUI_SetTableString, 0x100000, 0x1A00000, ("E8 ?? ?? ?? ?? 4C 8B 05 ?? ?? ?? ?? 48 8D 0D ?? ?? ?? ?? 48 8B 54 24 ?? E8 ?? ?? ?? ?? 0F B7 54 24"), resolve(Scanner::OP_CALL), true, debug);
			SCAN(var->Offest.LUI_SetTableInt, 0x100000, 0x1A00000, ("E8 ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? E8"), resolve(Scanner::OP_CALL), true, debug);
			SCAN(var->Offest.LUI_EndTable, 0x100000, 0x1A00000, ("E8 ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 81 C3 ?? ?? ?? ?? 4D"), resolve(Scanner::OP_CALL), true, debug);
			SCAN(var->Offest.LUI_EndEvent, 0x100000, 0x1A00000, ("E8 ?? ?? ?? ?? 48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 8B 7C 24 ?? 48 8B 5C 24"), add(0xC).resolve(Scanner::OP_CALL), true, debug);*/
		}
		

		// cbuf
		uintptr_t GScr_structPtr                              = utility::PatternScanEx(var->hProc, var->baseModule + 0x2A00000, 0x3000000, xorstr_("\x48\x8D\x15\x00\x00\x00\x00\x48\x8D\x4D\x90\xE8\x00\x00\x00\x00\x48\x8D\x4D\x90\xE8"), xorstr_("xxx????xxxxx????xxxxx")) + 3;
		uintptr_t GScr_StructAddr                             = GScr_structPtr + 4 + *reinterpret_cast<int*>(GScr_structPtr);
		var->Offest.CbufOffset                                = *reinterpret_cast<uintptr_t*>(utility::PatternScanEx(var->hProc, GScr_StructAddr, 0xF000000, xorstr_("\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x5F\x00\x00\x00\x00\x00\x00\x00"), xorstr_("xxxxxxxxxxxxxxxxxx")) + 0x12) - var->baseModule;
		var->Offest.xpartyOffset                              = utility::FindOffset(var->hProc, var->baseModule + 0x2A00000, 0x3000000, xorstr_("\x48\x8D\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x01\xBB\x00\x00\x00\x00\xB9\x00\x00\x00\x00\x48"), xorstr_("xx?????x????xx????x????x"), 0, 4, 3);

		//logging
		if (debug)
		{
			LOGS_ADDR(var->Offest.chamOffset);
			LOGS_ADDR(var->Offest.gamemode);
			LOGS_ADDR(var->Offest.inGameOffset);
			LOGS_ADDR(var->Offest.playerCountOffset);
			LOGS_ADDR(var->Offest.clantag_offset);
			LOGS_ADDR(var->Offest.unlock_offsets);
			LOGS_ADDR(var->Offest.ddl_loadasset);
			LOGS_ADDR(var->Offest.ddl_getrootstate);
			LOGS_ADDR(var->Offest.ddl_getdllbuffer);
			LOGS_ADDR(var->Offest.ddl_movetoname);
			LOGS_ADDR(var->Offest.ddl_movetopath);
			LOGS_ADDR(var->Offest.ddl_setint);
			LOGS_ADDR(var->Offest.ddl_getint);
			LOGS_ADDR(var->Offest.ddl_setstring);
			LOGS_ADDR(var->Offest.a_parse);
			LOGS_ADDR(var->Offest.ShowToastNotificationAfterUserJoinedParty);
			LOGS_ADDR(var->Offest.StringTable_GetAsset);
			LOGS_ADDR(var->Offest.OnlineChatManger_GetInstance);
			LOGS_ADDR(var->Offest.sendPlayerEvent);
			LOGS_ADDR(var->Offest.DDL_GetType);
			LOGS_ADDR(var->Offest.NavigateBlueprintDDL);
			LOGS_ADDR(var->Offest.Com_DDL_CreateContext);
			LOGS_ADDR(var->Offest.DDL_SetEnum);
			LOGS_ADDR(var->Offest.uploadbps);
			LOGS_ADDR(var->Offest.notsure);
			LOGS_ADDR(var->Offest.Dvar_FindVarByName);
			LOGS_ADDR(var->Offest.Dvar_SetBoolInternal);
			LOGS_ADDR(var->Offest.Dvar_SetFloat_Internal);
			LOGS_ADDR(var->Offest.Dvar_SetInt_Internal);
			LOGS_ADDR(var->Offest.ShowToastNotificationAfterUserLeftParty);
			LOGS_ADDR(var->Offest.wepStructOffset);
			LOGS_ADDR(var->Offest.end_bytes);
			LOGS_ADDR(var->Offest.ingame);
			LOGS_ADDR(var->Offest.initDDLState);
		}
	}
	else
	{
		MessageBoxW(var->hWind, L"Game process could not be found for injection. Restart your PC.", L"Error!", MB_OK);
	}
}

void loadConfig()
{
	CHAR my_documents[MAX_PATH];
	SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);
	var->Settings.docuPath = (std::string)my_documents + "\\PUT AIO";
	string path = var->Settings.docuPath + "\\config1.json";
	if (!filesystem::exists(path))
	{
		newConfig();
	}
	setVars(1);
}

void init()
{
	var = new global_vars();
	var->procID = utility::GetProcId("ModernWarfare.exe");
	var->hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, var->procID);
	var->baseModule = (QWORD)(iat(GetModuleHandleA).get()("ModernWarfare.exe"));
	var->hWind = process::get_process_window(var->procID);
	GetModuleFileNameEx(var->hProc, NULL, var->filePath, MAX_PATH);
	if (string(var->filePath).contains("steam") || string(var->filePath).contains("Steam"))
	{
		var->steam = true;
	}
	loadConfig();
}

float calculateAlpha(float n, float lower, float upper)
{
	n = (n > 0.0f) * n + !(n > 0.0f) * 0.0f;
	return (n < 1.0f) * n + !(n < 1.0f) * 1.0f;
}

void fade()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImGuiIO& io = ImGui::GetIO();
	static float cAlpha{ 0.0f };
	static float frequency{ 1 / 0.35f };
	
	if (var->Settings.open)
	{
		cAlpha = calculateAlpha(cAlpha + frequency * io.DeltaTime, 0.f, 1.f);
		style.Alpha = cAlpha;

		menu->MENUSHOW();
	}
	else
	{
		if ((style.Alpha >= 0))
		{
			style.Alpha = cAlpha;
			cAlpha = calculateAlpha(cAlpha + -frequency * io.DeltaTime, 0.f, 1.f);

			menu->MENUSHOW();
		}
		else
		{
			style.Alpha = 0;
		}
	}
}

bool discinit = false;

__declspec(dllexport)HRESULT present_hk(IDXGISwapChain3* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!pSwapChain)
		return ori_present(pSwapChain, SyncInterval, Flags);
	if (d3d12::pCommandQueue == nullptr)
	{
		ori_present(pSwapChain, SyncInterval, Flags);
	}

	DXGI_SWAP_CHAIN_DESC sdesc;
	pSwapChain->GetDesc(&sdesc);
	
	if (sdesc.OutputWindow == GetForegroundWindow())
	{
		ImFont* main_font = imgui::start(
			reinterpret_cast<IDXGISwapChain3*>(pSwapChain),
			reinterpret_cast<ID3D12CommandQueue*>((d3d12::pCommandQueue)), nullptr, 16.0f);

		imgui::imgui_frame_header();

		if (GetAsyncKeyState(var->Settings.cfg.i_ejectkey) & 1)
		{
			var->Settings.open = false;
			ImGui::GetIO().WantCaptureMouse = false;
			kiero::shutdown();
		}


		if (!discinit)
		{
			if ((GetAsyncKeyState(var->Settings.cfg.i_menukey) & 1) || (GetAsyncKeyState(var->Settings.cfg.i_menu2key) & 1))
				var->Settings.open = !var->Settings.open;
		}

		fade();

		if (var->Settings.chrosshair)
		{
			constexpr long crosshair_size = 10.0f;
			ImVec2 origin;
			origin.x = screenX / static_cast<float>(2);
			origin.y = screenY / static_cast<float>(2);
			draw_line(ImVec2((origin.x), (origin.y) - crosshair_size), ImVec2((origin.x), (origin.y) + crosshair_size), var->Settings.crosshair_color.color(), 1.5f);
			draw_line(ImVec2((origin.x) - crosshair_size, (origin.y)), ImVec2((origin.x) + crosshair_size, (origin.y)), var->Settings.crosshair_color.color(), 1.5f);
		}

		if (var->keybinds)
		{
			if (GetAsyncKeyState(var->Settings.cfg.i_unlockallkey) & true) {
				if (var->Settings.server.unlockall)
				{
					if (var->Settings.b_unlock)
					{
						lock();
					}
					else
					{
						unlock();
					}
					Sleep(15);

					var->Settings.b_unlock = !var->Settings.b_unlock;
				}
			}
			if (GetAsyncKeyState(var->Settings.cfg.i_reversekey) & true) {
				if (var->Settings.server.reverse)
				{
					if (var->Settings.b_camo == true)
					{
						lockreverse();
					}
					else
					{
						reversecamo();
					}
					Sleep(15);

					var->Settings.b_camo = !var->Settings.b_camo;
				}
			}
			if (GetAsyncKeyState(var->Settings.cfg.i_200fovkey) & true) {
				// 200 FOV
				if (var->Settings.server.fov)
				{
					if (var->Settings.b_fov)
					{
						// disable
						dvar_set2("NSSLSNKPN", 1);
						var->Settings.f_fov = 1.f;
						SendToastNotification("^1PUT AIO", "200 FOV Disabled!", "ui_camo_11c");
					}
					else
					{
						// enable
						dvar_set2("NSSLSNKPN", 2);
						var->Settings.f_fov = 2.f;
						SendToastNotification("^1PUT AIO", "200 FOV Enabled!", "ui_camo_11c");
					}
					Sleep(15);

					var->Settings.b_fov = !var->Settings.b_fov;
				}
			}
			if (GetAsyncKeyState(var->Settings.cfg.i_chamskey) & true) {
				// Chams

				var->Settings.chams = !var->Settings.chams;
				Sleep(15);
			}
			if (var->Settings.b_dynamic3p)
			{
				if (var->Settings.server.d3person)
				{
					if (is_key_down(VK_RBUTTON) || is_key_down(VK_GAMEPAD_LEFT_TRIGGER))
					{
						dvar_set2("NOSLRNTRKL", 0);
					}
					else
					{
						dvar_set2("NOSLRNTRKL", 1);
					}
				}
			}
		}
		if (GetAsyncKeyState(var->Settings.cfg.i_disablekey) & true) {
			var->keybinds = !var->keybinds;
			Sleep(15);
		}
		imgui::imgui_no_border(g_game::init, main_font);
	}
	//g_game::init();
	imgui::imgui_frame_end();
	
	return ori_present(pSwapChain, SyncInterval, Flags);
}

//extern void Log_(const char* fmt, ...);
#define LOGS(fmt, ...) Log_(xorstr_(fmt), ##__VA_ARGS__)

#define LOGS_ADDR(var_name)										\
		LOGS(#var_name ": 0x%llX (0x%llx)", var_name, var_name > var->baseModule - 0x10000 ? var_name -  var->baseModule : 0);

std::future<void> disc_future;
bool b_disc;

DWORD WINAPI initthread(HMODULE hModule)
{
	init();
	getOffsets();
	getSwapper();

	var->Settings.menuInit = true;

	if (kiero::init(kiero::RenderType::D3D12) == kiero::Status::Success)
	{
		kiero::bind(54, (void**)&oExecuteCommandListsD3D12, imgui::hookExecuteCommandListsD3D12);
		kiero::bind(140, (void**)&ori_present, present_hk);
	}
	else
	{
		MessageBoxW(var->hWind, L"Could not hook to the game process. Try reinstalling DirectX, updating your graphics drivers, disabling any overlays, and restarting your PC.", L"Error!", MB_ICONERROR);
	}
	return 0;
}

std::future<DWORD WINAPI> init_future;

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		try {
			init_future = std::async(std::launch::async, initthread, module);
		}
		catch (const std::system_error&) {
			return FALSE;
		}
		//initthread(module);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}