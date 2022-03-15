#include "sb7.h"


class TriangleMovement : public sb7::application
{
public:
	void init()
	{
		static const char title[] = "Triangle Movement";

		sb7::application::init();

		memcpy(info.title, title, sizeof(title));
	}


	GLuint compile_shaders(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		//������ɫ��Դ����//L("")

		
		/*static const GLchar* vertex_shader_source[] =
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
		};*/
		
		static const GLchar* vertex_shader_source[] =
		{
			"#version 450 core													\n"
			"layout(location = 0) in vec4 offset;								\n"
			"																	\n"	
			"void main(void)													\n"
			"{																	\n"
			"	const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),	\n"
			"									vec4(-0.25,-0.25,0.5,1.0),		\n"
			"									vec4(0.0,0.25,0.5,1.0));		\n"
			
			"	gl_Position = vertices[gl_VertexID] + offset;					\n"
			"}																	\n"

		};


		//Ƭ����ɫ��Դ����


		static const GLchar* fragment_shader_source[] =
		{
			"#version 450 core												\n"
			"out vec4 color;												\n"
			"void main(void)												\n"
			"{																\n"
			"																\n"
			"	color = vec4( 0.6f,											\n"
			"				  0.8f,											\n"
			"					1f,											\n"
			"				1.0);											\n"
			"}																\n"
		};




		//���������붥����ɫ��
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);//��������ɫ���������ڽ���Դ���벢����
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);//����ɫ��Դ�봫�ݸ���ɫ�������Ա���Դ���븱��
		glCompileShader(vertex_shader);//������ɫ�������а�����Դ����

		//����������Ƭ����ɫ��
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		//�������򡢸�����ɫ�����ˡ�����
		program = glCreateProgram();//����������󣬿ɽ���ɫ�����󸽼ӵ��������
		glAttachShader(program, vertex_shader);//������ɫ�����󵽳������
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);//�����ӵ�����������ɫ������������һ��

		//��ɫ�������Ӳ���������program�����ɾ��
		glDeleteShader(vertex_shader);//ɾ����ɫ�����󣬲�����Ҫ
		glDeleteShader(fragment_shader);


		return program;//����������Ⱦ�ı�ʾ��ʽΪ�м�����ƵĿ�ִ���ļ�
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
		float r = 0.7f*0.25f + 0.75f;

		float g = 0.2f*0.25f + 0.75f;

		float b = 0.4f*0.25f + 0.75f;

		const GLfloat color[] = { r,
								  g,
								  b,
								  1.0f };

		glClearBufferfv(GL_COLOR, 0, color);

		///////////////////////////////////////////


		glUseProgram(rendering_program);

		GLfloat attrib[] = { (float)cos(currentTime) *0.6f,
						   (float)sin(2*currentTime)*0.6f,
							0.0f,0.0f };

		glVertexAttrib4fv(0, attrib);


		glDrawArrays(GL_TRIANGLES, 0, 3);



	}
private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

DECLARE_MAIN(TriangleMovement);




