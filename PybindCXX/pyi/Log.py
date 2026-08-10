import spdlogcxx

import inspect

from dataclasses import dataclass
from enum import IntEnum
from pathlib import Path

__all__ = [
	"LogInit",
	"LogShutdown",

	"CORE_TRACE",
	"CORE_DEBUG",
	"CORE_INFO",
	"CORE_WARN",
	"CORE_ERROR",
	"CORE_FATAL",

	"CLIENT_TRACE",
	"CLIENT_DEBUG",
	"CLIENT_INFO",
	"CLIENT_WARN",
	"CLIENT_ERROR",
	"CLIENT_FATAL",

	"CORE_TRACE_TAG",
	"CORE_DEBUG_TAG",
	"CORE_INFO_TAG",
	"CORE_WARN_TAG",
	"CORE_ERROR_TAG",
	"CORE_FATAL_TAG",

	"CLIENT_TRACE_TAG",
	"CLIENT_DEBUG_TAG",
	"CLIENT_INFO_TAG",
	"CLIENT_WARN_TAG",
	"CLIENT_ERROR_TAG",
	"CLIENT_FATAL_TAG",

	"CORE_ASSERT",
]

class EType(IntEnum):
	Core = 0
	Client = 1

class ELevel(IntEnum):
	Trace = 0
	Debug = 1
	Info = 2
	Warn = 3
	Error = 4
	Fatal = 5

@dataclass(frozen=True, slots=True)
class FTagDetails:
	bEnabled: bool = True
	LevelFilter: ELevel = ELevel.Trace

class Log:

	@classmethod
	def Init(cls) -> None:
		logsDirectory = Path("logs")
		logsDirectory.mkdir(parents=True, exist_ok=True)

		coreSinks: list[spdlogcxx.sinks.sink] = [
			spdlogcxx.sinks.basic_file_sink_mt("logs/CORE.log", True),
			spdlogcxx.sinks.stdout_color_sink_mt(),
		]

		clientSinks: list[spdlogcxx.sinks.sink] = [
			spdlogcxx.sinks.basic_file_sink_mt("logs/CLIENT.log", True),
			spdlogcxx.sinks.stdout_color_sink_mt()
		]

		coreSinks[0].set_pattern("[%T] [%l] %n: %v")
		clientSinks[0].set_pattern("[%T] [%l] %n: %v")

		coreSinks[1].set_pattern("%^[%T] %n: %v%$")
		clientSinks[1].set_pattern("%^[%T] %n: %v%$")

		cls.s_CoreLogger = spdlogcxx.logger("CORE", coreSinks)
		cls.s_CoreLogger.set_level(spdlogcxx.level.trace)

		cls.s_ClientLogger = spdlogcxx.logger("CLIENT", clientSinks)
		cls.s_ClientLogger.set_level(spdlogcxx.level.trace)

		cls.SetDefaultTagSettings()

	@classmethod
	def Shutdown(cls) -> None:
		cls.s_CoreLogger = None
		cls.s_ClientLogger = None
		cls.s_CustomSinks.clear()

	@classmethod
	def SetDefaultTagSettings(cls) -> None:
		cls.s_EnabledTags = cls.s_DefaultTagDetails

	@classmethod
	def PrintMessage(cls, inType: EType, inLevel: ELevel, inTag: str, inMessage: str) -> None:
		detail = cls.s_EnabledTags[""]
		if inTag in cls.s_EnabledTags:
			detail = cls.s_EnabledTags[inTag]
	
		if detail.bEnabled and detail.LevelFilter <= inLevel:
			logger = cls.s_CoreLogger if inType == EType.Core else cls.s_ClientLogger
			assert logger, "Please call function after Log.Init()."
			match inLevel:
				case ELevel.Trace: logger.trace(inMessage)
				case ELevel.Debug: logger.debug(inMessage)
				case ELevel.Info: logger.info(inMessage)
				case ELevel.Warn: logger.warn(inMessage)
				case ELevel.Error: logger.error(inMessage)
				case ELevel.Fatal: logger.critical(inMessage)

	@classmethod
	def PrintAssertMessage(cls, inType: EType, inMessage: str) -> None:
		logger = cls.s_CoreLogger if inType == EType.Core else cls.s_ClientLogger
		assert logger, "Please call function after Log.Init()."
		logger.error(inMessage)

	s_CoreLogger: spdlogcxx.logger | None = None
	s_ClientLogger: spdlogcxx.logger | None = None

	s_CustomSinks: dict[str, spdlogcxx.sinks.sink] = {}

	s_EnabledTags: dict[str, FTagDetails] = {}
	s_DefaultTagDetails: dict[str, FTagDetails] = {
		"": FTagDetails(),
	}



def LogInit() -> None:
	Log.Init()

def LogShutdown() -> None:
	Log.Shutdown()

###############################################################################
# Tagged logs (prefer these!)
###############################################################################

# Core logging
def CORE_TRACE_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Core, ELevel.Trace, inTag, formatter)

def CORE_DEBUG_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Core, ELevel.Debug, inTag, formatter)

def CORE_INFO_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Core, ELevel.Info, inTag, formatter)

def CORE_WARN_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Core, ELevel.Warn, inTag, formatter)

def CORE_ERROR_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Core, ELevel.Error, inTag, formatter)

def CORE_FATAL_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Core, ELevel.Fatal, inTag, formatter)

# Client logging
def CLIENT_TRACE_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Client, ELevel.Trace, inTag, formatter)

def CLIENT_DEBUG_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Client, ELevel.Debug, inTag, formatter)

def CLIENT_INFO_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Client, ELevel.Info, inTag, formatter)

def CLIENT_WARN_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Client, ELevel.Warn, inTag, formatter)

def CLIENT_ERROR_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Client, ELevel.Error, inTag, formatter)

def CLIENT_FATAL_TAG(inTag: str, inMessage: object) -> None:
	formatter = f"[{inTag}] {inMessage}"
	Log.PrintMessage(EType.Client, ELevel.Fatal, inTag, formatter)

###############################################################################

# Core logging
def CORE_TRACE(inMessage: object) -> None:
	Log.PrintMessage(EType.Core, ELevel.Trace, "", inMessage.__repr__())

def CORE_DEBUG(inMessage: object) -> None:
	Log.PrintMessage(EType.Core, ELevel.Debug, "", inMessage.__repr__())

def CORE_INFO(inMessage: object) -> None:
	Log.PrintMessage(EType.Core, ELevel.Info, "", inMessage.__repr__())

def CORE_WARN(inMessage: object) -> None:
	Log.PrintMessage(EType.Core, ELevel.Warn, "", inMessage.__repr__())

def CORE_ERROR(inMessage: object) -> None:
	Log.PrintMessage(EType.Core, ELevel.Error, "", inMessage.__repr__())

def CORE_FATAL(inMessage: object) -> None:
	Log.PrintMessage(EType.Core, ELevel.Fatal, "", inMessage.__repr__())

# Client logging
def CLIENT_TRACE(inMessage: object) -> None:
	Log.PrintMessage(EType.Client, ELevel.Trace, "", inMessage.__repr__())

def CLIENT_DEBUG(inMessage: object) -> None:
	Log.PrintMessage(EType.Client, ELevel.Debug, "", inMessage.__repr__())

def CLIENT_INFO(inMessage: object) -> None:
	Log.PrintMessage(EType.Client, ELevel.Info, "", inMessage.__repr__())

def CLIENT_WARN(inMessage: object) -> None:
	Log.PrintMessage(EType.Client, ELevel.Warn, "", inMessage.__repr__())

def CLIENT_ERROR(inMessage: object) -> None:
	Log.PrintMessage(EType.Client, ELevel.Error, "", inMessage.__repr__())

def CLIENT_FATAL(inMessage: object) -> None:
	Log.PrintMessage(EType.Client, ELevel.Fatal, "", inMessage.__repr__())

def CORE_ASSERT(inCondition: bool, inMessage: object) -> None:
	if not inCondition:
		frame = inspect.currentframe()
		if not frame:
			assert False, "Failed to get current frame."

		if frame.f_back:
			frame = frame.f_back

		Log.PrintAssertMessage(EType.Core, f"Assertion Failed ({frame.f_code.co_filename}:{frame.f_lineno}) {inMessage}")
		breakpoint()

def CLIENT_ASSERT(inCondition: bool, inMessage: object) -> None:
	if not inCondition:
		frame = inspect.currentframe()
		if not frame:
			assert False, "Failed to get current frame."

		if frame.f_back:
			frame = frame.f_back

		Log.PrintAssertMessage(EType.Client, f"Assertion Failed ({frame.f_code.co_filename}:{frame.f_lineno}) {inMessage}")
		breakpoint()