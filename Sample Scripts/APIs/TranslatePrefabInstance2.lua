--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/translateprefabinstance/

--Name of script is TranslatePrefabInstance2.lua

translateX = 0.0
translateY = 0.0
translateZ = 0.0

function Init()

end

function Update()
	translateX = translateX + (GetElapsedTime() * 0.1)
	translateY = translateY + (GetElapsedTime() * 0.2)
	translateZ = translateZ + (GetElapsedTime() * 0.3)

	if translateX > 5.0 then translateX = 0.0 end
	if translateY > 5.0 then translateY = 0.0 end
	if translateZ > 5.0 then translateZ = 0.0 end

	TranslatePrefabInstance("this", translateX, translateY, translateZ)
end
