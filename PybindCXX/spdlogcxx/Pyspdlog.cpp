#include "PyspdlogFunctions.h"
#include "PyspdlogTypes.h"

#include <pybind11/native_enum.h>



class PyFormatter : public spdlog::formatter
{
public:

	virtual ~PyFormatter() = default;

	virtual void format(const spdlog::details::log_msg& inMessage, spdlog::memory_buf_t& inDest) override
	{
		PYBIND11_OVERRIDE_PURE(void, spdlog::formatter, format, inMessage, inDest);
	}

	virtual std::unique_ptr<spdlog::formatter> clone() const override
	{
		PYBIND11_OVERRIDE_PURE(std::unique_ptr<spdlog::formatter>, spdlog::formatter, clone);
	}
};

class PySink : public spdlog::sinks::sink
{
public:

	virtual ~PySink() = default;

	virtual void log(const spdlog::details::log_msg& inMessage) override
	{
		PYBIND11_OVERRIDE_PURE(void, spdlog::sinks::sink, log, inMessage);
	}

	virtual void flush() override
	{
		PYBIND11_OVERRIDE_PURE(void, spdlog::sinks::sink, flush);
	}

	virtual void set_pattern(const std::string& inPattern) override
	{
		PYBIND11_OVERRIDE_PURE(void, spdlog::sinks::sink, set_pattern, inPattern);
	}

	virtual void set_formatter(std::unique_ptr<spdlog::formatter> inFormatter) override
	{
		PYBIND11_OVERRIDE_PURE(void, spdlog::sinks::sink, set_formatter, inFormatter);
	}
};

class PyBaseSinkMt : public spdlog::sinks::base_sink<std::mutex>
{
public:

	virtual ~PyBaseSinkMt() = default;

protected:

	virtual void sink_it_(const spdlog::details::log_msg& inMessage) override
	{
		PYBIND11_OVERRIDE_PURE(void, spdlog::sinks::base_sink<std::mutex>, sink_it_, inMessage);
	}

	virtual void flush_() override
	{
		PYBIND11_OVERRIDE_PURE(void, spdlog::sinks::base_sink<std::mutex>, flush_);
	}

	virtual void set_pattern_(const std::string& inPattern) override
	{
		PYBIND11_OVERRIDE(void, spdlog::sinks::base_sink<std::mutex>, set_pattern_, inPattern);
	}

	virtual void set_formatter_(std::unique_ptr<spdlog::formatter> inFormatter) override
	{
		PYBIND11_OVERRIDE(void, spdlog::sinks::base_sink<std::mutex>, set_formatter_, std::move(inFormatter));
	}
};

class PublicBaseSinkMt : public spdlog::sinks::base_sink<std::mutex>
{
public:

	using spdlog::sinks::base_sink<std::mutex>::sink_it_;
	using spdlog::sinks::base_sink<std::mutex>::flush_;
	using spdlog::sinks::base_sink<std::mutex>::set_pattern_;
	using spdlog::sinks::base_sink<std::mutex>::set_formatter_;

public:

	using spdlog::sinks::base_sink<std::mutex>::formatter_;
};



class PyBaseSinkSt : public spdlog::sinks::base_sink<spdlog::details::null_mutex>
{
public:

	virtual ~PyBaseSinkSt() = default;

protected:

	virtual void sink_it_(const spdlog::details::log_msg& inMessage) override
	{
		PYBIND11_OVERRIDE_PURE(void, spdlog::sinks::base_sink<spdlog::details::null_mutex>, sink_it_, inMessage);
	}

	virtual void flush_() override
	{
		PYBIND11_OVERRIDE_PURE(void, spdlog::sinks::base_sink<spdlog::details::null_mutex>, flush_);
	}

	virtual void set_pattern_(const std::string& inPattern) override
	{
		PYBIND11_OVERRIDE(void, spdlog::sinks::base_sink<spdlog::details::null_mutex>, set_pattern_, inPattern);
	}

	virtual void set_formatter_(std::unique_ptr<spdlog::formatter> inFormatter) override
	{
		PYBIND11_OVERRIDE(void, spdlog::sinks::base_sink<spdlog::details::null_mutex>, set_formatter_, std::move(inFormatter));
	}
};

class PublicBaseSinkSt : public spdlog::sinks::base_sink<spdlog::details::null_mutex>
{
public:

	using spdlog::sinks::base_sink<spdlog::details::null_mutex>::sink_it_;
	using spdlog::sinks::base_sink<spdlog::details::null_mutex>::flush_;
	using spdlog::sinks::base_sink<spdlog::details::null_mutex>::set_pattern_;
	using spdlog::sinks::base_sink<spdlog::details::null_mutex>::set_formatter_;

public:

	using spdlog::sinks::base_sink<spdlog::details::null_mutex>::formatter_;
};



namespace py = pybind11;

PYBIND11_MODULE(spdlogcxx, m)
{
	py::native_enum<ELevel>(m, "level", "enum.IntEnum")
		.value("trace",		ELevel::trace)
		.value("debug",		ELevel::debug)
		.value("info",		ELevel::info)
		.value("warn",		ELevel::warn)
		.value("err",		ELevel::err)
		.value("critical",	ELevel::critical)
		.value("off",		ELevel::off)
		.value("n_levels",	ELevel::n_levels)
		.finalize();

	py::native_enum<EColorMode>(m, "color_mode", "enum.Enum")
		.value("always",	EColorMode::always)
		.value("automatic", EColorMode::automatic)
		.value("never",		EColorMode::never)
		.finalize();

	py::class_<SourceLoc>(m, "source_loc")
		.def(py::init<>())
		.def(py::init<const char*, std::uint_least32_t, const char*>(),
			py::arg("inFileName"), py::arg("inLine"), py::arg("inFuncName")
		)

		.def("empty", &SourceLoc::empty)

		.def_readwrite("filename",			&SourceLoc::filename)
		.def_readwrite("short_filename",	&SourceLoc::short_filename)
		.def_readwrite("line",				&SourceLoc::line)
		.def_readwrite("funcname",			&SourceLoc::funcname)
		
		.def_static("basename",				&SourceLoc::basename);

	py::class_<LogMsg>(m, "log_msg")
		.def(py::init<>())
		.def(py::init<TimePoint, const SourceLoc&, StringView, ELevel, StringView>(),
			py::arg("inLogTime"), py::arg("inLocation"), 
			py::arg("inLoggerName"), py::arg("inLevel"), py::arg("inMessage")
		)
		.def(py::init<const SourceLoc&, StringView, ELevel, StringView>(),
			py::arg("inLocation"), 
			py::arg("inLoggerName"), py::arg("inLevel"), py::arg("inMessage")
		)
		.def(py::init<StringView, ELevel, StringView>(),
			py::arg("inLoggerName"), py::arg("inLevel"), py::arg("inMessage")
		)

		.def_readwrite("logger_name",		&LogMsg::logger_name)
		.def_readwrite("log_level",			&LogMsg::log_level)
		.def_readwrite("time",				&LogMsg::time)
		.def_readwrite("thread_id",			&LogMsg::thread_id)
		.def_readwrite("source",			&LogMsg::source)
		.def_readwrite("payload",			&LogMsg::payload)
		
		.def_readwrite("color_range_start", &LogMsg::color_range_start)
		.def_readwrite("color_range_end",	&LogMsg::color_range_end);;;



	py::class_<Formatter, PyFormatter>(m, "formatter")
		.def(py::init<>())

		.def("format", &Formatter_Format, py::arg("inMessage"))
		.def("clone", &Formatter::clone);


	
	auto sinks = m.def_submodule("sinks");
	py::class_<Sink, PySink, SinkPtr>(sinks, "sink")
		.def(py::init())

		.def("log",				&Sink::log)
		.def("flush",			&Sink::flush)
		.def("set_pattern",		&Sink::set_pattern)
		.def("set_formatter",	&Sink::set_formatter)
		.def("set_level",		&Sink::set_level)
		.def("log_level",		&Sink::log_level)
		.def("should_log",		&Sink::should_log);



	py::class_<BaseSinkMt, PyBaseSinkMt, std::shared_ptr<BaseSinkMt>>(sinks, "base_sink_mt", py::base<Sink>())
		.def(py::init<>())
		.def("sink_it_",		&PublicBaseSinkMt::sink_it_)
		.def("flush_",			&PublicBaseSinkMt::flush_)
		.def("set_pattern_",	&PublicBaseSinkMt::set_pattern_)
		.def("set_formatter_",	&PublicBaseSinkMt::set_formatter_)

		.def_readwrite("formatter_", &PublicBaseSinkMt::formatter_);

	py::class_<BaseSinkSt, PyBaseSinkSt, std::shared_ptr<BaseSinkSt>>(sinks, "base_sink_st", py::base<Sink>())
		.def(py::init<>())
		.def("sink_it_",		&PublicBaseSinkSt::sink_it_)
		.def("flush_",			&PublicBaseSinkSt::flush_)
		.def("set_pattern_",	&PublicBaseSinkSt::set_pattern_)
		.def("set_formatter_",	&PublicBaseSinkSt::set_formatter_)
		
		.def_readwrite("formatter_", &PublicBaseSinkSt::formatter_);



#ifdef _WIN32
	py::class_<ColorSinkMt, BaseSinkMt, std::shared_ptr<ColorSinkMt>>(sinks, "color_sink_mt")
		.def(py::init<py::capsule, EColorMode>(), py::arg("Handle"), py::arg("inMode"))

		.def("set_color", &ColorSinkMt::set_color)
		.def("set_color_mode", &ColorSinkMt::set_color_mode);

	py::class_<ColorSinkSt, BaseSinkSt, std::shared_ptr<ColorSinkSt>>(sinks, "color_sink_st")
		.def(py::init<py::capsule, EColorMode>(), py::arg("Handle"), py::arg("inMode"))

		.def("set_color", &ColorSinkSt::set_color)
		.def("set_color_mode", &ColorSinkSt::set_color_mode);
#else
	py::class_<ColorSinkMt, BaseSinkMt, std::shared_ptr<ColorSinkMt>>(sinks, "color_sink_mt")
		.def(py::init(
			[](py::object, EColorMode inMode)
			{
				// TODO: Implementation constructure function
			}))

		.def("set_color", &ColorSinkMt::set_color)
		.def("set_color_mode", &ColorSinkMt::set_color_mode);

	py::class_<ColorSinkSt, BaseSinkSt, std::shared_ptr<ColorSinkSt>>(sinks, "color_sink_st")
		.def(py::init(
			[](py::object, EColorMode inMode)
			{
				// TODO: Implementation constructure function
			}))

		.def("set_color", &ColorSinkSt::set_color)
		.def("set_color_mode", &ColorSinkSt::set_color_mode);
#endif


	py::class_<AsyncSink, Sink, std::shared_ptr<AsyncSink>> asyncSink(sinks, "async_sink");
	asyncSink
		.def_property_readonly_static("default_queue_size", &AsyncSink_GetDefaultQueueSize)
		.def_property_readonly_static("max_queue_size",		&AsyncSink_GetMaxQueueSize)
		
		.def_static("create_with", &AsyncSink_With);

	py::native_enum<EAsyncOverflowPolicy>(asyncSink, "overflow_policy", "enum.Enum")
		.value("block",				EAsyncOverflowPolicy::block)
		.value("overrun_oldest",	EAsyncOverflowPolicy::overrun_oldest)
		.value("discard_new",		EAsyncOverflowPolicy::discard_new)
		.finalize();

	py::class_<AsyncConfig>(asyncSink, "config")
		.def_readwrite("queue_size",			&AsyncConfig::queue_size)
		.def_readwrite("policy",				&AsyncConfig::policy)
		.def_readwrite("sinks",					&AsyncConfig::sinks)
		.def_readwrite("on_thread_start",		&AsyncConfig::on_thread_start)
		.def_readwrite("on_thread_stop",		&AsyncConfig::on_thread_stop)
		.def_readwrite("custom_err_handler",	&AsyncConfig::custom_err_handler);
	
	asyncSink.def(py::init<AsyncConfig>(), py::arg("inAsyncConfig"));



	py::class_<BasicFileSinkMt, BaseSinkMt, std::shared_ptr<BasicFileSinkMt>>(sinks, "basic_file_sink_mt")
		.def(py::init<const std::string&, bool>(), py::arg("inFileName"), py::arg("inbTruncate") = false)
		
		.def("filename", &BasicFileSinkMt::filename)
		.def("truncate", &BasicFileSinkMt::truncate);

	py::class_<BasicFileSinkSt, BaseSinkSt, std::shared_ptr<BasicFileSinkSt>>(sinks, "basic_file_sink_st")
		.def(py::init<const std::string&, bool>(), py::arg("inFileName"), py::arg("inbTruncate") = false)
		
		.def("filename", &BasicFileSinkSt::filename)
		.def("truncate", &BasicFileSinkSt::truncate);



	py::class_<StdoutColorSinkMt, ColorSinkMt, std::shared_ptr<StdoutColorSinkMt>>(sinks, "stdout_color_sink_mt")
		.def(py::init<EColorMode>(), py::arg("inMode") = EColorMode::automatic);

	py::class_<StdoutColorSinkSt, ColorSinkSt, std::shared_ptr<StdoutColorSinkSt>>(sinks, "stdout_color_sink_st")
		.def(py::init<EColorMode>(), py::arg("inMode") = EColorMode::automatic);

	py::class_<StdErrColorSinkMt, ColorSinkMt, std::shared_ptr<StdErrColorSinkMt>>(sinks, "stderr_color_sink_mt")
		.def(py::init<EColorMode>(), py::arg("inMode") = EColorMode::automatic);

	py::class_<StdErrColorSinkSt, ColorSinkSt, std::shared_ptr<StdErrColorSinkSt>>(sinks, "stderr_color_sink_st")
		.def(py::init<EColorMode>(), py::arg("inMode") = EColorMode::automatic);



	py::class_<Logger>(m, "logger")
		.def(py::init<std::string>(),			py::arg("inName"))
		.def(py::init<std::string, SinkPtr>(),	py::arg("inName"), py::arg("inSink"))
		.def(py::init(&Logger_Init), py::arg("inName"), py::arg("inSinks"))

		.def("set_level",	&Logger::set_level)
		.def("trace",		static_cast<void(Logger::*)(StringView)>(&Logger::trace))
		.def("debug",		static_cast<void(Logger::*)(StringView)>(&Logger::debug))
		.def("info",		static_cast<void(Logger::*)(StringView)>(&Logger::info))
		.def("warn",		static_cast<void(Logger::*)(StringView)>(&Logger::warn))
		.def("error",		static_cast<void(Logger::*)(StringView)>(&Logger::error))
		.def("critical",	static_cast<void(Logger::*)(StringView)>(&Logger::critical));
}
