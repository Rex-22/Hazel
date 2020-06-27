#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"
#include "TestingLayer.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		// PushLayer(new ExampleLayer());
		// PushLayer(new Sandbox2D());
		PushLayer(new TestingLayer());
	}

	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
