int main()
{
    __asm__ __volatile__ (".private_extern dummy_symbol \n"
        ".private_extern _dummy_symbol \n"
        ".globl dummy_symbol \n"
        ".globl _dummy_symbol \n"
        "dummy_symbol: \n"
        "_dummy_symbol: \n"
        "    nop \n"
        );

    return 0;
}