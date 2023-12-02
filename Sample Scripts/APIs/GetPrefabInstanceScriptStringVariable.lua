--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancescriptstringvariable/

--script name is GetPrefabInstanceScriptStringVariable.lua attached a to game object such as water
return_value = ""

function Init()
	return_value = GetPrefabInstanceScriptStringVariable("1_VandaEngine17-SamplePack1_birdcage", "a")
end

function Update()

end
