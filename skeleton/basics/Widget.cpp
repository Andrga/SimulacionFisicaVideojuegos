#include "Widget.h"

Widget::Widget(Vector3 Pos, float siz)
{
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(siz)), &physx::PxTransform(Pos), { 1, 0.0, 0.0, 0.0 }); 
}

void Widget::changeShape(physx::PxShape* shap)
{
	renderItem->shape = shap;
}

void Widget::setVisibility(bool visibility)
{
	visibility ?
		RegisterRenderItem(renderItem) :
		DeregisterRenderItem(renderItem);
}
