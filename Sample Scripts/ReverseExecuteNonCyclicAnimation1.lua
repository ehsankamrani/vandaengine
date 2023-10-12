--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/reverseexecutenoncyclicanimation/

function OnTriggerEnter(otherActorName)
	ExecuteNonCyclicAnimation("1_animation_test_boy", "defaultClip", 0.5, 0.7, 1.0, false)
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	ReverseExecuteNonCyclicAnimation("1_animation_test_boy", "defaultClip")
end

