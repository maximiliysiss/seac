#pragma once
#include <string>
#include "runtime.h"

#define uint unsigned int
#define ull unsigned long long
#define elif else if

#define read_only_prop(type, name) \
	protected: \
		type name; \
	public: \
		type get_##name(){ \
			return name; \
		} \
	private:

#define auto_prop(type, name) \
	protected: \
		type name; \
	public: \
		type get_##name(){ \
			return name; \
		} \
		void set_##name(##type name){ \
			this->##name = name; \
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

#define auto_prop_ref(type, name) \
	protected: \
		type name; \
	public: \
		type& get_##name(){ \
			return name; \
		} \
		void set_##name(##type name){ \
			this->##name = ##name; \
		} \
	private:

#define read_only_prop_ref(type, name, value) \
	protected: \
		type name{##value}; \
	public: \
		type& get_##name(){ \
			return name; \
		} \
	private:

#define auto_prop_ref(type, name, value) \
	protected: \
		type name{##value}; \
	public: \
		type& get_##name(){ \
			return name; \
		} \
		void set_##name(##type name){ \
			this->##name = ##name; \
		} \
	private:

#define to_str(value) std::to_string(value)