--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/setprefabinstanceemission/

--Script name is SetPrefabInstanceEmission2.lua

function Init()
	EnablePrefabInstanceMaterial("this")
	SetPrefabInstanceEmission("this", 0.75, 0.5, 0.25)
end

function Update()

end
