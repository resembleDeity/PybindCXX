from . import sinks

from collections.abc import Iterable
from datetime import datetime
from typing import overload, Any
from enum import IntEnum



class level(IntEnum):
	trace = ...
	debug = ...
	info = ...
	warn = ...
	err = ...
	critical = ...
	off = ...
	n_levels = ...

class color_mode(IntEnum):
	always = ...
	automatic = ...
	never = ...

class source_loc:

	@overload
	def __init__(self) -> None: ...

	@overload
	def __init__(self, inFileName: str, inLine: int, inFuncName: str) -> None: ...

	def __init__(self, *inArgs: Any, **inKwArgs: Any) -> None:
		self.filename: str
		self.short_filename: str
		self.line: int
		self.funcname: str

	def empty(self) -> bool: ...

	@staticmethod
	def basename(inPath: str) -> str: ...



class log_msg:

	@overload
	def __init__(self) -> None: ...

	@overload
	def __init__(self, 
		inLogTime: datetime, inLocation: source_loc, 
		inLoggerName: str, inLevel: level, inMessage: str
	) -> None: ...

	@overload
	def __init__(self, 
		inLocation: source_loc, 
		inLoggerName: str, inLevel: level, inMessage: str
	) -> None: ...

	@overload
	def __init__(self, 
		inLoggerName: str, inLevel: level, inMessage: str
	) -> None: ...

	def __init__(self, *inArgs: Any, **inKwArgs: Any) -> None:
		self.logger_name: str
		self.log_level: level
		self.time: datetime
		self.thread_id: int
		self.source: source_loc
		self.payload: str
		
		self.color_range_start: int
		self.color_range_end: int



class formatter:

	def __init__(self) -> None: ...

	def format(self, inMessage: log_msg) -> str: ...
	def clone(self) -> formatter: ...



class logger:

	@overload
	def __init__(self, inName: str) -> None: ...

	@overload
	def __init__(self, inName: str, inSink: sinks.sink) -> None: ...

	@overload
	def __init__(self, inName: str, inSink: Iterable[sinks.sink]) -> None: ...

	def set_level(self, inLevel: level) -> None: ...

	def trace(self, inMessage: str) -> None: ...
	def debug(self, inMessage: str) -> None: ...
	def info(self, inMessage: str) -> None: ...
	def warn(self, inMessage: str) -> None: ...
	def error(self, inMessage: str) -> None: ...
	def critical(self, inMessage: str) -> None: ...