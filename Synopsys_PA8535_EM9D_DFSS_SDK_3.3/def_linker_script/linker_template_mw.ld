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

  GROUP (NOLOAD) : {
    .heap? ALIGN(8) SIZE(_HEAPSIZE): {}
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