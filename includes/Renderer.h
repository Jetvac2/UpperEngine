#pragma once

namespace NRenderer
{
	class Renderer
	{
		const char* vertexShaderSource;
		const char* fragmentShaderSource;
	public:
		void init();
		void run();
		void destroy();
	};
}