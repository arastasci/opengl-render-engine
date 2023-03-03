#pragma once
#include "RenderObject.h"
#include <map>
namespace Engine {
	class Scene {
	public:
		int CreateRenderObject(Transform& t, Model m, Shader* s, Animator* a);
		void DestroyRenderObject(){}
		std::map <uint32_t, RenderObject>* GetObjectMap();

	private:
		uint32_t nextId = 0;
		std::map <uint32_t, RenderObject> renderObjectMap;
		int AddRenderObjectToScene(RenderObject& renderObject);
	};
}