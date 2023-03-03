#include "Scene.h"
namespace Engine {
	int Scene::CreateRenderObject(Transform& t, Model m, Shader* s, Animator* a) {
		RenderObject renderObject(t, m, s, a);
		return AddRenderObjectToScene(renderObject);
		
	}
	int Scene::AddRenderObjectToScene(RenderObject& renderObject) {
		renderObjectMap[nextId] = renderObject;
		
		return nextId++;
	}
	std::map<uint32_t, RenderObject>* Scene::GetObjectMap() {
		return &renderObjectMap;
	}
}