#pragma once
#include "Defines.h"
#include "Helper.h"
#include "RuntimeConfiguration.h"

namespace seac::common {

	enum class ExecuteMode {
		Single,
		Remote,
		FullRemote
	};

	static std::map<ExecuteMode, std::string> ExecuteConverter{
		{ ExecuteMode::Single, str_(single) },
		{ ExecuteMode::Remote, str_(remote) },
		{ ExecuteMode::FullRemote, str_(fullremote) },
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
		extcall = 2001,
		localend = 535,
		lower = 537,
		greater = 538,
		lequal = 539,
		gequal = 540,
		notequal = 542,
		andop = 543,
		orop = 544,
		ifop = 545,
		jump = 546,
		ref = 547,

		startrg = 548,
		endrg = 549
	};

}