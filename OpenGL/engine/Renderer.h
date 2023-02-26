#pragma once

#include <iostream>


namespace Engine {


	class Renderer {

	public:


		Renderer() {

		}

		void SetToPolygonMode() {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		
	private:
		

	};



}