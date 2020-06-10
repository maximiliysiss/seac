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
		endrg = 549,

		libstart = 550,
		libend = 551,
		libinfo = 552
	};

	static std::map<JitOperation, std::string> JitConverter{
	{ JitOperation::andop, str_(JitOperation::andop) },
	{ JitOperation::assign, str_(JitOperation::assign) },
	{ JitOperation::call, str_(JitOperation::call) },
	{ JitOperation::divide, str_(JitOperation::divide) },
	{ JitOperation::end, str_(JitOperation::end) },
	{ JitOperation::endrg, str_(JitOperation::endrg) },
	{ JitOperation::equal, str_(JitOperation::equal) },
	{ JitOperation::exit, str_(JitOperation::exit) },
	{ JitOperation::extcall, str_(JitOperation::extcall) },
	{ JitOperation::func, str_(JitOperation::func) },
	{ JitOperation::gequal, str_(JitOperation::gequal) },
	{ JitOperation::greater, str_(JitOperation::greater) },
	{ JitOperation::ifop, str_(JitOperation::ifop) },
	{ JitOperation::init, str_(JitOperation::init) },
	{ JitOperation::jump, str_(JitOperation::jump) },
	{ JitOperation::lequal, str_(JitOperation::lequal) },
	{ JitOperation::localend, str_(JitOperation::localend) },
	{ JitOperation::lower, str_(JitOperation::lower) },
	{ JitOperation::minus, str_(JitOperation::minus) },
	{ JitOperation::multiply, str_(JitOperation::multiply) },
	{ JitOperation::notequal, str_(JitOperation::notequal) },
	{ JitOperation::orop, str_(JitOperation::orop) },
	{ JitOperation::plus, str_(JitOperation::plus) },
	{ JitOperation::proc, str_(JitOperation::proc) },
	{ JitOperation::ref, str_(JitOperation::ref) },
	{ JitOperation::ret, str_(JitOperation::ret) },
	{ JitOperation::stack, str_(JitOperation::stack) },
	{ JitOperation::start, str_(JitOperation::start) },
	{ JitOperation::startrg, str_(JitOperation::startrg) },
	};
}