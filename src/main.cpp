#include <EngineCore/System/Log.h>
#include <EngineCore/Resources/ResourceManager.h>
#include <EngineCore/Resources/Scene.h>
#include <EngineCore/Engine/Application.h>
#include <EngineCore/Engine/Window.h>
#include <EngineCore/Renderer/Renderer.h>
#include <EngineCore/Renderer/Camera.h>
#include <EngineCore/Renderer/PostProcessor.h>
#include <EngineCore/Renderer/Material.h>
#include <EngineCore/Renderer3D/Skybox.h>
#include <EngineCore/Renderer3D/GraphicsObject.h>
#include <EngineCore/Light/DirectionalLight.h>
#include <EngineCore/System/ShadersSettings.h>
#include <EngineCore/System/Input.h>
#include <EngineCore/Meshes/Cube.h>
#include <EngineCore/Meshes/GraphicsModel.h>
#include <EngineCore/Components/Transform.h>
#include <EngineCore/Components/Highlight.h>
#include <EngineCore/GUI/GUI_place.h>
#include <EngineCore/GUI/TextRenderer.h>
#include <EngineCore/GUI/ScrollBox.h>
#include <EngineCore/GUI/Button.h>
#include <EngineCore/GUI/Sprite.h>
#include <EngineCore/GUI/Font.h>
#include <EngineCore/GUI/ScrollBox.h>

#include <vector>

#define GET_DATA_MATERIAL(name_material, type, name_data, index) ResourceManager::getMaterial(name_material)->get_data<type>(name_data)[index]

bool isKeyPressed = false;
bool enableMSAA = false;

class TestApp : public Application
{
public:
	TestApp()
	{
		// Don't init here, init OpenGL and many other be after start func call
	}
	~TestApp()
	{

	}
	bool init() override
	{
		m_postprc = new RenderEngine::PostProcessor(ResourceManager::getShaderProgram("postShader"), m_pWindow->get_size().x, m_pWindow->get_size().y, true, 8);

		m_postprc->set_effect(0);

		m_count_fps_check = 10;

		GET_DATA_MATERIAL("castle", float, "ambient_factor", 0) = 0.5f;
		GET_DATA_MATERIAL("castle", float, "diffuse_factor", 0) = 0.1f;
		GET_DATA_MATERIAL("castle", float, "specular_factor", 0) = 0.0f;
		GET_DATA_MATERIAL("castle", float, "metalic_factor", 0) = 0.0f;
		GET_DATA_MATERIAL("castle", float, "shininess", 0) = 0.1f;
		GET_DATA_MATERIAL("castle", int, "level_graphics", 0) = 1;

		GET_DATA_MATERIAL("defaultCube", float, "ambient_factor", 0) = 0.6f;
		GET_DATA_MATERIAL("defaultCube", float, "diffuse_factor", 0) = 0.1f;
		GET_DATA_MATERIAL("defaultCube", float, "specular_factor", 0) = 0.0f;
		GET_DATA_MATERIAL("defaultCube", float, "metalic_factor", 0) = 0.0f;
		GET_DATA_MATERIAL("defaultCube", float, "shininess", 0) = 0.1f;
		GET_DATA_MATERIAL("defaultCube", int, "level_graphics", 0) = 1;

		GET_DATA_MATERIAL("default", float, "sourceColor", 0) = 0.8f;
		GET_DATA_MATERIAL("default", float, "sourceColor", 1) = 0.3f;
		GET_DATA_MATERIAL("default", float, "sourceColor", 2) = 0.6f;
		GET_DATA_MATERIAL("default", float, "sourceColor", 3) = 1.f;

		m_cam = new Camera();

		m_cam->set_viewport_size(static_cast<float>(m_pWindow->get_size().x), static_cast<float>(m_pWindow->get_size().y));

		m_obj = ResourceManager::getGraphicsObject("castle");

		std::vector<std::string> names;
		names.push_back("default3DShader");

		m_scene.add_object<DirectionalLight>(names);
		cube = new Cube(ResourceManager::getMaterial("castle"));
		models.push_back(new GraphicsModel(ResourceManager::getGraphicsObject("castle"), ResourceManager::getMaterial("castle")));
		models.back()->addComponent<Transform>(glm::vec3(0.f, 0.f, 0.f));
		models.push_back(new GraphicsModel(ResourceManager::getGraphicsObject("castle"), ResourceManager::getMaterial("castle")));
		models.back()->addComponent<Transform>(glm::vec3(5.f, 0.f, 0.f));
		models.push_back(new GraphicsModel(ResourceManager::getGraphicsObject("castle"), ResourceManager::getMaterial("castle")));
		models.back()->addComponent<Transform>(glm::vec3(10.f, 0.f, 0.f));
		models.push_back(new GraphicsModel(ResourceManager::getGraphicsObject("castle"), ResourceManager::getMaterial("castle")));
		models.back()->addComponent<Transform>(glm::vec3(15.f, 0.f, 0.f));
		models.push_back(new GraphicsModel(ResourceManager::getGraphicsObject("castle"), ResourceManager::getMaterial("castle")));
		models.back()->addComponent<Transform>(glm::vec3(20.f, 0.f, 0.f));
		models.push_back(new GraphicsModel(ResourceManager::getGraphicsObject("castle"), ResourceManager::getMaterial("castle")));
		models.back()->addComponent<Transform>(glm::vec3(25.f, 0.f, 0.f));
		models.push_back(new GraphicsModel(ResourceManager::getGraphicsObject("castle"), ResourceManager::getMaterial("castle")));
		models.back()->addComponent<Transform>(glm::vec3(30.f, 0.f, 0.f));
		//model->addComponent<Highlight>(ResourceManager::getMaterial("default"), true, true, glm::vec3(1.f));
		
		//m_scene.at(1)->addComponent<Transform>(glm::vec3(0.f), glm::vec3(2.f));
		//m_scene.at(2)->addComponent<Transform>(glm::vec3(0.f, 0.f, 1.f), glm::vec3(2.f));

		m_gui = new GUI::GUI_place(m_cam, ResourceManager::getMaterial("default"));

		ResourceManager::get_font("agaaler")->set_scale(0.2f);

		float offset = 11.f;

		m_gui->add_element<GUI::Button>(new GUI::Sprite(ResourceManager::getMaterial("button"), "static"),
			glm::vec2(50.f, offset), glm::vec2(10.f, 5.f), "hello1", ResourceManager::getShaderProgram("textShader"),
			ResourceManager::get_font("agaaler"), glm::vec3(1.f), "b1");
		offset += 11.f;

		m_gui->add_element<GUI::Button>(new GUI::Sprite(ResourceManager::getMaterial("button"), "static"),
			glm::vec2(50.f, offset), glm::vec2(10.f, 5.f), "hello2", ResourceManager::getShaderProgram("textShader"),
			ResourceManager::get_font("agaaler"), glm::vec3(1.f), "b2");
		offset += 11.f;

		m_gui->add_element<GUI::Button>(new GUI::Sprite(ResourceManager::getMaterial("button"), "static"),
			glm::vec2(50.f, offset), glm::vec2(10.f, 5.f), "hello3", ResourceManager::getShaderProgram("textShader"),
			ResourceManager::get_font("agaaler"), glm::vec3(1.f), "b3");
		offset += 11.f;

		m_gui->add_element<GUI::Button>(new GUI::Sprite(ResourceManager::getMaterial("button"), "static"),
			glm::vec2(50.f, offset), glm::vec2(10.f, 5.f), "hello4", ResourceManager::getShaderProgram("textShader"),
			ResourceManager::get_font("agaaler"), glm::vec3(1.f), "b4");
		offset += 11.f;

		m_gui->add_element<GUI::Button>(new GUI::Sprite(ResourceManager::getMaterial("button"), "static"),
			glm::vec2(50.f, offset), glm::vec2(10.f, 5.f), "hello5", ResourceManager::getShaderProgram("textShader"),
			ResourceManager::get_font("agaaler"), glm::vec3(1.f), "b5");
		offset += 11.f;

		m_gui->add_element<GUI::Button>(new GUI::Sprite(ResourceManager::getMaterial("button"), "static"),
			glm::vec2(50.f, offset), glm::vec2(10.f, 5.f), "hello6", ResourceManager::getShaderProgram("textShader"),
			ResourceManager::get_font("agaaler"), glm::vec3(1.f), "b6");
		offset += 11.f;

		m_gui->add_element<GUI::Button>(new GUI::Sprite(ResourceManager::getMaterial("button"), "static"),
			glm::vec2(50.f, offset), glm::vec2(10.f, 5.f), "hello6", ResourceManager::getShaderProgram("textShader"),
			ResourceManager::get_font("agaaler"), glm::vec3(1.f), "b7");

		m_gui->add_element<GUI::ScrollBox>(new GUI::Sprite(ResourceManager::getMaterial("defaultSprite")),
			glm::vec2(50.f, 50.f), glm::vec2(40.f, 25.f), "TestScrollbox", 10, ResourceManager::getMaterial("default"), false, nullptr, true, false);

		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b1"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b2"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b3"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b4"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b5"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b6"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b7"));

		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->set_active(false);

		m_gui->add_element<GUI::TextRenderer>(-2, ResourceManager::get_font("calibriChat"), ResourceManager::getShaderProgram("textShader"),
			"FPS: 0", glm::vec3(0.f), glm::vec2(0.1f, offset), glm::vec2(0.5f), "fps", false);
		offset += 5.f;

		m_gui->add_element<GUI::TextRenderer>(-2, ResourceManager::get_font("calibriChat"), ResourceManager::getShaderProgram("textShader"),
			"disable", glm::vec3(0.f), glm::vec2(0.1f, offset), glm::vec2(0.5f), "switch", false);
		offset += 5.f;

		m_gui->add_element<GUI::TextRenderer>(-2, ResourceManager::get_font("calibriChat"), ResourceManager::getShaderProgram("textShader"),
			"-", glm::vec3(0.f), glm::vec2(0.1f, offset), glm::vec2(0.5f), "switch1", false);

		m_gui->set_active(true);

		m_postprc->set_active(true);

		std::vector<std::string> faces
		{
			"systemres/textures/skybox_1/right.jpg",
			"systemres/textures/skybox_1/left.jpg",
			"systemres/textures/skybox_1/top.jpg",
			"systemres/textures/skybox_1/bottom.jpg",
			"systemres/textures/skybox_1/front.jpg",
			"systemres/textures/skybox_1/back.jpg"
		};
		skybox = new RenderEngine::Skybox(faces, ResourceManager::getShaderProgram("skyboxShader").get());

		m_cam->set_far_clip_plane(300);

		return true;
	}

    void init_events() override
    {
		m_event_dispather.add_event_listener<EventWindowResize>([&](EventWindowResize& e) {
			m_cam->set_viewport_size(e.width, e.height);
			if (m_gui) m_gui->on_resize();
			m_postprc->on_resize(e.width, e.height);
			});
		m_event_dispather.add_event_listener<EventMouseButtonPressed>([&](EventMouseButtonPressed& e)
			{
				if (m_gui)
				{
					m_gui->on_key_press((KeyCode)e.mouse_button);
					m_gui->on_mouse_press(e.x_pos, e.y_pos);
				}
				m_init_mouse_pos_x = e.x_pos;
				m_init_mouse_pos_y = e.y_pos;
			});
		m_event_dispather.add_event_listener<EventMouseButtonReleased>([&](EventMouseButtonReleased& e)
			{
				if (m_gui) m_gui->on_mouse_release(e.x_pos, e.y_pos);
			});
		m_event_dispather.add_event_listener<EventKeyReleased>([&](EventKeyReleased& e)
			{
				isKeyPressed = false;
			});
		m_event_dispather.add_event_listener<EventMouseScrolled>([&](EventMouseScrolled& e)
			{
				if (m_gui)
				{
					m_gui->on_mouse_scroll(-e.y_offset);
				}
			});
    }

	void terminate() override
	{
		delete m_cam;
		delete m_gui;
	}

	void on_update(const double delta)
	{
		m_gui->on_update(delta);

		m_scene.update(delta);
	}

	void on_key_update(const double delta) override
	{
		glm::vec3 movement_delta{ 0,0,0 };
		glm::vec3 rotation_delta{ 0,0,0 };

		double addSpeed = 1;

		if (Input::isKeyPressed(KeyCode::KEY_R) && !isKeyPressed)
		{
			m_postprc->change_active();
			m_gui->get_element<GUI::TextRenderer>("switch1")->set_text(m_postprc->get_active() ? "+" : "-");
			isKeyPressed = true;
		}
		else if (Input::isKeyPressed(KeyCode::KEY_T) && !isKeyPressed)
		{
			if (enableMSAA)
			{
				m_gui->get_element<GUI::TextRenderer>("switch")->set_text("disable");
				//RenderEngine::Renderer::setActiveMultisampling(false);
				m_postprc->set_acive_msaa(false);
				enableMSAA = false;
			}
			else
			{
				m_gui->get_element<GUI::TextRenderer>("switch")->set_text("enable");
				//RenderEngine::Renderer::setActiveMultisampling(true);
				m_postprc->set_acive_msaa(true);
				enableMSAA = true;
			}
			isKeyPressed = true;
		}
		else if (Input::isKeyPressed(KeyCode::KEY_L) && !isKeyPressed)
		{
			m_postprc->set_effect(0);
		}
		else if (Input::isKeyPressed(KeyCode::KEY_K) && !isKeyPressed)
		{
			m_postprc->set_effect(1);
		}
		else if (Input::isKeyPressed(KeyCode::KEY_J) && !isKeyPressed)
		{
			m_postprc->set_effect(2);
		}
		else if (Input::isKeyPressed(KeyCode::KEY_H) && !isKeyPressed)
		{
			m_postprc->set_effect(3);
		}

		if (Input::isKeyPressed(KeyCode::KEY_W))
		{
			movement_delta.z += static_cast<float>(addSpeed * m_cam_velocity * delta);
		}
		if (Input::isKeyPressed(KeyCode::KEY_S))
		{
			movement_delta.z -= static_cast<float>(addSpeed * m_cam_velocity * delta);
		}
		if (Input::isKeyPressed(KeyCode::KEY_A))
		{
			movement_delta.x -= static_cast<float>(addSpeed * m_cam_velocity * delta);
		}
		if (Input::isKeyPressed(KeyCode::KEY_D))
		{
			movement_delta.x += static_cast<float>(addSpeed * m_cam_velocity * delta);
		}
		if (Input::isKeyPressed(KeyCode::KEY_SPACE))
		{
			movement_delta.y += static_cast<float>(addSpeed * m_cam_velocity * delta);
		}
		if (Input::isKeyPressed(KeyCode::KEY_LEFT_SHIFT))

		{
			movement_delta.y -= static_cast<float>(addSpeed * m_cam_velocity * delta);
		}

		if (Input::isMouseButtonPressed(MouseButton::MOUSE_BUTTON_MIDDLE))
		{
			glm::vec2 pos = m_pWindow->get_current_cursor_position();
			rotation_delta.y = m_isInversiveMouseY
				? (rotation_delta.y + ((m_init_mouse_pos_x - pos.x) / (1 / m_cam_sensetivity)))
				: (rotation_delta.y - ((m_init_mouse_pos_x - pos.x) / (1 / m_cam_sensetivity)));
			rotation_delta.x += (m_init_mouse_pos_y - pos.y) / (1 / m_cam_sensetivity);
			m_init_mouse_pos_x = pos.x;
			m_init_mouse_pos_y = pos.y;
		}

		m_cam->add_movement_and_rotation(movement_delta, rotation_delta);
	}

	void on_render()
	{
		m_postprc->start_render();

		RenderEngine::Renderer::setClearColor(0.8f, 0.8f, 0.8f, 1.f);
		RenderEngine::Renderer::clear();
		RenderEngine::Renderer::setStencilTest(false);
		RenderEngine::Renderer::setStencilMask(true);

		// set matrix
		ResourceManager::getShaderProgram("colorShader")->use();
		ResourceManager::getShaderProgram("colorShader")->setMatrix4(SS_VIEW_PROJECTION_MATRIX_NAME, m_cam->get_projection_matrix() * m_cam->get_view_matrix());
		ResourceManager::getShaderProgram("colorShader")->setVec4(SS_COLOR_PROP_NAME, glm::vec4(1.f, 0.33f, 0.33f, 1.f));

		ResourceManager::getShaderProgram("default3DShader")->use();
		ResourceManager::getShaderProgram("default3DShader")->setVec3("cam_position", m_cam->get_position());
		ResourceManager::getShaderProgram("default3DShader")->setFloat("brightness", 1);
		ResourceManager::getShaderProgram("default3DShader")->setMatrix4(SS_VIEW_PROJECTION_MATRIX_NAME, m_cam->get_projection_matrix() * m_cam->get_view_matrix());
		
		for (auto& model : models)
		{
			model->render();
		}

		skybox->render(m_cam->get_projection_matrix() * glm::mat4(glm::mat3(m_cam->get_view_matrix())));

		m_postprc->end_render();
	}

	void on_ui_render()
	{
		m_gui->get_element<GUI::TextRenderer>("fps")->set_text("FPS: " + std::to_string(m_current_fps));
		m_gui->on_render();
	}

private:

	RenderEngine::Skybox* skybox;
	RenderEngine::PostProcessor* m_postprc;

	std::shared_ptr<GraphicsObject> m_obj;

	unsigned int quadVAO, quadVBO;

	Cube* cube;
	std::vector<GraphicsModel*> models;

	GUI::GUI_place* m_gui;
	Camera* m_cam;
	Scene m_scene;
	double m_init_mouse_pos_x = 0;
	double m_init_mouse_pos_y = 0;

	float m_cam_velocity = 0.01f;
	float m_cam_sensetivity = 0.5f;

	bool m_isInversiveMouseY = false;
};

int main(int argc, char** argv)
{
	glm::ivec2 windowSize(800, 600);

	ResourceManager::setExecutablePath(argv[0]);

	TestApp* app = new TestApp();

	app->start(windowSize, "Test app", "systemres/resources.json", "TestaApp.ini");

	app->stop();
	delete app;

	system("pause");

	return 0;
}