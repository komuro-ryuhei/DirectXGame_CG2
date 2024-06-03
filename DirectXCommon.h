#pragma once
#include <cstdint>
#include <string>
#include <format>
#include <cassert>
#include <Windows.h>
#include <cstdint>
#include <wrl.h>

#include <d3d12.h>
#include <dxgi1_6.h>

#include "WinApp.h"

class DirectXCommon {

public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns></returns>
	static DirectXCommon* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="winApp"></param>
	void Initialize(WinApp* winApp);

private: // メンバ変数
	// ウィンドウズアプリケーション管理
	WinApp* winApp_;

	// ウィンドウサイズ
	uint32_t kClientWidth_;
	uint32_t kClientHeight_;


	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter_;
	Microsoft::WRL::ComPtr<ID3D12Device> device_;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_;
	// スワップチェーンを生成
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_;
	// ディスクリプタヒープの生成
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap_;
	// SwapChainからResourceを持ってくる
	Microsoft::WRL::ComPtr<ID3D12Resource> swapChainResources_[2];

	// RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	// ディスクリプタの先端を取得する
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle;
	// RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];

	// 書き込むバックバッファのインデックスを取得
	UINT backBufferIndex;


	ID3D12Debug1* debugController = nullptr;


	ID3D12InfoQueue* infoQueue = nullptr;


	D3D12_RESOURCE_BARRIER barrier{};


	ID3D12Fence* fence = nullptr;
	uint64_t fenceValue = 0;
	HANDLE fenceEvent;

private: // メンバ関数

	DirectXCommon() = default;
	~DirectXCommon() = default;

	/// <summary>
	/// DXGIデバイス初期化
	/// </summary>
	void InitializeDXGIDevice();

	/// <summary>
	/// コマンド初期化
	/// </summary>
	void InitializeCommand();

	/// <summary>
	/// スワップチェーンの生成
	/// </summary>
	void CreateSwapChain();

	/// <summary>
	/// ディスクリプタヒープの生成
	/// </summary>
	void DescriptorHeap();

	/// <summary>
	/// RTVの作成
	/// </summary>
	void CreateRTV();

	/// <summary>
	/// バックバッファのインデックスを取得
	/// </summary>
	void FindBackBufferIndex();


	void TransitionBarrir();

	void DebugLayer();

	/// <summary>
	/// Fenceの作成
	/// </summary>
	void CreateFence();
};