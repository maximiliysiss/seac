#include "RegionOperation.h"

gcew::trees::elements::operations::RegionStartOperation::RegionStartOperation(int index, std::string line, void* root)
	:gcew::trees::elements::Operation(index, line, RegexResult::RegionStart, root) {
}

void gcew::trees::elements::operations::RegionStartOperation::toCode(gcew::commons::CodeStream& code) {
	code << StreamData((ull)commons::JitOperation::startrg);
}

gcew::trees::elements::operations::RegionEndOperation::RegionEndOperation(int index, std::string line, void* root)
	:gcew::trees::elements::Operation(index, line, RegexResult::RegionStart, root) {
}

void gcew::trees::elements::operations::RegionEndOperation::toCode(gcew::commons::CodeStream& code) {
	code << StreamData((ull)commons::JitOperation::endrg);
}