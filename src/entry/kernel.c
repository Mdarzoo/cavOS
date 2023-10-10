#include "../../include/allocation.h"
#include "../../include/ata.h"
#include "../../include/disk.h"
#include "../../include/fat32.h"
#include "../../include/idt.h"
#include "../../include/isr.h"
#include "../../include/kb.h"
#include "../../include/multiboot.h"
#include "../../include/pmm.h"
#include "../../include/rtc.h"
#include "../../include/shell.h"
#include "../../include/testing.h"
#include "../../include/util.h"
#include "../../include/vga.h"

#include <stdint.h>

// Kernel entry file
// Copyright (C) 2023 Panagiotis

int kmain(uint32 magic, multiboot_info_t *mbi) {
  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    printf("invalid magic number!");
    asm("hlt");
  }

  if (!(mbi->flags >> 6 & 0x1)) {
    printf("invalid memory map given by GRUB bootloader");
    asm("hlt");
  }

  // pmmTesting(mbi);

  clearScreen();

  string center = "                   ";
  debugf("====== DEBUGGING LOGS ======\n\n");
  printf("%s=========================================%s\n", center, center);
  printf("%s==     Cave-Like Operating System      ==%s\n", center, center);
  printf("%s==      Copyright MalwarePad 2023      ==%s\n", center, center);
  printf("%s=========================================%s\n\n", center, center);

  isr_install();
  init_memory(mbi);
  initiateFat32();

  testingInit(mbi);

  printf("\n");

  launch_shell(0, mbi);
}
