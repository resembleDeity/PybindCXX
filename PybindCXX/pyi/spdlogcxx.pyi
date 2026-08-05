from collections.abc import Iterable
from datetime import datetime
from typing import overload
from types import CapsuleType
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

	def empty(self) -> bool: ...

	@staticmethod
	def basename(inPath: str) -> str: ...

	filename: str
	short_filename: str
	line: int
	funcname: str

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

	logger_name: str
	log_level: level
	time: datetime
	thread_id: int
	source: source_loc
	payload: str

	color_range_start: int
	color_range_end: int



class formatter:

	def __init__(self) -> None: ...

	def format(self, inMessage: log_msg) -> str: ...
	def clone(self) -> formatter: ...



class sink:

	def __init__(self) -> None: ...

	def log(self, inMessage: log_msg) -> None: ...
	def flush(self) -> None: ...
	def set_pattern(self, inPattern: str) -> None: ...
	def set_formatter(self, inFormatter: formatter) -> None: ...

	def set_level(self, inLevel: level) -> None: ...
	def log_level(self) -> level: ...
	def should_log(self, inLevel: level) -> bool: ...



class base_sink_mt(sink):

	def __init__(self) -> None: ...

	def sink_it_(self, inMessage: log_msg) -> None: 
		''' 
		This is protected virtual function, please do not call it in outside.
		It should be implemented in derived classes. 
		''' 
		...

	def flush_(self) -> None:
		''' 
		This is protected virtual function, please do not call it in outside.
		It should be implemented in derived classes. 
		'''
		...

	def set_pattern_(self, inPattern: str) -> None: 
		'''
		This is protected virtual function, please do not call it in outside.
		This function has default implementation.
		'''
		...

	def set_formatter_(self, inFormatter: formatter) -> None:
		'''
		This is protected virtual function, please do not call it in outside.
		This function has default implementation.
		'''
		...

	formatter_: formatter = ...

class base_sink_st(sink):

	def __init__(self) -> None: ...

	def sink_it_(self, inMessage: log_msg) -> None: 
		''' 
		This is protected virtual function, please do not call it in outside.
		It should be implemented in derived classes. 
		''' 
		...

	def flush_(self) -> None:
		''' 
		This is protected virtual function, please do not call it in outside.
		It should be implemented in derived classes. 
		'''
		...

	def set_pattern_(self, inPattern: str) -> None: 
		'''
		This is protected virtual function, please do not call it in outside.
		This function has default implementation.
		'''
		...

	def set_formatter_(self, inFormatter: formatter) -> None:
		'''
		This is protected virtual function, please do not call it in outside.
		This function has default implementation.
		'''
		...

	formatter_: formatter = ...



class basic_file_sink_mt(base_sink_mt):

	def __init__(self, inFileName: str, inbTruncate: bool = False) -> None: ...

	def filename(self) -> str: ...
	def truncate(self) -> None: ...

class basic_file_sink_st(base_sink_st):

	def __init__(self, inFileName: str, inbTruncate: bool = False) -> None: ...

	def filename(self) -> str: ...
	def truncate(self) -> None: ...


class color_sink_mt(base_sink_mt):
	
	def __init__(self, Handle: CapsuleType, inMode: color_mode) -> None: ...

	def set_color(self, inLevel: level, inColor: int) -> None: ...
	def set_color_mode(self, inMode: color_mode) -> None: ...

class color_sink_st(base_sink_st):
	
	def __init__(self, Handle: CapsuleType, inMode: color_mode) -> None: ...

	def set_color(self, inLevel: level, inColor: int) -> None: ...
	def set_color_mode(self, inMode: color_mode) -> None: ...

class stdout_color_sink_mt(color_sink_mt):
	
	def __init__(self, inMode: color_mode = color_mode.automatic) -> None: ...

class stdout_color_sink_st(color_sink_st):
	
	def __init__(self, inMode: color_mode = color_mode.automatic) -> None: ...



class logger:

	@overload
	def __init__(self, inName: str) -> None: ...

	@overload
	def __init__(self, inName: str, inSink: sink) -> None: ...

	@overload
	def __init__(self, inName: str, inSink: Iterable[sink]) -> None: ...

	def set_level(self, inLevel: level) -> None: ...

	def trace(self, inMessage: str) -> None: ...
	def debug(self, inMessage: str) -> None: ...
	def info(self, inMessage: str) -> None: ...
	def warn(self, inMessage: str) -> None: ...
	def error(self, inMessage: str) -> None: ...
	def critical(self, inMessage: str) -> None: ...