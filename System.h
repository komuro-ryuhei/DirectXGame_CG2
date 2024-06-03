#pragma once

class System {

public:
	
	/// <summary>
	/// システム全体の初期化
	/// </summary>
	/// <param name="title"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	static void Initialize(const char* title, int width, int height);

	/// <summary>
	/// 
	/// </summary>
	static void Finalize();

};

