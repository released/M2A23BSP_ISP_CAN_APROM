/**************************************************************************//**
 * @file     fmc_reg.h
 * @version  V3.00
 * @brief    FMC register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __FMC_REG_H__
#define __FMC_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup FMC Flash Memory Controller (FMC)
    Memory Mapped Structure for FMC Controller
@{ */

typedef struct
{
    /**
     * @var FMC_T::ISPCTL
     * Offset: 0x00  ISP Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ISPEN     |ISP Enable Bit (Write Protect)
     * |        |          |0 = ISP function Disabled.
     * |        |          |1 = ISP function Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[1]     |BS        |Boot Selection (Write Protect)
     * |        |          |Set/clear this bit to select next booting from LDROM/APROM, respectively.
     * |        |          |This bit also functions as chip booting status flag, which can be used to check where chip booted from.
     * |        |          |This bit is initiated with the inverse value of CBS[1] (CONFIG0[7]) after any reset is happened except CPU reset or system reset is happened.
     * |        |          |0 = Booting from APROM.
     * |        |          |1 = Booting from LDROM.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[2]     |SPUEN     |SPROM Update Enable Bit (Write Protect)
     * |        |          |0 = SPROM cannot be updated.
     * |        |          |1 = SPROM can be updated.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[3]     |APUEN     |APROM Update Enable Bit (Write Protect)
     * |        |          |0 = APROM cannot be updated when the chip runs in APROM.
     * |        |          |1 = APROM can be updated when the chip runs in APROM.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[4]     |CFGUEN    |CONFIG Update Enable Bit (Write Protect)
     * |        |          |0 = CONFIG cannot be updated.
     * |        |          |1 = CONFIG can be updated.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[5]     |LDUEN     |LDROM Update Enable Bit (Write Protect)
     * |        |          |0 = LDROM cannot be updated.
     * |        |          |1 = LDROM can be updated.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[6]     |ISPFF     |ISP Fail Flag (Write Protect)
     * |        |          |This bit is set by hardware when a triggered ISP meets any of the following conditions:
     * |        |          |This bit needs to be cleared by writing 1 to it.
     * |        |          |APROM writes to itself if APUEN is set to 0.
     * |        |          |LDROM writes to itself if LDUEN is set to 0.
     * |        |          |CONFIG is erased/programmed if CFGUEN is set to 0.
     * |        |          |SPROM is erased/programmed if SPUEN is set to 0.
     * |        |          |SPROM is programmed at SPROM secured mode.
     * |        |          |Page Erase command at LOCK mode with ICE connection.
     * |        |          |Erase or Program command at brown-out detected.
     * |        |          |Destination address is illegal, such as over an available range.
     * |        |          |Invalid ISP commands.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[24]    |INTEN     |ISP Interrupt Enable Bit (Write Protect)
     * |        |          |0= ISP interrupt Disabled.
     * |        |          |1= ISP interrupt Enabled.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Before using ISP interrupt, user needs to clear the INTFLAG(FMC_ISPSTS[8]) make sure interrupt happen at correct time.
     * @var FMC_T::ISPADDR
     * Offset: 0x04  ISP Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ISPADDR   |ISP Address
     * |        |          |ISPADDR[1:0] must be kept 00 for ISP 32-bit operation.
     * |        |          |For CRC32 Checksum Calculation command, this field is the Flash starting address for checksum calculation, 512 bytes alignment is necessary for checksum calculation.
     * |        |          |ISPADDR[8:0] must be kept all 0 for Vector Page Re-map Command.
     * @var FMC_T::ISPDAT
     * Offset: 0x08  ISP Data Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ISPDAT    |ISP Data
     * |        |          |Write data to this register before ISP program operation.
     * |        |          |Read data from this register after ISP read operation.
     * |        |          |When ISPFF is 1 in ISP read operation, ISPDAT will be written to 0xFFFF_FFFF.
     * |        |          |For run CRC32 Checksum Calculation command, ISPDAT is the memory size (byte) and 512 bytes alignment.
     * |        |          |For ISP Read Checksum command, ISPDAT is the checksum result.
     * |        |          |If ISPDAT = 0x0000_0000, it means that (1) the checksum calculation is in progress, or (2) the memory range for checksum calculation is incorrect.
     * @var FMC_T::ISPCMD
     * Offset: 0x0C  ISP Command Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:0]   |CMD       |ISP Command
     * |        |          |0x00 = Flash Read.
     * |        |          |0x04 = Read Unique ID.
     * |        |          |0x08 = Read All One.
     * |        |          |0x0B = Read Company ID.
     * |        |          |0x0C = Read Device ID.
     * |        |          |0x0D = Read CRC32 Checksum.
     * |        |          |0x21 = Flash 32-bit Program.
     * |        |          |0x22 = Flash Page Erase.
     * |        |          |0x23 = Flash APROM Bank Erase.
     * |        |          |0x27 = Flash Multi-word Program.
     * |        |          |0x28 = Run All One.
     * |        |          |0x2C = APROM Address Operation Model Selection.
     * |        |          |0x2D = Run CRC32 Checksum Calculation.
     * |        |          |0x2E = Vector Remap.
     * |        |          |0x40 = Flash 64-bit Read.
     * |        |          |0x61 = Flash 64-bit Program.
     * |        |          |Others = The other commands are invalid.
     * @var FMC_T::ISPTRG
     * Offset: 0x10  ISP Trigger Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ISPGO     |ISP Start Trigger (Write Protect)
     * |        |          |Write 1 to start ISP operation and this bit will be cleared to 0 by hardware automatically when ISP operation is finished.
     * |        |          |0 = ISP operation is finished.
     * |        |          |1 = ISP is progressed.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var FMC_T::DFBA
     * Offset: 0x14  Data Flash Base Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |DFBA      |Data Flash Base Address (Read Only)
     * |        |          |This register indicates Data Flash start address.
     * |        |          |The Data Flash is shared with APROM. The content of this register is loaded from CONFIG1.
     * |        |          |This register is valid when DFEN (CONFIG0[0]) = 0.
     * @var FMC_T::FTCTL
     * Offset: 0x18  Flash Access Time Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6:4]   |FOM       |Frequency Optimization Mode (Write Protect)
     * |        |          |Flash access timing is adjustable to optimize the Flash access cycles in different system working frequency.
     * |        |          |000 = Frequency is less than or equal to 72 MHz (7 cycles).
     * |        |          |010 = Frequency is less than or equal to 29 MHz (2 cycles).
     * |        |          |011 = Frequency is less than or equal to 43 MHz (3 cycles).
     * |        |          |100 = Frequency is less than or equal to 58 MHz (4 cycles).
     * |        |          |101 = Frequency is less than or equal to 72 MHz (5 cycles).
     * |        |          |Others = Reserved.
     * |        |          |Note: These bits are write protected. Refer to the SYS_REGLCTL register.
     * |[9]     |CACHEINV  |Flash Cache Invalidation (Write Protect)
     * |        |          |0 = Flash Cache Invalidation finished (default).
     * |        |          |1 = Flash Cache Invalidation.
     * |        |          |Note 1: Write 1 to start cache invalidation. The value will be changed to 0 once the process finishes.
     * |        |          |Note 2: This bit is write protected. Refer to the SYS_REGLCTL register.
     * @var FMC_T::ISPSTS
     * Offset: 0x40  ISP Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ISPBUSY   |ISP Busy Flag (Read Only)
     * |        |          |0 = ISP operation is finished.
     * |        |          |1 = ISP is progressed.
     * |[2:1]   |CBS       |Chip Boot Selection (Read Only)
     * |        |          |This bit is initiated with the CBS (CONFIG0[7:6]) after any reset is happened except CPU reset or system reset is happened.
     * |        |          |00 = LDROM with IAP mode.
     * |        |          |01 = LDROM without IAP mode.
     * |        |          |10 = APROM with IAP mode.
     * |        |          |11 = APROM without IAP mode.
     * |[5]     |PGFF      |Flash Program with Fast Verification Flag (Read Only)
     * |        |          |This bit is set if data is mismatched at ISP programming verification.
     * |        |          |This bit is clear by performing ISP flash erase or ISP read CID operation.
     * |        |          |0 = Flash Program is successful.
     * |        |          |1 = Flash Program is fail. Program data is different with data in the flash memory.
     * |[6]     |ISPFF     |ISP Fail Flag (Write Protect)
     * |        |          |This bit is the mirror of ISPFF (FMC_ISPCTL[6]), it needs to be cleared by writing 1 to FMC_ISPCTL[6] or FMC_ISPSTS[6].
     * |        |          |This bit is set by hardware when a triggered ISP meets any of the following conditions:
     * |        |          |APROM writes to itself if APUEN is set to 0.
     * |        |          |LDROM writes to itself if LDUEN is set to 0.
     * |        |          |CONFIG is erased/programmed if CFGUEN is set to 0.
     * |        |          |SPROM is erased/programmed if SPUEN is set to 0.
     * |        |          |SPROM is programmed at SPROM secured mode.
     * |        |          |Page Erase command at LOCK mode with ICE connection.
     * |        |          |Erase or Program command at brown-out detected.
     * |        |          |Destination address is illegal, such as over an available range.
     * |        |          |Invalid ISP commands.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |[7]     |ALLONE    |Flash All-one Verification Flag
     * |        |          |0 = Flash bits are not all 1 after "Run Flash All-One Verification" complete.
     * |        |          |1 = All of flash bits are 1 after "Run Flash All-One Verification" complete.
     * |[8 ]    |INTFLAG   |ISP Interrupt Flag
     * |        |          |This function needs to be enabled by INTEN(FMC_ISPCTL[24]) and cleared by writing 1 to it.
     * |        |          |0 = ISP Not Finished.
     * |        |          |1 = ISP done or ISPFF set.
     * |[29:9]  |VECMAP    |Vector Page Mapping Address (Read Only)
     * |        |          |All access to 0x0000_0000~0x0000_01FF is remapped to the Flash memory address {VECMAP[20:0], 9'h000} ~ {VECMAP[20:0], 9'1FF}, except SPROM.
     * |        |          |VECMAP [20:19] = 00 system vector address is mapped to Flash memory.
     * |        |          |VECMAP [18:12] should be 0.
     * |[30]    |FBS       |Flash Bank Select Indicator (Read Only)
     * |        |          |This bit indicates which APROM address model is selected to boot.
     * |        |          |0 = Address model OP0 is selected to boot.
     * |        |          |1 = Address model OP1 is selected to boot.
     * |[31]    |SCODE     |Security Code Active Flag
     * |        |          |This bit is set to 1 by hardware when detecting SPROM secured code is active at Flash initialization, or software writes 1 to this bit to make secured code active; this bit is only cleared by SPROM page erase operation.
     * |        |          |0 = SPROM secured code is inactive.
     * |        |          |1 = SPROM secured code is active.
     * @var FMC_T::MPDAT0
     * Offset: 0x80  ISP Data0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ISPDAT0   |ISP Data 0
     * |        |          |This register is the first 32-bit data for 32-bit/64-bit/multi-word programming, and it is also the mirror of FMC_ISPDAT, both registers keep the same data.
     * |        |          |When ISPFF is 1 in ISP read operation, ISPDAT0 will be written to 0xFFFF_FFFF.
     * @var FMC_T::MPDAT1
     * Offset: 0x84  ISP Data1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ISPDAT1   |ISP Data 1
     * |        |          |This register is the second 32-bit data for 64-bit/multi-word programming.
     * |        |          |When ISPFF is 1 in ISP read operation, ISPDAT0 will be written to 0xFFFF_FFFF.
     * @var FMC_T::MPDAT2
     * Offset: 0x88  ISP Data2 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ISPDAT2   |ISP Data 2
     * |        |          |This register is the third 32-bit data for multi-word programming.
     * @var FMC_T::MPDAT3
     * Offset: 0x8C  ISP Data3 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |ISPDAT3   |ISP Data 3
     * |        |          |This register is the fourth 32-bit data for multi-word programming.
     * @var FMC_T::MPSTS
     * Offset: 0xC0  ISP Multi-word Program Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |MPBUSY    |ISP Multi-word Program Busy Flag (Read Only)
     * |        |          |This bit is the mirror of ISPBUSY(FMC_ISPSTS[0]).
     * |        |          |0 = ISP multi-word program operation is finished.
     * |        |          |1 = ISP multi-word program operation is progressed.
     * |[1]     |PPGO      |ISP Multi-program Status (Read Only)
     * |        |          |0 = ISP multi-word program operation is not active.
     * |        |          |1 = ISP multi-word program operation is in progress.
     * |[2]     |ISPFF     |ISP Fail Flag (Read Only)
     * |        |          |This bit is the mirror of ISPFF (FMC_ISPCTL[6]), it needs to be cleared by writing 1 to FMC_ISPCTL[6] or FMC_ISPSTS[6].
     * |        |          |This bit is set by hardware when a triggered ISP meets any of the following conditions:
     * |        |          |APROM writes to itself if APUEN is set to 0.
     * |        |          |LDROM writes to itself if LDUEN is set to 0.
     * |        |          |CONFIG is erased/programmed if CFGUEN is set to 0.
     * |        |          |SPROM is erased/programmed if SPUEN is set to 0.
     * |        |          |SPROM is programmed at SPROM secured mode.
     * |        |          |Page Erase command at LOCK mode with ICE connection.
     * |        |          |Erase or Program command at brown-out detected.
     * |        |          |Destination address is illegal, such as over an available range.
     * |        |          |Invalid ISP commands.
     * |[4]     |D0        |ISP DATA 0 Flag (Read Only)
     * |        |          |This bit is set when FMC_MPDAT0 is written and auto-cleared to 0 when the FMC_MPDAT0 data is programmed to flash complete.
     * |        |          |0 = FMC_MPDAT0 register is empty, or program to flash complete.
     * |        |          |1 = FMC_MPDAT0 register has been written, and not program to flash complete.
     * |[5]     |D1        |ISP DATA 1 Flag (Read Only)
     * |        |          |This bit is set when FMC_MPDAT1 is written and auto-cleared to 0 when the FMC_MPDAT1 data is programmed to flash complete.
     * |        |          |0 = FMC_MPDAT1 register is empty, or program to flash complete.
     * |        |          |1 = FMC_MPDAT1 register has been written, and not program to flash complete.
     * |[6]     |D2        |ISP DATA 2 Flag (Read Only)
     * |        |          |This bit is set when FMC_MPDAT2 is written and auto-cleared to 0 when the FMC_MPDAT2 data is programmed to flash complete.
     * |        |          |0 = FMC_MPDAT2 register is empty, or program to flash complete.
     * |        |          |1 = FMC_MPDAT2 register has been written, and not program to flash complete.
     * |[7]     |D3        |ISP DATA 3 Flag (Read Only)
     * |        |          |This bit is set when FMC_MPDAT3 is written and auto-cleared to 0 when the FMC_MPDAT3 data is programmed to flash complete.
     * |        |          |0 = FMC_MPDAT3 register is empty, or program to flash complete.
     * |        |          |1 = FMC_MPDAT3 register has been written, and not program to flash complete.
     * @var FMC_T::MPADDR
     * Offset: 0xC4  ISP Multi-word Program Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |MPADDR    |ISP Multi-word Program Address (Read Only)
     * |        |          |MPADDR is the address of ISP multi-word program operation when ISPGO flag is 1.
     * |        |          |MPADDR will keep the final ISP address when ISP multi-word program is complete.
     * @var FMC_T::APWPROT0
     * Offset: 0x110  APROM Protect Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[n]     |APPROENn  |APROM Protect Enable Bit
     * |n=0,1.. |          |This bit indicates which APROM region is protected.
     * | ..31   |          |The reset value is inverse of CONFIG8.
     * |        |          |0 = APROM region n is not protected.
     * |        |          |1 = APROM region n is protected.
     * |        |          |Note: APROM protect region is 0x0 + n*(0x2000) to 0x7fff + n*(0x2000).
     * @var FMC_T::APWPKEEP
     * Offset: 0x118  APROM Write Protect Keep Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |APWPKEEP0 |APROM Write Protect Keep 0
     * |        |          |0x55AA = APWPROT0 and APWPKEEP registers are locked.
     * |        |          |Others = APWPROT0 and APWPKEEP registers are free to modify.
     * |        |          |Note 1: These bits reset value can be decided by CONFIG10.
     * |        |          |Note 2: APWPKEEP0 is equal to 0x55AA when APWPLVL1 or written 0x55AA to APWPKEEP0 in APWPLVL0.
     */

    __IO uint32_t ISPCTL;                /*!< [0x0000] ISP Control Register                                             */
    __IO uint32_t ISPADDR;               /*!< [0x0004] ISP Address Register                                             */
    __IO uint32_t ISPDAT;                /*!< [0x0008] ISP Data Register                                                */
    __IO uint32_t ISPCMD;                /*!< [0x000c] ISP Command Register                                             */
    __IO uint32_t ISPTRG;                /*!< [0x0010] ISP Trigger Control Register                                     */
    __I  uint32_t DFBA;                  /*!< [0x0014] Data Flash Base Address                                          */
    __IO uint32_t FTCTL;                 /*!< [0x0018] Flash Access Time Control Register                               */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[9];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t ISPSTS;                /*!< [0x0040] ISP Status Register                                              */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[15];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t MPDAT0;                /*!< [0x0080] ISP Data0 Register                                               */
    __IO uint32_t MPDAT1;                /*!< [0x0084] ISP Data1 Register                                               */
    __IO uint32_t MPDAT2;                /*!< [0x0088] ISP Data2 Register                                               */
    __IO uint32_t MPDAT3;                /*!< [0x008c] ISP Data3 Register                                               */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[12];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t MPSTS;                 /*!< [0x00c0] ISP Multi-word Program Status Register                           */
    __I  uint32_t MPADDR;                /*!< [0x00c4] ISP Multi-word Program Address Register                          */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[18];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t APWPROT0;              /*!< [0x0110] APROM Protect Register 0                                         */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE4[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t APWPKEEP;              /*!< [0x0118] APROM Write Protect Keep Register                                */
} FMC_T;

/**
    @addtogroup FMC_CONST FMC Bit Field Definition
    Constant Definitions for FMC Controller
@{ */

#define FMC_ISPCTL_ISPEN_Pos             (0)                                               /*!< FMC_T::ISPCTL: ISPEN Position          */
#define FMC_ISPCTL_ISPEN_Msk             (0x1ul << FMC_ISPCTL_ISPEN_Pos)                   /*!< FMC_T::ISPCTL: ISPEN Mask              */

#define FMC_ISPCTL_BS_Pos                (1)                                               /*!< FMC_T::ISPCTL: BS Position             */
#define FMC_ISPCTL_BS_Msk                (0x1ul << FMC_ISPCTL_BS_Pos)                      /*!< FMC_T::ISPCTL: BS Mask                 */

#define FMC_ISPCTL_SPUEN_Pos             (2)                                               /*!< FMC_T::ISPCTL: SPUEN Position          */
#define FMC_ISPCTL_SPUEN_Msk             (0x1ul << FMC_ISPCTL_SPUEN_Pos)                   /*!< FMC_T::ISPCTL: SPUEN Mask              */

#define FMC_ISPCTL_APUEN_Pos             (3)                                               /*!< FMC_T::ISPCTL: APUEN Position          */
#define FMC_ISPCTL_APUEN_Msk             (0x1ul << FMC_ISPCTL_APUEN_Pos)                   /*!< FMC_T::ISPCTL: APUEN Mask              */

#define FMC_ISPCTL_CFGUEN_Pos            (4)                                               /*!< FMC_T::ISPCTL: CFGUEN Position         */
#define FMC_ISPCTL_CFGUEN_Msk            (0x1ul << FMC_ISPCTL_CFGUEN_Pos)                  /*!< FMC_T::ISPCTL: CFGUEN Mask             */

#define FMC_ISPCTL_LDUEN_Pos             (5)                                               /*!< FMC_T::ISPCTL: LDUEN Position          */
#define FMC_ISPCTL_LDUEN_Msk             (0x1ul << FMC_ISPCTL_LDUEN_Pos)                   /*!< FMC_T::ISPCTL: LDUEN Mask              */

#define FMC_ISPCTL_ISPFF_Pos             (6)                                               /*!< FMC_T::ISPCTL: ISPFF Position          */
#define FMC_ISPCTL_ISPFF_Msk             (0x1ul << FMC_ISPCTL_ISPFF_Pos)                   /*!< FMC_T::ISPCTL: ISPFF Mask              */

#define FMC_ISPCTL_INTEN_Pos             (24)                                              /*!< FMC_T::ISPCTL: INTEN Position          */
#define FMC_ISPCTL_INTEN_Msk             (0x1ul << FMC_ISPCTL_INTEN_Pos)                   /*!< FMC_T::ISPCTL: INTEN Mask              */

#define FMC_ISPADDR_ISPADDR_Pos          (0)                                               /*!< FMC_T::ISPADDR: ISPADDR Position       */
#define FMC_ISPADDR_ISPADDR_Msk          (0xfffffffful << FMC_ISPADDR_ISPADDR_Pos)         /*!< FMC_T::ISPADDR: ISPADDR Mask           */

#define FMC_ISPDAT_ISPDAT_Pos            (0)                                               /*!< FMC_T::ISPDAT: ISPDAT Position         */
#define FMC_ISPDAT_ISPDAT_Msk            (0xfffffffful << FMC_ISPDAT_ISPDAT_Pos)           /*!< FMC_T::ISPDAT: ISPDAT Mask             */

#define FMC_ISPCMD_CMD_Pos               (0)                                               /*!< FMC_T::ISPCMD: CMD Position            */
#define FMC_ISPCMD_CMD_Msk               (0x7ful << FMC_ISPCMD_CMD_Pos)                    /*!< FMC_T::ISPCMD: CMD Mask                */

#define FMC_ISPTRG_ISPGO_Pos             (0)                                               /*!< FMC_T::ISPTRG: ISPGO Position          */
#define FMC_ISPTRG_ISPGO_Msk             (0x1ul << FMC_ISPTRG_ISPGO_Pos)                   /*!< FMC_T::ISPTRG: ISPGO Mask              */

#define FMC_DFBA_DFBA_Pos                (0)                                               /*!< FMC_T::DFBA: DFBA Position             */
#define FMC_DFBA_DFBA_Msk                (0xfffffffful << FMC_DFBA_DFBA_Pos)               /*!< FMC_T::DFBA: DFBA Mask                 */

#define FMC_FTCTL_FOM_Pos                (4)                                               /*!< FMC_T::FTCTL: FOM Position             */
#define FMC_FTCTL_FOM_Msk                (0x7ul << FMC_FTCTL_FOM_Pos)                      /*!< FMC_T::FTCTL: FOM Mask                 */

#define FMC_FTCTL_CACHEINV_Pos           (9)                                               /*!< FMC_T::FTCTL: CACHEINV Position        */
#define FMC_FTCTL_CACHEINV_Msk           (0x1ul << FMC_FTCTL_CACHEINV_Pos)                 /*!< FMC_T::FTCTL: CACHEINV Mask            */

#define FMC_ISPSTS_ISPBUSY_Pos           (0)                                               /*!< FMC_T::ISPSTS: ISPBUSY Position        */
#define FMC_ISPSTS_ISPBUSY_Msk           (0x1ul << FMC_ISPSTS_ISPBUSY_Pos)                 /*!< FMC_T::ISPSTS: ISPBUSY Mask            */

#define FMC_ISPSTS_CBS_Pos               (1)                                               /*!< FMC_T::ISPSTS: CBS Position            */
#define FMC_ISPSTS_CBS_Msk               (0x3ul << FMC_ISPSTS_CBS_Pos)                     /*!< FMC_T::ISPSTS: CBS Mask                */

#define FMC_ISPSTS_PGFF_Pos              (5)                                               /*!< FMC_T::ISPSTS: PGFF Position           */
#define FMC_ISPSTS_PGFF_Msk              (0x1ul << FMC_ISPSTS_PGFF_Pos)                    /*!< FMC_T::ISPSTS: PGFF Mask               */

#define FMC_ISPSTS_ISPFF_Pos             (6)                                               /*!< FMC_T::ISPSTS: ISPFF Position          */
#define FMC_ISPSTS_ISPFF_Msk             (0x1ul << FMC_ISPSTS_ISPFF_Pos)                   /*!< FMC_T::ISPSTS: ISPFF Mask              */

#define FMC_ISPSTS_ALLONE_Pos            (7)                                               /*!< FMC_T::ISPSTS: ALLONE Position         */
#define FMC_ISPSTS_ALLONE_Msk            (0x1ul << FMC_ISPSTS_ALLONE_Pos)                  /*!< FMC_T::ISPSTS: ALLONE Mask             */

#define FMC_ISPSTS_INTFLAG_Pos           (8)                                               /*!< FMC_T::ISPSTS: INTFLAG Position        */
#define FMC_ISPSTS_INTFLAG_Msk           (0x01ul << FMC_ISPSTS_INTFLAG_Pos)                /*!< FMC_T::ISPSTS: INTFLAG Position        */

#define FMC_ISPSTS_VECMAP_Pos            (9)                                               /*!< FMC_T::ISPSTS: VECMAP Position         */
#define FMC_ISPSTS_VECMAP_Msk            (0x1ffffful << FMC_ISPSTS_VECMAP_Pos)             /*!< FMC_T::ISPSTS: VECMAP Mask             */

#define FMC_ISPSTS_FBS_Pos               (30)                                              /*!< FMC_T::ISPSTS: FBS Position            */
#define FMC_ISPSTS_FBS_Msk               (0x1ul << FMC_ISPSTS_FBS_Pos)                     /*!< FMC_T::ISPSTS: FBS Msk                 */

#define FMC_ISPSTS_SCODE_Pos             (31)                                              /*!< FMC_T::ISPSTS: SCODE Position          */
#define FMC_ISPSTS_SCODE_Msk             (0x1ul << FMC_ISPSTS_SCODE_Pos)                   /*!< FMC_T::ISPSTS: SCODE Mask               */

#define FMC_MPDAT0_ISPDAT0_Pos           (0)                                               /*!< FMC_T::MPDAT0: ISPDAT0 Position        */
#define FMC_MPDAT0_ISPDAT0_Msk           (0xfffffffful << FMC_MPDAT0_ISPDAT0_Pos)          /*!< FMC_T::MPDAT0: ISPDAT0 Mask            */

#define FMC_MPDAT1_ISPDAT1_Pos           (0)                                               /*!< FMC_T::MPDAT1: ISPDAT1 Position        */
#define FMC_MPDAT1_ISPDAT1_Msk           (0xfffffffful << FMC_MPDAT1_ISPDAT1_Pos)          /*!< FMC_T::MPDAT1: ISPDAT1 Mask            */

#define FMC_MPDAT2_ISPDAT2_Pos           (0)                                               /*!< FMC_T::MPDAT2: ISPDAT2 Position        */
#define FMC_MPDAT2_ISPDAT2_Msk           (0xfffffffful << FMC_MPDAT2_ISPDAT2_Pos)          /*!< FMC_T::MPDAT2: ISPDAT2 Mask            */

#define FMC_MPDAT3_ISPDAT3_Pos           (0)                                               /*!< FMC_T::MPDAT3: ISPDAT3 Position        */
#define FMC_MPDAT3_ISPDAT3_Msk           (0xfffffffful << FMC_MPDAT3_ISPDAT3_Pos)          /*!< FMC_T::MPDAT3: ISPDAT3 Mask            */

#define FMC_MPSTS_MPBUSY_Pos             (0)                                               /*!< FMC_T::MPSTS: MPBUSY Position          */
#define FMC_MPSTS_MPBUSY_Msk             (0x1ul << FMC_MPSTS_MPBUSY_Pos)                   /*!< FMC_T::MPSTS: MPBUSY Mask              */

#define FMC_MPSTS_PPGO_Pos               (1)                                               /*!< FMC_T::MPSTS: PPGO Position            */
#define FMC_MPSTS_PPGO_Msk               (0x1ul << FMC_MPSTS_PPGO_Pos)                     /*!< FMC_T::MPSTS: PPGO Mask                */

#define FMC_MPSTS_ISPFF_Pos              (2)                                               /*!< FMC_T::MPSTS: ISPFF Position           */
#define FMC_MPSTS_ISPFF_Msk              (0x1ul << FMC_MPSTS_ISPFF_Pos)                    /*!< FMC_T::MPSTS: ISPFF Mask               */

#define FMC_MPSTS_D0_Pos                 (4)                                               /*!< FMC_T::MPSTS: D0 Position              */
#define FMC_MPSTS_D0_Msk                 (0x1ul << FMC_MPSTS_D0_Pos)                       /*!< FMC_T::MPSTS: D0 Mask                  */

#define FMC_MPSTS_D1_Pos                 (5)                                               /*!< FMC_T::MPSTS: D1 Position              */
#define FMC_MPSTS_D1_Msk                 (0x1ul << FMC_MPSTS_D1_Pos)                       /*!< FMC_T::MPSTS: D1 Mask                  */

#define FMC_MPSTS_D2_Pos                 (6)                                               /*!< FMC_T::MPSTS: D2 Position              */
#define FMC_MPSTS_D2_Msk                 (0x1ul << FMC_MPSTS_D2_Pos)                       /*!< FMC_T::MPSTS: D2 Mask                  */

#define FMC_MPSTS_D3_Pos                 (7)                                               /*!< FMC_T::MPSTS: D3 Position              */
#define FMC_MPSTS_D3_Msk                 (0x1ul << FMC_MPSTS_D3_Pos)                       /*!< FMC_T::MPSTS: D3 Mask                  */

#define FMC_MPADDR_MPADDR_Pos            (0)                                               /*!< FMC_T::MPADDR: MPADDR Position         */
#define FMC_MPADDR_MPADDR_Msk            (0xfffffffful << FMC_MPADDR_MPADDR_Pos)           /*!< FMC_T::MPADDR: MPADDR Mask             */

#define FMC_APWPROT0_APPROEN0_Pos        (0)                                               /*!< FMC_T::APWPROT0: APPROEN0 Position     */
#define FMC_APWPROT0_APPROEN0_Msk        (0x1ul << FMC_APWPROT0_APPROEN0_Pos)              /*!< FMC_T::APWPROT0: APPROEN0 Mask         */

#define FMC_APWPROT0_APPROEN1_Pos        (1)                                               /*!< FMC_T::APWPROT0: APPROEN1 Position     */
#define FMC_APWPROT0_APPROEN1_Msk        (0x1ul << FMC_APWPROT0_APPROEN1_Pos)              /*!< FMC_T::APWPROT0: APPROEN1 Mask         */

#define FMC_APWPROT0_APPROEN2_Pos        (2)                                               /*!< FMC_T::APWPROT0: APPROEN2 Position     */
#define FMC_APWPROT0_APPROEN2_Msk        (0x1ul << FMC_APWPROT0_APPROEN2_Pos)              /*!< FMC_T::APWPROT0: APPROEN2 Mask         */

#define FMC_APWPROT0_APPROEN3_Pos        (3)                                               /*!< FMC_T::APWPROT0: APPROEN3 Position     */
#define FMC_APWPROT0_APPROEN3_Msk        (0x1ul << FMC_APWPROT0_APPROEN3_Pos)              /*!< FMC_T::APWPROT0: APPROEN3 Mask         */

#define FMC_APWPROT0_APPROEN4_Pos        (4)                                               /*!< FMC_T::APWPROT0: APPROEN4 Position     */
#define FMC_APWPROT0_APPROEN4_Msk        (0x1ul << FMC_APWPROT0_APPROEN4_Pos)              /*!< FMC_T::APWPROT0: APPROEN4 Mask         */

#define FMC_APWPROT0_APPROEN5_Pos        (5)                                               /*!< FMC_T::APWPROT0: APPROEN5 Position     */
#define FMC_APWPROT0_APPROEN5_Msk        (0x1ul << FMC_APWPROT0_APPROEN5_Pos)              /*!< FMC_T::APWPROT0: APPROEN5 Mask         */

#define FMC_APWPROT0_APPROEN6_Pos        (6)                                               /*!< FMC_T::APWPROT0: APPROEN6 Position     */
#define FMC_APWPROT0_APPROEN6_Msk        (0x1ul << FMC_APWPROT0_APPROEN6_Pos)              /*!< FMC_T::APWPROT0: APPROEN6 Mask         */

#define FMC_APWPROT0_APPROEN7_Pos        (7)                                               /*!< FMC_T::APWPROT0: APPROEN7 Position     */
#define FMC_APWPROT0_APPROEN7_Msk        (0x1ul << FMC_APWPROT0_APPROEN7_Pos)              /*!< FMC_T::APWPROT0: APPROEN7 Mask         */

#define FMC_APWPROT0_APPROEN8_Pos        (8)                                               /*!< FMC_T::APWPROT0: APPROEN8 Position     */
#define FMC_APWPROT0_APPROEN8_Msk        (0x1ul << FMC_APWPROT0_APPROEN8_Pos)              /*!< FMC_T::APWPROT0: APPROEN8 Mask         */

#define FMC_APWPROT0_APPROEN9_Pos        (9)                                               /*!< FMC_T::APWPROT0: APPROEN9 Position     */
#define FMC_APWPROT0_APPROEN9_Msk        (0x1ul << FMC_APWPROT0_APPROEN9_Pos)              /*!< FMC_T::APWPROT0: APPROEN9 Mask         */

#define FMC_APWPROT0_APPROEN10_Pos       (10)                                              /*!< FMC_T::APWPROT0: APPROEN10 Position    */
#define FMC_APWPROT0_APPROEN10_Msk       (0x1ul << FMC_APWPROT0_APPROEN10_Pos)             /*!< FMC_T::APWPROT0: APPROEN10 Mask        */

#define FMC_APWPROT0_APPROEN11_Pos       (11)                                              /*!< FMC_T::APWPROT0: APPROEN11 Position    */
#define FMC_APWPROT0_APPROEN11_Msk       (0x1ul << FMC_APWPROT0_APPROEN11_Pos)             /*!< FMC_T::APWPROT0: APPROEN11 Mask        */

#define FMC_APWPROT0_APPROEN12_Pos       (12)                                              /*!< FMC_T::APWPROT0: APPROEN12 Position    */
#define FMC_APWPROT0_APPROEN12_Msk       (0x1ul << FMC_APWPROT0_APPROEN12_Pos)             /*!< FMC_T::APWPROT0: APPROEN12 Mask        */

#define FMC_APWPROT0_APPROEN13_Pos       (13)                                              /*!< FMC_T::APWPROT0: APPROEN13 Position    */
#define FMC_APWPROT0_APPROEN13_Msk       (0x1ul << FMC_APWPROT0_APPROEN13_Pos)             /*!< FMC_T::APWPROT0: APPROEN13 Mask        */

#define FMC_APWPROT0_APPROEN14_Pos       (14)                                              /*!< FMC_T::APWPROT0: APPROEN14 Position    */
#define FMC_APWPROT0_APPROEN14_Msk       (0x1ul << FMC_APWPROT0_APPROEN14_Pos)             /*!< FMC_T::APWPROT0: APPROEN14 Mask        */

#define FMC_APWPROT0_APPROEN15_Pos       (15)                                              /*!< FMC_T::APWPROT0: APPROEN15 Position    */
#define FMC_APWPROT0_APPROEN15_Msk       (0x1ul << FMC_APWPROT0_APPROEN15_Pos)             /*!< FMC_T::APWPROT0: APPROEN15 Mask        */

#define FMC_APWPROT0_APPROEN16_Pos       (16)                                              /*!< FMC_T::APWPROT0: APPROEN16 Position    */
#define FMC_APWPROT0_APPROEN16_Msk       (0x1ul << FMC_APWPROT0_APPROEN16_Pos)             /*!< FMC_T::APWPROT0: APPROEN16 Mask        */

#define FMC_APWPROT0_APPROEN17_Pos       (17)                                              /*!< FMC_T::APWPROT0: APPROEN17 Position    */
#define FMC_APWPROT0_APPROEN17_Msk       (0x1ul << FMC_APWPROT0_APPROEN17_Pos)             /*!< FMC_T::APWPROT0: APPROEN17 Mask        */

#define FMC_APWPROT0_APPROEN18_Pos       (18)                                              /*!< FMC_T::APWPROT0: APPROEN18 Position    */
#define FMC_APWPROT0_APPROEN18_Msk       (0x1ul << FMC_APWPROT0_APPROEN18_Pos)             /*!< FMC_T::APWPROT0: APPROEN18 Mask        */

#define FMC_APWPROT0_APPROEN19_Pos       (19)                                              /*!< FMC_T::APWPROT0: APPROEN19 Position    */
#define FMC_APWPROT0_APPROEN19_Msk       (0x1ul << FMC_APWPROT0_APPROEN19_Pos)             /*!< FMC_T::APWPROT0: APPROEN19 Mask        */

#define FMC_APWPROT0_APPROEN20_Pos       (20)                                              /*!< FMC_T::APWPROT0: APPROEN20 Position    */
#define FMC_APWPROT0_APPROEN20_Msk       (0x1ul << FMC_APWPROT0_APPROEN20_Pos)             /*!< FMC_T::APWPROT0: APPROEN20 Mask        */

#define FMC_APWPROT0_APPROEN21_Pos       (21)                                              /*!< FMC_T::APWPROT0: APPROEN21 Position    */
#define FMC_APWPROT0_APPROEN21_Msk       (0x1ul << FMC_APWPROT0_APPROEN21_Pos)             /*!< FMC_T::APWPROT0: APPROEN21 Mask        */

#define FMC_APWPROT0_APPROEN22_Pos       (22)                                              /*!< FMC_T::APWPROT0: APPROEN22 Position    */
#define FMC_APWPROT0_APPROEN22_Msk       (0x1ul << FMC_APWPROT0_APPROEN22_Pos)             /*!< FMC_T::APWPROT0: APPROEN22 Mask        */

#define FMC_APWPROT0_APPROEN23_Pos       (23)                                              /*!< FMC_T::APWPROT0: APPROEN23 Position    */
#define FMC_APWPROT0_APPROEN23_Msk       (0x1ul << FMC_APWPROT0_APPROEN23_Pos)             /*!< FMC_T::APWPROT0: APPROEN23 Mask        */

#define FMC_APWPROT0_APPROEN24_Pos       (24)                                              /*!< FMC_T::APWPROT0: APPROEN24 Position    */
#define FMC_APWPROT0_APPROEN24_Msk       (0x1ul << FMC_APWPROT0_APPROEN24_Pos)             /*!< FMC_T::APWPROT0: APPROEN24 Mask        */

#define FMC_APWPROT0_APPROEN25_Pos       (25)                                              /*!< FMC_T::APWPROT0: APPROEN25 Position    */
#define FMC_APWPROT0_APPROEN25_Msk       (0x1ul << FMC_APWPROT0_APPROEN25_Pos)             /*!< FMC_T::APWPROT0: APPROEN25 Mask        */

#define FMC_APWPROT0_APPROEN26_Pos       (26)                                              /*!< FMC_T::APWPROT0: APPROEN26 Position    */
#define FMC_APWPROT0_APPROEN26_Msk       (0x1ul << FMC_APWPROT0_APPROEN26_Pos)             /*!< FMC_T::APWPROT0: APPROEN26 Mask        */

#define FMC_APWPROT0_APPROEN27_Pos       (27)                                              /*!< FMC_T::APWPROT0: APPROEN27 Position    */
#define FMC_APWPROT0_APPROEN27_Msk       (0x1ul << FMC_APWPROT0_APPROEN27_Pos)             /*!< FMC_T::APWPROT0: APPROEN27 Mask        */

#define FMC_APWPROT0_APPROEN28_Pos       (28)                                              /*!< FMC_T::APWPROT0: APPROEN28 Position    */
#define FMC_APWPROT0_APPROEN28_Msk       (0x1ul << FMC_APWPROT0_APPROEN28_Pos)             /*!< FMC_T::APWPROT0: APPROEN28 Mask        */

#define FMC_APWPROT0_APPROEN29_Pos       (29)                                              /*!< FMC_T::APWPROT0: APPROEN29 Position    */
#define FMC_APWPROT0_APPROEN29_Msk       (0x1ul << FMC_APWPROT0_APPROEN29_Pos)             /*!< FMC_T::APWPROT0: APPROEN29 Mask        */

#define FMC_APWPROT0_APPROEN30_Pos       (30)                                              /*!< FMC_T::APWPROT0: APPROEN30 Position    */
#define FMC_APWPROT0_APPROEN30_Msk       (0x1ul << FMC_APWPROT0_APPROEN30_Pos)             /*!< FMC_T::APWPROT0: APPROEN30 Mask        */

#define FMC_APWPROT0_APPROEN31_Pos       (31)                                              /*!< FMC_T::APWPROT0: APPROEN31 Position    */
#define FMC_APWPROT0_APPROEN31_Msk       (0x1ul << FMC_APWPROT0_APPROEN31_Pos)             /*!< FMC_T::APWPROT0: APPROEN31 Mask        */

#define FMC_APWPKEEP_APWPKEEP0_Pos       (0)                                               /*!< FMC_T::APWPKEEP: APWPKEEP0 Position    */
#define FMC_APWPKEEP_APWPKEEP0_Msk       (0xfffful << FMC_APWPKEEP_APWPKEEP0_Pos)          /*!< FMC_T::APWPKEEP: APWPKEEP0 Mask        */

/**@}*/ /* FMC_CONST */
/**@}*/ /* end of FMC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __FMC_REG_H__ */
