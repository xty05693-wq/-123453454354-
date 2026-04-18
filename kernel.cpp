// kernel.cpp
// Multiboot-совместимое ядро для PythonOS

#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_HEADER_FLAGS 0x00000003
#define MULTIBOOT_HEADER_CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

// Заглушка для Multiboot заголовка (должна быть в секции .multiboot)
asm (
    ".section .multiboot\n\t"
    ".align 4\n\t"
    ".long 0x1BADB002\n\t"          // magic
    ".long 0x00000003\n\t"          // flags
    ".long -(0x1BADB002 + 0x00000003)\n\t" // checksum
    ".section .text\n\t"
);

extern "C" void kernel_main() {
    // Видеопамять VGA (0xB8000)
    volatile unsigned short* video = (unsigned short*)0xB8000;
    const char* msg = "PythonOS booted via GRUB!";

    // Очистка экрана (серый текст на чёрном фоне)
    for (int i = 0; i < 80 * 25; ++i) {
        video[i] = 0x0720;
    }

    // Вывод сообщения (зелёный цвет)
    for (int i = 0; msg[i] != '\0'; ++i) {
        video[i] = (0x0A << 8) | msg[i];
    }

    while (1) { asm volatile ("hlt"); }
}