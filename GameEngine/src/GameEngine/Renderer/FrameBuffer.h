#pragma once

#include "GameEngine/Core/Core.h"

namespace GameEngine {

	// 定义帧缓冲区中可以附加的纹理格式
	enum class FramebufferTextureFormat
	{
		None = 0,				// 表示无效或未指定
		RGBA8,					// 普通颜色纹理，8位R、G、B、A通道（常用于主颜色输出）	
		RED_INTEGER,			// Entity ID
		DEPTH24STENCIL8,		// 同时包含深度和模板缓冲（常用于深度测试）
		Depth = DEPTH24STENCIL8 // 给Depth一个别名，默认就是DEPTH24STENCIL8
	};

	// 纹理附件的格式，即：FBO的单个颜色或深度附件
	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format) : TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
	};

	// 一组纹理附件
	struct FramebufferAttachmentSpecification
	{
		FramebufferAttachmentSpecification() = default;
		FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}

		std::vector<FramebufferTextureSpecification> Attachments;
	};

	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		FramebufferAttachmentSpecification Attachments;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t t_width, uint32_t t_height) = 0;
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) = 0;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) = 0;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
	};


}