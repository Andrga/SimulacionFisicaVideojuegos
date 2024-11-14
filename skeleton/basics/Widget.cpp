#include "Widget.h"

Widget::Widget(Vector3 Pos, float siz) : position(Pos), size(siz)
{
	if (siz > 0)
		renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(siz)), &physx::PxTransform(Pos), { 1, 0.0, 0.0, 0.01 });
}

void Widget::changeShape(physx::PxShape* shap)
{
	if (renderItem == nullptr)
		renderItem = new RenderItem(shap, &physx::PxTransform(position), { 1, 0.0, 0.0, 0.01 });
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
