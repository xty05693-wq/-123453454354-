// Multiboot-совместимое ядро PythonOS
asm (
    ".section .multiboot\n\t"
    ".align 4\n\t"
    ".long 0x1BADB002\n\t"          // magic
    ".long 0x00000003\n\t"          // flags
    ".long -(0x1BADB002 + 0x00000003)\n\t" // checksum
    ".section .text\n\t"
);

extern "C" void kernel_main() {
    volatile unsigned short* video = (unsigned short*)0xB8000;
    const char* msg = "PythonOS is alive!";
    for (int i = 0; i < 80 * 25; ++i) video[i] = 0x0720;
    for (int i = 0; msg[i]; ++i) video[i] = (0x0A << 8) | msg[i];
    while (1) __asm__("hlt");
}
