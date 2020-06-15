#pragma once

#include <Swallow/Renderer/Framebuffer.h>

namespace Swallow {
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
		virtual RendererID GetRendererID() const override { return m_RendererID; }
		virtual RendererID GetColorAttachmentRendererID() const override { return m_ColorAttachmentID; }
	private:
		RendererID m_RendererID;
		RendererID m_ColorAttachmentID;
		RendererID m_DepthAttachmentID;
		FramebufferSpecification m_Specification;
	};
}