#!/bin/bash

#rm image_gen_config.ini 2>/dev/null

img_gen_path=$(dirname $0)

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
  cat > ${img_gen_path}/image_gen_config.ini <<EOF
  [PROJECT_BASE]
  flash_max_size = $ini_flash_size
  oupt_file = output\output.img
  odm_wrapkey = odm_key\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_part_name}\odm_wrapkey.key
  pubkey = odm_key\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_part_name}\we1_root_rsa_key.der.pub
  prikey = odm_key\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_part_name}\odm_rsa_key.der
  cert = odm_key\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_part_name}\cert1_rsa.bin
  devision_size_limit = FB00  
  chip_name = ${temp}
  config_mode = ${ini_config_mode}
  part_number = ${ini_part_name}

  [BOOTLOADER]
  pat_type = 0
  input_file = input\\${ini_sec_format}\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_sec_format}_${ini_part_name}\\${secure_file_name_var}_PA8530_EM9D_Bootloader.bin
  sec_format = $ini_sec_format
  version = 2
  fw_type = 1
  flash_addr = 10000

  [2ND_BOOTLOADER]
  pat_type = 1
  input_file = input\\${ini_sec_format}\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_sec_format}_${ini_part_name}\\${secure_file_name_var}_PA8530_EM9D_2nd_Bootloader.bin
  sec_format = $ini_sec_format
  version = 2
  fw_type = 1
  flash_addr = 0

  [MEMORY_DESCIRPTOR]
  pat_type = 3
  output_file = output\layout
  sec_format = BLp
  version = 2
  fw_type = 4
  flash_addr = 20000

  [APPLICATION]
  pat_type = 4
  input_file = input\WEI_FW_mw_arcem9d_wei_r16
  sec_format = $ini_sec_format
  version = 2
  fw_type = 3
  flash_addr = 21000
  devision_size = FB00
EOF
}

funcn_amr_gen_ini() {
  cat > ${img_gen_path}/image_gen_config.ini <<EOF
  [PROJECT_BASE]
  flash_max_size = $ini_flash_size
  oupt_file = output\output.img
  odm_wrapkey = odm_key\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_part_name}\odm_wrapkey.key
  pubkey = odm_key\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_part_name}\we1_root_rsa_key.der.pub
  prikey = odm_key\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_part_name}\odm_rsa_key.der
  cert = odm_key\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_part_name}\cert1_rsa.bin
  devision_size_limit = FB00  
  chip_name = ${temp}
  config_mode = ${ini_config_mode}
  part_number = ${ini_part_name}

  [BOOTLOADER]
  pat_type = 0
  input_file = input\\${ini_sec_format}\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_sec_format}_${ini_part_name}\\${secure_file_name_var}_PA8530_EM9D_Bootloader.bin
  sec_format = $ini_sec_format
  version = 2
  fw_type = 1
  flash_addr = 10000

  [2ND_BOOTLOADER]
  pat_type = 1
  input_file = input\\${ini_sec_format}\\${temp}_${ini_sec_format}_${ini_config_mode}\\${ini_sec_format}_${ini_part_name}\\${secure_file_name_var}_PA8530_EM9D_2nd_Bootloader.bin
  sec_format = $ini_sec_format
  version = 2
  fw_type = 1
  flash_addr = 0

  [MEMORY_DESCIRPTOR]
  pat_type = 3
  output_file = output\layout
  sec_format = BLp
  version = 2
  fw_type = 4
  flash_addr = 20000

  [APPLICATION]
  pat_type = 4
  input_file = input\WEI_FW_mw_arcem9d_wei_r16
  sec_format = $ini_sec_format
  version = 2
  fw_type = 3
  flash_addr = 21000
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




### chip_name start ###
echo "[HIMAX] ---------------- Chip Name List --------------- "

count=0

while read line 
do
  count=$[$count + 1]
  printf "[HIMAX] $count. %s \n" "$line"
done < ${img_gen_path}/ini_folder/chip_name.ini

echo -n "[HIMAX] Please select one option: "
read chpi_name_var
case $chpi_name_var in

1)
  echo "[HIMAX] Your selection is WLCSP38 "
  temp=WLCSP38
  part_number_file=part_number_38.ini
  ;;
2)
  echo "[HIMAX] Your selection is QFN72 "
  temp=QFN72
  part_number_file=part_number_72.ini
  ;;
3)
  echo "[HIMAX] Your selection is LQFP128 "
  temp=LQFP128
  part_number_file=part_number_128.ini
  ;;
*)
  echo "[HIMAX] Your selection $chpi_name_var is not on the list! Please check and try again!"
  funcn_fail_print
  exit
  ;;
esac
### chip_name end ###


echo "[HIMAX]"


### config_mode start ###
echo "[HIMAX] ---------------- Config Mode List --------------- "

count=0

while read line
do
  count=$[$count + 1]
  printf "[HIMAX] $count. %s \n" "$line"
done < ${img_gen_path}/ini_folder/config_mode.ini

echo -n "[HIMAX] Please select one option: "
read config_mode_var
case $config_mode_var in

1)
  echo "[HIMAX] Your selection is Debug "
  ini_config_mode=Debug
  ;;
2)
  echo "[HIMAX] Your selection is Release "
  ini_config_mode=Release
  ;;
*)
  echo "[HIMAX] Your selection $config_mode_var is not on the list! Please check and try again!"
  funcn_fail_print
  exit
  ;;
esac
### config_mode end ###


echo "[HIMAX]"


### sec_format start ###
echo "[HIMAX] ---------------- Security Format List --------------- "

count=0

while read line
do
  count=$[$count + 1]
  printf "[HIMAX] $count. %s \n" "$line"
done < ${img_gen_path}/ini_folder/sec_format.ini

echo -n "[HIMAX] Please select one option: "
read sec_format_var
case $sec_format_var in

1)
  echo "[HIMAX] Your selection is BLp "
  ini_sec_format=BLp
  secure_file_name_var=sign_formal
  ;;
2)
  echo "[HIMAX] Your selection is BLw "
  ini_sec_format=BLw
  secure_file_name_var=enc_formal2
  ;;
*)
  echo "[HIMAX] Your selection $sec_format_var is not on the list! Please check and try again!"
  funcn_fail_print
  exit
  ;;
esac
### sec_format end ###


echo "[HIMAX]"


### flash_max_size start ###
echo "[HIMAX] ---------------- Max Flash Size List --------------- "

count=0

while read line
do
  count=$[$count + 1]
  printf "[HIMAX] $count. %s \n" "$line"
done < ${img_gen_path}/ini_folder/flash_max_size.ini

echo -n "[HIMAX] Please select one option: "
read flash_max_size_var
case $flash_max_size_var in

1)
  echo "[HIMAX] Your selection is 1M "
  ini_flash_size=0x100000
  ;;
2)
  echo "[HIMAX] Your selection is 2M "
  ini_flash_size=0x200000
  ;;
*)
  echo "[HIMAX] Your selection $flash_max_size_var is not on the list! Please check and try again!"
  funcn_fail_print
  exit
  ;;
esac
### flash_max_size end ###


echo "[HIMAX]"


### part_number start ###
echo "[HIMAX] ---------------- $temp Part Number List --------------- "

count=0

while read line
do
  count=$[$count + 1]
  printf "[HIMAX] $count. %s \n" "$line"
done < ${img_gen_path}/ini_folder/part_number/$part_number_file

echo -n "[HIMAX] Please select one option: "
read flash_max_size_var

if [ $flash_max_size_var -gt 0 2>/dev/null ] && [ $flash_max_size_var -le $count 2>/dev/null ]
then
  echo -n "[HIMAX] Your selection is " 
  head -$flash_max_size_var ${img_gen_path}/ini_folder/part_number/$part_number_file | tail +$flash_max_size_var
  ini_part_name=$(head -$flash_max_size_var ${img_gen_path}/ini_folder/part_number/$part_number_file | tail +$flash_max_size_var)
else
  echo "[HIMAX] Your selection $flash_max_size_var is not on the list! Please check and try again!"
  funcn_fail_print
  exit 
fi
### part_number end ###


echo "[HIMAX]"


### AMR option start ###
while [ "${amr_user_input}" != "y" -a "${amr_user_input}" != "Y" -a "${amr_user_input}" != "n" -a "${amr_user_input}" != "N" ]
do
  read -p "[HIMAX] Setup AMR options: [Y,N]?" amr_user_input
done

if [ $amr_user_input == "y" 2>/dev/null ] || [ $amr_user_input == "Y" 2>/dev/null ]
then
  echo "[HIMAX] ---------------- AMR Options List --------------- "
  read -p "[HIMAX] Please enter AMR configuration input file (or press ENTER to use default: input\wr_config.bin): " amr_cfg_input_file
  if [ "$amr_cfg_input_file" == "" 2>/dev/null ]
  then
	amr_cfg_input_file=input\\wr_config.bin
  fi
  
  echo "[HIMAX]"
  
  if [ ! -f "${img_gen_path}/${amr_cfg_input_file}" ]; then
    echo "[HIMAX] [WARNING] User input \"$amr_cfg_input_file\" is not exist, using default path \"input\wr_config.bin\""
	amr_cfg_input_file=input\\wr_config.bin
  fi
  
  read -p "[HIMAX] Please enter AMR configuration flash address (or press ENTER to use default: C0000): " amr_cfg_flash_addr
  if [ "$amr_cfg_flash_addr" == "" 2>/dev/null ]
  then
	amr_cfg_flash_addr=C0000
  fi
  
  echo "[HIMAX]"
  
  read -p "[HIMAX] Please enter AMR model input file (or press ENTER to use default: input\AMR.tflite): " amr_model_input_file
  if [ "$amr_model_input_file" == "" 2>/dev/null ]
  then
	amr_model_input_file=input\\AMR.tflite
  fi
  
  echo "[HIMAX]"
  
  if [ ! -f "${img_gen_path}/${amr_model_input_file}" ]; then
    echo "[HIMAX] [WARNING] User input \"$amr_model_input_file\" is not exist, using default path \"input\AMR.tflite\""
	amr_model_input_file=input\\AMR.tflite
  fi
  
  echo "[HIMAX]"
  
  read -p "[HIMAX] Please enter AMR model flash address (or press ENTER to use default: D0000): " amr_model_flash_addr
  if [ "$amr_model_flash_addr" == "" 2>/dev/null ]
  then
	amr_model_flash_addr=D0000
  fi
  
  funcn_amr_gen_ini
elif [ $amr_user_input == "n" 2>/dev/null ] || [ $amr_user_input == "N" 2>/dev/null ]
then
  funcn_normal_gen_ini
fi
### AMR option end ###

echo "[HIMAX]"
echo "[HIMAX]"
echo "[HIMAX] *********************************************** "
echo "[HIMAX] ******************* Success ******************* "
echo "[HIMAX] *********************************************** "
echo "[HIMAX] ***                                         *** "
echo "[HIMAX] ***     image_gen_config.ini generated      *** "
echo "[HIMAX] ***                                         *** "
echo "[HIMAX] *********************************************** "
echo "[HIMAX] ******************* Success ******************* "
echo "[HIMAX] *********************************************** "
echo "[HIMAX]"
