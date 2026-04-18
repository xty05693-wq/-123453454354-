extern "C" void kernel_main() {
    volatile unsigned short* video = (unsigned short*)0xB8000;
    const char* msg = "PythonOS is alive!";
    for (int i = 0; i < 80*25; ++i) video[i] = 0x0720;
    for (int i = 0; msg[i]; ++i) video[i] = (0x0A << 8) | msg[i];
    while(1) __asm__("hlt");
}
