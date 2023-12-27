--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/rotateprefabinstance/

rotateX = 0.0
rotateY = 0.0
rotateZ = 0.0

function Init()

end

function Update()
	rotateX = rotateX + GetElapsedTime()
	rotateY = rotateY + (GetElapsedTime() * 2.0)
	rotateZ = rotateZ + (GetElapsedTime() * 3.0)

	if rotateX > 360.0 then rotateX = rotateX - 360.0 end
	if rotateY > 360.0 then rotateY = rotateY - 360.0 end
	if rotateZ > 360.0 then rotateZ = rotateZ - 360.0 end

	RotatePrefabInstance("1_VandaEngine17-SamplePack1_well", rotateX, rotateY, rotateZ)
end
