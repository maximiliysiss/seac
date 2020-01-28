#include "AssemblyRuntime.h"
#include "StaticAssemblyRuntime.h"
#include <fstream>

namespace seac::runtime {

	IAssemblyRuntime* IAssemblyRuntime::getAssemblyRuntime(seac::common::ExecuteMode executeMode)
	{
		switch (executeMode)
		{
		case seac::common::ExecuteMode::Single:
			return new StaticAssemblyRuntime();
		default:
			break;
		}

		return new StaticAssemblyRuntime();
	}

}
