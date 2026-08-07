from . import level, color_mode, log_msg, formatter

from types import CapsuleType

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