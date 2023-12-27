--Copyright (C) 2024 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/readintvariablefromFile/

iVar = 0

function Init()
   --Create a folder in Assets/Data/ path
   CreateFolder("Lev1")

   --Create and open file to write data
   OpenFileForWriting("Lev1/level1.bin")
   WriteIntVariableToFile(3)
   CloseFile("Lev1/level1.bin")

   --Open File to load data
   OpenFileForReading("Lev1/level1.bin")
   iVar = ReadIntVariableFromFile()
   CloseFile("Lev1/level1.bin")
end

