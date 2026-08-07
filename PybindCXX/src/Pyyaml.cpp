#include "PyyamlTypes.h"
#include "PyyamlFunctions.h"



PYBIND11_MODULE(yamlcxx, m)
{
	py::class_<Node>(m, "Node")
		.def("as_bool",		&Node::as<bool>)
		.def("as_int",		&Node::as<int>)
		.def("as_float",	&Node::as<double>)
		.def("as_str",		&Node::as<std::string>)

		.def("WriteTo",		&Node_RShift, py::arg("inObject"))

		.def("__rshift__",	&Node_RShift, py::arg("inObject"))
		.def("__getitem__", &Node_GetItem<const std::string&>, py::arg("inKey"))
		.def("__getitem__", &Node_GetItem<int>, py::arg("inKey"));


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

		.def("c_str",							&Emitter_CStr)
		.def("size",							&Emitter::size)

		.def("good",							&Emitter::good)
		.def("GetLastError",					&Emitter::GetLastError)

		.def("SetOutputCharset",				&Emitter::SetOutputCharset)
		.def("SetStringFormat",					&Emitter::SetStringFormat)
		.def("SetBoolFormat",					&Emitter::SetBoolFormat)
		.def("SetNullFormat",					&Emitter::SetNullFormat)
		.def("SetIntBase",						&Emitter::SetIntBase)
		.def("SetSeqFormat",					&Emitter::SetSeqFormat)
		.def("SetMapFormat",					&Emitter::SetMapFormat)
		.def("SetIndent",						&Emitter::SetIndent)
		.def("SetPreCommentIndent",				&Emitter::SetPreCommentIndent)
		.def("SetPostCommentIndent",			&Emitter::SetPostCommentIndent)
		.def("SetFloatPrecision",				&Emitter::SetFloatPrecision)
		.def("SetDoublePrecision",				&Emitter::SetDoublePrecision)
		.def("SetShowTrailingZero",				&Emitter::SetShowTrailingZero)
		.def("RestoreGlobalModifiedSettings",	&Emitter::RestoreGlobalModifiedSettings)

		.def("Start",		&Emitter_LShift<EmitterManip>,			py::arg("inManip"),		py::return_value_policy::reference_internal)
		.def("Type",		&Emitter_LShift<EmitterManip>,			py::arg("inManip"),		py::return_value_policy::reference_internal)
		.def("Value",		&Emitter_LShift<const py::object&>,		py::arg("inObject"),	py::return_value_policy::reference_internal)
		.def("End",			&Emitter_LShift_End,					py::arg("inManip"))

		.def("__lshift__",	&Emitter_LShift<EmitterManip>,			py::arg("inManip"),		py::return_value_policy::reference_internal)
		.def("__lshift__",	&Emitter_LShift<const py::object&>,		py::arg("inObject"),	py::return_value_policy::reference_internal);
	
	m.def("Load", py::overload_cast<const std::string&>(&YAML::Load));
}
