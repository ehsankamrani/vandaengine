--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/setprefabinstanceshininess/

--Script name is SetPrefabInstanceShininess2.lua

function Init()
	EnablePrefabInstanceMaterial("this")
	SetPrefabInstanceShininess("this", 20.0)
end

function Update()

end
