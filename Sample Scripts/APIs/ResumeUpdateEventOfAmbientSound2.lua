--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/resumeupdateeventofambientsound/

--Name of script is ResumeUpdateEventOfAmbientSound2.lua

function Init()
	PauseUpdateEventOfAmbientSound("this")

	ResumeUpdateEventOfAmbientSound("this")
end

function Update()
	PrintConsole("\nUpdate")
end
