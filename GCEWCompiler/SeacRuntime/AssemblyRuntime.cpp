#include "AssemblyRuntime.h"
#include "StaticAssemblyRuntime.h"
#include "RemoteAssemblyRuntime.h"
#include "FullRemoteAssemblyRuntime.h"

namespace seac::runtime {

	IAssemblyRuntime* IAssemblyRuntime::getAssemblyRuntime(seac::common::ExecuteMode executeMode)
	{
		switch (executeMode)
		{
		case seac::common::ExecuteMode::Single:
			return new StaticAssemblyRuntime();
		case seac::common::ExecuteMode::Remote:
			return new RemoteAssemblyRuntime();
		case seac::common::ExecuteMode::FullRemote:
			return new FullRemoteAssemblyRuntime();
		default:
			break;
		}

		return new StaticAssemblyRuntime();
	}

}
