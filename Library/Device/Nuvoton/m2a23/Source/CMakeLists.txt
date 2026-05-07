enable_language(C ASM)
add_library(system_startup
    system_m2a23.c
    $<$<STREQUAL:${C_COMPILER_ID},ARMCLANG>:ARM/startup_m2a23.S>
    $<$<STREQUAL:${C_COMPILER_ID},GCC>:GCC/_syscalls.c>
    $<$<STREQUAL:${C_COMPILER_ID},GCC>:GCC/startup_m2a23.S>
)
