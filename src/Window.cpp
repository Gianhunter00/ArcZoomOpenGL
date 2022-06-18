#include <iostream>
#include "Window.h"
#include "Common.h"

Window::Window(int InWidth, int InHeight, const std::string& InTitle)
 : Width(InWidth), Height(InHeight), Title(InTitle)
{
    DeltaTime = 0.f;
    LastTime = 0.f;
	
	DIE_ON_ERROR(glfwInit(), "Failed to initialize GLFW");

	// hints to init window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	RawWindow = glfwCreateWindow(Width, Height, Title.c_str(), NULL, NULL);
	DIE_ON_NULL(RawWindow, "Error: Opening Window");

    // redirect all commands to window
	glfwMakeContextCurrent(RawWindow);

    // load GLAD
	DIE_ON_ERROR(gladLoadGL(), "Error: GLAD Wrapper");
}

Window::~Window()
{
    glfwDestroyWindow(RawWindow);
    glfwTerminate();
}

void Window::SetCallbackKey(GLFWkeyfun callback)
{
	glfwSetKeyCallback(RawWindow, callback);
}

void Window::SetTitle(const std::string& InTitle)
{
    glfwSetWindowTitle(RawWindow, InTitle.c_str());
}

float Window::GetDeltaTime() const
{
    return DeltaTime;
}

bool Window::IsOpened() const
{
    return !glfwWindowShouldClose(RawWindow);
}

void Window::Update()
{
    float CurrentTime = glfwGetTime();
	DeltaTime = CurrentTime - LastTime;
	LastTime = CurrentTime;
    
    // swap buffers with all draw operations
	glfwSwapBuffers(RawWindow);
	// poll events
	glfwPollEvents();
}

void PrintInfo()
{
	printf("GL VERSION: %s\n", glGetString(GL_VERSION));
	printf("GL RENDERER: %s\n", glGetString(GL_RENDERER));
	printf("GL VENDOR: %s\n", glGetString(GL_VENDOR));
	printf("GLSL VERSION: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

