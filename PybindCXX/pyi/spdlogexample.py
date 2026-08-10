from Log import *
import spdlogcxx

LogInit()

CORE_TRACE_TAG("Tag", spdlogcxx.sinks.async_sink.default_queue_size)

LogShutdown()