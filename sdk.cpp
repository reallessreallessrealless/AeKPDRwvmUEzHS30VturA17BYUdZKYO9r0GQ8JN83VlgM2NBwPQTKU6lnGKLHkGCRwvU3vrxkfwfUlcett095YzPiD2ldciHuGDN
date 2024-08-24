#include "sdk.h"
#include "IconsFontAwesome.h"
#include "xor.h"
#include <wininet.h>
#include <future>
#include <urlmon.h>
#pragma comment(lib, "urlmon.lib")

#pragma warning(disable : 4996)

HWND process::hwnd;

#include <json/json.hpp>
#include "menu.h"
#include <cstdarg>
#include "utility.h"
using json = nlohmann::json;

std::string serverBoolFile;
bool serverConnected;

int boolToInt(bool btoi)
{
	if (btoi == true)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool intToBool(int itob)
{
	if (itob == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void saveConfig(int configNumber) {
	std::filesystem::create_directories(var->Settings.docuPath);
	std::string path = var->Settings.docuPath + "\\config" + std::to_string(configNumber) + ".json";
	remove(path.c_str());
	std::ofstream log(path.c_str(), std::ofstream::app | std::ofstream::out);

	json j;
	j["keybinds"] = { {"disable", var->Settings.cfg.i_disablekey}, {"menu1", var->Settings.cfg.i_menukey}, {"menu2", var->Settings.cfg.i_menu2key}, {"eject", var->Settings.cfg.i_ejectkey},
		{"unlockall", var->Settings.cfg.i_unlockallkey}, {"reversecamos", var->Settings.cfg.i_reversekey}, {"200fov", var->Settings.cfg.i_200fovkey}, {"chams", var->Settings.cfg.i_chamskey} };

	//favorites
	j["startup"] = { {"favorites", {"lootchecks", boolToInt(var->Settings.b_owner)}, {"unlockall", boolToInt(var->Settings.b_unlock)}, {"reversecamos", boolToInt(var->Settings.b_camo)}, 
		{"fov", {"enabled", boolToInt(var->Settings.b_fov)}, {"value", var->Settings.f_fov} },
		{"map", {"enabled", boolToInt(var->Settings.b_map)}, {"value", var->Settings.f_map} }, {"fpsboost", boolToInt(var->Settings.b_fps)} },
		//chams
		{"chams", {"enabled", boolToInt(var->Settings.chams)}, {"visible", boolToInt(var->Settings.visibleOutlines)}, {"nonvisible", boolToInt(var->Settings.notVisibleOutlines)}, {"fill", boolToInt(var->Settings.chamFill)},
		{"loot", boolToInt(var->Settings.lootChams)}, {"rgbplayer", boolToInt(var->Settings.rgbChams)}, {"rgbloot", boolToInt(var->Settings.rgblootChams)},
		{"playercolor", var->Settings.playerColor}, {"lootcolor", var->Settings.lootColor}, {"linewidth", var->Settings.lineWidthNum} },
		//dvars
		{"dvars", {"nogun", boolToInt(var->Settings.b_gun)}, {"crosshair", boolToInt(var->Settings.b_crosshair)}, {"noshieldshake", boolToInt(var->Settings.b_shield)}, {"heartcheat", boolToInt(var->Settings.b_heart)},
		{"profanitynames", boolToInt(var->Settings.b_name)}, {"removecrosshair", boolToInt(var->Settings.b_nocrosshair)}, {"breakcamera", boolToInt(var->Settings.b_fuckview)}, {"nofog", boolToInt(var->Settings.b_no_fog)},
		{"drawfps", boolToInt(var->Settings.b_fpss)}, {"devplaylist", boolToInt(var->Settings.b_playlist)}, {"skiptutorial", boolToInt(var->Settings.b_tut)}, {"thirdperson", boolToInt(var->Settings.b_Thirdperson)},
		{"dynamicthirdperson", boolToInt(var->Settings.b_dynamic3p)}, {"forcemploadouts", boolToInt(var->Settings.b_mploadout)}, {"maxbright", boolToInt(var->Settings.b_brightmax)} },
		//editor
		{"editor", {"clantag", ""}, {"operator", var->Settings.cfg.i_savedop}},
		//force save
		{"forcesave", {"name", {1, var->Settings.name1}, {2, var->Settings.name2}, {3, var->Settings.name3}, {4, var->Settings.name4}, {5, var->Settings.name5}, 
		{"camo", {1, var->Settings.current_camo}, {2, var->Settings.current_camo2}, {3, var->Settings.current_camo3}, {4, var->Settings.current_camo4}, {5, var->Settings.current_camo5} }, 
		{"enabled", {1, boolToInt(var->Settings.slot1)}, {2, boolToInt(var->Settings.slot2)}, {3, boolToInt(var->Settings.slot3)}, {4, boolToInt(var->Settings.slot4)}, {5, boolToInt(var->Settings.slot5)} } },
		{"guns", var->Settings.gamemodeselection}, {"attachments", var->Settings.attachselection}, {"delete", boolToInt(var->Settings.deletebp)} } };
	log << j;
	log.close();
}

void newConfig() {
	std::filesystem::create_directories(var->Settings.docuPath);
	std::string path = var->Settings.docuPath + "\\config1.json";
	std::ofstream log(path.c_str(), std::ofstream::app | std::ofstream::out);

	json j;
	j["keybinds"] = { {"disable", 112}, {"menu1", 45}, {"menu2", 36}, {"eject", 35}, {"unlockall", 120}, {"reversecamos", 121}, {"200fov", 122}, {"chams", 123} };

	//favorites
	j["startup"] = { {"favorites", {"lootchecks", 1}, {"unlockall", 0}, {"reversecamos", 0}, {"fov", {"enabled", 0}, {"value", 1.0} }, {"map", {"enabled", 0}, {"value", 1.0} }, {"fpsboost", 0} },
		//chams
		{"chams", {"enabled", 0}, {"visible", 1}, {"nonvisible", 1}, {"fill", 0}, {"loot", 0}, {"rgbplayer", 0}, {"rgbloot", 0},
		{"playercolor", var->Settings.playerColor }, {"lootcolor", var->Settings.lootColor }, {"linewidth", 1} },
		//dvars
		{"dvars", {"nogun", 0}, {"crosshair", 0}, {"noshieldshake", 0}, {"heartcheat", 0}, {"profanitynames", 0}, {"removecrosshair", 0},
		{"breakcamera", 0}, {"nofog", 0}, {"drawfps", 0}, {"devplaylist", 0}, {"skiptutorial", 0}, {"thirdperson", 0}, {"dynamicthirdperson", 0},
		{"forcemploadouts", 0}, {"maxbright", 0} },
		//editor
		{"editor", {"clantag", ""}, {"operator", 0} },
		//force save
		{"forcesave", {"name", {1, ""}, {2, ""}, {3, ""}, {4, ""}, {5, ""}, {"camo", {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}}, {"enabled", {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0} } },
		{"guns", 0}, {"attachments", 0}, {"delete", 0} } };
	log << j;
	log.close();
}

void setVars(int configNumber)
{
	std::string path = var->Settings.docuPath + "\\config" + std::to_string(configNumber) + ".json";
	if (!std::filesystem::exists(path))
	{
		MessageBoxA(var->hWind, "Config file does not exist. Save one before trying to apply it!", "Error!", MB_ICONERROR);
		return;
	}
	std::ifstream f(path);
	json data = json::parse(f);
	//keybinds
	var->Settings.cfg.i_disablekey = atoi(data["keybinds"]["disable"].dump().c_str());
	var->Settings.cfg.i_ejectkey = atoi(data["keybinds"]["eject"].dump().c_str());
	var->Settings.cfg.i_menukey = atoi(data["keybinds"]["menu1"].dump().c_str());
	var->Settings.cfg.i_menu2key = atoi(data["keybinds"]["menu2"].dump().c_str());
	var->Settings.cfg.i_unlockallkey = atoi(data["keybinds"]["unlockall"].dump().c_str());
	var->Settings.cfg.i_reversekey = atoi(data["keybinds"]["reversecamos"].dump().c_str());
	var->Settings.cfg.i_200fovkey = atoi(data["keybinds"]["200fov"].dump().c_str());
	var->Settings.cfg.i_chamskey = atoi(data["keybinds"]["chams"].dump().c_str());
	//favorites
	var->Settings.b_owner = atoi(data["startup"][0][1][1].dump().c_str());
	var->Settings.b_unlock = atoi(data["startup"][0][2][1].dump().c_str());
	var->Settings.b_camo = atoi(data["startup"][0][3][1].dump().c_str());
	var->Settings.b_fov = atoi(data["startup"][0][4][1][1].dump().c_str());
	var->Settings.f_fov = atof(data["startup"][0][4][2][1].dump().c_str());
	var->Settings.b_map = atoi(data["startup"][0][5][1][1].dump().c_str());
	var->Settings.f_map = atof(data["startup"][0][5][2][1].dump().c_str());
	var->Settings.b_fps = atoi(data["startup"][0][6][1].dump().c_str());
	//chams
	var->Settings.chams = atoi(data["startup"][1][1][1].dump().c_str());
	var->Settings.visibleOutlines = atoi(data["startup"][1][2][1].dump().c_str());
	var->Settings.notVisibleOutlines = atoi(data["startup"][1][3][1].dump().c_str());
	var->Settings.chamFill = atoi(data["startup"][1][4][1].dump().c_str());
	var->Settings.lootChams = atoi(data["startup"][1][5][1].dump().c_str());
	var->Settings.rgbChams = atoi(data["startup"][1][6][1].dump().c_str());
	var->Settings.rgblootChams = atoi(data["startup"][1][7][1].dump().c_str());
	var->Settings.playerColor = atoi(data["startup"][1][8][1].dump().c_str());
	var->Settings.lootColor = atoi(data["startup"][1][9][1].dump().c_str());
	var->Settings.lineWidthNum = atoi(data["startup"][1][10][1].dump().c_str());
	//dvars
	var->Settings.b_gun = atoi(data["startup"][2][1][1].dump().c_str());
	var->Settings.b_crosshair = atoi(data["startup"][2][2][1].dump().c_str());
	var->Settings.b_shield = atoi(data["startup"][2][3][1].dump().c_str());
	var->Settings.b_heart = atoi(data["startup"][2][4][1].dump().c_str());
	var->Settings.b_name = atoi(data["startup"][2][5][1].dump().c_str());
	var->Settings.b_nocrosshair = atoi(data["startup"][2][6][1].dump().c_str());
	var->Settings.b_fuckview = atoi(data["startup"][2][7][1].dump().c_str());
	var->Settings.b_no_fog = atoi(data["startup"][2][8][1].dump().c_str());
	var->Settings.b_fpss = atoi(data["startup"][2][9][1].dump().c_str());
	var->Settings.b_playlist = atoi(data["startup"][2][10][1].dump().c_str());
	var->Settings.b_tut = atoi(data["startup"][2][11][1].dump().c_str());
	var->Settings.b_Thirdperson = atoi(data["startup"][2][12][1].dump().c_str());
	var->Settings.b_dynamic3p = atoi(data["startup"][2][13][1].dump().c_str());
	var->Settings.b_mploadout = atoi(data["startup"][2][14][1].dump().c_str());
	var->Settings.b_brightmax = atoi(data["startup"][2][15][1].dump().c_str());
	//editor
	var->Settings.cfg.i_savedop = atoi(data["startup"][3][2][1].dump().c_str());
	//force save
	/*var->Settings.name1 = data["startup"][4][1][1].dump().c_str();
	var->Settings.name2 = data["startup"][4][2][1].dump().c_str();
	var->Settings.name3 = data["startup"][4][3][1].dump().c_str();
	var->Settings.name4 = data["startup"][4][4][1].dump().c_str();
	var->Settings.name5 = data["startup"][4][5][1].dump().c_str();*/
	var->Settings.current_camo = atoi(data["startup"][4][6][1].dump().c_str());
	var->Settings.current_camo2 = atoi(data["startup"][4][7][1].dump().c_str());
	var->Settings.current_camo3 = atoi(data["startup"][4][8][1].dump().c_str());
	var->Settings.current_camo4 = atoi(data["startup"][4][9][1].dump().c_str());
	var->Settings.current_camo5 = atoi(data["startup"][4][10][1].dump().c_str());
	var->Settings.slot1 = atoi(data["startup"][4][11][1].dump().c_str());
	var->Settings.slot2 = atoi(data["startup"][4][12][1].dump().c_str());
	var->Settings.slot3 = atoi(data["startup"][4][13][1].dump().c_str());
	var->Settings.slot4 = atoi(data["startup"][4][14][1].dump().c_str());
	var->Settings.slot5 = atoi(data["startup"][4][15][1].dump().c_str());
	var->Settings.gamemodeselection = atoi(data["startup"][4][16][1].dump().c_str());
	var->Settings.attachselection = atoi(data["startup"][4][17][1].dump().c_str());
	var->Settings.deletebp = atoi(data["startup"][4][18][1].dump().c_str());
	f.close();
}



BOOL CALLBACK process::EnumWindowCallBack(HWND hWnd, LPARAM lParam)
{
	DWORD dwPid = 0;
	GetWindowThreadProcessId(hWnd, &dwPid);
	if (dwPid == lParam)
	{
		hwnd = hWnd;
		return FALSE;
	}
	return TRUE;
}

HWND process::get_process_window()
{
	if (hwnd)
		return hwnd;

	EnumWindows(process::EnumWindowCallBack, GetCurrentProcessId());

	if (hwnd == NULL)
		Exit();

	return hwnd;
}

HWND process::get_process_window(DWORD procID)
{
	if (hwnd)
		return hwnd;

	EnumWindows(process::EnumWindowCallBack, procID);

	if (hwnd == NULL)
		Exit();

	return hwnd;
}

namespace g_game
{
	void main_loop(ImFont* font);
	void ui_header()
	{
		if (var->Settings.open)
		{
			ImGuiIO& io = ImGui::GetIO();
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.01f));
			ImGui::Begin("A", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
			ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
			ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
			ImU32 status = IM_COL32(255, 0, 0, 255);
			int dwWidth = GetSystemMetrics(SM_CXSCREEN) / 4;
			int dwHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
			//ImGui::GetForegroundDrawList()->AddRectFilled({ 10, 25 }, { 25,10 }, status, .4f, 10);
			//ImGui::GetForegroundDrawList()->AddText(ImVec2(dwWidth * 3.5f, 40), status, ICON_FA_GAMEPAD);
			//ImGui::GetForegroundDrawList()->AddText(ImVec2(20, 20), status, ICON_FA_GAMEPAD);
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
			ImGui::Begin("A", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus);
			ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
			ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
			int dwWidth = GetSystemMetrics(SM_CXSCREEN) / 4;
			int dwHeight = GetSystemMetrics(SM_CYSCREEN) / 2;
			ImU32 status = IM_COL32(255, 0, 0, 255);
			//ImGui::GetForegroundDrawList()->AddCircleFilled({ 20, 20 }, 5, status);
			//ImGui::GetForegroundDrawList()->AddText(ImVec2(dwWidth * 3.5f, 50), 6, status);
			//ImGui::GetForegroundDrawList()->AddText(ImVec2(20, 20), status, ICON_FA_GAMEPAD);
		}
	}

	void ui_end()
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		window->DrawList->PushClipRectFullScreen();
		ImGui::End();
		ImGui::PopStyleColor();
	}

	void init(ImFont* font)
	{
		ui_header();
		main_loop(font);
		ui_end();
	}

	struct GfxHudOutlineState// Size=0x118
	{
		bool enable;// Offset=0x0 Size=0x1
		unsigned int mode;// Offset=0x4 Size=0x4
		float width;// Offset=0x28 Size=0x4
		float scopeWidth;// Offset=0x7c Size=0x4
		float occludedColorFromFill;// Offset=0x110 Size=0x4
		bool depthTestInScope;// Offset=0x114 Size=0x1
		bool fillInScope;// Offset=0x115 Size=0x1
	};

	struct GfxSceneHudOutlineInfo// Size=0x24
	{
		unsigned int color;// Offset=0x0 Size=0x4
		float scopeStencil;// Offset=0x4 Size=0x4
		bool drawOccludedPixels;// Offset=0x8 Size=0x1
		bool drawNonOccludedPixels;// Offset=0x9 Size=0x1
		bool fill;// Offset=0xa Size=0x1
		bool useAlternateColor;// Offset=0xb Size=0x1
		bool forSpectator;// Offset=0xc Size=0x1
		bool specialActive;// Offset=0xd Size=0x1
		unsigned char renderMode;// Offset=0xe Size=0x1
		unsigned char lineWidth;// Offset=0xf Size=0x1
		unsigned char temperatureSet;// Offset=0x10 Size=0x1
		unsigned int mapEntLookup;// Offset=0x14 Size=0x4
		float temperatureBase;// Offset=0x18 Size=0x4
		float temperatureScale;// Offset=0x1c Size=0x4
		float characterEVOffset;// Offset=0x20 Size=0x4
	};

	enum HudOutlineColor
	{
		HUD_OUTLINE_COLOR_NONE = 0,
		HUD_OUTLINE_COLOR_WHITE = 1,
		HUD_OUTLINE_COLOR_RED = 2,
		HUD_OUTLINE_COLOR_GREEN = 3,
		HUD_OUTLINE_COLOR_CYAN = 4,
		HUD_OUTLINE_COLOR_ORANGE = 5,
		HUD_OUTLINE_COLOR_YELLOW = 6,
		HUD_OUTLINE_COLOR_SCOPE = 7,
		HUD_OUTLINE_COLOR_MLG_ENEMY = 8,
		HUD_OUTLINE_COLOR_MLG_FRIEND = 9,
		HUD_OUTLINE_COLOR_MLG_TEAM0 = 10,
		HUD_OUTLINE_COLOR_MLG_TEAM1 = 11,
		HUD_OUTLINE_COLOR_MAX = 12
	};

	enum PlayerOutlineColorMode
	{
		COLOR_BY_VIEWER_TEAM = 0,
		COLOR_BY_TEAM_COLOR = 1
	};

	enum PlayerOutlineViewMode
	{
		OUTLINE_ALL = 0,
		OUTLINE_SAME_TEAM = 1,
		OUTLINE_OPPOSITE_TEAM = 2,
		OUTLINE_NONE = 3
	};

	struct GfxSceneEntityMutableShaderData
	{
		char pad[0x88];
		GfxSceneHudOutlineInfo hudOutlineInfo;
	};

	struct CgCompassSystemMP
	{
		char pad[0xFF00];
		//GfxSceneHudOutlineInfo hudOutlineInfo;
	};

	unsigned char tempRainbow[4] = { 255, 0, 0, 0 };
	unsigned __int64 FuncOriginal;
	void updateRainbowColor()
	{
		int stage = tempRainbow[3];
		switch (stage) {
		case 0:        tempRainbow[2] += 5;        if (tempRainbow[2] == 255)            tempRainbow[3] = 1;        break;
		case 1:        tempRainbow[0] -= 5;        if (tempRainbow[0] == 0)            tempRainbow[3] = 2;        break;
		case 2:        tempRainbow[1] += 5;        if (tempRainbow[1] == 255)            tempRainbow[3] = 3;        break;
		case 3:        tempRainbow[2] -= 5;        if (tempRainbow[2] == 0)            tempRainbow[3] = 4;        break;
		case 4:        tempRainbow[0] += 5;        if (tempRainbow[0] == 255)            tempRainbow[3] = 5;        break;
		case 5:        tempRainbow[1] -= 5;        if (tempRainbow[1] == 0)            tempRainbow[3] = 0;        break;
		}
	}

	bool in_game()
	{
		return !*(char*)(var->baseModule + var->Offest.ingame);
	}

	void hookFunc(__int64 a1, __int64 a2, unsigned int entnum, unsigned int renderFlags, GfxSceneEntityMutableShaderData* a3, __int64 a4, float materialTime)
	{
		//
		if ((*(BYTE*)a2 == 1)) //1 = all players, 2 = dead bodies
		{
			if (renderFlags > 513) //0 = loot, 513 = player
			{
				if (entnum < 201)
				{
					if (var->Settings.visibleOutlines)
						a3->hudOutlineInfo.drawNonOccludedPixels = true;
					if (var->Settings.notVisibleOutlines)
						a3->hudOutlineInfo.drawOccludedPixels = true;
					if (var->Settings.chamFill)
						a3->hudOutlineInfo.fill = true;

					a3->hudOutlineInfo.renderMode = var->Settings.rendertype;

					if (var->Settings.rgbChams) {

						a3->hudOutlineInfo.color = var->Settings.chamColorRGB;
					}
					else
					{

						a3->hudOutlineInfo.color = var->Settings.playerColor;
					}
					a3->hudOutlineInfo.lineWidth = var->Settings.lineWidthNum;
				}
			}
		}
		if (var->Settings.lootChams)
		{
			if (renderFlags == 0)
			{
				if (var->Settings.visibleOutlines)
					a3->hudOutlineInfo.drawNonOccludedPixels = true;
				if (var->Settings.notVisibleOutlines)
					a3->hudOutlineInfo.drawOccludedPixels = true;
				if (var->Settings.chamFill)
					a3->hudOutlineInfo.fill = true;

				a3->hudOutlineInfo.renderMode = var->Settings.rendertype;

				if (var->Settings.rgblootChams)
				{

					a3->hudOutlineInfo.color = var->Settings.chamColorRGB;
				}
				else
				{

					a3->hudOutlineInfo.color = var->Settings.lootColor;
				}
				a3->hudOutlineInfo.lineWidth = var->Settings.lineWidthNum;
			}
		}
		if (FuncOriginal)
			((void(*)(...))FuncOriginal)(a1, a2, entnum, renderFlags, a3, a4, materialTime);
	}

	void chamCheck()
    {
        if (var->Settings.chams && var->Settings.b_ingame && var->Settings.server.chams) // checkbox && ingame
        {
            if (!var->Settings.chamHooked) // actually hooked or not
            {
                var->Settings.chamHooked = true;
                MH_CreateHook((LPVOID*)(var->baseModule + var->Offest.chamOffset), &hookFunc, (LPVOID*)&FuncOriginal);
                MH_EnableHook((LPVOID*)(var->baseModule + var->Offest.chamOffset));
				ShowToastNotificationAfterUserJoinedParty("^1Chams Enabled^7");
            }
        }
        else
        {
            if (var->Settings.chamHooked)
            {
                var->Settings.chamHooked = false;
                var->Settings.chams = false;
                MH_DisableHook((LPVOID*)(var->baseModule + var->Offest.chamOffset));
				ShowToastNotificationAfterUserLeftParty("^1Chams Disabled^7");
            }
        }
    }

	struct ClientFov
	{
		float finalFov;
		float baseFov;
		float baseFovAdjustment;
	};

	ClientFov* (*oCG_GetViewFovBySpace)(ClientFov* result, int entNum, int fovSpace, bool updateFovWeights);
	ClientFov* hkCG_GetViewFovBySpace(ClientFov* result, int entNum, int fovSpace, bool updateFovWeights)
	{
		ClientFov* fovData = VariadicCall<ClientFov*>(var->Offest.jmp_rbx, (DWORD64)oCG_GetViewFovBySpace, result, entNum, fovSpace, updateFovWeights);

		fovData->baseFov *= var->Settings.f_fovfunc;
		fovData->baseFovAdjustment *= var->Settings.f_fovfunc;
		fovData->finalFov *= var->Settings.f_fovfunc;
		return fovData;
	}

	void fovhook()
	{
		if (var->Settings.fovhook)
		{
			if (!var->Settings.fovhookenable)
			{
				MH_CreateHook((LPVOID*)(var->Offest.A_CG_GetViewFovBySpace), &hkCG_GetViewFovBySpace, reinterpret_cast<LPVOID*>(&oCG_GetViewFovBySpace));
				MH_EnableHook((LPVOID*)(var->Offest.A_CG_GetViewFovBySpace));
				var->Settings.fovhookenable = true;
			}
		}
		else
		{
			if (var->Settings.fovhookenable)
			{
				MH_DisableHook((LPVOID*)(var->Offest.A_CG_GetViewFovBySpace));
				var->Settings.fovhookenable = false;
				var->Settings.fovhook = false;
			}
		}
	}

	void enablefovhook()
	{
		var->Settings.fovhook = true;
		var->Settings.fovhookenable = true;
		MH_CreateHook((LPVOID*)(var->Offest.A_CG_GetViewFovBySpace), &hkCG_GetViewFovBySpace, reinterpret_cast<LPVOID*>(&oCG_GetViewFovBySpace));
		MH_EnableHook((LPVOID*)(var->Offest.A_CG_GetViewFovBySpace));
	}

	void (*oCG_StartShellShock)(__int64 cg, __int64 parms, int start, int duration);
	void hkCG_StartShellShock(__int64 cg, __int64 parms, int start, int duration) {
		return;
	}

	void shellhook()
	{
		if (var->Settings.shellhook)
		{
			if (!var->Settings.shellhookenable)
			{
				MH_CreateHook((LPVOID*)(var->Offest.A_CG_StartShellShock), &hkCG_StartShellShock, reinterpret_cast<LPVOID*>(&oCG_StartShellShock));
				MH_EnableHook((LPVOID*)(var->Offest.A_CG_StartShellShock));
				var->Settings.shellhookenable = true;
			}
		}
		else
		{
			if (var->Settings.shellhookenable)
			{
				MH_DisableHook((LPVOID*)(var->Offest.A_CG_StartShellShock));
				var->Settings.shellhookenable = false;
				var->Settings.shellhook = false;
			}
		}
	}

	void main_loop(ImFont* font)
	{
		var->Settings.b_ingame = g_game::in_game();
		if (!var->Settings.b_ingame)
		{
			var->Settings.chams = false;
			var->Settings.shellhook = false;
			var->Settings.fovhookmenu = false;
			return;
		}

		chamCheck();
		fovhook();
		shellhook();
		updateRainbowColor();
		var->Settings.chamColorRGB = ImGui::ColorConvertFloat4ToU32(ImVec4((float)tempRainbow[0] / 255, (float)tempRainbow[1] / 255, (float)tempRainbow[2] / 255, 1.0f));
	}
}

dvar_s* Dvar_FindVarByName(const char* dvarName)
{
	//[48 83 EC 48 49 8B C8 E8 ?? ?? ?? ?? + 0x7] resolve call.
	return reinterpret_cast<dvar_s * (__fastcall*)(const char* dvarName)>(var->baseModule + var->Offest.Dvar_FindVarByName)(dvarName);
}

uintptr_t Dvar_SetBool_Internal(dvar_s* a1, bool a2)
{
	//E8 ? ? ? ? 80 3D ? ? ? ? ? 4C 8D 35 ? ? ? ? 74 43 33 D2 F7 05 ? ? ? ? ? ? ? ? 76 2E
	return reinterpret_cast<std::ptrdiff_t(__fastcall*)(dvar_s * a1, bool a2)>(var->baseModule + var->Offest.Dvar_SetBoolInternal)(a1, a2);
}

uintptr_t Dvar_SetInt_Internal(dvar_s* a1, unsigned int a2)
{
	//40 53 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 0F B6 41 09 48 8B D9
	return reinterpret_cast<std::ptrdiff_t(__fastcall*)(dvar_s * a1, unsigned int a2)>(var->baseModule + var->Offest.Dvar_SetInt_Internal)(a1, a2);
}

uintptr_t Dvar_SetBoolByName(const char* dvarName, bool value)
{
	//"48 89 ? ? ? 57 48 81 EC ? ? ? ? 0F B6 ? 48 8B"
	int64(__fastcall * Dvar_SetBoolByName_t)(const char* dvarName, bool value); //48 89 5C 24 ? 57 48 81 EC ? ? ? ? 0F B6 DA
	return reinterpret_cast<decltype(Dvar_SetBoolByName_t)>(var->baseModule + var->Offest.Dvar_SetBoolByName)(dvarName, value);
}

uintptr_t Dvar_SetFloat_Internal(dvar_s* a1, float a2)
{
	//E8 ? ? ? ? 45 0F 2E C8 RESOLVE CALL
	return reinterpret_cast<std::ptrdiff_t(__fastcall*)(dvar_s * a1, float a2)>(var->baseModule + var->Offest.Dvar_SetFloat_Internal)(a1, a2);
}

uintptr_t Dvar_SetIntByName(const char* dvarname, int value)
{
	uintptr_t(__fastcall * Dvar_SetIntByName_t)(const char* dvarname, int value); //48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 8B DA 48 8B F9
	return reinterpret_cast<decltype(Dvar_SetIntByName_t)>(var->baseModule + var->Offest.Dvar_SetIntByName)(dvarname, value);
}

void CL_PlayerData_SetCustomClanTag(const char* clanTag)
{
	//74 ?? 48 8d 15 ?? ?? ?? ?? 8b cf e8 ?? ?? ?? ?? 48 8b 5c 24 30
	uintptr_t address = var->baseModule + var->Offest.clantag_offset;
	((void(*)(int, const char*))address)(0, clanTag);
}

void ShowToastNotificationAfterUserJoinedParty(const char* msg)
{
	uintptr_t address = var->baseModule + var->Offest.ShowToastNotificationAfterUserJoinedParty;
	if (is_valid_ptr(address))
	{
		if (var->Settings.server.toastjoin)
		{
			address += sizeof(1);
			((void(*)(int, int, int, const char*, int))address)(0, 0, 0, msg, 0);
		}
	}
}

__int64 Com_DDL_LoadAsset(__int64 file) {
	uintptr_t address = var->baseModule + var->Offest.ddl_loadasset;
	return ((__int64 (*)(__int64))address)(file);
}

bool CL_PlayerData_GetDDLBufferr(__int64 context, int controllerindex, int stats_source, unsigned int statsgroup) {
	uintptr_t address = var->baseModule + var->Offest.ddl_getdllbuffer;
	return ((bool (*)(__int64, int, int, unsigned int))address)(context, controllerindex, stats_source, statsgroup);
}

bool ParseShitt(const char* a, const char** b, const int c, int* d)
{
	uintptr_t address = var->baseModule + var->Offest.a_parse;
	return ((bool (*)(const char* a, const char** b, const int c, int* d))address)(a, b, c, d);
}

char DDL_MoveToPathh(__int64* fromState, __int64* toState, int depth, const char** path) {
	uintptr_t address = var->baseModule + var->Offest.ddl_movetopath;
	return ((char (*)(__int64* fromState, __int64* toState, int depth, const char** path))address)(fromState, toState, depth, path);

}

__int64 Com_DDL_LoadAsset(const char* file) {
	auto function = reinterpret_cast<__int64(*)(const char*)>(var->baseModule + var->Offest.ddl_loadasset);
	return function(file);
}

__int64 Com_DDL_LoadAssett(__int64 file) {
	uintptr_t address = var->baseModule + var->Offest.ddl_loadasset;
	return ((__int64 (*)(__int64))address)(file);
}

bool Com_DDL_CreateContext(void* buff, int len, __int64 def, DDLContext* ddlContext, __int64 a5, __int64 a6) {
	auto function = reinterpret_cast<bool(*)(void*, int, __int64, DDLContext*, __int64, __int64)>(var->baseModule + var->Offest.Com_DDL_CreateContext);
	return function(buff, len, def, ddlContext, a5, a6);
}

char NavigateBlueprintDDL(DDLState* state, const char* path) {
	auto function = reinterpret_cast<char(*)(DDLState*, const char*)>(var->baseModule + var->Offest.NavigateBlueprintDDL);
	return function(state, path);
}

DDLState* DDL_GetRootState(DDLState* state, __int64 def) {
	auto function = reinterpret_cast<DDLState * (*)(DDLState*, __int64)>(var->baseModule + var->Offest.ddl_getrootstate);
	return function(state, def);
}

__int64 DDL_GetRootState(__int64 state, __int64 file) {
	uintptr_t address = var->baseModule + var->Offest.ddl_getrootstate;
	return ((__int64 (*)(__int64, __int64))address)(state, file);
}

__int64 DDL_GetType(const DDLState* state) {
	auto function = reinterpret_cast<__int64(*)(const DDLState*)>(var->baseModule + var->Offest.DDL_GetType);
	return function(state);
}

bool DDL_SetString(const DDLState* state, DDLContext* ddlcontext, const char* value) {
	auto function = reinterpret_cast<bool(*)(const DDLState*, DDLContext*, const char*)>(var->baseModule + var->Offest.ddl_setstring);
	return function(state, ddlcontext, value);
}

char DDL_SetString(__int64 fstate, __int64 context, const char* value) {
	uintptr_t address = var->baseModule + var->Offest.ddl_setstring;
	return ((char (*)(__int64, __int64, const char*))address)(fstate, context, value);
}

bool DDL_SetEnum(const DDLState* state, DDLContext* ddlcontext, const char* value) {
	auto function = reinterpret_cast<bool(*)(const DDLState*, DDLContext*, const char*)>(var->baseModule + var->Offest.DDL_SetEnum);
	return function(state, ddlcontext, value);
}

bool DDL_SetInt(const DDLState* state, DDLContext* ddlcontext, int value) {
	auto function = reinterpret_cast<bool(*)(const DDLState*, DDLContext*, int)>(var->baseModule + var->Offest.ddl_setint);
	return function(state, ddlcontext, value);
}

char DDL_SetInt(__int64 fstate, __int64 context, unsigned int value) {
	uintptr_t address = var->baseModule + var->Offest.ddl_setint;
	return ((char (*)(__int64, __int64, unsigned int))address)(fstate, context, value);
}

char DDL_SetInt2(__int64* fstate, __int64* context, int value) {
	uintptr_t address = var->baseModule + var->Offest.ddl_setint;
	return ((char (*)(__int64*, __int64*, unsigned int))address)(fstate, context, value);
}

int DDL_GetInt(__int64* fstate, __int64* context) {
	uintptr_t address = var->baseModule + var->Offest.ddl_getint;
	return ((int (*)(__int64*, __int64*))address)(fstate, context);
}

void* OnlineChatManger_GetInstance() {
	auto function = reinterpret_cast<void* (*)()>(var->baseModule + var->Offest.OnlineChatManger_GetInstance);
	return function();
}

__int64 SendPlayerEvent(__int64 onlinechatmanager, int controllerindex, const char* message, unsigned __int64 xuid, const char* gamertag) {
	auto function = reinterpret_cast<__int64(*)(__int64, int, const char*, unsigned __int64, const char*)>(var->baseModule + var->Offest.sendPlayerEvent);
	return function(onlinechatmanager, controllerindex, message, xuid, gamertag);
}

void ShowToastNotificationAfterUserLeftParty(const char* Username)
{
	if (is_valid_ptr(var->baseModule + var->Offest.ShowToastNotificationAfterUserLeftParty))
	{
		if (var->Settings.server.toastleft)
		{
			void(__fastcall * ShowToastNotificationAfterUserLeftParty_t)(int, int, int, const char* text, int);
			return reinterpret_cast<decltype(ShowToastNotificationAfterUserLeftParty_t)>(var->baseModule + var->Offest.ShowToastNotificationAfterUserLeftParty)(0, 0, 0, Username, 0);
		}
	}
}

struct StringTable {
	const char* name;
	int columnCount;
	int rowCount;
	int uniqueCellCount;
	unsigned __int16* cellIndices;
	int* hashes;
	const char** strings;
};

void StringTable_GetAssett(const char* fileName, StringTable** stringtable) // E8 ? ? ? ? 48 8B 4C 24 ? E8 ? ? ? ? 33 FF [resolve call]    
{
	uintptr_t address = var->baseModule + var->Offest.StringTable_GetAsset;
	((void(*)(const char*, StringTable**))address)(fileName, stringtable);

}

uintptr_t getAddressForStringInStringTable(const char* stringTablePath, const char* assetToFind)
{
	StringTable* table = nullptr;
	StringTable_GetAssett(stringTablePath, (StringTable**)&table);
	auto total = (table->columnCount) * (table->rowCount);
	for (int i = 0; i < table->uniqueCellCount; i++)
		if (!strcmp(assetToFind, table->strings[i]))
			return reinterpret_cast<uintptr_t&>(table->strings[i]);
	return 0;
}

uintptr_t OGUnlockPTR1;
uintptr_t OGUnlockPTR2;
bool unlockInited = false;

const char CWGold[24] = "camo_mp_t9mastery_gold";
const char CWDiamond[27] = "camo_mp_t9mastery_diamond";
const char CWUltra[30] = "camo_mp_t9mastery_darkmatter";
const char CWZMGold[24] = "camo_zm_t9mastery_gold";
const char CWPDiamond[27] = "camo_zm_t9mastery_diamond";
const char CWAether[29] = "camo_zm_t9mastery_darkmatter";
const char Cherry[19] = "camo_mp_t9tier5_05";
const char CWFaze[18] = "camo_t9cdl_atl_pc";

const char Gold[9] = "camo_11a";
const char MW_Diamond[9] = "camo_11b";
const char Damascus[9] = "camo_11c";
const char Obisidian[9] = "camo_11d";
const char Activcamo[9] = "camo_00b";
const char MWFaze[9] = "camo_12a";

const char VGGold[12] = "s4_camo_11a";
const char VGDiamond[12] = "s4_camo_11b";
const char VGAtomic[12] = "s4_camo_11c";
const char VGGoldenViper[15] = "s4_camo_11a_zm";
const char VGPlagueDiamond[15] = "s4_camo_11b_zm";
const char VGDarkAether[15] = "s4_camo_11c_zm";
const char VGFPros[25] = "mtl_s4_camo_gold_digital";
const char VGDPros[26] = "mtl_s4_camo_gold_woodland";
const char VGTitanium[27] = "s4_camo_titanium_trials_01";
const char VGLiquid[27] = "s4_camo_titanium_trials_02";
const char VGSkynet[27] = "s4_camo_titanium_trials_03";
const char VGFaze[24] = "mtl_s4_camo_cdl_faze_pc";

uintptr_t ptr1;
uintptr_t ptr2;
uintptr_t ptr3;
bool camoSwapped;
bool camoSwappedMW;
bool camoSwappedCW;
bool camoSwappedVG;
void getSwapper()
{
	if (!camoSwapped) {
		if (var->Settings.server.camo)
		{
			ptr1 = (getAddressForStringInStringTable("loot/camo_ids.csv", "camo_01a"));
			ptr2 = (getAddressForStringInStringTable("loot/camo_ids.csv", "s4_camo_01a"));
			ptr3 = (getAddressForStringInStringTable("mp/camotable.csv", "camo_mp_t9tier1_01"));
			camoSwapped = true;
		}
		if (var->Settings.server.lootcheck)
		{
			dvar_set2("NRQQOMLOQL", 0);
			dvar_set2("RRTLRKKTT", 0);
			dvar_set2("MKQPRPLQKL", 0);
		}
	}
}

void unlock()
{
	//if (!unlockInited)
	//{
	//	uintptr_t num = (var->baseModule + var->Offest.unlock_offsets + 3);
	//	int num2 = mem::readMemory<int>(num);

	//	uintptr_t unlock_base = num + num2 + 4 - var->baseModule;
	//	uintptr_t numP = (var->baseModule + unlock_base + 0x300);

	//	OGUnlockPTR1 = mem::readMemory<uintptr_t>(var->baseModule + unlock_base + 8);
	//	OGUnlockPTR2 = mem::readMemory<uintptr_t>(var->baseModule + unlock_base);

	//	if (var->steam)
	//	{
	//		//memcpy((BYTE*)numP, (BYTE*)(xorstr_("\x48\x83\xC4\x08\x48\x8B\x5C\x24\x30\x48\x8B\x74\x24\x38\x48\x83\xC4\x20\x5F\x48\xC7\xC0\x01\x00\x00\x00\xC3")), 28);
	//		//memcpy((BYTE*)numP, (BYTE*)(xorstr_("\x48\x83\xC4\x08\x48\x8B\x5C\x24\x48\x48\x8B\x6C\x24\x50\x48\x83\xC4\x20\x41\x5E\x5F\x5E\xB8\x01\x00\x00\x00\xC3")), 29);
	//		memcpy((BYTE*)numP, (BYTE*)(xorstr_("\x48\x83\xC4\x08\x48\x8B\x5C\x24\x38\x48\x8B\x6C\x24\x40\x48\x8B\x74\x24\x48\x48\x83\xC4\x20\x5F\xB8\x01\x00\x00\x00\xC3")), 31);
	//	}
	//	else
	//	{
	//		//memcpy((BYTE*)numP, (BYTE*)(xorstr_("\x48\x83\xC4\x08\x48\x8B\x5C\x24\x30\x48\x8B\x74\x24\x38\x48\x83\xC4\x20\x5F\x48\xC7\xC0\x01\x00\x00\x00\xC3")), 28);
	//		//memcpy((BYTE*)numP, (BYTE*)(xorstr_("\x48\x83\xC4\x08\x48\x8B\x5C\x24\x48\x48\x8B\x6C\x24\x50\x48\x83\xC4\x20\x41\x5E\x5F\x5E\xB8\x01\x00\x00\x00\xC3")), 29);
	//		memcpy((BYTE*)numP, (BYTE*)(xorstr_("\x48\x83\xC4\x08\x48\x8B\x5C\x24\x38\x48\x8B\x6C\x24\x40\x48\x8B\x74\x24\x48\x48\x83\xC4\x20\x5F\xB8\x01\x00\x00\x00\xC3")), 31);
	//	}
	//	
	//	mem::writeMemory<uintptr_t>(var->baseModule + unlock_base + 8, numP);
	//	mem::writeMemory<uintptr_t>(var->baseModule + unlock_base, var->baseModule + unlock_base);

	//	ShowToastNotificationAfterUserJoinedParty("^1Unlock All");
	//	unlockInited = true;
	//}

	if (var->Settings.server.unlockall)
	{
		if (!unlockInited)
		{
			uintptr_t num = (var->baseModule + var->Offest.unlock_offsets + 3);
			int num2 = mem::readMemory<int>(num);

			uintptr_t unlock_base = num + num2 + 4 - var->baseModule;
			uintptr_t numP = (var->baseModule + unlock_base + 0x300);

			OGUnlockPTR1 = mem::readMemory<uintptr_t>(var->baseModule + unlock_base + 8);
			OGUnlockPTR2 = mem::readMemory<uintptr_t>(var->baseModule + unlock_base);

			BYTE shell[] = {
				0x48, 0x83, 0xC4, 0x08, 0xE9, 0x00, 0x00, 0x00, 0x00
			};

			*reinterpret_cast<int*>(shell + 5) = var->baseModule + var->Offest.end_bytes - numP - 9;
			memcpy((BYTE*)numP, shell, 9);

			mem::writeMemory<uintptr_t>(var->baseModule + unlock_base + 8, numP);
			mem::writeMemory<uintptr_t>(var->baseModule + unlock_base, var->baseModule + unlock_base);

			SendToastNotification("^1PUT AIO", "Unlocked Everything!", "ui_camo_11c");
			unlockInited = true;
		}
	}
	else
	{
		throwImGuiError("Unlock All has been disabled.", &var->Settings.b_unlock);
	}
}

void lock()
{
	if (unlockInited) {
		uintptr_t num = (var->baseModule + var->Offest.unlock_offsets + 3);
		int num2 = mem::readMemory<int>(num);

		uintptr_t unlock_base = num + num2 + 4 - var->baseModule;

		mem::writeMemory<uintptr_t>(var->baseModule + unlock_base + 8, OGUnlockPTR1);
		mem::writeMemory<uintptr_t>(var->baseModule + unlock_base, OGUnlockPTR2);

		SendToastNotification("^1PUT AIO", "Locked Everything!", "ui_camo_11c");
		unlockInited = false;
	}
}

void reversecamo()
{
	if (var->Settings.server.reverse)
	{
		if (camoSwappedMW == false) {
			utility::Write((BYTE*)ptr1, (BYTE*)&VGGold, sizeof(VGGold), var->hProc);
			utility::Write((BYTE*)ptr1 + (16), (BYTE*)&VGDiamond, sizeof(VGDiamond), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 2), (BYTE*)&VGAtomic, sizeof(VGAtomic), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 3), (BYTE*)&VGGoldenViper, sizeof(VGGoldenViper), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 5), (BYTE*)&VGPlagueDiamond, sizeof(VGPlagueDiamond), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 7), (BYTE*)&VGDarkAether, sizeof(VGDarkAether), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 9), (BYTE*)&CWGold, sizeof(CWGold), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 12), (BYTE*)&CWDiamond, sizeof(CWDiamond), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 15), (BYTE*)&CWUltra, sizeof(CWUltra), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 18), (BYTE*)&CWZMGold, sizeof(CWZMGold), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 21), (BYTE*)&CWPDiamond, sizeof(CWPDiamond), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 24), (BYTE*)&CWAether, sizeof(CWAether), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 27), (BYTE*)&CWFaze, sizeof(CWFaze), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 30), (BYTE*)&Cherry, sizeof(Cherry), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 33), (BYTE*)&VGFaze, sizeof(VGFaze), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 36), (BYTE*)&VGFPros, sizeof(VGFPros), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 39), (BYTE*)&VGDPros, sizeof(VGDPros), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 42), (BYTE*)&VGTitanium, sizeof(VGTitanium), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 45), (BYTE*)&VGLiquid, sizeof(VGLiquid), var->hProc);
			utility::Write((BYTE*)ptr1 + (16 * 48), (BYTE*)&VGSkynet, sizeof(VGSkynet), var->hProc);
			utility::Write((BYTE*)ptr2, (BYTE*)&Gold, sizeof(Gold), var->hProc);
			utility::Write((BYTE*)ptr2 + 21, (BYTE*)&MW_Diamond, sizeof(MW_Diamond), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 2, (BYTE*)&Damascus, sizeof(Damascus), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 3, (BYTE*)&Obisidian, sizeof(Obisidian), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 4, (BYTE*)&CWGold, sizeof(CWGold), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 6, (BYTE*)&CWDiamond, sizeof(CWDiamond), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 8, (BYTE*)&CWUltra, sizeof(CWUltra), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 10, (BYTE*)&CWZMGold, sizeof(CWZMGold), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 12, (BYTE*)&CWPDiamond, sizeof(CWPDiamond), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 14, (BYTE*)&CWAether, sizeof(CWAether), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 16, (BYTE*)&Cherry, sizeof(Cherry), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 18, (BYTE*)&CWFaze, sizeof(CWFaze), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 20, (BYTE*)&MWFaze, sizeof(MWFaze), var->hProc);
			utility::Write((BYTE*)ptr2 + 21 * 22, (BYTE*)&Activcamo, sizeof(Activcamo), var->hProc);
			utility::Write((BYTE*)ptr3, (BYTE*)&VGGold, sizeof(VGGold), var->hProc);
			utility::Write((BYTE*)ptr3 + 28, (BYTE*)&VGDiamond, sizeof(VGDiamond), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 2, (BYTE*)&VGAtomic, sizeof(VGAtomic), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 3, (BYTE*)&VGGoldenViper, sizeof(VGGoldenViper), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 4, (BYTE*)&VGPlagueDiamond, sizeof(VGPlagueDiamond), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 6, (BYTE*)&VGDarkAether, sizeof(VGDarkAether), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 8, (BYTE*)&Gold, sizeof(Gold), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 9, (BYTE*)&MW_Diamond, sizeof(MW_Diamond), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 10, (BYTE*)&Damascus, sizeof(Damascus), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 11, (BYTE*)&Obisidian, sizeof(Obisidian), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 12, (BYTE*)&MWFaze, sizeof(MWFaze), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 14, (BYTE*)&VGFaze, sizeof(VGFaze), var->hProc);
			utility::Write((BYTE*)ptr3 + 28 * 16, (BYTE*)&Activcamo, sizeof(Activcamo), var->hProc);
			utility::Write((BYTE*)ptr3 + (28 * 18), (BYTE*)&VGFPros, sizeof(VGFPros), var->hProc);
			utility::Write((BYTE*)ptr3 + (28 * 20), (BYTE*)&VGDPros, sizeof(VGDPros), var->hProc);
			utility::Write((BYTE*)ptr3 + (28 * 22), (BYTE*)&VGTitanium, sizeof(VGTitanium), var->hProc);
			utility::Write((BYTE*)ptr3 + (28 * 24), (BYTE*)&VGLiquid, sizeof(VGLiquid), var->hProc);
			utility::Write((BYTE*)ptr3 + (28 * 26), (BYTE*)&VGSkynet, sizeof(VGSkynet), var->hProc);
			SendToastNotification("^1PUT AIO", "Unlocked Reverse Camos!", "ui_camo_11d");
			camoSwappedMW = true;
		}
	}
	else
	{
		throwImGuiError("Reverse Camos has been disabled.", &var->Settings.b_camo);
	}
}

void lockreverse()
{
	if (camoSwappedMW == true) {
		utility::Write((BYTE*)ptr1, (BYTE*)&"camo_01a", sizeof("camo_01a"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16, (BYTE*)&"camo_01b", sizeof("camo_01b"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 2, (BYTE*)&"camo_01c", sizeof("camo_01c"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 3, (BYTE*)&"camo_01d", sizeof("camo_01d"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 4, (BYTE*)&"camo_01e", sizeof("camo_01e"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 5, (BYTE*)&"camo_01f", sizeof("camo_01f"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 6, (BYTE*)&"camo_01g", sizeof("camo_01g"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 7, (BYTE*)&"camo_01h", sizeof("camo_01h"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 8, (BYTE*)&"camo_01i", sizeof("camo_01i"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 9, (BYTE*)&"camo_01j", sizeof("camo_01j"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 10, (BYTE*)&"camo_02a", sizeof("camo_02a"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 11, (BYTE*)&"camo_02b", sizeof("camo_02b"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 12, (BYTE*)&"camo_02c", sizeof("camo_02c"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 13, (BYTE*)&"camo_02d", sizeof("camo_02d"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 14, (BYTE*)&"camo_02e", sizeof("camo_02e"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 15, (BYTE*)&"camo_02f", sizeof("camo_02f"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 16, (BYTE*)&"camo_02g", sizeof("camo_02g"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 17, (BYTE*)&"camo_02h", sizeof("camo_02h"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 18, (BYTE*)&"camo_02i", sizeof("camo_02i"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 19, (BYTE*)&"camo_02j", sizeof("camo_02j"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 20, (BYTE*)&"camo_03a", sizeof("camo_03a"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 21, (BYTE*)&"camo_03b", sizeof("camo_03b"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 22, (BYTE*)&"camo_03c", sizeof("camo_03c"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 23, (BYTE*)&"camo_03d", sizeof("camo_03d"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 24, (BYTE*)&"camo_03e", sizeof("camo_03e"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 25, (BYTE*)&"camo_03f", sizeof("camo_03f"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 26, (BYTE*)&"camo_03g", sizeof("camo_03g"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 27, (BYTE*)&"camo_03h", sizeof("camo_03h"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 28, (BYTE*)&"camo_03i", sizeof("camo_03i"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 29, (BYTE*)&"camo_03j", sizeof("camo_03j"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 30, (BYTE*)&"camo_04a", sizeof("camo_04a"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 31, (BYTE*)&"camo_04b", sizeof("camo_04b"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 32, (BYTE*)&"camo_04c", sizeof("camo_04c"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 33, (BYTE*)&"camo_04d", sizeof("camo_04d"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 34, (BYTE*)&"camo_04e", sizeof("camo_04e"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 35, (BYTE*)&"camo_04f", sizeof("camo_04f"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 36, (BYTE*)&"camo_04g", sizeof("camo_04g"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 37, (BYTE*)&"camo_04h", sizeof("camo_04h"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 38, (BYTE*)&"camo_04i", sizeof("camo_04i"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 39, (BYTE*)&"camo_04j", sizeof("camo_04j"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 40, (BYTE*)&"camo_05a", sizeof("camo_05a"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 41, (BYTE*)&"camo_05b", sizeof("camo_05b"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 42, (BYTE*)&"camo_05c", sizeof("camo_05c"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 43, (BYTE*)&"camo_05d", sizeof("camo_05d"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 44, (BYTE*)&"camo_05e", sizeof("camo_05e"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 45, (BYTE*)&"camo_05f", sizeof("camo_05f"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 46, (BYTE*)&"camo_05g", sizeof("camo_05g"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 47, (BYTE*)&"camo_05h", sizeof("camo_05h"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 48, (BYTE*)&"camo_05i", sizeof("camo_05i"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 49, (BYTE*)&"camo_05j", sizeof("camo_05j"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 50, (BYTE*)&"camo_06a", sizeof("camo_06a"), var->hProc);
		utility::Write((BYTE*)ptr1 + 16 * 51, (BYTE*)&"camo_06b", sizeof("camo_06b"), var->hProc);
		utility::Write((BYTE*)ptr2, (BYTE*)&"s4_camo_01a", sizeof("s4_camo_01a"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21, (BYTE*)&"s4_camo_01b", sizeof("s4_camo_01b"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 2, (BYTE*)&"s4_camo_01c", sizeof("s4_camo_01c"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 3, (BYTE*)&"s4_camo_01d", sizeof("s4_camo_01d"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 4, (BYTE*)&"s4_camo_01e", sizeof("s4_camo_01e"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 5, (BYTE*)&"s4_camo_01f", sizeof("s4_camo_01f"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 6, (BYTE*)&"s4_camo_01g", sizeof("s4_camo_01g"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 7, (BYTE*)&"s4_camo_01h", sizeof("s4_camo_01h"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 8, (BYTE*)&"s4_camo_01i", sizeof("s4_camo_01i"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 9, (BYTE*)&"s4_camo_01j", sizeof("s4_camo_01j"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 10, (BYTE*)&"s4_camo_02a", sizeof("s4_camo_02a"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 11, (BYTE*)&"s4_camo_02b", sizeof("s4_camo_02b"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 12, (BYTE*)&"s4_camo_02c", sizeof("s4_camo_02c"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 13, (BYTE*)&"s4_camo_02d", sizeof("s4_camo_02d"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 14, (BYTE*)&"s4_camo_02e", sizeof("s4_camo_02e"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 15, (BYTE*)&"s4_camo_02f", sizeof("s4_camo_02f"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 16, (BYTE*)&"s4_camo_02g", sizeof("s4_camo_02g"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 17, (BYTE*)&"s4_camo_02h", sizeof("s4_camo_02h"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 18, (BYTE*)&"s4_camo_02i", sizeof("s4_camo_02i"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 19, (BYTE*)&"s4_camo_02j", sizeof("s4_camo_02j"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 20, (BYTE*)&"s4_camo_03a", sizeof("s4_camo_03a"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 21, (BYTE*)&"s4_camo_03b", sizeof("s4_camo_03b"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 22, (BYTE*)&"s4_camo_03c", sizeof("s4_camo_03c"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 23, (BYTE*)&"s4_camo_03d", sizeof("s4_camo_03d"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 24, (BYTE*)&"s4_camo_03e", sizeof("s4_camo_03e"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 25, (BYTE*)&"s4_camo_03f", sizeof("s4_camo_03f"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 26, (BYTE*)&"s4_camo_03g", sizeof("s4_camo_03g"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 27, (BYTE*)&"s4_camo_03h", sizeof("s4_camo_03h"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 28, (BYTE*)&"s4_camo_03i", sizeof("s4_camo_03i"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 29, (BYTE*)&"s4_camo_03j", sizeof("s4_camo_03j"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 30, (BYTE*)&"s4_camo_04a", sizeof("s4_camo_04a"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 31, (BYTE*)&"s4_camo_04b", sizeof("s4_camo_04b"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 32, (BYTE*)&"s4_camo_04c", sizeof("s4_camo_04c"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 33, (BYTE*)&"s4_camo_04d", sizeof("s4_camo_04d"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 34, (BYTE*)&"s4_camo_04e", sizeof("s4_camo_04e"), var->hProc);
		utility::Write((BYTE*)ptr2 + 21 * 35, (BYTE*)&"s4_camo_04f", sizeof("s4_camo_04f"), var->hProc);
		utility::Write((BYTE*)ptr3, (BYTE*)&"camo_mp_t9tier1_01", sizeof("camo_mp_t9tier1_01"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28, (BYTE*)&"camo_mp_t9tier1_02", sizeof("camo_mp_t9tier1_02"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 2, (BYTE*)&"camo_mp_t9tier1_03", sizeof("camo_mp_t9tier1_03"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 3, (BYTE*)&"camo_mp_t9tier1_04", sizeof("camo_mp_t9tier1_04"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 4, (BYTE*)&"camo_mp_t9tier1_05", sizeof("camo_mp_t9tier1_05"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 5, (BYTE*)&"camo_mp_t9tier2_01", sizeof("camo_mp_t9tier2_01"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 6, (BYTE*)&"camo_mp_t9tier2_02", sizeof("camo_mp_t9tier2_02"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 7, (BYTE*)&"camo_mp_t9tier2_03", sizeof("camo_mp_t9tier2_03"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 8, (BYTE*)&"camo_mp_t9tier2_04", sizeof("camo_mp_t9tier2_04"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 9, (BYTE*)&"camo_mp_t9tier2_05", sizeof("camo_mp_t9tier2_05"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 10, (BYTE*)&"camo_mp_t9tier3_01", sizeof("camo_mp_t9tier3_01"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 11, (BYTE*)&"camo_mp_t9tier3_02", sizeof("camo_mp_t9tier3_02"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 12, (BYTE*)&"camo_mp_t9tier3_03", sizeof("camo_mp_t9tier3_03"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 13, (BYTE*)&"camo_mp_t9tier3_04", sizeof("camo_mp_t9tier3_04"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 14, (BYTE*)&"camo_mp_t9tier3_05", sizeof("camo_mp_t9tier3_05"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 15, (BYTE*)&"camo_mp_t9tier4_01", sizeof("camo_mp_t9tier4_01"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 16, (BYTE*)&"camo_mp_t9tier4_02", sizeof("camo_mp_t9tier4_02"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 17, (BYTE*)&"camo_mp_t9tier4_03", sizeof("camo_mp_t9tier4_03"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 18, (BYTE*)&"camo_mp_t9tier4_04", sizeof("camo_mp_t9tier4_04"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 19, (BYTE*)&"camo_mp_t9tier4_05", sizeof("camo_mp_t9tier4_05"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 20, (BYTE*)&"camo_mp_t9tier5_01", sizeof("camo_mp_t9tier5_01"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 21, (BYTE*)&"camo_mp_t9tier5_02", sizeof("camo_mp_t9tier5_02"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 22, (BYTE*)&"camo_mp_t9tier5_03", sizeof("camo_mp_t9tier5_03"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 23, (BYTE*)&"camo_mp_t9tier5_04", sizeof("camo_mp_t9tier5_04"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 24, (BYTE*)&"camo_mp_t9tier5_05", sizeof("camo_mp_t9tier5_05"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 25, (BYTE*)&"camo_mp_t9tier6_01", sizeof("camo_mp_t9tier6_01"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 26, (BYTE*)&"camo_mp_t9tier6_02", sizeof("camo_mp_t9tier6_02"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 27, (BYTE*)&"camo_mp_t9tier6_03", sizeof("camo_mp_t9tier6_03"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 28, (BYTE*)&"camo_mp_t9tier6_04", sizeof("camo_mp_t9tier6_04"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 29, (BYTE*)&"camo_mp_t9tier6_05", sizeof("camo_mp_t9tier6_05"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 30, (BYTE*)&"camo_mp_t9tier7_01", sizeof("camo_mp_t9tier7_01"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 31, (BYTE*)&"camo_mp_t9tier7_02", sizeof("camo_mp_t9tier7_02"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 32, (BYTE*)&"camo_mp_t9tier7_03", sizeof("camo_mp_t9tier7_03"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 33, (BYTE*)&"camo_mp_t9tier7_04", sizeof("camo_mp_t9tier7_04"), var->hProc);
		utility::Write((BYTE*)ptr3 + 28 * 34, (BYTE*)&"camo_mp_t9tier7_05", sizeof("camo_mp_t9tier7_05"), var->hProc);
		SendToastNotification("^1PUT AIO", "Locked Reverse Camos!", "ui_camo_11d");
		camoSwappedMW = false;
	}
}

void SetData(const char* path, DDLValue value) {
	DDLState state;
	DDLContext ddlcontext;

	__int64 ddldef = Com_DDL_LoadAsset(xorstr_("ddl/mp/blueprints.ddl"));
	if (Com_DDL_CreateContext((void*)(var->baseModule + var->Offest.notsure), 118784, ddldef, &ddlcontext, 0, 0)) {

		DDL_GetRootState(&state, ddldef);

		if (NavigateBlueprintDDL(&state, path)) {

			switch (DDL_GetType(&state)) {

			case 4:
				DDL_SetInt(&state, &ddlcontext, value.intValue);
				break;
			case 6:
				//DDL_SetFloat(&state, &ddlcontext, value.single);
				break;
			case 8:
				DDL_SetString(&state, &ddlcontext, value.stringPtr);
				break;
			case 10:
				DDL_SetEnum(&state, &ddlcontext, value.stringPtr);
				break;
			}

			DDL_SetEnum(&state, &ddlcontext, value.stringPtr);
		}
	}
}

void fseverything(const char* slot, const char* name, static int camo, static bool deletebp)
{
	const char* weapon_id_list[182]{
		"iw8_ar_kilo433",
		"iw8_ar_falima",
		"iw8_ar_mike4",
		"iw8_ar_falpha",
		"iw8_ar_asierra12",
		"iw8_ar_mcharlie",
		"iw8_ar_scharlie",
		"iw8_ar_akilo47",
		"iw8_ar_tango21",
		"iw8_ar_sierra552",
		"iw8_ar_galima",
		"iw8_ar_anovember94",
		"iw8_ar_valpha",
		"s4_ar_stango44",
		"s4_ar_asierra44",
		"s4_ar_balpha",
		"s4_ar_bromeopg",
		"s4_ar_chotel41",
		"s4_ar_fecho",
		"s4_ar_voscar",
		"s4_ar_kgolf40",
		"s4_ar_hyankee44",
		"s4_ar_promeo45",
		"s4_ar_valpha1952",
		"s4_ar_emike1",
		"iw8_ar_t9accurate",
		"iw8_ar_t9damage",
		"iw8_ar_t9standard",
		"iw8_ar_t9mobility",
		"iw8_ar_t9fasthandling",
		"iw8_ar_t9fastfire",
		"iw8_ar_t9slowhandling",
		"iw8_ar_t9slowfire",
		"iw8_ar_t9british",
		"iw8_ar_t9soviet",
		"iw8_ar_t9season6",
		//SMG
		"iw8_sm_augolf",
		"iw8_sm_papa90",
		"iw8_sm_mpapa5",
		"iw8_sm_uzulu",
		"iw8_sm_beta",
		"iw8_sm_mpapa7",
		"iw8_sm_smgolf45",
		"iw8_sm_victor",
		"iw8_sm_charlie9",
		"iw8_sm_secho",
		"s4_sm_mpapa40",
		"s4_sm_owhiskey",
		"s4_sm_ppapa41",
		"s4_sm_stango5",
		"s4_sm_thotel",
		"s4_sm_tyankee100",
		"s4_sm_aromeo43",
		"s4_sm_guniform45",
		"s4_sm_wecho43",
		"s4_sm_fromeo57",
		"s4_sm_salpha26",
		"iw8_sm_t9standard",
		"iw8_sm_t9handling",
		"iw8_sm_t9heavy",
		"iw8_sm_t9fastfire",
		"iw8_sm_t9burst",
		"iw8_sm_t9capacity",
		"iw8_sm_t9accurate",
		"iw8_sm_t9spray",
		"iw8_sm_t9nailgun",
		"iw8_sm_t9cqb",
		"iw8_sm_t9flechette",
		"iw8_sm_t9season6",
		//SHOTGUNS
		"iw8_sh_romeo870",
		"iw8_sh_dpapa12",
		"iw8_sh_charlie725",
		"iw8_sh_oscar12",
		"iw8_sh_mike26",
		"iw8_sh_aalpha12",
		"s4_sh_becho",
		"s4_sh_bromeo5",
		"s4_sh_lindia98",
		"s4_sh_mike97",
		"iw8_sh_t9fullauto",
		"iw8_sh_t9leveraction",
		"iw8_sh_t9pump",
		"iw8_sh_t9semiauto",
		//LMG
		"iw8_lm_pkilo",
		"iw8_lm_lima86",
		"iw8_lm_kilo121",
		"iw8_lm_mgolf34",
		"iw8_lm_mgolf36",
		"iw8_lm_mkilo3",
		"iw8_lm_sierrax",
		"iw8_lm_slima",
		"iw8_lm_t9accurate",
		"iw8_lm_t9slowfire",
		"iw8_lm_t9light",
		"iw8_lm_t9fastfire",
		"s4_mg_bromeo37",
		"s4_mg_dpapa27",
		"s4_mg_malpha7",
		"s4_mg_streak",
		"s4_mg_tyankee11",
		"s4_mg_mgolf42",
		//SNIPER
		"iw8_sn_mike14",
		"iw8_sn_sbeta",
		"iw8_sn_kilo98",
		"iw8_sn_crossbow",
		"iw8_sn_sksierra",
		"iw8_sn_romeo700",
		"iw8_sn_delta",
		"iw8_sn_hdromeo",
		"iw8_sn_alpha50",
		"iw8_sn_xmike109",
		"iw8_sn_t9quickscope",
		"iw8_sn_t9standard",
		"iw8_sn_t9powersemi",
		"iw8_sn_t9cannon",
		"iw8_sn_t9accurate",
		"s4_mr_moscar",
		"s4_mr_kalpha98",
		"s4_mr_aromeo99",
		"s4_mr_ptango41",
		"s4_mr_svictor40",
		"s4_mr_m1golf",
		"s4_mr_malpha1916",
		"s4_mr_gecho43",
		"iw8_sn_t9crossbow",
		//launchers
		"iw8_la_gromeo",
		"iw8_la_kgolf",
		"iw8_la_juliet",
		"iw8_la_rpapa7",
		"s4_la_m1bravo",
		"s4_la_mkilo1",
		"iw8_la_t9standard",
		"iw8_la_t9freefire",
		"iw8_la_t9launcher",
		//melee
		"iw8_me_riotshield",
		"iw8_knife",
		"iw8_me_akimboblunt",
		"iw8_me_akimboblades",
		"s4_me_knife",
		"s4_me_rindigo",
		"s4_me_icepick",
		"s4_me_sledgehammer",
		"s4_me_axe",
		"s4_me_katana",
		"s4_me_swordtitan",
		"iw8_me_t9wakizashi",
		"iw8_me_t9loadout",
		"iw8_me_t9machete",
		"iw8_me_t9etool",
		"iw8_me_t9ballisticknife",
		"iw8_me_t9bat",
		"iw8_me_t9mace",
		"iw8_me_t9cane",
		"iw8_me_t9sai",
		"iw8_me_t9battleaxe",
		"iw8_me_t9coldwar",
		"iw8_me_t9scythe",
		"iw8_me_t9sledgehammer",
		//pistols
		"iw8_pi_golf21",
		"iw8_pi_mike1911",
		"iw8_pi_cpapa",
		"iw8_pi_papa320",
		"iw8_pi_decho",
		"iw8_pi_mike9",
		"iw8_pi_mike",
		"s4_pi_luniform08",
		"s4_pi_malpha96",
		"s4_pi_mike1911",
		"s4_pi_ttango33",
		"s4_pi_wecho",
		"s4_pi_duniform",
		"iw8_pi_t9burst",
		"iw8_pi_t9semiauto",
		"iw8_pi_t9revolver",
		"iw8_pi_t9fullauto"
		"iw8_pi_t9pistolshot",
		//MISC
	   "iw8_sn_t9damagesemi",
		"s4_me_shovel",
		"s4_me_leiomano"
		"s4_me_champagne",
		"s4_me_barong",
		"iw8_sm_t9semiauto",
		"s4_ar_fnovember2000",
		"s4_mg_aalpha52"
		"s4_mg_sindia510"
	};
	const char* camo_id_list[22]{
		"camo_11a",
		"camo_11b",
		"camo_11c",
		"camo_11d",
		"camo_mp_t9mastery_gold",
		"camo_mp_t9mastery_diamond",
		"camo_mp_t9mastery_darkmatter",
		"camo_zm_t9mastery_gold",
		"camo_zm_t9mastery_diamond",
		"camo_zm_t9mastery_darkmatter",
		"camo_mp_t9tier5_05",
		"s4_camo_11a",
		"s4_camo_11b",
		"s4_camo_11c",
		"s4_camo_11a_zm",
		"s4_camo_11b_zm",
		"s4_camo_11c_zm",
		"mtl_s4_camo_gold_digital",
		"mtl_s4_camo_gold_woodland",
		"s4_camo_titanium_trials_01",
		"s4_camo_titanium_trials_02",
		"s4_camo_titanium_trials_03"

	};
	char buf_name[255];
	char buf_camo[255];

	char buf_weapon[255];
	char buf_selected_camo[255];
	char buf_gunsmith_name[255];
	DDLValue value;

	sprintf_s(buf_camo, xorstr_("%s"), camo_id_list[camo]);
	
	for (int i = 0; i < 182; i++) {
		sprintf_s(buf_name, xorstr_("%s%s"), xorstr_("000"), name, slot);

		if (deletebp == false)
		{
			value.stringPtr = buf_name;
			sprintf_s(buf_gunsmith_name, xorstr_("blueprints.%s.weaponSetup.%s.blueprintName"), weapon_id_list[i], slot);
			SetData(buf_gunsmith_name, value);

			value.stringPtr = buf_camo;
			sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.camo"), weapon_id_list[i], slot);
			SetData(buf_selected_camo, value);

			value.stringPtr = weapon_id_list[i];
			sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.weapon"), weapon_id_list[i], slot);
			SetData(buf_weapon, value);
		}
		else
		{
			value.stringPtr = "";
			sprintf_s(buf_gunsmith_name, xorstr_("blueprints.%s.weaponSetup.%s.blueprintName"), weapon_id_list[i], slot);
			SetData(buf_gunsmith_name, value);

			value.stringPtr = "";
			sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.camo"), weapon_id_list[i], slot);
			SetData(buf_selected_camo, value);

			value.stringPtr = "";
			sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.weapon"), weapon_id_list[i], slot);
			SetData(buf_weapon, value);
		}

		value.stringPtr = "none";
		sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.0.attachment"), weapon_id_list[i], slot);
		SetData(buf_selected_camo, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.1.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.2.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.3.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.4.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.5.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.6.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.7.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.8.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.9.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);
	}
}

void fsmw(const char* slot, const char* name, static int camo, static bool deletebp)
{
	const char* weapon_id_list[62]{
	   "iw8_ar_kilo433",
	   "iw8_ar_falima",
	   "iw8_ar_mike4",
	   "iw8_ar_falpha",
	   "iw8_ar_asierra12",
	   "iw8_ar_mcharlie",
	   "iw8_ar_scharlie",
	   "iw8_ar_akilo47",
	   "iw8_ar_tango21",
	   "iw8_ar_sierra552",
	   "iw8_ar_galima",
	   "iw8_ar_anovember94",
	   "iw8_ar_valpha",
	   //SMG
	   "iw8_sm_augolf",
	   "iw8_sm_papa90",
	   "iw8_sm_mpapa5",
	   "iw8_sm_uzulu",
	   "iw8_sm_beta",
	   "iw8_sm_mpapa7",
	   "iw8_sm_smgolf45",
	   "iw8_sm_victor",
	   "iw8_sm_charlie9",
	   "iw8_sm_secho",
	   //SHOTGUNS
	  "iw8_sh_romeo870",
	  "iw8_sh_dpapa12",
	  "iw8_sh_charlie725",
	  "iw8_sh_oscar12",
	  "iw8_sh_mike26",
	  "iw8_sh_aalpha12",
	  //LMG
	  "iw8_lm_pkilo",
	  "iw8_lm_lima86",
	  "iw8_lm_kilo121",
	  "iw8_lm_mgolf34",
	  "iw8_lm_mgolf36",
	  "iw8_lm_mkilo3",
	  "iw8_lm_sierrax",
	  "iw8_lm_slima",
	  //SNIPER
	  "iw8_sn_mike14",
	  "iw8_sn_sbeta",
	  "iw8_sn_kilo98",
	  "iw8_sn_crossbow",
	  "iw8_sn_sksierra",
	  "iw8_sn_romeo700",
	  "iw8_sn_delta",
	  "iw8_sn_hdromeo",
	  "iw8_sn_alpha50",
	  "iw8_sn_xmike109",
	  //launchers
	  "iw8_la_gromeo",
	  "iw8_la_kgolf",
	  "iw8_la_juliet",
	  "iw8_la_rpapa7",
	  //melee
	  "iw8_me_riotshield",
	  "iw8_knife",
	  "iw8_me_akimboblunt",
	  "iw8_me_akimboblades",
	  //pistols
	  "iw8_pi_golf21",
	  "iw8_pi_mike1911",
	  "iw8_pi_cpapa",
	  "iw8_pi_papa320",
	  "iw8_pi_decho",
	  "iw8_pi_mike9",
	  "iw8_pi_mike"
	};
	const char* camo_id_list[22]{
		"camo_11a",
		"camo_11b",
		"camo_11c",
		"camo_11d",
		"camo_mp_t9mastery_gold",
		"camo_mp_t9mastery_diamond",
		"camo_mp_t9mastery_darkmatter",
		"camo_zm_t9mastery_gold",
		"camo_zm_t9mastery_diamond",
		"camo_zm_t9mastery_darkmatter",
		"camo_mp_t9tier5_05",
		"s4_camo_11a",
		"s4_camo_11b",
		"s4_camo_11c",
		"s4_camo_11a_zm",
		"s4_camo_11b_zm",
		"s4_camo_11c_zm",
		"mtl_s4_camo_gold_digital",
		"mtl_s4_camo_gold_woodland",
		"s4_camo_titanium_trials_01",
		"s4_camo_titanium_trials_02",
		"s4_camo_titanium_trials_03"

	};
	char buf_name[255];
	char buf_camo[255];

	char buf_weapon[255];
	char buf_selected_camo[255];
	char buf_gunsmith_name[255];
	DDLValue value;

	sprintf_s(buf_camo, xorstr_("%s"), camo_id_list[camo]);

	for (int i = 0; i < 62; i++) {
		sprintf_s(buf_name, xorstr_("%s%s"), xorstr_("000"), name, slot);

		if (deletebp == false)
		{
			value.stringPtr = buf_name;
			sprintf_s(buf_gunsmith_name, xorstr_("blueprints.%s.weaponSetup.%s.blueprintName"), weapon_id_list[i], slot);
			SetData(buf_gunsmith_name, value);

			value.stringPtr = buf_camo;
			sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.camo"), weapon_id_list[i], slot);
			SetData(buf_selected_camo, value);

			value.stringPtr = weapon_id_list[i];
			sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.weapon"), weapon_id_list[i], slot);
			SetData(buf_weapon, value);
		}
		else
		{
			value.stringPtr = "";
			sprintf_s(buf_gunsmith_name, xorstr_("blueprints.%s.weaponSetup.%s.blueprintName"), weapon_id_list[i], slot);
			SetData(buf_gunsmith_name, value);

			value.stringPtr = "";
			sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.camo"), weapon_id_list[i], slot);
			SetData(buf_selected_camo, value);

			value.stringPtr = "";
			sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.weapon"), weapon_id_list[i], slot);
			SetData(buf_weapon, value);
		}

		value.stringPtr = "none";
		sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.0.attachment"), weapon_id_list[i], slot);
		SetData(buf_selected_camo, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.1.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.2.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.3.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.4.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.5.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.6.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.7.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.8.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.9.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);
	}
}

void fscw(const char* slot, const char* name, static int camo, static bool deletebp)
{
	const char* weapon_id_list[58]{
	   "iw8_ar_t9accurate",
	   "iw8_ar_t9damage",
	   "iw8_ar_t9standard",
	   "iw8_ar_t9mobility",
	   "iw8_ar_t9fasthandling",
	   "iw8_ar_t9fastfire",
	   "iw8_ar_t9slowhandling",
	   "iw8_ar_t9slowfire",
	   "iw8_ar_t9british",
	   "iw8_ar_t9soviet",
	   "iw8_ar_t9season6",
	   //SMG
	   "iw8_sm_t9standard",
	   "iw8_sm_t9handling",
	   "iw8_sm_t9heavy",
	   "iw8_sm_t9fastfire",
	   "iw8_sm_t9burst",
	   "iw8_sm_t9capacity",
	   "iw8_sm_t9accurate",
	   "iw8_sm_t9spray",
	   "iw8_sm_t9nailgun",
	   "iw8_sm_t9cqb",
	   "iw8_sm_t9flechette",
	   "iw8_sm_t9season6",
	   //SHOTGUNS
	   "iw8_sh_t9fullauto",
	   "iw8_sh_t9leveraction",
	   "iw8_sh_t9pump",
	   "iw8_sh_t9semiauto",
	   //LMG
	   "iw8_lm_t9accurate",
	   "iw8_lm_t9slowfire",
	   "iw8_lm_t9light",
	   "iw8_lm_t9fastfire",
	   //SNIPER
	   "iw8_sn_t9quickscope",
	   "iw8_sn_t9standard",
	   "iw8_sn_t9powersemi",
	   "iw8_sn_t9cannon",
	   "iw8_sn_t9accurate",
	   //launchers
	   "iw8_la_t9standard",
	   "iw8_la_t9freefire",
	   "iw8_la_t9launcher",
	   //melee
	   "iw8_me_t9wakizashi",
	   "iw8_me_t9loadout",
	   "iw8_me_t9machete",
	   "iw8_me_t9etool",
	   "iw8_me_t9ballisticknife",
	   "iw8_me_t9bat",
	   "iw8_me_t9mace",
	   "iw8_me_t9cane",
	   "iw8_me_t9sai",
	   "iw8_me_t9battleaxe",
	   "iw8_me_t9coldwar",
	   "iw8_me_t9scythe",
	   "iw8_me_t9sledgehammer",
	   //pistols
	  "iw8_pi_t9burst",
	   "iw8_pi_t9semiauto",
	   "iw8_pi_t9revolver",
	   "iw8_pi_t9fullauto"
	   "iw8_pi_t9pistolshot",
		//MISC
	   "iw8_sn_t9damagesemi",
	   "iw8_sm_t9semiauto"
	};
	const char* camo_id_list[22]{
		"camo_11a",
		"camo_11b",
		"camo_11c",
		"camo_11d",
		"camo_mp_t9mastery_gold",
		"camo_mp_t9mastery_diamond",
		"camo_mp_t9mastery_darkmatter",
		"camo_zm_t9mastery_gold",
		"camo_zm_t9mastery_diamond",
		"camo_zm_t9mastery_darkmatter",
		"camo_mp_t9tier5_05",
		"s4_camo_11a",
		"s4_camo_11b",
		"s4_camo_11c",
		"s4_camo_11a_zm",
		"s4_camo_11b_zm",
		"s4_camo_11c_zm",
		"mtl_s4_camo_gold_digital",
		"mtl_s4_camo_gold_woodland",
		"s4_camo_titanium_trials_01",
		"s4_camo_titanium_trials_02",
		"s4_camo_titanium_trials_03"

	};
	char buf_name[255];
	char buf_camo[255];

	char buf_weapon[255];
	char buf_selected_camo[255];
	char buf_gunsmith_name[255];
	DDLValue value;

	sprintf_s(buf_camo, xorstr_("%s"), camo_id_list[camo]);

	for (int i = 0; i < 58; i++) {
		sprintf_s(buf_name, xorstr_("%s%s"), xorstr_("000"), name, slot);

		if (deletebp == false)
		{
			value.stringPtr = buf_name;
			sprintf_s(buf_gunsmith_name, xorstr_("blueprints.%s.weaponSetup.%s.blueprintName"), weapon_id_list[i], slot);
			SetData(buf_gunsmith_name, value);

			value.stringPtr = buf_camo;
			sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.camo"), weapon_id_list[i], slot);
			SetData(buf_selected_camo, value);

			value.stringPtr = weapon_id_list[i];
			sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.weapon"), weapon_id_list[i], slot);
			SetData(buf_weapon, value);
		}
		else
		{
			value.stringPtr = "";
			sprintf_s(buf_gunsmith_name, xorstr_("blueprints.%s.weaponSetup.%s.blueprintName"), weapon_id_list[i], slot);
			SetData(buf_gunsmith_name, value);

			value.stringPtr = "";
			sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.camo"), weapon_id_list[i], slot);
			SetData(buf_selected_camo, value);

			value.stringPtr = "";
			sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.weapon"), weapon_id_list[i], slot);
			SetData(buf_weapon, value);
		}

		value.stringPtr = "none";
		sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.0.attachment"), weapon_id_list[i], slot);
		SetData(buf_selected_camo, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.1.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.2.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.3.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.4.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.5.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.6.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.7.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.8.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.9.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);
	}
}

void fsvg(const char* slot, const char* name, static int camo, static bool deletebp)
{
	const char* weapon_id_list[62]{
	   "s4_ar_stango44",
	   "s4_ar_asierra44",
	   "s4_ar_balpha",
	   "s4_ar_bromeopg",
	   "s4_ar_chotel41",
	   "s4_ar_fecho",
	   "s4_ar_voscar",
	   "s4_ar_kgolf40",
	   "s4_ar_hyankee44",
	   "s4_ar_promeo45",
	   "s4_ar_valpha1952",
	   "s4_ar_emike1",
	   //SMG
	   "s4_sm_mpapa40",
	   "s4_sm_owhiskey",
	   "s4_sm_ppapa41",
	   "s4_sm_stango5",
	   "s4_sm_thotel",
	   "s4_sm_tyankee100",
	   "s4_sm_aromeo43",
	   "s4_sm_guniform45",
	   "s4_sm_wecho43",
	   "s4_sm_fromeo57",
	   "s4_sm_salpha26",
	   //SHOTGUNS
	   "s4_sh_becho",
	   "s4_sh_bromeo5",
	   "s4_sh_lindia98",
	   "s4_sh_mike97",
	   //LMG
	   "s4_mg_bromeo37",
	   "s4_mg_dpapa27",
	   "s4_mg_malpha7",
	   "s4_mg_streak",
	   "s4_mg_tyankee11",
	   "s4_mg_mgolf42",
	   "s4_mg_aalpha52",
	   "s4_mg_sindia510",
	   //SNIPER
	   "s4_mr_moscar",
	   "s4_mr_kalpha98",
	   "s4_mr_aromeo99",
	   "s4_mr_ptango41",
	   "s4_mr_svictor40",
	   "s4_mr_m1golf",
	   "s4_mr_malpha1916",
	   "s4_mr_gecho43",

	   //launchers
	   "s4_la_m1bravo",
	   "s4_la_mkilo1",
	   //melee
	   "s4_me_knife",
	   "s4_me_rindigo",
	   "s4_me_icepick",
	   "s4_me_sledgehammer",
	   "s4_me_axe",
	   "s4_me_katana",
	   "s4_me_swordtitan",
	   //pistols
	   "s4_pi_luniform08",
	   "s4_pi_malpha96",
	   "s4_pi_mike1911",
	   "s4_pi_ttango33",
	   "s4_pi_wecho",
	   "s4_pi_duniform",
	   //MISC
	"s4_me_shovel",
	"s4_me_leiomano"
	"s4_me_champagne",
	"s4_me_barong",
	"s4_ar_fnovember2000"
	};
	const char* camo_id_list[22]{
		"camo_11a",
		"camo_11b",
		"camo_11c",
		"camo_11d",
		"camo_mp_t9mastery_gold",
		"camo_mp_t9mastery_diamond",
		"camo_mp_t9mastery_darkmatter",
		"camo_zm_t9mastery_gold",
		"camo_zm_t9mastery_diamond",
		"camo_zm_t9mastery_darkmatter",
		"camo_mp_t9tier5_05",
		"s4_camo_11a",
		"s4_camo_11b",
		"s4_camo_11c",
		"s4_camo_11a_zm",
		"s4_camo_11b_zm",
		"s4_camo_11c_zm",
		"mtl_s4_camo_gold_digital",
		"mtl_s4_camo_gold_woodland",
		"s4_camo_titanium_trials_01",
		"s4_camo_titanium_trials_02",
		"s4_camo_titanium_trials_03"

	};
	char buf_name[255];
	char buf_camo[255];

	char buf_weapon[255];
	char buf_selected_camo[255];
	char buf_gunsmith_name[255];
	DDLValue value;

	sprintf_s(buf_camo, xorstr_("%s"), camo_id_list[camo]);

	for (int i = 0; i < 62; i++) {
		sprintf_s(buf_name, xorstr_("%s%s"), xorstr_("000"), name, slot);

		if (deletebp == false)
		{
			value.stringPtr = buf_name;
			sprintf_s(buf_gunsmith_name, xorstr_("blueprints.%s.weaponSetup.%s.blueprintName"), weapon_id_list[i], slot);
			SetData(buf_gunsmith_name, value);

			value.stringPtr = buf_camo;
			sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.camo"), weapon_id_list[i], slot);
			SetData(buf_selected_camo, value);

			value.stringPtr = weapon_id_list[i];
			sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.weapon"), weapon_id_list[i], slot);
			SetData(buf_weapon, value);
		}
		else
		{
			value.stringPtr = "";
			sprintf_s(buf_gunsmith_name, xorstr_("blueprints.%s.weaponSetup.%s.blueprintName"), weapon_id_list[i], slot);
			SetData(buf_gunsmith_name, value);

			value.stringPtr = "";
			sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.camo"), weapon_id_list[i], slot);
			SetData(buf_selected_camo, value);

			value.stringPtr = "";
			sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.weapon"), weapon_id_list[i], slot);
			SetData(buf_weapon, value);
		}

		value.stringPtr = "none";
		sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.0.attachment"), weapon_id_list[i], slot);
		SetData(buf_selected_camo, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.1.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.2.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.3.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.4.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.5.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.6.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.7.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.8.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.9.attachment"), weapon_id_list[i], slot);
		SetData(buf_weapon, value);
	}
}

void fsattach(const char* gun, const char* slot, const char* attach1, const char* attach2, const char* attach3, const char* attach4, const char* attach5, const char* attach6, const char* attach7, const char* attach8, const char* attach9, const char* attach10, const char* name, static int camo, static bool deletebp)
{
	const char* camo_id_list[22]{
		"camo_11a",
		"camo_11b",
		"camo_11c",
		"camo_11d",
		"camo_mp_t9mastery_gold",
		"camo_mp_t9mastery_diamond",
		"camo_mp_t9mastery_darkmatter",
		"camo_zm_t9mastery_gold",
		"camo_zm_t9mastery_diamond",
		"camo_zm_t9mastery_darkmatter",
		"camo_mp_t9tier5_05",
		"s4_camo_11a",
		"s4_camo_11b",
		"s4_camo_11c",
		"s4_camo_11a_zm",
		"s4_camo_11b_zm",
		"s4_camo_11c_zm",
		"mtl_s4_camo_gold_digital",
		"mtl_s4_camo_gold_woodland",
		"s4_camo_titanium_trials_01",
		"s4_camo_titanium_trials_02",
		"s4_camo_titanium_trials_03"

	};
	char buf_name[255];
	char buf_camo[255];

	char buf_weapon[255];
	char buf_selected_camo[255];
	char buf_gunsmith_name[255];
	DDLValue value;

	sprintf_s(buf_camo, xorstr_("%s"), camo_id_list[camo]);

	sprintf_s(buf_name, xorstr_("%s%s"), xorstr_("000"), name, slot);

	if (deletebp == false)
	{
		value.stringPtr = buf_name;
		sprintf_s(buf_gunsmith_name, xorstr_("blueprints.%s.weaponSetup.%s.blueprintName"), gun, slot);
		SetData(buf_gunsmith_name, value);

		value.stringPtr = buf_camo;
		sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.camo"), gun, slot);
		SetData(buf_selected_camo, value);

		value.stringPtr = gun;
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.weapon"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = attach1;
		sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.0.attachment"), gun, slot);
		SetData(buf_selected_camo, value);

		value.stringPtr = attach2;
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.1.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = attach3;
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.2.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = attach4;
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.3.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = attach5;
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.4.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = attach6;
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.5.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = attach7;
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.6.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = attach8;
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.7.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = attach9;
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.8.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = attach10;
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.9.attachment"), gun, slot);
		SetData(buf_weapon, value);
	}
	else
	{
		value.stringPtr = "";
		sprintf_s(buf_gunsmith_name, xorstr_("blueprints.%s.weaponSetup.%s.blueprintName"), gun, slot);
		SetData(buf_gunsmith_name, value);

		value.stringPtr = "";
		sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.camo"), gun, slot);
		SetData(buf_selected_camo, value);

		value.stringPtr = "";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.weapon"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_selected_camo, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.0.attachment"), gun, slot);
		SetData(buf_selected_camo, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.1.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.2.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.3.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.4.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.5.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.6.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.7.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.8.attachment"), gun, slot);
		SetData(buf_weapon, value);

		value.stringPtr = "none";
		sprintf_s(buf_weapon, xorstr_("blueprints.%s.weaponSetup.%s.attachmentSetup.9.attachment"), gun, slot);
		SetData(buf_weapon, value);
	}
}

void fsattacheverything(const char* slot, bool deletebp, int game, const char* name, static int camo, static int attach)
{
	if (attach == 1)
	{
		fsattach("iw8_ar_kilo433", slot, "barlong", "stockno", "xmags", "fastreload", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_falima", slot, "barlong", "stockno", "reflexmini", "fastreload", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_mike4", slot, "barcust2", "pistolgrip02", "stockno", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_asierra12", slot, "barcust", "pistolgrip02", "stocks", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_mcharlie", slot, "barsil", "pistolgrip02", "stocks", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_scharlie", slot, "barlong", "pistolgrip02", "stockl", "xmagslrg", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_akilo47", slot, "barcust", "stockno", "pistolgrip02", "calsmg", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_tango21", slot, "silencer3", "reflex3", "pistolgrip02", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_sierra552", slot, "barlong", "stockno", "pistolgrip01", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_galima", slot, "barlong", "stockno", "pistolgrip02", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_anovember94", slot, "barlong", "stockno", "pistolgrip02", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_valpha", slot, "barcust", "stockcust", "pistolgrip02", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);

		//SMGS
		fsattach("iw8_sm_augolf", slot, "barshort", "pistolgrip02", "stocks", "calcust", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_papa90", slot, "barlong", "fastreload", "stockl", "gripcust", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_mpapa5", slot, "fastreload", "calcust", "pistolgrip02", "stockno", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_uzulu", slot, "calcust", "stockno", "reflexmini", "barcust2", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_beta", slot, "xmagslrg", "stockno", "pistolgrip02", "barlong", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_mpapa7", slot, "xmags", "stockno", "reflex3", "barlong", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_smgolf45", slot, "xmagslrg", "stocks", "pistolgrip02", "barlong", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_victor", slot, "drums", "stockno", "gripang", "barsil", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_charlie9", slot, "drums", "stockno", "gripang", "barsil", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_secho", slot, "barsil2", "stockno", "gripang", "drums", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);

		//shotguns
		fsattach("iw8_sh_romeo870", slot, "calcust", "silencer2", "barlong", "laserrange", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_dpapa12", slot, "barlong", "choke", "calcust", "laserrange", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_charlie725", slot, "barshort", "laserrange", "choke", "stockno", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_oscar12", slot, "barlong", "laserrange", "choke", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_mike26", slot, "barmid", "calcust", "silencer2", "stockno", "calcust", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_aalpha12", slot, "barcust", "laserrange", "silencer2", "xmagslrg", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);

		//LMG

		fsattach("iw8_lm_pkilo", slot, "barshort", "laserbalanced", "reflexmini", "stockno", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_lima86", slot, "stockcust", "barshort", "reflexmini", "laserbalanced", "gripang", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_kilo121", slot, "barshort", "laserbalanced", "reflexmini", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mgolf34", slot, "barshort", "laserbalanced", "reflexmini", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mgolf36", slot, "barshort", "calcust", "laserbalanced", "reflexmini", "stocks", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mkilo3", slot, "barshort", "laserbalanced", "reflexmini", "stockno", "smags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_sierrax", slot, "calcust", "barshort", "laserbalanced", "reflexmini", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_slima", slot, "smags", "barshort", "laserbalanced", "reflexmini", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);

		//SNIPER
		fsattach("iw8_sn_mike14", slot, "barshort", "pistolgrip03", "laserbalanced", "reflexmini", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_sbeta", slot, "barlong", "pistolgrip02", "stockh", "laserbalanced", "scope", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_kilo98", slot, "fastreload", "laserbalanced", "scope", "stockcust", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_crossbow", slot, "bolt2", "barlong", "laserbalanced", "reflexmini", "stocks", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_sksierra", slot, "barlong", "pistolgrip03", "xmags", "laserbalanced", "reflexmini", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_romeo700", slot, "boltl", "stockh", "laserbalanced", "scope", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_delta", slot, "stockcust", "fastreload", "barshort", "laserbalanced", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_hdromeo", slot, "stockh", "laserbalanced", "bipod", "fastreload", "none", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_alpha50", slot, "stocks", "barshort", "laserbalanced", "pistolgrip02", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_xmike109", slot, "stocks", "barshort", "laserbalanced", "pistolgrip02", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);

		//PISTOLS

		fsattach("iw8_pi_golf21", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike1911", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_cpapa", slot, "trigcust", "akimbo", "calcust2", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_papa320", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_decho", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike9", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike", slot, "trigcust", "silencer3", "drums", "barcust", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
	}
	else if (attach == 2)
	{
		fsattach("iw8_ar_kilo433", slot, "silencer3", "barlong", "acog2", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_falima", slot, "silencer3", "barlong", "acog2", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_mike4", slot, "silencer3", "barlong", "acog2", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_asierra12", slot, "barshort", "laserbalanced", "silencer2", "gripang", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_mcharlie", slot, "silencer3", "barlong", "acog2", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_scharlie", slot, "silencer3", "barlong", "acog2", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_akilo47", slot, "silencer3", "barlong", "acog2", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_tango21", slot, "silencer3", "barlong", "acog2", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_sierra552", slot, "silencer3", "barcust", "acog2", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_galima", slot, "silencer3", "barlong", "acog2", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_anovember94", slot, "silencer3", "barlong", "acog2", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_valpha", slot, "barcust", "laserbalanced", "stocks", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("iw8_ar_t9accurate", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_t9damage", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_t9standard", slot, "barlong", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_t9mobility", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_t9fasthandling", slot, "barcust", "stockcust", "gripvertpro", "silencer2", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_t9fastfire", slot, "barcust2", "silencer2", "stockcust", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_t9slowhandling", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_t9slowfire", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_t9british", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_t9soviet", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_t9season6", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("s4_ar_stango44", slot, "barlong", "silencer2", "vzscope2", "stockh", "calcust", "fastreload", "maxammo", "ammocust1", "gripangpro", "pistolgrip08", name, camo, deletebp);
		fsattach("s4_ar_asierra44", slot, "barmid", "muzzlecust", "vzscope2", "stockmarks", "calsmgdrums", "fastreload", "maxammo", "ammocust1", "gripangpro", "pistolgrip08", name, camo, deletebp);
		fsattach("s4_ar_balpha", slot, "barcust", "muzzlecust", "vzscope2", "stockskel", "calar", "gunperk_acrobatic", "maxammo", "ammocust1", "gripvert", "pistolgrip08", name, camo, deletebp);
		fsattach("s4_ar_bromeopg", slot, "barcust", "silencer2", "vzscope2", "stockl", "calsmgdrums", "fastreload", "gunperk_onhand", "ammocust1", "gripang", "pistolgrip03", name, camo, deletebp);
		fsattach("s4_ar_chotel41", slot, "barshort", "silencer2", "vzscope2", "stockcust", "calsmgdrums", "gunperk_brace", "maxammo", "ammocust1", "gripang", "pistolgrip08", name, camo, deletebp);
		fsattach("s4_ar_fecho", slot, "barlong", "silencer2", "vzscope2", "stockpad", "drums", "gunperk_tightgrip", "maxammo", "ammocust1", "gripang", "pistolgrip09", name, camo, deletebp);
		fsattach("s4_ar_voscar", slot, "barmid", "muzzlecust", "vzscope2", "stockl", "calcust", "gunperk_perfectionist", "gunperk_onhand", "bulsilent", "gripang", "pistolgrip10", name, camo, deletebp);
		fsattach("s4_ar_kgolf40", slot, "barcust2", "silencer2", "vzscope2", "stockcust", "xmags", "gunperk_brace", "maxammo", "ammocust1", "gripang", "pistolgrip10", name, camo, deletebp);
		fsattach("s4_ar_hyankee44", slot, "barmid", "silencer2", "vzscope2", "stockpad", "xmagslrg", "gunperk_tightgrip", "maxammo", "ammocust1", "gripang", "pistolgrip09", name, camo, deletebp);
		fsattach("s4_ar_promeo45", slot, "barextra", "muzzlecust", "reflexmini", "stockl", "calsmgdrums", "gunperk_perfectionist", "gunperk_onhand", "bulsilent", "gripang", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_ar_valpha1952", slot, "barsil", "silencer2", "vzscope2", "stockweight", "gripvert", "xmags", "ammocust1", "pistolgrip08", "gunperk_hardscope", "maxammo", name, camo, deletebp);
		fsattach("s4_ar_emike1", slot, "barcust2", "brake", "vzscope2", "stockh", "vertmags2", "gunperk_steady", "gunperk_onhand", "gripangpro", "pistolgrip08", "none", name, camo, deletebp);
		fsattach("s4_ar_fnovember2000", slot, "barlight", "muzzlecust", "reflexmini", "xmags", "stockl", "gunperk_brace", "maxammo", "bulsilent", "pistolgrip10", "laserbalanced", name, camo, deletebp);

		//SMGS
		fsattach("iw8_sm_augolf", slot, "silencer3", "laserbalanced", "stocks", "drums", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_papa90", slot, "silencer3", "laserbalanced", "stockh", "gripvertpro", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_mpapa5", slot, "barsil", "gripang", "xmags", "fastreload", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_uzulu", slot, "barcust2", "gripang", "calcust", "stocks", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_beta", slot, "silencer3", "barlong", "laserbalanced", "stockno", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_mpapa7", slot, "silencer3", "barlong", "laserbalanced", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_smgolf45", slot, "silencer3", "barmid", "laserbalanced", "stocks", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_victor", slot, "silencer3", "barsil", "gripvert", "drums", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_charlie9", slot, "stockno", "drums", "laserbalanced", "gripvertpro", "barsil", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_secho", slot, "pistolgrip02", "barsil2", "reflexmini", "gripang", "drums", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("iw8_sm_t9standard", slot, "stockcust", "silencer2", "gripang", "xmagslrg", "pistolgrip03", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9handling", slot, "silencer2", "reflexmini2", "gripang", "xmagslrg", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9heavy", slot, "silencer2", "stockcust", "gripang", "xmagslrg", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9fastfire", slot, "silencer2", "pistolgrip04", "gripang", "xmagslrg", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9burst", slot, "silencer", "stockcust", "gripang", "xmagslrg", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9capacity", slot, "silencer2", "laserrange", "gripang", "stockh", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9accurate", slot, "silencer2", "laserbalanced", "gripang", "barcust2", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9spray", slot, "silencer2", "stockcust", "gripang", "barcust2", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9cqb", slot, "silencer2", "stockcust", "pistolgrip04", "barcust2", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9flechette", slot, "silencer2", "stockh", "pistolgrip04", "barcust2", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9season6", slot, "silencer2", "stockcust", "barcust3", "reflexmini2", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("s4_sm_mpapa40", slot, "barmid", "muzzlecust", "reflexmini", "stockskel", "vertmags", "gunperk_momentum", "gunperk_quick", "gripcust2", "bulsilent", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_sm_owhiskey", slot, "muzzlecust", "reflexmini", "stockweight", "gripang", "calsmgdrums", "bulsilent", "pistolgrip07", "gunperk_steady", "gunperk_onhand", "none", name, camo, deletebp);
		fsattach("s4_sm_ppapa41", slot, "barsil2", "muzzlecust", "reflexmini", "stocks", "gripvert", "calsmgdrums", "bulsilent", "pistolgrip06", "gunperk_tightgrip", "gunperk_quick", name, camo, deletebp);
		fsattach("s4_sm_stango5", slot, "barcust", "muzzlecust", "reflexmini", "stockl", "gripcust2", "xmags", "bulsilent", "pistolgrip07", "gunperk_steady", "gunperk_quick", name, camo, deletebp);
		fsattach("s4_sm_thotel", slot, "barshortnoguard", "muzzlecust", "reflexmini", "stockskel", "calsmg", "gunperk_steady", "gunperk_quick", "bulsilent", "gripang", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_sm_tyankee100", slot, "barcust", "muzzlecust", "reflexmini", "stockl", "calar", "gunperk_vital", "gunperk_quick", "gripang", "bulsilent", "pistolgrip10", name, camo, deletebp);
		fsattach("s4_sm_aromeo43", slot, "barlong", "muzzlecust", "reflexmini", "stockskel", "xmagslrg", "gunperk_hardscope", "gunperk_quick", "bulsilent", "pistolgrip07", "none", name, camo, deletebp);
		fsattach("s4_sm_guniform45", slot, "barcust2", "muzzlecust", "reflexmini", "stockno", "calsmgdrums", "gripcust2", "gunperk_steady", "gunperk_quick", "pistolgrip10", "bulsilent", name, camo, deletebp);
		fsattach("s4_sm_wecho43", slot, "barcust", "muzzlecust", "reflexmini", "stockfold", "vertmags", "gunperk_acrobatic", "gunperk_quick", "bulsilent", "pistolgrip07", "gripcust2", name, camo, deletebp);
		fsattach("s4_sm_fromeo57", slot, "barlight", "muzzlecust", "reflexmini", "stockfold", "calsmgdrums", "gripcust2", "bulsilent", "pistolgrip07", "gunperk_momentum", "gunperk_quick", name, camo, deletebp);
		fsattach("s4_sm_salpha26", slot, "barcust", "muzzlecust", "reflexmini", "stockl", "calcust", "gripang", "gunperk_tightgrip", "gunperk_quick", "bulsilent", "pistolgrip07", name, camo, deletebp);


		//shotguns
		fsattach("iw8_sh_romeo870", slot, "calcust", "silencer2", "barlong", "laserrange", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_dpapa12", slot, "barlong", "choke", "calcust", "laserrange", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_charlie725", slot, "barshort", "laserrange", "choke", "stockno", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_oscar12", slot, "barlong", "laserrange", "choke", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_mike26", slot, "barmid", "calcust", "silencer2", "stockno", "calcust", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_aalpha12", slot, "barcust", "laserrange", "silencer2", "xmagslrg", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("iw8_sh_t9fullauto", slot, "barmid", "laserrange", "stocks", "xmags", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_t9leveraction", slot, "barcust2", "laserrange", "stockno", "xmags", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_t9pump", slot, "silencer2", "barmid", "laserrange", "xmagslrg", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_t9semiauto", slot, "silencer2", "barmid", "laserrange", "xmagslrg", "stocks", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("s4_sh_becho", slot, "barcust", "muzzlecust", "reflexmini", "stockno", "drums", "gripang", "gunperk_momentum", "gunperk_quick", "ammomod_incendiary", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_sh_bromeo5", slot, "barcust", "muzzlecust", "reflexmini", "stockno", "drums", "gripang", "gunperk_momentum", "gunperk_quick", "ammomod_incendiary", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_sh_lindia98", slot, "barcust", "muzzlecust", "reflexmini", "stockskel", "calcust2", "gripang", "gunperk_momentum", "gunperk_quick", "ammomod_incendiary", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_sh_mike97", slot, "barcust", "muzzlecust", "reflexmini", "stockskel", "calcust2", "gripang", "gunperk_momentum", "gunperk_quick", "ammomod_incendiary", "pistolgrip07", name, camo, deletebp);


		//LMG

		fsattach("iw8_lm_pkilo", slot, "barlong", "silencer3", "acog2", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_lima86", slot, "barlong", "silencer3", "acog2", "stockcust", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_kilo121", slot, "barlong", "silencer3", "acog2", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mgolf34", slot, "barlong", "silencer3", "acog2", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mgolf36", slot, "gripang", "silencer3", "acog2", "stockno", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mkilo3", slot, "holo", "silencer3", "barlong", "smags", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_sierrax", slot, "acog2", "silencer3", "barlong", "xmags", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_slima", slot, "acog2", "silencer3", "barlong", "xmags", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("iw8_lm_t9accurate", slot, "xmags", "acog2", "stockno", "barshort", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_t9slowfire", slot, "xmags", "acog2", "stockno", "barshort", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_t9light", slot, "xmags", "acog2", "stockno", "barshort", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_t9fastfire", slot, "xmags", "acog2", "stockno", "barshort", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("s4_mg_bromeo37", slot, "barcust", "silencer2", "vzscope2", "stockno", "xmagslrg", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_mg_dpapa27", slot, "barmid", "silencer2", "vzscope2", "stockl", "xmagslrg", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_mg_malpha7", slot, "barcust", "silencer2", "vzscope2", "stockskel", "xmags", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_mg_tyankee11", slot, "barmid", "silencer2", "vzscope2", "stockpad", "drums", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_mg_mgolf42", slot, "barmid", "silencer2", "vzscope2", "stockl", "smags", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_mg_aalpha52", slot, "barcust", "silencer2", "vzscope2", "stockl", "xmagslrg", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
		fsattach("s4_mg_sindia510", slot, "barcust", "silencer2", "vzscope2", "stockl", "calcust2", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);

		//SNIPER
		fsattach("iw8_sn_mike14", slot, "barlong", "silencer3", "laserbalanced", "scope", "pistolgrip03", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_sbeta", slot, "barlong", "silencer3", "laserbalanced", "scope", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_kilo98", slot, "barlong", "silencer3", "laserbalanced", "scope", "stockcust", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_crossbow", slot, "bolt2", "barlong", "laserbalanced", "reflexmini", "stocks", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_sksierra", slot, "barlong", "silencer3", "laserbalanced", "scope", "pistolgrip03", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_romeo700", slot, "scope", "barlong", "laserbalanced", "stockh", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_delta", slot, "scope", "barlong", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_hdromeo", slot, "scope", "barlong", "laserbalanced", "stockh", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_alpha50", slot, "scope", "barlong", "laserbalanced", "stocks", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_xmike109", slot, "scope", "barlong", "laserbalanced", "stocks", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("iw8_sn_t9quickscope", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_t9standard", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_t9powersemi", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_t9cannon", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_t9accurate", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("s4_mr_moscar", slot, "barextra", "silencer2", "stockcust", "gripcust", "calcust2", "ammocust1", "pistolgrip06", "gunperk_silentfocus", "gunperk_onhand", "none", name, camo, deletebp);
		fsattach("s4_mr_kalpha98", slot, "barextra", "silencer2", "stockno", "smags", "gunperk_fleet", "maxammo", "ammocust1", "pistolgrip01", "strap", "none", name, camo, deletebp);
		fsattach("s4_mr_aromeo99", slot, "barcust2", "silencer2", "stockno", "calsnpr", "gunperk_vital", "gunperk_onhand", "gripcust", "ammocust1", "pistolgrip06", "none", name, camo, deletebp);
		fsattach("s4_mr_ptango41", slot, "barmid", "silencer2", "vzscope2", "stockt", "drums", "gunperk_discard", "gunperk_onhand", "bipod", "fmj", "pistolgrip03", name, camo, deletebp);
		fsattach("s4_mr_svictor40", slot, "barlong", "silencer2", "vzscope2", "stockweight", "smags", "gunperk_vital", "gunperk_onhand", "gripangpro", "ammocust1", "pistolgrip03", name, camo, deletebp);
		fsattach("s4_mr_m1golf", slot, "barmid", "silencer2", "vzscope2", "stockcust", "xmags", "gunperk_hardscope", "gunperk_onhand", "gripvert", "ammocust1", "pistolgrip03", name, camo, deletebp);
		fsattach("s4_mr_malpha1916", slot, "barmid", "silencer2", "vzscope2", "stockmarks", "calar", "gunperk_quickscope", "gunperk_onhand", "gripvert", "ammocust1", "pistolgrip03", name, camo, deletebp);
		fsattach("s4_mr_gecho43", slot, "barlong", "silencer2", "vzscope2", "stockl", "xmags", "gunperk_quickscope", "gunperk_onhand", "gripcust", "ammocust1", "pistolgrip03", name, camo, deletebp);


		//PISTOLS

		fsattach("iw8_pi_golf21", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike1911", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_cpapa", slot, "trigcust", "akimbo", "calcust2", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_papa320", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_decho", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike9", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike", slot, "trigcust", "silencer3", "drums", "barcust", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("iw8_pi_t9burst", slot, "silencer2", "pistolgrip06", "xmagslrg", "barcust2", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_t9semiauto", slot, "silencer2", "pistolgrip06", "xmagslrg", "barcust2", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_t9revolver", slot, "silencer2", "pistolgrip06", "xmagslrg", "barcust2", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_t9fullauto", slot, "silencer2", "pistolgrip06", "xmagslrg", "barcust2", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_t9pistolshot", slot, "barmid", "akimbo", "xmags", "none", "none", "none", "none", "none", "none", "none", name, camo, deletebp);

		fsattach("s4_pi_luniform08", slot, "barlong", "silencer2", "reflexmini", "trigcust", "xmags", "gunperk_brace", "gunperk_onhand", "ammocust1", "pistolgrip03", "none", name, camo, deletebp);
		fsattach("s4_pi_malpha96", slot, "barcust", "silencer2", "reflexmini", "trigcust", "xmags", "gunperk_brace", "gunperk_onhand", "ammocust1", "pistolgrip03", "none", name, camo, deletebp);
		fsattach("s4_pi_mike1911", slot, "barcust2", "silencer2", "reflexmini", "trigcust", "drums", "gunperk_fleet", "gunperk_onhand", "ammocust1", "pistolgrip03", "none", name, camo, deletebp);
		fsattach("s4_pi_ttango33", slot, "barsil", "silencer2", "reflexmini", "trigcust", "drums", "gunperk_fleet", "gunperk_onhand", "ammocust1", "pistolgrip03", "none", name, camo, deletebp);
		fsattach("s4_pi_wecho", slot, "barsil", "silencer2", "reflexmini", "trigcust", "calsnpr", "gunperk_fleet", "gunperk_onhand", "ammocust1", "pistolgrip03", "none", name, camo, deletebp);


		//MISC
		fsattach("iw8_sn_t9damagesemi", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_t9semiauto", slot, "stockcust", "silencer2", "gripang", "xmagslrg", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
	}
}

void fsattachmw(const char* slot, bool deletebp, int game, const char* name, static int camo, static int attach)
{
	if (attach == 1)
	{
		fsattach("iw8_ar_kilo433", slot, "barlong", "stockno", "xmags", "fastreload", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_falima", slot, "barlong", "stockno", "reflexmini", "fastreload", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_mike4", slot, "barcust2", "pistolgrip02", "stockno", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_asierra12", slot, "barcust", "pistolgrip02", "stocks", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_mcharlie", slot, "barsil", "pistolgrip02", "stocks", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_scharlie", slot, "barlong", "pistolgrip02", "stockl", "xmagslrg", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_akilo47", slot, "barcust", "stockno", "pistolgrip02", "calsmg", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_tango21", slot, "silencer3", "reflex3", "pistolgrip02", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_sierra552", slot, "barlong", "stockno", "pistolgrip01", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_galima", slot, "barlong", "stockno", "pistolgrip02", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_anovember94", slot, "barlong", "stockno", "pistolgrip02", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_valpha", slot, "barcust", "stockcust", "pistolgrip02", "xmags", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);

		//SMGS
		fsattach("iw8_sm_augolf", slot, "barshort", "pistolgrip02", "stocks", "calcust", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_papa90", slot, "barlong", "fastreload", "stockl", "gripcust", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_mpapa5", slot, "fastreload", "calcust", "pistolgrip02", "stockno", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_uzulu", slot, "calcust", "stockno", "reflexmini", "barcust2", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_beta", slot, "xmagslrg", "stockno", "pistolgrip02", "barlong", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_mpapa7", slot, "xmags", "stockno", "reflex3", "barlong", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_smgolf45", slot, "xmagslrg", "stocks", "pistolgrip02", "barlong", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_victor", slot, "drums", "stockno", "gripang", "barsil", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_charlie9", slot, "drums", "stockno", "gripang", "barsil", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_secho", slot, "barsil2", "stockno", "gripang", "drums", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);

		//shotguns
		fsattach("iw8_sh_romeo870", slot, "calcust", "silencer2", "barlong", "laserrange", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_dpapa12", slot, "barlong", "choke", "calcust", "laserrange", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_charlie725", slot, "barshort", "laserrange", "choke", "stockno", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_oscar12", slot, "barlong", "laserrange", "choke", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_mike26", slot, "barmid", "calcust", "silencer2", "stockno", "calcust", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_aalpha12", slot, "barcust", "laserrange", "silencer2", "xmagslrg", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);

		//LMG

		fsattach("iw8_lm_pkilo", slot, "barshort", "laserbalanced", "reflexmini", "stockno", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_lima86", slot, "stockcust", "barshort", "reflexmini", "laserbalanced", "gripang", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_kilo121", slot, "barshort", "laserbalanced", "reflexmini", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mgolf34", slot, "barshort", "laserbalanced", "reflexmini", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mgolf36", slot, "barshort", "calcust", "laserbalanced", "reflexmini", "stocks", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mkilo3", slot, "barshort", "laserbalanced", "reflexmini", "stockno", "smags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_sierrax", slot, "calcust", "barshort", "laserbalanced", "reflexmini", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_slima", slot, "smags", "barshort", "laserbalanced", "reflexmini", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);

		//SNIPER
		fsattach("iw8_sn_mike14", slot, "barshort", "pistolgrip03", "laserbalanced", "reflexmini", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_sbeta", slot, "barlong", "pistolgrip02", "stockh", "laserbalanced", "scope", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_kilo98", slot, "fastreload", "laserbalanced", "scope", "stockcust", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_crossbow", slot, "bolt2", "barlong", "laserbalanced", "reflexmini", "stocks", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_sksierra", slot, "barlong", "pistolgrip03", "xmags", "laserbalanced", "reflexmini", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_romeo700", slot, "boltl", "stockh", "laserbalanced", "scope", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_delta", slot, "stockcust", "fastreload", "barshort", "laserbalanced", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_hdromeo", slot, "stockh", "laserbalanced", "bipod", "fastreload", "none", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_alpha50", slot, "stocks", "barshort", "laserbalanced", "pistolgrip02", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_xmike109", slot, "stocks", "barshort", "laserbalanced", "pistolgrip02", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);

		//PISTOLS

		fsattach("iw8_pi_golf21", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike1911", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_cpapa", slot, "trigcust", "akimbo", "calcust2", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_papa320", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_decho", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike9", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike", slot, "trigcust", "silencer3", "drums", "barcust", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
	}
	else if (attach == 2)
	{
		fsattach("iw8_ar_kilo433", slot, "silencer3", "barlong", "acog2", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_falima", slot, "silencer3", "barlong", "acog2", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_mike4", slot, "silencer3", "barlong", "acog2", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_asierra12", slot, "barshort", "laserbalanced", "silencer2", "gripang", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_mcharlie", slot, "silencer3", "barlong", "acog2", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_scharlie", slot, "silencer3", "barlong", "acog2", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_akilo47", slot, "silencer3", "barlong", "acog2", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_tango21", slot, "silencer3", "barlong", "acog2", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_sierra552", slot, "silencer3", "barcust", "acog2", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_galima", slot, "silencer3", "barlong", "acog2", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_anovember94", slot, "silencer3", "barlong", "acog2", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_ar_valpha", slot, "barcust", "laserbalanced", "stocks", "gripang", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);

		//SMGS
		fsattach("iw8_sm_augolf", slot, "silencer3", "laserbalanced", "stocks", "drums", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_papa90", slot, "silencer3", "laserbalanced", "stockh", "gripvertpro", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_mpapa5", slot, "barsil", "gripang", "xmags", "fastreload", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_uzulu", slot, "barcust2", "gripang", "calcust", "stocks", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_beta", slot, "silencer3", "barlong", "laserbalanced", "stockno", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_mpapa7", slot, "silencer3", "barlong", "laserbalanced", "gripang", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_smgolf45", slot, "silencer3", "barmid", "laserbalanced", "stocks", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_victor", slot, "silencer3", "barsil", "gripvert", "drums", "fastreload", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_charlie9", slot, "stockno", "drums", "laserbalanced", "gripvertpro", "barsil", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sm_secho", slot, "pistolgrip02", "barsil2", "reflexmini", "gripang", "drums", "none", "none", "none", "none", "none", name, camo, deletebp);


		//shotguns
		fsattach("iw8_sh_romeo870", slot, "calcust", "silencer2", "barlong", "laserrange", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_dpapa12", slot, "barlong", "choke", "calcust", "laserrange", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_charlie725", slot, "barshort", "laserrange", "choke", "stockno", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_oscar12", slot, "barlong", "laserrange", "choke", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_mike26", slot, "barmid", "calcust", "silencer2", "stockno", "calcust", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sh_aalpha12", slot, "barcust", "laserrange", "silencer2", "xmagslrg", "gripvert", "none", "none", "none", "none", "none", name, camo, deletebp);


		//LMG

		fsattach("iw8_lm_pkilo", slot, "barlong", "silencer3", "acog2", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_lima86", slot, "barlong", "silencer3", "acog2", "stockcust", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_kilo121", slot, "barlong", "silencer3", "acog2", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mgolf34", slot, "barlong", "silencer3", "acog2", "stockno", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mgolf36", slot, "gripang", "silencer3", "acog2", "stockno", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_mkilo3", slot, "holo", "silencer3", "barlong", "smags", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_sierrax", slot, "acog2", "silencer3", "barlong", "xmags", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_lm_slima", slot, "acog2", "silencer3", "barlong", "xmags", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);

		//SNIPER
		fsattach("iw8_sn_mike14", slot, "barlong", "silencer3", "laserbalanced", "scope", "pistolgrip03", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_sbeta", slot, "barlong", "silencer3", "laserbalanced", "scope", "pistolgrip02", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_kilo98", slot, "barlong", "silencer3", "laserbalanced", "scope", "stockcust", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_crossbow", slot, "bolt2", "barlong", "laserbalanced", "reflexmini", "stocks", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_sksierra", slot, "barlong", "silencer3", "laserbalanced", "scope", "pistolgrip03", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_romeo700", slot, "scope", "barlong", "laserbalanced", "stockh", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_delta", slot, "scope", "barlong", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_hdromeo", slot, "scope", "barlong", "laserbalanced", "stockh", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_alpha50", slot, "scope", "barlong", "laserbalanced", "stocks", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_sn_xmike109", slot, "scope", "barlong", "laserbalanced", "stocks", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);


		//PISTOLS

		fsattach("iw8_pi_golf21", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike1911", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_cpapa", slot, "trigcust", "akimbo", "calcust2", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_papa320", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_decho", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike9", slot, "trigcust", "akimbo", "xmagslrg", "barlong", "laserrange", "none", "none", "none", "none", "none", name, camo, deletebp);
		fsattach("iw8_pi_mike", slot, "trigcust", "silencer3", "drums", "barcust", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
	}
}

void fsattachcw(const char* slot, bool deletebp, int game, const char* name, static int camo, static int attach)
{
	fsattach("iw8_ar_t9accurate", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_ar_t9damage", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_ar_t9standard", slot, "barlong", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_ar_t9mobility", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_ar_t9fasthandling", slot, "barcust", "stockcust", "gripvertpro", "silencer2", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_ar_t9fastfire", slot, "barcust2", "silencer2", "stockcust", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_ar_t9slowhandling", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_ar_t9slowfire", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_ar_t9british", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_ar_t9soviet", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_ar_t9season6", slot, "barcust2", "silencer2", "acog2", "gripvertpro", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);

	fsattach("iw8_sm_t9standard", slot, "stockcust", "silencer2", "gripang", "xmagslrg", "pistolgrip03", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9handling", slot, "silencer2", "reflexmini2", "gripang", "xmagslrg", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9heavy", slot, "silencer2", "stockcust", "gripang", "xmagslrg", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9fastfire", slot, "silencer2", "pistolgrip04", "gripang", "xmagslrg", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9burst", slot, "silencer", "stockcust", "gripang", "xmagslrg", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9capacity", slot, "silencer2", "laserrange", "gripang", "stockh", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9accurate", slot, "silencer2", "laserbalanced", "gripang", "barcust2", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9spray", slot, "silencer2", "stockcust", "gripang", "barcust2", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9cqb", slot, "silencer2", "stockcust", "pistolgrip04", "barcust2", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9flechette", slot, "silencer2", "stockh", "pistolgrip04", "barcust2", "xmags", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9season6", slot, "silencer2", "stockcust", "barcust3", "reflexmini2", "xmagslrg", "none", "none", "none", "none", "none", name, camo, deletebp);

	fsattach("iw8_sh_t9fullauto", slot, "barmid", "laserrange", "stocks", "xmags", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sh_t9leveraction", slot, "barcust2", "laserrange", "stockno", "xmags", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sh_t9pump", slot, "silencer2", "barmid", "laserrange", "xmagslrg", "stockno", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sh_t9semiauto", slot, "silencer2", "barmid", "laserrange", "xmagslrg", "stocks", "none", "none", "none", "none", "none", name, camo, deletebp);

	fsattach("iw8_lm_t9accurate", slot, "xmags", "acog2", "stockno", "barshort", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_lm_t9slowfire", slot, "xmags", "acog2", "stockno", "barshort", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_lm_t9light", slot, "xmags", "acog2", "stockno", "barshort", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_lm_t9fastfire", slot, "xmags", "acog2", "stockno", "barshort", "silencer2", "none", "none", "none", "none", "none", name, camo, deletebp);

	fsattach("iw8_sn_t9quickscope", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sn_t9standard", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sn_t9powersemi", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sn_t9cannon", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sn_t9accurate", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);

	fsattach("iw8_pi_t9burst", slot, "silencer2", "pistolgrip06", "xmagslrg", "barcust2", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_pi_t9semiauto", slot, "silencer2", "pistolgrip06", "xmagslrg", "barcust2", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_pi_t9revolver", slot, "silencer2", "pistolgrip06", "xmagslrg", "barcust2", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_pi_t9fullauto", slot, "silencer2", "pistolgrip06", "xmagslrg", "barcust2", "laserbalanced", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_pi_t9pistolshot", slot, "barmid", "akimbo", "xmags", "none", "none", "none", "none", "none", "none", "none", name, camo, deletebp);

	//MISC
	fsattach("iw8_sn_t9damagesemi", slot, "pistolgrip06", "barcust2", "laserbalanced", "stockcust", "silencer3", "none", "none", "none", "none", "none", name, camo, deletebp);
	fsattach("iw8_sm_t9semiauto", slot, "stockcust", "silencer2", "gripang", "xmagslrg", "barcust2", "none", "none", "none", "none", "none", name, camo, deletebp);
}

void fsattachvg(const char* slot, bool deletebp, int game, const char* name, static int camo, static int attach)
{

	fsattach("s4_ar_stango44", slot, "barlong", "silencer2", "vzscope2", "stockh", "calcust", "fastreload", "maxammo", "ammocust1", "gripangpro", "pistolgrip08", name, camo, deletebp);
	fsattach("s4_ar_asierra44", slot, "barmid", "muzzlecust", "vzscope2", "stockmarks", "calsmgdrums", "fastreload", "maxammo", "ammocust1", "gripangpro", "pistolgrip08", name, camo, deletebp);
	fsattach("s4_ar_balpha", slot, "barcust", "muzzlecust", "vzscope2", "stockskel", "calar", "gunperk_acrobatic", "maxammo", "ammocust1", "gripvert", "pistolgrip08", name, camo, deletebp);
	fsattach("s4_ar_bromeopg", slot, "barcust", "silencer2", "vzscope2", "stockl", "calsmgdrums", "fastreload", "gunperk_onhand", "ammocust1", "gripang", "pistolgrip03", name, camo, deletebp);
	fsattach("s4_ar_chotel41", slot, "barshort", "silencer2", "vzscope2", "stockcust", "calsmgdrums", "gunperk_brace", "maxammo", "ammocust1", "gripang", "pistolgrip08", name, camo, deletebp);
	fsattach("s4_ar_fecho", slot, "barlong", "silencer2", "vzscope2", "stockpad", "drums", "gunperk_tightgrip", "maxammo", "ammocust1", "gripang", "pistolgrip09", name, camo, deletebp);
	fsattach("s4_ar_voscar", slot, "barmid", "muzzlecust", "vzscope2", "stockl", "calcust", "gunperk_perfectionist", "gunperk_onhand", "bulsilent", "gripang", "pistolgrip10", name, camo, deletebp);
	fsattach("s4_ar_kgolf40", slot, "barcust2", "silencer2", "vzscope2", "stockcust", "xmags", "gunperk_brace", "maxammo", "ammocust1", "gripang", "pistolgrip10", name, camo, deletebp);
	fsattach("s4_ar_hyankee44", slot, "barmid", "silencer2", "vzscope2", "stockpad", "xmagslrg", "gunperk_tightgrip", "maxammo", "ammocust1", "gripang", "pistolgrip09", name, camo, deletebp);
	fsattach("s4_ar_promeo45", slot, "barextra", "muzzlecust", "reflexmini", "stockl", "calsmgdrums", "gunperk_perfectionist", "gunperk_onhand", "bulsilent", "gripang", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_ar_valpha1952", slot, "barsil", "silencer2", "vzscope2", "stockweight", "gripvert", "xmags", "ammocust1", "pistolgrip08", "gunperk_hardscope", "maxammo", name, camo, deletebp);
	fsattach("s4_ar_emike1", slot, "barcust2", "brake", "vzscope2", "stockh", "vertmags2", "gunperk_steady", "gunperk_onhand", "gripangpro", "pistolgrip08", "none", name, camo, deletebp);
	fsattach("s4_ar_fnovember2000", slot, "barlight", "muzzlecust", "reflexmini", "xmags", "stockl", "gunperk_brace", "maxammo", "bulsilent", "pistolgrip10", "laserbalanced", name, camo, deletebp);

	fsattach("s4_sm_mpapa40", slot, "barmid", "muzzlecust", "reflexmini", "stockskel", "vertmags", "gunperk_momentum", "gunperk_quick", "gripcust2", "bulsilent", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_sm_owhiskey", slot, "muzzlecust", "reflexmini", "stockweight", "gripang", "calsmgdrums", "bulsilent", "pistolgrip07", "gunperk_steady", "gunperk_onhand", "none", name, camo, deletebp);
	fsattach("s4_sm_ppapa41", slot, "barsil2", "muzzlecust", "reflexmini", "stocks", "gripvert", "calsmgdrums", "bulsilent", "pistolgrip06", "gunperk_tightgrip", "gunperk_quick", name, camo, deletebp);
	fsattach("s4_sm_stango5", slot, "barcust", "muzzlecust", "reflexmini", "stockl", "gripcust2", "xmags", "bulsilent", "pistolgrip07", "gunperk_steady", "gunperk_quick", name, camo, deletebp);
	fsattach("s4_sm_thotel", slot, "barshortnoguard", "muzzlecust", "reflexmini", "stockskel", "calsmg", "gunperk_steady", "gunperk_quick", "bulsilent", "gripang", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_sm_tyankee100", slot, "barcust", "muzzlecust", "reflexmini", "stockl", "calar", "gunperk_vital", "gunperk_quick", "gripang", "bulsilent", "pistolgrip10", name, camo, deletebp);
	fsattach("s4_sm_aromeo43", slot, "barlong", "muzzlecust", "reflexmini", "stockskel", "xmagslrg", "gunperk_hardscope", "gunperk_quick", "bulsilent", "pistolgrip07", "none", name, camo, deletebp);
	fsattach("s4_sm_guniform45", slot, "barcust2", "muzzlecust", "reflexmini", "stockno", "calsmgdrums", "gripcust2", "gunperk_steady", "gunperk_quick", "pistolgrip10", "bulsilent", name, camo, deletebp);
	fsattach("s4_sm_wecho43", slot, "barcust", "muzzlecust", "reflexmini", "stockfold", "vertmags", "gunperk_acrobatic", "gunperk_quick", "bulsilent", "pistolgrip07", "gripcust2", name, camo, deletebp);
	fsattach("s4_sm_fromeo57", slot, "barlight", "muzzlecust", "reflexmini", "stockfold", "calsmgdrums", "gripcust2", "bulsilent", "pistolgrip07", "gunperk_momentum", "gunperk_quick", name, camo, deletebp);
	fsattach("s4_sm_salpha26", slot, "barcust", "muzzlecust", "reflexmini", "stockl", "calcust", "gripang", "gunperk_tightgrip", "gunperk_quick", "bulsilent", "pistolgrip07", name, camo, deletebp);

	fsattach("s4_sh_becho", slot, "barcust", "muzzlecust", "reflexmini", "stockno", "drums", "gripang", "gunperk_momentum", "gunperk_quick", "ammomod_incendiary", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_sh_bromeo5", slot, "barcust", "muzzlecust", "reflexmini", "stockno", "drums", "gripang", "gunperk_momentum", "gunperk_quick", "ammomod_incendiary", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_sh_lindia98", slot, "barcust", "muzzlecust", "reflexmini", "stockskel", "calcust2", "gripang", "gunperk_momentum", "gunperk_quick", "ammomod_incendiary", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_sh_mike97", slot, "barcust", "muzzlecust", "reflexmini", "stockskel", "calcust2", "gripang", "gunperk_momentum", "gunperk_quick", "ammomod_incendiary", "pistolgrip07", name, camo, deletebp);

	fsattach("s4_mg_bromeo37", slot, "barcust", "silencer2", "vzscope2", "stockno", "xmagslrg", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_mg_dpapa27", slot, "barmid", "silencer2", "vzscope2", "stockl", "xmagslrg", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_mg_malpha7", slot, "barcust", "silencer2", "vzscope2", "stockskel", "xmags", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_mg_tyankee11", slot, "barmid", "silencer2", "vzscope2", "stockpad", "drums", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_mg_mgolf42", slot, "barmid", "silencer2", "vzscope2", "stockl", "smags", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_mg_aalpha52", slot, "barcust", "silencer2", "vzscope2", "stockl", "xmagslrg", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);
	fsattach("s4_mg_sindia510", slot, "barcust", "silencer2", "vzscope2", "stockl", "calcust2", "gunperk_tightgrip", "gunperk_quick", "gripang", "ammocust1", "pistolgrip07", name, camo, deletebp);

	fsattach("s4_mr_moscar", slot, "barextra", "silencer2", "stockcust", "gripcust", "calcust2", "ammocust1", "pistolgrip06", "gunperk_silentfocus", "gunperk_onhand", "none", name, camo, deletebp);
	fsattach("s4_mr_kalpha98", slot, "barextra", "silencer2", "stockno", "smags", "gunperk_fleet", "maxammo", "ammocust1", "pistolgrip01", "strap", "none", name, camo, deletebp);
	fsattach("s4_mr_aromeo99", slot, "barcust2", "silencer2", "stockno", "calsnpr", "gunperk_vital", "gunperk_onhand", "gripcust", "ammocust1", "pistolgrip06", "none", name, camo, deletebp);
	fsattach("s4_mr_ptango41", slot, "barmid", "silencer2", "vzscope2", "stockt", "drums", "gunperk_discard", "gunperk_onhand", "bipod", "fmj", "pistolgrip03", name, camo, deletebp);
	fsattach("s4_mr_svictor40", slot, "barlong", "silencer2", "vzscope2", "stockweight", "smags", "gunperk_vital", "gunperk_onhand", "gripangpro", "ammocust1", "pistolgrip03", name, camo, deletebp);
	fsattach("s4_mr_m1golf", slot, "barmid", "silencer2", "vzscope2", "stockcust", "xmags", "gunperk_hardscope", "gunperk_onhand", "gripvert", "ammocust1", "pistolgrip03", name, camo, deletebp);
	fsattach("s4_mr_malpha1916", slot, "barmid", "silencer2", "vzscope2", "stockmarks", "calar", "gunperk_quickscope", "gunperk_onhand", "gripvert", "ammocust1", "pistolgrip03", name, camo, deletebp);
	fsattach("s4_mr_gecho43", slot, "barlong", "silencer2", "vzscope2", "stockl", "xmags", "gunperk_quickscope", "gunperk_onhand", "gripcust", "ammocust1", "pistolgrip03", name, camo, deletebp);

	fsattach("s4_pi_luniform08", slot, "barlong", "silencer2", "reflexmini", "trigcust", "xmags", "gunperk_brace", "gunperk_onhand", "ammocust1", "pistolgrip03", "none", name, camo, deletebp);
	fsattach("s4_pi_malpha96", slot, "barcust", "silencer2", "reflexmini", "trigcust", "xmags", "gunperk_brace", "gunperk_onhand", "ammocust1", "pistolgrip03", "none", name, camo, deletebp);
	fsattach("s4_pi_mike1911", slot, "barcust2", "silencer2", "reflexmini", "trigcust", "drums", "gunperk_fleet", "gunperk_onhand", "ammocust1", "pistolgrip03", "none", name, camo, deletebp);
	fsattach("s4_pi_ttango33", slot, "barsil", "silencer2", "reflexmini", "trigcust", "drums", "gunperk_fleet", "gunperk_onhand", "ammocust1", "pistolgrip03", "none", name, camo, deletebp);
	fsattach("s4_pi_wecho", slot, "barsil", "silencer2", "reflexmini", "trigcust", "calsnpr", "gunperk_fleet", "gunperk_onhand", "ammocust1", "pistolgrip03", "none", name, camo, deletebp);
}

void forceSave(const char* slot, bool deletebp, int game, const char* name, static int camo, static int attach)
{
	if (attach == 0)
	{
		if (game == 0)
		{
			fseverything(slot, name, camo, deletebp);
		}
		else if (game == 1)
		{
			fsmw(slot, name, camo, deletebp);
		}
		else if (game == 2)
		{
			fscw(slot, name, camo, deletebp);
		}
		else if (game == 3)
		{
			fsvg(slot, name, camo, deletebp);
		}
	}
	else
	{
		if (game == 0)
		{
			fsattacheverything(slot, deletebp, game, name, camo, attach);
		}
		else if (game == 1)
		{
			fsattachmw(slot, deletebp, game, name, camo, attach);
		}
		else if (game == 2)
		{
			fsattachcw(slot, deletebp, game, name, camo, attach);
		}
		else if (game == 3)
		{
			fsattachvg(slot, deletebp, game, name, camo, attach);
		}
	}
}

void Cbuf_AddText(const char* fmt, ...)
{
	char cmd[512]{};
	char post[512]{};

	va_list ap;
	va_start(ap, fmt);
	vsprintf_s(cmd, fmt, ap);
	va_end(ap);
	//Log_(cmd);
	memcpy((BYTE*)post, (BYTE*)(var->baseModule + var->Offest.xpartyOffset), 512);
	strcpy((char*)(var->baseModule + var->Offest.xpartyOffset), cmd);
	reinterpret_cast<void(*)(void*)>(var->baseModule + var->Offest.CbufOffset)(nullptr);
	memcpy((BYTE*)(var->baseModule + var->Offest.xpartyOffset), (BYTE*)post, 512);
}

//uintptr_t t_clientinfo_ptr;
//uintptr_t t_clientbase_ptr;
//uintptr_t c_infoptr_ptr_offset;
//
//uint64_t get_clientinfo_ptr()
//{
//	if (var->gcached.cached_character_ptr)
//		return var->gcached.cached_character_ptr;
//
//	auto addr = (t_clientinfo_ptr)(var->baseModule + var->Offest.clientinfo_ptr);
//
//	if (!c_infoptr_ptr_offset)
//		c_infoptr_ptr_offset = spoof_call((void*)(var->Offest.rbx_jmp), addr, 300);
//
//	if (!c_infoptr_ptr_offset)
//	{
//		c_infoptr_ptr_offset = 0;
//		return 0;
//	}
//
//	var->gcached.cached_character_ptr = spoof_call((void*)(var->Offest.rbx_jmp), addr, 0) - c_infoptr_ptr_offset;
//
//	if (!var->gcached.cached_character_ptr)
//	{
//		var->gcached.cached_character_ptr = 0;
//		return 0;
//	}
//	//LOGS_ADDR(var->gcached.cached_character_ptr);
//	return var->gcached.cached_character_ptr;
//
//}
//
//uint64_t get_clientbase_ptr(int entityNum)
//{
//	if (var->gcached.cached_base_ptr)
//		return var->gcached.cached_base_ptr;
//
//	auto addr = (t_clientbase_ptr)(var->baseModule + var->Offest.clientbase_ptr);
//	uint64_t ptr = spoof_call((void*)(var->Offest.rbx_jmp), addr, 0, 0);
//	//LOGS_ADDR(ptr);
//	if (ptr != 0)
//		return ptr; //+ (entityNum * DW->goffsets.c_size));
//	else
//		return 0;
//}

std::string keyIntToString(int key)
{
	if (key == VK_RSHIFT) {
		return "RShift";
	}
	if (key == VK_LSHIFT) {
		return "LShift";
	}
	if (key == VK_BACK) {
		return "Backspace";

	}
	if (key == VK_TAB) {
		return "Tab";

	}
	if (key == VK_CLEAR) {
		return "Clear";

	}
	if (key == VK_RETURN) {
		return "Enter";

	}
	if (key == VK_PAUSE) {
		return "Pause";

	}
	if (key == VK_CAPITAL) {
		return "Caps Lock";

	}
	if (key == VK_ESCAPE) {
		return "ESC";

	}
	if (key == VK_SPACE) {
		return "Spacebar";

	}
	if (key == VK_PRIOR) {
		return "Page Up";

	}
	if (key == VK_NEXT) {
		return "Page Down";

	}
	if (key == VK_END) {
		return "END";

	}
	if (key == VK_HOME) {
		return "HOME";

	}
	if (key == VK_LEFT) {
		return "Left";

	}
	if (key == VK_UP) {
		return "Up";

	}
	if (key == VK_RIGHT) {
		return "Right";

	}
	if (key == VK_DOWN) {
		return "Down";

	}
	if (key == VK_SELECT) {
		return "Select";

	}
	if (key == VK_PRINT) {
		return "Print";

	}
	if (key == VK_EXECUTE) {
		return "Execute";

	}
	if (key == VK_SNAPSHOT) {
		return "Print Screen";

	}
	if (key == VK_INSERT) {
		return "INS";

	}
	if (key == VK_DELETE) {
		return "DEL";

	}
	if (key == VK_HELP) {
		return "HELP";

	}
	if (key == 0x30) {
		return "0";

	}
	if (key == 0x31) {
		return "1";

	}
	if (key == 0x32) {
		return "2";

	}
	if (key == 0x33) {
		return "3";

	}
	if (key == 0x34) {
		return "4";

	}
	if (key == 0x35) {
		return "5";

	}
	if (key == 0x36) {
		return "6";

	}
	if (key == 0x37) {
		return "7";

	}
	if (key == 0x38) {
		return "8";

	}
	if (key == 0x39) {
		return "9";

	}
	if (key == 0x41) {
		return "A";

	}
	if (key == 0x42) {
		return "B";

	}
	if (key == 0x43) {
		return "C";

	}
	if (key == 0x44) {
		return "D";

	}
	if (key == 0x45) {
		return "E";

	}
	if (key == 0x46) {
		return "F";

	}
	if (key == 0x47) {
		return "G";

	}
	if (key == 0x48) {
		return "H";

	}
	if (key == 0x49) {
		return "I";

	}
	if (key == 0x4A) {
		return "J";

	}
	if (key == 0x4B) {
		return "K";

	}
	if (key == 0x4C) {
		return "L";

	}
	if (key == 0x4D) {
		return "M";

	}
	if (key == 0x4E) {
		return "N";

	}
	if (key == 0x4F) {
		return "O";

	}
	if (key == 0x50) {
		return "P";

	}
	if (key == 0x51) {
		return "Q";

	}
	if (key == 0x52) {
		return "R";

	}
	if (key == 0x53) {
		return "S";

	}
	if (key == 0x54) {
		return "T";

	}
	if (key == 0x55) {
		return "U";

	}
	if (key == 0x56) {
		return "V";

	}
	if (key == 0x57) {
		return "W";

	}
	if (key == 0x58) {
		return "X";

	}
	if (key == 0x59) {
		return "Y";

	}
	if (key == 0x5A) {
		return "Z";

	}
	if (key == VK_LWIN) {
		return "Left Win";

	}
	if (key == VK_RWIN) {
		return "Right Win";

	}
	if (key == VK_APPS) {
		return "Apps";

	}
	if (key == VK_SLEEP) {
		return "Sleep";

	}
	if (key == VK_NUMPAD0) {
		return "Numpad 0";

	}
	if (key == VK_NUMPAD1) {
		return "Numpad 1";

	}
	if (key == VK_NUMPAD2) {
		return "Numpad 2";

	}
	if (key == VK_NUMPAD3) {
		return "Numpad 3";

	}
	if (key == VK_NUMPAD4) {
		return "Numpad 4";

	}
	if (key == VK_NUMPAD5) {
		return "Numpad 5";

	}
	if (key == VK_NUMPAD6) {
		return "Numpad 6";

	}
	if (key == VK_NUMPAD7) {
		return "Numpad 7";

	}
	if (key == VK_NUMPAD8) {
		return "Numpad 8";

	}
	if (key == VK_NUMPAD9) {
		return "Numpad 9";

	}
	if (key == VK_MULTIPLY) {
		return "Multiply";

	}
	if (key == VK_ADD) {
		return "Plus";

	}
	if (key == VK_SEPARATOR) {
		return "Separator";

	}
	if (key == VK_SUBTRACT) {
		return "Minus";

	}
	if (key == VK_DECIMAL) {
		return "Decimal";

	}
	if (key == VK_DIVIDE) {
		return "Divide";

	}
	if (key == VK_F1) {
		return "F1";

	}
	if (key == VK_F2) {
		return "F2";

	}
	if (key == VK_F3) {
		return "F3";

	}
	if (key == VK_F4) {
		return "F4";

	}
	if (key == VK_F5) {
		return "F5";

	}
	if (key == VK_F6) {
		return "F6";

	}
	if (key == VK_F7) {
		return "F7";

	}
	if (key == VK_F8) {
		return "F8";

	}
	if (key == VK_F9) {
		return "F9";

	}
	if (key == VK_F10) {
		return "F10";

	}
	if (key == VK_F11) {
		return "F11";

	}
	if (key == VK_F12) {
		return "F12";

	}
	if (key == VK_F13) {
		return "F13";

	}
	if (key == VK_F14) {
		return "F14";

	}
	if (key == VK_F15) {
		return "F15";

	}
	if (key == VK_F16) {
		return "F16";

	}
	if (key == VK_F17) {
		return "F17";

	}
	if (key == VK_F18) {
		return "F18";

	}
	if (key == VK_F19) {
		return "F19";

	}
	if (key == VK_F20) {
		return "F20";

	}
	if (key == VK_F21) {
		return "F21";

	}
	if (key == VK_F22) {
		return "F22";

	}
	if (key == VK_F23) {
		return "F23";

	}
	if (key == VK_F24) {
		return "F24";

	}
	if (key == VK_NUMLOCK) {
		return "Num Lock";

	}
	if (key == VK_SCROLL) {
		return "Scroll Lock";

	}
	if (key == VK_LCONTROL) {
		return "Left CTRL";

	}
	if (key == VK_RCONTROL) {
		return "Right CTRL";

	}
	if (key == VK_LMENU) {
		return "Left MENU";

	}
	if (key == VK_RMENU) {
		return "Right MENU";

	}
	if (key == VK_OEM_1) {
		return "Semi-Colon";

	}
	if (key == VK_OEM_2) {
		return "Forward Slash";

	}
	if (key == VK_OEM_3) {
		return "GRAVE";

	}
	if (key == VK_OEM_4) {
		return "Left Bracket";

	}
	if (key == VK_OEM_5) {
		return "Back Slash";

	}
	if (key == VK_OEM_6) {
		return "Right Bracket";

	}
	if (key == VK_OEM_7) {
		return "Apostrophe";
	}
	if (key == VK_OEM_COMMA) {
		return "Comma";
	}
	if (key == VK_OEM_PERIOD) {
		return "Period";
	}
	if (key == VK_OEM_MINUS) {
		return "Dash";
	}
	if (key == VK_OEM_PLUS) {
		return "Equals";
	}
}

void isKeyPressed(int* key, bool* clicked, std::string* nameKey)
{
	if (GetAsyncKeyState(VK_RSHIFT) & 0x8000) {
		*key = VK_RSHIFT;
		*nameKey = "RShift";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
		*key = VK_LSHIFT;
		*nameKey = "LShift";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_BACK) & 0x8000) {
		*key = VK_BACK;
		*nameKey = "Backspace";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_TAB) & 0x8000) {
		*key = VK_TAB;
		*nameKey = "Tab";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_CLEAR) & 0x8000) {
		*key = VK_CLEAR;
		*nameKey = "Clear";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
		*key = VK_RETURN;
		*nameKey = "Enter";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_PAUSE) & 0x8000) {
		*key = VK_PAUSE;
		*nameKey = "Pause";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_CAPITAL) & 0x8000) {
		*key = VK_CAPITAL;
		*nameKey = "Caps Lock";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
		*key = VK_ESCAPE;
		*nameKey = "ESC";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		*key = VK_SPACE;
		*nameKey = "Spacebar";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_PRIOR) & 0x8000) {
		*key = VK_PRIOR;
		*nameKey = "Page Up";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NEXT) & 0x8000) {
		*key = VK_NEXT;
		*nameKey = "Page Down";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_END) & 0x8000) {
		*key = VK_END;
		*nameKey = "END";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_HOME) & 0x8000) {
		*key = VK_HOME;
		*nameKey = "HOME";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		*key = VK_LEFT;
		*nameKey = "Left";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) {
		*key = VK_UP;
		*nameKey = "Up";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		*key = VK_RIGHT;
		*nameKey = "Right";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
		*key = VK_DOWN;
		*nameKey = "Down";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_SELECT) & 0x8000) {
		*key = VK_SELECT;
		*nameKey = "Select";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_PRINT) & 0x8000) {
		*key = VK_PRINT;
		*nameKey = "Print";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_EXECUTE) & 0x8000) {
		*key = VK_EXECUTE;
		*nameKey = "Execute";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_SNAPSHOT) & 0x8000) {
		*key = VK_SNAPSHOT;
		*nameKey = "Print Screen";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_INSERT) & 0x8000) {
		*key = VK_INSERT;
		*nameKey = "INS";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
		*key = VK_DELETE;
		*nameKey = "DEL";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_HELP) & 0x8000) {
		*key = VK_HELP;
		*nameKey = "HELP";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x30) & 0x8000) {
		*key = 0x30;
		*nameKey = "0";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x31) & 0x8000) {
		*key = 0x31;
		*nameKey = "1";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x32) & 0x8000) {
		*key = 0x32;
		*nameKey = "2";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x33) & 0x8000) {
		*key = 0x33;
		*nameKey = "3";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x34) & 0x8000) {
		*key = 0x34;
		*nameKey = "4";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x35) & 0x8000) {
		*key = 0x35;
		*nameKey = "5";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x36) & 0x8000) {
		*key = 0x36;
		*nameKey = "6";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x37) & 0x8000) {
		*key = 0x37;
		*nameKey = "7";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x38) & 0x8000) {
		*key = 0x38;
		*nameKey = "8";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x39) & 0x8000) {
		*key = 0x39;
		*nameKey = "9";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x41) & 0x8000) {
		*key = 0x41;
		*nameKey = "A";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x42) & 0x8000) {
		*key = 0x42;
		*nameKey = "B";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x43) & 0x8000) {
		*key = 0x43;
		*nameKey = "C";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x44) & 0x8000) {
		*key = 0x44;
		*nameKey = "D";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x45) & 0x8000) {
		*key = 0x45;
		*nameKey = "E";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x46) & 0x8000) {
		*key = 0x46;
		*nameKey = "F";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x47) & 0x8000) {
		*key = 0x47;
		*nameKey = "G";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x48) & 0x8000) {
		*key = 0x48;
		*nameKey = "H";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x49) & 0x8000) {
		*key = 0x49;
		*nameKey = "I";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x4A) & 0x8000) {
		*key = 0x4A;
		*nameKey = "J";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x4B) & 0x8000) {
		*key = 0x4B;
		*nameKey = "K";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x4C) & 0x8000) {
		*key = 0x4C;
		*nameKey = "L";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x4D) & 0x8000) {
		*key = 0x4D;
		*nameKey = "M";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x4E) & 0x8000) {
		*key = 0x4E;
		*nameKey = "N";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x4F) & 0x8000) {
		*key = 0x4F;
		*nameKey = "O";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x50) & 0x8000) {
		*key = 0x50;
		*nameKey = "P";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x51) & 0x8000) {
		*key = 0x51;
		*nameKey = "Q";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x52) & 0x8000) {
		*key = 0x52;
		*nameKey = "R";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x53) & 0x8000) {
		*key = 0x53;
		*nameKey = "S";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x54) & 0x8000) {
		*key = 0x54;
		*nameKey = "T";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x55) & 0x8000) {
		*key = 0x55;
		*nameKey = "U";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x56) & 0x8000) {
		*key = 0x56;
		*nameKey = "V";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x57) & 0x8000) {
		*key = 0x57;
		*nameKey = "W";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x58) & 0x8000) {
		*key = 0x58;
		*nameKey = "X";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x59) & 0x8000) {
		*key = 0x59;
		*nameKey = "Y";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(0x5A) & 0x8000) {
		*key = 0x5A;
		*nameKey = "Z";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_LWIN) & 0x8000) {
		*key = VK_LWIN;
		*nameKey = "Left Win";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_RWIN) & 0x8000) {
		*key = VK_RWIN;
		*nameKey = "Right Win";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_APPS) & 0x8000) {
		*key = VK_APPS;
		*nameKey = "Apps";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_SLEEP) & 0x8000) {
		*key = VK_SLEEP;
		*nameKey = "Sleep";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMPAD0) & 0x8000) {
		*key = VK_NUMPAD0;
		*nameKey = "Numpad 0";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000) {
		*key = VK_NUMPAD1;
		*nameKey = "Numpad 1";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000) {
		*key = VK_NUMPAD2;
		*nameKey = "Numpad 2";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000) {
		*key = VK_NUMPAD3;
		*nameKey = "Numpad 3";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000) {
		*key = VK_NUMPAD4;
		*nameKey = "Numpad 4";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMPAD5) & 0x8000) {
		*key = VK_NUMPAD5;
		*nameKey = "Numpad 5";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMPAD6) & 0x8000) {
		*key = VK_NUMPAD6;
		*nameKey = "Numpad 6";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMPAD7) & 0x8000) {
		*key = VK_NUMPAD7;
		*nameKey = "Numpad 7";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMPAD8) & 0x8000) {
		*key = VK_NUMPAD8;
		*nameKey = "Numpad 8";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMPAD9) & 0x8000) {
		*key = VK_NUMPAD9;
		*nameKey = "Numpad 9";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_MULTIPLY) & 0x8000) {
		*key = VK_MULTIPLY;
		*nameKey = "Multiply";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_ADD) & 0x8000) {
		*key = VK_ADD;
		*nameKey = "Plus";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_SEPARATOR) & 0x8000) {
		*key = VK_SEPARATOR;
		*nameKey = "Separator";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000) {
		*key = VK_SUBTRACT;
		*nameKey = "Minus";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_DECIMAL) & 0x8000) {
		*key = VK_DECIMAL;
		*nameKey = "Decimal";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_DIVIDE) & 0x8000) {
		*key = VK_DIVIDE;
		*nameKey = "Divide";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		*key = VK_F1;
		*nameKey = "F1";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F2) & 0x8000) {
		*key = VK_F2;
		*nameKey = "F2";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F3) & 0x8000) {
		*key = VK_F3;
		*nameKey = "F3";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F4) & 0x8000) {
		*key = VK_F4;
		*nameKey = "F4";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F5) & 0x8000) {
		*key = VK_F5;
		*nameKey = "F5";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F6) & 0x8000) {
		*key = VK_F6;
		*nameKey = "F6";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F7) & 0x8000) {
		*key = VK_F7;
		*nameKey = "F7";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F8) & 0x8000) {
		*key = VK_F8;
		*nameKey = "F8";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F9) & 0x8000) {
		*key = VK_F9;
		*nameKey = "F9";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F10) & 0x8000) {
		*key = VK_F10;
		*nameKey = "F10";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F11) & 0x8000) {
		*key = VK_F11;
		*nameKey = "F11";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F12) & 0x8000) {
		*key = VK_F12;
		*nameKey = "F12";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F13) & 0x8000) {
		*key = VK_F13;
		*nameKey = "F13";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F14) & 0x8000) {
		*key = VK_F14;
		*nameKey = "F14";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F15) & 0x8000) {
		*key = VK_F15;
		*nameKey = "F15";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F16) & 0x8000) {
		*key = VK_F16;
		*nameKey = "F16";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F17) & 0x8000) {
		*key = VK_F17;
		*nameKey = "F17";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F18) & 0x8000) {
		*key = VK_F18;
		*nameKey = "F18";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F19) & 0x8000) {
		*key = VK_F19;
		*nameKey = "F19";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F20) & 0x8000) {
		*key = VK_F20;
		*nameKey = "F20";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F21) & 0x8000) {
		*key = VK_F21;
		*nameKey = "F21";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F22) & 0x8000) {
		*key = VK_F22;
		*nameKey = "F22";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F23) & 0x8000) {
		*key = VK_F23;
		*nameKey = "F23";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_F24) & 0x8000) {
		*key = VK_F24;
		*nameKey = "F24";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_NUMLOCK) & 0x8000) {
		*key = VK_NUMLOCK;
		*nameKey = "Num Lock";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_SCROLL) & 0x8000) {
		*key = VK_SCROLL;
		*nameKey = "Scroll Lock";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_LCONTROL) & 0x8000) {
		*key = VK_LCONTROL;
		*nameKey = "Left CTRL";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_RCONTROL) & 0x8000) {
		*key = VK_RCONTROL;
		*nameKey = "Right CTRL";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_LMENU) & 0x8000) {
		*key = VK_LMENU;
		*nameKey = "Left MENU";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_RMENU) & 0x8000) {
		*key = VK_RMENU;
		*nameKey = "Right MENU";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_1) & 0x8000) {
		*key = VK_OEM_1;
		*nameKey = "Semi-Colon";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_2) & 0x8000) {
		*key = VK_OEM_2;
		*nameKey = "Forward Slash";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_3) & 0x8000) {
		*key = VK_OEM_3;
		*nameKey = "GRAVE";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_4) & 0x8000) {
		*key = VK_OEM_4;
		*nameKey = "Left Bracket";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_5) & 0x8000) {
		*key = VK_OEM_5;
		*nameKey = "Back Slash";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_6) & 0x8000) {
		*key = VK_OEM_6;
		*nameKey = "Right Bracket";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_7) & 0x8000) {
		*key = VK_OEM_7;
		*nameKey = "Apostrophe";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_COMMA) & 0x8000) {
		*key = VK_OEM_COMMA;
		*nameKey = "Comma";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) {
		*key = VK_OEM_PERIOD;
		*nameKey = "Period";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_MINUS) & 0x8000) {
		*key = VK_OEM_MINUS;
		*nameKey = "Dash";
		*clicked = !*clicked;
	}
	if (GetAsyncKeyState(VK_OEM_PLUS) & 0x8000) {
		*key = VK_OEM_PLUS;
		*nameKey = "Equals";
		*clicked = !*clicked;
	}
}

void LiveStorage_InitializeDDLStateForStatsGroup(const void* def, DDLState* state, const StatsGroup statsGroup) // E8 ? ? ? ? 48 63 05 ? ? ? ? 4C 8D 8C 24 (xref)
{
	uintptr_t address = var->baseModule + var->Offest.initDDLState;
	((void(*)(const void*, DDLState*, const StatsGroup))address)(def, state, statsGroup);
}

bool SetDatab(const char* path, DDLValue& value, StatsGroup group) {
	DDLState state;
	DDLContext ddlcontext;
	char* navStrings[16]{};
	int navStringCount;
	bool flag = false;

	if (CL_PlayerData_GetDDLBufferr((__int64)&ddlcontext, 0, 0, group)) {

		ParseShitt(path, (const char**)navStrings, 16, &navStringCount);

		LiveStorage_InitializeDDLStateForStatsGroup(ddlcontext.def, &state, group);

		if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings)) {

			switch (DDL_GetType(&state)) {

			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				flag = DDL_SetInt(&state, &ddlcontext, value.intValue);
				break;

			case 8:
			case 10:
				flag = DDL_SetString(&state, &ddlcontext, value.stringPtr);
				break;
			}
		}
	}

	return flag;
}

int GetLogonStatus(int status) {
	return reinterpret_cast<int(*)(int)>(var->baseModule + var->Offest.logonstatus)(status);
}

bool
LUI_BeginEvent(int client, const char* eventType, uintptr_t luaVM)
{
	if (!is_bad_ptr(var->Offest.LUI_BeginEvent))
		return reinterpret_cast<bool(*)(int, const char*, uintptr_t)>(var->baseModule + var->Offest.LUI_BeginEvent)(client, eventType, luaVM);
}

void
LUI_BeginTable(const char* key, int narr, int nrec, uintptr_t luaVM)
{
	if (!is_bad_ptr(var->Offest.LUI_BeginTable))
		reinterpret_cast<void(*)(const char*, int, int, uintptr_t)>(var->baseModule + var->Offest.LUI_BeginTable)(key, narr, nrec, luaVM);
}

void
LUI_SetTableInt(const char* key, __int64 value, uintptr_t luaVM)
{
	if (!is_bad_ptr(var->Offest.LUI_SetTableInt))
		reinterpret_cast<void(*)(const char*, __int64, uintptr_t)>(var->baseModule + var->Offest.LUI_SetTableInt)(key, value, luaVM);
}

void
LUI_SetTableString(const char* key, const char* value, uintptr_t luaVM)
{
	if (!is_bad_ptr(var->Offest.LUI_SetTableString))
		reinterpret_cast<void(*)(const char*, const char*, uintptr_t)>(var->baseModule + var->Offest.LUI_SetTableString)(key, value, luaVM);
}

void
LUI_EndTable(uintptr_t luaVM)
{
	if (!is_bad_ptr(var->Offest.LUI_EndTable))
		reinterpret_cast<void(*)(uintptr_t)>(var->baseModule + var->Offest.LUI_EndTable)(luaVM);
}

void
LUI_EndEvent(uintptr_t luaVM)
{
	if (!is_bad_ptr(var->Offest.LUI_EndEvent))
		reinterpret_cast<void(*)(uintptr_t)>(var->baseModule + var->Offest.LUI_EndEvent)(luaVM);
}

void SendToastNotification(const char* header, const char* description, const char* icon)
{
	uintptr_t luaVM;
	if (is_bad_ptr(var->Offest.LUI_luaVM))
		return;
	luaVM = *reinterpret_cast<uintptr_t*>(var->baseModule + var->Offest.LUI_luaVM);
	if (!is_bad_ptr(var->Offest.LUI_BeginEvent) && !is_bad_ptr(var->Offest.LUI_BeginTable) && !is_bad_ptr(var->Offest.LUI_SetTableInt) && !is_bad_ptr(var->Offest.LUI_SetTableString) && !is_bad_ptr(var->Offest.LUI_EndTable) && !is_bad_ptr(var->Offest.LUI_EndEvent))
	{
		if (LUI_BeginEvent(0, ("send_toast_notification"), luaVM))
		{
			LUI_SetTableInt(("immediate"), 1, luaVM);
			LUI_BeginTable(("options"), 0, 6, luaVM);
			LUI_SetTableInt(("displayTime"), 4000, luaVM);
			LUI_SetTableString(("icon"), icon, luaVM);
			LUI_SetTableString(("header"), header, luaVM);
			LUI_SetTableString(("description"), description, luaVM);
			LUI_SetTableInt(("type"), 6, luaVM);
			LUI_SetTableInt(("controllerIndex"), 0, luaVM);
			LUI_EndTable(luaVM);
			LUI_EndEvent(luaVM);
		}
	}
}

void SendToastNotification(const char* header, const char* description, const char* icon, int time)
{
	uintptr_t luaVM;
	if (is_bad_ptr(var->Offest.LUI_luaVM))
		return;
	luaVM = *reinterpret_cast<uintptr_t*>(var->baseModule + var->Offest.LUI_luaVM);
	if (!is_bad_ptr(var->Offest.LUI_BeginEvent) && !is_bad_ptr(var->Offest.LUI_BeginTable) && !is_bad_ptr(var->Offest.LUI_SetTableInt) && !is_bad_ptr(var->Offest.LUI_SetTableString) && !is_bad_ptr(var->Offest.LUI_EndTable) && !is_bad_ptr(var->Offest.LUI_EndEvent))
	{
		if (LUI_BeginEvent(0, ("send_toast_notification"), luaVM))
		{
			LUI_SetTableInt(("immediate"), 1, luaVM);
			LUI_BeginTable(("options"), 0, 6, luaVM);
			LUI_SetTableInt(("displayTime"), time, luaVM);
			LUI_SetTableString(("icon"), icon, luaVM);
			LUI_SetTableString(("header"), header, luaVM);
			LUI_SetTableString(("description"), description, luaVM);
			LUI_SetTableInt(("type"), 6, luaVM);
			LUI_SetTableInt(("controllerIndex"), 0, luaVM);
			LUI_EndTable(luaVM);
			LUI_EndEvent(luaVM);
		}
	}
}