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
  SYSTEM0 : ORIGIN = EXT_RAM_APPDATA_START, LENGTH = (0x2011d650 - EXT_RAM_APPDATA_START)
#endif
  VERSION : ORIGIN = 0x2011d650, LENGTH = (0x2011d670 - 0x2011d650)
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
	} > SYSTEM0

	GROUP (NOLOAD) : {
		.bss ALIGN(8): {
			_f_bss = .;
			*(TYPE bss)
			_e_bss = .;
		}
	} > SYSTEM0

	GROUP : {
		.sdata ALIGN(8): {
			_f_sdata = .;
			tx_thread_context_restore.o
			tx_thread_context_save.o
			tx_thread_schedule.o
			tx_thread_system_return.o
			tx_timer_interrupt.o
			_e_sdata = .;
			*(TYPE data)
		}
		.data ALIGN(8): {
			_f_data = .;
			*(TYPE data)
		}
		.tls ALIGN(8): {
			*(.tls*)
			_e_data = .;
		}
	} > DCCM

  GROUP (NOLOAD) : {
    .heap? ALIGN(8) SIZE(_HEAPSIZE): {}
    .stack ALIGN(8) SIZE(_STACKSIZE): {}
    .free_memory: {}
  } >DCCM

	GROUP BLOCK(4): {
		.ver? ALIGN(16): {}
	} > VERSION

	_f_stack = ADDR(.stack);
	_e_stack = ADDR(.stack) + SIZEOF(.stack);
	_f_heap = ADDR(.heap);
	_e_heap = ADDR(.heap) + SIZEOF(.heap);
	_f_free_memory = ADDR(.free_memory) + 4;

	_load_addr_text = LOADADDR(.text);
	_load_addr_rodata = LOADADDR(.rodata);
	_load_addr_data = LOADADDR(.data);
}