#include "GuiTest.hpp"
#include "GuiRenderer.hpp"
#include "engine/opengl/opengl.hpp"
#include "engine/system/Time.hpp"
#include "zengui/Text.hpp"

using namespace zn;

namespace experimental
{
	GuiTest::GuiTest() : ABasicGame(800, 600, "zENGui - test")
	{}

	GuiTest::~GuiTest()
	{}

	bool GuiTest::init()
	{
		if(!m_shader.load("assets\\shaders\\basic.vert", "assets\\shaders\\tvstatic.frag"))
			return false;

		m_gui = new ui::Root(m_window.getSize().x, m_window.getSize().y);
		m_gui->setRenderer(new GuiRenderer());
		if(!m_gui->installSkin(new BasicSkin()))
			return false;
		m_gui->setSkin("Basic");

		r_panel = new ui::Panel();
		r_panel->setID("myFirstPanel");
		r_panel->setBounds(IntRect(100, 100, 300, 250));
		m_gui->add(r_panel);

		ui::Panel * panel2 = new ui::Panel();
		panel2->setID("myPanel2");
		panel2->setBounds(IntRect(400, 200, 600, 300));
		m_gui->add(panel2);

		ui::Panel * panel3 = new ui::Panel();
		panel3->setID("myPanel3");
		panel3->setBounds(IntRect(10, 150, 20, 30));
		r_panel->add(panel3);

		ui::Text * text = new ui::Text();
		text->setID("myText");
		text->setText("This is not a sample text");
		r_panel->add(text);

		return true;
	}

	void GuiTest::dispose()
	{
		delete m_gui;
	}

	void GuiTest::resized(const Vector2i & newSize)
	{
	}

	void GuiTest::processEvent(const sf::Event & event)
	{
		m_guiInput.forward(event, *m_gui);
	}

	void GuiTest::update(const zn::Time & delta)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			r_panel->setBounds(IntRect(r_panel->getBounds()).offset(-1, 0));
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			r_panel->setBounds(IntRect(r_panel->getBounds()).offset(1, 0));
		}

		m_gui->animate(delta.hz());
	}

	void GuiTest::renderScene(const Time & delta)
	{
		glClearColor(0.2f, 0.1f, 0, 1.f);
	}

	void GuiTest::renderGUI(const zn::Time & delta)
	{
//		m_shader.bind();
//		m_shader.setUniform("time", m_time.getElapsedTime().asSeconds());
		m_gui->render();
//		m_shader.unbind();
	}

} // namespace experimental



