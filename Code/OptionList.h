#pragma once
#include <vector>
struct CompressedOption {
	const char* name;
	std::function<void()> function;
	long id;
};
inline std::vector<CompressedOption> option_list = {};