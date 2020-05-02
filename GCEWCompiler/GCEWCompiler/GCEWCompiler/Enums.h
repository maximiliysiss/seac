#pragma once
#include <map>
#include <string>
#include "CommonLogger.h"
#define ull unsigned long long
#define elif else if

namespace gcew::commons
{
	enum class Operations : ull {
		FieldSet = 0,
		Convert = 1,
		FieldGet = 2,
		Start = 3,
		BoolTrue = 5,
		BoolFalse = 6,
		Body = 7,
		Iter,
		End,
		Compare,
		Plus = '+',
		Minus = '-',
		Multiply = '*',
		Divide = '/',
		And = '&',
		Or = '|',
		Greater = '>',
		Lower = '<',
		Equal = '=',
		Not = '!',
		Mod = '%',
		Call = 2000,
		ExtCall = 2001,
		Addr = 2002
	};

	enum class RegexResult : ull {
		Include,
		Type,
		For,
		While,
		If,
		Else,
		Function,
		Procedure,
		NotClassic,
		FigureClose,
		FigureOpen,
		Mathematic,
		Assigment,
		Call,
		ExternalCall,
		Break,
		Continue,
		PureAsm,
		Class,
		Struct,
		Return,
		Block
	};

	enum class JitOperation : ull {
		func = 428,
		proc = 436,
		init = 1306,
		equal = 536,
		plus = 452,
		minus = 556,
		divide = 629,
		multiply = 896,
		call = 412,
		start = 558,
		ret = 672,
		end = 311,
		exit = 442,
		assign = 645,
		stack = 534,
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
		ref = 547
	};
}
