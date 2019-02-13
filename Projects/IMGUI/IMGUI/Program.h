#pragma once
#include "UserInterface.h"
#include "Recorder.h"

class Settings_VideoRendering;
class Settings_AudioInterface;
class Settings_Visualisation;

class Model_VideoRendering;
class Model_AudioInterface;
class Model_Visualisation;

struct GLFWwindow;

class Program
{
public:
	Program(GLFWwindow * window, std::string glslVersion);
	~Program();

	void initialise();
	void deinitialise();

	void run();


	/* This one way to do it, not very thought through yet. */
	void updateGlobalAudioBuffer(std::shared_ptr<LockableBuffer> & buf);
private:
	GLFWwindow * m_window;
	std::string m_glslVersion;

	UserInterface m_interface;

	/* Settings Instances */
	std::shared_ptr<Settings_VideoRendering> m_settingsVideoRendering;
	std::shared_ptr<Settings_AudioInterface> m_settingsAudioInterface;
	std::shared_ptr<Settings_Visualisation> m_settingsVisualisation;

	/* Model Instances */
	std::shared_ptr<Model_VideoRendering> m_modelVideoRendering;
	std::shared_ptr<Model_AudioInterface> m_modelAudioInterface;
	std::shared_ptr<Model_Visualisation> m_modelVisualisation;

};

