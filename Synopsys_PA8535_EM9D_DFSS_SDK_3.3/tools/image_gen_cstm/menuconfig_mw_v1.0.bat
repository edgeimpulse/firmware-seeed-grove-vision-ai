@echo off 
rem cls
set /a feature_flag_package=0
set /a feature_flag_load_config=0
set /a feature_flag_amr=0
set /a feature_flag_gen_ini=0
set /a amr_enable_flag=0
set /a VERSION_MAJOR = 2		rem MajorNum indicate tool type
set /a VERSION_MINOR = 0		rem MinorNum indicate tool feature update
set /a VERSION_MINI = 0			rem MiniNum indicate tool bug/issue fix

rem ### menu start ###
:menu_list
cls
:load_priv_package_setting
set priv_package_setting_path=ini_folder\priv.ini
set tmp_setting_path=ini_folder\tmp.ini
set key1=tmp_chip_name
set key2=sec_format_name
set key3=ini_sign_forma
set key4=ini_flash_size
set key5=part_number_name
echo off > %tmp_setting_path%

for /f "tokens=1,2 delims=/=" %%i in (%priv_package_setting_path%) do (
	rem echo i = %%i, key1 = %key1%, key2 = %key2%, key3 = %key3%, key4 = %key4%, key5 = %key5%, 
	if "%%j" == "" (
		echo %%i>>%tmp_setting_path%
	) else (
		echo %%i=%%j>>%tmp_setting_path%
	)
    if "%%i"=="%key1%" set %key1%=%%j
	if "%%i"=="%key2%" set %key2%=%%j
	if "%%i"=="%key3%" set %key3%=%%j
	if "%%i"=="%key4%" set %key4%=%%j
	if "%%i"=="%key5%" set %key5%=%%j
)
rem echo tmp_chip_name = %tmp_chip_name%, sec_format_name = %sec_format_name%, ini_sign_forma = %ini_sign_forma%, ini_flash_size = %ini_flash_size%, part_number_name = %part_number_name%
rem pause

@echo [HIMAX] ***************************************************************** 
@echo [HIMAX] ****************                              *******************
@echo [HIMAX] ****************     Menuconfig Ver.%VERSION_MAJOR%.%VERSION_MINOR%.%VERSION_MINI%     *******************  
@echo [HIMAX] ****************                              ******************* 
@echo [HIMAX] *****************************************************************
set menu_list_path=ini_folder\menu_list.ini
set /a menu_list_cnt=1
set /a menu_tmp_cnt=1
set /a aa=0
set menu_list_input=NULL

echo [HIMAX] Feature list:
Setlocal EnableDelayedExpansion
for /f "delims=" %%i in (%menu_list_path%) do (
    echo [HIMAX] !menu_list_cnt!. %%i
	set /a menu_list_cnt += 1
)
set /a menu_tmp_cnt = menu_list_cnt - 2

@echo [HIMAX]
set /p menu_list_input="[HIMAX] Please select one feature ( 1 ~ %menu_tmp_cnt% ): "

if not defined menu_list_input (
    @echo [HIMAX] User input can not be NULL please check and try again!
	goto menu_list
)

if %menu_list_input% leq %menu_tmp_cnt% (
	if %menu_list_input% gtr 0 (
		For /f "delims=" %%c in (%menu_list_path%) do (
			Set /a aa += 1
			rem echo [cdc] !aa!. %%c
			if !aa! equ %menu_list_input% set tmp_menu_list=%%c
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %menu_list_input% is not on the list please check and try again!
		goto menu_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %menu_list_input% is not on the list please check and try again!
	goto menu_list
)

@echo [HIMAX] Your selection is "%tmp_menu_list%"
cls

if "%tmp_menu_list%" == "Package" (
	goto Package_Start
) else if "%tmp_menu_list%" == "Load Config (Option)" (
	goto Load_Config_Start
) else if "%tmp_menu_list%" == "AMR (Option)" (
	set /a amr_enable_flag=1
	goto AMR_Start
) else if "%tmp_menu_list%" == "Generate ini File" (
	if "%amr_enable_flag%" == "1" (
		goto gen_amr_ini
	) else (
		goto gen_normal_ini
	)
)
rem ### menu end ###


@echo [HIMAX] 


:Package_Start
rem ### chip_name start ###
:chip_name_list
Setlocal EnableDelayedExpansion
set chip_name_path=ini_folder\chip_name.ini
@echo [HIMAX] -------------------- Chip Name List --------------------- 
set /a chip_name_cnt=1
set /a chip_tmp_cnt=1
rem set chip_name_input=NULL
Set /a aa=0
for /f "delims=" %%i in (%chip_name_path%) do (
    echo [HIMAX] !chip_name_cnt!. %%i
	set /a chip_name_cnt += 1
)
set /a chip_tmp_cnt = chip_name_cnt - 2

@echo [HIMAX]
set /p chip_name_input="[HIMAX] Please select one option ( 1 ~ %chip_tmp_cnt% ): "

if not defined chip_name_input (
    @echo [HIMAX] Your selection can not be NULL please check and try again!
	goto chip_name_list
)

if %chip_name_input% leq %chip_tmp_cnt% (
	if %chip_name_input% gtr 0 (
		For /f "delims=" %%c in (%chip_name_path%) do (
			Set /a aa += 1
			rem echo [cdc] !aa!. %%c
			if !aa! equ %chip_name_input% set tmp_chip_name=%%c
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %chip_name_input% is not on the list please check and try again!
		goto chip_name_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %chip_name_input% is not on the list please check and try again!
	goto chip_name_list
)

@echo [HIMAX] Your selection is "%tmp_chip_name%"
echo off > %priv_package_setting_path%
for /f "tokens=1,2 delims=/=" %%i in (%tmp_setting_path%) do (
	if "%%j" == "" (
		echo %%i>>%priv_package_setting_path%
	) else if "%%i"=="%key1%" (
		echo %%i=%tmp_chip_name%>>%priv_package_setting_path%
	) else (
		echo %%i=%%j>>%priv_package_setting_path%
	)
)
echo off > %tmp_setting_path%
for /f "tokens=1,2 delims=/=" %%i in (%priv_package_setting_path%) do (
	if "%%j" == "" (
		echo %%i>>%tmp_setting_path%
	) else (
		echo %%i=%%j>>%tmp_setting_path%
	)
)
rem cls
rem ### chip_name end ###


@echo [HIMAX]


rem ### sec_format start ###
Setlocal EnableDelayedExpansion
set sec_format_path=ini_folder\sec_format.ini
@echo [HIMAX] -------------------- Sec Format List -------------------- 

:sec_format_list
set /a sec_format=1
set /a sec_format_cnt=1
rem set sec_format_input=NULL
Set /a bb=0
for /f "delims=" %%i in (%sec_format_path%) do (
    echo [HIMAX] !sec_format!. %%i
	set /a sec_format += 1
)
set /a sec_format_cnt = sec_format - 2

@echo [HIMAX]
set /p sec_format_input="[HIMAX] Please select one option ( 1 ~ %sec_format_cnt% ): "

if not defined sec_format_input (
    @echo [HIMAX] Your selection can not be NULL please check and try again!
	goto sec_format_list
)

if %sec_format_input% leq %sec_format_cnt% (
	if %sec_format_input% gtr 0 (
		For /f "delims=" %%c in (%sec_format_path%) do (
			Set /a bb += 1
			if !bb! equ %sec_format_input% set sec_format_name=%%c
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %sec_format_input% is not on the list please check and try again!
		goto sec_format_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %sec_format_input% is not on the list please check and try again!
	goto sec_format_list
)

@echo [HIMAX] Your selection is "%sec_format_name%"
if %sec_format_input% equ 1 (
	set sec_format_name=BLp
	set ini_sign_forma=sign_formal
) else if %sec_format_input% equ 2 (
	set sec_format_name=BLw
	set ini_sign_forma=enc_formal2
) else (
	set sec_format_name=BLp
	set ini_sign_forma=sign_formal
)
echo off > %priv_package_setting_path%
for /f "tokens=1,2 delims=/=" %%i in (%tmp_setting_path%) do (
	if "%%j" == "" (
		echo %%i>>%priv_package_setting_path%
	) else if "%%i"=="%key2%" (
		echo %%i=%sec_format_name%>>%priv_package_setting_path%
	) else if "%%i"=="%key3%" (
		echo %%i=%ini_sign_forma%>>%priv_package_setting_path%
	) else (
		echo %%i=%%j>>%priv_package_setting_path%
	)
)
echo off > %tmp_setting_path%
for /f "tokens=1,2 delims=/=" %%i in (%priv_package_setting_path%) do (
	if "%%j" == "" (
		echo %%i>>%tmp_setting_path%
	) else (
		echo %%i=%%j>>%tmp_setting_path%
	)
)
rem ### sec_format end ###


@echo [HIMAX]


rem ### flash_max_size start ###
Setlocal EnableDelayedExpansion
set flash_max_size_path=ini_folder\flash_max_size.ini
@echo [HIMAX] ------------------ Max Flash Size List ------------------ 

:flash_max_size_list
set /a flash_max_size=1
set /a flash_max_size_cnt=1
set flash_max_size_input=NULL
Set /a cc=0
for /f "delims=" %%i in (%flash_max_size_path%) do (
    echo [HIMAX] !flash_max_size!. %%i
	set /a flash_max_size += 1
)
set /a flash_max_size_cnt = flash_max_size - 2

@echo [HIMAX]
set /p flash_max_size_input="[HIMAX] Please select one option ( 1 ~ %flash_max_size_cnt% ): "

if not defined flash_max_size_input (
    @echo [HIMAX] Your selection can not be NULL please check and try again!
	goto flash_max_size_list
)

if %flash_max_size_input% leq %flash_max_size_cnt% (
	if %flash_max_size_input% gtr 0 (
		For /f "delims=" %%c in (%flash_max_size_path%) do (
			Set /a cc += 1
			if !cc! equ %flash_max_size_input% set flash_max_size_name=%%c
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %flash_max_size_input% is not on the list please check and try again!
		goto flash_max_size_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %flash_max_size_input% is not on the list please check and try again!
	goto flash_max_size_list
)

@echo [HIMAX] Your selection is "%flash_max_size_name%"
if %flash_max_size_input% equ 1 (set ini_flash_size=0x100000) else if %flash_max_size_input% equ 2 (set ini_flash_size=0x200000) else (set ini_flash_size=0x100000)
echo off > %priv_package_setting_path%
for /f "tokens=1,2 delims=/=" %%i in (%tmp_setting_path%) do (
	if "%%j" == "" (
		echo %%i>>%priv_package_setting_path%
	) else if "%%i"=="%key4%" (
		echo %%i=%ini_flash_size%>>%priv_package_setting_path%
	) else (
		echo %%i=%%j>>%priv_package_setting_path%
	)
)
echo off > %tmp_setting_path%
for /f "tokens=1,2 delims=/=" %%i in (%priv_package_setting_path%) do (
	if "%%j" == "" (
		echo %%i>>%tmp_setting_path%
	) else (
		echo %%i=%%j>>%tmp_setting_path%
	)
)
rem ### flash_max_size end ###


@echo [HIMAX]


rem ### part_number start ###
if %chip_name_input% equ 1 set chip_pin_name=part_number_WLCSP38.ini
if %chip_name_input% equ 2 set chip_pin_name=part_number_QFN72.ini
if %chip_name_input% equ 3 set chip_pin_name=part_number_LQFP128.ini

Setlocal EnableDelayedExpansion
set part_number_path=ini_folder\part_number\%chip_pin_name%
@echo [HIMAX] ---------------- %tmp_chip_name% Part Number List ----------------- 

:part_number_list
set /a part_number=1
set /a part_number_cnt=1
set part_number_input=NULL
Set /a ee=0
for /f "delims=" %%i in (%part_number_path%) do (
    echo [HIMAX] !part_number!. %%i
	set /a part_number += 1
)
set /a part_number_cnt = part_number - 2

@echo [HIMAX]
set /p part_number_input="[HIMAX] Please select one option ( 1 ~ %part_number_cnt% ): "

if not defined part_number_input (
    @echo [HIMAX] Your selection can not be NULL please check and try again!
	goto part_number_list
)

if %part_number_input% leq %part_number_cnt% (
	if %part_number_input% gtr 0 (
		For /f "delims=" %%c in (%part_number_path%) do (
			Set /a ee += 1
			if !ee! equ %part_number_input% set part_number_name=%%c
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %part_number_input% is not on the list please check and try again!
		goto part_number_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %part_number_input% is not on the list please check and try again!
	goto part_number_list
)

@echo [HIMAX] Your selection is "%part_number_name%"
echo off > %priv_package_setting_path%
for /f "tokens=1,2 delims=/=" %%i in (%tmp_setting_path%) do (
	if "%%j" == "" (
		echo %%i>>%priv_package_setting_path%
	) else if "%%i"=="%key5%" (
		echo %%i=%part_number_name%>>%priv_package_setting_path%
	) else (
		echo %%i=%%j>>%priv_package_setting_path%
	)
)
echo off > %tmp_setting_path%
for /f "tokens=1,2 delims=/=" %%i in (%priv_package_setting_path%) do (
	if "%%j" == "" (
		echo %%i>>%tmp_setting_path%
	) else (
		echo %%i=%%j>>%tmp_setting_path%
	)
)
rem ### part_number end ###


@echo [HIMAX]
goto menu_list


rem ### load config start ###
:Load_Config_Start
set /a boot_loader_value=1
set /a boot_loader_cnt=1
Set /a gg=0
set first_2nd_loader_input=NULL
set boot_loader_item_path=ini_folder\boot_loader\loader_options.ini

set /a first_bootloader_cnt=1
rem set first_loader_input=NULL
set first_bootloader_path=ini_folder\boot_loader\first_bootloader.ini

set /a first_uart_cnt=1
set first_uart_print_path=ini_folder\boot_loader\first_uart_print.ini

set /a first_re_encryption_cnt=1
set re_encryption_path=ini_folder\boot_loader\re_encryption.ini

set /a first_clock_source_cnt=1
set clock_source_path=ini_folder\boot_loader\clock_source.ini

set /a first_cpu_frequency_cnt=1

set /a second_bootloader_cnt=1
set second_bootloader_path=ini_folder\boot_loader\second_bootloader.ini

set /a second_ota_method_cnt=1
set second_ota_method_path=ini_folder\boot_loader\second_ota_method.ini

set /a second_re_encryption_cnt=1

set /a second_clock_source_cnt=1

set /a second_cpu_frequency_cnt=1
Setlocal EnableDelayedExpansion

cls
@echo [HIMAX] ------------------- Boot Loader List -------------------- 
for /f "delims=" %%i in (%boot_loader_item_path%) do (
    echo [HIMAX] !boot_loader_value!. %%i
	set /a boot_loader_value += 1
)
set /a boot_loader_cnt = boot_loader_value - 2

@echo [HIMAX]
set /p first_2nd_loader_input="[HIMAX] Please select loader config ( 1 ~ %boot_loader_cnt% ): "

if not defined first_2nd_loader_input (
    @echo [HIMAX] Your selection can not be NULL please check and try again!
	goto Load_Config_Start
)

if %first_2nd_loader_input% leq %boot_loader_cnt% (
	if %first_2nd_loader_input% gtr 0 (
		For /f "delims=" %%c in (%boot_loader_item_path%) do (
			Set /a gg += 1
			if !gg! equ %first_2nd_loader_input% set loader_name=%%c
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %first_2nd_loader_input% is not on the list please check and try again!
		goto Load_Config_Start
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %first_2nd_loader_input% is not on the list please check and try again!
	goto Load_Config_Start
)

@echo [HIMAX] Your selection is "%loader_name%"
@echo [HIMAX]
if %first_2nd_loader_input% equ 1 (
	goto 1st_bootloader_selection
) else if %first_2nd_loader_input% equ 2 (
	goto 2nd_bootloader_selection
) else if %first_2nd_loader_input% equ 3 (
	goto menu_list
)

:1st_bootloader_selection
set /a first_bootloader_value=1
set first_loader_input=NULL
Set /a ga=0

echo [HIMAX] ------------------ First Boot Loader -------------------- 
for /f "delims=" %%i in (%first_bootloader_path%) do (
	echo [HIMAX] !first_bootloader_value!. %%i
	set /a first_bootloader_value += 1
)
set /a first_bootloader_cnt = !first_bootloader_value! - 2

@echo [HIMAX] 
set /p first_loader_input="[HIMAX] Please select one option ( 1 ~ !first_bootloader_cnt! ): "

if not defined first_loader_input (
	@echo [HIMAX] Your selection can not be NULL please check and try again!
	goto 1st_bootloader_selection
)

if %first_loader_input% leq %first_bootloader_cnt% (
	if %first_loader_input% gtr 0 (
		For /f "delims=" %%c in (%first_bootloader_path%) do (
			Set /a ga += 1
			if !ga! equ %first_loader_input% set first_loader_name=%%c
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %first_loader_input% is not on the list please check and try again!
		goto 1st_bootloader_selection
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %first_loader_input% is not on the list please check and try again!
	goto 1st_bootloader_selection
)
echo [HIMAX] Your selection is "%first_loader_name%"

if "%first_loader_input%" == "1" (
	goto first_uart_print_list
) else if "%first_loader_input%" == "2" (
	goto first_re_encryption_list
) else if "%first_loader_input%" == "3" (
	goto first_clock_source_list
) else if "%first_loader_input%" == "4" (
	goto Load_Config_Start
)

rem ### 1st boot loader Uart Print start ###
:first_uart_print_list
set /a first_uart_value=1
set first_uart_print_input=NULL
Set /a ad=0

@echo [HIMAX]
@echo [HIMAX] ----------------- 1st UART Print List ------------------- 
for /f "delims=" %%i in (%first_uart_print_path%) do (
	echo [HIMAX] !first_uart_value!. %%i
	set /a first_uart_value += 1
)
set /a first_uart_cnt = first_uart_value - 2

@echo [HIMAX]
set /p first_uart_print_input="[HIMAX] Please select options ( 1 ~ %first_uart_cnt% ): "

if not defined first_uart_print_input (
	@echo [HIMAX] Your selection can not be NULL please check and try again!
	goto first_uart_print_list
)

if %first_uart_print_input% leq %first_uart_cnt% (
	if %first_uart_print_input% gtr 0 (
		For /f "delims=" %%m in (%first_uart_print_path%) do (
			Set /a ad += 1
			if !ad! equ %first_uart_print_input% set first_uart_name=%%m
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %first_uart_print_input% is not on the list please check and try again!
		goto first_uart_print_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %first_uart_print_input% is not on the list please check and try again!
	goto first_uart_print_list
)

@echo [HIMAX] Set "%first_uart_name%" finished!
@echo [HIMAX]

if "%first_uart_print_input%" == "1" (
	Set "content_value_mask=00"
	goto set_first_uart_print_bin
) else if "%first_uart_print_input%" == "2" (
	Set "content_value_mask=01"
	goto set_first_uart_print_bin
)
:set_first_uart_print_bin
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
Set /a ae=0
set "content_value="
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a ae += 1
	if !ae! equ 1 (
		rem echo sam_shih %%a, %%b, %%c, %%d, !content_value_mask!, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d !content_value_mask! %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	) else (
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>temp.txt echo(!content_value!
)
certutil -f -decodehex temp.txt input\Loader_config.bin >nul
del temp.txt
goto 1st_bootloader_selection
rem ### 1st boot loader Uart Print end ###

rem ### 1st boot loader Re-encryption start ###
:first_re_encryption_list
set /a first_re_encryption_value=1
set first_re_encryption_input=NULL
Set /a ab=0

@echo [HIMAX]
@echo [HIMAX] ---------------- 1st Re-encryption List ----------------- 
for /f "delims=" %%i in (%re_encryption_path%) do (
	echo [HIMAX] !first_re_encryption_value!. %%i
	set /a first_re_encryption_value += 1
)
set /a first_re_encryption_cnt = first_re_encryption_value - 2

@echo [HIMAX]
set /p first_re_encryption_input="[HIMAX] Please select options ( 1 ~ %first_re_encryption_cnt% ): "

if not defined first_re_encryption_input (
	@echo [HIMAX] Your selection can not be NULL please check and try again!
	goto first_re_encryption_list
)

if %first_re_encryption_input% leq %first_re_encryption_cnt% (
	if %first_re_encryption_input% gtr 0 (
		For /f "delims=" %%n in (%re_encryption_path%) do (
			Set /a ab += 1
			if !ab! equ %first_re_encryption_input% set first_re_encryption_name=%%n
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %first_re_encryption_input% is not on the list please check and try again!
		goto first_re_encryption_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %first_re_encryption_input% is not on the list please check and try again!
	goto first_re_encryption_list
)

@echo [HIMAX] Set "%first_re_encryption_name%" finished!
@echo [HIMAX]

if "%first_re_encryption_input%" == "1" (
	Set "content_value_mask=00"
	goto set_first_re_encryption_bin
) else if "%first_re_encryption_input%" == "2" (
	Set "content_value_mask=01"
	goto set_first_re_encryption_bin
)
:set_first_re_encryption_bin
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
Set /a ag=0
set "content_value="
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a ag += 1
	if !ag! equ 1 (
		rem echo sam_shih %%a, %%b, %%c, %%d, %%e, !content_value_mask!, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e !content_value_mask! %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>temp.txt echo(!content_value!
)
certutil -f -decodehex temp.txt input\Loader_config.bin >nul
del temp.txt
goto 1st_bootloader_selection
rem ### 1st boot loader Re-encryption end ###


rem ### 1st boot loader clock cource start ###
:first_clock_source_list
set /a first_clock_source_value=1
set first_clock_source_input=NULL
Set /a ac=0

@echo [HIMAX]
@echo [HIMAX] ---------------- 1st Clock Source List ------------------
for /f "delims=" %%i in (%clock_source_path%) do (
	echo [HIMAX] !first_clock_source_value!. %%i
	set /a first_clock_source_value += 1
)
set /a first_clock_source_cnt = first_clock_source_value - 2

@echo [HIMAX]
set /p first_clock_source_input="[HIMAX] Please select options ( 1 ~ %first_clock_source_cnt% ): "

if not defined first_clock_source_input (
	@echo [HIMAX] Your selection can not be NULL please check and try again!
	goto first_clock_source_list
)

if %first_clock_source_input% leq %first_clock_source_cnt% (
	if %first_clock_source_input% gtr 0 (
		For /f "delims=" %%o in (%clock_source_path%) do (
			Set /a ac += 1
			if !ac! equ %first_clock_source_input% set first_clock_source_name=%%o
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %first_clock_source_input% is not on the list please check and try again!
		goto first_clock_source_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %first_clock_source_input% is not on the list please check and try again!
	goto first_clock_source_list
)

@echo [HIMAX] Set "%first_clock_source_name%" finished!
@echo [HIMAX]

if "%first_clock_source_input%" == "1" (
	Set "content_value_mask=00"
	set first_cpu_frequency_path=ini_folder\boot_loader\cpu_frequency_rc36.ini
	goto set_first_clock_source_bin
) else if "%first_clock_source_input%" == "2" (
	Set "content_value_mask=01"
	set first_cpu_frequency_path=ini_folder\boot_loader\cpu_frequency_xtal24.ini
	goto set_first_clock_source_bin
)
:set_first_clock_source_bin
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
set "content_value="
Set /a ae=0
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a ae += 1
	if !ae! equ 1 (
		rem echo sam_shih %%a, %%b, %%c, %%d, %%e, !content_value_mask!, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f !content_value_mask! %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>temp.txt echo(!content_value!
)
certutil -f -decodehex temp.txt input\Loader_config.bin >nul
del temp.txt
rem ### 1st boot loader clock cource end ###

rem ### 1st boot loader cpu frequency start ###
:first_cpu_frequency_list
set /a first_cpu_frequency_value=1
set first_cpu_frequency_input=NULL
Set /a ah=0

set /a cpu_frequency_400M_enable=0
set /a cpu_frequency_300M_enable=0
set /a cpu_frequency_32M_enable=0

@echo [HIMAX] --------------- 1st CPU Frequency List ------------------ 
for /f "delims=" %%i in (%first_cpu_frequency_path%) do (
	echo [HIMAX] !first_cpu_frequency_value!. %%i
	set /a first_cpu_frequency_value += 1
)
set /a first_cpu_frequency_cnt = first_cpu_frequency_value - 2

@echo [HIMAX]
set /p first_cpu_frequency_input="[HIMAX] Please select options ( 1 ~ %first_cpu_frequency_cnt% ): "

if not defined first_cpu_frequency_input (
	@echo [HIMAX] Your selection can not be NULL please check and try again!
	goto first_cpu_frequency_list
)

if %first_cpu_frequency_input% leq %first_cpu_frequency_cnt% (
	if %first_cpu_frequency_input% gtr 0 (
		For /f "delims=" %%p in (%first_cpu_frequency_path%) do (
			Set /a ah += 1
			if !ah! equ %first_cpu_frequency_input% set first_cpu_frequency_name=%%p
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %first_cpu_frequency_input% is not on the list please check and try again!
		goto first_cpu_frequency_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %first_cpu_frequency_input% is not on the list please check and try again!
	goto first_cpu_frequency_list
)

@echo [HIMAX] Set "%first_cpu_frequency_name%" finished!
@echo [HIMAX]

if "%first_cpu_frequency_input%" == "1" (
	Set "content_value_mask=00"
	Set "content_value_mask_f=84"
	Set "content_value_mask_n=D7"
	Set "content_value_mask_t=17"
	set /a cpu_frequency_400M_enable=1
	goto set_first_cpu_frequency_bin
) else if "%first_cpu_frequency_input%" == "2" (
	Set "content_value_mask=00"
	Set "content_value_mask_f=A3"
	Set "content_value_mask_n=E1"
	Set "content_value_mask_t=11"
	set /a cpu_frequency_300M_enable=1
	goto set_first_cpu_frequency_bin
) else if "%first_cpu_frequency_input%" == "3" (
	Set "content_value_mask=00"
	Set "content_value_mask_f=48"
	Set "content_value_mask_n=E8"
	Set "content_value_mask_t=01"
	set /a cpu_frequency_32M_enable=1
	goto set_first_cpu_frequency_bin
)
:set_first_cpu_frequency_bin
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
set "content_value="
Set /a ca=0
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a ca += 1
	if !ca! equ 1 (
		rem echo sam_shih %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, !content_value_mask!, !content_value_mask_f!, !content_value_mask_n!, !content_value_mask_t!
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l !content_value_mask! !content_value_mask_f! !content_value_mask_n! !content_value_mask_t!"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>input\temp.txt echo(!content_value!
)
certutil -f -decodehex input\temp.txt input\Loader_config.bin >nul
del input\temp.txt
rem ### 1st boot loader cpu frequency end ###

rem ### 1st boot loader spi frequency start ###
:first_spi_frequency_list
set first_spi_frequency_input=NULL
set /a spi_def_frequency=0
set /a spi_def_frequency_tmp=0

if !cpu_frequency_32M_enable! equ 1 (
	set /a spi_def_frequency=8
) else (
	set /a spi_def_frequency=50
)

@echo [HIMAX] --------------- 1st SPI Frequency List ------------------ 
set /p first_spi_frequency_input="[HIMAX] Please enter SPI clock of %first_cpu_frequency_name% CPU frequency (or press ENTER to use default: %spi_def_frequency%MHz): "

if "%first_spi_frequency_input%" == "NULL" (
	if !cpu_frequency_32M_enable! equ 1 (
		set first_spi_frequency_input=8
		Set "content_value_mask=00"
		Set "content_value_mask_f=24"
		Set "content_value_mask_n=F4"
		Set "content_value_mask_t=00"
		goto set_first_spi_frequency_bin
	) else (
		set first_spi_frequency_input=50
		Set "content_value_mask=80"
		Set "content_value_mask_f=F0"
		Set "content_value_mask_n=FA"
		Set "content_value_mask_t=02"
		goto set_first_spi_frequency_bin
	)
)

set /a first_spi_frequency_input=%first_spi_frequency_input%
set /a spi_def_frequency_tmp=%spi_def_frequency%+1

if %first_spi_frequency_input% gtr 0 (
	if %first_spi_frequency_input% lss %spi_def_frequency_tmp% (
		rem continue...
	) else (
		@echo [HIMAX] [ERROR1] Your input "%first_spi_frequency_input%" error, SPI clock should be 1~%spi_def_frequency%
		@echo [HIMAX]
		goto first_spi_frequency_list
	)
) else (
	@echo [HIMAX] [ERROR2] Your input "%first_spi_frequency_input%" error, SPI clock should be 1~%spi_def_frequency%
	@echo [HIMAX]
	goto first_spi_frequency_list
)
@echo [HIMAX]
set C=0123456789ABCDEF
set "var=%first_spi_frequency_input%000000"
set str=
:hex_colum
set /a tra=%var% %% 16
call,set tra=%%C:~%tra%,1%%
set /a var/=16
set str=%tra%%str%
if %var% geq 10 (
	goto hex_colum
)
if %var% neq 0 (
	set hexstr=%var%%str%
) else (
	set hexstr=%str%
)
rem echo hexstr=%hexstr%

set /a length=0
set value_tmp=%hexstr%
:string_length_counter
if defined value_tmp (
    set value_tmp=%value_tmp:~1%
    set /a length+=1
    goto string_length_counter
)
set /a length=8-%length%
set /a ten_dec=10
set ret=1
for /L %%i in (1,1,%length%) do set /a ret*=%ten_dec%

set /a zero_complement=%ret%
set zero_complement=%zero_complement:~1%
set "result=%zero_complement%%hexstr%"
rem echo result=%result%

Set "content_value_mask=%result:~-2,2%"
Set "content_value_mask_f=%result:~-4,2%"
Set "content_value_mask_n=%result:~-6,2%"
Set "content_value_mask_t=%result:~-8,2%"
rem echo sam_shih-----!content_value_mask!, !content_value_mask_f!, !content_value_mask_n!, !content_value_mask_t!

:set_first_spi_frequency_bin
@echo [HIMAX]
@echo [HIMAX] Set spi clock "%first_spi_frequency_input%MHz" and "PLL setting" finished!
@echo [HIMAX]
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
set "content_value="
Set /a cf=0
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a cf += 1
	if !cf! equ 1 (
		rem echo sam_shih %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, !content_value_mask!, !content_value_mask_f!, !content_value_mask_n!, !content_value_mask_t!, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h !content_value_mask! !content_value_mask_f! !content_value_mask_n! !content_value_mask_t! %%m %%n %%o %%p"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>input\temp.txt echo(!content_value!
)
certutil -f -decodehex input\temp.txt input\Loader_config.bin >nul
del input\temp.txt
rem ### 1st boot loader cpu frequency end ###

rem ### 1st boot loader pll_setting start ###
:first_pll_setting_list
for /L %%i in (1,1,%length%) do set /a ret*=%ten_dec%
for /L %%g in (1,1,28) do set pll_%%g_value=NULL

if %first_clock_source_input% equ 1 (
	rem echo is RC36M
	if %first_cpu_frequency_input% equ 1 (
		rem echo is 400MHz 01
		Set "pll_1_value=04"
		Set "pll_2_value=10"
		Set "pll_3_value=61"
		Set "pll_4_value=38"
		Set "pll_5_value=8D"
		Set "pll_6_value=08"
		Set "pll_7_value=B6"
		Set "pll_8_value=C0"
		Set "pll_9_value=16"
		Set "pll_10_value=2D"
		Set "pll_11_value=00"
		Set "pll_12_value=00"
		Set "pll_13_value=80"
		Set "pll_14_value=0E"
		Set "pll_15_value=66"
		Set "pll_16_value=D0"
		Set "pll_17_value=E9"
		Set "pll_18_value=C0"
		Set "pll_19_value=51"
		Set "pll_20_value=03"
		Set "pll_21_value=8E"
		Set "pll_22_value=2A"
		Set "pll_23_value=C0"
		Set "pll_24_value=00"
		Set "pll_25_value=FE"
		Set "pll_26_value=00"
		Set "pll_27_value=00"
		Set "pll_28_value=00"
	) else if %first_cpu_frequency_input% equ 2 (
		rem echo is 300MHz 01
		Set "pll_1_value=04"
		Set "pll_2_value=10"
		Set "pll_3_value=61"
		Set "pll_4_value=38"
		Set "pll_5_value=8D"
		Set "pll_6_value=08"
		Set "pll_7_value=B6"
		Set "pll_8_value=C0"
		Set "pll_9_value=16"
		Set "pll_10_value=22"
		Set "pll_11_value=00"
		Set "pll_12_value=00"
		Set "pll_13_value=80"
		Set "pll_14_value=0A"
		Set "pll_15_value=E1"
		Set "pll_16_value=D0"
		Set "pll_17_value=E4"
		Set "pll_18_value=C0"
		Set "pll_19_value=3D"
		Set "pll_20_value=02"
		Set "pll_21_value=AB"
		Set "pll_22_value=2A"
		Set "pll_23_value=C0"
		Set "pll_24_value=00"
		Set "pll_25_value=FE"
		Set "pll_26_value=00"
		Set "pll_27_value=00"
		Set "pll_28_value=00"
	)
) else if %first_clock_source_input% equ 2 (
	rem echo is XTAL24
	if %first_cpu_frequency_input% equ 1 (
		rem echo is 400MHz 02
		Set "pll_1_value=03"
		Set "pll_2_value=10"
		Set "pll_3_value=61"
		Set "pll_4_value=38"
		Set "pll_5_value=8D"
		Set "pll_6_value=08"
		Set "pll_7_value=B6"
		Set "pll_8_value=C0"
		Set "pll_9_value=16"
		Set "pll_10_value=32"
		Set "pll_11_value=00"
		Set "pll_12_value=00"
		Set "pll_13_value=80"
		Set "pll_14_value=10"
		Set "pll_15_value=00"
		Set "pll_16_value=D0"
		Set "pll_17_value=66"
		Set "pll_18_value=C0"
		Set "pll_19_value=66"
		Set "pll_20_value=00"
		Set "pll_21_value=00"
		Set "pll_22_value=2A"
		Set "pll_23_value=C0"
		Set "pll_24_value=00"
		Set "pll_25_value=FE"
		Set "pll_26_value=00"
		Set "pll_27_value=00"
		Set "pll_28_value=00"
	) else if %first_cpu_frequency_input% equ 2 (
		rem echo is 300MHz 02
		Set "pll_1_value=48"
		Set "pll_2_value=10"
		Set "pll_3_value=34"
		Set "pll_4_value=EB"
		Set "pll_5_value=8D"
		Set "pll_6_value=08"
		Set "pll_7_value=B6"
		Set "pll_8_value=C0"
		Set "pll_9_value=16"
		Set "pll_10_value=64"
		Set "pll_11_value=00"
		Set "pll_12_value=00"
		Set "pll_13_value=80"
		Set "pll_14_value=0C"
		Set "pll_15_value=29"
		Set "pll_16_value=D0"
		Set "pll_17_value=D3"
		Set "pll_18_value=C0"
		Set "pll_19_value=4D"
		Set "pll_20_value=04"
		Set "pll_21_value=00"
		Set "pll_22_value=2A"
		Set "pll_23_value=C0"
		Set "pll_24_value=00"
		Set "pll_25_value=FE"
		Set "pll_26_value=00"
		Set "pll_27_value=00"
		Set "pll_28_value=00"
	) else if %first_cpu_frequency_input% equ 3 (
		rem echo is 32MHz 02
		Set "pll_1_value=02"
		Set "pll_2_value=68"
		Set "pll_3_value=61"
		Set "pll_4_value=38"
		Set "pll_5_value=8D"
		Set "pll_6_value=08"
		Set "pll_7_value=B6"
		Set "pll_8_value=C0"
		Set "pll_9_value=16"
		Set "pll_10_value=20"
		Set "pll_11_value=00"
		Set "pll_12_value=00"
		Set "pll_13_value=80"
		Set "pll_14_value=10"
		Set "pll_15_value=00"
		Set "pll_16_value=D0"
		Set "pll_17_value=66"
		Set "pll_18_value=C0"
		Set "pll_19_value=66"
		Set "pll_20_value=00"
		Set "pll_21_value=00"
		Set "pll_22_value=2A"
		Set "pll_23_value=C0"
		Set "pll_24_value=00"
		Set "pll_25_value=FE"
		Set "pll_26_value=00"
		Set "pll_27_value=00"
		Set "pll_28_value=00"
	)
)
:set_first_pll_setting_bin
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
set "content_value="
Set /a cf=0
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a cf += 1
	if !cf! equ 2 (
		rem echo sam_shih !pll_1_value!, !pll_2_value!, !pll_3_value!, !pll_4_value!, !pll_5_value!, !pll_6_value!, !pll_7_value!, !pll_8_value!, !pll_9_value!, !pll_10_value!, !pll_11_value!, !pll_12_value!, !pll_13_value!, !pll_14_value!, !pll_15_value!, !pll_16_value!
		set "content_value=!pll_1_value! !pll_2_value! !pll_3_value! !pll_4_value! !pll_5_value! !pll_6_value! !pll_7_value! !pll_8_value! !pll_9_value! !pll_10_value! !pll_11_value! !pll_12_value! !pll_13_value! !pll_14_value! !pll_15_value! !pll_16_value!"
	) else if !cf! equ 3 (		
		rem echo sam_shih !pll_17_value!, !pll_18_value!, !pll_19_value!, !pll_20_value!, !pll_21_value!, !pll_22_value!, !pll_23_value!, !pll_24_value!, !pll_25_value!, !pll_26_value!, !pll_27_value!, !pll_28_value!, %%m, %%n, %%o, %%p
		set "content_value=!pll_17_value! !pll_18_value! !pll_19_value! !pll_20_value! !pll_21_value! !pll_22_value! !pll_23_value! !pll_24_value! !pll_25_value! !pll_26_value! !pll_27_value! !pll_28_value! %%m %%n %%o %%p"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>input\temp.txt echo(!content_value!
)
certutil -f -decodehex input\temp.txt input\Loader_config.bin >nul
del input\temp.txt
goto 1st_bootloader_selection
rem ### 1st boot loader pll_setting end ###

rem cls
pause
rem goto menu_list
:2nd_bootloader_selection
set /a second_bootloader_value=1
set second_loader_input=NULL
Set /a gb=0

echo [HIMAX] ------------------ Second Boot Loader ------------------- 
for /f "delims=" %%i in (%second_bootloader_path%) do (
	echo [HIMAX] !second_bootloader_value!. %%i
	set /a second_bootloader_value += 1
)
set /a second_bootloader_cnt = !second_bootloader_value! - 2

@echo [HIMAX] 
set /p second_loader_input="[HIMAX] Please select one option ( 1 ~ !second_bootloader_cnt! ): "

if not defined second_loader_input (
	@echo [HIMAX] Your selection can not be NULL please check and try again!
	goto 2nd_bootloader_selection
)

if %second_loader_input% leq %second_bootloader_cnt% (
	if %second_loader_input% gtr 0 (
		For /f "delims=" %%c in (%second_bootloader_path%) do (
			Set /a gb += 1
			if !gb! equ %second_loader_input% set second_loader_name=%%c
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %second_loader_input% is not on the list please check and try again!
		goto 2nd_bootloader_selection
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %second_loader_input% is not on the list please check and try again!
	goto 2nd_bootloader_selection
)
echo [HIMAX] Your selection is "%second_loader_name%"

if "%second_loader_input%" == "1" (
	goto second_ota_method_list
) else if "%second_loader_input%" == "2" (
	goto second_re_encryption_list
) else if "%second_loader_input%" == "3" (
	goto second_clock_source_list
) else if "%second_loader_input%" == "4" (
	goto second_console_baud_rate_list
) else if "%second_loader_input%" == "5" (
	goto Load_Config_Start
)

rem ### 2nd boot loader OTA method start ###
:second_ota_method_list
set /a second_ota_method_value=1
set second_ota_method_input=NULL
Set /a bb=0

@echo [HIMAX]
@echo [HIMAX] -------------------- OTA Method List -------------------- 
for /f "delims=" %%i in (%second_ota_method_path%) do (
	echo [HIMAX] !second_ota_method_value!. %%i
	set /a second_ota_method_value += 1
)
set /a second_ota_method_cnt = second_ota_method_value - 2

@echo [HIMAX]
set /p second_ota_method_input="[HIMAX] Please select options ( 1 ~ %second_ota_method_cnt% ): "

if "%second_ota_method_input%" == "NULL" (
	@echo [HIMAX] Your selection can not be NULL please check and try again!
	goto second_ota_method_list
)

if %second_ota_method_input% leq %second_ota_method_cnt% (
	if %second_ota_method_input% gtr 0 (
		For /f "delims=" %%f in (%second_ota_method_path%) do (
			Set /a bb += 1
			if !bb! equ %second_ota_method_input% set second_ota_method_name=%%f
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %second_ota_method_input% is not on the list please check and try again!
		goto second_ota_method_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %second_ota_method_input% is not on the list please check and try again!
	goto second_ota_method_list
)

@echo [HIMAX] Set "%second_ota_method_name%" finished!
@echo [HIMAX]

if "%second_ota_method_input%" == "1" (
	Set "content_value_mask=00"
	goto set_second_ota_method_bin
) else if "%second_ota_method_input%" == "2" (
	Set "content_value_mask=01"
	goto set_second_ota_method_bin
)
:set_second_ota_method_bin
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
Set /a ae=0
set "content_value="
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a ae += 1
	if !ae! equ 3 (
		rem echo sam_shih %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, !content_value_mask!, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l !content_value_mask! %%n %%o %%p"
	) else (
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>temp.txt echo(!content_value!
)
certutil -f -decodehex temp.txt input\Loader_config.bin >nul
del temp.txt

if "%second_ota_method_input%" == "1" (
	goto 2nd_bootloader_selection
) else if "%second_ota_method_input%" == "2" (
	goto second_cmd_baud_rate_list
)
rem ### 2nd boot loader OTA method end ###

rem ### 2nd boot loader command baud rate start ###
:second_cmd_baud_rate_list
set second_cmd_baud_rate_input=NULL

@echo [HIMAX] --------------- OTA CMD Baud Rate List ------------------ 
set /p second_cmd_baud_rate_input="[HIMAX] Please enter OTA cmd baud rate (or press ENTER to use default: 921600): "

if "%second_cmd_baud_rate_input%" == "NULL" (
	set second_cmd_baud_rate_input=921600
	Set "content_value_mask=00"
	Set "content_value_mask_f=10"
	Set "content_value_mask_n=0E"
	Set "content_value_mask_t=00"
	goto set_second_cmd_baud_rate_bin
)

if %second_cmd_baud_rate_input% gtr 0 (
	if %second_cmd_baud_rate_input% lss 921601 (
		rem continue...
	) else (
		@echo [HIMAX]
		@echo [HIMAX] [ERROR] Your input "%second_cmd_baud_rate_input%" error, should be less than 921600
		@echo [HIMAX]
		goto second_cmd_baud_rate_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] [ERROR] Your input "%second_cmd_baud_rate_input%" error, should be greater than 0
	@echo [HIMAX]
	goto second_cmd_baud_rate_list
)
@echo [HIMAX]
set C=0123456789ABCDEF
set "var=%second_cmd_baud_rate_input%"
set str=
:hex_cmd_baud_colum
set /a tra=%var% %% 16
call,set tra=%%C:~%tra%,1%%
set /a var/=16
set str=%tra%%str%
if %var% geq 10 (
	goto hex_cmd_baud_colum
)
if %var% neq 0 (
	set hexstr=%var%%str%
) else (
	set hexstr=%str%
)
rem echo hexstr=%hexstr%

set /a length=0
set value_tmp=%hexstr%
:string_cmd_baud_length_counter
if defined value_tmp (
    set value_tmp=%value_tmp:~1%
    set /a length+=1
    goto string_cmd_baud_length_counter
)
set /a length=8-%length%
set /a ten_dec=10
set ret=1
for /L %%i in (1,1,%length%) do set /a ret*=%ten_dec%

set /a zero_complement=%ret%
set zero_complement=%zero_complement:~1%
set "result=%zero_complement%%hexstr%"
rem echo result=%result%

Set "content_value_mask=%result:~-2,2%"
Set "content_value_mask_f=%result:~-4,2%"
Set "content_value_mask_n=%result:~-6,2%"
Set "content_value_mask_t=%result:~-8,2%"
rem echo sam_shih-----!content_value_mask!, !content_value_mask_f!, !content_value_mask_n!, !content_value_mask_t!

:set_second_cmd_baud_rate_bin
@echo [HIMAX]
@echo [HIMAX] Set OTA command baud rate "%second_cmd_baud_rate_input%" finished!
@echo [HIMAX]
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
set "content_value="
Set /a cf=0
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a cf += 1
	if !cf! equ 4 (
		rem echo sam_shih %%a, %%b, %%c, %%d, !content_value_mask!, !content_value_mask_f!, !content_value_mask_n!, !content_value_mask_t!, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d !content_value_mask! !content_value_mask_f! !content_value_mask_n! !content_value_mask_t! %%i %%j %%k %%l %%m %%n %%o %%p"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>input\temp.txt echo(!content_value!
)
certutil -f -decodehex input\temp.txt input\Loader_config.bin >nul
del input\temp.txt
goto 2nd_bootloader_selection
rem ### 2nd boot loader command baud rate end ###

rem ### 2nd boot loader Re-encryption start ###
:second_re_encryption_list
set /a second_re_encryption_value=1
set second_re_encryption_input=NULL
Set /a ba=0

@echo [HIMAX]
@echo [HIMAX] ---------------- 2nd Re-encryption List ----------------- 
for /f "delims=" %%i in (%re_encryption_path%) do (
	echo [HIMAX] !second_re_encryption_value!. %%i
	set /a second_re_encryption_value += 1
)
set /a second_re_encryption_cnt = second_re_encryption_value - 2

@echo [HIMAX]
set /p second_re_encryption_input="[HIMAX] Please select options ( 1 ~ %second_re_encryption_cnt% ): "

if "%second_re_encryption_input%" == "NULL" (
	@echo [HIMAX] Your selection can not be NULL please check and try again!
	goto second_re_encryption_list
)

if %second_re_encryption_input% leq %second_re_encryption_cnt% (
	if %second_re_encryption_input% gtr 0 (
		For /f "delims=" %%q in (%re_encryption_path%) do (
			Set /a ba += 1
			if !ba! equ %second_re_encryption_input% set second_re_encryption_name=%%q
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %second_re_encryption_input% is not on the list please check and try again!
		goto second_re_encryption_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %second_re_encryption_input% is not on the list please check and try again!
	goto second_re_encryption_list
)

@echo [HIMAX] Set "%second_re_encryption_name%" finished!
@echo [HIMAX]

if "%second_re_encryption_input%" == "1" (
	Set "content_value_mask=00"
	goto set_second_re_encryption_bin
) else if "%second_re_encryption_input%" == "2" (
	Set "content_value_mask=01"
	goto set_second_re_encryption_bin
)
:set_second_re_encryption_bin
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
Set /a ag=0
set "content_value="
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a ag += 1
	if !ag! equ 3 (
		rem echo sam_shih %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, !content_value_mask!, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m !content_value_mask! %%o %%p"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>temp.txt echo(!content_value!
)
certutil -f -decodehex temp.txt input\Loader_config.bin >nul
del temp.txt
goto 2nd_bootloader_selection
rem ### 2nd boot loader Re-encryption end ###

rem ### 2nd boot loader clock source start ###
:second_clock_source_list
set /a second_clock_source_value=1
set second_clock_source_input=NULL
Set /a bc=0

@echo [HIMAX]
@echo [HIMAX] ---------------- 2nd Clock Source List ------------------ 
for /f "delims=" %%i in (%clock_source_path%) do (
	echo [HIMAX] !second_clock_source_value!. %%i
	set /a second_clock_source_value += 1
)
set /a second_clock_source_cnt = second_clock_source_value - 2

@echo [HIMAX]
set /p second_clock_source_input="[HIMAX] Please select options ( 1 ~ %second_clock_source_cnt% ): "

if "%second_clock_source_input%" == "NULL" (
	@echo [HIMAX] Your selection can not be NULL please check and try again!
	goto second_clock_source_list
)

if %second_clock_source_input% leq %second_clock_source_cnt% (
	if %second_clock_source_input% gtr 0 (
		For /f "delims=" %%s in (%clock_source_path%) do (
			Set /a bc += 1
			if !bc! equ %second_clock_source_input% set second_clock_source_name=%%s
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %second_clock_source_input% is not on the list please check and try again!
		goto second_clock_source_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %second_clock_source_input% is not on the list please check and try again!
	goto second_clock_source_list
)

@echo [HIMAX] Set "%second_clock_source_name%" finished!

if "%second_clock_source_input%" == "1" (
	Set "content_value_mask=00"
	set second_cpu_frequency_path=ini_folder\boot_loader\cpu_frequency_rc36.ini
	goto set_second_clock_source_bin
) else if "%second_clock_source_input%" == "2" (
	Set "content_value_mask=01"
	set second_cpu_frequency_path=ini_folder\boot_loader\cpu_frequency_xtal24.ini
	goto set_second_clock_source_bin
)
:set_second_clock_source_bin
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
set "content_value="
Set /a ge=0
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a ge += 1
	if !ge! equ 3 (
		rem echo sam_shih %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, !content_value_mask!, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%f %%h %%i %%j %%k %%l %%m %%n !content_value_mask! %%p"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>temp.txt echo(!content_value!
)
certutil -f -decodehex temp.txt input\Loader_config.bin >nul
del temp.txt
rem ### 2nd boot loader clock source end ###

rem ### 2nd boot loader cpu frequency start ###
:second_cpu_frequency_list
set /a second_cpu_frequency_value=1
set second_cpu_frequency_input=NULL
Set /a ha=0

set /a cpu_frequency_400M_enable=0
set /a cpu_frequency_300M_enable=0
set /a cpu_frequency_32M_enable=0

@echo [HIMAX]
@echo [HIMAX] --------------- 2nd CPU Frequency List ------------------ 
for /f "delims=" %%i in (%second_cpu_frequency_path%) do (
	echo [HIMAX] !second_cpu_frequency_value!. %%i
	set /a second_cpu_frequency_value += 1
)
set /a second_cpu_frequency_cnt = second_cpu_frequency_value - 2

@echo [HIMAX]
set /p second_cpu_frequency_input="[HIMAX] Please select options ( 1 ~ %second_cpu_frequency_cnt% ): "

if "%second_cpu_frequency_input%" == "NULL" (
	@echo [HIMAX] Your selection can not be NULL please check and try again!
	goto second_cpu_frequency_list
)

if %second_cpu_frequency_input% leq %second_cpu_frequency_cnt% (
	if %second_cpu_frequency_input% gtr 0 (
		For /f "delims=" %%p in (%second_cpu_frequency_path%) do (
			Set /a ha += 1
			if !ha! equ %second_cpu_frequency_input% set second_cpu_frequency_name=%%p
		)
	) else (
		@echo [HIMAX]
		@echo [HIMAX] Your selection %second_cpu_frequency_input% is not on the list please check and try again!
		goto second_cpu_frequency_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] Your selection %second_cpu_frequency_input% is not on the list please check and try again!
	goto second_cpu_frequency_list
)

@echo [HIMAX] Set "%second_cpu_frequency_name%" finished!
@echo [HIMAX]

if "%second_cpu_frequency_input%" == "1" (
	Set "content_value_mask=00"
	Set "content_value_mask_f=84"
	Set "content_value_mask_n=D7"
	Set "content_value_mask_t=17"
	set /a cpu_frequency_400M_enable=1
	goto set_second_cpu_frequency_bin
) else if "%second_cpu_frequency_input%" == "2" (
	Set "content_value_mask=00"
	Set "content_value_mask_f=A3"
	Set "content_value_mask_n=E1"
	Set "content_value_mask_t=11"
	set /a cpu_frequency_300M_enable=1
	goto set_second_cpu_frequency_bin
) else if "%second_cpu_frequency_input%" == "3" (
	Set "content_value_mask=00"
	Set "content_value_mask_f=48"
	Set "content_value_mask_n=E8"
	Set "content_value_mask_t=01"
	set /a cpu_frequency_32M_enable=1
	goto set_second_cpu_frequency_bin
)
:set_second_cpu_frequency_bin
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
set "content_value="
Set /a ct=0
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a ct += 1
	if !ct! equ 4 (
		rem echo sam_shih %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, !content_value_mask!, !content_value_mask_f!, !content_value_mask_n!, !content_value_mask_t!
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l !content_value_mask! !content_value_mask_f! !content_value_mask_n! !content_value_mask_t!"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>input\temp.txt echo(!content_value!
)
certutil -f -decodehex input\temp.txt input\Loader_config.bin >nul
del input\temp.txt
rem ### 2nd boot loader cpu frequency end ###

rem ### 2nd boot loader spi frequency start ###
:second_spi_frequency_list
set second_spi_frequency_input=NULL
set /a second_spi_def_frequency=0
set /a second_spi_def_frequency_tmp=0

if !cpu_frequency_32M_enable! equ 1 (
	set /a second_spi_def_frequency=8
) else (
	set /a second_spi_def_frequency=50
)

@echo [HIMAX] --------------- 2nd SPI Frequency List ------------------ 
set /p second_spi_frequency_input="[HIMAX] Please enter SPI clock of %second_cpu_frequency_name% CPU frequency (or press ENTER to use default: %second_spi_def_frequency%MHz): "

if "%second_spi_frequency_input%" == "NULL" (
	if !cpu_frequency_32M_enable! equ 1 (
		set second_spi_frequency_input=8
		Set "content_value_mask=00"
		Set "content_value_mask_f=12"
		Set "content_value_mask_n=7A"
		Set "content_value_mask_t=00"
		goto set_second_spi_frequency_bin
	) else (
		set second_spi_frequency_input=50
		Set "content_value_mask=80"
		Set "content_value_mask_f=F0"
		Set "content_value_mask_n=FA"
		Set "content_value_mask_t=02"
		goto set_second_spi_frequency_bin
	)
)

set /a second_spi_frequency_input=%second_spi_frequency_input%
set /a second_spi_def_frequency_tmp=%second_spi_def_frequency%+1

if %second_spi_frequency_input% gtr 0 (
	if %second_spi_frequency_input% lss %second_spi_def_frequency_tmp% (
		rem continue...
	) else (
		@echo [HIMAX] [ERROR1] Your input "%second_spi_frequency_input%" error, SPI clock should be 1~%second_spi_def_frequency%
		@echo [HIMAX]
		goto second_spi_frequency_list
	)
) else (
	@echo [HIMAX] [ERROR2] Your input "%second_spi_frequency_input%" error, SPI clock should be 1~%second_spi_def_frequency%
	@echo [HIMAX]
	goto second_spi_frequency_list
)
@echo [HIMAX]
set C=0123456789ABCDEF
set "var=%second_spi_frequency_input%000000"
set str=
:second_hex_colum
set /a tra=%var% %% 16
call,set tra=%%C:~%tra%,1%%
set /a var/=16
set str=%tra%%str%
if %var% geq 10 (
	goto second_hex_colum
)
if %var% neq 0 (
	set hexstr=%var%%str%
) else (
	set hexstr=%str%
)

set /a length=0
set value_tmp=%hexstr%
:second_string_length_counter
if defined value_tmp (
    set value_tmp=%value_tmp:~1%
    set /a length+=1
    goto second_string_length_counter
)
set /a length=8-%length%
set /a ten_dec=10
set ret=1
for /L %%i in (1,1,%length%) do set /a ret*=%ten_dec%

set /a zero_complement=%ret%
set zero_complement=%zero_complement:~1%
set "result=%zero_complement%%hexstr%"
rem echo result=%result%

Set "content_value_mask=%result:~-2,2%"
Set "content_value_mask_f=%result:~-4,2%"
Set "content_value_mask_n=%result:~-6,2%"
Set "content_value_mask_t=%result:~-8,2%"
rem echo sam_shih-----!content_value_mask!, !content_value_mask_f!, !content_value_mask_n!, !content_value_mask_t!

:set_second_spi_frequency_bin
@echo [HIMAX]
@echo [HIMAX] Set spi clock "%second_spi_frequency_input%MHz" and "PLL setting" finished!
@echo [HIMAX]
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
set "content_value="
Set /a fc=0
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a fc += 1
	if !fc! equ 4 (
		rem echo sam_shih %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, !content_value_mask!, !content_value_mask_f!, !content_value_mask_n!, !content_value_mask_t!, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h !content_value_mask! !content_value_mask_f! !content_value_mask_n! !content_value_mask_t! %%m %%n %%o %%p"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>input\temp.txt echo(!content_value!
)
certutil -f -decodehex input\temp.txt input\Loader_config.bin >nul
del input\temp.txt
goto 2nd_bootloader_selection
rem ### 2nd boot loader spi frequency end ###

rem ### 2nd boot loader console baud rate start ###
:second_console_baud_rate_list
set second_console_baud_rate_input=NULL

@echo [HIMAX]
@echo [HIMAX] --------------- Console Baud Rate List ------------------ 
set /p second_console_baud_rate_input="[HIMAX] Please enter console baud rate (or press ENTER to use default: 115200): "

if "%second_console_baud_rate_input%" == "NULL" (
	set second_console_baud_rate_input=115200
	Set "content_value_mask=00"
	Set "content_value_mask_f=C2"
	Set "content_value_mask_n=01"
	Set "content_value_mask_t=00"
	goto set_second_console_baud_rate_bin
)

if %second_console_baud_rate_input% gtr 0 (
	if %second_console_baud_rate_input% lss 921601 (
		rem continue...
	) else (
		@echo [HIMAX]
		@echo [HIMAX] [ERROR] Your input "%second_console_baud_rate_input%" error, should be less than 921600
		@echo [HIMAX]
		goto second_console_baud_rate_list
	)
) else (
	@echo [HIMAX]
	@echo [HIMAX] [ERROR] Your input "%second_console_baud_rate_input%" error, should be greater than 0
	@echo [HIMAX]
	goto second_console_baud_rate_list
)
@echo [HIMAX]
set C=0123456789ABCDEF
set "var=%second_console_baud_rate_input%"
set str=
:hex_console_baud_colum
set /a tra=%var% %% 16
call,set tra=%%C:~%tra%,1%%
set /a var/=16
set str=%tra%%str%
if %var% geq 10 (
	goto hex_console_baud_colum
)
if %var% neq 0 (
	set hexstr=%var%%str%
) else (
	set hexstr=%str%
)
rem echo hexstr=%hexstr%

set /a length=0
set value_tmp=%hexstr%
:string_console_baud_length_counter
if defined value_tmp (
    set value_tmp=%value_tmp:~1%
    set /a length+=1
    goto string_console_baud_length_counter
)
set /a length=8-%length%
set /a ten_dec=10
set ret=1
for /L %%i in (1,1,%length%) do set /a ret*=%ten_dec%

set /a zero_complement=%ret%
set zero_complement=%zero_complement:~1%
set "result=%zero_complement%%hexstr%"
rem echo result=%result%

Set "content_value_mask=%result:~-2,2%"
Set "content_value_mask_f=%result:~-4,2%"
Set "content_value_mask_n=%result:~-6,2%"
Set "content_value_mask_t=%result:~-8,2%"
rem echo sam_shih-----!content_value_mask!, !content_value_mask_f!, !content_value_mask_n!, !content_value_mask_t!

:set_second_console_baud_rate_bin
@echo [HIMAX]
@echo [HIMAX] Set console baud rate "%second_console_baud_rate_input%" finished!
@echo [HIMAX]
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
set "content_value="
Set /a cf=0
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a cf += 1
	if !cf! equ 4 (
		rem echo sam_shih !content_value_mask!, !content_value_mask_f!, !content_value_mask_n!, !content_value_mask_t!, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=!content_value_mask! !content_value_mask_f! !content_value_mask_n! !content_value_mask_t! %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>input\temp.txt echo(!content_value!
)
certutil -f -decodehex input\temp.txt input\Loader_config.bin >nul
del input\temp.txt
goto 2nd_bootloader_selection
rem ### 2nd boot loader console baud rate end ###

rem ### 2nd boot loader pll_setting start ###
:second_pll_setting_list
for /L %%i in (1,1,%length%) do set /a ret*=%ten_dec%
for /L %%z in (1,1,28) do set pll_%%z_value=NULL

if %second_clock_source_input% equ 1 (
	rem echo is RC36M
	if %second_cpu_frequency_input% equ 1 (
		rem echo is 400MHz 01
		Set "pll_1_value=04"
		Set "pll_2_value=10"
		Set "pll_3_value=61"
		Set "pll_4_value=38"
		Set "pll_5_value=8D"
		Set "pll_6_value=08"
		Set "pll_7_value=B6"
		Set "pll_8_value=C0"
		Set "pll_9_value=16"
		Set "pll_10_value=2D"
		Set "pll_11_value=00"
		Set "pll_12_value=00"
		Set "pll_13_value=80"
		Set "pll_14_value=0E"
		Set "pll_15_value=66"
		Set "pll_16_value=D0"
		Set "pll_17_value=E9"
		Set "pll_18_value=C0"
		Set "pll_19_value=51"
		Set "pll_20_value=03"
		Set "pll_21_value=8E"
		Set "pll_22_value=2A"
		Set "pll_23_value=C0"
		Set "pll_24_value=00"
		Set "pll_25_value=FE"
		Set "pll_26_value=00"
		Set "pll_27_value=00"
		Set "pll_28_value=00"
	) else if %second_cpu_frequency_input% equ 2 (
		rem echo is 300MHz 01
		Set "pll_1_value=04"
		Set "pll_2_value=10"
		Set "pll_3_value=61"
		Set "pll_4_value=38"
		Set "pll_5_value=8D"
		Set "pll_6_value=08"
		Set "pll_7_value=B6"
		Set "pll_8_value=C0"
		Set "pll_9_value=16"
		Set "pll_10_value=22"
		Set "pll_11_value=00"
		Set "pll_12_value=00"
		Set "pll_13_value=80"
		Set "pll_14_value=0A"
		Set "pll_15_value=E1"
		Set "pll_16_value=D0"
		Set "pll_17_value=E4"
		Set "pll_18_value=C0"
		Set "pll_19_value=3D"
		Set "pll_20_value=02"
		Set "pll_21_value=AB"
		Set "pll_22_value=2A"
		Set "pll_23_value=C0"
		Set "pll_24_value=00"
		Set "pll_25_value=FE"
		Set "pll_26_value=00"
		Set "pll_27_value=00"
		Set "pll_28_value=00"
	)
) else if %second_clock_source_input% equ 2 (
	rem echo is XTAL24
	if %second_cpu_frequency_input% equ 1 (
		rem echo is 400MHz 02
		Set "pll_1_value=03"
		Set "pll_2_value=10"
		Set "pll_3_value=61"
		Set "pll_4_value=38"
		Set "pll_5_value=8D"
		Set "pll_6_value=08"
		Set "pll_7_value=B6"
		Set "pll_8_value=C0"
		Set "pll_9_value=16"
		Set "pll_10_value=32"
		Set "pll_11_value=00"
		Set "pll_12_value=00"
		Set "pll_13_value=80"
		Set "pll_14_value=10"
		Set "pll_15_value=00"
		Set "pll_16_value=D0"
		Set "pll_17_value=66"
		Set "pll_18_value=C0"
		Set "pll_19_value=66"
		Set "pll_20_value=00"
		Set "pll_21_value=00"
		Set "pll_22_value=2A"
		Set "pll_23_value=C0"
		Set "pll_24_value=00"
		Set "pll_25_value=FE"
		Set "pll_26_value=00"
		Set "pll_27_value=00"
		Set "pll_28_value=00"
	) else if %second_cpu_frequency_input% equ 2 (
		rem echo is 300MHz 02
		Set "pll_1_value=48"
		Set "pll_2_value=10"
		Set "pll_3_value=34"
		Set "pll_4_value=EB"
		Set "pll_5_value=8D"
		Set "pll_6_value=08"
		Set "pll_7_value=B6"
		Set "pll_8_value=C0"
		Set "pll_9_value=16"
		Set "pll_10_value=64"
		Set "pll_11_value=00"
		Set "pll_12_value=00"
		Set "pll_13_value=80"
		Set "pll_14_value=0C"
		Set "pll_15_value=29"
		Set "pll_16_value=D0"
		Set "pll_17_value=D3"
		Set "pll_18_value=C0"
		Set "pll_19_value=4D"
		Set "pll_20_value=04"
		Set "pll_21_value=00"
		Set "pll_22_value=2A"
		Set "pll_23_value=C0"
		Set "pll_24_value=00"
		Set "pll_25_value=FE"
		Set "pll_26_value=00"
		Set "pll_27_value=00"
		Set "pll_28_value=00"
	) else if %second_cpu_frequency_input% equ 3 (
		rem echo is 32MHz 02
		Set "pll_1_value=02"
		Set "pll_2_value=68"
		Set "pll_3_value=61"
		Set "pll_4_value=38"
		Set "pll_5_value=8D"
		Set "pll_6_value=08"
		Set "pll_7_value=B6"
		Set "pll_8_value=C0"
		Set "pll_9_value=16"
		Set "pll_10_value=20"
		Set "pll_11_value=00"
		Set "pll_12_value=00"
		Set "pll_13_value=80"
		Set "pll_14_value=10"
		Set "pll_15_value=00"
		Set "pll_16_value=D0"
		Set "pll_17_value=66"
		Set "pll_18_value=C0"
		Set "pll_19_value=66"
		Set "pll_20_value=00"
		Set "pll_21_value=00"
		Set "pll_22_value=2A"
		Set "pll_23_value=C0"
		Set "pll_24_value=00"
		Set "pll_25_value=FE"
		Set "pll_26_value=00"
		Set "pll_27_value=00"
		Set "pll_28_value=00"
	)
)
:set_second_pll_setting_bin
certutil -f -encodehex input\Loader_config.bin input\Loader_config.txt >nul
del input\Loader_config.bin
set "content_value="
Set /a cf=0
For /f "tokens=2-17" %%a in (input\Loader_config.txt) do (
	Set /a cf += 1
	if !cf! equ 5 (
		rem echo sam_shih !pll_1_value!, !pll_2_value!, !pll_3_value!, !pll_4_value!, !pll_5_value!, !pll_6_value!, !pll_7_value!, !pll_8_value!, !pll_9_value!, !pll_10_value!, !pll_11_value!, !pll_12_value!, !pll_13_value!, !pll_14_value!, !pll_15_value!, !pll_16_value!
		set "content_value=!pll_1_value! !pll_2_value! !pll_3_value! !pll_4_value! !pll_5_value! !pll_6_value! !pll_7_value! !pll_8_value! !pll_9_value! !pll_10_value! !pll_11_value! !pll_12_value! !pll_13_value! !pll_14_value! !pll_15_value! !pll_16_value!"
	) else if !cf! equ 6 (		
		rem echo sam_shih !pll_17_value!, !pll_18_value!, !pll_19_value!, !pll_20_value!, !pll_21_value!, !pll_22_value!, !pll_23_value!, !pll_24_value!, !pll_25_value!, !pll_26_value!, !pll_27_value!, !pll_28_value!, %%m, %%n, %%o, %%p
		set "content_value=!pll_17_value! !pll_18_value! !pll_19_value! !pll_20_value! !pll_21_value! !pll_22_value! !pll_23_value! !pll_24_value! !pll_25_value! !pll_26_value! !pll_27_value! !pll_28_value! %%m %%n %%o %%p"
	) else (
		rem echo sam_shihhh %%a, %%b, %%c, %%d, %%e, %%f, %%g, %%h, %%i, %%j, %%k, %%l, %%m, %%n, %%o, %%p
		set "content_value=%%a %%b %%c %%d %%e %%f %%g %%h %%i %%j %%k %%l %%m %%n %%o %%p"
	)
	>>input\temp.txt echo(!content_value!
)
certutil -f -decodehex input\temp.txt input\Loader_config.bin >nul
del input\temp.txt
goto 2nd_bootloader_selection
rem ### 2nd boot loader pll_setting end ###

rem ### load config end ###


@echo [HIMAX]


rem ### AMR option start ###
rem choice /C YN /M "[HIMAX] Setup AMR options: "
rem if %errorlevel% == 1 goto gen_amr_ini
rem if %errorlevel% == 2 goto gen_normal_ini
:AMR_Start
@echo [HIMAX] ------------------- AMR Options List -------------------- 
set /p amr_cfg_input_file="[HIMAX] Please enter AMR configuration input file (or press ENTER to use default: input\wr_config.bin): "
if not defined amr_cfg_input_file (
    set amr_cfg_input_file=input\wr_config.bin
)
@echo [HIMAX]
if not exist %amr_cfg_input_file% (
	@echo [HIMAX] [WARNING] User input "%amr_cfg_input_file%" is not exist, using default path "input\wr_config.bin"
	@echo [HIMAX]
)
set /p amr_cfg_flash_addr="[HIMAX] Please enter AMR configuration flash address (or press ENTER to use default: C0000): "
if not defined amr_cfg_flash_addr (
    set amr_cfg_flash_addr=C0000
)
@echo [HIMAX]
set /p amr_model_input_file="[HIMAX] Please enter AMR model input file (or press ENTER to use default: input\AMR.tflite): "
if not defined amr_model_input_file (
    set amr_model_input_file=input\AMR.tflite
)
@echo [HIMAX]
if not exist %amr_model_input_file% (
	@echo [HIMAX] [WARNING] User input "%amr_model_input_file%" is not exist, using default path "input\AMR.tflite"
	@echo [HIMAX]
)
set /p amr_model_flash_addr="[HIMAX] Please enter AMR model flash address (or press ENTER to use default: D0000): "
if not defined amr_model_flash_addr (
    set amr_model_flash_addr=D0000
)
goto menu_list
::echo off > %cd%\%tmp_var%
rem 這裡可以是多個路徑，用空格間隔 
::for %%a in (%cd%) do (
	rem /r . 遞迴
	rem for /r . %%b in (*.txt) do (
	::for %%b in (*.txt) do (
		::if exist "%%b" ( 
			::type "%%b" | findstr /i "freertos" && echo %%b >> %cd%\%tmp_var%
		::)
	::) 
) 
::type %tmp_var% | find /i "test02.txt" && goto no 
::echo not found! 
::rem del fileList.txt>nul 2>nul echo. 
:::no 
rem cls echo. 
::echo record at %tmp_var%! 
::start %tmp_var%
rem ### AMR option end ###

:gen_amr_ini
(
	echo [PROJECT_BASE]
	echo flash_max_size = %ini_flash_size%
	echo oupt_file = output\output.img
	echo odm_wrapkey = odm_key\%tmp_chip_name%_%sec_format_name%\%part_number_name%\odm_wrapkey.key
	echo pubkey = odm_key\%tmp_chip_name%_%sec_format_name%\%part_number_name%\we1_root_rsa_key.der.pub
	echo prikey = odm_key\%tmp_chip_name%_%sec_format_name%\%part_number_name%\odm_rsa_key.der
	echo cert = odm_key\%tmp_chip_name%_%sec_format_name%\%part_number_name%\cert1_rsa.bin
	echo devision_size_limit = FB00  
	echo chip_name = %tmp_chip_name%
	echo part_number = %part_number_name%
	echo:
	echo [BOOTLOADER]
	echo pat_type = 0
	echo input_file = input\%sec_format_name%\%tmp_chip_name%\%part_number_name%\%ini_sign_forma%_PA8530_EM9D_Bootloader.bin
	echo sec_format = %sec_format_name%
	echo version = 2
	echo fw_type = 1
	echo flash_addr = 10000
	echo:
	echo [2ND_BOOTLOADER]
	echo pat_type = 1
	echo input_file = input\%sec_format_name%\%tmp_chip_name%\%part_number_name%\%ini_sign_forma%_PA8530_EM9D_2nd_Bootloader.bin
	echo sec_format = %sec_format_name%
	echo version = 2
	echo fw_type = 1
	echo flash_addr = 0
	echo:
	echo [MEMORY_DESCIRPTOR]
	echo pat_type = 3
	echo output_file = output\layout
	echo sec_format = BLp
	echo version = 2
	echo fw_type = 4
	echo flash_addr = 20000
	echo:
	echo [LOADER_CONFIG]
	echo pat_type = 12
	echo input_file = input\Loader_config.bin
	echo sec_format = BLp
	echo version = 2
	echo fw_type = 4
	echo flash_addr = 21000
	echo:
	echo [APPLICATION]
	echo pat_type = 4
	echo input_file = input\WEI_FW_mw_arcem9d_wei_r16
	echo sec_format = %sec_format_name%
	echo version = 2
	echo fw_type = 3
	echo flash_addr = 22000
	echo devision_size = FB00
	echo:
	echo [WATER_METER_CONFIG]
	echo pat_type = 10
	echo input_file = %amr_cfg_input_file%
	echo sec_format = RAW
	echo version = 2
	echo fw_type = 3
	echo flash_addr = %amr_cfg_flash_addr%
	echo:
	echo [WATER_METER_MODEL]
	echo pat_type = 11
	echo input_file = %amr_model_input_file%
	echo sec_format = RAW
	echo version = 2
	echo fw_type = 3
	echo flash_addr = %amr_model_flash_addr%
) > image_gen_config.ini
set /a amr_enable_flag=0
goto end_menuconfig_process

:gen_normal_ini
(
	echo [PROJECT_BASE]
	echo flash_max_size = %ini_flash_size%
	echo oupt_file = output\output.img
	echo odm_wrapkey = odm_key\%tmp_chip_name%_%sec_format_name%\%part_number_name%\odm_wrapkey.key
	echo pubkey = odm_key\%tmp_chip_name%_%sec_format_name%\%part_number_name%\we1_root_rsa_key.der.pub
	echo prikey = odm_key\%tmp_chip_name%_%sec_format_name%\%part_number_name%\odm_rsa_key.der
	echo cert = odm_key\%tmp_chip_name%_%sec_format_name%\%part_number_name%\cert1_rsa.bin
	echo devision_size_limit = FB00  
	echo chip_name = %tmp_chip_name%
	echo part_number = %part_number_name%
	echo:
	echo [BOOTLOADER]
	echo pat_type = 0
	echo input_file = input\%sec_format_name%\%tmp_chip_name%\%part_number_name%\%ini_sign_forma%_PA8530_EM9D_Bootloader.bin
	echo sec_format = %sec_format_name%
	echo version = 2
	echo fw_type = 1
	echo flash_addr = 10000
	echo:
	echo [2ND_BOOTLOADER]
	echo pat_type = 1
	echo input_file = input\%sec_format_name%\%tmp_chip_name%\%part_number_name%\%ini_sign_forma%_PA8530_EM9D_2nd_Bootloader.bin
	echo sec_format = %sec_format_name%
	echo version = 2
	echo fw_type = 1
	echo flash_addr = 0
	echo:
	echo [MEMORY_DESCIRPTOR]
	echo pat_type = 3
	echo output_file = output\layout
	echo sec_format = BLp
	echo version = 2
	echo fw_type = 4
	echo flash_addr = 20000
	echo:
	echo [LOADER_CONFIG]
	echo pat_type = 12
	echo input_file = input\Loader_config.bin
	echo sec_format = BLp
	echo version = 2
	echo fw_type = 4
	echo flash_addr = 21000
	echo:
	echo [APPLICATION]
	echo pat_type = 4
	echo input_file = input\WEI_FW_mw_arcem9d_wei_r16
	echo sec_format = %sec_format_name%
	echo version = 2
	echo fw_type = 3
	echo flash_addr = 22000
	echo devision_size = FB00
) > image_gen_config.ini
goto end_menuconfig_process

:end_menuconfig_process
echo [HIMAX] ********************************************************** 
echo [HIMAX] ************************* SUCCESS ************************ 
echo [HIMAX] ********************************************************** 
echo [HIMAX] ********                                          ******** 
echo [HIMAX] ********      image_gen_config.ini generated      ******** 
echo [HIMAX] ********                                          ******** 
echo [HIMAX] ********************************************************** 
echo [HIMAX] ************************* SUCCESS ************************ 
echo [HIMAX] ********************************************************** 
echo [HIMAX]
exit /b 0

:fail_menuconfig_process
echo [HIMAX] ********************************************************** 
echo [HIMAX] ************************** FAIL ************************** 
echo [HIMAX] ********************************************************** 
echo [HIMAX] *******                                            ******* 
echo [HIMAX] *******    image_gen_config.ini generated fail!     ******* 
echo [HIMAX] *******                                            ******* 
echo [HIMAX] ********************************************************** 
echo [HIMAX] ************************** FAIL **************************
echo [HIMAX] ********************************************************** 
echo [HIMAX] 
exit /b 2