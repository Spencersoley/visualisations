#include "Interpolation.h"
#include "Serialisation.h"
#include <imgui/imgui.h>
#include <cmath>
#include <boost/property_tree/ptree.hpp>

constexpr char funcTypeStr[] = "Polynomial\0Exponential\0Sinusoidal\0";

float Interpolation::value(float x) const // input is \in [0,1]
{
	float result{ 0.f };
	float normalisation{ 0.f };
	switch (m_functionType)
	{
	case FunctionType::Polynomial:
	{
		int degree{ 0 };
		for (float c : m_coefficients)
		{
			result += c * pow(x, degree);
			normalisation += c; // pow(1,k) = 1 \forall k
			++degree;
		}
	}
	break;
	case FunctionType::Exponential:
	{
		int degree{ 0 };
		for (float c : m_coefficients)
		{
			result += std::exp(c * pow(x, degree));
			normalisation += std::exp(c);
			++degree;
		}
	}
	break;
	case FunctionType::Sinusoidal:
	{
		int degree{ 0 };
		for (float c : m_coefficients)
		{
			result += std::sin(c * pow(x, degree));
			normalisation += std::sin(c);
			++degree;
		}
	}
	break;
	}
	return (normalisation != 0.f) ? (result / normalisation) : 0.f; // avoid division by zero
}

void Interpolation::drawUI(const std::string& name)
{
	int f{ (int)m_functionType };
	ImGui::Combo(std::string{ "Function (" + name + ")"}.c_str(), &f, &funcTypeStr[0]);
	for (size_t i{ 0 }; i < m_coefficients.size(); ++i)
		ImGui::SliderFloat(std::string{ "c" + std::to_string(i) + " " + name }.c_str(), &m_coefficients[i], 0.f, 1.f);
	// TODO: Safety check of coefficients to prevent division by zero.
}

bool Interpolation::loadFileTree(const boost::property_tree::ptree& t)
{
	m_coefficients = Serialisation::strToFloatingVect<float>(t.get<std::string>("coefficients"));
	m_functionType = (FunctionType)t.get<int>("functionType");
	return true;
}

bool Interpolation::saveFileTree(boost::property_tree::ptree& t) const
{
	t.put("coefficients", Serialisation::floatingVectToStr<float>(m_coefficients));
	t.put("functionType", (int)m_functionType);
	return true;
}
