from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pathlib import Path

buildDirectory: Path = Path(__file__).parent.absolute()
moduleDirectory: Path = buildDirectory.parent/"src"
vendorDirectory: Path = buildDirectory.parent/"vendor"

fmtDirectory: Path = vendorDirectory/"fmt"
spdlogDirectory: Path = vendorDirectory/"spdlog"

includes: list[str] = []
includes.extend([str(fmtDirectory/"include"), str(spdlogDirectory/"include"), str(spdlogDirectory/"src")])

sources: list[str] = []
sources.append(str(moduleDirectory/"Pyspdlog.cpp"))
sources.append(str(fmtDirectory/"src"/"format.cc"))
sources.extend(
	[
		str(spdlogDirectory/"src"/"common.cpp"),
		str(spdlogDirectory/"src"/"logger.cpp"),
		str(spdlogDirectory/"src"/"pattern_formatter.cpp"),
		str(spdlogDirectory/"src"/"spdlog.cpp"),
		str(spdlogDirectory/"src"/"details/file_helper.cpp"),
		str(spdlogDirectory/"src"/"details/os_filesystem.cpp"),
		str(spdlogDirectory/"src"/"details/log_msg.cpp"),
		str(spdlogDirectory/"src"/"details/async_log_msg.cpp"),
		str(spdlogDirectory/"src"/"details/err_helper.cpp"),
		str(spdlogDirectory/"src"/"sinks/base_sink.cpp"),
		str(spdlogDirectory/"src"/"sinks/basic_file_sink.cpp"),
		str(spdlogDirectory/"src"/"sinks/rotating_file_sink.cpp"),
		str(spdlogDirectory/"src"/"sinks/stdout_sinks.cpp"),
		str(spdlogDirectory/"src"/"sinks/async_sink.cpp"),
		str(spdlogDirectory/"src"/"details"/"os_windows.cpp"),
    	str(spdlogDirectory/"src"/"sinks"/"wincolor_sink.cpp"),
	]
)

extModule = [
	Pybind11Extension(
		"spdlogcxx.__init__",
		sources=sources,
		include_dirs=includes,
		extra_compile_args=["/O2", "/utf-8", "/MP", "/std:c++latest"] if Path(__file__).drive else ["-O3", "-std=c++23"],
	)
]

setup(
	name="spdlogcxx",
	version="0.1.0",
	packages=["spdlogcxx"],
	ext_modules=extModule,
	cmdclass={"build_ext": build_ext},
	package_data={
		"spdlogcxx": ["*.pyi", "py.typed"],
	},
	zip_safe=False,
	python_requires=">=3.9"
)