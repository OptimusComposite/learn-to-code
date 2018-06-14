#include "stdafx.h"

inline HANDLE __stdcall BeginThread(
	LPSECURITY_ATTRIBUTES lpThreadAttributes,
	SIZE_T dwStackSize,
	LPTHREAD_START_ROUTINE lpStartAddress,
	LPVOID lpParameter,
	DWORD dwCreationFlags,
	LPDWORD lpThread
) {
	return reinterpret_cast<HANDLE>(_beginthreadex(static_cast<void *>(lpThreadAttributes),
		dwStackSize,
		reinterpret_cast<unsigned(__stdcall *) (void *)>(lpStartAddress),
		lpParameter,
		dwCreationFlags,
		reinterpret_cast<unsigned *>(lpThread)));
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI RenderThreadMain(LPVOID);

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE,
	LPWSTR lpCmdLine,
	int nCmdShow) {
		{
			WNDCLASSEXW wcex;
			wcex.cbSize = sizeof(WNDCLASSEX);
			wcex.style = CS_OWNDC;
			wcex.lpfnWndProc = WndProc;
			wcex.cbClsExtra = 0;
			wcex.cbWndExtra = 0;
			wcex.hInstance = hInstance;
			wcex.hIcon = LoadIconW(hInstance, IDI_APPLICATION);
			wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
			wcex.hbrBackground = NULL;
			wcex.lpszMenuName = NULL;
			wcex.lpszClassName = L"{640CB8AD-56CD-4328-B4D0-2A9DAA951494}";
			wcex.hIconSm = LoadIconW(hInstance, IDI_APPLICATION);
			RegisterClassExW(&wcex);

			RECT windowrect;
			windowrect.left = 0;
			windowrect.top = 0;
			windowrect.right = 800;
			windowrect.bottom = 600;
			AdjustWindowRect(&windowrect, WS_POPUP | WS_VISIBLE, FALSE);

			HWND hWnd = CreateWindowExW(0,
				L"{640CB8AD-56CD-4328-B4D0-2A9DAA951494}",
				L"<<Direct3D 12 ���>>",
				WS_POPUP | WS_VISIBLE,
				0,
				0,
				windowrect.right,
				windowrect.bottom,
				NULL,
				NULL,
				hInstance,
				NULL
			);

			BeginThread(
				NULL,
				0,
				RenderThreadMain,
				static_cast<void *>(hWnd),
				0,
				NULL
			);
		}

		MSG msg;

		while (GetMessageW(&msg, NULL, 0, 0))
			DispatchMessageW(&msg);
		return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, message, wParam, lParam);
	}
	return 0;
}