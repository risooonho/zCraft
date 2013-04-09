/*
Container.cpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#include "Container.hpp"
#include "Skin.hpp"

namespace zn
{
namespace ui
{
	void AContainer::setSkin(ISkin & theme, bool recursive)
	{
		r_skin = &theme;
		if(recursive)
		{
			for(auto & child : m_children)
				child->setSkin(theme, recursive);
		}
	}

	bool AContainer::checkChild(const AWidget * child, const std::string & from)
	{
		if(child == nullptr)
		{
			std::cout << "ERROR: AContainer::" << from << ": "
				<< "given widget is null." << std::endl;
			return false;
		}
		if(child == this)
		{
			std::cout << "ERROR: AContainer::" << from << ": "
				<< "can't do that with self."
				<< "ID=\"" << child->getID() << '"' << std::endl;
			return false;
		}
		return true;
	}

	std::list<AWidget*>::iterator
			AContainer::getCheckChild(
					const AWidget * child, const std::string & from)
	{
		if(!checkChild(child, from))
			return m_children.end();

		for(auto it = m_children.begin(); it != m_children.end(); it++)
		{
			if((*it) == child)
				return it;
		}

		std::cout << "ERROR: AContainer::" << from << ": "
			<< "child not found. "
			<< "ID=\"" << child->getID() << '"' << std::endl;
		return m_children.end();
	}

	bool AContainer::contains(const AWidget * child) const
	{
		for(auto it = m_children.begin(); it != m_children.end(); it++)
		{
			if((*it) == child)
				return true;
		}
		return false;
	}

	void AContainer::add(AWidget * child)
	{
		if(!checkChild(child, "add"))
			return;
		if(contains(child))
		{
			std::cout << "ERROR: AContainer::add: "
				<< "can't add twice the same widget. "
				<< "ID=\"" << child->getID() << '"' << std::endl;
			return;
		}

		m_children.push_back(child);

		child->setParent(this);

		if(r_skin != nullptr)
			child->setSkin(*r_skin);
	}

	void AContainer::erase(AWidget * child)
	{
		auto it = getCheckChild(child, "erase");
		if(it != m_children.end())
		{
			delete (*it);
			m_children.erase(it);
		}
	}

	void AContainer::eraseAll()
	{
		for(auto it = m_children.begin(); it != m_children.end(); it++)
			delete (*it);
	}

	AWidget * AContainer::getChildFromID(const std::string & ID)
	{
		AWidget * w;
		for(auto it = m_children.begin(); it != m_children.end(); it++)
		{
			w = (*it);
			if(w->getID() == ID)
				return w;
		}
		return nullptr;
	}

	void AContainer::bringChildToFront(AWidget * child)
	{
		auto it = getCheckChild(child, "bringChildToFront");
		if(it != m_children.end())
		{
			m_children.erase(it);
			m_children.push_front(child);
		}
	}

	void AContainer::focusChild(const AWidget * child)
	{
		if(child == this)
		{
			std::cout << "ERROR: AContainer::focusChild: "
				<< "can't do that with self."
				<< "ID=\"" << child->getID() << '"' << std::endl;
			return;
		}

		AWidget * w;
		for(auto it = m_children.begin(); it != m_children.end(); it++)
		{
			w = (*it);
			w->setFocused(w == child);
		}
	}

	void AContainer::layout()
	{
	}

	bool AContainer::processInput(const InputEvent & e)
	{
		if(!isVisible())
			return false;

		// Fetch children first
		for(auto & w : m_children)
		{
			if(w->isVisible())
			{
				if(w->processInput(e))
				{
					if(w->blocksInput())
						return true;
				}
			}
		}

		// Then process the event for the container itself
		return IInputListener::processInput(e);
	}

	void AContainer::render(IRenderer & r)
	{
		if(m_visible)
		{
			if(r_skin != nullptr)
				r_skin->drawDummyWidget(r, *this);
			renderChildren(r);
		}
	}

	void AContainer::animate(float dt)
	{
		if(m_visible)
		{
			animateChildren(dt);
		}
	}

	void AContainer::renderChildren(IRenderer & r)
	{
		AWidget * w;
		for(auto it = m_children.rbegin(); it != m_children.rend(); it++)
		{
			w = (*it);
			if(w->isVisible())
				w->render(r);
		}
	}

	void AContainer::animateChildren(float dt)
	{
		for(auto & w : m_children)
		{
			if(w->isVisible())
				w->animate(dt);
		}
	}

} // namespace ui
} // namespace zn



