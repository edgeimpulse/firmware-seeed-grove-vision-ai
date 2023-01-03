
@echo off 
:mm
	cls

	set backpoint=NULL
	set backpoint=mm_1
	call :Usage_print
:mm_1
  
	Set _File=setting.txt
	Set /a _Lines=0
	For /f %%j in ('Find "" /v /c ^< %_File%') Do Set /a _Lines=%%j
	Echo Load %_File% Success - %_Lines% lines.
 

	set /a var=1
	set/p var=EnterVar:
	rem echo %var%
  rem call :file_read
  
	if %var% EQU 1 (
	echo exit
	pause
	exit 
	)
  
	if %var% LEQ %_Lines% (
	call :file_read
	echo Finish~~
	pause
	goto mm
	)
	
	if %var% gtr %_Lines% (
		set n_chip=NULL
		set n_version=NULL
		set n_partnumber=NULL
		set n_config=NULL
		set n_sec_mode=NULL
		
		echo ADD NEW ITEM
		echo Please input chip name

		set/p n_chip=chip_name:
		rem echo %n_chip%
		@if not exist input\!n_chip! (
			echo The folder %n_chip% not exist , please check
			echo check path : input\!n_chip!
			pause
			goto mm
			)
			
		echo Please input version_name
		set/p n_version=version_name:
		rem echo %n_version%
		@if not exist input\!n_chip!\!n_version! (
			echo The folder %n_version% not exist , please check
			echo check path : input\!n_chip!\!n_version!
			pause
			goto mm
			)	
			
		echo Please input partnumber_name
		set/p n_partnumber=partnumber_name:
		rem echo %n_partnumber%
		@if not exist input\!n_chip!\!n_version!\!n_partnumber! (
			echo The folder %n_partnumber% not exist , please check
			echo check path : input\!n_chip!\!n_version!\!n_partnumber!
			pause
			goto mm
			)	
			
		echo Please input config_name
		set/p n_config=config_name:
		rem echo %n_config%
		@if not exist input\!n_chip!\!n_version!\!n_partnumber!\!n_config! (
			echo The folder %n_config% not exist , please check
			echo check path : input\!n_chip!\!n_version!\!n_partnumber!\!n_config!
			pause
			goto mm
			)	
			
		echo Please input sec_mode_name
		set/p n_sec_mode=sec_mode_name:
		rem echo %n_sec_mode%
		@if not exist input\!n_chip!\!n_version!\!n_partnumber!\!n_config!\!n_sec_mode! (
			echo The folder %n_sec_mode% not exist , please check
			echo check path : input\!n_chip!\!n_version!\!n_partnumber!\!n_config!\!n_sec_mode!
			pause
			goto mm
			)		
			
		@echo !n_chip! !n_version! !n_partnumber! !n_config! !n_sec_mode! >> setting.txt

		echo Add Success ~ ~

		pause
		goto mm
	)

	
	
	pause
	
	goto mm



:Usage_print
	echo ##########################################################
	echo Please choice one
	SETLOCAL EnableDelayedExpansion
	set /a total=1
  rem echo %cd%
	for /f "usebackq delims=" %%a in (setting.txt) do ( 
	    set "var=%%a"   
	    set "var=!var:*:=!"
	    echo !total!. !var!
	    set /a total += 1	    
	)
	echo !total!. None, Create new list(DOTO NOT Finish yet)
	set /a total += 1
	
	ENDLOCAL
	echo ##########################################################
	goto %backpoint%
	
:file_read

  set /a index = %var% -1
	for /f "skip=%index% delims=" %%a in (setting.txt) do (
		setlocal enabledelayedexpansion
	  for /f "tokens=1,2,3 delims= " %%i in ("%%a") do ( 
	  rem echo %%a
		
		set chip=%%i
		set partnumber=%%j
		set sec_mode=%%k
		
		rem echo !chip!
		rem echo !partnumber!
		rem echo !sec_mode!
		
		CD input
		
		if !sec_mode! == BLw (
			COPY !sec_mode!\!chip!\!partnumber!\*.* *.*
			if errorlevel 1 (
			 echo copy loader files fail , please check the loader files exist
			 echo copy path : !sec_mode!\!chip!\!partnumber!
			 CD..
			 pause
			 goto mm
			)
	    CD ..\odm_key
			COPY !chip!_!sec_mode!\!partnumber!\*.* *.*
			if errorlevel 1 (
			 echo copy odm key fail , please check the odm keys exist
			 echo copy path : !chip!\!partnumber!
			 CD..
			 pause
			 goto mm
			)		
		)

		if !sec_mode! == BLp (
			COPY !sec_mode!\!chip!\!partnumber!\*.* *.*
			if errorlevel 1 (
			 echo copy loader files fail , please check the loader files exist
			 echo copy path : !chip!\!versoin!\!partnumber!\!config!\!sec_mode!
			 CD..
			 pause
			 goto mm
			)
	    CD ..\odm_key
			COPY !chip!_!sec_mode!\!partnumber!\*.* *.*
			if errorlevel 1 (
			 echo copy odm key fail , please check the odm keys exist
			 echo copy path : !chip!\!versoin!\!partnumber!
			 CD..
			 pause
			 goto mm
			)		
		)		

             		
		CD ..
		COPY image_gen_config_!sec_mode!.ini image_gen_config.ini
		if errorlevel 1 (
		 echo copy config.ini fail , please check the config.ini exist
		 pause
		 goto mm
		)
		
		image_gen_cstm.exe		

		@if not exist output\!chip!\!versoin!\!partnumber!\!config!\!sec_mode! goto new
		@goto end
		:new
			mkdir output\!chip!\!versoin!\!partnumber!\!config!\!sec_mode!
		:end
		COPY output\*.img output\!chip!\!versoin!\!partnumber!\!config!\!sec_mode!\*.img
		COPY output\*.bin output\!chip!\!versoin!\!partnumber!\!config!\!sec_mode!\*.bin
		
		goto :eof
	  )	
	
	)
	





	
