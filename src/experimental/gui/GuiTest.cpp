#include "GuiTest.hpp"
#include "GuiRenderer.hpp"

#include "engine/opengl/opengl.hpp"
#include "engine/system/Time.hpp"

#include "zengui/Text.hpp"
#include "zengui/skins/BasicSkin.hpp"
#include "zengui/DragZone.hpp"
#include "zengui/PushButton.hpp"

using namespace zn;

namespace experimental
{
	GuiTest::GuiTest() : ABasicGame(800, 600, "zENGui - test")
	{}

	GuiTest::~GuiTest()
	{}

	bool GuiTest::init()
	{
		if(!m_shader.load("assets/shaders/basic.vert", "assets/shaders/tvstatic.frag"))
			return false;

		//
		// GUI setup
		//

		m_gui = new ui::Root(m_window.getSize().x, m_window.getSize().y);
		m_gui->setRenderer(new GuiRenderer());
		if(!m_gui->installSkin(new ui::BasicSkin("Basic", "assets/fonts/tahoma16.fnt")))
			return false;
		m_gui->setSkin("Basic");

		//
		// Panel 1
		//

		r_panel = new ui::Panel();
		r_panel->setID("myFirstPanel");
		r_panel->setLocalBounds(IntRect(100, 100, 300, 250));
		r_panel->setAlign(ui::CENTER_H | ui::FILL_H | ui::TOP);

		ui::PushButton * button = new ui::PushButton();
		button->setID("myButton");
		button->setText("My big button");
		button->setLocalBounds(IntRect(10, 120, 100, 140));
		button->onClickSignal.connect([](){
			std::cout << "Hello world !" << std::endl;
		});
		r_panel->add(button);

		r_text = new ui::Text();
		r_text->setID("myText");
		r_text->setWrap(true);
		r_text->setLocalBounds(IntRect(10, 10, 190, 110));
		r_text->setText("This is not a sample text. This is a brand new "
						"testing system involving character strings linked "
						"together in a byte-based dynamic array, also called "
						"std::string.");
		r_panel->add(r_text);

		m_gui->add(r_panel);

		//
		// Panel 2
		//

		ui::Panel * panel2 = new ui::Panel();
		panel2->setID("myPanel2");
		panel2->setLocalBounds(IntRect(400, 200, 600, 300));

		ui::DragZone * dragZone = new ui::DragZone();
		dragZone->setLocalBounds(IntRect(0, 0, 200, 50));
		panel2->add(dragZone);

		m_gui->add(panel2);

		m_gui->layout();

		return true;
	}

	void GuiTest::dispose()
	{
		delete m_gui;
	}

	void GuiTest::resized(const Vector2i & /*newSize*/)
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
			//r_panel->setBounds(IntRect(r_panel->getBounds()).offset(-1, 0));
			r_text->setLocalBounds(r_text->getLocalBounds().contract(-1, 0));
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			//r_panel->setBounds(IntRect(r_panel->getBounds()).offset(1, 0));
			r_text->setLocalBounds(r_text->getLocalBounds().expand(1, 0));
		}

		m_gui->animate(delta.hz());
	}

	void GuiTest::renderScene(const Time & /*delta*/)
	{
		glClearColor(0.2f, 0.1f, 0, 1.f);
	}

	void GuiTest::renderGUI(const zn::Time & /*delta*/)
	{
//		m_shader.bind();
//		m_shader.setUniform("time", m_time.getElapsedTime().asSeconds());
		m_gui->render();
//		m_shader.unbind();
	}

} // namespace experimental



