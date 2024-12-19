#include "Widget.h"


Widget::Widget(string nam, Scene* scn, Vector3 Pos, float siz) : GameObject(nam, scn)
{
	pose = new PxTransform(Pos);
	size = { siz,siz,siz };

	if (siz > 0)
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(siz)), pose, { 1, 0.0, 0.0, 0.01 });
}

Widget::Widget(string nam, Scene* scn, Vector3 Pos, physx::PxShape* shap) : GameObject(nam, scn)
{
	pose = new PxTransform(Pos);

	if (shap != nullptr)
		renderItem = new RenderItem(shap, pose, { 1, 0.0, 0.0, 0.01 });
	else
		std::cout << "ERROR AL CREAR WIDGET" << std::endl;
}

Widget::Widget(string nam, Scene* scn, PxTransform* pos, float siz ): GameObject(nam, scn)
{
	pose = pos;
	size = { siz,siz,siz };

	if (siz > 0)
		renderItem = new RenderItem(CreateShape(PxSphereGeometry(siz)), pose, { 1, 0.0, 0.0, 0.01 });
}


