#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader {
private:
	unsigned int m_rendererID; //GLuint
	std::unordered_map<std::string, int> m_uniformLocationCache;
	std::string m_filepath;

public:
	Shader();
	Shader(const std::string& filepath);
	~Shader();

	void bind() const;
	void unbind() const;

	// Set uniforms
	void setUniform1i(const std::string& name, int value);
	void setUniform1f(const std::string& name, float value);
	void setUniform2f(const std::string& name, float v0, float v1);
	void setUniform3f(const std::string& name, float v0, float v1, float v2);
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void setUniform1f(const std::string& name, glm::vec1& value);
	void setUniform2f(const std::string& name, glm::vec2& value);
	void setUniform3f(const std::string& name, glm::vec3& value);
	void setUniform4f(const std::string& name, glm::vec4& value);


	void setUniformMat2f(const std::string& name, const glm::mat2& matrix);
	void setUniformMat3f(const std::string& name, const glm::mat3& matrix);
	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	int getUniformLocation(const std::string& name);

	ShaderProgramSource ParseShader(const std::string& filepath);
	int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};