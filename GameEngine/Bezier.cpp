#include "Bezier.h"
#include "Texture.h"

#include "json.h"

#include <iostream>
#include <fstream>
#include "Texture.h"


using namespace Engine;

Math::Math()
{

}

Math::~Math() 
{

}

void Math::start()
{
	read_json_data(m_data_filename);
	
	surface_calc();

	// Renderer init
	m_surface = new model_t();

	tinyobj::material_t mat;
	mat.ambient[0] = 1.f; mat.ambient[1] = 1.f; mat.ambient[2] = 1.f;
	mat.diffuse[0] = 1.f; mat.diffuse[1] = 1.f; mat.diffuse[2] = 1.f;
	m_surface->materials.push_back(mat);


	m_surface->name = "math_bz_surface";
	Renderer::AddModel(m_surface);
	compileForOpenGL();


    //m_renderer->SetTexture(Texture::LoadTexture("../Ressources/Textures/checker.png"));
    //m_renderer->SetTexture(Texture::LoadTexture("..\\Ressources\\Textures\\tile.png"));


	m_renderer->SetModel("math_bz_surface");
	m_renderer->SetMaterial(0);
	m_renderer->SetShader(Core::Get()->m_shaders.GetShader(0));
}

void Math::compileForOpenGL()
{
	int nb_row = m_precision + 1;
	int nb_col = m_precision + 1;

	for (int i = 0; i < nb_row - 1; ++i)
	{
		for (int j = 0; j < nb_col - 1; ++j)
		{
			// Square
            glm::vec2 uv(0.f, 1.f);
            //glm::vec2 uv(float(i) / float(nb_col-1), float(j) / float(nb_col - 1));
				glm::vec3 normal = glm::cross(m_curve_points[(i + 1) * nb_col + j] - m_curve_points[i * nb_col + j], m_curve_points[i * nb_col + j] - m_curve_points[(i + 1) * nb_col + j + 1]);
            //glm::vec3 normal = glm::cross(m_curve_points[i * nb_col + j], m_curve_points[(i + 1) * nb_col + j]);
            glm::normalize(normal);

                glm::vec3 normal2 = glm::cross(m_curve_points[(i + 1) * nb_col + j + 1] - m_curve_points[i * nb_col + j + 1], m_curve_points[(i + 1) * nb_col + j + 1] - m_curve_points[i * nb_col + j]);
                glm::normalize(normal2);

                // Triangle
				vbo.push_back(m_curve_points[i * nb_col + j].x);//A
				vbo.push_back(m_curve_points[i * nb_col + j].y);
				vbo.push_back(m_curve_points[i * nb_col + j].z);
				vbo.push_back(normal.x); vbo.push_back(normal.y); vbo.push_back(normal.z);
				vbo.push_back(0); vbo.push_back(0);

				vbo.push_back(m_curve_points[(i + 1) * nb_col + j].x);//D
				vbo.push_back(m_curve_points[(i + 1) * nb_col + j].y);
				vbo.push_back(m_curve_points[(i + 1) * nb_col + j].z);
				vbo.push_back(normal.x); vbo.push_back(normal.y); vbo.push_back(normal.z);
				vbo.push_back(1); vbo.push_back(0);

				vbo.push_back(m_curve_points[(i + 1) * nb_col + j + 1].x);//C
				vbo.push_back(m_curve_points[(i + 1) * nb_col + j + 1].y);
				vbo.push_back(m_curve_points[(i + 1) * nb_col + j + 1].z);
				vbo.push_back(normal.x); vbo.push_back(normal.y); vbo.push_back(normal.z);
				vbo.push_back(1); vbo.push_back(1);

				// Triangle
				vbo.push_back(m_curve_points[(i + 1) * nb_col + j + 1].x);//C
				vbo.push_back(m_curve_points[(i + 1) * nb_col + j + 1].y);
				vbo.push_back(m_curve_points[(i + 1) * nb_col + j + 1].z);
				vbo.push_back(normal2.x); vbo.push_back(normal2.y); vbo.push_back(normal2.z);
				vbo.push_back(1); vbo.push_back(1);

				vbo.push_back(m_curve_points[i * nb_col + j + 1].x);//B
				vbo.push_back(m_curve_points[i * nb_col + j + 1].y);
				vbo.push_back(m_curve_points[i * nb_col + j + 1].z);
				vbo.push_back(normal2.x); vbo.push_back(normal2.y); vbo.push_back(normal2.z);
				vbo.push_back(0); vbo.push_back(1);

				vbo.push_back(m_curve_points[i * nb_col + j].x);//A
				vbo.push_back(m_curve_points[i * nb_col + j].y);
				vbo.push_back(m_curve_points[i * nb_col + j].z);
				vbo.push_back(normal2.x); vbo.push_back(normal2.y); vbo.push_back(normal2.z);
				vbo.push_back(0); vbo.push_back(0);

			for (int i = 0; i < 6; ++i) {
				ibo.push_back(ibo.size());
			}
		}
	}

	m_surface->vertices_size = vbo.size();
	m_surface->vertices = &vbo[0];
	m_surface->indexes_size = ibo.size();
	m_surface->indexes = &ibo[0];
	m_surface->vbo_ibo_index = Core::Get()->CreateGLBuffer(m_surface->vertices, m_surface->indexes, m_surface->vertices_size, m_surface->indexes_size);
}

// Surface

void Math::surface_calc()
{
	int n = 0;
	for (int i = 0; i <= m_precision; i++)
	{
		float u = (float)i / (float)m_precision;


		for (int j = 0; j <= m_precision; j++)
		{
			float v = (float)j / (float) m_precision;

			std::vector<glm::vec3> q_points;
			for (int q = 0; q < m_subdivision[0]; q++) 
			{
				std::vector<glm::vec3> line_points;
				for (int z = 0; z < m_subdivision[1]; z++)
					line_points.push_back(m_control_points[q * m_subdivision[1] + z]);

				q_points.push_back(de_castle_jau(line_points, v));
			}

			m_curve_points.push_back(de_castle_jau(q_points, u));
		}
	}
}

// IO

void Math::read_json_data(std::string filename)
{
	std::ifstream input_file(filename);
	nlohmann::json j; input_file >> j;

	std::vector<int> j_size = j["size"].get<std::vector<int>>();
	m_subdivision[0] = j_size[0] + 1;
	m_subdivision[1] = j_size[1] + 1;

	m_precision = j["precision"].get<int>();

	nlohmann::json j_points = j["control_points"];
	for (auto points_it = j_points.begin(); points_it != j_points.end(); ++points_it)
	{
		std::vector<float> r_coord = points_it.value().get<std::vector<float>>();
		glm::vec3 coord(r_coord[0], r_coord[1], r_coord[2]);
		m_control_points.push_back(coord);
	}

	input_file.close();
}


// Math

int Math::factorial(int n)
{
	int r = 1;
	for (int i = n; i>0; i--) { r *= i; }
	return r;
}

float Math::bernstein(int i, int n, int t)
{
	float r = (float)factorial(n) / (float)(factorial(i) * factorial(n - i));
	r *= pow(t, i);
	r *= pow(1 - t, n - i);
	return r;
}

glm::vec3 Math::de_castle_jau(std::vector<glm::vec3> points, float t)
{
	for (int k = 1; k <= points.size(); k++)
	{
		for (int j = 0; j < points.size() - k; j++)
		{
            points[j] = glm::vec3(
				(1 - t) * points[j].x + t * points[j + 1].x,
				(1 - t) * points[j].y + t * points[j + 1].y,
				(1 - t) * points[j].z + t * points[j + 1].z
			);
		}
	}

	return glm::vec3(points[0].x, points[0].y, points[0].z);
}