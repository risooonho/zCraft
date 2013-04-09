/*
Panel.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZENGUI_PANEL_HPP_INCLUDED
#define ZENGUI_PANEL_HPP_INCLUDED

#include "Composite.hpp"

namespace zn
{
namespace ui
{
	class Panel : public AComposite
	{
	public :

		Panel() : AComposite() {}
		virtual ~Panel() {}

		virtual void render(IRenderer & r) override
		{
			if(r_skin != nullptr)
				r_skin->drawPanel(r, *this);
		}

	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_PANEL_HPP_INCLUDED
