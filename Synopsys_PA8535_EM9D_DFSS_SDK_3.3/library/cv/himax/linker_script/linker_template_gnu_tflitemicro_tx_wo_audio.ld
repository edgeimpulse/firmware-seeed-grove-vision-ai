/* SYSTEM memory regions indicate where external memory might be located.
   The TCF has no specific knowledge of whether SYSTEM regions contain
   external memory or not.
   CCMWRAP memory regions indicate unusable portions of the address space
   due to CCM memory wrapping into upper addresses beyond its size
*/
#define __ASSEMPLY__
MEMORY {
    ICCM0   : ORIGIN = 0x00000000, LENGTH = 0x00010000
    ICCM1   : ORIGIN = 0x10000000, LENGTH = 0x00050000
    SYSTEM0 : ORIGIN = 0x20010800, LENGTH = (0x2011d650 - 0x20010800)
    VERSION : ORIGIN = 0x2011d650, LENGTH = (0x2011d670 - 0x2011d650)
    DCCM    : ORIGIN = 0x80000000, LENGTH = 0x00040000
    XCCM    : ORIGIN = 0x90000000, LENGTH = 0x00008000
    YCCM    : ORIGIN = 0xa0000000, LENGTH = 0x00008000
}

ENTRY(_arc_reset)

SECTIONS {

    .ivt DEFINED (ivtbase_addr) ? ivtbase_addr : 0x10000004 :
    {
        *(.init_vector)
        *(.init_bootstrap)
    } > ICCM1

    .vector : ALIGN(1024)
    {
        . = ALIGN(1024);
        *(.vector)
    } > ICCM1

    .text           : ALIGN(4)
    {
        . = ALIGN(4);
        PROVIDE (_f_text = .);
        /* Remaining code.  */
        . = ALIGN(4);
        *(.text .stub .text.* .gnu.linkonce.t.*)

        PROVIDE (_e_text = .);
    }  > ICCM1


    .read_only_data   : ALIGN(4)
    {
        PROVIDE (_f_rodata = .);
        *(.rodata) *(.rodata.*) *(.gnu.linkonce.r.*)
        *(.rodata1)

        . = ALIGN(4);
        __CTOR_LIST__ = .;
        LONG((__CTOR_END__ - __CTOR_LIST__) / 4 - 2)
        *(SORT_BY_NAME(".ctors*"))
        LONG(0)
        __CTOR_END__ = .;

        . = ALIGN(4);
        __init_array_start = .;
        *(SORT_BY_NAME(".init_array*"))
        __init_array_end = .;

        . = ALIGN(4);
        __DTOR_LIST__ = .;
        LONG((__DTOR_END__ - __DTOR_LIST__) / 4 - 2)
        *(SORT_BY_NAME(".dtors*"))
        LONG(0)
        __DTOR_END__ = .;

        PROVIDE (_e_rodata = .);
    } > SYSTEM0

    .data	  : ALIGN(4)
    {
        /* Start of the data section image in ROM.  */
        PROVIDE (__data_image = .);
        PROVIDE (__data_start = .) ;
        /* --gc-sections will delete empty .data. This leads to wrong start
        addresses for subsequent sections because -Tdata= from the command
        line will have no effect, see PR13697.  Thus, keep .data  */
        *(.data)
        *(.data.* .gnu.linkonce.d.*)

    }  > SYSTEM0


    /* We want the small data sections together, so single-instruction offsets
        can access them all, and initialized data all before uninitialized, so
        we can shorten the on-disk segment size.  */
    .sdata          : ALIGN(8)
    {
        __SDATA_BEGIN__ = . ;
        _f_sdata = .;
        *(.sdata .sdata.* .gnu.linkonce.s.*)
        _edata  =  .;
        PROVIDE (edata = .);
    }  > SYSTEM0

    .sbss_all           : ALIGN(4)
    {
        PROVIDE (__sbss_start = .);
        PROVIDE (___sbss_start = .);
        *(.sbss .sbss.* .gnu.linkonce.sb.*)
        PROVIDE (__sbss_end = .);
        PROVIDE (___sbss_end = .);

    }  > SYSTEM0


    .bss_all           : ALIGN(4)
    {
        PROVIDE (_f_bss = .) ;
        *(.dynbss)
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
        /* Align here to ensure that the .bss section occupies space up to
            _end.  Align after .bss to ensure correct alignment even if the
            .bss section disappears because there are no input sections.  */
        . = ALIGN(32 / 8);
        _end = .;
        PROVIDE (end = .);

        PROVIDE (_e_bss = .) ;
    }  > SYSTEM0

    .tensor_arena : ALIGN(16)
    {
        _f_bss_tensor_arena = .;
        *(.bss.tensor_arena)
        _e_bss_tensor_arena = .;
    }  > SYSTEM0

    .stack : ALIGN(8)
    {
        __start_stack = . ;
        _f_stack = .;
        . = . + _STACKSIZE;
        _e_stack = .;
        __end_stack = . ;
    } > DCCM

    .heap : ALIGN(8)
    {
        __start_heap = . ;
        _f_heap = .;
        . = . + _HEAPSIZE;
        _e_heap = .;
        __end_heap = . ;
    } > DCCM

    .Zdata : ALIGN(16)
    {
        . = ALIGN(16);
        *(.Zdata*)
        /* PROVIDE (__start_heap = .); */
        /* PROVIDE (_f_heap = .); */
    }  > DCCM

    .Xdata : ALIGN(4)
    {
        *(.Xdata*)
    }  > XCCM

    .Ydata : ALIGN(4)
    {
        *(.Ydata*)
    }  > YCCM

    .ver : ALIGN(16)
    {
        *(.data*)
    }  > VERSION

    /* PROVIDE (__stack_top = (ORIGIN (DCCM) + LENGTH (DCCM) - 1) & -4); */
    /* PROVIDE (__end_heap = ORIGIN (DCCM) + LENGTH (DCCM) - 1); */

    /* PROVIDE (_e_stack = (ORIGIN (DCCM) + LENGTH (DCCM) - 8192) & -4); */
    /* PROVIDE (_e_heap = __end_heap); */
    PROVIDE (_load_addr_text = _f_text);
    PROVIDE (_load_addr_rodata = _f_rodata);


}

