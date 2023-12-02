--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/getanimationclipdurationofprefabinstance/

--name of this script is GetAnimationClipDurationOfPrefabInstance2.lua

animationTime = 0.0

function Init()
	animationTime = GetAnimationClipDurationOfPrefabInstance("this", "defaultClip")

	message = string.format("\nanimation duration is > %.2f" ,animationTime )
	PrintConsole(message)
end

function Update()

end
