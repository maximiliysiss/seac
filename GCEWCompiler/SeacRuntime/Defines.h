#pragma once
#include <string>

#define uint unsigned int
#define ull unsigned long long

#define read_only_prop(type, name) \
	protected: \
		type name; \
	public: \
		type get_##name(){ \
			return name; \
		} \
	private:

#define read_only_prop(type, name, value) \
	protected: \
		type name{##value}; \
	public: \
		type get_##name(){ \
			return name; \
		} \
	private:

#define read_only_prop_ref(type, name) \
	protected: \
		type name; \
	public: \
		type& get_##name(){ \
			return name; \
		} \
	private:

#define to_str(value) std::to_string(value)