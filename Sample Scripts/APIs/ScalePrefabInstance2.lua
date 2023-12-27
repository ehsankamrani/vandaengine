--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/scaleprefabinstance/

--Name of script is ScalePrefabInstance2.lua

scaleX = 1.0
scaleY = 1.0
scaleZ = 1.0

function Init()

end

function Update()
	scaleX = scaleX + (GetElapsedTime() * 0.1)
	scaleY = scaleY + (GetElapsedTime() * 0.2)
	scaleZ = scaleZ + (GetElapsedTime() * 0.3)

	if scaleX > 5.0 then scaleX = 1.0 end
	if scaleY > 5.0 then scaleY = 1.0 end
	if scaleZ > 5.0 then scaleZ = 1.0 end

	ScalePrefabInstance("this", scaleX, scaleY, scaleZ)
end
