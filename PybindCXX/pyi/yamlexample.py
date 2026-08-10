import yamlcxx
from dataclasses import dataclass

@dataclass
class Project:
	Name: str = ""

	def __yaml_emitter__(self, inEmitter: yamlcxx.Emitter) -> yamlcxx.Emitter:
		return inEmitter << yamlcxx.Key << "Name" << yamlcxx.Value << self.Name

	def __yaml_load__(self, inNode: yamlcxx.Node) -> None:
		self.Name = inNode["Name"].as_str()



testProject = Project("TestProject")

with open("testProject.yproj", "w") as file:
	e = yamlcxx.Emitter()
	e.Start(yamlcxx.BeginMap)
	e.Start(yamlcxx.Key).Value("Project").Type(yamlcxx.Value)
	e.Start(yamlcxx.BeginMap)

	e.Start(yamlcxx.Key).Value("Name").Type(yamlcxx.Value).Value("Untitled")

	e.End(yamlcxx.EndMap)
	e.Start(yamlcxx.Key).Value("ConfigName").Type(yamlcxx.Value).Value("ProjectConfig")
	e.End(yamlcxx.EndMap)

	file.write(e.c_str())



data = yamlcxx.LoadFile("testProject.yproj")
projectNode = data["Project"]
loadProject = Project()
projectNode >> loadProject

configName: str = data["ConfigName"].as_str()

print(loadProject)
print(configName)