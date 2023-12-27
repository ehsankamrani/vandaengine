--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/setprefabinstancetransparency/

--Script name is SetPrefabInstanceTransparency2.lua

function Init()
	EnablePrefabInstanceMaterial("this")
	SetPrefabInstanceTransparency("this", 0.5)
end

function Update()

end
