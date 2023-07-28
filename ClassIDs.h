#pragma once
#define ClassID(x)                CLASS_##x
#define	DefineClassID(x,classID)  ClassID(x) = (classID),

enum ClassIDType
{
	DefineClassID(Undefined, -1)
	DefineClassID(Object, 0)
	DefineClassID(Node, 1)
	DefineClassID(Component, 2)
	DefineClassID(Camera, 3)
	DefineClassID(Light, 4)
	DefineClassID(Render, 5)
	DefineClassID(Spin, 6)
	DefineClassID(Prefab, 7)
	DefineClassID(Scene, 8)
};
