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

using namespace Microsoft::WRL;

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

	/// <summary>
	/// 描画前処理
	/// </summary>
	void PreDraw();

	/// <summary>
	/// 描画後処理
	/// </summary>
	void PostDraw();

	/// <summary>
	/// レンダーターゲットのクリア
	/// </summary>
	void ClearRenderTarget();

	/// <summary>
	/// 深度バッファのクリア
	/// </summary>
	void ClearDepthBuffer();

	/// <summary>
	/// デバイスの取得
	/// </summary>
	ComPtr<ID3D12Device> GetDevice() const { return device_.Get(); }
	
	/// <summary>
	/// コマンドリストの取得
	/// </summary>
	ComPtr<ID3D12GraphicsCommandList> GetCommandList() const { return commandList_.Get(); }

private: // メンバ変数
	// ウィンドウズアプリケーション管理
	WinApp* winApp_;

	// ウィンドウサイズ
	uint32_t kClientWidth_;
	uint32_t kClientHeight_;


	ComPtr<IDXGIFactory7> dxgiFactory_;
	ComPtr<IDXGIAdapter4> useAdapter_;
	ComPtr<ID3D12Device> device_;
	ComPtr<ID3D12GraphicsCommandList> commandList_;
	ComPtr<ID3D12CommandQueue> commandQueue_;
	ComPtr<ID3D12CommandAllocator> commandAllocator_;
	// スワップチェーンを生成
	ComPtr<IDXGISwapChain4> swapChain_;
	// ディスクリプタヒープの生成
	ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap_;
	ComPtr<ID3D12DescriptorHeap> srvDescriptorHeap_;
	ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap_;
	// SwapChainからResourceを持ってくる
	ComPtr<ID3D12Resource> swapChainResources_[2];

	// RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	// ディスクリプタの先端を取得する
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle;
	// RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];

	// 書き込むバックバッファのインデックスを取得
	UINT backBufferIndex;


	//ComPtr<ID3D12Debug1> debugController = nullptr;


	//ComPtr<ID3D12InfoQueue> infoQueue = nullptr;


	D3D12_RESOURCE_BARRIER barrier{};


	ComPtr<ID3D12Fence> fence = nullptr;
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


	ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(
		ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	ComPtr<ID3D12Resource> CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);

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
	/// レンダーターゲット生成
	/// </summary>
	void CreateFinalRenderTargets();

	/// <summary>
	/// 深度バッファ生成
	/// </summary>
	void CreateDepthBuffer();

	/// <summary>
	/// フェンス生成
	/// </summary>
	void CreateFence();
};