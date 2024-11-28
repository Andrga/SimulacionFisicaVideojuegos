#include "Widget.h"

Widget::Widget(Vector3 Pos, float siz) : position(Pos), size(siz)
{
	pose = new physx::PxTransform();
	pose->p = Pos;
	if (siz > 0)
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(siz)), pose, { 1, 0.0, 0.0, 0.01 });
}

Widget::Widget(Vector3 Pos, physx::PxShape* shap) : position(Pos)
{
	pose = new physx::PxTransform();
	pose->p = Pos;
	if (shap != nullptr)
		renderItem = new RenderItem(shap, pose, { 1, 0.0, 0.0, 0.01 });
	else
		std::cout << "ERROR AL CREAR WIDGET" << std::endl;
}

void Widget::changeShape(physx::PxShape* shap)
{
	if (renderItem == nullptr)
		renderItem = new RenderItem(shap, pose, { 1, 0.0, 0.0, 0.01 });
	else
		renderItem->shape = shap;
}

void Widget::setVisibility(bool visibility)
{
	if (renderItem == nullptr) return;
	if (visibility)
		RegisterRenderItem(renderItem);
	else
		DeregisterRenderItem(renderItem);
}
