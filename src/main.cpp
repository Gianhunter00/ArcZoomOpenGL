#include <iostream>
#include "Window.h"
#include "Ex12ArcZoom.h"

static float zoom = 1;
static float left_right = 0;
static float up_down = 0;
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && (action == GLFW_PRESS || action == GLFW_REPEAT))
        zoom += 0.1f;
	if (key == GLFW_KEY_Q && (action == GLFW_PRESS || action == GLFW_REPEAT))
        zoom -= 0.1f;
	if(key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
		left_right += 2.f;
	if(key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
		left_right -= 2.f;
	if(key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
		up_down += 2.f;
	if(key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
		up_down -= 2.f;
}

int main() {
	std::cout << "It' Working" << std::endl;

	Window* Win = new Window(800, 600, "OpenGL Window");
	
	float TimeElapsed = 0.f;

	Ex12ArcZoom Scene;
	Scene.Start();
	Win->SetCallbackKey(key_callback);
	// till Window is not in closing
	while (Win->IsOpened())
	{
		// update fps 1 sec
		TimeElapsed += Win->GetDeltaTime();
		if (TimeElapsed >= 1.f)
		{
			TimeElapsed -= 1.f;
			int Fps = 1.f / Win->GetDeltaTime();
			char Title[50];
			sprintf_s(Title, sizeof(Title), "OpenGL App | DeltaTime: %f - FPS: %d", Win->GetDeltaTime(), Fps);

			Win->SetTitle(Title);
		}

		// Scene.Update(Win->GetDeltaTime());
		Scene.Update(zoom, left_right, up_down);
		
		Win->Update();
	}

	Scene.Destroy();
	delete Win;
	return 0;	
}