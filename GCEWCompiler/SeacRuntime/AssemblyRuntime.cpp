#include "AssemblyRuntime.h"
#include "StaticAssemblyRuntime.h"
#include "RemoteAssemblyRuntime.h"

namespace seac::runtime {

	IAssemblyRuntime* IAssemblyRuntime::getAssemblyRuntime(seac::common::ExecuteMode executeMode)
	{
		switch (executeMode)
		{
		case seac::common::ExecuteMode::Single:
			return new StaticAssemblyRuntime();
		case seac::common::ExecuteMode::Remote:
			return new RemoteAssemblyRuntime();
		default:
			break;
		}

		return new StaticAssemblyRuntime();
	}

}
