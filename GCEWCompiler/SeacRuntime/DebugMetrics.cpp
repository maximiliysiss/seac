#include "DebugMetrics.h"

namespace seac::metrics {

#ifdef _DEBUG

	DebugMetrics* DebugMetrics::dm = nullptr;

	DebugMetrics::DebugMetrics(){
	}

	DebugMetrics& seac::metrics::DebugMetrics::manager() {
		if (dm)
			return *dm;
		return *(dm = new DebugMetrics());
	}

	metric_point DebugMetrics::start(seac::common::JitOperation jit) {
		auto key = common::JitConverter[jit];
		return std::make_tuple(data[key], std::chrono::high_resolution_clock::now(), key);
	}

	metric_point DebugMetrics::start(std::string key){
		return std::make_tuple(data[key], std::chrono::high_resolution_clock::now(), key);
	}

	void DebugMetrics::end(metric_point data) {
		auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - std::get<1>(data)).count();
		this->data[std::get<2>(data)] = (std::get<0>(data) + microseconds) / 2;
	}

#endif

}
