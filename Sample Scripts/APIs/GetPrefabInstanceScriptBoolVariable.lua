--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancescriptboolvariable/

--script name is GetPrefabInstanceScriptBoolVariable.lua attached a to game object such as water
return_value = false

function Init()
	return_value = GetPrefabInstanceScriptBoolVariable("1_VandaEngine17-SamplePack1_birdcage", "a")
end

function Update()

end
