#include "menu.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imguipp_v2.h"
#include "CProjectSDK.hpp"
#include "xor.h"
#include "sdk.h"
#include "recoil.h"
#include <conio.h>
#include <stdio.h>
#include <Lmcons.h>
#include <string>
#include "vectorstruct.h"
#include "doubleguns.h"
//#include "imgui_impl_win32.h"
#pragma warning(disable: 4996)

ImFont* MainCaps;
ImFont* mainFeatureFBold;
ImFont* g_pAwesome;
ImFont* Main;
ImFont* FMenu;
ImFont* BigFont;
ImFont* mainfont;
ImFont* mainfontBig;
ImFont* icons;
ImFont* icons2;
ImFont* mainF;
ImFont* mainFBold;
ImFont* ChildTitle;
static int Tabs = 1;

#define NO_ALPHA (ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Float | ImGuiColorEditFlags_NoDragDrop)


void ToggleNL(const char* toggleName, bool* featureBool, BOOL newLine)
{
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = ImGui::GetFrameHeight();
    float width = height * 1.55f;
    float radius = height * 0.50f;

    ImGui::InvisibleButton(toggleName, ImVec2(width, height));
    if (ImGui::IsItemClicked())
        *featureBool = !*featureBool;

    float t = *featureBool ? 1.0f : 0.0f;

    ImGuiContext& g = *GImGui;
    float ANIM_SPEED = 0.08f;
    if (g.LastActiveId == g.CurrentWindow->GetID(toggleName))// && g.LastActiveIdTimer < ANIM_SPEED)
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = *featureBool ? (t_anim) : (1.0f - t_anim);
    }

    ImU32 col_bg;
    if (ImGui::IsItemHovered())
        col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 0.40f), ImVec4(ImColor(78, 78, 78)), t)); // ImColor(255, 0, 255, 255) // 0.64f, 0.83f, 0.34f, 1.0f
    else
        col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 0.60f), ImVec4(ImColor(78, 78, 78)), t)); // ImColor(255, 0, 255, 255) // 0.56f, 0.83f, 0.26f, 1.0f

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

    ImGui::SameLine();
    ImGui::Text(toggleName);


}

namespace helper
{
    int rotation_start_index;
    void ImRotateStart()
    {
        rotation_start_index = ImGui::GetWindowDrawList()->VtxBuffer.Size;
    }

    ImVec2 ImRotationCenter()
    {
        ImVec2 l(FLT_MAX, FLT_MAX), u(-FLT_MAX, -FLT_MAX); // bounds

        const auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
        for (int i = rotation_start_index; i < buf.Size; i++)
            l = ImMin(l, buf[i].pos), u = ImMax(u, buf[i].pos);

        return ImVec2((l.x + u.x) / 2, (l.y + u.y) / 2); // or use _ClipRectStack?
    }

    ImVec2 operator-(const ImVec2& l, const ImVec2& r) { return{ l.x - r.x, l.y - r.y }; }

    void ImRotateEnd(float rad, ImVec2 center = ImRotationCenter())
    {
        float s = sin(rad), c = cos(rad);
        center = ImRotate(center, s, c) - center;

        auto& buf = ImGui::GetWindowDrawList()->VtxBuffer;
        for (int i = rotation_start_index; i < buf.Size; i++)
            buf[i].pos = ImRotate(buf[i].pos, s, c) - center;
    }
}

void TextCentered(std::string text) {
    auto windowWidth = ImGui::GetWindowSize().x;
    auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    ImGui::Text(text.c_str());
}

void subHeaderText(std::string text) {
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 0.4f, 0.4f, 1));
    ImGui::PushFont(ChildTitle);
    ImGui::SetCursorPosY(6);
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(text.c_str()).x) * 0.5f);
    ImGui::Text(text.c_str());
    ImGui::PopStyleColor(1);
    ImGui::PopFont();
}

void throwImGuiError(std::string text, bool* disable) 
{
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.671f, 0.f, 0.99f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.571f, 0.f, 0.99f, 1.00f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.471f, 0.f, 0.99f, 1.00f));
    ImGuiIO io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x / 2 - ImGui::GetWindowWidth() / 2, io.DisplaySize.y / 2 - ImGui::GetWindowHeight() / 2));
    ImGui::OpenPopup(text.c_str());
    ImGui::SetNextWindowSize(ImVec2(400, 150));
    if (ImGui::BeginPopupModal(text.c_str(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
    {
        ImGui::SetCursorPos(ImVec2(17, 10));
        ImGui::PushFont(mainFBold);
        ImGui::BeginGroup();
        {
            TextCentered(xorstr_("Error!"));
            ImGui::PopFont();
        }
        ImGui::EndGroup();
        ImGui::Separator();
        ImGui::PushFont(mainfontBig);
        ImGui::SetCursorPos(ImVec2(10, 118));
        if (ImGui::Button(xorstr_("Close"), ImVec2(380, 23)))
        {
            *disable = false;
            ImGui::CloseCurrentPopup();
        }
    }
    ImGui::EndPopup();
    ImGui::PopStyleColor(3);
}

static std::string colorRebrand = "";

namespace custom
{
    void combosearch(char* input, int* index, std::string hint, std::vector<std::string> list, std::vector<std::string> listLower, ImVec2 size, bool op = false)
    {
        ImGui::PushItemWidth(size.x);
        // State
        char empty[1] = { "" };
        std::string str;
        str = input;
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        std::string label = "##input" + hint;
        // Code
        const bool is_input_text_enter_pressed = ImGui::InputTextWithHint(label.c_str(), hint.c_str(), input, sizeof(input), ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue);
        const bool is_input_text_active = ImGui::IsItemActive();
        const bool is_input_text_activated = ImGui::IsItemActivated();

        if (is_input_text_activated)
        {
            ImGui::OpenPopup("##popup");
        }
        {
            ImGui::SetNextWindowPos(ImVec2(ImGui::GetItemRectMin().x, ImGui::GetItemRectMax().y));
            ImGui::SetNextWindowSize(ImVec2(size.x, 70));
            if (ImGui::BeginPopup("##popup", ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_ChildWindow))
            {
                for (int i = 0; i < list.size(); i++)
                {
                    if (strstr(listLower[i].c_str(), str.c_str()) == NULL)
                        continue;
                    if (ImGui::Selectable(list[i].c_str()))
                    {
                        ImGui::ClearActiveID();
                        strcpy(input, list[i].c_str());
                        *index = i;
                        if (op)
                            var->Settings.cfg.i_savedop = vector::opListInt[i];
                    }
                }

                if (!is_input_text_active && !ImGui::IsWindowFocused())
                {
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
    }

}


static const auto CustomSlider = [&](const char* label, float min, float max, float* value)
{
    //ImVec4(0.435, 0, 1, 1)
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 1));
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0, 0, 0, 1));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0, 0, 0, 1));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 1));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);

    ImGui::PushID(label);
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10.0f);
    ImGui::SliderFloat("##CustomSlider_", value, min, max);
    ImGui::PopID();

    ImGui::Spacing();

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(4);
};

static bool allslots = false;
static int guns = 0;
static int meta = 0;
static char bpname0[64] = "";
static char bpname1[64] = "";
static char bpname2[64] = "";
static char bpname3[64] = "";
static char bpname4[64] = "";
static int bpcombo0 = 0;
static int bpcombo1 = 0;
static int bpcombo2 = 0;
static int bpcombo3 = 0;
static int bpcombo4 = 0;
static bool bpcheckbox0 = false;
static bool bpcheckbox1 = false;
static bool bpcheckbox2 = false;
static bool bpcheckbox3 = false;
static bool bpcheckbox4 = false;
static char moddedbpname[64] = "";
static int moddedbpcombo1 = 0;
static int moddedbpcombo2 = 0;
static int mpclasscombo = 0;
static char mpclassname[64] = "";
static int wzclasscombo = 0;
static char wzclassname[64] = "";
static int moddedclantags = 0;
static int gamemode = 4;
ImVec4 player_colorVec4 = ImVec4(0.87f, 0.0f, 0.0f, 1.0f);
ImVec4 item_colorVec4 = ImVec4(0.0f, 0.61f, 1.0f, 1.0f);
static int moddedGunCombo = 0;
static int moddedCamoCombo = 0;
static bool recoilBool = false;
static bool spreadBool = false;

unsigned char tempRainbow[4] = { 255, 0, 0, 0 };

void UpdateRainbowColor()
{
    int stage = tempRainbow[3];
    switch (stage) {
    case 0:        tempRainbow[2] += 5;        if (tempRainbow[2] == 255)         tempRainbow[3] = 1;        break;
    case 1:        tempRainbow[0] -= 5;        if (tempRainbow[0] == 0)             tempRainbow[3] = 2;        break;
    case 2:        tempRainbow[1] += 5;        if (tempRainbow[1] == 255)         tempRainbow[3] = 3;        break;
    case 3:        tempRainbow[2] -= 5;        if (tempRainbow[2] == 0)             tempRainbow[3] = 4;        break;
    case 4:        tempRainbow[0] += 5;        if (tempRainbow[0] == 255)         tempRainbow[3] = 5;        break;
    case 5:        tempRainbow[1] -= 5;        if (tempRainbow[1] == 0)             tempRainbow[3] = 0;        break;
    }
}

enum heads {
    favorites, editors, visuals, _settings, aimbot
};

enum sub_heads {
    page1, page2, page3, _general, advanced
};

void AIO::MENUSHOW()
{
    if (var->Settings.server.spread || var->Settings.server.recoil)
        weapons = (WeaponCompleteDefArr*)(var->baseModule + var->Offest.wepStructOffset);

    ImVec2 P1, P2;

    if (Tabs == 1)
    {
        ImGui::SetNextWindowSize(ImVec2(850, 485));
    }
    if (Tabs == 2)
    {
        ImGui::SetNextWindowSize(ImVec2(880, 485));
    }
    if (Tabs == 3)
    {
        ImGui::SetNextWindowSize(ImVec2(850, 485));
    }
    if (Tabs == 4)
    {
        ImGui::SetNextWindowSize(ImVec2(850, 485));
    }
    if (Tabs == 5)
    {
        ImGui::SetNextWindowSize(ImVec2(850, 485));
    }
    UpdateRainbowColor();
    ImGui::StyleColorsDark();
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.10f, 0.10f, 0.11f, 1.00f));
    ImVec4* colors = ImGui::GetStyle().Colors;
    ImGuiStyle& Style = ImGui::GetStyle();

    Style.ChildRounding = 5.0f;
    Style.WindowRounding = 2;
    Style.FramePadding = ImVec2(4, 2);
    Style.FrameBorderSize = 0;
    Style.ScrollbarSize = 10;
    Style.FrameRounding = 4;
    Style.PopupRounding = 4;
    Style.ScrollbarRounding = 6;
    Style.GrabRounding = 4;
    Style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    Style.WindowMenuButtonPosition = ImGuiDir_Right;
    Style.DisplaySafeAreaPadding = ImVec2(4, 4);

    if (var->Settings.rgbChams)
    {
        player_colorVec4 = ImColor((int)tempRainbow[0], (int)tempRainbow[1], (int)tempRainbow[2]);
    }
    if (var->Settings.rgblootChams)
    {
        item_colorVec4 = ImColor((int)tempRainbow[0], (int)tempRainbow[1], (int)tempRainbow[2]);
    }


    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.11f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.32f, 0.32f, 0.32f, 0.54f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.32f, 0.32f, 0.32f, 0.75f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.62f, 0.00f, 0.99f, 0.78f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.44f, 0.02f, 0.69f, 0.59f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.62f, 0.00f, 0.99f, 0.78f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.59f);
    colors[ImGuiCol_Text] = ImVec4(0.99f, 0.99f, 0.99f, 1.00f);
    ImColor tabfillColor;
    ImColor iconfillColor;
    ImColor namefillColor;

    static float rainbow;
    rainbow += 0.0010f; //0.0001f
    if (rainbow > 1.f)
        rainbow = 0.f;
    auto rgb = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);

    // rainbow
    if (var->Settings.b_rainbowmenu)
    {
        colorRebrand = "rainbow";
        colors[ImGuiCol_Button] = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
        colors[ImGuiCol_ButtonHovered] = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
        colors[ImGuiCol_ButtonActive] = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
        colors[ImGuiCol_SliderGrab] = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
        colors[ImGuiCol_SliderGrabActive] = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
        colors[ImGuiCol_CheckMark] = ImColor::HSV(rainbow, 1.f, 1.f, 0.8f);
        tabfillColor = ImColor((int)tempRainbow[0], (int)tempRainbow[1], (int)tempRainbow[2], (int)Style.Alpha * 255);
        iconfillColor = ImColor((int)tempRainbow[0], (int)tempRainbow[1], (int)tempRainbow[2], (int)Style.Alpha * 255);
        namefillColor = ImColor((int)tempRainbow[0], (int)tempRainbow[1], (int)tempRainbow[2], (int)Style.Alpha * 255);
    }
    else
    {   //normal
        tabfillColor = ImColor(ImGui::GetColorU32(ImGuiCol_Text, Style.Alpha));
        iconfillColor = ImColor(ImGui::GetColorU32(ImGuiCol_Text, Style.Alpha));
        namefillColor = ImColor(ImGui::GetColorU32(ImGuiCol_Text, Style.Alpha));


        colors[ImGuiCol_Button] = ImColor(78, 78, 78); //78, 78, 78
        colors[ImGuiCol_ButtonHovered] = ImColor(84, 84, 84, 255);
        colors[ImGuiCol_ButtonActive] = ImColor(78, 78, 78);
        colors[ImGuiCol_CheckMark] = ImColor(255, 255, 255);
        colors[ImGuiCol_SliderGrab] = ImColor(255, 255, 255);
        colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255);

    }

    colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.14f, 0.14f, 54.f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.14f, 0.14f, 75.f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.14f, 0.14f, 0.14f, 1.f);
    colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.14f, 0.14f, 54.f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 75.f);
    colors[ImGuiCol_TabActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.f);

    static heads tab{ favorites };
    static sub_heads subtab{ page1 };
    static sub_heads subtab2{ page1 };


    const char* tab_name = tab == favorites ? "Favorites" : tab == editors ? "Editors" : tab == visuals ? "Visuals" : tab == _settings ? "Config" : tab == aimbot ? "Aimbot" : 0;

    const char* combo_gamemode[5] = { "WZ Public", "WZ Private", "MW Public", "MW Private", "All Modes" };
    const char* combo_meta[3] = { "No Attachments", "S&D Meta", "Warzone Meta" };
    const char* combo_guns[4] = { "All Guns", "MW Guns", "CW Guns", "VG Guns" };

    const char* vanityName = "VIP AIO"; // PUT AIO = PUT, VIP AIO = Morpheus
    const char* vanityLogo = "Y"; // M = PUT, Y = Morpheus
    const int posx_vanity = 70; // 65 = PUT AIO, 70 = VIP AIO
    const int posy_vanity = 290;
    const char* version = "V1.64";
    const int posx_version = 105;
    const int posy_version = 260;

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(46, 46, 46, 18).Value);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImColor(18, 18, 18, 255).Value); //18, 18, 18, 255
    ImGui::Begin(xorstr_("Hello, world!"), nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    {
        ImGui::SetCursorPos(ImVec2(0, 0));
        ImGui::PushStyleColor(ImGuiCol_Border, ImColor(0, 0, 0, 0).Value);
        if (ImGui::BeginChild(xorstr_("fag"), ImVec2(880, 700), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse));
        ImGui::PopStyleColor();
        {
            auto draw = ImGui::GetWindowDrawList();
            auto pos = ImGui::GetWindowPos();
            auto size = ImGui::GetWindowSize();
            ImGuiStyle style = ImGui::GetStyle();

            ImGui::SetCursorPos(ImVec2(0, 0));



            ImGui::PushStyleColor(ImGuiCol_Header, ImColor(78, 78, 78).Value);
            ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImColor(78, 78, 78).Value);
            ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImColor(78, 78, 78).Value);

            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImColor(18, 18, 18, 255).Value);

            ImGui::SetCursorPos(ImVec2(0, 0));
            Style.ChildRounding = 1.0f;
            if (ImGui::BeginChild("##NIGGATABS", ImVec2(125, 800), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
            {
                ImGui::BeginGroup();
                {
                    ImGui::PushFont(g_pAwesome);
                    ImGui::PushFont(mainfont);
                    ImGui::TextDisabled("");
                    ImGui::NewLine();
                    ImGui::PopStyleColor();
                    ImGui::PopFont();

                }
                ImGui::EndGroup();


                ImGui::BeginGroup();
                if (Tabs == 1)
                {
                    if (var->Settings.b_rainbowmenu)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor::HSV(rainbow, 1.f, 1.f, 0.8f).Value);
                    }
                    else
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(78, 78, 78).Value);
                    }
                    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0, 0, 0, 0).Value);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::SetCursorPos(ImVec2(0, 0));
                    if (ImGui::Button(ICON_FA_HOME, ImVec2(125, 100)))
                    {
                        Tabs = 1;
                    }
                    ImGui::PopStyleColor();
                    ImGui::SetCursorPos(ImVec2(39, 22));
                    ImGui::PushFont(mainfont);
                    ImGui::Text("\n\n\n  HOME");
                    ImGui::PopFont();
                    ImGui::PopStyleColor(4);
                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255).Value);
                    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0, 0, 0, 0).Value);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::SetCursorPos(ImVec2(0, 0));
                    if (ImGui::Button(ICON_FA_HOME, ImVec2(125, 100)))
                    {
                        Tabs = 1;
                    }
                    ImGui::PopStyleColor();
                    ImGui::SetCursorPos(ImVec2(39, 22));
                    ImGui::PushFont(mainfont);
                    ImGui::Text("\n\n\n  HOME");
                    ImGui::PopFont();
                    ImGui::PopStyleColor(4);
                }

                if (Tabs == 2)
                {
                    if (var->Settings.b_rainbowmenu)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor::HSV(rainbow, 1.f, 1.f, 0.8f).Value);
                    }
                    else
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(78, 78, 78).Value);
                    }
                    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0, 0, 0, 0).Value);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::SetCursorPosX(0);
                    if (ImGui::Button(ICON_FA_PAINT_BRUSH, ImVec2(125, 100)))
                    {
                        Tabs = 2;
                    }
                    ImGui::PopStyleColor();
                    ImGui::SetCursorPos(ImVec2(39, 112));
                    ImGui::PushFont(mainfont);
                    ImGui::Text("\n\n\nEDITORS");
                    ImGui::PopFont();
                    ImGui::PopStyleColor(4);

                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255).Value);
                    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0, 0, 0, 0).Value);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::SetCursorPosX(0);
                    if (ImGui::Button(ICON_FA_PAINT_BRUSH, ImVec2(125, 100)))
                    {
                        Tabs = 2;
                    }
                    ImGui::PopStyleColor();
                    ImGui::SetCursorPos(ImVec2(39, 112));
                    ImGui::PushFont(mainfont);
                    ImGui::Text("\n\n\nEDITORS");
                    ImGui::PopFont();
                    ImGui::PopStyleColor(4);
                }

                if (Tabs == 3)
                {
                    if (var->Settings.b_rainbowmenu)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor::HSV(rainbow, 1.f, 1.f, 0.8f).Value);
                    }
                    else
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(78, 78, 78).Value);
                    }
                    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0, 0, 0, 0).Value);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::SetCursorPosX(0);
                    if (ImGui::Button(ICON_FA_EYE, ImVec2(125, 100)))
                    {
                        Tabs = 3;
                    }
                    ImGui::PopStyleColor();
                    ImGui::SetCursorPos(ImVec2(35, 203));
                    ImGui::PushFont(mainfont);
                    ImGui::Text("\n\n\n VISUALS");
                    ImGui::PopFont();
                    ImGui::PopStyleColor(4);
                }
                else
                {

                    ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255).Value);
                    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0, 0, 0, 0).Value);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::SetCursorPosX(0);
                    if (ImGui::Button(ICON_FA_EYE, ImVec2(125, 100)))
                    {
                        Tabs = 3;
                    }
                    ImGui::PopStyleColor();
                    ImGui::SetCursorPos(ImVec2(35, 203));
                    ImGui::PushFont(mainfont);
                    ImGui::Text("\n\n\n VISUALS");
                    ImGui::PopFont();
                    ImGui::PopStyleColor(4);
                }

                if (Tabs == 4)
                {
                    if (var->Settings.b_rainbowmenu)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor::HSV(rainbow, 1.f, 1.f, 0.8f).Value);
                    }
                    else
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(78, 78, 78).Value);
                    }
                    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0, 0, 0, 0).Value);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::SetCursorPosX(0);
                    if (ImGui::Button(ICON_FA_BUG, ImVec2(125, 100)))
                    {
                        Tabs = 4;
                    }
                    ImGui::PopStyleColor();
                    ImGui::SetCursorPos(ImVec2(35, 293));
                    ImGui::PushFont(mainfont);
                    ImGui::Text("\n\n\nEXPLOITS");
                    ImGui::PopFont();
                    ImGui::PopStyleColor(4);
                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255).Value);
                    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0, 0, 0, 0).Value);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::SetCursorPosX(0);
                    if (ImGui::Button(ICON_FA_BUG, ImVec2(125, 100)))
                    {
                        Tabs = 4;
                    }
                    ImGui::PopStyleColor();
                    ImGui::SetCursorPos(ImVec2(35, 293));
                    ImGui::PushFont(mainfont);
                    ImGui::Text("\n\n\nEXPLOITS");
                    ImGui::PopFont();
                    ImGui::PopStyleColor(4);
                }



                if (Tabs == 5)
                {
                    if (var->Settings.b_rainbowmenu)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor::HSV(rainbow, 1.f, 1.f, 0.8f).Value);
                    }
                    else
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, ImColor(78, 78, 78).Value);
                    }
                    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0, 0, 0, 0).Value);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::SetCursorPosX(0);
                    if (ImGui::Button(ICON_FA_COG, ImVec2(125, 100)))
                    {
                        Tabs = 5;
                    }
                    ImGui::PopStyleColor();
                    ImGui::SetCursorPos(ImVec2(35, 383));
                    ImGui::PushFont(mainfont);
                    ImGui::Text("\n\n\nSETTINGS");
                    ImGui::PopFont();
                    ImGui::PopStyleColor(4);
                }
                else
                {
                    ImGui::PushStyleColor(ImGuiCol_Text, ImColor(255, 255, 255).Value);
                    ImGui::PushStyleColor(ImGuiCol_Button, ImColor(0, 0, 0, 0).Value);
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(0, 0, 0, 0)));
                    ImGui::SetCursorPosX(0);
                    if (ImGui::Button(ICON_FA_COG, ImVec2(125, 100)))
                    {
                        Tabs = 5;
                    }
                    ImGui::PopStyleColor();
                    ImGui::SetCursorPos(ImVec2(35, 383));
                    ImGui::PushFont(mainfont);
                    ImGui::Text("\n\n\nSETTINGS");
                    ImGui::PopFont();
                    ImGui::PopStyleColor(4);
                }

                ImGui::EndGroup();
                ImGui::PopFont();
                ImGui::PopStyleColor();

            } ImGui::EndChild(); ImGui::PopStyleColor();

            ImGui::SameLine();

            //            ImGui::SetCursorPosY(5);

            ImGui::SameLine();

            Style.ChildRounding = 5.0f;
            if (Tabs == 1)
            {
                ImGui::SetCursorPos(ImVec2(390, 5));
                ImGui::PushStyleColor(ImGuiCol_Text, ImColor(78, 78, 78).Value);
                ImGui::Text("PAIO");
                ImGui::PopStyleColor();

                ImGui::SetCursorPos(ImVec2(165, 40));
                if (ImGui::BeginChild("aimkey/location", ImVec2(310, 155), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Main Features");
                        static bool unlockinit = false;
                        ImGui::SetCursorPosY(29);



                        ImGui::Checkbox("Unlock All", &var->Settings.b_unlock);
                        ImGui::Checkbox("Reverse Camos", &var->Settings.b_camo);

                        static bool recoilOn = false;
                        static bool recoilOff = true;
                        static bool spreadOn = false;
                        static bool spreadOff = true;
                        static bool ro = false;
                        static bool so = false;
                        {
   
                            if (ImGui::Checkbox("No Spread", &var->Settings.b_spread))
                            {
                                if (var->Settings.server.spread)
                                {
                                    if (!spreadOn && spreadOff)
                                    {
                                        if (!spreadBool)
                                        {
                                            for (int count = 0; count < 962; count++)
                                            {
                                                if (weapons->weaponCompleteDefArr[count]->weapDef)
                                                {
                                                    // value resetters
                                                    valuesSpreadBackup[count][0] = weapons->weaponCompleteDefArr[count]->weapDef->fHipSpreadDuckedDecay;
                                                    valuesSpreadBackup[count][1] = weapons->weaponCompleteDefArr[count]->weapDef->fHipSpreadProneDecay;
                                                    valuesSpreadBackup[count][2] = weapons->weaponCompleteDefArr[count]->weapDef->hipSpreadSprintDecay;
                                                    valuesSpreadBackup[count][3] = weapons->weaponCompleteDefArr[count]->weapDef->hipSpreadInAirDecay;
                                                    valuesSpreadBackup[count][4] = weapons->weaponCompleteDefArr[count]->weapDef->fHipReticleSidePos;
                                                    valuesSpreadBackup[count][5] = weapons->weaponCompleteDefArr[count]->weapDef->fAdsIdleAmount;
                                                    valuesSpreadBackup[count][6] = weapons->weaponCompleteDefArr[count]->weapDef->fHipIdleAmount;
                                                    valuesSpreadBackup[count][7] = weapons->weaponCompleteDefArr[count]->weapDef->adsIdleSpeed;
                                                    valuesSpreadBackup[count][8] = weapons->weaponCompleteDefArr[count]->weapDef->hipIdleSpeed;
                                                    valuesSpreadBackup[count][9] = weapons->weaponCompleteDefArr[count]->weapDef->fIdleCrouchFactor;
                                                    valuesSpreadBackup[count][10] = weapons->weaponCompleteDefArr[count]->weapDef->fIdleProneFactor;
                                                    valuesSpreadBackup[count][11] = weapons->weaponCompleteDefArr[count]->weapDef->fGunMaxPitch;
                                                    valuesSpreadBackup[count][12] = weapons->weaponCompleteDefArr[count]->weapDef->fGunMaxYaw;
                                                    valuesSpreadBackup[count][13] = weapons->weaponCompleteDefArr[count]->weapDef->fViewMaxPitch;
                                                    valuesSpreadBackup[count][14] = weapons->weaponCompleteDefArr[count]->weapDef->fViewMaxYaw;
                                                    valuesSpreadBackup[count][15] = weapons->weaponCompleteDefArr[count]->weapDef->adsIdleLerpStartTime;
                                                    valuesSpreadBackup[count][16] = weapons->weaponCompleteDefArr[count]->weapDef->adsIdleLerpTime;
                                                    valuesSpreadBackup[count][17] = weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadMin;
                                                    valuesSpreadBackup[count][18] = weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadMax;
                                                    valuesSpreadBackup[count][19] = weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadDecayRate;
                                                    valuesSpreadBackup[count][20] = weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadFireAdd;
                                                    valuesSpreadBackup[count][21] = weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadTurnAdd;
                                                }
                                            }
                                            spreadBool = true;
                                        }
                                        for (int count = 0; count < 962; count++)
                                        {
                                            if (weapons->weaponCompleteDefArr[count]->weapDef)
                                            {
                                                // WRITE
                                                weapons->weaponCompleteDefArr[count]->weapDef->fHipSpreadDuckedDecay = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->fHipSpreadProneDecay = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->hipSpreadSprintDecay = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->hipSpreadInAirDecay = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->fHipReticleSidePos = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->fAdsIdleAmount = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->fHipIdleAmount = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->adsIdleSpeed = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->hipIdleSpeed = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->fIdleCrouchFactor = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->fIdleProneFactor = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->fGunMaxPitch = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->fGunMaxYaw = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->fViewMaxPitch = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->fViewMaxYaw = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->adsIdleLerpStartTime = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->adsIdleLerpTime = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadMin = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadMax = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadDecayRate = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadFireAdd = 0.0F;
                                                weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadTurnAdd = 0.0F;
                                            }
                                        }
                                        spreadOn = true;
                                        spreadOff = false;
                                    }
                                }
                                else
                                {
                                    so = true;
                                    var->Settings.b_spread = false;
                                }
                            }
                            else if (var->Settings.b_spread == false)
                            {
                                if (!spreadOff && spreadOn)
                                {
                                    for (int count = 0; count < 962; count++)
                                    {
                                        if (weapons->weaponCompleteDefArr[count]->weapDef)
                                        {
                                            // WRITE
                                            weapons->weaponCompleteDefArr[count]->weapDef->fHipSpreadDuckedDecay = valuesSpreadBackup[count][0];
                                            weapons->weaponCompleteDefArr[count]->weapDef->fHipSpreadProneDecay = valuesSpreadBackup[count][1];
                                            weapons->weaponCompleteDefArr[count]->weapDef->hipSpreadSprintDecay = valuesSpreadBackup[count][2];
                                            weapons->weaponCompleteDefArr[count]->weapDef->hipSpreadInAirDecay = valuesSpreadBackup[count][3];
                                            weapons->weaponCompleteDefArr[count]->weapDef->fHipReticleSidePos = valuesSpreadBackup[count][4];
                                            weapons->weaponCompleteDefArr[count]->weapDef->fAdsIdleAmount = valuesSpreadBackup[count][5];
                                            weapons->weaponCompleteDefArr[count]->weapDef->fHipIdleAmount = valuesSpreadBackup[count][6];
                                            weapons->weaponCompleteDefArr[count]->weapDef->adsIdleSpeed = valuesSpreadBackup[count][7];
                                            weapons->weaponCompleteDefArr[count]->weapDef->hipIdleSpeed = valuesSpreadBackup[count][8];
                                            weapons->weaponCompleteDefArr[count]->weapDef->fIdleCrouchFactor = valuesSpreadBackup[count][9];
                                            weapons->weaponCompleteDefArr[count]->weapDef->fIdleProneFactor = valuesSpreadBackup[count][10];
                                            weapons->weaponCompleteDefArr[count]->weapDef->fGunMaxPitch = valuesSpreadBackup[count][11];
                                            weapons->weaponCompleteDefArr[count]->weapDef->fGunMaxYaw = valuesSpreadBackup[count][12];
                                            weapons->weaponCompleteDefArr[count]->weapDef->fViewMaxPitch = valuesSpreadBackup[count][13];
                                            weapons->weaponCompleteDefArr[count]->weapDef->fViewMaxYaw = valuesSpreadBackup[count][14];
                                            weapons->weaponCompleteDefArr[count]->weapDef->adsIdleLerpStartTime = valuesSpreadBackup[count][15];
                                            weapons->weaponCompleteDefArr[count]->weapDef->adsIdleLerpTime = valuesSpreadBackup[count][16];
                                            weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadMin = valuesSpreadBackup[count][17];
                                            weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadMax = valuesSpreadBackup[count][18];
                                            weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadDecayRate = valuesSpreadBackup[count][19];
                                            weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadFireAdd = valuesSpreadBackup[count][20];
                                            weapons->weaponCompleteDefArr[count]->weapDef->slideSpreadTurnAdd = valuesSpreadBackup[count][21];
                                        }
                                    }
                                    spreadOff = true;
                                    spreadOn = false;
                                }
                            }
                            if (ImGui::Checkbox("No Recoil", &var->Settings.b_recoil))
                            {
                                if (var->Settings.server.recoil)
                                {
                                    if (!recoilOn && recoilOff)
                                    {
                                        if (!recoilBool)
                                        {
                                            for (int count = 0; count < 962; count++)
                                            {
                                                if (weapons->weaponCompleteDefArr[count]->weapDef)
                                                {
                                                    for (int countGunKick = 0; countGunKick < 6; countGunKick++)
                                                    {
                                                        // value resetters
                                                        valuesRecoilBackup[count][0] = weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickDir[countGunKick]; // 0x9BC
                                                        valuesRecoilBackup[count][1] = weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickDev[countGunKick];
                                                        valuesRecoilBackup[count][2] = weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickStrengthMin[countGunKick];
                                                        valuesRecoilBackup[count][3] = weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickStrengthMax[countGunKick];
                                                        valuesRecoilBackup[count][4] = weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickPitchScale[countGunKick];
                                                        valuesRecoilBackup[count][5] = weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickDir[countGunKick];
                                                        valuesRecoilBackup[count][6] = weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickDev[countGunKick];
                                                        valuesRecoilBackup[count][7] = weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickStrengthMin[countGunKick];
                                                        valuesRecoilBackup[count][8] = weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickStrengthMax[countGunKick];
                                                        valuesRecoilBackup[count][9] = weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickPitchScale[countGunKick];
                                                    }
                                                }
                                            }
                                            recoilBool = true;
                                        }
                                        for (int count = 0; count < 962; count++)
                                        {
                                            if (weapons->weaponCompleteDefArr[count]->weapDef)
                                            {
                                                for (int countGunKick = 0; countGunKick < 6; countGunKick++)
                                                {
                                                    // write
                                                    weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickDir[countGunKick] = 0.0F; // 0x9BC
                                                    weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickDev[countGunKick] = 0.0F;
                                                    weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickStrengthMin[countGunKick] = 0.0F;
                                                    weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickStrengthMax[countGunKick] = 0.0F;
                                                    weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickPitchScale[countGunKick] = 0.0F;
                                                    weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickDir[countGunKick] = 0.0F;
                                                    weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickDev[countGunKick] = 0.0F;
                                                    weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickStrengthMin[countGunKick] = 0.0F;
                                                    weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickStrengthMax[countGunKick] = 0.0F;
                                                    weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickPitchScale[countGunKick] = 0.0F;
                                                }
                                            }
                                        }
                                        recoilOn = true;
                                        recoilOff = false;
                                    }
                                }
                                else
                                {
                                    ro = true;
                                    var->Settings.b_recoil = false;
                                }
                            }
                            else if (var->Settings.b_recoil == false)
                            {
                                if (!recoilOff && recoilOn)
                                {
                                    for (int count = 0; count < 962; count++)
                                    {
                                        if (weapons->weaponCompleteDefArr[count]->weapDef)
                                        {
                                            for (int countGunKick = 0; countGunKick < 6; countGunKick++)
                                            {
                                                // write
                                                weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickDir[countGunKick] = valuesRecoilBackup[count][0]; // 0x9BC
                                                weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickDev[countGunKick] = valuesRecoilBackup[count][1];
                                                weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickStrengthMin[countGunKick] = valuesRecoilBackup[count][2];
                                                weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickStrengthMax[countGunKick] = valuesRecoilBackup[count][3];
                                                weapons->weaponCompleteDefArr[count]->weapDef->hipAngularGunKickPitchScale[countGunKick] = valuesRecoilBackup[count][4];
                                                weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickDir[countGunKick] = valuesRecoilBackup[count][5];
                                                weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickDev[countGunKick] = valuesRecoilBackup[count][6];
                                                weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickStrengthMin[countGunKick] = valuesRecoilBackup[count][7];
                                                weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickStrengthMax[countGunKick] = valuesRecoilBackup[count][8];
                                                weapons->weaponCompleteDefArr[count]->weapDef->adsAngularGunKickPitchScale[countGunKick] = valuesRecoilBackup[count][9];
                                            }
                                        }
                                    }
                                    recoilOff = true;
                                    recoilOn = false;
                                }
                            }
                        }
                        ImGui::PopStyleVar(1);
                        if (so)
                            throwImGuiError("No Spread has been disabled.", &so);
                        if (ro)
                            throwImGuiError("No Recoil has been disabled.", &ro);



                    }
                    ImGui::EndGroup();

                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild(); ImGui::PopStyleColor(4);




                ImGui::SetCursorPos(ImVec2(495, 40));
                if (ImGui::BeginChild("jay=daddy/location", ImVec2(310, 155), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
                {

                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Sliders");

                        ImGui::PushItemWidth(181);
                        ImGui::SetCursorPosY(29);

                        static float cur_fov;
                        if (ImGui::Checkbox("##fovhookmenu", &var->Settings.fovhookmenu))
                        {
                            if (var->Settings.fovhookmenu && var->Settings.b_ingame)
                            {
                                g_game::enablefovhook();
                            }
                            else
                            {
                                var->Settings.fovhookenable = false;
                                var->Settings.fovhook = false;
                                MH_DisableHook((LPVOID*)(var->Offest.A_CG_GetViewFovBySpace));
                            }
                            var->Settings.f_fov -= 0.00001f;
                            dvar_set2("NSSLSNKPN", var->Settings.f_fov);
                        }
                        if (var->Settings.f_fov > 0.01f)
                        {
                            if (cur_fov != var->Settings.f_fov)
                            {
                                dvar_set2("NSSLSNKPN", var->Settings.f_fov);
                                cur_fov = var->Settings.f_fov;
                            }
                        }
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();
                            ImGui::TextUnformatted("Enable Extended FOV Mode");
                            ImGui::EndTooltip();
                        }
                        ImGui::PushItemWidth(146); ImGui::SameLine(); ImGui::SetCursorPosX(34);
                        if (ImGui::SliderFloat("FOV", &var->Settings.f_fov, 0.01f, 2.0f, "%.2f"))
                        {
                            dvar_set2("NSSLSNKPN", var->Settings.f_fov);
                        }
                        //if (var->Settings.server.fov)
                            //var->Settings.b_fov = var->Settings.f_fov < 1.0f ? true : var->Settings.f_fov > 1.0f ? true : var->Settings.f_fov == 1.0f ? false : 0;

                        ImGui::PushItemWidth(170);
                        ImGui::SliderFloat("Map", &var->Settings.f_map, 0.01f, 10.f, "%.2f");
                        if (var->Settings.server.map)
                            var->Settings.b_map = var->Settings.f_map < 1.0f ? true : var->Settings.f_map > 1.0f ? true : var->Settings.f_map == 1.0f ? false : 0;


                    }ImGui::EndGroup();


                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild(); ImGui::PopStyleColor(4);

                ImGui::SetCursorPos(ImVec2(165, 225));
                if (ImGui::BeginChild("jaysmodz.com", ImVec2(640, 220), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {

                    static char char_array1[64];
                    static char char_array2[64];
                    static char char_array3[64];
                    static char char_array4[64];
                    static char char_array5[64];
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Force Save");
                        ImGui::SetCursorPosY(25);

                        ImGui::PushItemWidth(120);
                        ImGui::SetCursorPosX(147);
                        ImGui::Combo(xorstr_("##attachcombo0"), &var->Settings.attachselection, combo_meta, IM_ARRAYSIZE(combo_meta)); ImGui::SameLine();
                        ImGui::Combo(xorstr_("##gmcombo1"), &var->Settings.gamemodeselection, combo_guns, IM_ARRAYSIZE(combo_guns)); ImGui::SameLine();
                        ToggleNL("Delete Blueprints", &var->Settings.deletebp, TRUE);
                        ImGui::PopItemWidth();
                        ImGui::PushItemWidth(275);
                        ImGui::SetCursorPosX(25);
                        ImGui::BeginGroup();
                        {

                            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3, 6));

                            ImGui::SetCursorPosX(25);
                            if (!var->Settings.slot1)
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                            }
                            else
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, false);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
                            }
                            ImGui::InputTextWithHint(xorstr_("##bpname0"), xorstr_("Enter BP 1 Name"), char_array1, sizeof(char_array1));
                            ImGui::SameLine();
                            ImGui::Combo(xorstr_("##bpcombo0"), &var->Settings.current_camo, var->Settings.camo_list, IM_ARRAYSIZE(var->Settings.camo_list));
                            ImGui::PopStyleVar(1);
                            ImGui::PopItemFlag();
                            ImGui::SameLine();
                            ToggleNL("              ", &var->Settings.slot1, TRUE);

                            ImGui::SetCursorPosX(25);
                            if (!var->Settings.slot2)
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                            }
                            else
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, false);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
                            }
                            ImGui::InputTextWithHint(xorstr_("##bpname1"), xorstr_("Enter BP 2 Name"), char_array2, sizeof(char_array2));
                            ImGui::SameLine();
                            ImGui::Combo(xorstr_("##bpcombo1"), &var->Settings.current_camo2, var->Settings.camo_list2, IM_ARRAYSIZE(var->Settings.camo_list2));
                            ImGui::PopStyleVar(1);
                            ImGui::PopItemFlag();
                            ImGui::SameLine();
                            ToggleNL("        ", &var->Settings.slot2, TRUE);

                            ImGui::SetCursorPosX(25);
                            if (!var->Settings.slot3)
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                            }
                            else
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, false);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
                            }
                            ImGui::InputTextWithHint(xorstr_("##bpname2"), xorstr_("Enter BP 3 Name"), char_array3, sizeof(char_array3));
                            ImGui::SameLine();
                            ImGui::Combo(xorstr_("##bpcombo2"), &var->Settings.current_camo3, var->Settings.camo_list3, IM_ARRAYSIZE(var->Settings.camo_list3));
                            ImGui::PopStyleVar(1);
                            ImGui::PopItemFlag();
                            ImGui::SameLine();
                            ToggleNL("         ", &var->Settings.slot3, TRUE);

                            ImGui::SetCursorPosX(25);
                            if (!var->Settings.slot4)
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                            }
                            else
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, false);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
                            }
                            ImGui::InputTextWithHint(xorstr_("##bpname3"), xorstr_("Enter BP 4 Name"), char_array4, sizeof(char_array4));
                            ImGui::SameLine();
                            ImGui::Combo(xorstr_("##bpcombo3"), &var->Settings.current_camo4, var->Settings.camo_list4, IM_ARRAYSIZE(var->Settings.camo_list4));
                            ImGui::PopStyleVar(1);
                            ImGui::PopItemFlag();
                            ImGui::SameLine();
                            ToggleNL("   ", &var->Settings.slot4, TRUE);

                            ImGui::SetCursorPosX(25);
                            if (!var->Settings.slot5)
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                            }
                            else
                            {
                                ImGui::PushItemFlag(ImGuiItemFlags_Disabled, false);
                                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
                            }
                            ImGui::InputTextWithHint(xorstr_("##bpname4"), xorstr_("Enter BP 5 Name"), char_array5, sizeof(char_array5));
                            ImGui::SameLine();
                            ImGui::Combo(xorstr_("##bpcombo4"), &var->Settings.current_camo5, var->Settings.camo_list5, IM_ARRAYSIZE(var->Settings.camo_list5));
                            ImGui::PopStyleVar(1);
                            ImGui::PopItemFlag();
                            ImGui::SameLine();
                            ToggleNL("  ", &var->Settings.slot5, TRUE);

                            ImGui::PopStyleVar(1);
                            ImGui::PopItemWidth();
                        }
                        ImGui::EndGroup();


                        static bool fs = false;

                        if (!var->Settings.slot1 && !var->Settings.slot2 && !var->Settings.slot3 && !var->Settings.slot4 && !var->Settings.slot5)
                        {
                            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
                            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                        }
                        else
                        {
                            ImGui::PushItemFlag(ImGuiItemFlags_Disabled, false);
                            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
                        }
                        ImGui::PushFont(mainfontBig);
                        ImGui::SetCursorPosX(25);
                        if (ImGui::Button("Force Save", ImVec2(584, 24)))
                        {
                            if (var->Settings.server.forcesave)
                            {
                                if (var->Settings.slot1)
                                    forceSave("0", var->Settings.deletebp, var->Settings.gamemodeselection, char_array1, var->Settings.current_camo, var->Settings.attachselection);
                                if (var->Settings.slot2)
                                    forceSave("1", var->Settings.deletebp, var->Settings.gamemodeselection, char_array2, var->Settings.current_camo2, var->Settings.attachselection);
                                if (var->Settings.slot3)
                                    forceSave("2", var->Settings.deletebp, var->Settings.gamemodeselection, char_array3, var->Settings.current_camo3, var->Settings.attachselection);
                                if (var->Settings.slot4)
                                    forceSave("3", var->Settings.deletebp, var->Settings.gamemodeselection, char_array4, var->Settings.current_camo4, var->Settings.attachselection);
                                if (var->Settings.slot5)
                                    forceSave("4", var->Settings.deletebp, var->Settings.gamemodeselection, char_array5, var->Settings.current_camo5, var->Settings.attachselection);

                                *(BYTE*)(var->baseModule + var->Offest.uploadbps) = 1;

                                SendToastNotification("^1Force Save", "Selected Weapons have been saved as blueprints! Check your armory.", "ui_emblem_780", 8000);
                            }
                            else
                            {
                                fs = true;
                            }
                        }
                        ImGui::PopFont();
                        ImGui::PopStyleVar(1);
                        ImGui::PopItemFlag();
                        if (fs)
                            throwImGuiError("Force Save has been disabled.", &fs);
                    }
                    ImGui::EndGroup();




                }
                ImGui::EndChild();


            }


            if (Tabs == 2)
            {

                ImGui::SetCursorPos(ImVec2(420, 5));
                ImGui::PushStyleColor(ImGuiCol_Text, ImColor(78, 78, 78).Value);
                ImGui::Text("PAIO");
                ImGui::PopStyleColor();


                static bool cto = false;
                static bool cno = false;
                static bool dwo = false;
                static bool opo = false;
                static bool cao = false;
                static bool emo = false;

                static bool mwo = false;
                static bool geo = false;
                static bool ceo = false;
                static bool seo = false;
                static bool reo = false;
                static bool weo = false;

                ImGui::SetCursorPos(ImVec2(165, 40));
                if (ImGui::BeginChild("aaaaaaaaa/location", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
                {

                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {

                        static int retNum = 0;
                        static int wepCombo = 0;
                        static int classCombo = 0;
                        std::vector<std::string> reticles;
                        for (auto const& imap : vector::retList)
                            reticles.push_back(imap.first);
                        ImGui::SetCursorPosY(21);
                        ImGui::Separator();
                        ImGui::SetCursorPos({ 4, 4 });
                        ImGui::BeginGroup();
                        {
                            subHeaderText("Reticle");
                            ImGui::SetCursorPosY(25);
                            ImGui::PushItemWidth(212);
                            ImGui::Combo("##stickerc", &retNum, reticles);
                            ImGui::PushItemWidth(102);
                            ImGui::Combo("##wepcombo", &wepCombo, "Primary\0\Secondary\000");
                            ImGui::SameLine();
                            ImGui::Combo("##retclass", &classCombo, "Class 1\0\Class 2\0\Class 3\0\Class 4\0\Class 5\0\Class 6\0\Class 7\0\Class 8\0\Class 9\0\Class 10##2");

                            if (ImGui::Button("Apply One", ImVec2(102, 20)))
                            {
                                if (var->Settings.server.reticle)
                                {
                                    char context[255];
                                    char state[255];
                                    int navStringCount = 0;
                                    char* navStrings[16]{};
                                    const char* mode = "";

                                    if (gamemode != 4)
                                    {
                                        if (gamemode == 2)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        else if (gamemode == 0)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        else if (gamemode == 1)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        else if (gamemode == 3)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }
                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                        DDL_GetRootState((__int64)state, ddl_file);
                                        char buffer[200];
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.reticle"), classCombo, wepCombo);
                                        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                        {
                                            DDL_SetInt2((__int64*)&state, (__int64*)&context, retNum);
                                        }
                                    }
                                    else
                                    {
                                        for (int j = 3; j < 7; j++)
                                        {
                                            if (j == 3)
                                            {
                                                mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                            }
                                            else if (j == 5)
                                            {
                                                mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                            }
                                            else if (j == 6)
                                            {
                                                mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                            }
                                            else if (j == 4)
                                            {
                                                mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                            }
                                            __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                            DDL_GetRootState((__int64)state, ddl_file);
                                            char buffer[200];
                                            memset(buffer, 0, 200);
                                            sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.reticle"), classCombo, wepCombo);
                                            ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                            if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                            {
                                                DDL_SetInt2((__int64*)&state, (__int64*)&context, retNum);
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    reo = true;
                                }
                            }
                            ImGui::SameLine();
                            if (ImGui::Button("Apply All", ImVec2(102, 20)))
                            {
                                if (var->Settings.server.reticle)
                                {
                                    for (int i = 0; i < 10; i++)
                                    {
                                        for (int j = 0; j < 2; j++)
                                        {
                                            char context[255];
                                            char state[255];
                                            int navStringCount = 0;
                                            char* navStrings[16]{};
                                            const char* mode = "";

                                            if (gamemode != 4)
                                            {
                                                if (gamemode == 2)
                                                {
                                                    mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                                }
                                                else if (gamemode == 0)
                                                {
                                                    mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                                }
                                                else if (gamemode == 1)
                                                {
                                                    mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                                }
                                                else if (gamemode == 3)
                                                {
                                                    mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                                }
                                                __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                                DDL_GetRootState((__int64)state, ddl_file);
                                                char buffer[200];
                                                memset(buffer, 0, 200);
                                                sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.reticle"), classCombo, wepCombo);
                                                ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                                if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                                {
                                                    DDL_SetInt2((__int64*)&state, (__int64*)&context, retNum);
                                                }
                                            }
                                            else
                                            {
                                                for (int k = 3; k < 7; k++)
                                                {
                                                    if (k == 3)
                                                    {
                                                        mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                                    }
                                                    else if (k == 5)
                                                    {
                                                        mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                                    }
                                                    else if (k == 6)
                                                    {
                                                        mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                                    }
                                                    else if (k == 4)
                                                    {
                                                        mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                                    }
                                                    __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                                    DDL_GetRootState((__int64)state, ddl_file);
                                                    char buffer[200];
                                                    memset(buffer, 0, 200);
                                                    sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.reticle"), classCombo, wepCombo);
                                                    ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                                    if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                                    {
                                                        DDL_SetInt2((__int64*)&state, (__int64*)&context, retNum);
                                                    }
                                                }
                                            }
                                        }

                                    }

                                }
                                else
                                {
                                    reo = true;
                                }
                            }

                        }
  

                    }
                    ImGui::EndGroup();



                }
                ImGui::EndChild(); ImGui::PopStyleColor(4);


                ImGui::SetCursorPos(ImVec2(165, 144));
                if (ImGui::BeginChild("jay=ddd/location", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
                {

                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });

                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {

                        static int stickerNum = 0;
                        static int wepCombo = 0;
                        static int stickerClass = 0;
                        static int stickerSlot = 0;
                        ImGui::SetCursorPosY(21);
                        ImGui::Separator();
                        ImGui::SetCursorPos({ 4, 4 });
                        ImGui::BeginGroup();
                        {
                            subHeaderText("Sticker");
                            ImGui::SetCursorPosY(25);
                            ImGui::PushItemWidth(102);
                            std::vector<std::string> stickers;
                            for (auto const& imap : vector::stickerList)
                                stickers.push_back(imap.first);
                            ImGui::Combo("##stickerc", &stickerNum, stickers);
                            ImGui::SameLine();
                            ImGui::Combo("##stickerslot", &stickerSlot, "Slot 1\0\Slot 2\0\Slot 3\0\Slot 4\000");
                            ImGui::Combo("##gesture", &wepCombo, "Primary\0\Secondary\000");
                            ImGui::SameLine();
                            ImGui::Combo("##charmclass", &stickerClass, "Class 1\0\Class 2\0\Class 3\0\Class 4\0\Class 5\0\Class 6\0\Class 7\0\Class 8\0\Class 9\0\Class 10##2");

                            if (ImGui::Button("Apply One", ImVec2(102, 20)))
                            {
                                if (var->Settings.server.sticker)
                                {
                                    char context[255];
                                    char state[255];
                                    int navStringCount = 0;
                                    char* navStrings[16]{};
                                    const char* mode = "";

                                    if (gamemode != 4)
                                    {
                                        if (gamemode == 2)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        else if (gamemode == 0)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        else if (gamemode == 1)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        else if (gamemode == 3)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }
                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                        DDL_GetRootState((__int64)state, ddl_file);
                                        char buffer[200];
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.sticker.%i"), stickerClass, wepCombo, stickerSlot);
                                        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                        {
                                            DDL_SetInt2((__int64*)&state, (__int64*)&context, stickerNum);
                                        }
                                    }
                                    else
                                    {
                                        for (int j = 3; j < 7; j++)
                                        {
                                            if (j == 3)
                                            {
                                                mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                            }
                                            else if (j == 5)
                                            {
                                                mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                            }
                                            else if (j == 6)
                                            {
                                                mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                            }
                                            else if (j == 4)
                                            {
                                                mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                            }
                                            __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                            DDL_GetRootState((__int64)state, ddl_file);
                                            char buffer[200];
                                            memset(buffer, 0, 200);
                                            sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.sticker.%i"), stickerClass, wepCombo, stickerSlot);
                                            ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                            if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                            {
                                                DDL_SetInt2((__int64*)&state, (__int64*)&context, stickerNum);
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    seo = true;
                                }
                            }
                            ImGui::SameLine();
                            if (ImGui::Button("Apply All", ImVec2(102, 20)))
                            {
                                if (var->Settings.server.sticker)
                                {
                                    for (int i = 0; i < 10; i++)
                                    {
                                        for (int j = 0; j < 2; j++)
                                        {
                                            char context[255];
                                            char state[255];
                                            int navStringCount = 0;
                                            char* navStrings[16]{};
                                            const char* mode = "";

                                            if (gamemode != 4)
                                            {
                                                if (gamemode == 2)
                                                {
                                                    mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                                }
                                                else if (gamemode == 0)
                                                {
                                                    mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                                }
                                                else if (gamemode == 1)
                                                {
                                                    mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                                }
                                                else if (gamemode == 3)
                                                {
                                                    mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                                }
                                                __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                                DDL_GetRootState((__int64)state, ddl_file);
                                                char buffer[200];
                                                memset(buffer, 0, 200);
                                                sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.sticker.%i"), i, j, stickerSlot);
                                                ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                                if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                                {
                                                    DDL_SetInt2((__int64*)&state, (__int64*)&context, stickerNum);
                                                }
                                            }
                                            else
                                            {
                                                for (int k = 3; k < 7; k++)
                                                {
                                                    if (k == 3)
                                                    {
                                                        mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                                    }
                                                    else if (k == 5)
                                                    {
                                                        mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                                    }
                                                    else if (k == 6)
                                                    {
                                                        mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                                    }
                                                    else if (k == 4)
                                                    {
                                                        mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                                    }
                                                    __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                                    DDL_GetRootState((__int64)state, ddl_file);
                                                    char buffer[200];
                                                    memset(buffer, 0, 200);
                                                    sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.sticker.%i"), i, j, stickerSlot);
                                                    ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                                    if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                                    {
                                                        DDL_SetInt2((__int64*)&state, (__int64*)&context, stickerNum);
                                                    }
                                                }
                                            }
                                        }

                                    }

                                }
                                else
                                {
                                    seo = true;
                                }
                            }
                        }
                        ImGui::EndGroup();
                    

                    }
                    ImGui::EndGroup();


                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild(); ImGui::PopStyleColor(4);


                ImGui::SetCursorPos(ImVec2(165, 248));
                if (ImGui::BeginChild("dddddddddddddddd.com", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    static int classnamecombo = 0;
                    static char classname[64];
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {

                        static int gestureCombo = 0;
                        static int gestureNum = 0;
                        ImGui::SetCursorPosY(21);
                        ImGui::Separator();
                        ImGui::SetCursorPos({ 4, 4 });
                        ImGui::BeginGroup();
                        {
                            subHeaderText("Gesture");
                            ImGui::SetCursorPosY(25);
                            ImGui::PushItemWidth(212);
                            static char input[64];
                            custom::combosearch(input, &gestureNum, "Search For Gesture", vector::gestures, vector::gesturesLower, ImVec2(212, 70), false);
                            ImGui::Combo("##gesture", &gestureCombo, "Gesture 1\0\Gesture 2\0\Gesture 3\0\Gesture 4\0\Gesture 5\0\Gesture 6\0\Gesture 7\0\Gesture 8\000");
                            if (ImGui::Button("Set Gesture", ImVec2(212, 20)))
                            {
                                if (var->Settings.server.gesture)
                                {
                                    char context[255];
                                    char state[255];
                                    int navStringCount = 0;
                                    char* navStrings[16]{};
                                    const char* mode = "";

                                    if (gamemode != 4)
                                    {
                                        if (gamemode == 2)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        else if (gamemode == 0)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        else if (gamemode == 1)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        else if (gamemode == 3)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }
                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                        DDL_GetRootState((__int64)state, ddl_file);
                                        char buffer[200];
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, xorstr_("customizationSetup.radial.%i"), gestureCombo);
                                        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                        {
                                            DDL_SetInt2((__int64*)&state, (__int64*)&context, vector::gestureInts[gestureNum]);
                                        }
                                    }
                                    else
                                    {
                                        for (int j = 3; j < 7; j++)
                                        {
                                            if (j == 3)
                                            {
                                                mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                            }
                                            else if (j == 5)
                                            {
                                                mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                            }
                                            else if (j == 6)
                                            {
                                                mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                            }
                                            else if (j == 4)
                                            {
                                                mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                            }
                                            __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                            DDL_GetRootState((__int64)state, ddl_file);
                                            char buffer[200];
                                            memset(buffer, 0, 200);
                                            sprintf_s(buffer, xorstr_("customizationSetup.radial.%i"), gestureCombo);
                                            ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                            if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                            {
                                                DDL_SetInt2((__int64*)&state, (__int64*)&context, vector::gestureInts[gestureNum]);
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    geo = true;
                                }
                            }

                        }ImGui::EndGroup();





                    }
                    ImGui::EndGroup();



                }
                ImGui::EndChild();



                ImGui::SetCursorPos(ImVec2(165, 352));
                if (ImGui::BeginChild("ddd", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    static int clancombo = 0;

                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Clantag");
                        ImGui::SetCursorPosY(25);
                        ImGui::PushItemWidth(212);
                        ImGui::InputTextWithHint("##redtag", "Enter Clan-Tag", var->Settings.c_clantag, sizeof(var->Settings.c_clantag));
                        ImGui::Combo("##redtagcombo", &clancombo, vector::logoTags);
                        DDLValue value;

                        if (ImGui::Button("Set Clan-Tag", ImVec2(212, 22)))
                        {
                            if (var->Settings.server.clan)
                            {
                                CL_PlayerData_SetCustomClanTag("");
                                CL_PlayerData_SetCustomClanTag(var->Settings.c_clantag);
                                if (clancombo == 3)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("iw"));
                                if (clancombo == 4)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("rvn"));
                                if (clancombo == 5)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("shg"));
                                if (clancombo == 6)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("dw"));
                                if (clancombo == 7)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("hms"));
                                if (clancombo == 8)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("bnox"));
                                if (clancombo == 9)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("3arc"));
                                if (clancombo == 10)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("vv"));
                                if (clancombo == 11)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("tfb"));
                                if (clancombo == 12)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("bliz"));
                                if (clancombo == 13)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("king"));
                                if (clancombo == 14)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("ATVI"));
                                if (clancombo == 15)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("LW"));
                                if (clancombo == 16)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("IWDev"));
                                if (clancombo == 17)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("RAVN"));
                                if (clancombo == 18)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("RAVEN"));
                                if (clancombo == 19)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("R4VEN"));
                                if (clancombo == 20)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("OW"));
                                if (clancombo == 21)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("BN0X"));
                                if (clancombo == 22)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("34RC"));
                                if (clancombo == 23)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("1W"));
                                if (clancombo == 24)
                                    CL_PlayerData_SetCustomClanTag(xorstr_("MLG"));
                                if (clancombo == 0)
                                {
                                    value.intValue = 1;
                                }
                                else if (clancombo == 1)
                                {
                                    value.intValue = 3;
                                }
                                else if (clancombo == 2)
                                {
                                    value.intValue = 2;
                                }
                                else
                                {
                                    value.intValue = 1;
                                }
                                if (var->Settings.server.clanColor)
                                    SetDatab("clanTagType", value, STATSGROUP_COMMON);
                            }
                            else
                            {
                                cto = true;
                            }
                        }
                        ImGui::PopItemWidth();
                    }
                    ImGui::EndGroup();

                }ImGui::EndChild();


                ImGui::SetCursorPos(ImVec2(390, 40));
                if (ImGui::BeginChild("daddddddddda", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Operator");
                        ImGui::SetCursorPos(ImVec2(201, 4));
                        ImGui::TextDisabled("(?)");
                        if (ImGui::IsItemHovered())
                        {
                            ImGui::BeginTooltip();
                            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                            ImGui::TextUnformatted("Must Have Default Milsim Operator Equipped");
                            ImGui::PopTextWrapPos();
                            ImGui::EndTooltip();
                        }
                        static int secondarycombo = 0;
                        static char input[64] = { "" };
                        custom::combosearch(input, &secondarycombo, "Search For Operator", vector::opList, vector::opListLower, ImVec2(212, 70), true);
                        ImGui::PopStyleColor(3);
                        ImGui::SetCursorPosY(48);
                        if (ImGui::InputInt("##operatorinput", &var->Settings.cfg.i_savedop, 1, 100, ImGuiInputTextFlags_AutoSelectAll))
                        {
                            memset(input, NULL, sizeof(NULL));
                        }


                        ImGui::SetCursorPosY(72);
                        if (ImGui::Button("Set Coalition", ImVec2(102, 22)))
                        {
                            if (var->Settings.server.operator1)
                            {
                                char context[255];
                                char state[255];
                                int string_count;
                                char* str[16]{};
                                const char* mode = "";
                                char buffer[200];

                                if (gamemode != 4)
                                {
                                    if (gamemode == 0)
                                    {
                                        mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                    }
                                    else if (gamemode == 1)
                                    {
                                        mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                    }
                                    else if (gamemode == 2)
                                    {
                                        mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                    }
                                    else if (gamemode == 3)
                                    {
                                        mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                    }
                                    __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                    DDL_GetRootState((__int64)state, ddl_file);
                                    memset(buffer, 0, 200);
                                    sprintf_s(buffer, xorstr_("customizationSetup.operatorCustomization.default_western.skin"));
                                    ParseShitt(buffer, (const char**)str, 16, &string_count);
                                    if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
                                    {
                                        if (var->Settings.cfg.i_savedop != 0)
                                            DDL_SetInt((__int64)state, (__int64)context, var->Settings.cfg.i_savedop);
                                        else
                                            DDL_SetInt((__int64)state, (__int64)context, var->Settings.cfg.i_savedop);
                                    }
                                }
                                else
                                {
                                    for (int j = 3; j < 7; j++)
                                    {
                                        if (j == 5)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        else if (j == 6)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        else if (j == 3)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        else if (j == 4)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }
                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                        DDL_GetRootState((__int64)state, ddl_file);
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, xorstr_("customizationSetup.operatorCustomization.default_western.skin"));
                                        ParseShitt(buffer, (const char**)str, 16, &string_count);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
                                        {
                                            if (var->Settings.cfg.i_savedop != 0)
                                                DDL_SetInt((__int64)state, (__int64)context, var->Settings.cfg.i_savedop);
                                            else
                                                DDL_SetInt((__int64)state, (__int64)context, var->Settings.cfg.i_savedop);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                opo = true;
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Set Allegiance", ImVec2(102, 22)))
                        {
                            if (var->Settings.server.operator1)
                            {
                                char context[255];
                                char state[255];
                                int string_count;
                                char* str[16]{};
                                const char* mode = "";
                                char buffer[200];

                                if (gamemode != 4)
                                {
                                    if (gamemode == 0)
                                    {
                                        mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                    }
                                    else if (gamemode == 1)
                                    {
                                        mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                    }
                                    else if (gamemode == 2)
                                    {
                                        mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                    }
                                    else if (gamemode == 3)
                                    {
                                        mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                    }
                                    __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                    DDL_GetRootState((__int64)state, ddl_file);
                                    memset(buffer, 0, 200);
                                    sprintf_s(buffer, xorstr_("customizationSetup.operatorCustomization.default_eastern.skin"));
                                    ParseShitt(buffer, (const char**)str, 16, &string_count);
                                    if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
                                    {
                                        if (var->Settings.cfg.i_savedop != 0)
                                            DDL_SetInt((__int64)state, (__int64)context, var->Settings.cfg.i_savedop);
                                        else
                                            DDL_SetInt((__int64)state, (__int64)context, var->Settings.cfg.i_savedop);
                                    }
                                }
                                else
                                {
                                    for (int j = 3; j < 7; j++)
                                    {
                                        if (j == 5)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        else if (j == 6)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        else if (j == 3)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        else if (j == 4)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }
                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                        DDL_GetRootState((__int64)state, ddl_file);
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, xorstr_("customizationSetup.operatorCustomization.default_eastern.skin"));
                                        ParseShitt(buffer, (const char**)str, 16, &string_count);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, string_count, (const char**)str))
                                        {
                                            if (var->Settings.cfg.i_savedop != 0)
                                                DDL_SetInt((__int64)state, (__int64)context, var->Settings.cfg.i_savedop);
                                            else
                                                DDL_SetInt((__int64)state, (__int64)context, var->Settings.cfg.i_savedop);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                opo = true;
                            }
                        }
                    }
                    ImGui::EndGroup();

                }ImGui::EndChild();


                ImGui::SetCursorPos(ImVec2(390, 248));
                if (ImGui::BeginChild("daddddadadavvddddda", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });


                    static int charmNum = 0;
                    static int wepCombo = 0;
                    static int charmClass = 0;
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Charm");
                        ImGui::SetCursorPosY(25);
                        ImGui::PushItemWidth(212);
                        std::vector<std::string> charms;
                        for (auto const& imap : vector::charmList)
                            charms.push_back(imap.first);
                        ImGui::Combo("##charmc", &charmNum, charms);
                        ImGui::PushItemWidth(102);
                        ImGui::Combo("##charmwep", &wepCombo, "Primary\0\Secondary\000");
                        ImGui::SameLine();
                        ImGui::Combo("##charmclass", &charmClass, "Class 1\0\Class 2\0\Class 3\0\Class 4\0\Class 5\0\Class 6\0\Class 7\0\Class 8\0\Class 9\0\Class 10##2");

                        if (ImGui::Button("Apply One", ImVec2(102, 20)))
                        {
                            if (var->Settings.server.charm)
                            {
                                char context[255];
                                char state[255];
                                int navStringCount = 0;
                                char* navStrings[16]{};
                                const char* mode = "";

                                if (gamemode != 4)
                                {
                                    if (gamemode == 2)
                                    {
                                        mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                    }
                                    else if (gamemode == 0)
                                    {
                                        mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                    }
                                    else if (gamemode == 1)
                                    {
                                        mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                    }
                                    else if (gamemode == 3)
                                    {
                                        mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                    }
                                    __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                    DDL_GetRootState((__int64)state, ddl_file);
                                    char buffer[200];
                                    memset(buffer, 0, 200);
                                    sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.cosmeticAttachment"), charmClass, wepCombo);
                                    ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                    if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                    {
                                        DDL_SetInt2((__int64*)&state, (__int64*)&context, charmNum);
                                    }
                                }
                                else
                                {
                                    for (int j = 3; j < 7; j++)
                                    {
                                        if (j == 3)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        else if (j == 5)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        else if (j == 6)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        else if (j == 4)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }
                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                        DDL_GetRootState((__int64)state, ddl_file);
                                        char buffer[200];
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.cosmeticAttachment"), charmClass, wepCombo);
                                        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                        {
                                            DDL_SetInt2((__int64*)&state, (__int64*)&context, charmNum);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                ceo = true;
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Apply All", ImVec2(102, 20)))
                        {
                            if (var->Settings.server.charm)
                            {
                                for (int i = 0; i < 10; i++)
                                {
                                    for (int j = 0; j < 2; j++)
                                    {
                                        char context[255];
                                        char state[255];
                                        int navStringCount = 0;
                                        char* navStrings[16]{};
                                        const char* mode = "";

                                        if (gamemode != 4)
                                        {
                                            if (gamemode == 2)
                                            {
                                                mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                            }
                                            else if (gamemode == 0)
                                            {
                                                mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                            }
                                            else if (gamemode == 1)
                                            {
                                                mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                            }
                                            else if (gamemode == 3)
                                            {
                                                mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                            }
                                            __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                            DDL_GetRootState((__int64)state, ddl_file);
                                            char buffer[200];
                                            memset(buffer, 0, 200);
                                            sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.cosmeticAttachment"), i, j);
                                            ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                            if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                            {
                                                DDL_SetInt2((__int64*)&state, (__int64*)&context, charmNum);
                                            }
                                        }
                                        else
                                        {
                                            for (int k = 3; k < 7; k++)
                                            {
                                                if (k == 3)
                                                {
                                                    mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                                }
                                                else if (k == 5)
                                                {
                                                    mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                                }
                                                else if (k == 6)
                                                {
                                                    mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                                }
                                                else if (k == 4)
                                                {
                                                    mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                                }
                                                __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                                DDL_GetRootState((__int64)state, ddl_file);
                                                char buffer[200];
                                                memset(buffer, 0, 200);
                                                sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.cosmeticAttachment"), i, j);
                                                ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                                if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                                {
                                                    DDL_SetInt2((__int64*)&state, (__int64*)&context, charmNum);
                                                }
                                            }
                                        }
                                    }

                                }

                            }
                            else
                            {
                                ceo = true;
                            }
                        }
                    }
                    ImGui::EndGroup();




                }ImGui::EndChild();





                ImGui::SetCursorPos(ImVec2(390, 144));
                if (ImGui::BeginChild("daddddadadadccaaaavvddddda", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Modded Weapons");
                        ImGui::SetCursorPosY(25);
                        static char moddedName[255];
                        const char* moddedGunList[12] = { "M4A1","AK47","MP5" ,"M13" ,"KILO" ,"FENNEC" ,"HDR" ,"SPR" ,"RYTEC" ,"SYKOV" ,"CX-9" ,"GRAU" };
                        const char* moddedCamoList[22] = { "MW Gold", "MW Platinum", "MW Damascus", "MW Obsidian",  "CW Gold", "CW Diamond", "CW DM-Ultra", "CW ZM Gold", "CW ZM Diamond", "CW ZM Dark Aether", "CW Cherry Blossom", "VG Gold", "VG Diamond", "VG Atomic", "VG ZM Gold", "VG ZM Diamond", "VG ZM Dark Aether", "VG False Prospector", "VG Death Prospector", "VG Titanium Chrome ", "VG Liquid Metal ", "VG Skynet" };
                        ImGui::PushItemWidth(102);
                        ImGui::InputTextWithHint(xorstr_("##moddedgunname"), xorstr_("Enter BP Name"), moddedName, IM_ARRAYSIZE(moddedName));
                        ImGui::SameLine();
                        ImGui::Combo(xorstr_("##moddedbpcombo1"), &moddedGunCombo, moddedGunList, IM_ARRAYSIZE(moddedGunList));
                        ImGui::PushItemWidth(212);
                        ImGui::Combo(xorstr_("##moddedbpcombo2"), &moddedCamoCombo, moddedCamoList, IM_ARRAYSIZE(moddedCamoList));

                        if (ImGui::Button(xorstr_("Save Gun"), ImVec2(212, 20)))
                        {
                            if (var->Settings.server.modweapon)
                            {
                                char buf_weapon[255];
                                char buf_selected_camo[255];
                                char buf_gunsmith_name[255];
                                char buf_name[255];
                                char buf_camo[255];
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
                                DDLValue value;

                                sprintf_s(buf_name, xorstr_("%s%s"), xorstr_("000"), moddedName);

                                sprintf_s(buf_camo, xorstr_("%s"), camo_id_list[moddedCamoCombo]);

                                switch (moddedGunCombo)
                                {
                                case 0:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_ar_mike4.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_ar_mike4.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_ar_mike4";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_mike4.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barsil";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_mike4.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "silencer3";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_mike4.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;

                                case 1:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_ar_akilo47.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_ar_akilo47.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_ar_akilo47";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_akilo47.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barcustnoguard";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_akilo47.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "gripvert";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_akilo47.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                case 2:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_sm_mpapa5.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_sm_mpapa5.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_sm_mpapa5";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sm_mpapa5.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barsil";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sm_mpapa5.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "silencer3";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sm_mpapa5.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                case 3:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_ar_mcharlie.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_ar_mcharlie.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_ar_mcharlie";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_mcharlie.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barsil";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_mcharlie.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "silencer3";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_mcharlie.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                case 4:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_ar_kilo433.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_ar_kilo433.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_ar_kilo433";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_kilo433.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barsil";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_kilo433.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "silencer3";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_kilo433.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                case 5:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_sm_victor.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_sm_victor.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_sm_victor";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sm_victor.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barsil";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sm_victor.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "silencer3";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sm_victor.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                case 6:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_sn_hdromeo.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_sn_hdromeo.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_sn_hdromeo";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sn_hdromeo.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barsil";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sn_hdromeo.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "silencer3";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sn_hdromeo.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                case 7:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_sn_romeo700.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_sn_romeo700.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_sn_romeo700";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sn_romeo700.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barsil";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sn_romeo700.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "silencer3";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sn_romeo700.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                case 8:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_sn_xmike109.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_sn_xmike109.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_sn_xmike109";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sn_xmike109.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barsil";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sn_xmike109.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "silencer3";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sn_xmike109.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                case 9:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_pi_mike.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_pi_mike.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_pi_mike";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_pi_mike.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barsil";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_pi_mike.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "choke";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_pi_mike.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                case 10:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_sm_secho.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_sm_secho.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_sm_secho";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sm_secho.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barsil";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sm_secho.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "silencer3";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_sm_secho.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                case 11:
                                    value.stringPtr = buf_name;
                                    sprintf_s(buf_gunsmith_name, xorstr_("blueprints.iw8_ar_sierra552.weaponSetup.0.blueprintName"));
                                    SetData(buf_gunsmith_name, value);

                                    value.stringPtr = buf_camo;
                                    sprintf_s(buf_selected_camo, xorstr_("blueprints.iw8_ar_sierra552.weaponSetup.0.camo"));
                                    SetData(buf_selected_camo, value);

                                    value.stringPtr = "iw8_ar_sierra552";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_sierra552.weaponSetup.0.weapon"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "barshort";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_sierra552.weaponSetup.0.attachmentSetup.0.attachment"));
                                    SetData(buf_weapon, value);

                                    value.stringPtr = "gripvert";
                                    sprintf_s(buf_weapon, xorstr_("blueprints.iw8_ar_sierra552.weaponSetup.0.attachmentSetup.1.attachment"));
                                    SetData(buf_weapon, value);
                                    break;
                                }
                                *(BYTE*)(var->baseModule + var->Offest.uploadbps) = 1;
                            }
                            else
                            {
                                mwo = true;
                            }
                        }
                    }
                    ImGui::EndGroup();







                }ImGui::EndChild();




                ImGui::SetCursorPos(ImVec2(615, 144));
                if (ImGui::BeginChild("daddddadadadccaaaavvdddddaccaaazz", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });



                    static int classcombo = 0;
                    static int primarycombo = 0;
                    static int secondarycombo = 0;
                    static char searchbuf[128];
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Camoflauge");
                        ImGui::SetCursorPosY(25);

                        ImGui::PushItemWidth(212);
                        custom::combosearch(searchbuf, &secondarycombo, "Search For Camo", vector::camoswapList, vector::camoswapListLower, ImVec2(212, 70));
                        ImGui::SetCursorPosY(50);
                        ImGui::PushItemWidth(102);
                        ImGui::Combo("##classcombo", &classcombo, "Class 1\0\Class 2\0\Class 3\0\Class 4\0\Class 5\0\Class 6\0\Class 7\0\Class 8\0\Class 9\0\Class 10");
                        ImGui::SameLine();
                        ImGui::Combo("##primarycombo", &primarycombo, "Primary\0\Secondary\0");
                        ImGui::PopItemWidth();
                        ImGui::SetCursorPosY(75);
                        if (ImGui::Button("Set Camo", ImVec2(102, 20)))
                        {
                            if (var->Settings.server.camo)
                            {
                                char context[255];
                                char state[255];
                                int navStringCount;
                                char* navStrings[16]{};
                                const char* mode = "";

                                if (gamemode != 4)
                                {
                                    if (gamemode == 0)
                                    {
                                        mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                    }
                                    if (gamemode == 1)
                                    {
                                        mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                    }
                                    if (gamemode == 2)
                                    {
                                        mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                    }
                                    if (gamemode == 3)
                                    {
                                        mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                    }


                                    __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);

                                    DDL_GetRootState((__int64)state, ddl_file);
                                    char buffer[200];
                                    memset(buffer, 0, 200);
                                    sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.camo"), classcombo, primarycombo);
                                    ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                    if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                    {
                                        DDL_SetInt((__int64)state, (__int64)context, vector::camoswapListInt[secondarycombo]);
                                    }
                                }
                                else
                                {
                                    for (int j = 3; j < 7; j++)
                                    {
                                        if (j == 5)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        if (j == 6)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        if (j == 3)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        if (j == 4)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }

                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);

                                        DDL_GetRootState((__int64)state, ddl_file);
                                        char buffer[200];
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.camo"), classcombo, primarycombo);
                                        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                        {
                                            DDL_SetInt((__int64)state, (__int64)context, vector::camoswapListInt[secondarycombo]);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                cao = true;
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Apply All##3", ImVec2(102, 20)))
                        {
                            if (var->Settings.server.camo)
                            {
                                char context[255];
                                char state[255];
                                int navStringCount;
                                char* navStrings[16]{};
                                const char* mode = "";

                                for (int classindex = 0; classindex < 10; classindex++)
                                {
                                    for (int weaponindex = 0; weaponindex < 2; weaponindex++)
                                    {
                                        if (gamemode != 4)
                                        {
                                            if (gamemode == 0)
                                            {
                                                mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                            }
                                            else if (gamemode == 1)
                                            {
                                                mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                            }
                                            else if (gamemode == 2)
                                            {
                                                mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                            }
                                            else if (gamemode == 3)
                                            {
                                                mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                            }

                                            __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);

                                            DDL_GetRootState((__int64)state, ddl_file);
                                            char buffer[200];
                                            memset(buffer, 0, 200);
                                            sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.camo"), classindex, weaponindex);
                                            ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                            if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                            {
                                                DDL_SetInt((__int64)state, (__int64)context, vector::camoswapListInt[secondarycombo]);
                                            }
                                        }
                                        else
                                        {
                                            for (int j = 3; j < 7; j++)
                                            {
                                                if (j == 5)
                                                {
                                                    mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                                }
                                                else if (j == 6)
                                                {
                                                    mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                                }
                                                else if (j == 3)
                                                {
                                                    mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                                }
                                                else if (j == 4)
                                                {
                                                    mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                                }

                                                __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);

                                                DDL_GetRootState((__int64)state, ddl_file);
                                                char buffer[200];
                                                memset(buffer, 0, 200);
                                                sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.camo"), classindex, weaponindex);
                                                ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                                if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                                {
                                                    DDL_SetInt((__int64)state, (__int64)context, vector::camoswapListInt[secondarycombo]);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                cao = true;
                            }
                        }
                    }
                    ImGui::EndGroup();





                }ImGui::EndChild();






                ImGui::SetCursorPos(ImVec2(390, 352));
                if (ImGui::BeginChild("adadaccaaa", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });


                    static int eqclasscombo = 0;
                    static int slotcombo = 0;
                    static int fillcombo = 0;
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Equipment");
                        ImGui::SetCursorPosY(25);

                        ImGui::PushItemWidth(102);
                        ImGui::Combo("##eqclasscombo", &eqclasscombo, "Class 1\0\Class 2\0\Class 3\0\Class 4\0\Class 5\0\Class 6\0\Class 7\0\Class 8\0\Class 9\0\Class 10\0");
                        ImGui::SameLine();
                        ImGui::Combo("##slotcombo", &slotcombo, "Lethal\0\Tactical\0");
                        ImGui::PushItemWidth(212);
                        ImGui::Combo("##fillcombo", &fillcombo, "Frag\0\Semtex\0\C4\0\Throwing Knife\0\Claymore\0\Molotov\0\Thermite\0\Proximity Mine\0\Pop Rocket\0\Ballistic Helmet\0\Flash Grenade\0\Smoke Grenade\0\Stun Grenade\0\Stim\0\Trophy System\0\Snap Shot Grenade\0\Decoy Grenade\0\Deployable Cover\0\Buy Station Marker\0\Chaff Grenade\0\Tac Insert\0\Gas Grenade\0\Heartbeat Sensor\0\Rock\0\Flaming Throwing Knife\0\EHV Throwing Knife\0\Phlebotomist Throwing Knife\0\Radiation Counter\0\Snowball\0\Radar Jammer\0\P.D.S");
                        if (ImGui::Button("Set Equipment", ImVec2(212, 20)))
                        {
                            if (var->Settings.server.equip)
                            {
                                char context[255];
                                char state[255];
                                int navStringCount;
                                char* navStrings[16]{};
                                const char* mode = "";

                                if (gamemode != 4)
                                {
                                    if (gamemode == 0)
                                    {
                                        mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                    }
                                    else if (gamemode == 1)
                                    {
                                        mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                    }
                                    else if (gamemode == 2)
                                    {
                                        mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                    }
                                    else if (gamemode == 3)
                                    {
                                        mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                    }

                                    __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);

                                    DDL_GetRootState((__int64)state, ddl_file);
                                    char buffer[200];
                                    memset(buffer, 0, 200);
                                    sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.equipmentSetups.%i.equipment"), eqclasscombo, slotcombo);
                                    ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                    if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                    {
                                        DDL_SetInt((__int64)state, (__int64)context, vector::equipListInt[fillcombo]);
                                    }
                                }
                                else
                                {
                                    for (int j = 3; j < 7; j++)
                                    {
                                        if (j == 5)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        else if (j == 6)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        else if (j == 3)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        else if (j == 4)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }

                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);

                                        DDL_GetRootState((__int64)state, ddl_file);
                                        char buffer[200];
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.equipmentSetups.%i.equipment"), eqclasscombo, slotcombo);
                                        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                        {
                                            DDL_SetInt((__int64)state, (__int64)context, vector::equipListInt[fillcombo]);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                emo = true;
                            }
                        }
                        ImGui::PopItemWidth();
                    }
                    ImGui::EndGroup();
                






                }ImGui::EndChild();






                ImGui::SetCursorPos(ImVec2(615, 40));
                if (ImGui::BeginChild("double", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });



                    static int doubleweaponcombo = 0;
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Double Weapons");
                        ImGui::SetCursorPosY(25);
                        ImGui::PushItemWidth(212);
                        ImGui::Combo("##doublweapon", &doubleweaponcombo, xorstr_("Class 1\0\Class 2\0\Class 3\0\Class 4\0\Class 5\0\Class 6\0\Class 7\0\Class 8\0\Class 9\0\Class 10##1"));
                        if (ImGui::Button("Apply One##1", ImVec2(212, 20)))
                        {
                            if (var->Settings.server.dblweapon)
                            {
                                if (gamemode == 4)
                                {
                                    for (int j = 0; j < 4; j++)
                                    {
                                        dblgnuns::doublegunsget(doubleweaponcombo, j);
                                        dblgnuns::dblgunsset(doubleweaponcombo, j);
                                    }
                                }
                                else
                                {
                                    dblgnuns::doublegunsget(doubleweaponcombo, gamemode);
                                    dblgnuns::dblgunsset(doubleweaponcombo, gamemode);
                                }
                            }
                            else
                            {
                                dwo = true;
                            }
                        }
                        if (ImGui::Button("Apply All##1", ImVec2(212, 20)))
                        {
                            if (var->Settings.server.dblweapon)
                            {
                                for (int i = 0; i < 10; i++)
                                {
                                    if (gamemode == 4)
                                    {
                                        for (int j = 0; j < 4; j++)
                                        {
                                            dblgnuns::doublegunsget(i, j);
                                            dblgnuns::dblgunsset(i, j);
                                        }
                                    }
                                    else
                                    {
                                        dblgnuns::doublegunsget(i, gamemode);
                                        dblgnuns::dblgunsset(i, gamemode);
                                    }

                                }
                            }
                            else
                            {
                                dwo = true;
                            }
                        }
                        ImGui::PopItemWidth();
                    }
                    ImGui::EndGroup();






                }ImGui::EndChild();




                ImGui::SetCursorPos(ImVec2(615, 248));
                if (ImGui::BeginChild("gayclass", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });


                    static int classnamecombo = 0;
                    static char classname[64];
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Class Name");
                        ImGui::SetCursorPosY(25);

                        ImGui::PushItemWidth(212);
                        ImGui::InputTextWithHint("##customclass", "Enter Name", classname, 64);
                        ImGui::Combo("##classname", &classnamecombo, "Class 1\0\Class 2\0\Class 3\0\Class 4\0\Class 5\0\Class 6\0\Class 7\0\Class 8\0\Class 9\0\Class 10##2");
                        if (ImGui::Button("Apply One##2", ImVec2(102, 20)))
                        {
                            if (var->Settings.server.classname)
                            {
                                char context[255];
                                char state[255];
                                int navStringCount;
                                char* navStrings[16]{};
                                const char* mode = "";

                                if (gamemode != 4)
                                {
                                    if (gamemode == 0)
                                    {
                                        mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                    }
                                    if (gamemode == 1)
                                    {
                                        mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                    }
                                    if (gamemode == 2)
                                    {
                                        mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                    }
                                    if (gamemode == 3)
                                    {
                                        mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                    }


                                    __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);

                                    DDL_GetRootState((__int64)state, ddl_file);
                                    char buffer[200];
                                    memset(buffer, 0, 200);
                                    sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.name"), classnamecombo);
                                    ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                    if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                    {
                                        DDL_SetString((__int64)state, (__int64)context, classname);
                                    }
                                }
                                else
                                {
                                    for (int j = 3; j < 7; j++)
                                    {
                                        if (j == 5)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        if (j == 6)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        if (j == 3)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        if (j == 4)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }

                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);

                                        DDL_GetRootState((__int64)state, ddl_file);
                                        char buffer[200];
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.name"), classnamecombo);
                                        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                        {
                                            DDL_SetString((__int64)state, (__int64)context, classname);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                cno = true;
                            }
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Apply All##2", ImVec2(102, 20)))
                        {
                            if (var->Settings.server.classname)
                            {
                                char context[255];
                                char state[255];
                                int navStringCount;
                                char* navStrings[16]{};
                                const char* mode = "";

                                for (int classindex = 0; classindex < 10; classindex++)
                                {
                                    if (gamemode != 4)
                                    {
                                        if (gamemode == 0)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        if (gamemode == 1)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        if (gamemode == 2)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        if (gamemode == 3)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }

                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                        DDL_GetRootState((__int64)state, ddl_file);
                                        char buffer[200];
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.name"), classindex);
                                        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                        {
                                            DDL_SetString((__int64)state, (__int64)context, classname);
                                        }
                                    }
                                    else
                                    {
                                        for (int j = 3; j < 7; j++)
                                        {
                                            if (j == 5)
                                            {
                                                mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                            }
                                            if (j == 6)
                                            {
                                                mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                            }
                                            if (j == 3)
                                            {
                                                mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                            }
                                            if (j == 4)
                                            {
                                                mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                            }

                                            __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                            DDL_GetRootState((__int64)state, ddl_file);
                                            char buffer[200];
                                            memset(buffer, 0, 200);
                                            sprintf_s(buffer, xorstr_("squadMembers.loadouts.%i.name"), classindex);
                                            ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                            if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                            {
                                                DDL_SetString((__int64)state, (__int64)context, classname);
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                cno = true;
                            }
                        }
                        ImGui::PopItemWidth();
                    }
                    ImGui::EndGroup();




                }ImGui::EndChild();






                ImGui::SetCursorPos(ImVec2(615, 352));
                if (ImGui::BeginChild("wataches", ImVec2(220, 99), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });


                    static int watchNum = 0;
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 4, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Watch");
                        ImGui::SetCursorPosY(25);
                        ImGui::PushItemWidth(212);
                        std::vector<std::string> watches;
                        for (auto const& imap : vector::watchList)
                            watches.push_back(imap.first);
                        ImGui::Combo("##watchc", &watchNum, watches);
                        ImGui::Dummy(ImVec2(0, 20));
                        if (ImGui::Button("Set Watch", ImVec2(212, 20)))
                        {
                            if (var->Settings.server.watch)
                            {
                                char context[255];
                                char state[255];
                                int navStringCount = 0;
                                char* navStrings[16]{};
                                const char* mode = "";

                                if (gamemode != 4)
                                {
                                    if (gamemode == 2)
                                    {
                                        mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                    }
                                    else if (gamemode == 0)
                                    {
                                        mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                    }
                                    else if (gamemode == 1)
                                    {
                                        mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                    }
                                    else if (gamemode == 3)
                                    {
                                        mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                        CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                    }
                                    __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                    DDL_GetRootState((__int64)state, ddl_file);
                                    char buffer[200];
                                    memset(buffer, 0, 200);
                                    sprintf_s(buffer, ("customizationSetup.operatorWatch"));
                                    ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                    if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                    {
                                        DDL_SetInt2((__int64*)&state, (__int64*)&context, watchNum);
                                    }
                                }
                                else
                                {
                                    for (int j = 3; j < 7; j++)
                                    {
                                        if (j == 3)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        else if (j == 5)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        else if (j == 6)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        else if (j == 4)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }
                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                        DDL_GetRootState((__int64)state, ddl_file);
                                        char buffer[200];
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, ("customizationSetup.operatorWatch"));
                                        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                        {
                                            DDL_SetInt2((__int64*)&state, (__int64*)&context, watchNum);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                weo = true;
                            }
                        }
                    }
                    ImGui::EndGroup();





                }ImGui::EndChild();

            }


            if (Tabs == 3)
            {
                ImGui::SetCursorPos(ImVec2(390, 5));
                ImGui::PushStyleColor(ImGuiCol_Text, ImColor(78, 78, 78).Value);
                ImGui::Text("PAIO");
                ImGui::PopStyleColor();

                ImGui::SetCursorPos(ImVec2(165, 40));
                if (ImGui::BeginChild("gagagga/location", ImVec2(310, 190), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("ESP ON/OFF");
                        ImGui::SetCursorPosY(29);


                        ToggleNL("Enable ESP/Chams", &var->Settings.chams, TRUE);
                        ToggleNL("Loot ESP/Chams", &var->Settings.lootChams, TRUE);
                        ToggleNL("Fill Outlines", &var->Settings.chamFill, TRUE);



                    }
                    ImGui::EndGroup();

                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild(); ImGui::PopStyleColor(4);


                ImGui::SetCursorPos(ImVec2(495, 40));
                if (ImGui::BeginChild("jay=gaggdaddy/location", ImVec2(310, 190), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
                {

                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("ESP Settings");

                        ImGui::PushItemWidth(181);
                        ImGui::SetCursorPosY(29);

                        ToggleNL("RGB Player", &var->Settings.rgbChams, TRUE); ImGui::SameLine(170);
                        ImGui::ColorEdit4("Player Color", (float*)&player_colorVec4, NO_ALPHA);
                        ToggleNL("RGB Loot", &var->Settings.rgblootChams, TRUE); ImGui::SameLine(170);
                        ImGui::ColorEdit4("Loot Color", (float*)&item_colorVec4, NO_ALPHA);
                        var->Settings.playerColor = ImGui::ColorConvertFloat4ToU32(player_colorVec4);
                        var->Settings.lootColor = ImGui::ColorConvertFloat4ToU32(item_colorVec4);


                    }
                    ImGui::EndGroup();


                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild(); ImGui::PopStyleColor(4);


                ImGui::SetCursorPos(ImVec2(165, 255));
                if (ImGui::BeginChild("dddaaaaaaaaa.com", ImVec2(310, 190), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("ESP Distance");

                        ImGui::PushItemWidth(181);
                        ImGui::SetCursorPosY(29);


                        ImGui::SliderInt("Line Width", &var->Settings.lineWidthNum, 1, 10);
                        ImGui::SliderInt("Render Type", &var->Settings.rendertype, 0, 1000);


                    }
                    ImGui::EndGroup();


                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild();


                ImGui::SetCursorPos(ImVec2(495, 255));
                if (ImGui::BeginChild("dddaaaaaaaaaaaaaaaaaaaaaaaa.com", ImVec2(310, 190), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Visble Check");

                        ImGui::PushItemWidth(181);
                        ImGui::SetCursorPosY(29);

                        ToggleNL("Visible Check", &var->Settings.visibleOutlines, TRUE);
                        ToggleNL("Non-Visible Check", &var->Settings.notVisibleOutlines, TRUE);



                    }
                    ImGui::EndGroup();


                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild();

            }



            if (Tabs == 4)
            {


                ImGui::SetCursorPos(ImVec2(390, 5));
                ImGui::PushStyleColor(ImGuiCol_Text, ImColor(78, 78, 78).Value);
                ImGui::Text("PAIO");
                ImGui::PopStyleColor();

                ImGui::SetCursorPos(ImVec2(165, 40));
                if (ImGui::BeginChild("gagagga/location", ImVec2(310, 405), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Player Options");
                        ImGui::SetCursorPosY(29);


                        static bool prone;
                        static int pronef;
                        static bool niggaf;

                        ImGui::Checkbox("No Gun", &var->Settings.b_gun);

                        ImGui::Checkbox("No Shield Shake", &var->Settings.b_shield);
                        ImGui::Checkbox("Heartcheat", &var->Settings.b_heart);
                        ImGui::Checkbox("Remove Crosshair", &var->Settings.b_nocrosshair);
                        ImGui::Checkbox("Break Camera", &var->Settings.b_fuckview);
                        ImGui::Checkbox("Skip Tutorial", &var->Settings.b_tut);


                        ImGui::Checkbox("Third Person", &var->Settings.b_Thirdperson);
                        ImGui::Checkbox("Dynamic Third Person", &var->Settings.b_dynamic3p);
                        ImGui::Checkbox(xorstr_("Force MP Loadouts"), &var->Settings.b_mploadout);
 
                        ImGui::Checkbox("Disable Loot Checks", &var->Settings.b_owner);
                        ImGui::Checkbox("Disable Shellshock", &var->Settings.shellhook);
                        ImGui::Checkbox("Prone Fly", &prone);
                        if (prone)
                        {
                            if (ImGui::SliderInt("##prone", &pronef, 1, 10000))
                                dvar_set2("MMSRPNPNON", pronef);
                        }


                    }
                    ImGui::EndGroup();

                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild(); ImGui::PopStyleColor(4);


                ImGui::SetCursorPos(ImVec2(500, 40));
                if (ImGui::BeginChild("jay=gaggdaddy/location", ImVec2(310, 190), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
                {

                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Game Options");

                        ImGui::PushItemWidth(181);
                        ImGui::SetCursorPosY(29);



                        ImGui::Checkbox("No Fog", &var->Settings.b_no_fog);
                        ImGui::Checkbox("Max Bright", &var->Settings.b_brightmax);
                        ImGui::Checkbox("FPS Boost", &var->Settings.b_fps);
                        ImGui::Checkbox("Dev Playlist", &var->Settings.b_playlist);

                    }
                    ImGui::EndGroup();


                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild(); ImGui::PopStyleColor(4);




                ImGui::SetCursorPos(ImVec2(500, 255));
                if (ImGui::BeginChild("dddaaaaaaaaaaaaaaaaaaaaaaaa.com", ImVec2(310, 190), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("PC Options");

                        ImGui::PushItemWidth(181);
                        ImGui::SetCursorPosY(29);


                        ImGui::Checkbox("Crosshair", &var->Settings.chrosshair);
                        ImGui::Checkbox("Draw FPS", &var->Settings.b_fpss);

                    }
                    ImGui::EndGroup();


                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild();



            }


            if (Tabs == 5)
            {


                ImGui::SetCursorPos(ImVec2(390, 5));
                ImGui::PushStyleColor(ImGuiCol_Text, ImColor(78, 78, 78).Value);
                ImGui::Text("PAIO");
                ImGui::PopStyleColor();

                ImGui::SetCursorPos(ImVec2(165, 40));
                if (ImGui::BeginChild("gagagga/location", ImVec2(310, 405), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
                {


                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("KeyBinds");
                        ImGui::SetCursorPosY(24);
                        ImGui::BeginGroup();
                        {
                            ImGui::PushFont(mainfontBig);
                            ImGui::Text("Disable Keybinds: ");
                            ImGui::PopFont();
                            ImGui::SetCursorPos(ImVec2(155, 25));
                            {
                                static int* key = 0;
                                static bool keyButtonClicked = false;
                                const char* pressKey = "...";
                                std::string currentKey = keyIntToString(var->Settings.cfg.i_disablekey);
                                if (keyButtonClicked)
                                {
                                    if (ImGui::Button(pressKey, ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;

                                    isKeyPressed(&var->Settings.cfg.i_disablekey, &keyButtonClicked, &currentKey);
                                }
                                else
                                {
                                    if (ImGui::Button(currentKey.c_str(), ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;
                                }
                            }
                            ImGui::PushFont(mainfontBig);
                            ImGui::Text("Eject Tool: ");
                            ImGui::PopFont();
                            ImGui::SetCursorPos(ImVec2(155, 50));
                            {
                                static int* key = 0;
                                static bool keyButtonClicked = false;
                                const char* pressKey = "...";
                                std::string currentKey = keyIntToString(var->Settings.cfg.i_ejectkey);
                                if (keyButtonClicked)
                                {
                                    if (ImGui::Button(pressKey, ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;

                                    isKeyPressed(&var->Settings.cfg.i_ejectkey, &keyButtonClicked, &currentKey);
                                }
                                else
                                {
                                    if (ImGui::Button(currentKey.c_str(), ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;
                                }
                            }
                            ImGui::PushFont(mainfontBig);
                            ImGui::Text("Menu Key 1: ");
                            ImGui::PopFont();
                            ImGui::SetCursorPos(ImVec2(155, 75));
                            {
                                static int* key = 0;
                                static bool keyButtonClicked = false;
                                const char* pressKey = "...";
                                std::string  currentKey = keyIntToString(var->Settings.cfg.i_menukey);
                                if (keyButtonClicked)
                                {
                                    if (ImGui::Button(pressKey, ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;

                                    isKeyPressed(&var->Settings.cfg.i_menukey, &keyButtonClicked, &currentKey);
                                }
                                else
                                {
                                    if (ImGui::Button(currentKey.c_str(), ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;
                                }
                            }
                            ImGui::PushFont(mainfontBig);
                            ImGui::Text("Menu Key 2: ");
                            ImGui::PopFont();
                            ImGui::SetCursorPos(ImVec2(155, 100));
                            {
                                static int* key = 0;
                                static bool keyButtonClicked = false;
                                const char* pressKey = "...";
                                std::string  currentKey = keyIntToString(var->Settings.cfg.i_menu2key);
                                if (keyButtonClicked)
                                {
                                    if (ImGui::Button(pressKey, ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;

                                    isKeyPressed(&var->Settings.cfg.i_menu2key, &keyButtonClicked, &currentKey);
                                }
                                else
                                {
                                    if (ImGui::Button(currentKey.c_str(), ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;
                                }
                            }
                            ImGui::PushFont(mainfontBig);
                            ImGui::Text("200 FOV: ");
                            ImGui::PopFont();
                            ImGui::SetCursorPos(ImVec2(155, 125));
                            {
                                static int* key = 0;
                                static bool keyButtonClicked = false;
                                const char* pressKey = "...";
                                std::string  currentKey = keyIntToString(var->Settings.cfg.i_200fovkey);
                                if (keyButtonClicked)
                                {
                                    if (ImGui::Button(pressKey, ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;

                                    isKeyPressed(&var->Settings.cfg.i_200fovkey, &keyButtonClicked, &currentKey);
                                }
                                else
                                {
                                    if (ImGui::Button(currentKey.c_str(), ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;
                                }
                            }
                            ImGui::PushFont(mainfontBig);
                            ImGui::Text("Enable Chams: ");
                            ImGui::PopFont();
                            ImGui::SetCursorPos(ImVec2(155, 150));
                            {
                                static int* key = 0;
                                static bool keyButtonClicked = false;
                                const char* pressKey = "...";
                                std::string  currentKey = keyIntToString(var->Settings.cfg.i_chamskey);
                                if (keyButtonClicked)
                                {
                                    if (ImGui::Button(pressKey, ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;

                                    isKeyPressed(&var->Settings.cfg.i_chamskey, &keyButtonClicked, &currentKey);
                                }
                                else
                                {
                                    if (ImGui::Button(currentKey.c_str(), ImVec2(75, 20)))
                                        keyButtonClicked = !keyButtonClicked;
                                }
                            }
                        }
                        ImGui::EndGroup();



                    }
                    ImGui::EndGroup();

                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild(); ImGui::PopStyleColor(4);



                ImGui::SetCursorPos(ImVec2(500, 40));
                if (ImGui::BeginChild("jay=gaggdaddy/location", ImVec2(310, 190), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar))
                {

                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 10, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Menu Design");

                        ImGui::PushItemWidth(181);
                        ImGui::SetCursorPosY(29);


                        ToggleNL("Rainbow Menu", &var->Settings.b_rainbowmenu, TRUE);
                        ToggleNL("Commands Always On", &var->Settings.alwayson, TRUE);

                    }
                    ImGui::EndGroup();


                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild(); ImGui::PopStyleColor(4);




                ImGui::SetCursorPos(ImVec2(500, 255));
                if (ImGui::BeginChild("dddaaaaaaaaaaaaaaaaaaaaaaaa.com", ImVec2(310, 190), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::SetCursorPosY(21);
                    ImGui::Separator();
                    ImGui::SetCursorPos({ 50, 4 });
                    ImGui::BeginGroup();
                    {
                        subHeaderText("Configs");

                        ImGui::PushItemWidth(181);
                        ImGui::SetCursorPosY(70);


                        static int configNum;
                        ImGui::PushItemWidth(197);
                        ImGui::Combo("##confignumber", &configNum, "Configuration 1\0\Configuration 2\0\Configuration 3\0\Configuration 4\0\Configuration 5\0\Configuration 6\0\Configuration 7\0\Configuration 8\0\Configuration 9\0\Configuration 10");
                        if (ImGui::Button("Save Config", ImVec2(94, 23)))
                        {
                            saveConfig(configNum + 1);
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Apply Config", ImVec2(95, 23)))
                        {
                            setVars(configNum + 1);
                        }


                    }
                    ImGui::EndGroup();


                    ImGui::SetCursorPos({ 219, 29 });



                }
                ImGui::EndChild();



            }


            if (Tabs == 6)
            {
                {
                    ImGui::SetCursorPos({ 63, 53 });
                    ImGui::BeginGroup();
                    {
                        ImGui::PushItemWidth(130);
                        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.10f, 0.10f, 0.10f, 1.00f));
                        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.12f, 0.12f, 0.12f, 1.00f));
                        ImGui::Combo("##gamemode", &gamemode, combo_gamemode, IM_ARRAYSIZE(combo_gamemode));
                        draw->AddText(mainFBold, 15.0f, ImVec2(pos.x + posx_version, pos.y + posy_version), ImColor(.7f, .7f, .7f, style.Alpha), version);
                        ImGui::PopStyleColor(2);
                    }
                    ImGui::SetCursorPos({ 221, 8 });
                    ImGui::BeginChild("##aimbot", ImVec2(216, 308));
                    {
                        ImGui::SetCursorPos({ 4, 4 });
                        ImGui::BeginGroup();
                        {
                            draw->AddText(mainFBold, 15.0f, ImVec2(pos.x + 288, pos.y + 14), ImColor(.4f, .4f, .4f, style.Alpha), "Aimbot/ESP");
                            ImGui::SetCursorPosY(21);
                            ImGui::Separator();

                            static int input;
                            ImGui::InputInt("", &input);
                            if (ImGui::Button("Set Camo", ImVec2(102, 20)))
                            {
                                if (var->Settings.server.camo)
                                {
                                    char context[255];
                                    char state[255];
                                    int navStringCount;
                                    char* navStrings[16]{};
                                    const char* mode = "";

                                    if (gamemode != 4)
                                    {
                                        if (gamemode == 0)
                                        {
                                            mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                        }
                                        if (gamemode == 1)
                                        {
                                            mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                        }
                                        if (gamemode == 2)
                                        {
                                            mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                        }
                                        if (gamemode == 3)
                                        {
                                            mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                            CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                        }


                                        __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);

                                        DDL_GetRootState((__int64)state, ddl_file);
                                        char buffer[200];
                                        memset(buffer, 0, 200);
                                        sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.camo"), 0, 0);
                                        ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                        if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                        {
                                            DDL_SetInt((__int64)state, (__int64)context, input);
                                        }
                                    }
                                    else
                                    {
                                        for (int j = 3; j < 7; j++)
                                        {
                                            if (j == 5)
                                            {
                                                mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                            }
                                            if (j == 6)
                                            {
                                                mode = xorstr_("ddl/mp/wzprivateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 6);
                                            }
                                            if (j == 3)
                                            {
                                                mode = xorstr_("ddl/mp/rankedloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 3);
                                            }
                                            if (j == 4)
                                            {
                                                mode = xorstr_("ddl/mp/privateloadouts.ddl");
                                                CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 4);
                                            }

                                            __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);

                                            DDL_GetRootState((__int64)state, ddl_file);
                                            char buffer[200];
                                            memset(buffer, 0, 200);
                                            sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.camo"), 0, 0);
                                            ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                            if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                            {
                                                DDL_SetInt((__int64)state, (__int64)context, input);
                                            }
                                        }
                                    }
                                }
                            }
                            if (ImGui::Button("Get Camo", ImVec2(102, 20)))
                            {
                                if (var->Settings.server.camo)
                                {
                                    char context[255];
                                    char state[255];
                                    int navStringCount;
                                    char* navStrings[16]{};
                                    const char* mode = "";
                                    mode = xorstr_("ddl/mp/wzrankedloadouts.ddl");
                                    CL_PlayerData_GetDDLBufferr((__int64)context, 0, 0, 5);
                                    __int64 ddl_file = Com_DDL_LoadAssett((__int64)mode);
                                    DDL_GetRootState((__int64)state, ddl_file);
                                    char buffer[200];
                                    memset(buffer, 0, 200);
                                    sprintf_s(buffer, ("squadMembers.loadouts.%i.weaponSetups.%i.camo"), 0, 0);
                                    ParseShitt(buffer, (const char**)navStrings, 16, &navStringCount);
                                    if (DDL_MoveToPathh((__int64*)&state, (__int64*)&state, navStringCount, (const char**)navStrings))
                                    {
                                        int outlog = DDL_GetInt((__int64*)state, (__int64*)context);
                                        Log_(std::to_string(outlog).c_str());
                                    }
                                }
                            }
                        }
                        ImGui::EndGroup();
                    }
                    ImGui::EndChild();
                }

            }
        }

        // always on
        ImGui::BeginGroup();
        {
            if (var->Settings.alwayson)
            {
                if (var->Settings.menuInit)
                {
                    if (var->Settings.b_map == true)
                    {
                        if (var->Settings.server.map)
                        {
                            dvar_set2("MKMRRLNRTM", var->Settings.f_map);
                        }
                        else
                        {
                            throwImGuiError("Map Slider has been disabled.", &var->Settings.b_map);
                            var->Settings.f_map = 1.f;
                        }
                    }
                    else if (var->Settings.b_map == false)
                    {
                        if (var->Settings.server.map)
                            dvar_set2("MKMRRLNRTM", 1);
                    }
                    if (var->Settings.b_unlock)
                    {
                        unlock();
                    }
                    else if (var->Settings.b_unlock == false)
                    {
                        lock();
                    }
                    if (var->Settings.b_camo)
                    {
                        reversecamo();
                    }
                    else if (var->Settings.b_camo == false)
                    {
                        lockreverse();
                    }
                    if (var->Settings.b_owner)
                    {
                        if (var->Settings.server.lootcheck)
                        {
                            dvar_set2("NRQQOMLOQL", 0);
                            dvar_set2("RRTLRKKTT", 0);
                            dvar_set2("MKQPRPLQKL", 0);
                        }
                        else
                        {
                            throwImGuiError("Loot Checks have been disabled.", &var->Settings.b_owner);
                        }
                    }
                    else if (var->Settings.b_owner == false)
                    {
                        if (var->Settings.server.lootcheck)
                        {
                            dvar_set2("NRQQOMLOQL", 1);
                            dvar_set2("RRTLRKKTT", 1);
                            dvar_set2("MKQPRPLQKL", 1);
                        }
                    }
                    if (var->Settings.b_fps)
                    {
                        if (var->Settings.server.fpsboost)
                        {
                            dvar_set2("OPOTTRRNQ", 0);
                            dvar_set2("NNRQTQNLRL", 0);
                            dvar_set2("NNTOQLMSLO", 3);
                            dvar_set2("NTROOKOSPM", 3);
                            dvar_set2("NNKRMTSNPL", 0);
                            dvar_set2("MOLLKMTMRS", 0);
                            dvar_set2("MQOPRPQLQL", 0);
                            dvar_set2("NLNKQNROQM", 0);
                            dvar_set2("LTOKRMRTMM", 0);
                        }
                        else
                        {
                            throwImGuiError("FPS Booster has been disabled.", &var->Settings.b_fps);
                        }
                    }
                    if (var->Settings.b_gun)
                    {
                        if (var->Settings.server.nogun)
                        {
                            dvar_set2(xorstr_("SROLTPQLK"), 0);
                        }
                        else
                        {
                            throwImGuiError("No Gun has been disabled.", &var->Settings.b_gun);
                        }
                    }
                    else if (var->Settings.b_gun == false)
                    {
                        if (var->Settings.server.nogun)
                            dvar_set2(xorstr_("SROLTPQLK"), 1);
                    }
                    if (var->Settings.b_shield)
                    {
                        if (var->Settings.server.noshield)
                        {
                            dvar_set2(xorstr_("LQKTTRTSNS"), 0);
                        }
                        else
                        {
                            throwImGuiError("No Shield has been disabled.", &var->Settings.b_shield);
                        }
                    }
                    else if (var->Settings.b_shield == false)
                    {
                        if (var->Settings.server.noshield)
                            dvar_set2(xorstr_("LQKTTRTSNS"), 1);
                    }
                    if (var->Settings.b_heart)
                    {
                        if (var->Settings.server.heartcheat)
                        {
                            dvar_set2("NSKNMSMOLP", 2);
                            dvar_set2("NLLRSSOQMQ", 10000);
                        }
                        else
                        {
                            throwImGuiError("Heartcheat has been disabled.", &var->Settings.b_heart);
                        }
                    }
                    else if (var->Settings.b_heart == false)
                    {
                        if (var->Settings.server.heartcheat)
                        {
                            dvar_set2("NSKNMSMOLP", 5);
                            dvar_set2("NLLRSSOQMQ", 500);
                        }
                    }
                    if (var->Settings.b_nocrosshair)
                    {
                        if (var->Settings.server.crosshair)
                        {
                            dvar_set2(xorstr_("LOPKSRNTTS"), 0);
                        }
                        else
                        {
                            throwImGuiError("No Crosshair has been disabled.", &var->Settings.b_nocrosshair);
                        }
                    }
                    else if (var->Settings.b_nocrosshair == false)
                    {
                        if (var->Settings.server.crosshair)
                            dvar_set2(xorstr_("LOPKSRNTTS"), 1);
                    }
                    if (var->Settings.b_fuckview)
                    {
                        if (var->Settings.server.breakcam)
                        {
                            dvar_set2(xorstr_("LLLRKRROOP"), 1);
                        }
                        else
                        {
                            throwImGuiError("Break Camera has been disabled.", &var->Settings.b_fuckview);
                        }
                    }
                    else if (var->Settings.b_fuckview == false)
                    {
                        if (var->Settings.server.breakcam)
                            dvar_set2(xorstr_("LLLRKRROOP"), 0);
                    }
                    if (var->Settings.b_no_fog)
                    {
                        if (var->Settings.server.fog)
                        {
                            dvar_set2(xorstr_("LTOKRMRTMM"), 0);
                        }
                        else
                        {
                            throwImGuiError("No Fog has been disabled.", &var->Settings.b_no_fog);
                        }
                    }
                    else if (var->Settings.b_no_fog == false)
                    {
                        if (var->Settings.server.fog)
                            dvar_set2(xorstr_("LTOKRMRTMM"), 1);
                    }
                    if (var->Settings.b_fpss)
                    {
                        if (var->Settings.server.drawfps)
                        {
                            dvar_set2("NLLPTKRKKN", 1);
                        }
                        else
                        {
                            throwImGuiError("Draw FPS has been disabled.", &var->Settings.b_fpss);
                        }
                    }
                    else if (var->Settings.b_fpss == false)
                    {
                        if (var->Settings.server.drawfps)
                            dvar_set2("NLLPTKRKKN", 0);
                    }
                    if (var->Settings.b_playlist)
                    {
                        if (var->Settings.server.devplay)
                        {
                            dvar_set2("LSSRRSMNMR", 1);
                        }
                        else
                        {
                            throwImGuiError("Dev Playlist has been disabled", &var->Settings.b_playlist);
                        }
                    }
                    else if (var->Settings.b_playlist == false)
                    {
                        if (var->Settings.server.devplay)
                            dvar_set2("LSSRRSMNMR", 0);
                    }
                    if (var->Settings.b_tut)
                    {
                        if (var->Settings.server.skiptut)
                        {
                            dvar_set2(xorstr_("LSPSKLPNQT"), 1);
                        }
                        else
                        {
                            throwImGuiError("Skip Tutorial has been disabled.", &var->Settings.b_tut);
                        }
                    }
                    else if (var->Settings.b_tut == false)
                    {
                        if (var->Settings.server.skiptut)
                            dvar_set2(xorstr_("LSPSKLPNQT"), 0);
                    }
                    if (var->Settings.b_Thirdperson)
                    {
                        if (var->Settings.server.thirdperson)
                        {
                            dvar_set2("NOSLRNTRKL", 1);
                        }
                        else
                        {
                            throwImGuiError("Third Person has been disabled.", &var->Settings.b_Thirdperson);
                        }
                    }
                    else if (var->Settings.b_Thirdperson == false)
                    {
                        if (var->Settings.server.thirdperson)
                            dvar_set2("NOSLRNTRKL", 0);
                    }
                    if (var->Settings.b_mploadout)
                    {
                        if (var->Settings.server.forcemp)
                        {
                            dvar_set2(xorstr_("LNLMORMPTS"), 0);
                        }
                        else
                        {
                            throwImGuiError("Force MP Loadouts has been disabled.", &var->Settings.b_mploadout);
                        }
                    }
                    else
                    {
                        if (var->Settings.server.forcemp)
                            dvar_set2(xorstr_("LNLMORMPTS"), 1);
                    }
                    if (var->Settings.b_brightmax)
                    {
                        if (var->Settings.server.maxbright)
                        {
                            dvar_set2("NQKKOONQPR", 0);
                            dvar_set2("MTLMSQMNTR", 0);
                            dvar_set2("RNPPKQOTN", 0);
                            dvar_set2("LKOLRONRNQ", 0);
                            dvar_set2("LTOKRMRTMM", 0);
                        }
                        else
                        {
                            throwImGuiError("Max Bright has been disabled.", &var->Settings.b_brightmax);
                        }
                    }
                    else if (var->Settings.b_brightmax == false)
                    {
                        if (var->Settings.server.maxbright)
                        {
                            dvar_set2("NQKKOONQPR", 1);
                            dvar_set2("MTLMSQMNTR", 1);
                            dvar_set2("RNPPKQOTN", 1);
                            dvar_set2("LKOLRONRNQ", 1);
                            dvar_set2("LTOKRMRTMM", 1);
                        }
                    }
                    if (var->Settings.b_dynamic3p)
                    {
                        if (!var->Settings.server.d3person)
                        {
                            throwImGuiError("Dynamic Third Person has been disabled.", &var->Settings.b_dynamic3p);
                        }
                    }
                }
            }
        }
        ImGui::EndGroup();
    }
           
        
    
}