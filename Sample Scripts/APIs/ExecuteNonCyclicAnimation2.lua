--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/Executenoncyclicanimation/

--name of script is executenoncyclicanimation2.lua

animation = true

function Init()

end

function Update()
	if animation == true then 
		ExecuteNonCyclicAnimation("this", "defaultClip", 0.5, 0.6, 0.4, true)
		animation = false
	end
end




