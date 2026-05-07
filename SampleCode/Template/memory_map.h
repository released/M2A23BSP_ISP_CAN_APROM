#ifndef __MEMORY_MAP_H__
#define __MEMORY_MAP_H__

/* Unified flash layout: ISP in LDROM, APP in APROM */
#define APROM_BASE_ADDR                  (0x00000000UL)
#define APROM_SIZE_BYTES                 (0x00010000UL)

#define APP_START_ADDR                   (APROM_BASE_ADDR)
#define APP_SIZE_BYTES                   (APROM_SIZE_BYTES)
#define APP_END_ADDR                     (APP_START_ADDR + APP_SIZE_BYTES)
#define APP_CHECKSUM_ADDR                (APP_END_ADDR - 4UL)

#define APP_SRAM_SIZE                    (0x00006000UL)

#endif /* __MEMORY_MAP_H__ */
