#pragma once

#include "GameEngine/Core/Core.h"

namespace GameEngine {

	// ����֡�������п��Ը��ӵ������ʽ
	enum class FramebufferTextureFormat
	{
		None = 0,				// ��ʾ��Ч��δָ��
		RGBA8,					// ��ͨ��ɫ����8λR��G��B��Aͨ��������������ɫ�����	
		RED_INTEGER,			// Entity ID
		DEPTH24STENCIL8,		// ͬʱ������Ⱥ�ģ�建�壨��������Ȳ��ԣ�
		Depth = DEPTH24STENCIL8 // ��Depthһ��������Ĭ�Ͼ���DEPTH24STENCIL8
	};

	// �������ĸ�ʽ������FBO�ĵ�����ɫ����ȸ���
	struct FramebufferTextureSpecification
	{
		FramebufferTextureSpecification() = default;
		FramebufferTextureSpecification(FramebufferTextureFormat format) : TextureFormat(format) {}

		FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
	};

	// һ��������
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