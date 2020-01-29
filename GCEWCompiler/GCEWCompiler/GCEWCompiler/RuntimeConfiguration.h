#pragma once

namespace gcew::commons {


	class RuntimeConfiguration
	{
	private:
		RuntimeConfiguration() {}
		static RuntimeConfiguration* runtime;
	public:
		static RuntimeConfiguration& getInstance();
	};
}

