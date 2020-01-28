#pragma once

namespace seac::common {

	enum class ExecuteMode {
		Single,
		Remote,
		FullRemote
	};

	enum class Level {
		Error,
		Warning,
		Info,
		Trace
	};

}