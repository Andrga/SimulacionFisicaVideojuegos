// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2018 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  



#include "Camera.h"
#include <ctype.h>
#include "foundation/PxMat33.h"

#include "../core.hpp"

using namespace physx;

namespace Snippets
{

	Camera::Camera(const PxVec3& eye, const PxVec3& dir)
	{
		mEye = eye;
		mDir = dir.getNormalized();
		mMouseX = 0;
		mMouseY = 0;
	}

	void Camera::handleMouse(int button, int state, int x, int y)
	{
		PX_UNUSED(state);
		PX_UNUSED(button);
		mMouseX = x;
		mMouseY = y;
	}

	bool Camera::handleKey(unsigned char key, int x, int y, float speed)
	{
		PX_UNUSED(x);
		PX_UNUSED(y);

		// si se puede mover la camara a mano lo activamos, si no pasamos
		if (!movible) return false;

		PxVec3 viewY = mDir.cross(PxVec3(0, 1, 0)).getNormalized();
		PxVec3 viewX = mDir.cross(PxVec3(1, 0, 0)).getNormalized();
		switch (toupper(key))
		{
		case 'W':	mEye -= viewX * 2.0f * speed;		break;
		case 'S':	mEye += viewX * 2.0f * speed;		break;
		case 'A':	mEye -= viewY * 2.0f * speed;		break;
		case 'D':	mEye += viewY * 2.0f * speed;		break;
		default:							return false;
		}
		return true;
	}

	void Camera::handleAnalogMove(float x, float y)
	{
		PxVec3 viewY = mDir.cross(PxVec3(0, 1, 0)).getNormalized();
		mEye += mDir * y;
		mEye += viewY * x;
	}

	void Camera::handleMotion(int x, int y)
	{
		int dx = mMouseX - x;
		int dy = mMouseY - y;

		PxVec3 viewY = mDir.cross(PxVec3(0, 1, 0)).getNormalized();

		PxQuat qx(PxPi * dx / 180.0f, PxVec3(0, 1, 0));
		mDir = qx.rotate(mDir);
		PxQuat qy(PxPi * dy / 180.0f, viewY);
		mDir = qy.rotate(mDir);

		mDir.normalize();

		mMouseX = x;
		mMouseY = y;
	}

	PxTransform Camera::getTransform() const
	{
		PxVec3 viewY = mDir.cross(PxVec3(0, 1, 0));

		if (viewY.normalize() < 1e-6f)
			return PxTransform(mEye);

		PxMat33 m(mDir.cross(viewY), viewY, -mDir);
		return PxTransform(mEye, PxQuat(m));
	}

	void Camera::setMovible(bool mov) noexcept
	{
		movible = mov;
	}

	PxVec3 Camera::getEye() const
	{
		return mEye;
	}

	PxVec3 Camera::getDir() const
	{
		return mDir;
	}

	physx::PxVec3 Camera::getMouseWorldPos() const
	{
		// posiciones normalizadas
		float   nX = (2 * mMouseX) / widthCam - 1.0,
				nY = 1- (2 * mMouseY) / heightCam;
		// posiciones en el mundo
		float   wX = nX * 100,
				wY = nY * 60;

		return physx::PxVec3(wX, wY, mEye.z);
	}

	// Mover la camara a una nueva posicion
	void Camera::moveTo(const PxVec3& newEye)
	{
		mEye = newEye;
	}

	// Hacer que la camara mire a un punto especifico
	void Camera::lookAt(const PxVec3& target)
	{
		// Calculamos el vector de direccion desde la posicion de la camara hacia el objetivo
		PxVec3 dir = target - mEye;
		mDir = dir.getNormalized();
	}

}

