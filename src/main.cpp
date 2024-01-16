#include <EngineCore/System/Log.h>
#include <EngineCore/Resources/ResourceManager.h>
#include <EngineCore/Engine/Application.h>
#include <EngineCore/Engine/Window.h>
#include <EngineCore/Renderer/Renderer.h>
#include <EngineCore/Renderer/Camera.h>
#include <EngineCore/System/ShadersSettings.h>
#include <EngineCore/GUI/GUI_place.h>
#include <EngineCore/GUI/ScrollBox.h>
#include <EngineCore/GUI/Button.h>
#include <EngineCore/GUI/Sprite.h>
#include <EngineCore/GUI/Font.h>
#include <EngineCore/GUI/ScrollBox.h>

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
		m_cam = new Camera();

		m_cam->set_viewport_size(static_cast<float>(m_pWindow->get_size().x), static_cast<float>(m_pWindow->get_size().y));

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
			glm::vec2(50.f, 50.f), glm::vec2(12.f, 15.f), "TestScrollbox", 10, ResourceManager::getMaterial("default"), false, nullptr, false, false);

		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b1"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b2"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b3"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b4"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b5"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b6"));
		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->add_element(m_gui->get_element<GUI::Button>("b7"));

		m_gui->get_element<GUI::ScrollBox>("TestScrollbox")->set_active(true);

		m_gui->set_active(true);

		return true;
	}

    void init_events() override
    {
		m_event_dispather.add_event_listener<EventWindowResize>([&](EventWindowResize& e) {
			m_cam->set_viewport_size(e.width, e.height);
			if (m_gui) m_gui->on_resize();
			});
		m_event_dispather.add_event_listener<EventMouseButtonPressed>([&](EventMouseButtonPressed& e)
			{
				if (m_gui)
				{
					m_gui->on_key_press((KeyCode)e.mouse_button);
					m_gui->on_mouse_press(e.x_pos, e.y_pos);
				}
			});
		m_event_dispather.add_event_listener<EventMouseButtonReleased>([&](EventMouseButtonReleased& e)
			{
				if (m_gui) m_gui->on_mouse_release(e.x_pos, e.y_pos);
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
	}

	void on_render()
	{
		// clear screen
		RenderEngine::Renderer::setClearColor(0.33f, 0.33f, 0.33f, 1.f);
		RenderEngine::Renderer::clearColor();

	}

	void on_ui_render()
	{
		m_gui->on_render();
	}

private:
	GUI::GUI_place* m_gui;
	Camera* m_cam;
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