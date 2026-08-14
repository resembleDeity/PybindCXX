#pragma once

#include <pybind11/pybind11.h>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/async_sink.h>



static inline std::string Formatter_Format(spdlog::formatter& self, const spdlog::details::log_msg& inMessage)
{
	spdlog::memory_buf_t formatted;
	self.format(inMessage, formatted);
	return fmt::to_string(formatted);
}



static inline size_t AsyncSink_GetDefaultQueueSize(pybind11::object&)
{
	return spdlog::sinks::async_sink::default_queue_size;
}

static inline size_t AsyncSink_GetMaxQueueSize(pybind11::object&)
{
	return spdlog::sinks::async_sink::max_queue_size;
}

static inline std::shared_ptr<spdlog::sinks::async_sink> AsyncSink_With(const pybind11::object& inCls, const pybind11::args& inArgs, const pybind11::kwargs& inKwArgs)
{
	if (!pybind11::isinstance<pybind11::type>(inCls))
	{
		pybind11::pybind11_fail("must a type object.");
	}

	spdlog::sinks::async_sink::config asyncSinkConfig;
	try
	{
		asyncSinkConfig.sinks.emplace_back(pybind11::cast<spdlog::sink_ptr>(inCls(*inArgs, **inKwArgs)));
	}
	catch (pybind11::cast_error& e)
	{
		pybind11::pybind11_fail(e.what());
	}
	
	return std::make_shared<spdlog::sinks::async_sink>(asyncSinkConfig);
}



static inline spdlog::logger* Logger_Init(std::string inName, const pybind11::iterable& inSinks)
{
	std::vector<spdlog::sink_ptr> sinks;
	for (auto& it : inSinks)
	{
		sinks.push_back(it.cast<spdlog::sink_ptr>());
	}

	return new spdlog::logger(std::move(inName), sinks.begin(), sinks.end());
}
