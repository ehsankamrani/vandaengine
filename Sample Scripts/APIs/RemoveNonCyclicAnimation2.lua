--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/removenoncyclicanimation/

--name of script is RemoveNonCyclicAnimation2.lua

animation = true

function Init()

end

function Update()
	if animation == true then 
		RemoveNonCyclicAnimation("this", "run") 
		animation = false
	end
end


