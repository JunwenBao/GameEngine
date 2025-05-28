#include "hzpch.h"
#include "OpenGLFramebuffer.h"

#include <glad/glad.h>

namespace GameEngine {

	static const uint32_t s_MaxFramebufferSize = 8192;
	
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec) : m_Specification(spec)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
		glDeleteTextures(1, &m_ColorAttachment);
		glDeleteTextures(1, &m_DepthAttachment);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);
			glDeleteTextures(1, &m_DepthAttachment);
		}

		// 创建并绑定一个新的FBO
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		// 创建并绑定一个2D纹理作为颜色附件（m_ColorAttachment）
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		
		// 设置颜色纹理的缩放过滤方式为线性（平滑过渡）
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// 将颜色纹理附加到FBO的颜色通道
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

		// 创建并绑定一个包含深度和模板缓冲的纹理（m_DepthAttachment），用于深度测试和模板测试
		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height);

		// 将深度+模板纹理绑定到FBO中
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);

		HZ_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		glViewport(0, 0, m_Specification.Width, m_Specification.Height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Resize(uint32_t t_width, uint32_t t_height)
	{
		if (t_width == 0 || t_height == 0 || t_width > s_MaxFramebufferSize || t_height > s_MaxFramebufferSize)
		{
			HZ_CORE_WARN("Attempted to rezize framebuffer to {0}, {1}", t_width, t_height);
			return;
		}

		m_Specification.Width = t_width;
		m_Specification.Height = t_height;

		Invalidate();
	}

}