--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancescriptdoublevariable/

--script name is GetPrefabInstanceScriptDoubleVariable.lua attached a to game object such as water
return_value = 0.0

function Init()
	return_value = GetPrefabInstanceScriptDoubleVariable("1_VandaEngine17-SamplePack1_birdcage", "a")
end

function Update()

end
