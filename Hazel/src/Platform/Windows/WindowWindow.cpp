#include "hzpch.h"
#include "WindowWindow.h"

namespace Hazel {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowWindow(props);
	}

	WindowWindow::WindowWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowWindow::~WindowWindow()
	{
		Shutdown();
	}

	void WindowWindow::Init(const WindowProps& props)
	{

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		//HZ_CORE_INFO("Create window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) 
		{
			int success = glfwInit();
			HZ_CORE_ASSERT(success, "Could not initialize GLFW!");

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
	}

	void WindowWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}
