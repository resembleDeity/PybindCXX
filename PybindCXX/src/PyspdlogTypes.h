#pragma once

#include <spdlog/spdlog.h>

#include <spdlog/sinks/async_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>



// Spdlog names
// Structures
// root namespace
using ELevel 			= spdlog::level;
using EColorMode 		= spdlog::color_mode;

using SourceLoc 		= spdlog::source_loc;
using LogMsg 			= spdlog::details::log_msg;
using TimePoint 		= spdlog::log_clock::time_point;
using StringView 		= spdlog::string_view_t;
using SinkPtr 			= spdlog::sink_ptr;

using Formatter 		= spdlog::formatter;

using Logger 			= spdlog::logger;

// sinks namespace
using Sink 				= spdlog::sinks::sink;
using BaseSinkMt 		= spdlog::sinks::base_sink<std::mutex>;
using BaseSinkSt 		= spdlog::sinks::base_sink<spdlog::details::null_mutex>;

#ifdef _WIN32
	#include <sinks/wincolor_sink.cpp>
	using ColorSinkMt 	= spdlog::sinks::wincolor_sink<std::mutex>;
	using ColorSinkSt 	= spdlog::sinks::wincolor_sink<spdlog::details::null_mutex>;
#else
	#include <sinks/ansicolor_sink.cpp>
	using ColorSinkMt 	= spdlog::sinks::ansicolor_sink<std::mutex>;
	using ColorSinkSt 	= spdlog::sinks::ansicolor_sink<spdlog::details::null_mutex>;
#endif

using AsyncSink = spdlog::sinks::async_sink;
using EAsyncOverflowPolicy = AsyncSink::overflow_policy;
using AsyncConfig = AsyncSink::config;

// File sinks
using BasicFileSinkMt 	= spdlog::sinks::basic_file_sink_mt;
using BasicFileSinkSt 	= spdlog::sinks::basic_file_sink_st;

// Stdout sinks
using StdoutColorSinkMt = spdlog::sinks::stdout_color_sink_mt;
using StdoutColorSinkSt = spdlog::sinks::stdout_color_sink_st;
using StdErrColorSinkMt = spdlog::sinks::stderr_color_sink_mt;
using StdErrColorSinkSt = spdlog::sinks::stderr_color_sink_st;
