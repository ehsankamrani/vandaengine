--Copyright (C) 2023 Ehsan Kamrani 
--This file is licensed and distributed under MIT license

--Explanations: https://vanda3d.org/closefile/

function Init()
	OpenFileForWriting("level1/data.bin")
	--write data to file here
	closefile("level1/data.bin")
end

function Update()

end



