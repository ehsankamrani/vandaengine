//Original Work: Copyright 2006 Sony Computer Entertainment Inc.
//Modified Work: Copyright (C) 2021 Ehsan Kamrani 
//This file is licensed and distributed under MIT license

#include "stdafx.h"
#include "scene.h"
#include "Animation.h"
#include "..\VandaEngine1Dlg.h"

CScene::CScene()
{
	m_collada = NULL;
	m_loadAnimation = CTrue; //Load animations by default. We can read from a file to specify its value
	m_currentClipIndex = 0;
	//m_loadDefaultCamera = CFalse; //Just need to load the defult camera once	
	//used in animation
	m_lastKeyTime = 0; 
	m_firstKeyTime = 0; 
	m_sceneRoot = NULL;
	m_numAnimatedNodes = 0;

	m_hasAnimation = CFalse;
	m_animationStatus = eANIM_PLAY;
	m_updateAnimationLists = CFalse;
	m_update = CTrue; //used to update the scene( computing the local to world matrices, etc. )
	m_updateAnimation = CTrue;
	m_numClips = 0;
	m_isTrigger = CFalse;
	m_compress = CTrue;
	m_playAnimation = m_loopAnimationAtStartup = CTrue;
	m_alwaysVisible = CFalse;
	m_castShadow = CTrue;
	m_isTransformable = CFalse;
	m_isSelectable = CFalse;
	m_clipIndexForStartup = 0;
	m_isLODScene = CFalse;
	m_baseOfLODScene = NULL;
	m_isVisible = CTrue;
	m_updateBoundingBox = CFalse;
	m_calculateDynamicBoundingBox = CFalse;
	//m_hasScript = CFalse;
	//m_updateScript = CFalse;
	//Cpy(m_script, "\n");
}

CScene::~CScene()
{
	Destroy();
}

CVoid CScene::SetUpdateBB(CBool update)
{
	m_updateBoundingBox = update;
}

CBool CScene::GetUpdateBB()
{
	return 	m_updateBoundingBox;
}

int CScene::GetFileCrc(const char* filenameinzip,void*buf,unsigned long size_buf,unsigned long* result_crc)
{
   unsigned long calculate_crc=0;
   int err=ZIP_OK;
   FILE * fin = fopen64(filenameinzip,"rb");
   unsigned long size_read = 0;
   unsigned long total_read = 0;
   if (fin==NULL)
   {
       err = ZIP_ERRNO;
   }

    if (err == ZIP_OK)
        do
        {
            err = ZIP_OK;
            size_read = (int)fread(buf,1,size_buf,fin);
            if (size_read < size_buf)
                if (feof(fin)==0)
            {
				CChar temp[MAX_NAME_SIZE];
                sprintf( temp, "\n%s %s", "error in reading ",filenameinzip);
				PrintInfo( temp, COLOR_RED );
                err = ZIP_ERRNO;
            }

            if (size_read>0)
                calculate_crc = crc32(calculate_crc,(Bytef*)buf,size_read);
            total_read += size_read;

        } while ((err == ZIP_OK) && (size_read>0));

    if (fin)
        fclose(fin);

    *result_crc=calculate_crc;
    return err;
}

CInt CScene::WriteZipFile(CChar* zipFileName, CChar* fileInZipName, CChar* fileInZipPath, const CChar* password )
{
    FILE * fin;
	fin = fopen(fileInZipPath,"rb");
    if (fin==NULL)
    {
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "\n%s %s %s", "Error in opening",fileInZipPath, "for reading");
		PrintInfo( temp, COLOR_RED );
		return -1;
   }

    int size_buf=WRITEBUFFERSIZE;
    unsigned long crcFile=0;
    unsigned long size_read = 0;
    zip_fileinfo zi;
    int err=0;
    void* buf=NULL;
    buf = (void*)malloc(size_buf);
    if (buf==NULL)
    {
		PrintInfo("\nWriteZipFile: Error allocating memory", COLOR_RED);
        return -1;
    }
	zipFile zf;
	zf = zipOpen(zipFileName, 0);
    if (zf == NULL)
    {
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "\n%s%s", "Error opening ",zipFileName);
		PrintInfo( temp, COLOR_RED );
		free(buf);
        return -1;
    }
    if (password != NULL)
		GetFileCrc(fileInZipPath,buf,size_buf,&crcFile);

    err = zipOpenNewFileInZip3(zf,fileInZipName,&zi,
                     NULL,0,NULL,0,NULL /* comment*/,
                     Z_DEFLATED,  Z_DEFAULT_COMPRESSION ,0,
                     -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                     password,crcFile);
    if (err != ZIP_OK)
	{
		CChar temp[MAX_NAME_SIZE];
        sprintf(temp, "\n%s %s %s", "Error in opening",fileInZipPath, "in zipfile");
		zipCloseFileInZip(zf);
		zipClose(zipOpen, "Vanda Engine 1.7.8");
		free(buf);
		return -1;
	}
   // else
   // {
   //     fin = fopen(fileInZipPath,"rb");
   //     if (fin==NULL)
   //     {
			//CChar temp[MAX_NAME_SIZE];
			//sprintf(temp, "\n%s %s %s", "Error in opening",fileInZipPath, "for reading");
			//PrintInfo( temp, COLOR_RED );
			//zipCloseFileInZip(zf);
			//zipClose(zf, "Vanda Engine 1.7.8");
			//free(buf);
			//return -1;
   //     }
   // }
    do
    {
        err = ZIP_OK;
        size_read = (int)fread(buf,1,size_buf,fin);
        if (size_read < (unsigned long)size_buf)
		{
			if (feof(fin)==0)
			{
				CChar temp[MAX_NAME_SIZE];
				sprintf(temp, "\n%s%s", "Error in reading ",fileInZipPath);
				zipCloseFileInZip(zf);
				zipClose(zf, "Vanda Engine 1.7.8");
				free(buf);
				return -1;
			}
		}

        if (size_read>0)
        {
            err = zipWriteInFileInZip (zf,buf,size_read);
            if (err<0)
            {
				CChar temp[MAX_NAME_SIZE];

                sprintf( temp, "\n%s%s%s", "Error in writing ", fileInZipPath, " in the zipfile");
				zipCloseFileInZip(zf);
				zipClose(zf, "Vanda Engine 1.7.8");
				free(buf);
				return -1;
            }
        }
    } while ((err == ZIP_OK) && (size_read>0));

    if (fin)
        fclose(fin);
	zipCloseFileInZip(zf);
	zipClose(zf,"Vanda Engine 1.7.8");
    free(buf);
	return 1;
}

std::string CScene::ReadZipFile(CChar* zipFile, CChar* fileInZip) {
    int err = UNZ_OK;                 // error status
    uInt size_buf = WRITEBUFFERSIZE;  // byte size of buffer to store raw csv data
    void* buf;                        // the buffer  
	std::string sout;                      // output strings
    char filename_inzip[256];         // for unzGetCurrentFileInfo
    unz_file_info file_info;          // for unzGetCurrentFileInfo   
 
    unzFile uf = unzOpen(zipFile); // open zipfile stream
    if (uf==NULL) {
		CChar temp[MAX_URI_SIZE];
        sprintf( temp, "\n%s %s %s", "Cannot open '", zipFile, "'" );
		PrintInfo( temp, COLOR_RED );
        return sout;
    } // file is open
 
    if ( unzLocateFile(uf,fileInZip,1) ) { // try to locate file inside zip
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s %s %s %s %s", "File '", fileInZip, "' not found in '", zipFile, "'" );
		PrintInfo( temp, COLOR_RED );
        // second argument of unzLocateFile: 1 = case sensitive, 0 = case-insensitive
        return sout;
    } // file inside zip found
 
    if (unzGetCurrentFileInfo(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0)) {
		CChar temp[MAX_URI_SIZE];
        sprintf( temp, "\n%s %s %s", "Error with zipfile '", zipFile, "' in unzGetCurrentFileInfo()" );
		PrintInfo( temp, COLOR_RED );
        return sout;
    } // obtained the necessary details about file inside zip
 
    buf = (void*)malloc(size_buf); // setup buffer
    if (buf==NULL) {
        PrintInfo( "\nError allocating memory for read buffer", COLOR_RED );
        return sout;
    } // buffer ready
 
	if( Cmp( g_currentPassword, "\n" ) )
		err = unzOpenCurrentFilePassword(uf,NULL); // Open the file inside the zip (password = NULL)
	else
		err = unzOpenCurrentFilePassword(uf, g_currentPassword); // Open the file inside the zip (password = NULL)
    if (err!=UNZ_OK) {
		CChar temp[MAX_URI_SIZE];
        sprintf( temp, "%s %s %s", "Error with zipfile '", zipFile, "' in unzOpenCurrentFilePassword()" );
		PrintInfo( temp, COLOR_RED );
        return sout;
    } // file inside the zip is open
 
    // Copy contents of the file inside the zip to the buffer
	CChar temp[MAX_URI_SIZE];
    sprintf( temp, "\n%s %s %s %s %s", "Extracting '", filename_inzip, "' from '", zipFile, "'");
	PrintInfo( temp );
    do {
        err = unzReadCurrentFile(uf,buf,size_buf);
        if (err<0) {
			CChar temp[MAX_URI_SIZE];
            sprintf( temp, "\n%s %s %s", "Error with zipfile '", zipFile, "' in unzReadCurrentFile()");
			PrintInfo( temp, COLOR_RED );
            sout = ""; // empty output string
            break;
        }
        // copy the buffer to a string
        if (err>0) for (int i = 0; i < (int) err; i++) 
		{
			sout.push_back( *(((char*)buf)+i) );
		}
    } while (err>0);
 
    err = unzCloseCurrentFile (uf);  // close the zipfile
    if (err!=UNZ_OK) {
		CChar temp[MAX_URI_SIZE];
        sprintf( temp, "\n%s %s %s", "Error with zipfile '", zipFile, "' in unzCloseCurrentFile()");
		PrintInfo( temp, COLOR_RED );
        sout = ""; // empty output string
    }
	unzClose( uf );
    free(buf); // free up buffer memory
    return sout;
}

CBool CScene::Load(CChar * fileName, CChar* clipName, CInt clipIndex, CScene* otherScene, CBool reportWarningsAndErrors, CBool readFromBuffer )
{
	if ( fileName == NULL )
		return CFalse; 
	CChar * nameOnly = GetAfterPath( fileName );
	SetName( nameOnly );

	// Instantiate the reference implementation
	m_collada = new DAE;
	PrintInfo( "\n" );
	PrintInfo( _T("\n========Importing new external scene========"), COLOR_BLUE ); 
	numErrors = numWarnings = 0;
	domCOLLADA *dom;
	if( readFromBuffer )
	{
		/////////////////////////////////////////////////////////////////
		//zip path
		CChar zipPath[MAX_NAME_SIZE];
		Cpy( zipPath, fileName );
		GetWithoutDot( zipPath );
		Append(zipPath, ".zip" );
		Cpy(g_currentZipFileName, zipPath);

		//file name inside zip file
		CChar fileNameInZip[MAX_NAME_SIZE];
		Cpy( fileNameInZip, GetAfterPath( fileName ) );
		//Uncompress zip file
		std::string buffer = ReadZipFile( zipPath, fileNameInZip );
		//res = m_collada->load( "", buffer.c_str() );
		dom = m_collada->openFromMemory( "", buffer.c_str() );
		///////////////////////////////////////////////////////////////
	}
	else
	{
		// load with full path 
		//res = m_collada->load( fileName );
		dom = m_collada->open(fileName);
	}

	//if (res != DAE_OK)
	//{
	//	PrintInfo(_T("\nCScene::Load > Error loading the COLLADA file:") + CString(fileName), COLOR_RED );
	//	delete m_collada;
	//	m_collada = NULL;

		//if( reportWarningsAndErrors )
		//{
		//	char tempReport[MAX_NAME_SIZE];;
		//	sprintf( tempReport, "%s - fatal error (s)", nameOnly );
		//	PrintInfo2( tempReport, COLOR_RED ); 
		//}

	//	return CFalse;
	//}
	PrintInfo( _T("\nCOLLADA_DOM Runtime database initialized from" ) );
	PrintInfo( _T("'") +  CString( fileName ), COLOR_RED_GREEN );
	//PrintInfo( _T("nameOnly: '") + (CString)nameOnly + _T( "'\n" ) );

	//domCOLLADA *dom = m_collada->getDom(nameOnly);
	//if ( !dom )
	//	dom = m_collada->getDom( fileName); 
	if ( !dom )
	{
		PrintInfo( _T("\nCScene::Load > COLLADA File loaded to the dom, but query for the dom assets failed "), COLOR_RED );
		PrintInfo( _T("\nCScene::Load > COLLADA Load Aborted! "), COLOR_RED );
		delete m_collada;	
		m_collada = NULL;
		if( reportWarningsAndErrors )
		{
			char tempReport[MAX_NAME_SIZE];;
			sprintf( tempReport, "\n%s - Fatal error (s)", nameOnly );
			PrintInfo( tempReport, COLOR_RED ); 
		}
		return CFalse; 
	}

	CInt ret = 0;
	//PrintInfo("Begin Conditioning\n");
	//ret = kmzcleanup(m_collada, true);
	//if (ret)
	//	PrintInfo("kmzcleanup complete\n");
	if (!otherScene)
	{
		ret = Triangulate(m_collada);
		if (ret)
			PrintInfo("\nTriangulate complete");
	}
	//ret = deindexer(m_collada);
	//if (ret)
	//	PrintInfo("deindexer complete\n");

	//PrintInfo("Finish Conditioning\n");

	// Need to now get the asset tag which will determine what vector x y or z is up.  Typically y or z. 
	if ( dom->getAsset()->getUp_axis() )
	{
		domAsset::domUp_axis *up = dom->getAsset()->getUp_axis();
		switch( up->getValue() )
		{
			case UPAXISTYPE_X_UP:
				PrintInfo(_T("\nWarning!X is Up Data and Hiearchies must be converted!") ); 
				PrintInfo(_T("\nConversion to X axis Up isn't currently supported!") ); 
				PrintInfo(_T("\nCOLLADA defaulting to Y Up") ); 
				numWarnings +=1;
				//CRender.SetUpAxis(eCYUp); 
				break; 
			case UPAXISTYPE_Y_UP:
				PrintInfo( _T("\nY Axis is Up for this file...COLLADA set to Y Up ") ); 
				//CRender.SetUpAxis(eCYUp); 
				break;
			case UPAXISTYPE_Z_UP:
				PrintInfo( _T("\nZ Axis is Up for this file ") ); 
				PrintInfo( _T("\nAll Geometries and Hiearchies converted!"), COLOR_YELLOW ) ; 
				numWarnings +=1;
				//CRender.SetUpAxis(eCZUp); 
				break; 
			default:
				break; 
		}
	}
	strcpy( m_fileName, fileName ); 
	strcpy( m_pureFileName, nameOnly ); 

	// Load all the image libraries
	//for ( CUInt i = 0; i < dom->getLibrary_images_array().getCount(); i++)
	//{
	//	ReadImageLibrary( dom->getLibrary_images_array()[i] );			
	//}

	CBool success = CFalse;

	/*
	CChar *cfxBinFilename = ReadCfxBinaryFilename( dom->getExtra_array() );
	
	if ( cfxBinFilename != NULL ) 
	{
		cfxLoader::setBinaryLoadRemotePath( BasePath );
		success = (CBool) cfxLoader::loadMaterialsAndEffectsFromBinFile(cfxBinFilename, cfxMaterials, cfxEffects, cgContext);
		assert(success);
	}
	else
	{
	*/
		//success = ( CBool ) cfxLoader::loadMaterialsAndEffects( m_collada, m_cfxMaterials, m_cfxEffects, m_cgContext );
		//assert(success);
	/*}*/
	
	// Load all the effect libraries
	//for ( CUInt i = 0; i < dom->getLibrary_effects_array().getCount(); i++)
	//{
	//	ReadEffectLibrary( dom->getLibrary_effects_array()[i] );			
	//}

	//// Load all the material libraries
	//for ( CUInt i = 0; i < dom->getLibrary_materials_array().getCount(); i++)
	//{
 //		ReadMaterialLibrary( dom->getLibrary_materials_array()[i] );			
	//}

	// Load all the animation libraries
	for (CUInt i = 0; i < dom->getLibrary_animations_array().getCount(); i++)
	{
		if (otherScene)
		{
			otherScene->ReadAnimationLibrary(dom->getLibrary_animations_array()[i], CTrue);
			otherScene->m_hasAnimation = CTrue;

		}
		else
		{
			ReadAnimationLibrary(dom->getLibrary_animations_array()[i]);
			m_hasAnimation = CTrue;
		}
	}
	//Load all animation clips
	for ( CUInt i = 0; i < dom->getLibrary_animation_clips_array().getCount(); i++)
	{
		ReadAnimationClipLibrary( dom->getLibrary_animation_clips_array()[i] );			
	}

	if (!otherScene)
	{
		//If there's no clip in COLLADA file, try to create a default clip
		if (m_numClips == 0 && dom->getLibrary_animations_array().getCount() > 0)
		{
			//Create a default clip and attach all the animations to this clip
			PrintInfo("\nAdding default animation clip...");
			CAnimationClip * newAnimClip = CNew(CAnimationClip);
			//CAssert("No memory\n", newAnimClip!=NULL);
			newAnimClip->SetName("defaultClip");
			newAnimClip->SetIndex(0);
			newAnimClip->SetStart(0.0);
			CFloat endTime = 0.0;
			for (CUInt i = 0; i<m_animations.size(); i++)
			{
				CAnimation * anim = m_animations[i];

				PrintInfo("\nAttaching animation ' ", COLOR_WHITE); PrintInfo(anim->GetName(), COLOR_RED_GREEN);
				PrintInfo(" ' to the default animation clip", COLOR_WHITE);

				anim->SetClipTarget(newAnimClip);
				newAnimClip->m_animations.push_back(anim);
				if (anim->GetEndTime() > endTime)
					endTime = anim->GetEndTime();
			}
			newAnimClip->SetEnd((CDouble)endTime);

			m_numClips = 1;
			m_animationClips.push_back(newAnimClip);
		}
	}
	else
	{
		//Create a default clip and attach all the animations to this clip
		PrintInfo("\nAdding new animation clip...");
		CAnimationClip * newAnimClip = CNew(CAnimationClip);
		//CAssert("No memory\n", newAnimClip!=NULL);
		newAnimClip->SetName(clipName);
		newAnimClip->SetIndex(clipIndex);
		newAnimClip->SetStart(0.0);
		CFloat endTime = 0.0;
		for (CUInt i = 0; i< otherScene->m_tempAnimations.size(); i++)
		{
			CAnimation * anim = otherScene->m_tempAnimations[i];

			PrintInfo("\nAttaching animation ' ", COLOR_WHITE); PrintInfo(anim->GetName(), COLOR_RED_GREEN);
			PrintInfo(" ' to the animation clip ' ", COLOR_WHITE); PrintInfo(clipName, COLOR_RED_GREEN);
			PrintInfo(" ' ", COLOR_WHITE);

			anim->SetClipTarget(newAnimClip);
			newAnimClip->m_animations.push_back(anim);
			if (anim->GetEndTime() > endTime)
				endTime = anim->GetEndTime();
		}
		newAnimClip->SetEnd((CDouble)endTime);
		otherScene->m_animationClips.push_back(newAnimClip);
	}
	// Find the scene we want
	daeElement* defaultScene = dom->getScene()->getInstance_visual_scene()->getUrl().getElement();
	domAsset::domUp_axis *up = dom->getAsset()->getUp_axis();

	switch( up->getValue() )
	{
		case UPAXISTYPE_X_UP:
			upAxis = eCXUp;
			break; 
		case UPAXISTYPE_Y_UP:
			upAxis = eCYUp;
			break;
		case UPAXISTYPE_Z_UP:
			upAxis = eCZUp;
			break; 
		default:
			break; 
	}

	if (otherScene)
	{
		//for (CUInt i = 0; i< otherScene->m_tempAnimations.size(); i++)
		//{
		//	CAnimation * anim = otherScene->m_tempAnimations[i];
		//	for (CUInt j = 0; j < anim->m_channels.size(); j++)
		//	{
		//		for (CUInt k = 0; k < otherScene->m_allNodes.size(); k++)
		//		{
		//			CNode* tempNode = otherScene->m_allNodes[k];
		//			if (Cmp(tempNode->GetId(), anim->m_channels[j]->GetTarget()))
		//			{
		//				PrintInfo("\nAttaching animation ' ", COLOR_WHITE); PrintInfo(anim->GetName(), COLOR_RED_GREEN);
		//				PrintInfo(" ' to the node ' ", COLOR_WHITE); PrintInfo(tempNode->GetName(), COLOR_RED_GREEN);
		//				PrintInfo(" '", COLOR_WHITE);

		//				//anim->SetFoundTarget();
		//				tempNode->SetAnimation(anim);
		//				// don't want to break, though there maybe be multiple anim targets 
		//				otherScene->m_numAnimatedNodes++;
		//			}
		//		}
		//		// Update all the child nodes
		//	}
		//}
		if (m_collada)
		{
			delete m_collada;
			m_collada = 0;
		}
		Cpy(g_currentZipFileName, "\n");

		return CTrue;
	}

	if(defaultScene)
		ReadScene( (domVisual_scene *)defaultScene, upAxis );
	
	if (m_collada)
	{
		delete m_collada;
		m_collada = 0;
	}
	if( reportWarningsAndErrors )
	{
		char tempReport[MAX_NAME_SIZE];
		COLORREF color;
		if( numErrors > 0 )
			color = COLOR_RED;
		else if (numWarnings > 0 )
			color = COLOR_YELLOW;
		else
			color = COLOR_GREEN;
		sprintf( tempReport, "\n%s - %i error (s), %i warning (s)", nameOnly, numErrors, numWarnings );

		PrintInfo( tempReport, color );

		totalErrors += numErrors;
		totalWarnings += numWarnings;
	}
	Cpy(g_currentZipFileName, "\n");
	return CTrue;
}

CVoid CScene::Destroy()
{
	NxScene* tempScene = gPhysXscene/*gPhysicsSDK->getScene(i)*/;
	if(tempScene && !g_clickedNew && !g_clickedOpen)
	{
		for( CUInt i = 0; i < m_instanceGeometries.size(); i++ )
		{
			CInstanceGeometry* m_instanceGeo = m_instanceGeometries[i];
			if( tempScene )
			{
				for( CUInt j = 0; j < tempScene->getNbActors(); j++ )
				{
					CChar actorName[MAX_NAME_SIZE];
					if( !tempScene->getActors()[j]->getName() ) continue;
					Cpy( actorName, tempScene->getActors()[j]->getName() );
					if( !Cmp(m_instanceGeo->m_physXName, "\n" ) && Cmp( actorName, m_instanceGeo->m_physXName ) )
					{
						for(CInt nItem =0 ; nItem <  ex_pVandaEngine1Dlg->m_listBoxPhysXElements.GetItemCount(); nItem++)
						{
							CString strText = ex_pVandaEngine1Dlg->m_listBoxPhysXElements.GetItemText(nItem, 0);
							char charPtr[MAX_NAME_SIZE];
							sprintf(charPtr, "%s", strText);
							if(Cmp( m_instanceGeo->m_physXName, charPtr ) )
							{
								ex_pVandaEngine1Dlg->m_listBoxPhysXElements.DeleteItem(nItem);
								ex_pVandaEngine1Dlg->SortPhysXList();
							}
						}

						tempScene->releaseActor( *tempScene->getActors()[j] );
						g_multipleView->m_nx->gControllers->reportSceneChanged();
						m_instanceGeo->m_hasPhysX = CFalse;
						Cpy( m_instanceGeo->m_physXName, "\n" );
					}
				}
			}
		}
	}
	//while(!m_cfxMaterials.empty())
	//{
		//std::map<std::string, cfxMaterial*>::iterator iter = m_cfxMaterials.begin();
		//CDelete(iter->second);
		//m_cfxMaterials.erase(iter);
	//}
	//m_cfxEffects.clear();

	//while(!m_cfxEffects.empty())
	//{
		//std::map<std::string, cfxEffect*>::iterator iter = m_cfxEffects.begin();
		//CDelete(iter->second);
		//m_cfxEffects.erase(iter);
	//}
	//m_cfxEffects.clear();
	//delete all the geometries
	m_animationSceneNames.clear();
	m_textureList.clear(); //save functions
	m_prefabList.clear(); //save functions

	if (g_editorMode == eMODE_PREFAB)
	{
		while (!m_geometries.empty())
		{
			CDelete(m_geometries[0]);
			m_geometries.erase(m_geometries.begin());
		}
		m_geometries.clear();
	}
	m_instanceGeometries.clear();

	//m_instanceControllers.clear();
	while(!m_lightInstances.empty())
	{
		CDelete(m_lightInstances[0]);
		m_lightInstances.erase(m_lightInstances.begin());
	}
	while(!m_lights.empty())
	{
		CDelete( m_lights[0] ); 
		m_lights.erase(m_lights.begin());
	}
	while(!m_cameraInstances.empty())
	{
		for( CUInt size = 0; size < g_importedCameraInstances.size(); size++ )
		{
			//if( Cmp( m_cameraInstances[0]->m_abstractCamera->GetName(), g_importedCameraInstances[size]->m_abstractCamera->GetName() ) )
			if (m_cameraInstances[0] == g_importedCameraInstances[size])
			{
				if( g_render.GetActiveInstanceCamera() == g_importedCameraInstances[size] )
				{
					if (g_multipleView && g_render.GetDefaultInstanceCamera())
					{
						g_render.SetActiveInstanceCamera(g_render.GetDefaultInstanceCamera());
						g_currentCameraType = eCAMERA_DEFAULT_FREE_NO_PHYSX; ex_pVandaEngine1Dlg->m_mainBtnFreeCamera.EnableWindow(FALSE);
						g_multipleView->m_lockInput = CFalse;
					}
					else
					{
						g_render.SetActiveInstanceCamera(NULL);
					}

				}
				g_importedCameraInstances.erase( g_importedCameraInstances.begin() + size );
			}
		}
		CDelete(m_cameraInstances[0]);
		m_cameraInstances.erase(m_cameraInstances.begin());
	}

	while (!g_resourceFiles.empty())
	{
		CDelete(g_resourceFiles[0]);
		g_resourceFiles.erase(g_resourceFiles.begin());
	}

	while(!m_cameras.empty())
	{
		CDelete( m_cameras[0] ); 
		m_cameras.erase(m_cameras.begin());
	}
	while(!m_controllers.empty())
	{
		CDelete( m_controllers[0] );
		m_controllers.erase(m_controllers.begin());
	}
	//Delete all the nodes
	CDelete( m_sceneRoot );
	m_nodes.clear();
	m_allNodes.clear();
	//Clear all the images
	//for( std::vector<CImage*>::iterator it = m_images.begin(); it != m_images.end(); it++ )
	//{
	//	CDelete( *it );
	//}
	//Clear the vector objects
	m_images.clear();

	//clear all the effects
	for( std::vector<CEffect*>::iterator it = m_effects.begin(); it != m_effects.end(); it++ )
	{
		CDelete( *it );
	}
	//Clear the vector objects
	m_effects.clear();

	for( std::vector<CMaterial*>::iterator it = m_materials.begin(); it != m_materials.end(); it++ )
	{
		CDelete( *it );
	}
	//Clear the vector objects
	m_materials.clear();

	for( std::vector<CAnimation*>::iterator it = m_animations.begin(); it != m_animations.end(); it++ )
	{
		CDelete( *it );
	}
	//Clear the vector objects
	m_animations.clear();

	for( std::vector<CAnimationClip*>::iterator it = m_animationClips.begin(); it != m_animationClips.end(); it++ )
	{
		CDelete( *it );
	}
	//Clear the vector objects
	m_animationClips.clear();
}

CVoid CScene::CalculateDistances()
{
	if (g_camera)
	{
		for (CUInt i = 0; i < m_instanceGeometries.size(); i++)
		{
			CFloat x = g_camera->m_perspectiveCameraPos.x - m_instanceGeometries[i]->m_center.x;
			CFloat y = g_camera->m_perspectiveCameraPos.y - m_instanceGeometries[i]->m_center.y;
			CFloat z = g_camera->m_perspectiveCameraPos.z - m_instanceGeometries[i]->m_center.z;

			m_instanceGeometries[i]->m_distanceFromCamera = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)) - m_instanceGeometries[i]->m_radius;
		}
	}
}

CVoid CScene::UpdateDynamicPhysicsObjects()
{
	if (m_sceneRoot)
	{
		m_sceneRoot->UpdateDynamicPhysicsObjects(m_sceneRoot);
	}
}

CVoid CScene::RenderModelsControlledByPhysX(CBool sceneManager)
{
	if ( m_sceneRoot )
	{
		m_sceneRoot->RenderModelsControlledByPhysX(sceneManager, m_sceneRoot); 
	}
}

CVoid CScene::RenderAnimatedModels(CBool sceneManager, CBool renderController)
{
	if ( m_sceneRoot )
	{
		m_sceneRoot->RenderAnimatedModels(sceneManager, m_sceneRoot, renderController);
	}
}

CVoid CScene::ResetSkinData()
{
	if (m_sceneRoot)
	{
		m_sceneRoot->ResetSkinData();
	}
}

CVoid CScene::Render(CBool sceneManager, CChar* parentTreeNameOfGeometries, CBool renderController, CBool checkVisibility, CBool drawGeometry)
{
	if ( m_sceneRoot )
	{
		m_sceneRoot->Render(sceneManager, parentTreeNameOfGeometries, renderController, checkVisibility, drawGeometry);
	}
}

CVoid CScene::RenderAABBWithLines( CBool animatedGeo )
{
	if ( m_sceneRoot )
	{
		m_sceneRoot->RenderAABBWithLines(animatedGeo); 
	}
}

CVoid CScene::RenderAABBWithQuads()
{
	if( m_sceneRoot )
	{
		m_sceneRoot->RenderAABBWithQuads();
	}
}

CVoid CScene::RenderSelectionMode()
{
	if( m_sceneRoot )
	{
		m_sceneRoot->RenderSelectionMode(m_sceneRoot);
	}
}

//Note: if cycle is true, we blend from animation1 to animation2 and continue from the second animation
//Note: if cycle is false, we blend from animation1 to animation2 and after finishing the second animation,
//we blend from  animation2 to animation1, and continue from the first animation
CVoid CScene::Update( CFloat elapsedTime, CBool updateOrient, CBool resetTimer )
{
	g_render.SetScene(this);
	m_sceneRoot->Update( elapsedTime, updateOrient ); 
	UpdateBlendCycleList(elapsedTime, resetTimer );

	CBool updateExecuteActionList = CFalse;
	UpdateExecuteActionList(elapsedTime, updateExecuteActionList);

	if( m_blendCycleList.size() == 0 && !updateExecuteActionList )
		m_updateAnimationLists = CFalse;
}

CVoid CScene::UpdateBlendCycleList(CFloat elapsedTime, CBool resetTimer)
{
	//Blend Cycle List
	for (CUInt i = 0; i < m_blendCycleList.size(); i++)
	{
		CChar blendCycleName[MAX_NAME_SIZE];
		Cpy(blendCycleName, m_blendCycleList[i].c_str());
		CInt clipIndex = 0;
		//Find the animation clip 
		for (CInt ac = 0; ac < GetNumClips(); ac++)
		{
			if (Cmp(m_animationClips[ac]->GetName(), blendCycleName))
			{
				clipIndex = ac;
				break;
			}
		}
		if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_CLEAR_CYCLE && m_animationClips[clipIndex]->GetCurrentWeight() <= EPSILON)
		{
			m_animationClips[clipIndex]->SetAnimationStatus(eANIM_NONE);
			m_blendCycleList.erase(m_blendCycleList.begin() + i);
			continue;
		}

		//make sure that current weight is not greater than target weight
		if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_BLEND_CYCLE && m_animationClips[clipIndex]->GetCurrentWeight() >= m_animationClips[clipIndex]->GetTargetWeight())
		{
			m_animationClips[clipIndex]->SetCurrentWeight(m_animationClips[clipIndex]->GetTargetWeight());
		}
		else
		{
			//compute current delay in or delay out time
			CFloat Dc = 0.0f;
			if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_BLEND_CYCLE)
			{
				m_animationClips[clipIndex]->SetCurrentDelayInTime2(elapsedTime);
				Dc = m_animationClips[clipIndex]->GetCurrentDelayInTime();
			}
			else if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_CLEAR_CYCLE)
			{
				m_animationClips[clipIndex]->SetCurrentDelayOutTime2(elapsedTime);
				Dc = m_animationClips[clipIndex]->GetCurrentDelayOutTime();
			}
			//compute M
			CFloat M = 0.0f;
			if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_BLEND_CYCLE)
				M = (m_animationClips[clipIndex]->GetTargetWeight() - m_animationClips[clipIndex]->GetStartWeight()) / m_animationClips[clipIndex]->GetTargetDelayIn();
			else
				M = (m_animationClips[clipIndex]->GetTargetWeight() - m_animationClips[clipIndex]->GetStartWeight()) / m_animationClips[clipIndex]->GetTargetDelayOut();

			//compute current weight
			CFloat Wc = 0.0f;
			Wc = M * Dc + m_animationClips[clipIndex]->GetStartWeight();
			m_animationClips[clipIndex]->SetCurrentWeight(Wc);

			//make sure that W is not less than or greate than target weight
			if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_BLEND_CYCLE && m_animationClips[clipIndex]->GetCurrentWeight() >= m_animationClips[clipIndex]->GetTargetWeight())
			{
				m_animationClips[clipIndex]->SetCurrentWeight(m_animationClips[clipIndex]->GetTargetWeight());
			}
			else if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_CLEAR_CYCLE && m_animationClips[clipIndex]->GetCurrentWeight() <= EPSILON)
			{
				m_animationClips[clipIndex]->SetCurrentWeight(0.0f);
			}
		}

		if (resetTimer)
		{
			if (m_animationClips[clipIndex]->GetCurrentAnimationTime() > m_animationClips[clipIndex]->GetEnd())
			{
				m_animationClips[clipIndex]->SetCalculateDynamicBoundingBox(CFalse);
				m_animationClips[clipIndex]->SetCurrentTime(m_animationClips[clipIndex]->GetCurrentAnimationTime() - m_animationClips[clipIndex]->GetEnd() + m_animationClips[clipIndex]->GetStart());
			}
		}
		m_animationClips[clipIndex]->SetCurrentTime2(elapsedTime);
	}
}

CVoid CScene::UpdateExecuteActionList(CFloat elapsedTime, CBool &updateExecuteActionList)
{
	//Execute Action List
	if (m_executeActionList.size() == 0)
	{
		updateExecuteActionList = CFalse;
		return;
	}

	for (CUInt i = 0; i < m_executeActionList.size(); i++)
	{
		CChar executeActionName[MAX_NAME_SIZE];
		Cpy(executeActionName, m_executeActionList[i].c_str());
		CInt clipIndex = 0;
		//Find the animation clip 
		for (CInt ac = 0; ac < GetNumClips(); ac++)
		{
			if (Cmp(m_animationClips[ac]->GetName(), executeActionName))
			{
				clipIndex = ac;
				break;
			}
		}

		if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_EXECUTE_ACTION && m_animationClips[clipIndex]->GetCurrentAnimationTime() >= m_animationClips[clipIndex]->GetEnd())
		{
			m_animationClips[clipIndex]->SetCalculateDynamicBoundingBox(CFalse);
		}

		if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_EXECUTE_ACTION && m_animationClips[clipIndex]->GetCurrentAnimationTime() >= m_animationClips[clipIndex]->GetEnd() && !m_animationClips[clipIndex]->GetLock())
		{
			m_animationClips[clipIndex]->SetAnimationStatus(eANIM_NONE);
			m_executeActionList.erase(m_executeActionList.begin() + i);
			continue;
		}
		if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_EXECUTE_ACTION && m_animationClips[clipIndex]->GetStart() >= m_animationClips[clipIndex]->GetCurrentAnimationTime() && m_animationClips[clipIndex]->GetReverse())
		{
			m_animationClips[clipIndex]->SetAnimationStatus(eANIM_NONE);
			m_executeActionList.erase(m_executeActionList.begin() + i);
			continue;
		}

		if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_REMOVE_ACTION)
		{
			m_animationClips[clipIndex]->SetAnimationStatus(eANIM_NONE);
			m_executeActionList.erase(m_executeActionList.begin() + i);
			continue;
		}

		if (!(m_animationClips[clipIndex]->GetCurrentAnimationTime() >= m_animationClips[clipIndex]->GetEnd() && m_animationClips[clipIndex]->GetLock() && !m_animationClips[clipIndex]->GetReverse()))
			updateExecuteActionList = CTrue;

		if (m_animationClips[clipIndex]->GetReverse())
			elapsedTime = -elapsedTime;

		if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_EXECUTE_ACTION && m_animationClips[clipIndex]->GetCurrentAnimationTime() >= (m_animationClips[clipIndex]->GetStart() + m_animationClips[clipIndex]->GetTargetDelayIn()) && m_animationClips[clipIndex]->GetCurrentAnimationTime() <= (m_animationClips[clipIndex]->GetEnd() - m_animationClips[clipIndex]->GetTargetDelayOut()))
		{
			m_animationClips[clipIndex]->SetCurrentWeight(m_animationClips[clipIndex]->GetTargetWeight());
		}
		else if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_EXECUTE_ACTION && m_animationClips[clipIndex]->GetCurrentAnimationTime() < (m_animationClips[clipIndex]->GetStart() + m_animationClips[clipIndex]->GetTargetDelayIn()))
		{
			//compute current delay in or delay out time
			CFloat Dc = 0.0f;
			m_animationClips[clipIndex]->SetCurrentDelayInTime2(elapsedTime);
			Dc = m_animationClips[clipIndex]->GetCurrentDelayInTime();
			//compute M
			CFloat M = 0.0f;
			M = (m_animationClips[clipIndex]->GetTargetWeight() - m_animationClips[clipIndex]->GetStartWeight()) / m_animationClips[clipIndex]->GetTargetDelayIn();

			//compute current weight
			CFloat Wc = 0.0f;
			Wc = M * Dc + m_animationClips[clipIndex]->GetStartWeight();
			m_animationClips[clipIndex]->SetCurrentWeight(Wc);

			if (m_animationClips[clipIndex]->GetCurrentWeight() >= m_animationClips[clipIndex]->GetTargetWeight())
				m_animationClips[clipIndex]->SetCurrentWeight(m_animationClips[clipIndex]->GetTargetWeight());
		}
		else if (m_animationClips[clipIndex]->GetAnimationStatus() == eANIM_EXECUTE_ACTION && m_animationClips[clipIndex]->GetCurrentAnimationTime() > (m_animationClips[clipIndex]->GetEnd() - m_animationClips[clipIndex]->GetTargetDelayOut()))
		{
			//compute current delay in or delay out time
			CFloat Dc = 0.0f;
			m_animationClips[clipIndex]->SetCurrentDelayOutTime2(elapsedTime);
			Dc = m_animationClips[clipIndex]->GetCurrentDelayOutTime();
			//compute M
			CFloat M = 0.0f;
			M = (-m_animationClips[clipIndex]->GetTargetWeight()) / m_animationClips[clipIndex]->GetTargetDelayOut();
			//compute current weight
			CFloat Wc = 0.0f;
			Wc = M * Dc + m_animationClips[clipIndex]->GetTargetWeight();
			m_animationClips[clipIndex]->SetCurrentWeight(Wc);
			if (m_animationClips[clipIndex]->GetCurrentWeight() <= 0.0f)
				m_animationClips[clipIndex]->SetCurrentWeight(0.0f);
		}

		if (m_animationClips[clipIndex]->GetReverse())
		{
			m_animationClips[clipIndex]->SetCurrentTime2(elapsedTime);
			//if( m_animationClips[clipIndex]->GetCurrentAnimationTime() < m_animationClips[clipIndex]->GetStart() )
			//	m_animationClips[clipIndex]->SetCurrentTime( m_animationClips[clipIndex]->GetStart() );
		}
		else
		{
			m_animationClips[clipIndex]->SetCurrentTime2(elapsedTime);
			//if( m_animationClips[clipIndex]->GetCurrentAnimationTime() > m_animationClips[clipIndex]->GetEnd() )
			//	m_animationClips[clipIndex]->SetCurrentTime( m_animationClips[clipIndex]->GetEnd() );
		}
	}
}

CVoid CScene::CreateTrigger( CNovodex* nx )
{
	if( m_sceneRoot )
	{	
		m_sceneRoot->CreateTrigger(nx);
	}
}

CVoid CScene::SetupGlossTexture()
{
	if( m_sceneRoot )
	{	
		m_sceneRoot->SetupGlossTexture();
	}
}


CVoid CScene::SetupDirtTexture()
{
	if( m_sceneRoot )
	{	
		m_sceneRoot->SetupDirtTexture();
	}
}

CVoid CScene::SetupNormalTexture()
{
	if( m_sceneRoot )
	{	
		m_sceneRoot->SetupNormalTexture();
	}
}

CVoid CScene::SetupDiffuseTexture()
{
	if( m_sceneRoot )
	{	
		m_sceneRoot->SetupDiffuseTexture();
	}
}

CInt CScene::Triangulate(DAE * _dae)
{
	CInt error = 0;

	// How many geometry elements are there?
	CInt geometryElementCount = (CInt)(_dae->getDatabase()->getElementCount(NULL, "geometry" ));
//	if(verbose)	cerr<<"There are "<<geometryElementCount<<" geometry elements in this file\n"; 

	for(CInt currentGeometry = 0; currentGeometry < geometryElementCount; currentGeometry++)
	{
		// Find the next geometry element
		domGeometry *thisGeometry;
//		error = _dae->getDatabase()->getElement((daeElement**)&thisGeometry,currentGeometry, NULL, "geometry");
		daeElement * element = 0;
		error = _dae->getDatabase()->getElement(&element,currentGeometry, NULL, "geometry");
		thisGeometry = (domGeometry *) element;

		// Get the mesh out of the geometry
		domMesh *thisMesh = thisGeometry->getMesh();

		if (thisMesh == NULL)
			continue;

		// Loop over all the polygon elements
		for(CInt currentPolygons = 0; currentPolygons < (CInt)(thisMesh->getPolygons_array().getCount()); currentPolygons++)
		{
			// Get the polygons out of the mesh
			// Always get index 0 because every pass through this loop deletes the <polygons> element as it finishes with it
			domPolygons *thisPolygons = thisMesh->getPolygons_array()[currentPolygons];  
			CreateTrianglesFromPolygons( thisMesh, thisPolygons );
			// Remove the polygons from the mesh
//			thisMesh->removeChildElement(thisPolygons);
		}
		while (thisMesh->getPolygons_array().getCount() > 0)
		{
			domPolygons *thisPolygons = thisMesh->getPolygons_array().get(0);  
			// Remove the polygons from the mesh
			thisMesh->removeChildElement(thisPolygons);
		}
		CInt polylistElementCount = (CInt)(thisMesh->getPolylist_array().getCount());
		//if(verbose)	cerr<<"There are "<<polylistElementCount<<" polylist elements in this file\n"; 
		for(CInt currentPolylist = 0; currentPolylist < polylistElementCount; currentPolylist++)
		{
			// Get the polylist out of the mesh
			// Always get index 0 because every pass through this loop deletes the <polygons> element as it finishes with it
			domPolylist *thisPolylist = thisMesh->getPolylist_array()[currentPolylist];  
			CreateTrianglesFromPolylist( thisMesh, thisPolylist );
			// Remove the polylist from the mesh
//			thisMesh->removeChildElement(thisPolylist);
		}
		while (thisMesh->getPolylist_array().getCount() > 0)
		{
			domPolylist *thisPolylist = thisMesh->getPolylist_array().get(0);  
			// Remove the polylist from the mesh
			thisMesh->removeChildElement(thisPolylist);
		}
	}
	return 0;
}

CVoid CScene::CreateTrianglesFromPolylist( domMesh *thisMesh, domPolylist *thisPolylist )
{
	// Create a new <triangles> inside the mesh that has the same material as the <polylist>
	domTriangles *thisTriangles = (domTriangles *)thisMesh->createAndPlace("triangles");
	//thisTriangles->setCount( 0 );
	unsigned CInt triangles = 0;
	thisTriangles->setMaterial(thisPolylist->getMaterial());
	domP* p_triangles = (domP*)thisTriangles->createAndPlace("p");

	// Give the new <triangles> the same <_dae> and <parameters> as the old <polylist>
	for(CInt i=0; i<(CInt)(thisPolylist->getInput_array().getCount()); i++)
	{
		thisTriangles->placeElement( thisPolylist->getInput_array()[i]->clone() );
	}

	// Get the number of inputs and primitives for the polygons array
	CInt numberOfInputs = (CInt)GetMaxOffset(thisPolylist->getInput_array()) + 1;
	CInt numberOfPrimitives = (CInt)(thisPolylist->getVcount()->getValue().getCount());

	unsigned CInt offset = 0;

	// Triangulate all the primitives, this generates all the triangles in a single <p> element
	for(CInt j = 0; j < numberOfPrimitives; j++)
	{	
		CInt triangleCount = (CInt)thisPolylist->getVcount()->getValue()[j] -2;
		// Write out the primitives as triangles, just fan using the first element as the base
		CInt idx = numberOfInputs;
		for(CInt k = 0; k < triangleCount; k++)
		{
			// First vertex
			for(CInt l = 0; l < numberOfInputs; l++)
			{
				p_triangles->getValue().append(thisPolylist->getP()->getValue()[offset + l]);
			}
			// Second vertex
			for(CInt l = 0; l < numberOfInputs; l++)
			{
				p_triangles->getValue().append(thisPolylist->getP()->getValue()[offset + idx + l]);
			}
			// Third vertex
			idx += numberOfInputs;
			for(CInt l = 0; l < numberOfInputs; l++)
			{
				p_triangles->getValue().append(thisPolylist->getP()->getValue()[offset + idx + l]);
			}
			//thisTriangles->setCount(thisTriangles->getCount()+1);
			triangles++;
		}
		offset += (unsigned CInt)thisPolylist->getVcount()->getValue()[j] * numberOfInputs;
	}
	thisTriangles->setCount( triangles );
}


CVoid CScene::CreateTrianglesFromPolygons( domMesh *thisMesh, domPolygons *thisPolygons )
{
	// Create a new <triangles> inside the mesh that has the same material as the <polygons>
	domTriangles *thisTriangles = (domTriangles *)thisMesh->createAndPlace("triangles");
	thisTriangles->setCount( 0 );
	thisTriangles->setMaterial(thisPolygons->getMaterial());
	domP* p_triangles = (domP*)thisTriangles->createAndPlace("p");

	// Give the new <triangles> the same <_dae> and <parameters> as the old <polygons>
	for(CInt i=0; i<(CInt)(thisPolygons->getInput_array().getCount()); i++)
	{
		thisTriangles->placeElement( thisPolygons->getInput_array()[i]->clone() );
	}

	// Get the number of inputs and primitives for the polygons array
	CInt numberOfInputs = (CInt)GetMaxOffset(thisPolygons->getInput_array()) +1;
	CInt numberOfPrimitives = (CInt)(thisPolygons->getP_array().getCount());

	// Triangulate all the primitives, this generates all the triangles in a single <p> element
	for(CInt j = 0; j < numberOfPrimitives; j++)
	{
		// Check the polygons for consistancy (some exported files have had the wrong number of indices)
		domP * thisPrimitive = thisPolygons->getP_array()[j];
		CInt elementCount = (CInt)(thisPrimitive->getValue().getCount());
		if((elementCount%numberOfInputs) != 0)
		{
			//cerr<<"Primitive "<<j<<" has an element count "<<elementCount<<" not divisible by the number of inputs "<<numberOfInputs<<"\n";
		}
		else
		{
			CInt triangleCount = (elementCount/numberOfInputs)-2;
			// Write out the primitives as triangles, just fan using the first element as the base
			CInt idx = numberOfInputs;
			for(CInt k = 0; k < triangleCount; k++)
			{
				// First vertex
				for(CInt l = 0; l < numberOfInputs; l++)
				{
					p_triangles->getValue().append(thisPrimitive->getValue()[l]);
				}
				// Second vertex
				for(CInt l = 0; l < numberOfInputs; l++)
				{
					p_triangles->getValue().append(thisPrimitive->getValue()[idx + l]);
				}
				// Third vertex
				idx += numberOfInputs;
				for(CInt l = 0; l < numberOfInputs; l++)
				{
					p_triangles->getValue().append(thisPrimitive->getValue()[idx + l]);
				}
				thisTriangles->setCount(thisTriangles->getCount()+1);
			}
		}
	}
}

unsigned int CScene::GetMaxOffset( domInputLocalOffset_Array &input_array )
{
	unsigned int maxOffset = 0;
	for ( unsigned int i = 0; i < input_array.getCount(); i++ ) {
		if ( input_array[i]->getOffset() > maxOffset ) {
			maxOffset = (unsigned int)input_array[i]->getOffset();
		}
	}
	return maxOffset;
}

CInt CScene::GetClipIndexForStartup()
{
	return m_clipIndexForStartup;
}
CVoid CScene::SetClipIndexForStartup( CInt index )
{
	m_clipIndexForStartup = index;
}

CVoid CScene::SetCurrentClipIndex(CInt index)
{
	m_currentClipIndex = index;
}

CVoid CScene::SetClipIndex(CInt index, CBool loopAnimation)
{
	CBool setIndex = CTrue;

	if (g_editorMode == eMODE_PREFAB)
		if (g_selectedName == -1)
			setIndex = CFalse;
	if (setIndex)
	{
		if (m_numClips == 0)
			return;
		m_currentClipIndex = index;
		if (g_editorMode == eMODE_PREFAB)
		{
			if (m_currentClipIndex == m_numClips - 1)
				ex_pBtnNextAnim->EnableWindow(FALSE);
			else if (m_numClips > 1)
				ex_pBtnNextAnim->EnableWindow(TRUE);

			if (m_currentClipIndex == 0)
				ex_pBtnPrevAnim->EnableWindow(FALSE);
			else if (m_numClips > 1)
				ex_pBtnPrevAnim->EnableWindow(TRUE);
		}

		if (g_currentInstancePrefab)
			PrintInfo("\nAnimation '" + (CString)g_currentInstancePrefab->GetName() + ":" + (CString)m_animationClips[m_currentClipIndex]->GetName() + "' activated");
		else
			PrintInfo("\nAnimation '" + (CString)g_render.GetScene()->GetName() + ":" + (CString)m_animationClips[m_currentClipIndex]->GetName() + "' activated");
	}
}
CVoid CScene::SetNextAnimation() 
{
	m_currentClipIndex++;
	if( m_currentClipIndex == m_numClips - 1)
		ex_pBtnNextAnim->EnableWindow( FALSE );
	if( m_numClips > 1 )
		ex_pBtnPrevAnim->EnableWindow( TRUE );

	if( m_currentClipIndex == m_numClips)
		m_currentClipIndex = m_numClips - 1;

	for( CInt index = 0; index < m_numClips; index++ )
	{
		if( m_currentClipIndex != index ) 
		{
			ClearCycle( index, 1.0f ); //0.5 second
		}
		else
		{
			BlendCycle( index, 1.0f, 1.0f );
		}
	}

	PrintInfo( "\nAnimation '" + (CString)m_animationClips[m_currentClipIndex]->GetName() + "' activated" );

}
CVoid CScene::SetPrevAnimation() 
{
	if (g_selectedName != -1)
	{
		m_currentClipIndex--;
		if (m_currentClipIndex == 0)
			ex_pBtnPrevAnim->EnableWindow(FALSE);
		if (m_numClips > 1)
			ex_pBtnNextAnim->EnableWindow(TRUE);

		if (m_currentClipIndex < 0)
			m_currentClipIndex = 0;

		for (CInt index = 0; index < m_numClips; index++)
		{
			if (m_currentClipIndex != index)
			{
				ClearCycle(index, 1.0f); //0.5 second
			}
			else
			{
				BlendCycle(index, 1.0f, 1.0f);
			}
		}

		PrintInfo("\nAnimation '" + (CString)m_animationClips[m_currentClipIndex]->GetName() + "' activated");
	}
}

CVoid CScene::SetCurrentClipIndex()
{
	if (g_selectedName != -1)
	{
		if (m_currentClipIndex == m_numClips - 1)
			ex_pBtnNextAnim->EnableWindow(FALSE);
		else if (m_numClips > 1)
			ex_pBtnNextAnim->EnableWindow(TRUE);

		if (m_currentClipIndex == 0)
			ex_pBtnPrevAnim->EnableWindow(FALSE);
		else if (m_numClips > 1)
			ex_pBtnPrevAnim->EnableWindow(TRUE);
	}
}

CInt CScene::GetCurrentClipIndex()
{
	return m_currentClipIndex;
}

CInt CScene::GetNumClips()
{
	return m_numClips;
}

CVoid CScene::SetNumClips(CInt clips)
{
	m_numClips = clips;
}

CBool CScene::BlendCycle(CInt id, CFloat weight, CFloat delay)
{
	if (m_numClips == 0)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "\n%s%s%s", "scene '", GetName(), "' has no animation");
		PrintInfo(temp, COLOR_RED);
		return CFalse;
	}

	if (id > m_numClips - 1 || id < 0)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "\n%s%s%s", "Invalid animation ID for scene '", GetName(), "'");
		PrintInfo(temp, COLOR_RED);
		return CFalse;
	}

	if (weight < EPSILON) return CFalse;
	if (weight > 1.0f) weight = 1.0f;

	if (m_animationClips[id]->GetAnimationStatus() == eANIM_EXECUTE_ACTION)
		return CFalse;

	if (m_animationClips[id]->GetAnimationStatus() != eANIM_BLEND_CYCLE && m_animationClips[id]->GetAnimationStatus() != eANIM_CLEAR_CYCLE)
	{
		m_blendCycleList.push_back(m_animationClips[id]->GetName());
		m_animationClips[id]->SetCurrentDelayInTime(0.0f);
		m_animationClips[id]->SetCurrentDelayOutTime(0.0f);
	}
	else if (m_animationClips[id]->GetAnimationStatus() == eANIM_CLEAR_CYCLE)
	{
		m_animationClips[id]->SetCurrentDelayInTime(0.0f);
		m_animationClips[id]->SetCurrentDelayOutTime(0.0f);
	}

	m_animationClips[id]->SetTargetDelayIn( delay );
	m_animationClips[id]->SetTargetDelayOut( 0.0f );
	if( m_animationClips[id]->GetAnimationStatus() != eANIM_BLEND_CYCLE && m_animationClips[id]->GetAnimationStatus() != eANIM_CLEAR_CYCLE)
		m_animationClips[id]->SetCurrentTime( m_animationClips[id]->GetStart() );
	m_animationClips[id]->SetTargetWeight( weight );
	m_animationClips[id]->SetStartWeight( m_animationClips[id]->GetCurrentWeight() );
	m_animationClips[id]->SetAnimationStatus( eANIM_BLEND_CYCLE );
	m_updateAnimationLists = CTrue;

	return CTrue;
}

CBool CScene::ClearCycle(CInt id, CFloat delay)
{
	if( m_numClips == 0 )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "scene '", GetName(), "' has no animation" );
		PrintInfo( temp, COLOR_RED );
		return CFalse;
	}

	if( id > m_numClips - 1 || id < 0 )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Invalid animation ID for scene '", GetName(), "'" );
		PrintInfo( temp, COLOR_RED );
		return CFalse;
	}

	if (m_animationClips[id]->GetAnimationStatus() == eANIM_NONE)
		return CFalse;

	if( m_animationClips[id]->GetAnimationStatus() != eANIM_BLEND_CYCLE || m_animationClips[id]->GetAnimationStatus() == eANIM_EXECUTE_ACTION)
		return CFalse;

	if (m_animationClips[id]->GetAnimationStatus() != eANIM_BLEND_CYCLE && m_animationClips[id]->GetAnimationStatus() != eANIM_CLEAR_CYCLE)
	{
		m_blendCycleList.push_back(m_animationClips[id]->GetName());
		m_animationClips[id]->SetCurrentDelayInTime(0.0f);
		m_animationClips[id]->SetCurrentDelayOutTime(0.0f);
	}
	else if (m_animationClips[id]->GetAnimationStatus() == eANIM_BLEND_CYCLE)
	{
		m_animationClips[id]->SetCurrentDelayInTime(0.0f);
		m_animationClips[id]->SetCurrentDelayOutTime(0.0f);
	}

	m_animationClips[id]->SetTargetDelayIn( 0.0f );
	m_animationClips[id]->SetTargetDelayOut( delay );
	m_animationClips[id]->SetTargetWeight( 0.0f );
	m_animationClips[id]->SetStartWeight( m_animationClips[id]->GetCurrentWeight() );
	m_animationClips[id]->SetAnimationStatus( eANIM_CLEAR_CYCLE );
	m_updateAnimationLists = CTrue;

	return CTrue;
}

CBool CScene::ExecuteAction(CInt id, CFloat delayIn, CFloat delayOut, CFloat weight, CBool LockToLastFrame)
{
	if( m_numClips == 0 )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "scene '", GetName(), "' has no animation" );
		PrintInfo( temp, COLOR_RED );
		return CFalse;
	}

	if( id > m_numClips - 1 || id < 0 )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Invalid animation ID for scene '", GetName(), "'" );
		PrintInfo( temp, COLOR_RED );
		return CFalse;
	}

	if( weight < EPSILON ) return CFalse;
	if( weight > 1.0f ) weight = 1.0f;

	if( delayIn + delayOut  > m_animationClips[id]->GetDuration() )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s%s%s", "scene ' ", GetName(), " ': delayIn + delayOut values are greater than duration of animation ' ", m_animationClips[id]->GetName(), " '" );
		PrintInfo( temp, COLOR_RED );
		return CFalse;
	}

	if( m_animationClips[id]->GetAnimationStatus() == eANIM_EXECUTE_ACTION && m_animationClips[id]->GetReverse() )
	{
		m_animationClips[id]->SetReverse(CFalse);
		return CTrue;
	}
	if( m_animationClips[id]->GetAnimationStatus() == eANIM_BLEND_CYCLE || m_animationClips[id]->GetAnimationStatus() == eANIM_CLEAR_CYCLE || m_animationClips[id]->GetAnimationStatus() == eANIM_EXECUTE_ACTION)
		return CFalse;

	if (m_animationClips[id]->GetAnimationStatus() != eANIM_EXECUTE_ACTION)
	{
		m_executeActionList.push_back(m_animationClips[id]->GetName());
		m_animationClips[id]->SetCurrentDelayInTime(0.0f);
		m_animationClips[id]->SetCurrentDelayOutTime(0.0f);
		m_animationClips[id]->SetCurrentTime(m_animationClips[id]->GetStart());
	}

	m_animationClips[id]->SetTargetDelayIn( delayIn );
	m_animationClips[id]->SetTargetDelayOut( delayOut );
	m_animationClips[id]->SetTargetWeight( weight );
	m_animationClips[id]->SetStartWeight( 0.0f );
	m_animationClips[id]->SetAnimationStatus( eANIM_EXECUTE_ACTION );
	m_animationClips[id]->SetLock( LockToLastFrame );
	m_animationClips[id]->SetReverse(CFalse);
	m_updateAnimationLists = CTrue;
	return CTrue;
}

CBool CScene::ReverseExecuteAction(CInt id )
{
	if( m_numClips == 0 )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "scene '", GetName(), "' has no animation" );
		PrintInfo( temp, COLOR_RED );
		return CFalse;
	}

	if( id > m_numClips - 1 || id < 0 )
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf( temp, "\n%s%s%s", "Invalid animation ID for scene '", GetName(), "'" );
		PrintInfo( temp, COLOR_RED );
		return CFalse;
	}

	if( m_animationClips[id]->GetAnimationStatus() == eANIM_BLEND_CYCLE || m_animationClips[id]->GetAnimationStatus() == eANIM_CLEAR_CYCLE )
		return CFalse;

	if( m_animationClips[id]->GetAnimationStatus() != eANIM_EXECUTE_ACTION )
		return CFalse;

	if( m_animationClips[id]->GetReverse() )
		return CFalse;

	m_animationClips[id]->SetReverse(CTrue);
	m_updateAnimationLists = CTrue;
	return CTrue;
}

CBool CScene::RemoveAction(CInt id)
{
	if (m_numClips == 0)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "\n%s%s%s", "scene '", GetName(), "' has no animation");
		PrintInfo(temp, COLOR_RED);
		return CFalse;
	}

	if (id > m_numClips - 1 || id < 0)
	{
		CChar temp[MAX_NAME_SIZE];
		sprintf(temp, "\n%s%s%s", "Invalid animation ID for scene '", GetName(), "'");
		PrintInfo(temp, COLOR_RED);
		return CFalse;
	}

	if (m_animationClips[id]->GetAnimationStatus() == eANIM_NONE)
		return CFalse;

	if (m_animationClips[id]->GetAnimationStatus() == eANIM_BLEND_CYCLE || m_animationClips[id]->GetAnimationStatus() == eANIM_CLEAR_CYCLE)
		return CFalse;

	if (m_animationClips[id]->GetAnimationStatus() != eANIM_EXECUTE_ACTION)
		return CFalse;

	m_animationClips[id]->SetAnimationStatus(eANIM_REMOVE_ACTION);
	m_animationClips[id]->SetTargetWeight(0.0f);
	m_animationClips[id]->SetStartWeight(0.0f);
	m_animationClips[id]->SetCurrentWeight(0.0f);

	m_updateAnimationLists = CTrue;
	return CTrue;
}

CInt CScene::GeneratePhysX(CPhysXAlgorithm algorithm, CFloat density, CInt percentage, CBool isTrigger, CBool isInvisible, CInstanceGeometry* m_instanceGeo, CBool loadFromFile, CInstancePrefab* prefab)
{
	CGeometry* m_geo = m_instanceGeo->m_abstractGeometry;

	if (m_geo->m_physx_points.size() == 0)
	{
		CUInt initialVertexCount = 0;
		CUInt totalVertexCount = 0;
		//DeIndex Mesh
		for (CUInt groupCount = 0; groupCount < m_geo->m_groups.size(); groupCount++)
		{
			CPolyGroup* triangle = m_geo->m_groups[groupCount];
			totalVertexCount += m_geo->m_groups[groupCount]->m_count * 3;
			if (groupCount != 0)
				initialVertexCount += m_geo->m_groups[groupCount - 1]->m_count * 3;

			DeindexMesh(initialVertexCount, totalVertexCount, m_geo, triangle);
		}
	}
	if (!loadFromFile)
	{
		if (m_instanceGeo->m_abstractGeometry->m_collapseMap.num == 0 && (algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH))
		{
			PrintInfo("\nCalculating LOD...");
			m_instanceGeo->m_abstractGeometry->CalculateLODInfo(algorithm);
		}
		else
		{
			if ((algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH) && (m_instanceGeo->m_prevLodAlgorithm == eLOD_LENGTH_CURVATURE ||
				m_instanceGeo->m_prevLodAlgorithm == eLOD_LENGTH))
			{
				if (m_instanceGeo->m_prevLodAlgorithm != algorithm) //regenerate PhysX informations
				{
					PrintInfo("\nRegenerating LOD...");
					m_instanceGeo->m_abstractGeometry->CalculateLODInfo(algorithm);
				}

			}

		}
	}
	//Generate PhysX mesh////////////////
	std::vector<CFloat> vertices_temp;
	std::vector<CInt> triangles_temp;
	CInt num_verts;
	if (algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH)
	{
		num_verts = CInt(CFloat(m_geo->m_physx_points.size()) * (CFloat)((CFloat)percentage / 100.0f));
		if (num_verts < 3) num_verts = 3;
		m_geo->RegenerateIndex(num_verts, triangles_temp);
	}
	else
	{
		num_verts = CInt(m_geo->m_physx_points.size());
	}
	//Scale and Rotation and Translation Matrices for Convex Hulls
	CMatrix ZUpRotationForSkins;
	CMatrixLoadIdentity(ZUpRotationForSkins);

	CNode* tempParentNode = m_instanceGeo->m_node;
	CBool foundTarget = CFalse;

	CMatrix convexLocalToWorld;
	const CMatrix *convex_ltow;
	if (prefab)
		convex_ltow = prefab->GetInstanceMatrix();
	else
		convex_ltow = m_instanceGeo->m_node->GetLocalToWorldMatrix();
	CMatrixCopy(*convex_ltow, convexLocalToWorld);
	CMatrix4x4Mult(convexLocalToWorld, ZUpRotationForSkins);
	CMatrixCopy(ZUpRotationForSkins, convexLocalToWorld);

	//decomp_affine;
	AffineParts *parts = CNew(AffineParts);
	HMatrix A;
	CUInt k = 0;
	for (CUInt i = 0; i < 4; i++)
		for (CUInt j = 0; j < 4; j++)
		{
			A[j][i] = convexLocalToWorld[k];
			k++;
		}
	decomp_affine(A, parts);
	//rotation
	CMatrix convexRotationMatrix;
	CQuat convexQRotation(parts->q.x, parts->q.y, parts->q.z, parts->q.w);
	CMatrixLoadIdentity(convexRotationMatrix);
	CQuaternionToMatrix(&convexQRotation, convexRotationMatrix);

	//////////////////////////SHEARING//////////////////////////////
	CMatrix finalRS;
	CMatrixLoadIdentity(finalRS);
	//rotation scale
	CMatrix convexRotationScaleMatrix;
	CQuat convexQRotationScale(parts->u.x, parts->u.y, parts->u.z, parts->u.w);
	CMatrixLoadIdentity(convexRotationScaleMatrix);
	CQuaternionToMatrix(&convexQRotationScale, convexRotationScaleMatrix);
	//transpose of rotation scale
	CMatrix tConvexRotationScaleMatrix;
	CMatrixLoadIdentity(tConvexRotationScaleMatrix);
	CMatrixTranspose(convexRotationScaleMatrix, tConvexRotationScaleMatrix);
	//scale factor
	CMatrix convexScaleMatrix;
	CVec4f convexScaleFactor(parts->f * parts->k.x, parts->f * parts->k.y, parts->f * parts->k.z, parts->f * parts->k.w);
	CMatrixLoadIdentity(convexScaleMatrix);
	CMatrix4x4Scale(convexScaleMatrix, convexScaleFactor);

	//Compute UK(Ut) for possible shearing
	CMatrix4x4Mult(convexRotationScaleMatrix, finalRS);
	CMatrix4x4Mult(convexScaleMatrix, finalRS);
	CMatrix4x4Mult(tConvexRotationScaleMatrix, finalRS);
	///////////////////////////END OF SHEARING//////////////////////

	CDelete(parts);

	CVec3f convexPosition(convexLocalToWorld[12], convexLocalToWorld[13], convexLocalToWorld[14]);

	NxVec3 NxConvexRow0(convexRotationMatrix[0], convexRotationMatrix[4], convexRotationMatrix[8]);
	NxVec3 NxConvexRow1(convexRotationMatrix[1], convexRotationMatrix[5], convexRotationMatrix[9]);
	NxVec3 NxConvexRow2(convexRotationMatrix[2], convexRotationMatrix[6], convexRotationMatrix[10]);
	NxMat33 NxConvexMat33Rotation(NxConvexRow0, NxConvexRow1, NxConvexRow2);
	////////////////
	CMatrix PhysXMatrix;
	CMatrixLoadIdentity(PhysXMatrix);
	tempParentNode = m_instanceGeo->m_node;
	foundTarget = CFalse;
	for (CUInt i = 0; i < 16; i++)
	{
		PhysXMatrix[i] = m_instanceGeo->m_localToWorldMatrix[i];
	}
	for (CUInt i = 0; i < m_geo->m_physx_points.size(); i++)
	{
		CVec3f v = *(m_geo->m_physx_points[i]);

		if (algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH)
		{
			CVec3f tv = *(m_geo->m_physx_points[i]);
			CMatrixTransform(PhysXMatrix, v, tv);
			vertices_temp.push_back(tv.x);
			vertices_temp.push_back(tv.y);
			vertices_temp.push_back(tv.z);
		}
		else
		{
			CVec3f tv = *(m_geo->m_physx_points[i]);
			CMatrixTransform(finalRS, v, tv);

			vertices_temp.push_back(tv.x);
			vertices_temp.push_back(tv.y);
			vertices_temp.push_back(tv.z);
		}
	}
	CFloat* vertices = NULL;
	CInt* triangles = NULL;
	if (vertices_temp.size() > 0)
		vertices = &vertices_temp[0];
	if (triangles_temp.size() > 0)
		triangles = &triangles_temp[0];
	CBool failed = CFalse;
	if (vertices != NULL && triangles != NULL && (algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH))
	{
		if (!g_multipleView->m_nx->CreateTriangleMesh((CInt)(vertices_temp.size() / 3), (CInt)(triangles_temp.size() / 3), vertices, triangles, isTrigger, m_instanceGeo->m_physXName))
			failed = CTrue;
		else if (g_editorMode == eMODE_PREFAB)
			sprintf(m_instanceGeo->m_physXName, "%s%d", "PhysX_mesh_", m_instanceGeo->m_nameIndex);
		else if (g_editorMode == eMODE_VSCENE)
			sprintf(m_instanceGeo->m_physXName, "%s%s%d", g_currentInstancePrefab->GetName(), "_PhysX_mesh_", m_instanceGeo->m_nameIndex);

	}
	else if (vertices != NULL && algorithm == eLOD_CONVEX_HULL)
	{
		if (!g_multipleView->m_nx->CreateConvexMesh((CInt)(vertices_temp.size() / 3), vertices, NxVec3(convexPosition.x, convexPosition.y, convexPosition.z), NxConvexMat33Rotation, density, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation))
			failed = CTrue;
		else if (g_editorMode == eMODE_PREFAB)
			sprintf(m_instanceGeo->m_physXName, "%s%d", "PhysX_mesh_", m_instanceGeo->m_nameIndex);
		else if (g_editorMode == eMODE_VSCENE)
			sprintf(m_instanceGeo->m_physXName, "%s%s%d", g_currentInstancePrefab->GetName(), "_PhysX_mesh_", m_instanceGeo->m_nameIndex);
	}
	////////////////////////////////////////
	if (algorithm == eLOD_LENGTH_CURVATURE || algorithm == eLOD_LENGTH || algorithm == eLOD_CONVEX_HULL)
	{
		vertices_temp.clear();
		triangles_temp.clear();
		vertices = NULL;
		triangles = NULL;

		if (!failed)
		{
			m_instanceGeo->m_lodAlgorithm = algorithm;
			if (algorithm != eLOD_CONVEX_HULL)
				m_instanceGeo->m_prevLodAlgorithm = algorithm;
			m_instanceGeo->m_hasPhysX = CTrue;
			m_instanceGeo->m_physXDensity = density;
			m_instanceGeo->m_physXPercentage = percentage;
			m_instanceGeo->m_isTrigger = isTrigger;
			m_instanceGeo->m_isInvisible = isInvisible;

			return m_instanceGeo->m_nameIndex;
		}
		else
			return -1;
	}
	else if (algorithm == eLOD_BOX || algorithm == eLOD_TRIGGER)
	{
		CFloat DimX, DimY, DimZ;
		CFloat PosX, PosY, PosZ;
		PosX = (m_instanceGeo->m_maxLocalToWorldAABB.x + m_instanceGeo->m_minLocalToWorldAABB.x) / 2.f;
		PosY = (m_instanceGeo->m_maxLocalToWorldAABB.y + m_instanceGeo->m_minLocalToWorldAABB.y) / 2.f;
		PosZ = (m_instanceGeo->m_maxLocalToWorldAABB.z + m_instanceGeo->m_minLocalToWorldAABB.z) / 2.f;

		//scale: For all of vertexes of original mesh, multiply the SR matrix by each vertex and find the bouding box
		CVec3f m_minAABB;
		CVec3f m_maxAABB;
		m_minAABB.x = m_minAABB.y = m_minAABB.z = 100000000.0f;
		m_maxAABB.x = m_maxAABB.y = m_maxAABB.z = -100000000.0f;

		for (CUInt i = 0; i < vertices_temp.size() / 3; i++)
		{
			if (vertices_temp[i * 3] > m_maxAABB.x)
				m_maxAABB.x = vertices_temp[i * 3];
			if (vertices_temp[(i * 3) + 1] > m_maxAABB.y)
				m_maxAABB.y = vertices_temp[(i * 3) + 1];
			if (vertices_temp[(i * 3) + 2]  > m_maxAABB.z)
				m_maxAABB.z = vertices_temp[(i * 3) + 2];

			if (vertices_temp[i * 3] < m_minAABB.x)
				m_minAABB.x = vertices_temp[i * 3];
			if (vertices_temp[(i * 3) + 1] < m_minAABB.y)
				m_minAABB.y = vertices_temp[(i * 3) + 1];
			if (vertices_temp[(i * 3) + 2]  < m_minAABB.z)
				m_minAABB.z = vertices_temp[(i * 3) + 2];
		}


		CVec3f min(m_minAABB.x, m_minAABB.y, m_minAABB.z);
		CVec3f max(m_maxAABB.x, m_maxAABB.y, m_maxAABB.z);

		DimX = fabs(max.x - min.x) / 2.f;
		DimY = fabs(max.y - min.y) / 2.f;
		DimZ = fabs(max.z - min.z) / 2.f;
		////////////////
		if (algorithm == eLOD_BOX)
			g_multipleView->m_nx->CreateBox(NxVec3(PosX, PosY, PosZ), NxVec3(DimX, DimY, DimZ), density, NxConvexMat33Rotation, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation);
		else
			g_multipleView->m_nx->CreateTriggerBox(NxVec3(PosX, PosY, PosZ), NxVec3(DimX, DimY, DimZ), NxConvexMat33Rotation, m_instanceGeo->m_physXName, m_instanceGeo->m_abstractGeometry->m_hasAnimation);
		if (g_editorMode == eMODE_PREFAB)
			sprintf(m_instanceGeo->m_physXName, "%s%d", "PhysX_mesh_", m_instanceGeo->m_nameIndex);
		else if (g_editorMode == eMODE_VSCENE)
			sprintf(m_instanceGeo->m_physXName, "%s%s%d", g_currentInstancePrefab->GetName(), "_PhysX_mesh_", m_instanceGeo->m_nameIndex);
		m_instanceGeo->m_lodAlgorithm = algorithm;
		m_instanceGeo->m_hasPhysX = CTrue;
		m_instanceGeo->m_physXDensity = density;
		m_instanceGeo->m_physXPercentage = percentage;
		m_instanceGeo->m_isTrigger = isTrigger;
		m_instanceGeo->m_isInvisible = isInvisible;

		vertices_temp.clear();
		triangles_temp.clear();
		vertices = NULL;
		triangles = NULL;

		return m_instanceGeo->m_nameIndex;
	}
	else if (algorithm == eLOD_SPHERE)
	{
		CFloat PosX, PosY, PosZ;
		PosX = (m_instanceGeo->m_maxLocalToWorldAABB.x + m_instanceGeo->m_minLocalToWorldAABB.x) / 2.f;
		PosY = (m_instanceGeo->m_maxLocalToWorldAABB.y + m_instanceGeo->m_minLocalToWorldAABB.y) / 2.f;
		PosZ = (m_instanceGeo->m_maxLocalToWorldAABB.z + m_instanceGeo->m_minLocalToWorldAABB.z) / 2.f;

		CFloat radius = 0.0f;
		for (CUInt i = 0; i < vertices_temp.size() / 3; i++)
		{
			CVec3f cPos(0, 0, 0);
			CVec3f vPos;
			vPos.x = vertices_temp[i * 3]; vPos.y = vertices_temp[(i * 3) + 1]; vPos.z = vertices_temp[(i * 3) + 2];
			CFloat length = (vPos - cPos).Size();
			if (radius < length)
				radius = length;
		}
		g_multipleView->m_nx->CreateSphere(NxVec3(PosX, PosY, PosZ), radius, density, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation);
		if (g_editorMode == eMODE_PREFAB)
			sprintf(m_instanceGeo->m_physXName, "%s%d", "PhysX_mesh_", m_instanceGeo->m_nameIndex);
		else if (g_editorMode == eMODE_VSCENE)
			sprintf(m_instanceGeo->m_physXName, "%s%s%d", g_currentInstancePrefab->GetName(), "_PhysX_mesh_", m_instanceGeo->m_nameIndex);
		m_instanceGeo->m_lodAlgorithm = algorithm;
		m_instanceGeo->m_hasPhysX = CTrue;
		m_instanceGeo->m_physXDensity = density;
		m_instanceGeo->m_physXPercentage = percentage;
		m_instanceGeo->m_isTrigger = isTrigger;
		m_instanceGeo->m_isInvisible = isInvisible;

		vertices_temp.clear();
		triangles_temp.clear();
		vertices = NULL;
		triangles = NULL;

		return m_instanceGeo->m_nameIndex;
	}
	else if (algorithm == eLOD_CAPSULE_METHOD1 || algorithm == eLOD_CAPSULE_METHOD2 || algorithm == eLOD_CAPSULE_METHOD3)
	{
		//For all of vertexes of original mesh, find the bouding box
		CVec3f m_minAABB;
		CVec3f m_maxAABB;
		m_minAABB.x = m_minAABB.y = m_minAABB.z = 100000000.0f;
		m_maxAABB.x = m_maxAABB.y = m_maxAABB.z = -100000000.0f;

		for (CUInt i = 0; i < vertices_temp.size() / 3; i++)
		{
			if (vertices_temp[i * 3] > m_maxAABB.x)
				m_maxAABB.x = vertices_temp[i * 3];
			if (vertices_temp[(i * 3) + 1] > m_maxAABB.y)
				m_maxAABB.y = vertices_temp[(i * 3) + 1];
			if (vertices_temp[(i * 3) + 2]  > m_maxAABB.z)
				m_maxAABB.z = vertices_temp[(i * 3) + 2];

			if (vertices_temp[i * 3] < m_minAABB.x)
				m_minAABB.x = vertices_temp[i * 3];
			if (vertices_temp[(i * 3) + 1] < m_minAABB.y)
				m_minAABB.y = vertices_temp[(i * 3) + 1];
			if (vertices_temp[(i * 3) + 2]  < m_minAABB.z)
				m_minAABB.z = vertices_temp[(i * 3) + 2];
		}


		CFloat radius, height, PosX, PosY, PosZ;
		if (algorithm == eLOD_CAPSULE_METHOD1)
		{
			CVec4f rot(1.0, .0, 0.0, 90.0);
			CMatrix4x4RotateAngleAxis(convexRotationMatrix, rot);

			radius = fabs(m_maxAABB.x - m_minAABB.x) / 2.f;
			if (radius < fabs(m_maxAABB.y - m_minAABB.y) / 2.f)
				radius = fabs(m_maxAABB.y - m_minAABB.y) / 2.f;

			height = fabs(fabs(m_maxAABB.z - m_minAABB.z) - radius);
		}
		else if (algorithm == eLOD_CAPSULE_METHOD2)//second method
		{
			radius = fabs(m_maxAABB.x - m_minAABB.x) / 2.f;
			if (radius < fabs(m_maxAABB.z - m_minAABB.z) / 2.f)
				radius = fabs(m_maxAABB.z - m_minAABB.z) / 2.f;

			height = fabs(fabs(m_maxAABB.y - m_minAABB.y) - radius);
		}
		else if (algorithm == eLOD_CAPSULE_METHOD3)//second method
		{
			CVec4f rot(0.0, 0.0, 1.0, 90.0);
			CMatrix4x4RotateAngleAxis(convexRotationMatrix, rot);

			radius = fabs(m_maxAABB.y - m_minAABB.y) / 2.f;
			if (radius < fabs(m_maxAABB.z - m_minAABB.z) / 2.f)
				radius = fabs(m_maxAABB.z - m_minAABB.z) / 2.f;

			height = fabs(fabs(m_maxAABB.x - m_minAABB.x) - radius);
		}
		NxVec3 NxCapsuleRow0(convexRotationMatrix[0], convexRotationMatrix[4], convexRotationMatrix[8]);
		NxVec3 NxCapsuleRow1(convexRotationMatrix[1], convexRotationMatrix[5], convexRotationMatrix[9]);
		NxVec3 NxCapsuleRow2(convexRotationMatrix[2], convexRotationMatrix[6], convexRotationMatrix[10]);
		NxMat33 NxCapsuleMat33Rotation(NxCapsuleRow0, NxCapsuleRow1, NxCapsuleRow2);

		PosX = (m_instanceGeo->m_maxLocalToWorldAABB.x + m_instanceGeo->m_minLocalToWorldAABB.x) / 2.f;
		PosY = (m_instanceGeo->m_maxLocalToWorldAABB.y + m_instanceGeo->m_minLocalToWorldAABB.y) / 2.f;
		PosZ = (m_instanceGeo->m_maxLocalToWorldAABB.z + m_instanceGeo->m_minLocalToWorldAABB.z) / 2.f;

		g_multipleView->m_nx->CreateCapsule(NxVec3(PosX, PosY, PosZ), height, radius, density, NxCapsuleMat33Rotation, m_instanceGeo->m_physXName, isTrigger, m_instanceGeo->m_abstractGeometry->m_hasAnimation);
		if (g_editorMode == eMODE_PREFAB)
			sprintf(m_instanceGeo->m_physXName, "%s%d", "PhysX_mesh_", m_instanceGeo->m_nameIndex);
		else if (g_editorMode == eMODE_VSCENE)
			sprintf(m_instanceGeo->m_physXName, "%s%s%d", g_currentInstancePrefab->GetName(), "_PhysX_mesh_", m_instanceGeo->m_nameIndex);
		m_instanceGeo->m_lodAlgorithm = algorithm;
		m_instanceGeo->m_hasPhysX = CTrue;
		m_instanceGeo->m_physXDensity = density;
		m_instanceGeo->m_physXPercentage = percentage;
		m_instanceGeo->m_isTrigger = isTrigger;
		m_instanceGeo->m_isInvisible = isInvisible;

		vertices_temp.clear();
		triangles_temp.clear();
		vertices = NULL;
		triangles = NULL;

		return m_instanceGeo->m_nameIndex;
	}
	vertices_temp.clear();
	triangles_temp.clear();
	vertices = NULL;
	triangles = NULL;

	return -1;
}
