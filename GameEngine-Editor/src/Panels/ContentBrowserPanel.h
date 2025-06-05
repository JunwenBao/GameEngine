#pragma once

#include <filesystem>
#include "GameEngine/Renderer/Texture.h"

namespace GameEngine {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path m_CurrentDirectory; // 当前文件夹路径

		Ref<Texture2D> m_DirectoryIcon; // 文件夹图标
		Ref<Texture2D> m_FileIcon;		// 文件图标
	};

}