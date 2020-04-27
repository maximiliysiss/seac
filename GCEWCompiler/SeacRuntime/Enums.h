#pragma once
#include "Defines.h"
#include "RuntimeConfiguration.h"

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

	enum class ReaderType : ull {
		Header = 0,
		Universal = 1,
		String = 2
	};

	enum class JitOperation : ull {
		func = 428,
		proc = 436,
		init = 1306,
		equal = 536,
		//plus = 452,
		//minus = 556,
		//divide = 629,
		//multiply = 896,
		start = 558,
		ret = 672,
		end = 311,
		exit = 442,
		assign = 645,
		stack = 534,
		plus = '+',
		minus = '-',
		multiply = '*',
		divide = '/',
		call = 2000,
		extcall = 2001
	};

}