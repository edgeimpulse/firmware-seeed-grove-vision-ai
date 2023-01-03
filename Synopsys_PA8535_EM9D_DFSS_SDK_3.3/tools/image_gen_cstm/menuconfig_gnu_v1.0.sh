#!/bin/bash

#rm image_gen_config.ini 2>/dev/null

img_gen_path=$(dirname $0)
VERSION_MAJOR=2
VERSION_MINOR=0
VERSION_MINI=0

GNU_INI_TMP_PATH=${img_gen_path}/ini_folder/tmp_gnu.ini

funcn_fail_print(){
  echo "[HIMAX]"
  echo "[HIMAX] *********************************************** "
  echo "[HIMAX] ***     ***     ****     *****    ****     **** "
  echo "[HIMAX] *** ******* **** *** **** *** **** *** **** *** "
  echo "[HIMAX] *** ******* **** *** **** *** **** *** **** *** "
  echo "[HIMAX] ***     *** *** **** *** **** **** *** *** **** "
  echo "[HIMAX] *** ******* * ****** * ****** **** *** * ****** "
  echo "[HIMAX] *** ******* *** **** *** **** **** *** *** **** "
  echo "[HIMAX] ***     *** **** *** **** ****    **** **** *** "
  echo "[HIMAX] *********************************************** "  
  echo "[HIMAX]"
}

funcn_normal_gen_ini(){
  cat > ${img_gen_path}/image_gen_config_gnu.ini <<EOF
  [PROJECT_BASE]
  flash_max_size = $ini_flash_size
  oupt_file = output/output.img
  odm_wrapkey = odm_key/${chpi_name_var_name}_${ini_sec_format}/${ini_part_name}/odm_wrapkey.key
  pubkey = odm_key/${chpi_name_var_name}_${ini_sec_format}/${ini_part_name}/we1_root_rsa_key.der.pub
  prikey = odm_key/${chpi_name_var_name}_${ini_sec_format}/${ini_part_name}/odm_rsa_key.der
  cert = odm_key/${chpi_name_var_name}_${ini_sec_format}/${ini_part_name}/cert1_rsa.bin
  devision_size_limit = FB00  
  chip_name = ${chpi_name_var_name}
  part_number = ${ini_part_name}

  [BOOTLOADER]
  pat_type = 0
  input_file = input/${ini_sec_format}/${chpi_name_var_name}_${ini_sec_format}/${ini_sec_format}_${ini_part_name}/${secure_file_name_var}_PA8530_EM9D_Bootloader.bin
  sec_format = $ini_sec_format
  version = 2
  fw_type = 1
  flash_addr = 10000

  [2ND_BOOTLOADER]
  pat_type = 1
  input_file = input/${ini_sec_format}/${chpi_name_var_name}_${ini_sec_format}/${ini_sec_format}_${ini_part_name}/${secure_file_name_var}_PA8530_EM9D_2nd_Bootloader.bin
  sec_format = $ini_sec_format
  version = 2
  fw_type = 1
  flash_addr = 0

  [MEMORY_DESCIRPTOR]
  pat_type = 3
  output_file = output/layout
  sec_format = BLp
  version = 2
  fw_type = 4
  flash_addr = 20000

  [LOADER_CONFIG]
  pat_type = 12
  input_file = input/Loader_config.bin
  sec_format = BLp
  version = 2
  fw_type = 4
  flash_addr = 21000

  [APPLICATION]
  pat_type = 4
  input_file = input/WEI_FW_gnu_arcem9d_wei_r16
  sec_format = $ini_sec_format
  version = 2
  fw_type = 3
  flash_addr = 22000
  devision_size = FB00
EOF
}

funcn_amr_gen_ini(){
  cat > ${img_gen_path}/image_gen_config_gnu.ini <<EOF
  [PROJECT_BASE]
  flash_max_size = $ini_flash_size
  oupt_file = output/output.img
  odm_wrapkey = odm_key/${chpi_name_var_name}_${ini_sec_format}/${ini_part_name}/odm_wrapkey.key
  pubkey = odm_key/${chpi_name_var_name}_${ini_sec_format}/${ini_part_name}/we1_root_rsa_key.der.pub
  prikey = odm_key/${chpi_name_var_name}_${ini_sec_format}/${ini_part_name}/odm_rsa_key.der
  cert = odm_key/${chpi_name_var_name}_${ini_sec_format}/${ini_part_name}/cert1_rsa.bin
  devision_size_limit = FB00  
  chip_name = ${chpi_name_var_name}
  part_number = ${ini_part_name}

  [BOOTLOADER]
  pat_type = 0
  input_file = input/${ini_sec_format}/${chpi_name_var_name}_${ini_sec_format}/${ini_sec_format}_${ini_part_name}/${secure_file_name_var}_PA8530_EM9D_Bootloader.bin
  sec_format = $ini_sec_format
  version = 2
  fw_type = 1
  flash_addr = 10000

  [2ND_BOOTLOADER]
  pat_type = 1
  input_file = input/${ini_sec_format}/${chpi_name_var_name}_${ini_sec_format}/${ini_sec_format}_${ini_part_name}/${secure_file_name_var}_PA8530_EM9D_2nd_Bootloader.bin
  sec_format = $ini_sec_format
  version = 2
  fw_type = 1
  flash_addr = 0

  [MEMORY_DESCIRPTOR]
  pat_type = 3
  output_file = output/layout
  sec_format = BLp
  version = 2
  fw_type = 4
  flash_addr = 20000

  [LOADER_CONFIG]
  pat_type = 12
  input_file = input/Loader_config.bin
  sec_format = BLp
  version = 2
  fw_type = 4
  flash_addr = 21000

  [APPLICATION]
  pat_type = 4
  input_file = input/WEI_FW_gnu_arcem9d_wei_r16
  sec_format = $ini_sec_format
  version = 2
  fw_type = 3
  flash_addr = 22000
  devision_size = FB00

  [WATER_METER_CONFIG]
  pat_type = 10
  input_file = $amr_cfg_input_file
  sec_format = RAW
  version = 2
  fw_type = 3
  flash_addr = $amr_cfg_flash_addr

  [WATER_METER_MODEL]
  pat_type = 11
  input_file = $amr_model_input_file
  sec_format = RAW
  version = 2
  fw_type = 3
  flash_addr = $amr_model_flash_addr
EOF
}

funcn_menu_list(){
  clear
  echo "[HIMAX] ***************************************************************** "
  echo "[HIMAX] ****************                              *******************"
  echo "[HIMAX] ****************     Menuconfig Ver."$VERSION_MAJOR"."$VERSION_MINOR"."$VERSION_MINI"     *******************  "
  echo "[HIMAX] ****************                              ******************* "
  echo "[HIMAX] ***************************************************************** "
  echo "[HIMAX] Feature list: "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/menu_list.ini

  while read -p "[HIMAX] Please select one feature: " menu_list_input
  do
    echo "[HIMAX]"
    if [ $menu_list_input -gt 0 2>/dev/null ] && [ $menu_list_input -le $count 2>/dev/null ]
      then
      menu_list_input_name=$(sed -n "$menu_list_input"p ${img_gen_path}/ini_folder/menu_list.ini)
      echo "[HIMAX] Your selection is: $menu_list_input_name "
      echo "[HIMAX]"
      if [ "$menu_list_input" == "1" ]; then
        funcn_package_list
      elif  [ "$menu_list_input" == "2" ]; then
        funcn_load_config_list
      elif  [ "$menu_list_input" == "3" ]; then
        amr_enable_flag=1
        funcn_amr_list
      elif  [ "$menu_list_input" == "4" ]; then
        funcn_gen_ini_list
      fi
      break
    else
      echo "[HIMAX] Your selection \"$menu_list_input\" is not on the list! Please check and try again!"
    fi
  done
}


funcn_package_list(){
  ### chip_name start ###
  echo "[HIMAX] ------------------------- Chip Name List ------------------------ "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/chip_name.ini

  while read -p "[HIMAX] Please select one option: " chpi_name_var
  do
    echo "[HIMAX]"
    if [ "$chpi_name_var" == "1" ] || [ "$chpi_name_var" == "2" ] || [ "$chpi_name_var" == "3" ]; then
      chpi_name_var_name=$(sed -n "$chpi_name_var"p ${img_gen_path}/ini_folder/chip_name.ini)
      echo "[HIMAX] Your selection is $chpi_name_var_name "
      part_number_file=part_number_$chpi_name_var_name.ini

      sed -i "/^\[Package_Setting\]/,/^\[/ {/^\[Package_Setting\]/b;/^\[/b;s/^tmp_chip_name*=.*/tmp_chip_name=$chpi_name_var_name/g;}" $GNU_INI_TMP_PATH
      break
    else
      echo "[HIMAX] Your selection \"$chpi_name_var\" is not on the list! Please check and try again!"
    fi
  done
  ### chip_name end ###


  echo "[HIMAX]"


  ### sec_format start ###
  echo "[HIMAX] ----------------------- Security Format List -------------------- "
  count=0
  while read line
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/sec_format.ini

  while read -p "[HIMAX] Please select one option: " sec_format_var
  do
    echo "[HIMAX]"
    if [ "$sec_format_var" == "1" ] || [ "$sec_format_var" == "2" ]; then
      sec_format_name=$(sed -n "$sec_format_var"p ${img_gen_path}/ini_folder/sec_format.ini)
      echo "[HIMAX] Your selection is $sec_format_name "

      if [ "$sec_format_var" == "1" ]; then
        ini_sec_format=BLp
        secure_file_name_var=sign_formal
      elif  [ "$sec_format_var" == "2" ]; then
        ini_sec_format=BLw
        secure_file_name_var=enc_formal2
      fi

      sed -i "/^\[Package_Setting\]/,/^\[/ {/^\[Package_Setting\]/b;/^\[/b;s/^sec_format_name*=.*/sec_format_name=$ini_sec_format/g;}" $GNU_INI_TMP_PATH
      sed -i "/^\[Package_Setting\]/,/^\[/ {/^\[Package_Setting\]/b;/^\[/b;s/^ini_sign_forma*=.*/ini_sign_forma=$secure_file_name_var/g;}" $GNU_INI_TMP_PATH
      break
    else
      echo "[HIMAX] Your selection \"$sec_format_var\" is not on the list! Please check and try again!"
    fi
  done
  ### sec_format end ###


  echo "[HIMAX]"


  ### flash_max_size start ###
  echo "[HIMAX] ------------------------ Max Flash Size List -------------------- "
  count=0
  while read line
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/flash_max_size.ini

  while read -p "[HIMAX] Please select one option: " flash_max_size_var
  do
    echo "[HIMAX]"
    if [ "$flash_max_size_var" == "1" ] || [ "$flash_max_size_var" == "2" ]; then
      flash_max_size_name=$(sed -n "$flash_max_size_var"p ${img_gen_path}/ini_folder/sec_format.ini)
      echo "[HIMAX] Your selection is $flash_max_size_name "

      if [ "$flash_max_size_var" == "1" ]; then
        ini_flash_size=0x100000
      elif  [ "$flash_max_size_var" == "2" ]; then
        ini_flash_size=0x200000
      fi

      sed -i "/^\[Package_Setting\]/,/^\[/ {/^\[Package_Setting\]/b;/^\[/b;s/^ini_flash_size*=.*/ini_flash_size=$ini_flash_size/g;}" $GNU_INI_TMP_PATH
      break
    else
      echo "[HIMAX] Your selection \"$flash_max_size_var\" is not on the list! Please check and try again!"
    fi
  done
  ### flash_max_size end ###


  echo "[HIMAX]"


  ### part_number start ###
  echo "[HIMAX] ---------------- $chpi_name_var_name Part Number List --------------- "
  count=0
  while read line
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/part_number/$part_number_file

  while read -p "[HIMAX] Please select one option: " flash_max_size_var
  do
    echo "[HIMAX]"
    if [ $flash_max_size_var -gt 0 2>/dev/null ] && [ $flash_max_size_var -le $count 2>/dev/null ]
    then
      echo -n "[HIMAX] Your selection is " 
      head -$flash_max_size_var ${img_gen_path}/ini_folder/part_number/$part_number_file | tail +$flash_max_size_var
      ini_part_name=$(head -$flash_max_size_var ${img_gen_path}/ini_folder/part_number/$part_number_file | tail +$flash_max_size_var)

      sed -i "/^\[Package_Setting\]/,/^\[/ {/^\[Package_Setting\]/b;/^\[/b;s/^part_number_name*=.*/part_number_name=$ini_part_name/g;}" $GNU_INI_TMP_PATH
      break
    else
      echo "[HIMAX] Your selection $flash_max_size_var is not on the list! Please check and try again!"
    fi
  done
  echo "[HIMAX]"
  funcn_menu_list
  ### part_number end ###
}


funcn_amr_list(){
  echo "[HIMAX] ---------------- AMR Options List --------------- "
  read -p "[HIMAX] Please enter AMR configuration input file (or press ENTER to use default: input/wr_config.bin): " amr_cfg_input_file
  if [ "$amr_cfg_input_file" == "" 2>/dev/null ]
  then
	amr_cfg_input_file=input/wr_config.bin
  fi
  
  echo "[HIMAX]"
  
  if [ ! -f "${img_gen_path}/${amr_cfg_input_file}" ]; then
    echo "[HIMAX] [WARNING] User input \"$amr_cfg_input_file\" is not exist, using default path \"input/wr_config.bin\""
	amr_cfg_input_file=input/wr_config.bin
  fi
  
  read -p "[HIMAX] Please enter AMR configuration flash address (or press ENTER to use default: C0000): " amr_cfg_flash_addr
  if [ "$amr_cfg_flash_addr" == "" 2>/dev/null ]
  then
	amr_cfg_flash_addr=C0000
  fi
  
  echo "[HIMAX]"
  
  read -p "[HIMAX] Please enter AMR model input file (or press ENTER to use default: input/AMR.tflite): " amr_model_input_file
  if [ "$amr_model_input_file" == "" 2>/dev/null ]
  then
	amr_model_input_file=input/AMR.tflite
  fi
  
  echo "[HIMAX]"
  
  if [ ! -f "${img_gen_path}/${amr_model_input_file}" ]; then
    echo "[HIMAX] [WARNING] User input \"$amr_model_input_file\" is not exist, using default path \"input/AMR.tflite\""
	amr_model_input_file=input/AMR.tflite
  fi
  
  echo "[HIMAX]"
  
  read -p "[HIMAX] Please enter AMR model flash address (or press ENTER to use default: D0000): " amr_model_flash_addr
  if [ "$amr_model_flash_addr" == "" 2>/dev/null ]
  then
	amr_model_flash_addr=D0000
  fi
}


funcn_gen_ini_list(){
  if  [ "$amr_enable_flag" == "1" ]; then
    funcn_amr_gen_ini
  else
    funcn_normal_gen_ini
  fi
  amr_enable_flag=0
  
  echo "[HIMAX]"
  echo "[HIMAX]"
  echo "[HIMAX] ***************************************************************** "
  echo "[HIMAX] **************************** SUCCESS **************************** "
  echo "[HIMAX] ***************************************************************** "
  echo "[HIMAX] ************                                         ************ "
  echo "[HIMAX] ************   image_gen_config_gnu.ini generated    ************ "
  echo "[HIMAX] ************                                         ************ "
  echo "[HIMAX] ***************************************************************** "
  echo "[HIMAX] *************************** SUCCESS *************************** "
  echo "[HIMAX] ***************************************************************** "
  echo "[HIMAX]"
  exit
}


funcn_load_config_list(){
  clear
  echo "[HIMAX] ------------------------ Boot Loader List ----------------------- "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/boot_loader/loader_options.ini

  while read -p "[HIMAX] Please select loader config: " loader_config_var
  do
    echo "[HIMAX]"
    if [ $loader_config_var -gt 0 2>/dev/null ] && [ $loader_config_var -le $count 2>/dev/null ]; then
      loader_config_name=$(sed -n "$loader_config_var"p ${img_gen_path}/ini_folder/boot_loader/loader_options.ini)
      echo "[HIMAX] Your selection is $loader_config_name "
      echo "[HIMAX] "
      if [ "$loader_config_var" == "1" ]; then
        funcn_first_load_config_list
      elif  [ "$loader_config_var" == "2" ]; then
        funcn_second_load_config_list
      elif  [ "$loader_config_var" == "3" ]; then
        funcn_menu_list
      fi
      break
    else
      echo "[HIMAX] Your selection \"$loader_config_var\" is not on the list! Please check and try again!"
    fi
  done
  funcn_menu_list
}


funcn_first_load_config_list(){
  echo "[HIMAX] --------------------- First Boot Loader List -------------------- "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/boot_loader/first_bootloader.ini

  while read -p "[HIMAX] Please select loader config: " first_loader_config_var
  do
    echo "[HIMAX]"
    if [ $first_loader_config_var -gt 0 2>/dev/null ] && [ $first_loader_config_var -le $count 2>/dev/null ]; then
      first_loader_config_name=$(sed -n "$first_loader_config_var"p ${img_gen_path}/ini_folder/boot_loader/first_bootloader.ini)
      echo "[HIMAX] Your selection is $first_loader_config_name "
      echo "[HIMAX] "
      if [ "$first_loader_config_var" == "1" ]; then
        funcn_first_uart_print_list
      elif  [ "$first_loader_config_var" == "2" ]; then
        funcn_loader_re_encryption_list 1st
      elif  [ "$first_loader_config_var" == "3" ]; then
        funcn_loader_clock_source_list 1st
      elif  [ "$first_loader_config_var" == "4" ]; then
        clear
        funcn_load_config_list
      fi
      break
    else
      echo "[HIMAX] Your selection \"$first_loader_config_var\" is not on the list! Please check and try again!"
    fi
  done
  funcn_menu_list
}


funcn_first_uart_print_list(){
  echo "[HIMAX] ------------------- 1st Boot Loader UART Print ------------------ "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/boot_loader/first_uart_print.ini

  while read -p "[HIMAX] Please select one option: " first_loader_uart_print_var
  do
    echo "[HIMAX]"
    if [ $first_loader_uart_print_var -gt 0 2>/dev/null ] && [ $first_loader_uart_print_var -le $count 2>/dev/null ]; then
      first_uart_print_name=$(sed -n "$first_loader_uart_print_var"p ${img_gen_path}/ini_folder/boot_loader/first_uart_print.ini)
      echo "[HIMAX] Your selection is $first_uart_print_name "
      echo "[HIMAX] "
      if [ "$first_loader_uart_print_var" == "1" ]; then
        printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=4 2>/dev/null
      elif  [ "$first_loader_uart_print_var" == "2" ]; then
        printf "\x01" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=4 2>/dev/null
      fi
      break
    else
      echo "[HIMAX] Your selection \"$first_loader_uart_print_var\" is not on the list! Please check and try again!"
    fi
  done
  funcn_first_load_config_list
}


funcn_loader_re_encryption_list(){
  echo "[HIMAX] ------------------- $1 Boot Loader UART Print ------------------ "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/boot_loader/re_encryption.ini

  while read -p "[HIMAX] Please select one option: " loader_re_encryption_var
  do
    echo "[HIMAX]"
    if [ $loader_re_encryption_var -gt 0 2>/dev/null ] && [ $loader_re_encryption_var -le $count 2>/dev/null ]; then
      re_encryption_name=$(sed -n "$loader_re_encryption_var"p ${img_gen_path}/ini_folder/boot_loader/re_encryption.ini)
      echo "[HIMAX] Your selection is $re_encryption_name "
      echo "[HIMAX] "
      if [ "$loader_re_encryption_var" == "1" ] && [ "$1" == "1st" ]; then
        printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=4 2>/dev/null
      elif  [ "$loader_re_encryption_var" == "2" ] && [ "$1" == "1st" ]; then
        printf "\x01" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=4 2>/dev/null
      elif  [ "$loader_re_encryption_var" == "1" ] && [ "$1" == "2nd" ]; then
        printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=45 2>/dev/null
      elif  [ "$loader_re_encryption_var" == "2" ] && [ "$1" == "2nd" ]; then
        printf "\x01" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=45 2>/dev/null
      fi
      break
    else
      echo "[HIMAX] Your selection \"$loader_re_encryption_var\" is not on the list! Please check and try again!"
    fi
  done
  funcn_first_load_config_list
}


funcn_loader_clock_source_list(){
  echo "[HIMAX] ------------------ $1 Boot Loader Clock Source ----------------- "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/boot_loader/clock_source.ini

  while read -p "[HIMAX] Please select one option: " loader_clock_source_var
  do
    echo "[HIMAX]"
    if [ $loader_clock_source_var -gt 0 2>/dev/null ] && [ $loader_clock_source_var -le $count 2>/dev/null ]; then
      re_encryption_name=$(sed -n "$loader_clock_source_var"p ${img_gen_path}/ini_folder/boot_loader/clock_source.ini)
      echo "[HIMAX] Your selection is $re_encryption_name "
      echo "[HIMAX] "
      if [ "$loader_clock_source_var" == "1" ] && [ "$1" == "1st" ]; then
        printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=6 2>/dev/null

        re_encryption_file_name=cpu_frequency_rc36.ini
        funcn_loader_cpu_frequency_list RC36
      elif  [ "$loader_clock_source_var" == "2" ] && [ "$1" == "1st" ]; then
        printf "\x01" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=6 2>/dev/null

        re_encryption_file_name=cpu_frequency_xtal24.ini
        funcn_loader_cpu_frequency_list XTAL24
      elif  [ "$loader_clock_source_var" == "1" ] && [ "$1" == "2nd" ]; then
        printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=46 2>/dev/null

        re_encryption_file_name=cpu_frequency_rc36.ini
        funcn_2nd_loader_cpu_frequency_list RC36
      elif  [ "$loader_clock_source_var" == "2" ] && [ "$1" == "2nd" ]; then
        printf "\x01" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=46 2>/dev/null

        re_encryption_file_name=cpu_frequency_xtal24.ini
        funcn_2nd_loader_cpu_frequency_list XTAL24
      fi
      break
    else
      echo "[HIMAX] Your selection \"$loader_clock_source_var\" is not on the list! Please check and try again!"
    fi
  done
}


funcn_loader_cpu_frequency_list(){
  echo "[HIMAX] ----------------- 1st Bootloader CPU Frequency ----------------- "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/boot_loader/$re_encryption_file_name

  while read -p "[HIMAX] Please select one option: " loader_cpu_frequency_var
  do
    echo "[HIMAX]"
    if [ $loader_cpu_frequency_var -gt 0 2>/dev/null ] && [ $loader_cpu_frequency_var -le $count 2>/dev/null ]; then
      cpu_frequency_name=$(sed -n "$loader_cpu_frequency_var"p ${img_gen_path}/ini_folder/boot_loader/$re_encryption_file_name)
      echo "[HIMAX] Your selection is $cpu_frequency_name "
      echo "[HIMAX] "
      if [ "$1" == "RC36" ]; then
        if [ "$loader_cpu_frequency_var" == "1" ]; then   #400M
          printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=12 2>/dev/null
          printf "\x84" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=13 2>/dev/null
          printf "\xD7" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=14 2>/dev/null
          printf "\x17" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=15 2>/dev/null
          funcn_loader_spi_frequency_list 400MHz rc36
        else                                              #300M
          printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=12 2>/dev/null
          printf "\xA3" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=13 2>/dev/null
          printf "\xE1" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=14 2>/dev/null
          printf "\x11" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=15 2>/dev/null
          funcn_loader_spi_frequency_list 300MHz rc36
        fi
      elif  [ "$1" == "XTAL24" ]; then
        if [ "$loader_cpu_frequency_var" == "1" ]; then   #400M
          printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=12 2>/dev/null
          printf "\x84" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=13 2>/dev/null
          printf "\xD7" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=14 2>/dev/null
          printf "\x17" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=15 2>/dev/null
          funcn_loader_spi_frequency_list 400MHz xtal24
        elif [ "$loader_cpu_frequency_var" == "2" ]; then #300M
          printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=12 2>/dev/null
          printf "\xA3" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=13 2>/dev/null
          printf "\xE1" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=14 2>/dev/null
          printf "\x11" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=15 2>/dev/null
          funcn_loader_spi_frequency_list 300MHz xtal24
        else                                              #32M
          printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=12 2>/dev/null
          printf "\x48" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=13 2>/dev/null
          printf "\xE8" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=14 2>/dev/null
          printf "\x01" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=15 2>/dev/null
          funcn_loader_spi_frequency_list 32MHz xtal24
        fi
      fi
      break
    else
      echo "[HIMAX] Your selection \"$loader_cpu_frequency_var\" is not on the list! Please check and try again!"
    fi
  done
}


funcn_2nd_loader_cpu_frequency_list(){
  echo "[HIMAX] ----------------- 2nd Bootloader CPU Frequency ----------------- "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/boot_loader/$re_encryption_file_name

  while read -p "[HIMAX] Please select one option: " loader_2nd_cpu_frequency_var
  do
    echo "[HIMAX]"
    if [ $loader_2nd_cpu_frequency_var -gt 0 2>/dev/null ] && [ $loader_2nd_cpu_frequency_var -le $count 2>/dev/null ]; then
      cpu_2nd_frequency_name=$(sed -n "$loader_2nd_cpu_frequency_var"p ${img_gen_path}/ini_folder/boot_loader/$re_encryption_file_name)
      echo "[HIMAX] Your selection is $cpu_2nd_frequency_name "
      echo "[HIMAX] "
      if [ "$1" == "RC36" ]; then
        if [ "$loader_2nd_cpu_frequency_var" == "1" ]; then   #400M
          printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=60 2>/dev/null
          printf "\x84" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=61 2>/dev/null
          printf "\xD7" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=62 2>/dev/null
          printf "\x17" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=63 2>/dev/null
          funcn_2nd_loader_spi_frequency_list 400MHz rc36
        else                                              #300M
          printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=60 2>/dev/null
          printf "\xA3" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=61 2>/dev/null
          printf "\xE1" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=62 2>/dev/null
          printf "\x11" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=63 2>/dev/null
          funcn_2nd_loader_spi_frequency_list 300MHz rc36
        fi
      elif  [ "$1" == "XTAL24" ]; then
        if [ "$loader_2nd_cpu_frequency_var" == "1" ]; then   #400M
          printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=60 2>/dev/null
          printf "\x84" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=61 2>/dev/null
          printf "\xD7" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=62 2>/dev/null
          printf "\x17" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=63 2>/dev/null
          funcn_2nd_loader_spi_frequency_list 400MHz xtal24
        elif [ "$loader_2nd_cpu_frequency_var" == "2" ]; then #300M
          printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=60 2>/dev/null
          printf "\xA3" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=61 2>/dev/null
          printf "\xE1" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=62 2>/dev/null
          printf "\x11" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=63 2>/dev/null
          funcn_2nd_loader_spi_frequency_list 300MHz xtal24
        else                                              #32M
          printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=60 2>/dev/null
          printf "\x48" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=61 2>/dev/null
          printf "\xE8" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=62 2>/dev/null
          printf "\x01" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=63 2>/dev/null
          funcn_2nd_loader_spi_frequency_list 32MHz xtal24
        fi
      fi
      break
    else
      echo "[HIMAX] Your selection \"$loader_2nd_cpu_frequency_var\" is not on the list! Please check and try again!"
    fi
  done
}


funcn_loader_spi_frequency_list(){
  echo "[HIMAX] ------------- 1st Boot Loader SPI Frequency Setting --------- "
  if [ "$1" == "32MHz" ]; then
    spi_limit_var=8
  else
    spi_limit_var=50
  fi 

  if [ "$2" == "rc36" ]; then
    if [ "$1" == "400MHz" ]; then
      funcn_1st_rc36_set_pll_setting 400MHz
    else
      funcn_1st_rc36_set_pll_setting 300MHz
    fi
  else
    if [ "$1" == "400MHz" ]; then
      funcn_1st_xtal24_set_pll_setting 400MHz
    elif [ "$1" == "300MHz" ]; then
      funcn_1st_xtal24_set_pll_setting 300MHz
    else
      funcn_1st_xtal24_set_pll_setting 32MHz
    fi
  fi

  while read -p "[HIMAX] Please enter SPI clock of $1 CPU frequency (or press ENTER to use default: $spi_limit_var MHz): " loader_spi_frequency_var
  do
    echo "[HIMAX]"
    if [ $loader_spi_frequency_var -gt 0 2>/dev/null ] && [ $loader_spi_frequency_var -le 50 2>/dev/null ] && [ "$loader_spi_frequency_var" != "" 2>/dev/null ]; then
      echo "[HIMAX] Set SPI frequency as "$loader_spi_frequency_var"MHz finished!"
      echo "[HIMAX] "
      loader_spi_frequency_var_hex=$(printf '%x\n' $loader_spi_frequency_var)
      tmp1=$(printf '%x\n' $((0x$loader_spi_frequency_var_hex & 0xff)))

      loader_spi_frequency_var_hex=$((0x$loader_spi_frequency_var_hex >> 8))
      loader_spi_frequency_var_hex_2=$(printf '%x\n' $loader_spi_frequency_var_hex)
      tmp2=$(printf '%x\n' $((0x$loader_spi_frequency_var_hex_2 & 0xff)))

      loader_spi_frequency_var_hex_2=$((0x$loader_spi_frequency_var_hex_2 >> 8))
      loader_spi_frequency_var_hex_3=$(printf '%x\n' $loader_spi_frequency_var_hex_2)
      tmp3=$(printf '%x\n' $((0x$loader_spi_frequency_var_hex_3 & 0xff)))

      loader_spi_frequency_var_hex_3=$((0x$loader_spi_frequency_var_hex_3 >> 8))
      loader_spi_frequency_var_hex_4=$(printf '%x\n' $loader_spi_frequency_var_hex_3)
      tmp4=$(printf '%x\n' $((0x$loader_spi_frequency_var_hex_4 & 0xff)))

      #echo $tmp1, $tmp2, $tmp3, $tmp4
      printf "\x$tmp1" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=8 2>/dev/null
      printf "\x$tmp2" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=9 2>/dev/null
      printf "\x$tmp3" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=10 2>/dev/null
      printf "\x$tmp4" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=11 2>/dev/null
      break
    fi

    if [ "$loader_spi_frequency_var" == "" 2>/dev/null ] && [ "$spi_limit_var" == "8" 2>/dev/null ];then
      echo "[HIMAX] Set SPI frequency as "$spi_limit_var"MHz finished!"
      printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=8 2>/dev/null
      printf "\x12" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=9 2>/dev/null
      printf "\x7A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=10 2>/dev/null
      printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=11 2>/dev/null
      break
    elif [ "$loader_spi_frequency_var" == "" 2>/dev/null ] && [ "$spi_limit_var" == "50" 2>/dev/null ];then
      echo "[HIMAX] Set SPI frequency as "$spi_limit_var"MHz finished!"
      printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=8 2>/dev/null
      printf "\xF0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=9 2>/dev/null
      printf "\xFA" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=10 2>/dev/null
      printf "\x02" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=11 2>/dev/null
      break
    else
      echo "[HIMAX] [ERROR] Your input "$loader_spi_frequency_var" error, should be 0~$spi_limit_var MHz"
      echo -n "[HIMAX] Please enter SPI clock of $1 CPU frequency (or press ENTER to use default: $spi_limit_var MHz): "
    fi
  done
  echo "[HIMAX] "
  funcn_first_load_config_list
}


funcn_2nd_loader_spi_frequency_list(){
  echo "[HIMAX] ------------- 2nd Boot Loader SPI Frequency Setting --------- "
  if [ "$1" == "32MHz" ]; then
    spi_2nd_limit_var=8
  else
    spi_2nd_limit_var=50
  fi

  if [ "$2" == "rc36" ]; then
    if [ "$1" == "400MHz" ]; then
      funcn_2nd_rc36_set_pll_setting 400MHz
    else
      funcn_2nd_rc36_set_pll_setting 300MHz
    fi
  else
    if [ "$1" == "400MHz" ]; then
      funcn_2nd_xtal24_set_pll_setting 400MHz
    elif [ "$1" == "300MHz" ]; then
      funcn_2nd_xtal24_set_pll_setting 300MHz
    else
      funcn_2nd_xtal24_set_pll_setting 32MHz
    fi
  fi


  while read -p "[HIMAX] Please enter SPI clock of $2 CPU frequency (or press ENTER to use default: $spi_2nd_limit_var MHz): " loader_spi_frequency_var
  do
    echo "[HIMAX]"
    if [ $loader_spi_frequency_var -gt 0 2>/dev/null ] && [ $loader_spi_frequency_var -le 50 2>/dev/null ] && [ "$loader_spi_frequency_var" != "" 2>/dev/null ]; then
      echo "[HIMAX] Set SPI frequency as "$loader_spi_frequency_var"MHz finished!"
      echo "[HIMAX] "
      loader_spi_frequency_var_hex=$(printf '%x\n' $loader_spi_frequency_var)
      tmp1=$(printf '%x\n' $((0x$loader_spi_frequency_var_hex & 0xff)))

      loader_spi_frequency_var_hex=$((0x$loader_spi_frequency_var_hex >> 8))
      loader_spi_frequency_var_hex_2=$(printf '%x\n' $loader_spi_frequency_var_hex)
      tmp2=$(printf '%x\n' $((0x$loader_spi_frequency_var_hex_2 & 0xff)))

      loader_spi_frequency_var_hex_2=$((0x$loader_spi_frequency_var_hex_2 >> 8))
      loader_spi_frequency_var_hex_3=$(printf '%x\n' $loader_spi_frequency_var_hex_2)
      tmp3=$(printf '%x\n' $((0x$loader_spi_frequency_var_hex_3 & 0xff)))

      loader_spi_frequency_var_hex_3=$((0x$loader_spi_frequency_var_hex_3 >> 8))
      loader_spi_frequency_var_hex_4=$(printf '%x\n' $loader_spi_frequency_var_hex_3)
      tmp4=$(printf '%x\n' $((0x$loader_spi_frequency_var_hex_4 & 0xff)))

      #echo $tmp1, $tmp2, $tmp3, $tmp4
      printf "\x$tmp1" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=48 2>/dev/null
      printf "\x$tmp2" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=49 2>/dev/null
      printf "\x$tmp3" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=50 2>/dev/null
      printf "\x$tmp4" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=51 2>/dev/null
      break
    fi

    if [ "$loader_spi_frequency_var" == "" 2>/dev/null ] && [ "$spi_2nd_limit_var" == "8" 2>/dev/null ];then
      echo "[HIMAX] Set SPI frequency as "$spi_2nd_limit_var"MHz finished!"
      printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=56 2>/dev/null
      printf "\x12" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=57 2>/dev/null
      printf "\x7A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=58 2>/dev/null
      printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=59 2>/dev/null
      break
    elif [ "$loader_spi_frequency_var" == "" 2>/dev/null ] && [ "$spi_2nd_limit_var" == "50" 2>/dev/null ];then
      echo "[HIMAX] Set SPI frequency as "$spi_2nd_limit_var"MHz finished!"
      printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=56 2>/dev/null
      printf "\xF0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=57 2>/dev/null
      printf "\xFA" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=58 2>/dev/null
      printf "\x02" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=59 2>/dev/null
      break
    else
      echo "[HIMAX] [ERROR] Your input "$loader_spi_frequency_var" error, should be 0~$spi_2nd_limit_var MHz"
    fi
  done
  echo "[HIMAX] "
  funcn_second_load_config_list
}


funcn_1st_rc36_set_pll_setting(){
  if [ "$1" == "400MHz" ]; then
    printf "\x04" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=16 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=17 2>/dev/null
    printf "\x61" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=18 2>/dev/null
    printf "\x38" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=19 2>/dev/null
    printf "\x8D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=20 2>/dev/null
    printf "\x08" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=21 2>/dev/null
    printf "\xB6" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=22 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=23 2>/dev/null
    printf "\x16" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=24 2>/dev/null
    printf "\x2D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=25 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=26 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=27 2>/dev/null
    printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=28 2>/dev/null
    printf "\x0E" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=29 2>/dev/null
    printf "\x66" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=30 2>/dev/null
    printf "\xD0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=31 2>/dev/null
    printf "\xE9" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=32 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=33 2>/dev/null
    printf "\x51" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=34 2>/dev/null
    printf "\x03" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=35 2>/dev/null
    printf "\x8E" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=36 2>/dev/null
    printf "\x2A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=37 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=38 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=39 2>/dev/null
    printf "\xFE" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=40 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=41 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=42 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=43 2>/dev/null
  else
    printf "\x04" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=16 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=17 2>/dev/null
    printf "\x61" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=18 2>/dev/null
    printf "\x38" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=19 2>/dev/null
    printf "\x8D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=20 2>/dev/null
    printf "\x08" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=21 2>/dev/null
    printf "\xB6" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=22 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=23 2>/dev/null
    printf "\x16" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=24 2>/dev/null
    printf "\x22" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=25 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=26 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=27 2>/dev/null
    printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=28 2>/dev/null
    printf "\x0A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=29 2>/dev/null
    printf "\xE1" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=30 2>/dev/null
    printf "\xD0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=31 2>/dev/null
    printf "\xE4" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=32 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=33 2>/dev/null
    printf "\x3D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=34 2>/dev/null
    printf "\x02" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=35 2>/dev/null
    printf "\xAB" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=36 2>/dev/null
    printf "\x2A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=37 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=38 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=39 2>/dev/null
    printf "\xFE" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=40 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=41 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=42 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=43 2>/dev/null
  fi
}


funcn_2nd_rc36_set_pll_setting(){
  if [ "$1" == "400MHz" ]; then
    printf "\x04" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=64 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=65 2>/dev/null
    printf "\x61" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=66 2>/dev/null
    printf "\x38" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=67 2>/dev/null
    printf "\x8D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=68 2>/dev/null
    printf "\x08" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=69 2>/dev/null
    printf "\xB6" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=70 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=71 2>/dev/null
    printf "\x16" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=72 2>/dev/null
    printf "\x2D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=73 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=74 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=75 2>/dev/null
    printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=76 2>/dev/null
    printf "\x0E" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=77 2>/dev/null
    printf "\x66" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=78 2>/dev/null
    printf "\xD0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=79 2>/dev/null
    printf "\xE9" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=80 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=81 2>/dev/null
    printf "\x51" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=82 2>/dev/null
    printf "\x03" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=83 2>/dev/null
    printf "\x8E" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=84 2>/dev/null
    printf "\x2A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=85 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=86 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=87 2>/dev/null
    printf "\xFE" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=88 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=89 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=90 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=91 2>/dev/null
  else
    printf "\x04" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=64 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=65 2>/dev/null
    printf "\x61" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=66 2>/dev/null
    printf "\x38" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=67 2>/dev/null
    printf "\x8D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=68 2>/dev/null
    printf "\x08" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=69 2>/dev/null
    printf "\xB6" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=70 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=71 2>/dev/null
    printf "\x16" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=72 2>/dev/null
    printf "\x22" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=73 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=74 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=75 2>/dev/null
    printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=76 2>/dev/null
    printf "\x0A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=77 2>/dev/null
    printf "\xE1" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=78 2>/dev/null
    printf "\xD0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=79 2>/dev/null
    printf "\xE4" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=80 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=81 2>/dev/null
    printf "\x3D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=82 2>/dev/null
    printf "\x02" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=83 2>/dev/null
    printf "\xAB" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=84 2>/dev/null
    printf "\x2A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=85 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=86 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=87 2>/dev/null
    printf "\xFE" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=88 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=89 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=90 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=91 2>/dev/null
  fi
}


funcn_1st_xtal24_set_pll_setting(){
  if [ "$1" == "400MHz" ]; then
    printf "\x03" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=16 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=17 2>/dev/null
    printf "\x61" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=18 2>/dev/null
    printf "\x38" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=19 2>/dev/null
    printf "\x8D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=20 2>/dev/null
    printf "\x08" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=21 2>/dev/null
    printf "\xB6" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=22 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=23 2>/dev/null
    printf "\x16" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=24 2>/dev/null
    printf "\x32" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=25 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=26 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=27 2>/dev/null
    printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=28 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=29 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=30 2>/dev/null
    printf "\xD0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=31 2>/dev/null
    printf "\x66" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=32 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=33 2>/dev/null
    printf "\x66" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=34 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=35 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=36 2>/dev/null
    printf "\x2A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=37 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=38 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=39 2>/dev/null
    printf "\xFE" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=40 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=41 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=42 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=43 2>/dev/null
  elif [ "$1" == "300MHz" ]; then
    printf "\x48" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=16 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=17 2>/dev/null
    printf "\x34" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=18 2>/dev/null
    printf "\xEB" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=19 2>/dev/null
    printf "\x8D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=20 2>/dev/null
    printf "\x08" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=21 2>/dev/null
    printf "\xB6" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=22 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=23 2>/dev/null
    printf "\x16" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=24 2>/dev/null
    printf "\x64" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=25 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=26 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=27 2>/dev/null
    printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=28 2>/dev/null
    printf "\x0C" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=29 2>/dev/null
    printf "\x29" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=30 2>/dev/null
    printf "\xD0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=31 2>/dev/null
    printf "\xD3" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=32 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=33 2>/dev/null
    printf "\x4D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=34 2>/dev/null
    printf "\x04" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=35 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=36 2>/dev/null
    printf "\x2A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=37 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=38 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=39 2>/dev/null
    printf "\xFE" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=40 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=41 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=42 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=43 2>/dev/null
  else
    printf "\x02" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=16 2>/dev/null
    printf "\x68" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=17 2>/dev/null
    printf "\x61" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=18 2>/dev/null
    printf "\x38" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=19 2>/dev/null
    printf "\x8D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=20 2>/dev/null
    printf "\x08" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=21 2>/dev/null
    printf "\xB6" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=22 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=23 2>/dev/null
    printf "\x16" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=24 2>/dev/null
    printf "\x20" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=25 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=26 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=27 2>/dev/null
    printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=28 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=29 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=30 2>/dev/null
    printf "\xD0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=31 2>/dev/null
    printf "\x66" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=32 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=33 2>/dev/null
    printf "\x66" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=34 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=35 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=36 2>/dev/null
    printf "\x2A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=37 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=38 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=39 2>/dev/null
    printf "\xFE" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=40 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=41 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=42 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=43 2>/dev/null
  fi
}


funcn_2nd_xtal24_set_pll_setting(){
  if [ "$1" == "400MHz" ]; then
    printf "\x03" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=64 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=65 2>/dev/null
    printf "\x61" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=66 2>/dev/null
    printf "\x38" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=67 2>/dev/null
    printf "\x8D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=68 2>/dev/null
    printf "\x08" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=69 2>/dev/null
    printf "\xB6" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=70 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=71 2>/dev/null
    printf "\x16" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=72 2>/dev/null
    printf "\x32" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=73 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=74 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=75 2>/dev/null
    printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=76 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=77 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=78 2>/dev/null
    printf "\xD0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=79 2>/dev/null
    printf "\x66" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=80 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=81 2>/dev/null
    printf "\x66" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=82 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=83 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=84 2>/dev/null
    printf "\x2A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=85 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=86 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=87 2>/dev/null
    printf "\xFE" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=88 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=89 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=90 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=91 2>/dev/null
  elif [ "$1" == "300MHz" ]; then
    printf "\x48" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=64 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=65 2>/dev/null
    printf "\x34" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=66 2>/dev/null
    printf "\xEB" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=67 2>/dev/null
    printf "\x8D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=68 2>/dev/null
    printf "\x08" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=69 2>/dev/null
    printf "\xB6" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=70 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=71 2>/dev/null
    printf "\x16" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=72 2>/dev/null
    printf "\x64" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=73 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=74 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=75 2>/dev/null
    printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=76 2>/dev/null
    printf "\x0C" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=77 2>/dev/null
    printf "\x29" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=78 2>/dev/null
    printf "\xD0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=79 2>/dev/null
    printf "\xD3" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=80 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=81 2>/dev/null
    printf "\x4D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=82 2>/dev/null
    printf "\x04" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=83 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=84 2>/dev/null
    printf "\x2A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=85 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=86 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=87 2>/dev/null
    printf "\xFE" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=88 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=89 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=90 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=91 2>/dev/null
  else
    printf "\x02" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=64 2>/dev/null
    printf "\x68" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=65 2>/dev/null
    printf "\x61" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=66 2>/dev/null
    printf "\x38" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=67 2>/dev/null
    printf "\x8D" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=68 2>/dev/null
    printf "\x08" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=69 2>/dev/null
    printf "\xB6" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=70 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=71 2>/dev/null
    printf "\x16" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=72 2>/dev/null
    printf "\x20" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=73 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=74 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=75 2>/dev/null
    printf "\x80" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=76 2>/dev/null
    printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=77 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=78 2>/dev/null
    printf "\xD0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=79 2>/dev/null
    printf "\x66" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=80 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=81 2>/dev/null
    printf "\x66" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=82 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=83 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=84 2>/dev/null
    printf "\x2A" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=85 2>/dev/null
    printf "\xC0" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=86 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=87 2>/dev/null
    printf "\xFE" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=88 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=89 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=90 2>/dev/null
    printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=91 2>/dev/null
  fi
}


funcn_second_load_config_list(){
  echo "[HIMAX] ---------------------- Second Boot Loader List ------------------ "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/boot_loader/second_bootloader.ini

  while read -p "[HIMAX] Please select loader config: " second_loader_config_var
  do
    echo "[HIMAX]"
    if [ $second_loader_config_var -gt 0 2>/dev/null ] && [ $second_loader_config_var -le $count 2>/dev/null ]; then
      second_loader_config_name=$(sed -n "$second_loader_config_var"p ${img_gen_path}/ini_folder/boot_loader/second_bootloader.ini)
      echo "[HIMAX] Your selection is $second_loader_config_name "
      echo "[HIMAX] "
      if [ "$second_loader_config_var" == "1" ]; then
        funcn_second_ota_method_list
      elif  [ "$second_loader_config_var" == "2" ]; then
        funcn_loader_re_encryption_list 2nd
      elif  [ "$second_loader_config_var" == "3" ]; then
        funcn_loader_clock_source_list 2nd
      elif  [ "$second_loader_config_var" == "4" ]; then
        func_second_console_baud_rate_list
      elif  [ "$second_loader_config_var" == "5" ]; then
        clear
        funcn_load_config_list
      fi
      break
    else
      echo "[HIMAX] Your selection \"$second_loader_config_var\" is not on the list! Please check and try again!"
    fi
  done
  funcn_menu_list
}


funcn_second_ota_method_list(){
  echo "[HIMAX] ----------------- 2nd Boot Loader OTA Method List --------------- "
  count=0
  while read line 
  do
    count=$[$count + 1]
    printf "[HIMAX] $count. %s \n" "$line"
  done < ${img_gen_path}/ini_folder/boot_loader/second_ota_method.ini

  while read -p "[HIMAX] Please select one option: " second_loader_ota_method_var
  do
    echo "[HIMAX]"
    if [ $second_loader_ota_method_var -gt 0 2>/dev/null ] && [ $second_loader_ota_method_var -le $count 2>/dev/null ]; then
      first_uart_print_name=$(sed -n "$second_loader_ota_method_var"p ${img_gen_path}/ini_folder/boot_loader/second_ota_method.ini)
      echo "[HIMAX] Your selection is $first_uart_print_name "
      echo "[HIMAX] "
      if [ "$second_loader_ota_method_var" == "1" ]; then
        printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=44 2>/dev/null
      elif  [ "$second_loader_ota_method_var" == "2" ]; then
        printf "\x01" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=44 2>/dev/null
        func_second_cmd_baud_rate_list
      fi
      break
    else 
      echo "[HIMAX] Your selection \"$second_loader_ota_method_var\" is not on the list! Please check and try again!"
    fi
  done
  funcn_second_load_config_list
}


func_second_cmd_baud_rate_list(){
  echo "[HIMAX] ------------- 2nd Boot Loader OTA CMD Baud Rate Setting --------- "

  while read -p "[HIMAX] Please enter OTA cmd baud rate (or press ENTER to use default: 921600): " second_loader_ota_cmd_baud_rate_var
  do
    echo "[HIMAX]"
    if [ $second_loader_ota_cmd_baud_rate_var -gt 0 2>/dev/null ] && [ $second_loader_ota_cmd_baud_rate_var -le 921600 2>/dev/null ] && [ "$second_loader_ota_cmd_baud_rate_var" != "" 2>/dev/null ]; then
      echo "[HIMAX] Set OTA command baud rate "$second_loader_ota_cmd_baud_rate_var" finished!"
      echo "[HIMAX] "
      second_loader_ota_cmd_baud_rate_var_hex=$(printf '%x\n' $second_loader_ota_cmd_baud_rate_var)
      tmp1=$(printf '%x\n' $((0x$second_loader_ota_cmd_baud_rate_var_hex & 0xff)))

      second_loader_ota_cmd_baud_rate_var_hex=$((0x$second_loader_ota_cmd_baud_rate_var_hex >> 8))
      second_loader_ota_cmd_baud_rate_var_hex_2=$(printf '%x\n' $second_loader_ota_cmd_baud_rate_var_hex)
      tmp2=$(printf '%x\n' $((0x$second_loader_ota_cmd_baud_rate_var_hex_2 & 0xff)))

      second_loader_ota_cmd_baud_rate_var_hex_2=$((0x$second_loader_ota_cmd_baud_rate_var_hex_2 >> 8))
      second_loader_ota_cmd_baud_rate_var_hex_3=$(printf '%x\n' $second_loader_ota_cmd_baud_rate_var_hex_2)
      tmp3=$(printf '%x\n' $((0x$second_loader_ota_cmd_baud_rate_var_hex_3 & 0xff)))

      second_loader_ota_cmd_baud_rate_var_hex_3=$((0x$second_loader_ota_cmd_baud_rate_var_hex_3 >> 8))
      second_loader_ota_cmd_baud_rate_var_hex_4=$(printf '%x\n' $second_loader_ota_cmd_baud_rate_var_hex_3)
      tmp4=$(printf '%x\n' $((0x$second_loader_ota_cmd_baud_rate_var_hex_4 & 0xff)))

      #echo $tmp1, $tmp2, $tmp3, $tmp4
      printf "\x$tmp1" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=52 2>/dev/null
      printf "\x$tmp2" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=53 2>/dev/null
      printf "\x$tmp3" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=54 2>/dev/null
      printf "\x$tmp4" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=55 2>/dev/null
      break
    fi

    if [ "$second_loader_ota_cmd_baud_rate_var" == "" 2>/dev/null ]; then
      printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=52 2>/dev/null
      printf "\x10" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=53 2>/dev/null
      printf "\x0E" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=54 2>/dev/null
      printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=55 2>/dev/null
    else 
      echo "[HIMAX] [ERROR] Your input "$second_loader_ota_cmd_baud_rate_var" error, should be 0~921600"
    fi
  done
  funcn_second_load_config_list
}


func_second_console_baud_rate_list(){
  echo "[HIMAX] ------------- 2nd Boot Loader Consloe Baud Rate Setting --------- "

  while read -p "[HIMAX] Please enter OTA cmd baud rate (or press ENTER to use default: 115200): " second_loader_console_baud_rate_var
  do
    echo "[HIMAX]"
    if [ $second_loader_console_baud_rate_var -gt 0 2>/dev/null ] && [ $second_loader_console_baud_rate_var -le 921600 2>/dev/null ] && [ "$second_loader_console_baud_rate_var" != "" 2>/dev/null ]; then
      echo "[HIMAX] Set OTA command baud rate "$second_loader_console_baud_rate_var" finished!"
      echo "[HIMAX] "
      second_loader_console_baud_rate_var_hex=$(printf '%x\n' $second_loader_console_baud_rate_var)
      tmp1=$(printf '%x\n' $((0x$second_loader_console_baud_rate_var_hex & 0xff)))

      second_loader_console_baud_rate_var_hex=$((0x$second_loader_console_baud_rate_var_hex >> 8))
      second_loader_console_baud_rate_var_hex_2=$(printf '%x\n' $second_loader_console_baud_rate_var_hex)
      tmp2=$(printf '%x\n' $((0x$second_loader_console_baud_rate_var_hex_2 & 0xff)))

      second_loader_console_baud_rate_var_hex_2=$((0x$second_loader_console_baud_rate_var_hex_2 >> 8))
      second_loader_console_baud_rate_var_hex_3=$(printf '%x\n' $second_loader_console_baud_rate_var_hex_2)
      tmp3=$(printf '%x\n' $((0x$second_loader_console_baud_rate_var_hex_3 & 0xff)))

      second_loader_console_baud_rate_var_hex_3=$((0x$second_loader_console_baud_rate_var_hex_3 >> 8))
      second_loader_console_baud_rate_var_hex_4=$(printf '%x\n' $second_loader_console_baud_rate_var_hex_3)
      tmp4=$(printf '%x\n' $((0x$second_loader_console_baud_rate_var_hex_4 & 0xff)))

      #echo $tmp1, $tmp2, $tmp3, $tmp4
      printf "\x$tmp1" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=48 2>/dev/null
      printf "\x$tmp2" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=49 2>/dev/null
      printf "\x$tmp3" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=50 2>/dev/null
      printf "\x$tmp4" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc seek=51 2>/dev/null
      break
    fi

    if [ "$second_loader_ota_cmd_baud_rate_var" == "" 2>/dev/null ]; then
      printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=48 2>/dev/null
      printf "\xC2" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=49 2>/dev/null
      printf "\x01" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=50 2>/dev/null
      printf "\x00" | dd of=${img_gen_path}/input/Loader_config.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=51 2>/dev/null
    else 
      echo "[HIMAX] [ERROR] Your input "$second_loader_ota_cmd_baud_rate_var" error, should be 0~921600"
    fi
  done
  funcn_second_load_config_list
}


### Start ###
chpi_name_var_name=$(awk -F '=' '/\['Package_Setting'\]/{a=1}a==1&&$1~/'tmp_chip_name'/{print $2}' $GNU_INI_TMP_PATH)
#chpi_name_var_name=$(awk -F "=" '/tmp_chip_name/ {print $2}' ini_folder/tmp_gnu.ini)
ini_sec_format=$(awk -F '=' '/\['Package_Setting'\]/{a=1}a==1&&$1~/'sec_format_name'/{print $2}' $GNU_INI_TMP_PATH)
#ini_sec_format=$(awk -F "=" '/sec_format_name/ {print $2}' ini_folder/tmp_gnu.ini)
secure_file_name_var=$(awk -F '=' '/\['Package_Setting'\]/{a=1}a==1&&$1~/'ini_sign_forma'/{print $2}' $GNU_INI_TMP_PATH)
#secure_file_name_var=$(awk -F "=" '/ini_sign_forma/ {print $2}' ini_folder/tmp_gnu.ini)
ini_flash_size=$(awk -F '=' '/\['Package_Setting'\]/{a=1}a==1&&$1~/'ini_flash_size'/{print $2}' $GNU_INI_TMP_PATH)
#ini_flash_size=$(awk -F "=" '/ini_flash_size/ {print $2}' ini_folder/tmp_gnu.ini)
ini_part_name=$(awk -F '=' '/\['Package_Setting'\]/{a=1}a==1&&$1~/'part_number_name'/{print $2}' $GNU_INI_TMP_PATH)
#ini_part_name=$(awk -F "=" '/part_number_name/ {print $2}' ini_folder/tmp_gnu.ini)
# Note. tmp_gnu.ini file should be unix format
# Step.1 vi "FILE_NAME"
# Step.2 :set ff=unix
# Step.3 :wq!


#printf "\xee" | dd of=${img_gen_path}/input/tmp.bin bs=1 count=1 conv=notrunc bs=1 count=1 seek=46
funcn_menu_list
