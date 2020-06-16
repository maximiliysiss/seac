#pragma once
#include "Enums.h"
#include <chrono>
#include <map>
#include <string>

namespace seac::metrics {

#ifdef _DEBUG

	typedef std::tuple<double, std::chrono::high_resolution_clock::time_point, std::string> metric_point;

	class DebugMetrics {

		typedef std::map<std::string, double>  DataValue;

		static DebugMetrics* dm;
		std::chrono::high_resolution_clock::time_point startPoint;
		read_only_prop_ref(DataValue, data);
		std::string startData;
		DebugMetrics();
	public:
		static DebugMetrics& manager();
		metric_point start(seac::common::JitOperation jit);
		metric_point start(std::string op);
		void end(metric_point data);
	};

#endif // _DEBUG

}

