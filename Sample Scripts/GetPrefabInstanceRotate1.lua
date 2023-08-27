--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancerotate/

rotateX = 0.0
rotateY = 0.0
rotateZ = 0.0

function Init()
	rotateX, rotateY, rotateZ = GetPrefabInstanceRotate("1_VandaEngine17-SamplePack1_well")

	message = string.format("\nPrefab instance rotation is > (%.2f, %.2f, %.2f)" , rotateX, rotateY, rotateZ)
	PrintConsole(message)
end

function Update()

end
