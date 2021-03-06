#pragma once

#ifndef ENGINE_COREOBJECT_H
#define ENGINE_COREOBJECT_H

#include "GL/glew.h"
#ifdef _MSC_VER
#pragma comment(lib, "glew32.lib")
#endif

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/OpenGL.hpp>

#include "Shader.h"
#include "GameObject.h"
#include "Camera.h"

namespace Engine {

	class Renderer;

	class Skybox;

	class Core {

	private:
		static Core * m_instance;

		std::vector<Renderer*> m_renderers;

		sf::RenderWindow * m_window;

		bool m_waitForLoadScene = false;

		std::string m_scene_file;

		Core& operator=(const Core&) {};
		Core(const Core&) {};

		Core() {};
		~Core() {};

		void InitScene();

	public:
		std::vector<GLuint> m_vbo;
		std::vector<GLuint> m_ibo;
		std::vector<GLuint> m_textures;

		std::vector<GameObject*> m_gameObjects;

		Camera * m_camera;

		Skybox * m_skybox;

		Shader m_shaders;

		float m_deltaTime = 0.f;
		float m_Time = 0.f;

		static Core * Get() {
			if (!m_instance) m_instance = new Core();
			return m_instance;
		}

		static void Kill() {
			delete m_instance;
			m_instance = nullptr;
		}

		void AddRenderer(Renderer *r);

		void RemoveRenderer(Renderer *r);

		sf::RenderWindow * GetWindowContext() {
			return m_window;
		}

		int CreateGLBuffer(GLfloat * vertices, GLuint * indexes, unsigned int size_v, unsigned int size_i);

		void Init();

		void LoadScene(std::string path);

		void Run();

		void ClearScene();

		void Free();

	};

}

#endif