#include "System.h"

#include "DirectXCommon.h"
#include "WinApp.h"
#include <cstdint>
#include <string>
#include <format>
#include <cassert>

#include <d3d12.h>
#include <dxgi1_6.h>

#include "Loger.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")


// WindowsAPI
WinApp* winApp_ = nullptr;
// DirectX
DirectXCommon* dxCommon_ = nullptr;

void System::Initialize(const char* title, int width, int height) {

	winApp_ = WinApp::GetInstance();

	// ゲームウインドウの作成
	std::string titleWithVersion = std::string(title);
	auto&& titleString = ConvertString(titleWithVersion);
	winApp_->CreateGameWindow(
		titleString.c_str(), WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME), width,
		height);

	// DirectXの初期化処理
	dxCommon_ = DirectXCommon::GetInstance();
	dxCommon_->Initialize(winApp_);
}

void System::Finalize() {

	winApp_->TerminateGameWindow();
}