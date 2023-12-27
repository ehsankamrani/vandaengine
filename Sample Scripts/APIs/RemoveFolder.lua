--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/removefolder/

function OnTriggerEnter(otherActorName)
   --Create a folder in Assets/Data/ path
   CreateFolder("Lev1")

    --Create a folder in Assets/Data/Lev1 path
	CreateFolder("Lev1/subLev1")

   --Create and open file to write data
   OpenFileForWriting("Lev1/subLev1/level1.bin")
   WriteBoolVariableToFile(true)
   CloseFile("Lev1/subLev1/level1.bin")
end

function OnTriggerStay(otherActorName)

end

function OnTriggerExit(otherActorName)
	RemoveFolder("Lev1")
end
