#include <pybind11/pybind11.h>

#include <yaml-cpp/yaml.h>

inline YAML::Emitter& operator<<(YAML::Emitter& inEmitter, const pybind11::object& inObject)
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

inline void operator>>(YAML::Node& inNode, pybind11::object& inObject)
{
	if (pybind11::isinstance<pybind11::bool_>(inObject))
	{
		inObject = pybind11::cast(inNode.as<bool>());
		return;
	}
	else if (pybind11::isinstance<pybind11::int_>(inObject))
	{
		inObject = pybind11::cast(inNode.as<int64_t>());
		return;
	}
	else if (pybind11::isinstance<pybind11::float_>(inObject))
	{
		inObject = pybind11::cast(inNode.as<float>());
		return;
	}
	else if (pybind11::isinstance<pybind11::str>(inObject))
	{
		inObject = pybind11::cast(inNode.as<std::string>());
		return;
	}
	else if (pybind11::hasattr(inObject, "__yaml_load__"))
	{
		inObject.attr("__yaml_load__")(inNode);
		return;
	}

	pybind11::pybind11_fail("Object must has \"__yaml_load__\" function");
}

// namespaces
namespace py = pybind11;

// yaml names
using EmitterManip = YAML::EMITTER_MANIP;
using Emitter = YAML::Emitter;
using Node = YAML::Node;

PYBIND11_MODULE(yamlcxx, m)
{
	py::class_<Node>(m, "Node")
		.def("as_bool", &Node::as<bool>)
		.def("as_int", &Node::as<int>)
		.def("as_float", &Node::as<double>)
		.def("as_str", &Node::as<std::string>)

		.def("WriteTo", [](Node& self, py::object& inObject) { self >> inObject; }, py::arg("inObject"))

		.def("__rshift__", [](Node& self, py::object& inObject) { self >> inObject; }, py::arg("inObject"))
		.def("__getitem__", [](Node& self, const std::string& inKey) -> Node { return self[inKey]; }, py::arg("inKey"))
		.def("__getitem__", [](Node& self, const int inKey) -> Node { return self[inKey]; }, py::arg("inKey"));


	py::enum_<EmitterManip>(m, "EMITTER_MANIP")
		// general manipulators
		.value("Auto",				EmitterManip::Auto)
		.value("TagByKind",			EmitterManip::TagByKind)
		.value("Newline",			EmitterManip::Newline)

		// output character set
		.value("EmitNonAscii",		EmitterManip::EmitNonAscii)
		.value("EscapeNonAscii",	EmitterManip::EscapeNonAscii)
		.value("EscapeAsJson",		EmitterManip::EscapeAsJson)

		// string manipulators
		// Auto, // duplicate
		.value("SingleQuoted",		EmitterManip::SingleQuoted)
		.value("DoubleQuoted",		EmitterManip::DoubleQuoted)
		.value("Literal",			EmitterManip::Literal)

		// null manipulators
		.value("LowerNull",			EmitterManip::LowerNull)
		.value("UpperNull",			EmitterManip::UpperNull)
		.value("CamelNull",			EmitterManip::CamelNull)
		.value("TildeNull",			EmitterManip::TildeNull)

		// bool manipulators
		.value("YesNoBool",			EmitterManip::YesNoBool) // yes, no
		.value("TrueFalseBool",		EmitterManip::TrueFalseBool) // true, false
		.value("OnOffBool",			EmitterManip::OnOffBool) // on, off
		.value("UpperCase",			EmitterManip::UpperCase) // TRUE, N
		.value("LowerCase",			EmitterManip::LowerCase) // f, yes
		.value("CamelCase",			EmitterManip::CamelCase) // No, Off
		.value("LongBool",			EmitterManip::LongBool) // yes, On
		.value("ShortBool",			EmitterManip::ShortBool) // y, t  

		// int manipulators
		.value("Dec",				EmitterManip::Dec)
		.value("Hex",				EmitterManip::Hex)
		.value("Oct",				EmitterManip::Oct)

		// document manipulators
		.value("BeginDoc",			EmitterManip::BeginDoc)
		.value("EndDoc",			EmitterManip::EndDoc)

		// sequence manipulators
		.value("BeginSeq",			EmitterManip::BeginSeq)
		.value("EndSeq",			EmitterManip::EndSeq)
		.value("Flow",				EmitterManip::Flow)
		.value("Block",				EmitterManip::Block)

		// map manipulators
		.value("BeginMap",			EmitterManip::BeginMap)
		.value("EndMap",			EmitterManip::EndMap)
		.value("Key",				EmitterManip::Key)
		.value("Value",				EmitterManip::Value)
		// Flow, // duplicate
		// Block, // duplicate
		// Auto, // duplicate
		.value("LongKey",			EmitterManip::LongKey)
		.export_values();

	py::class_<Emitter>(m, "Emitter")
		.def(py::init<>())

		.def("c_str", [](const Emitter& self) { return py::str(self.c_str()); })
		.def("size", &Emitter::size)

		.def("good", &Emitter::good)
		.def("GetLastError", &Emitter::GetLastError)

		.def("SetOutputCharset", &Emitter::SetOutputCharset)
		.def("SetStringFormat", &Emitter::SetStringFormat)
		.def("SetBoolFormat", &Emitter::SetBoolFormat)
		.def("SetNullFormat", &Emitter::SetNullFormat)
		.def("SetIntBase", &Emitter::SetIntBase)
		.def("SetSeqFormat", &Emitter::SetSeqFormat)
		.def("SetMapFormat", &Emitter::SetMapFormat)
		.def("SetIndent", &Emitter::SetIndent)
		.def("SetPreCommentIndent", &Emitter::SetPreCommentIndent)
		.def("SetPostCommentIndent", &Emitter::SetPostCommentIndent)
		.def("SetFloatPrecision", &Emitter::SetFloatPrecision)
		.def("SetDoublePrecision", &Emitter::SetDoublePrecision)
		.def("SetShowTrailingZero", &Emitter::SetShowTrailingZero)
		.def("RestoreGlobalModifiedSettings", &Emitter::RestoreGlobalModifiedSettings)

		.def("Start",
			[](Emitter& self, const EmitterManip& inManip) -> Emitter&
			{
				return self << inManip;
			}, py::arg("inManip"), py::return_value_policy::reference_internal)
		.def("Type",
			[](Emitter& self, const EmitterManip& inManip) -> Emitter&
			{
				return self << inManip;
			}, py::arg("inManip"), py::return_value_policy::reference_internal)
		.def("Value",
			[](Emitter& self, const py::object& inObject) -> Emitter&
			{
				return self << inObject;
			}, py::arg("inObject"), py::return_value_policy::reference_internal)
		.def("End",
			[](Emitter& self, const EmitterManip& inManip)
			{
				self << inManip;
			}, py::arg("inManip"))



		.def("__lshift__", 
			[](Emitter& self, const EmitterManip& inManip) -> Emitter&
			{
				return self << inManip;
			}, py::arg("inManip"), py::return_value_policy::reference_internal)
		.def("__lshift__", 
			[](Emitter& self, const py::object& inObject) -> Emitter&
			{
				return self << inObject;
			}, py::arg("inObject"), py::return_value_policy::reference_internal);
	
	m.def("Load", py::overload_cast<const std::string&>(&YAML::Load));
}
