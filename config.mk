# Written by dk from dk.json; change dk.json, not this file.
EXE := SLUS_205.15
TARGET_SHA := bee9fc13d12ab2818822d905d820320fc6427f23
AS_FLAGS := -EL -G0 -march=r5900 -mabi=eabi -no-pad-sections
export DK_PLATFORM := ps2
export DK_GCC := mwcps2-2.3.3-000906
export DK_CFLAGS := -O4,p -sdatathreshold 0 -relax_pointers
export DK_G := 0
export DK_MASPSX := 
