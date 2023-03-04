#include "Scene.h"
namespace Engine {
	/*int Scene::CreateRenderObject(Model& m, Shader* s, Animator* a, ShaderProps* props) {
		RenderObject renderObject(m, s, a, props);
		return AddRenderObjectToScene(&renderObject);
	}*/
	int Scene::CreateRenderObjectWithParent(RenderObject* parent, Model& m, Shader* s, Animator* a) {
		RenderObject renderObject(m, s, a);
		renderObject.SetParent(parent);
		return AddRenderObjectToScene(&renderObject);
	}
	RenderObject* Scene::CreateRenderObject(Model& m, Shader* s, Animator* a) {
		RenderObject renderObject(m, s, a);
		AddRenderObjectToScene(&renderObject);
		return &renderObject;
	}
	int Scene::AddRenderObjectToScene(RenderObject* renderObject) {
		renderObjectMap.insert({ nextId, *renderObject });
		renderObject->SetId(nextId);
		return nextId++;
	}
	std::map<int32_t, RenderObject>* Scene::GetObjectMap() {
		return &renderObjectMap;
	}
}