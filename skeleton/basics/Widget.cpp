#include "Widget.h"


Widget::Widget(string nam, Scene* scn, Vector3 Pos, float siz) : GameObject(nam, scn)
{
	pose = PxTransform(Pos);
	size = siz;

	if (siz > 0)
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(siz)), &pose, { 1, 0.0, 0.0, 0.01 });
}

Widget::Widget(string nam, Scene* scn, Vector3 Pos, physx::PxShape* shap) : GameObject(nam, scn)
{
	pose = PxTransform(Pos);

	if (shap != nullptr)
		renderItem = new RenderItem(shap, &pose, { 1, 0.0, 0.0, 0.01 });
	else
		std::cout << "ERROR AL CREAR WIDGET" << std::endl;
}

void Widget::changeShape(physx::PxShape* shap)
{
	if (renderItem == nullptr)
		renderItem = new RenderItem(shap, &pose, { 1, 0.0, 0.0, 0.01 });
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
