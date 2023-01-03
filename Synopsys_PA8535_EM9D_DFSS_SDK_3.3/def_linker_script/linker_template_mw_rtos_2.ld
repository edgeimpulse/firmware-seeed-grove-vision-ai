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
  SYSTEM0 : ORIGIN = EXT_RAM_APPDATA_START, LENGTH = 0xFCE70
#endif

    XCCM    : ORIGIN = 0x90000000, LENGTH = 0x00008000
    YCCM    : ORIGIN = 0xa0000000, LENGTH = 0x00008000

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
			*(.vector)
			_e_vector = .;
		}
	} > ICCM1

	GROUP : {

		.text ALIGN(4): {
			_f_text = .;
			*(TYPE text)
			_e_text = .;
		}
 	} > ICCM1

	GROUP : {
         _f_bss2 = .;
        .ds_wk_m ? ALIGN(4): {}
         _e_bss2 = .;
 	} > DCCM

 	GROUP : {
         _f_bss3 = .;
        .fr_bk_m ?ALIGN(8): {}
         _e_bss3 = .;
 	} > DCCM


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
	} > SYSTEM0

	GROUP (NOLOAD) : {
		.bss ALIGN(8): {
			_f_bss = .;
			*(TYPE bss)
			_e_bss = .;
		}
	} > SYSTEM0

    GROUP : {
        .heap? ALIGN(8) SIZE(_HEAPSIZE): {}
    } > SYSTEM0

    GROUP : {
        .stack ALIGN(8) SIZE(_STACKSIZE): {}
    } >DCCM

	_f_stack = ADDR(.stack);
	_e_stack = ADDR(.stack) + SIZEOF(.stack);
	_f_heap = ADDR(.heap);
	_e_heap = ADDR(.heap) + SIZEOF(.heap);

	_load_addr_text = LOADADDR(.text);
	_load_addr_rodata = LOADADDR(.rodata);
	_load_addr_data = LOADADDR(.data);
}
