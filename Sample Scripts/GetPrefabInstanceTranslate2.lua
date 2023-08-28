--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getprefabinstancetranslate/

--Name of script is GetPrefabInstanceTranslate2.lua

posX = 0.0
posY = 0.0
posZ = 0.0

function Init()
	posX, posY, posZ = GetPrefabInstanceTranslate("this")

	message = string.format("\nPrefab instance position is > (%.2f, %.2f, %.2f)" , posX, posY, posZ)
	PrintConsole(message)
end

function Update()

end

