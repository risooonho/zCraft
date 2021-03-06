/*
Camera3D.hpp
Copyright (C) 2010-2012 Marc GILLERON
This file is part of the zCraft project.
*/

#ifndef ZN_CAMERA3D_HPP_INCLUDED
#define ZN_CAMERA3D_HPP_INCLUDED

#include "engine/core/Vector2.hpp"
#include "engine/core/Vector3.hpp"
#include "engine/core/raycast.hpp"

namespace zn
{
	/*
		This is a basic 3D camera implementation.
	*/

	class Camera3D
	{
	public :

		Camera3D(const Vector2f viewportSize = Vector2f(512));

		void updateViewport(const Vector2f vps);

		void setNearAndFar(f32 near, f32 far);
		void setFov(f32 fovDegrees);
		void setPosition(const Vector3f pos);
		void setVertical(const Vector3f vert);
		void setForward(const Vector3f fw);

		inline Vector3f getPosition() const { return m_pos; }
		inline Vector3f getForward() const { return m_forward; }
		inline Vector3f getVertical() const { return m_vertical; }
		inline f32 getFov() const { return m_fov; }

		Ray screenToRay(f32 screenX, f32 screenY) const;

		void look();

	private :

		// Projection
		Vector2f m_viewportSize;
		f32 m_fov;
		f32 m_near;
		f32 m_far;

		// Position
		Vector3f m_pos;
		Vector3f m_forward;
		Vector3f m_vertical;

		// Update flags
		bool m_projectionChanged;
		bool m_positionChanged;

		// TODO orthographic options

	};

} // namespace zn

#endif // ZN_CAMERA3D_HPP_INCLUDED


