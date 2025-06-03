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

		// FBO配置模板
		FramebufferSpecification m_Specification;
		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications; //纹理配置
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None; // 深度配置

		// FBO实际资源
		std::vector<uint32_t> m_ColorAttachments; // 纹理附件ID列表：附加到当前帧的颜色附件
		uint32_t m_DepthAttachment = 0;			  // 深度附件ID
	};

}