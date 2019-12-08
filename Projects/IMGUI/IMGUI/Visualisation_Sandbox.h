#pragma once
#include "Visualisation.h"
#include "Camera.h"
#include "Mesh.h"
#include <deque>
class Buffer;
struct GLFWwindow;
class Shader;

class Visualisation_Sandbox : public Visualisation
{
public:
	Visualisation_Sandbox();

	/* Set up callbacks, shaders, vertex objects */
	void activate() override;
	/* Free callbacks, shaders, vertex objects */
	void deactivate() override;

	void processSamples(const Buffer & buf, unsigned samples) override;
	void renderFrame() override;

	std::string titleString() override { return "Sandbox"; };
private:
	// camera
	Camera m_camera;
	float m_lastX, m_lastY;
	bool m_firstMouse = true;

	// timing
	float m_deltaTime;	// time between current frame and last frame
	float m_lastFrame;

	unsigned int m_cubeVAO, m_lightVAO, m_cubeVBO;

	Shader * m_objectShader;
	Shader * m_lampShader;

	std::vector<float> m_vertices;

	std::vector<glm::vec3> m_cubePositions;
	std::vector<glm::vec3> m_cubeColours;

	std::deque<double> m_signalPowerHistory;

	glm::vec3 m_lightPos;

	glm::vec3 m_scaleVec;

	Mesh m_mesh;
};