from setuptools import setup
from pybind11.setup_helpers import Pybind11Extension, build_ext
from pathlib import Path

buildDirectory: Path = Path(__file__).parent.absolute()
moduleDirectory: Path = buildDirectory.parent/"src"
vendorDirectory: Path = buildDirectory.parent/"vendor"

yamlDirectory: Path = vendorDirectory/"yaml-cpp"

includes: list[str] = []
includes.append(str(yamlDirectory/"include"))

sources: list[str] = []
sources.append(str(moduleDirectory/"Pyyaml.cpp"))
sources.extend([str(file) for file in (yamlDirectory/"src").glob("*.cpp") if file.is_file()])

extModule = [
	Pybind11Extension(
		"yamlcxx.__init__",
		sources=sources,
		include_dirs=includes,
		define_macros=[("YAML_CPP_STATIC_DEFINE", "1")],
		extra_compile_args=["/O2", "/utf-8", "/MP", "/std:c++latest"] if Path(__file__).drive else ["-O3", "-std=c++23"],
	)
]

setup(
	name="yamlcxx",
	version="0.1.0",
	packages=["yamlcxx"],
	ext_modules=extModule,
	cmdclass={"build_ext": build_ext},
	package_data={
		"yamlcxx": ["*.pyi", "py.typed"],
	},
	zip_safe=False,
	python_requires=">=3.9"
)