#pragma once
#include "RenderObject.h"
#include <map>
namespace Engine {
	class Scene {
	public:
		//int CreateRenderObject(Model& m, Shader* s, Animator* a, ShaderProps* props);
		RenderObject* CreateRenderObject(Model& m, Shader* s, Animator* a);

		int CreateRenderObjectWithParent(RenderObject* parent, Model& m, Shader* s, Animator* a);
		void DestroyRenderObject(){}
		std::map <int32_t, RenderObject>* GetObjectMap();

	private:
		int32_t nextId = 0;
		std::map <int32_t, RenderObject> renderObjectMap;
		int AddRenderObjectToScene(RenderObject* renderObject);
	};
}