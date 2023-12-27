--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/setprefabinstancespecular/

--Script name is SetPrefabInstanceSpecular2.lua

function Init()
	EnablePrefabInstanceMaterial("this")
	SetPrefabInstanceSpecular("this", 0.75, 0.5, 0.25)
end

function Update()

end
