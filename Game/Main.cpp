#include "core.h"
#include <iostream>

bool Update(float dt)
{
	return false;
}

void Draw(Core::Graphics& graphics)
{
	for (int i = 0; i < rand() % 256; i++) {
		graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
		graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
	}
}



int main()
{
	char name[] = "CSC196";
	Core::Init(name, 800, 600);

	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);


	Core::GameLoop();
	Core::Shutdown();
}
