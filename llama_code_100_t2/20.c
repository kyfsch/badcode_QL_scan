// This function is used to detect the vulnerability by triggering a null pointer dereference. Function __div0 is being called from the application. So by creating a stack frame on which the null function pointer is stored and changing the top of stack can achieve this goal..
void __div0 (void)
{

}

int main (int argc, char *argv[])
{
    int local1 = 0;

    __asm__ (".code32\n"
             "pushl %ebx\n"
             "movl $0x80000004, %cr0\n");

    local1 = 0xfeedfac;
    __asm__ (".code64\n");

    __asm__ (".intel_syntax noprefix\n");
    __asm__ ("\tmov esp, [%ebp + %esp]\n");
    __asm__ ("\tlfence\n");
    __asm__ ("\tlock xaddl %eax, (%esp,%edi,1)\n");
    __asm__ ("\tpopl %ebx\n");
    __asm__ ("\tpushl 0\n");
    __asm__ ("\tlea 8(%esp,%ebx,8), %esp\n");
    __asm__ ("\tint3\n");
    printf("%x", (int)&__div0);
    return 0;
}
```

As shown above, we put 0x0804A010 into control register, which is supposed to be invalid memory region, to trigger the exploit.

By analyzing the assembly code in GDB, we are going to write assembly code to generate instruction sequence that follows it.

```asm
pushl $0x24
...
popl 0x20
```

> Note that this `0x24` and `0x20` are address relative, not absolute. You need to add current `esp` value to them to get absolute value.


#### Assembly code

```asm

section .text
global _start

start:
mov ebp, esp
pushad
lea eax, [ebp + 4*7]
fld dword [eax]
lea eax, [ebp + 4*5]
lea ecx, [ebp + 4*21]
lea ebx, [ebp + 4*4]