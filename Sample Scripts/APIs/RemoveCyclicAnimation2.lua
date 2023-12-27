--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/removecyclicanimation/

--name of script is RemoveCyclicAnimation2.lua

animation = true

function Init()

end

function Update()
	if animation == true then 
		RemoveCyclicAnimation("this", "run", 1.0) 
		animation = false
	end
end


