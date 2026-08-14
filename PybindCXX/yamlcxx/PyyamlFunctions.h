#pragma once

#include <pybind11/pybind11.h>
#include <yaml-cpp/yaml.h>

static inline YAML::Emitter& operator<<(YAML::Emitter& inEmitter, const pybind11::object& inObject)
{
	if (pybind11::isinstance<pybind11::bool_>(inObject))
	{
		return inEmitter << inObject.cast<bool>();
	}
	else if (pybind11::isinstance<pybind11::int_>(inObject))
	{
		return inEmitter << inObject.cast<int64_t>();
	}
	else if (pybind11::isinstance<pybind11::float_>(inObject))
	{
		return inEmitter << inObject.cast<double>();
	}
	else if (pybind11::isinstance<pybind11::str>(inObject))
	{
		return inEmitter << inObject.cast<std::string>();
	}
	else if (pybind11::hasattr(inObject, "__yaml_emit__"))
	{
		return inObject.attr("__yaml_emit__")(inEmitter).cast<YAML::Emitter&>();
	}

	pybind11::pybind11_fail("Object must has \"__yaml_emit__\" function");
}

static inline void operator>>(YAML::Node& inNode, pybind11::object& inObject)
{
	if (pybind11::isinstance<pybind11::bool_>(inObject))
	{
		inObject = pybind11::bool_(inNode.as<bool>());
		return;
	}
	else if (pybind11::isinstance<pybind11::int_>(inObject))
	{
		inObject = pybind11::int_(inNode.as<int64_t>());
		return;
	}
	else if (pybind11::isinstance<pybind11::float_>(inObject))
	{
		inObject = pybind11::float_(inNode.as<float>());
		return;
	}
	else if (pybind11::isinstance<pybind11::str>(inObject))
	{
		inObject = pybind11::str(inNode.as<std::string>());
		return;
	}
	else if (pybind11::hasattr(inObject, "__yaml_load__"))
	{
		inObject.attr("__yaml_load__")(inNode);
		return;
	}

	pybind11::pybind11_fail("Object must has \"__yaml_load__\" function");
}



static inline void Node_RShift(YAML::Node& self, pybind11::object& inObject)
{
	self >> inObject;
}

template<typename TKey>
static inline YAML::Node Node_GetItem(YAML::Node& self, TKey inKey)
{
	return self[inKey];
}



static inline pybind11::str Emitter_CStr(const YAML::Emitter& self)
{
	return pybind11::str(self.c_str());
}

template<typename TValue>
static inline YAML::Emitter& Emitter_LShift(YAML::Emitter& self, TValue inValue)
{
	return self << inValue;
}

static inline void Emitter_LShift_End(YAML::Emitter& self, YAML::EMITTER_MANIP inValue)
{
	self << inValue;
}
