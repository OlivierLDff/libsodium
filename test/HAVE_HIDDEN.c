void main()
{
    __asm__ __volatile__ (".hidden dummy_symbol \n"
        ".hidden _dummy_symbol \n"
        ".globl dummy_symbol \n"
        ".globl _dummy_symbol \n"
        "dummy_symbol: \n"
        "_dummy_symbol: \n"
        "    nop \n"
        );
}