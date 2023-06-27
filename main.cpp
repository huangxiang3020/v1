#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include "GfxDevice.h"
#include <glm/vec4.hpp>
#include "Shader.h"

int main(int argc, char* argv[])
{
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "v1", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	const int32_t version = gladLoadGL(glfwGetProcAddress);
	if (version == 0)
	{
		return -1;
	}

	auto context = DrawContext();
	const std::vector<glm::vec3> vertices{
		glm::vec3(0.5f, 0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(-0.5f, 0.5f, 0.0f),
	};

	const std::vector<uint32_t> intices{
		0, 1, 3,
		1, 2, 3
	};
	context.setVertices(vertices);
	context.setIndices(intices);

	const char* vertexCode = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}";
	const char* fragmentCode = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n";
	const auto shader = Shader(vertexCode, fragmentCode);

	constexpr auto device = GfxDevice();
	while (!glfwWindowShouldClose(window))
	{
		device.clearColor(glm::vec4(1, 1, 1, 1));
		shader.use();
		device.draw(context);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
