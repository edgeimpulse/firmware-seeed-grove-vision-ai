#define __ASSEMBLY__
#include <target_mem_config.h>

MEMORY {
#if (ICCM0_SIZE != 0)
	ICCM0 :		ORIGIN = ICCM0_START,	LENGTH = ICCM0_SIZE
#endif
#if (ICCM1_SIZE != 0)
	ICCM1 :		ORIGIN = ICCM1_START,	LENGTH = ICCM1_SIZE
#endif
#if (DCCM_SIZE !=0)
	DCCM :		ORIGIN = DCCM_START,	LENGTH = DCCM_SIZE
#endif
#if (EXT_RAM_SIZE != 0)
	SYSTEM0 : ORIGIN = 0x20010800, LENGTH = (0x2011D650-0x20010800)

#endif
  VERSION : ORIGIN = 0x2011d650, LENGTH = (0x2011d670 - 0x2011d650)
  XCCM :		ORIGIN = 0x90000000,	LENGTH = 32768
  YCCM :		ORIGIN = 0xA0000000,	LENGTH = 32768
#ifdef FLASH_AS_SRAM
  FLASH_SECTOR : ORIGIN = FLASH_SECTOR_START,	LENGTH = 0x00300000
#endif
}

ENTRY(_arc_start)

SECTIONS {

	GROUP : {
		.init_bootstrap:{
			*(.init_vector)
			*(.init_bootstrap)
		}
		.vector ALIGN(1024): {
			_f_vector = .;
			*(.vector .vector.*)
			_e_vector = .;
		}
	} > ICCM1

#ifdef FLASH_AS_SRAM

 	 	GROUP : {
     .rodata ALIGN(4): {
		 #ifdef YOLO_FASTEST_HUMAN_DETECTION
         		yolo_coco.o (TYPE rodata)
         #endif
            }
      } > FLASH_SECTOR
#endif

	GROUP : {

		.text ALIGN(4): {
			_f_text = .;
			*(TYPE text)
			_e_text = .;
		}
	} > ICCM1

	GROUP BLOCK(4): {
		_f_bss_tensor_arena = .;
		.tensor_arena? ALIGN(16): {}
		_e_bss_tensor_arena = .;
	} > SYSTEM0

	GROUP : {
		.rodata  ALIGN(4): {
			_f_rodata = .;
			_fctors = .;
			*(.ctors*)
			_ectors = .;
			_fdtors = .;
			*(.dtors*)
			_edtors = .;
			_feh_frame = .;
			*(.eh_frame*)
			_eeh_frame = .;
			*(TYPE lit)
			_e_rodata = .;
		}
	} > SYSTEM0

	GROUP BLOCK(4): {
		.Xdata? : {}
	} > XCCM
	GROUP BLOCK(4): {
		.Ydata? : {}
	} > YCCM
	GROUP BLOCK(4): {
		.rodata_in_data?:{}
	} > DCCM

	GROUP : {
		.data ALIGN(8): {
			_f_data = .;
			_f_sdata = .;
			*(.sdata)
			_e_sdata = .;
			*(TYPE data)
		}
		.tls ALIGN(8): {
			*(.tls*)
			_e_data = .;
		}
	} > DCCM

	GROUP (NOLOAD) : {
		.bss ALIGN(8): {
			_f_bss = .;
			*(TYPE bss)
			_e_bss = .;
		}
	} > DCCM

	GROUP : {
		.heap? ALIGN(8) SIZE(_HEAPSIZE): {}
	} > SYSTEM0

	GROUP : {
		.sdata?: {}
		.sbss?: {}
		.protobuf?: {}
		.Zdata?: {}
		.stack ALIGN(8) SIZE(_STACKSIZE): {}
	} >DCCM

	GROUP BLOCK(4): {
		.ver? ALIGN(16): {}
	} > VERSION

	_f_stack = ADDR(.stack);
	_e_stack = ADDR(.stack) + SIZEOF(.stack);
	_f_heap = ADDR(.heap);
	_e_heap = ADDR(.heap) + SIZEOF(.heap);

	_load_addr_text = LOADADDR(.text);
	_load_addr_rodata = LOADADDR(.rodata);
	_load_addr_data = LOADADDR(.data);
}