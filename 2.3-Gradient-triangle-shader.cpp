#include "sb7.h"


class MyFirstShader : public sb7::application
{
public:
	void init()
	{
		static const char title[] = "My First Shader";

		sb7::application::init();

		memcpy(info.title, title, sizeof(title));
	}


	GLuint compile_shaders(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		//顶点着色器源代码//L("")
		
		static const GLchar* vertex_shader_source[] =
		{
			"#version 450 core 												\n"
			"																\n"
			"void main(void)												\n"
			"{																\n"
			"	const vec4 vertices[3] = vec4[3](vec4(0.25,-0.25,0.5,1.0),  \n"
			"									 vec4(-0.25,-0.25,0.5,1.0),	\n"
			"									 vec4(0.0,0.25,0.5,1.0));	\n"
			"   gl_Position = vertices[gl_VertexID]	;						\n"
			"}																\n"
		};

		

		//片段着色器源代码
		

		static const GLchar* fragment_shader_source[] =
		{
			"#version 450 core												\n"
			"out vec4 color;												\n"
			"void main(void)												\n"
			"{																\n"
			"	color = vec4(sin(gl_FragCoord.x* 0.275)* 0.25f + 0.75f,		\n"
			"				 cos(gl_FragCoord.y* 0.275)* 0.25f + 0.75f,		\n"
			"				 sin(gl_FragCoord.y* 0.275)* 0.25f + 0.75f,	\n"
			"				 1.0);											\n"
			"}																\n"
		};

		


		//创建并编译顶点着色器
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);//创建空着色器对象，用于接收源代码并编译
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);//将着色器源码传递给着色器对象，以保留源代码副本
		glCompileShader(vertex_shader);//编译着色器对象中包含的源代码

		//创建并编译片段着色器
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		//创建程序、附加着色器至此、连接
		program = glCreateProgram();//创建程序对象，可将着色器对象附加到程序对象
		glAttachShader(program, vertex_shader);//附加着色器对象到程序对象
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);//将附加到程序对象的着色器对象连接至一起

		//着色器被附加并连接至“program”后就删除
		glDeleteShader(vertex_shader);//删除着色器对象，不再需要
		glDeleteShader(fragment_shader);


		return program;//返回用于渲染的表示形式为中间二进制的可执行文件
	}


	void startup()
	{
		rendering_program = compile_shaders();


		glCreateVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

	}

	void shutdown()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
		glDeleteVertexArrays(1, &vertex_array_object);

	}


	void render(double currentTime)
	{
		float r = (float)sin(currentTime)*0.25f + 0.75f;

		float g = (float)cos(currentTime)*0.25f + 0.75f;

		float b = (float)cos(currentTime + 1)*0.25f + 0.75f;

		const GLfloat color[] = { r,
								  g,
								  b,
								  1.0f };

		glClearBufferfv(GL_COLOR, 0, color);

		///////////////////////////////////////////

		glUseProgram(rendering_program);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
	

	}
private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

DECLARE_MAIN(MyFirstShader);




