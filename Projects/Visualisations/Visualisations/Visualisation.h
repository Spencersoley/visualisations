#pragma once
#include <string>
#include "Camera.h"

class Buffer;
typedef double Timecode;

class Visualisation
{
public:
	Visualisation() :
		m_active{ false }
	{};
	/* Set up shaders, initial VAOs, VBOs */
	virtual void activate() = 0;
	/* Unload shaders etc. */
	virtual void deactivate() = 0;
	virtual void processSamples(const Buffer& buf, unsigned samples) = 0;
	virtual void renderFrame(const Camera& camera, Timecode t) = 0;
	virtual void drawInterface() {};
	virtual std::string titleString() = 0;
protected:
	bool m_active;
};