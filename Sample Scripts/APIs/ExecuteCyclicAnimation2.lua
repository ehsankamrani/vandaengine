--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/executecyclicanimation/

--name of script is executecyclicanimation2.lua

animation = true

function Init()

end

function Update()
	if animation == true then 
		ExecuteCyclicAnimation("this", "run", 0.3, 1.0) 
		animation = false
	end
end


