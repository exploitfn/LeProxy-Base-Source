#include "FN Utils\includes.h"
#include "FN Utils\structs.h"
#include "Imgui\imgui_impl_win32.cpp"

/*
OVERLAY.HPP - AKA PROBLEM CENTRE
WorldToScreen is and GetBone are not getting defined in "entry.cpp" because they are in a different file. <- in structs.h
EVERYTHING in here is getting a redifinition error or a undefined error when i call it.

ALL ERRORS ARE FROM IT BEING IN ANOTHER FILE

SUGGESTION
Copy everything in here and organize it in entry.cpp
Nothing here will because its getting redfined and not included.

Sincerely, LeProxy#1336
*/


DWORD ScreenCenterX;
DWORD ScreenCenterY;
DWORD ScreenCenterZ;
DWORD ScreenCenter = ScreenCenterX / 2 + ScreenCenterY / 2 + ScreenCenterZ / 2;

ImFont* SkeetFont;
DWORD process_id;
DWORD64 base_address;
HWND hwnd = NULL;

IDirect3D9Ex* p_Object = NULL;
IDirect3DDevice9Ex* p_Device = NULL;
D3DPRESENT_PARAMETERS p_Params = { NULL };
HWND MyWnd = NULL;
HWND GameWnd = NULL;
RECT GameRect = { NULL };
MSG Message = { NULL };

static void xCreateWindow();
static void xInitD3d();
static void xMainLoop();
static void xShutdown();
static LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Overlay
{
	namespace cheat
	{

		void DrawCircleFilled(int x, int y, int radius, RGBA* color)
		{
			ImGui::GetOverlayDrawList()->AddCircleFilled(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)));
		}

		void DrawCircle(int x, int y, int size, RGBA* color, int Segaments, int Thickness)
		{
			ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), size, ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), Segaments, Thickness);
		}

		void DrawSnapline(int x, int y, int w, int h, ImU32 color, int Thickness)
		{
			ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y), ImVec2(w, h), color, Thickness);
		}

		void DrawFilledPlayerBox(int x, int y, int w, int h, ImU32 color)
		{
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
		}

		void DrawRect(int x, int y, int w, int h, ImU32 color)
		{
			ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
		}

		void DrawRoundedRect(int x, int y, int w, int h, ImU32& color, int thickness)
		{
			ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(w, h), ImGui::ColorConvertFloat4ToU32(ImVec4(1 / 255.0, 1 / 255.0, 1 / 255.0, 255 / 255.0)), 0, 0, 3);
			ImGui::GetOverlayDrawList()->AddRect(ImVec2(x, y), ImVec2(w, h), ImGui::GetColorU32(color), 0, 0, thickness);
		}

		void FilledRect(int x, int y, int w, int h, ImColor color)
		{
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 150)), 0, 0);
		}

		void DrawCornerBox(int x, int y, int w, int h, int borderPx, ImU32 color) {
			DrawFilledPlayerBox(x + borderPx, y, w / 3, borderPx, color);
			DrawFilledPlayerBox(x + w - w / 3 + borderPx, y, w / 3, borderPx, color);
			DrawFilledPlayerBox(x, y, borderPx, h / 3, color);
			DrawFilledPlayerBox(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
			DrawFilledPlayerBox(x + borderPx, y + h + borderPx, w / 3, borderPx, color);
			DrawFilledPlayerBox(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color);
			DrawFilledPlayerBox(x + w + borderPx, y, borderPx, h / 3, color);
			DrawFilledPlayerBox(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);
		}
	}
}

	void Cleanup()
	{
		if (p_Device != NULL)
		{
			p_Device->EndScene();
			p_Device->Release();
		}
		if (p_Object != NULL)
		{
			p_Object->Release();
		}
	}

	void SetWindow()
	{
		while (true)
		{
			GameWnd = get_process_wnd(process_id);
			if (GameWnd)
			{
				ZeroMemory(&GameRect, sizeof(GameRect));
				GetWindowRect(GameWnd, &GameRect);
				Width = GameRect.right - GameRect.left;
				Height = GameRect.bottom - GameRect.top;
				DWORD dwStyle = GetWindowLong(GameWnd, GWL_STYLE);
				if (dwStyle & WS_BORDER)
				{
					GameRect.top += 32;
					Height -= 39;
				}
				ScreenCenterX = Width / 2;
				ScreenCenterY = Height / 2;
				MoveWindow(hwnd, GameRect.left, GameRect.top, Width, Height, true);
			}
		}
	}

	HRESULT DirectXInit(HWND hWnd)
	{
		if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
			exit(3);

		ZeroMemory(&p_Params, sizeof(p_Params));
		p_Params.Windowed = TRUE;
		p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		p_Params.hDeviceWindow = hWnd;
		p_Params.MultiSampleQuality = D3DMULTISAMPLE_NONE;
		p_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
		p_Params.BackBufferWidth = Width;
		p_Params.BackBufferHeight = Height;
		p_Params.EnableAutoDepthStencil = TRUE;
		p_Params.AutoDepthStencilFormat = D3DFMT_D16;
		p_Params.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

		if (FAILED(p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device)))
		{
			p_Object->Release();
			exit(4);
		}

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::GetIO().Fonts->AddFontDefault();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.Fonts->AddFontFromFileTTF(("C:\\Windows\\Fonts\\Micross.ttf"), 13.f);


		static const ImWchar ranges[] =
		{
			0x0020, 0x00FF,
			0x0400, 0x044F,
			0,
		};


		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX9_Init(p_Device);

		return S_OK;
	}

	void StartWindow()
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindow, 0, 0, 0);

		WNDCLASSEXA wcex = {
			sizeof(WNDCLASSEXA),
			0,
			DefWindowProcA,
			0,
			0,
			nullptr,
			LoadIcon(nullptr, IDI_APPLICATION),
			LoadCursor(nullptr, IDC_ARROW),
			nullptr,
			nullptr,
			("Discord"),
			LoadIcon(nullptr, IDI_APPLICATION)
		};

		RECT Rect;
		GetWindowRect(GetDesktopWindow(), &Rect);

		RegisterClassExA(&wcex);

		hwnd = CreateWindowExA(NULL, ("Discord"), ("Discord"), WS_POPUP, Rect.left, Rect.top, Rect.right, Rect.bottom, NULL, NULL, wcex.hInstance, NULL);
		SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW);
		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 255, LWA_ALPHA);
		//SetWindowDisplayAffinity(hwnd, 1);

		MARGINS margin = { -1 };
		DwmExtendFrameIntoClientArea(hwnd, &margin);

		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);
	}

	LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, Message, wParam, lParam))
			return true;

		switch (Message)
		{
		case WM_DESTROY:
			Cleanup();
			PostQuitMessage(0);
			exit(4);
			break;
		case WM_SIZE:
			if (p_Device != NULL && wParam != SIZE_MINIMIZED)
			{
				ImGui_ImplDX9_InvalidateDeviceObjects();
				p_Params.BackBufferWidth = LOWORD(lParam);
				p_Params.BackBufferHeight = HIWORD(lParam);
				HRESULT hr = p_Device->Reset(&p_Params);
				if (hr == D3DERR_INVALIDCALL)
					IM_ASSERT(0);
				ImGui_ImplDX9_CreateDeviceObjects();
			}
			break;
		default:
			return DefWindowProc(hWnd, Message, wParam, lParam);
			break;
		}
		return 0;
	}



