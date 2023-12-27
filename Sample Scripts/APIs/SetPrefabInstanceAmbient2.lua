--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/setprefabinstanceambient/

--Script name is SetPrefabInstanceAmbient2.lua

function Init()
	EnablePrefabInstanceMaterial("this")
	SetPrefabInstanceAmbient("this", 0.75, 0.5, 0.25)
end

function Update()

end
