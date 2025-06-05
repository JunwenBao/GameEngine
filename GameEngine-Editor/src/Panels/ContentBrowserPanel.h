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
		std::filesystem::path m_CurrentDirectory; // ��ǰ�ļ���·��

		Ref<Texture2D> m_DirectoryIcon; // �ļ���ͼ��
		Ref<Texture2D> m_FileIcon;		// �ļ�ͼ��
	};

}