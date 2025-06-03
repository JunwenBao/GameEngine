#pragma once

#include "GameEngine/Renderer/Framebuffer.h"

namespace GameEngine {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t t_width, uint32_t t_height) override;

		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { return m_ColorAttachments[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID = 0;

		// FBO����ģ��
		FramebufferSpecification m_Specification;
		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications; //��������
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None; // �������

		// FBOʵ����Դ
		std::vector<uint32_t> m_ColorAttachments; // ������ID�б����ӵ���ǰ֡����ɫ����
		uint32_t m_DepthAttachment = 0;			  // ��ȸ���ID
	};

}