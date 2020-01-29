#pragma once
#include <map>
#include <string>
#define ull unsigned long long

namespace gcew::commons
{
	enum Operations {
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
		Mod = '%'
	};

	enum RegexResult {
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
		Break,
		Continue,
		PureAsm,
		Class,
		Struct,
		Return,
		Block
	};

	enum class JitOperation: ull {
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
		exit = 442
	};
}
