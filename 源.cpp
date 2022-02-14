#include "sb7.h"

class AHelloWorld :public sb7::application
{
public:

	void init()
	{
		static const char title[] = "HelloooOOOOpenGL";

		sb7::application::init();

		memcpy(info.title, title, sizeof(title));
	}
	void render(double currentTime)
	{
		float r = (float)sin(currentTime)*0.25f + 0.75f;
			
		float g = (float)cos(currentTime)*0.25f + 0.75f;

		float b = (float)cos(currentTime+1)*0.25f + 0.75f;

		const GLfloat color[] = { r,
								  g,
								  b,
								  1.0f };

		glClearBufferfv(GL_COLOR, 0, color);

	}
};

DECLARE_MAIN(AHelloWorld);

