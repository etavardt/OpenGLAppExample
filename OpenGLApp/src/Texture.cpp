#include "Texture.hpp"
#include <glad/glad.h>
#include <stb/stb_image.h>
#include <KewlF/Logger.hpp>

#include "OpenGLDebug.hpp"

Texture::Texture(const std::string& path) : m_rendererID(0), m_filepath(path), m_localBuffer(nullptr), m_width(0), m_height(0), m_bpp(0) {
	//Load Image via stb
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

	if (m_localBuffer != NULL) {
		GLCall(glGenTextures(1, &m_rendererID));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

		GLCall(glBindTexture(GL_TEXTURE_2D, 0));

		if (m_localBuffer)
			stbi_image_free(m_localBuffer);
	} else {

		LOG(ERROR) << "Unable to load file(\"" << path << "\") for reason: " << stbi_failure_reason() << std::endl;
	}

}

Texture::~Texture() {
	GLCall(glDeleteTextures(1, &m_rendererID));
	LOG(INFO) << "Destruct Texture" << std::endl;
}

void Texture::bind(unsigned int slot /*= 0*/) const {
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void Texture::unbind() const {
	GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}