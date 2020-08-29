# -----------------------------------------------------------------------------
#
# Copyright (C) 2015-2017 Infineon Technologies AG. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# - Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
# - Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation.
#   and/or other materials provided with the distribution.
# - Neither the name of the copyright holders nor the names of its
#   contributors may be used to endorse or promote products derived from this
#   software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# To improve the quality of the software, users are encouraged to share
# modifications, enhancements or bug fixes with Infineon Technologies AG
# (support@infineon.com).
# 
# -----------------------------------------------------------------------------
# Subdirectory make file for ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/SnsAct
# !! Generated make file, modifications could be overwritten !!
#------------------------------------------------------------------------------


# Make-Rules:
# Make-rules for architecture: Tricore

#Make-rule to build file: BasicStm.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/BasicStm.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/BasicStm.o

2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/BasicStm.o: ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/SnsAct/BasicStm.c $(B_GEN_CONFIG_TRICORE_GNUC)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file BasicStm.c for Tricore'
	$(B_GEN_TRICORE_GNUC_CC) $(B_GNUC_TRICORE_CC_OPTIONS) -DBOARD=SHIELD_BUDDY @$(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -c $< -o $@ -save-temps=obj -MMD

#Make-rule to build file: Digital_IO.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/Digital_IO.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/Digital_IO.o

2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/Digital_IO.o: ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/SnsAct/Digital_IO.c $(B_GEN_CONFIG_TRICORE_GNUC)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file Digital_IO.c for Tricore'
	$(B_GEN_TRICORE_GNUC_CC) $(B_GNUC_TRICORE_CC_OPTIONS) -DBOARD=SHIELD_BUDDY @$(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -c $< -o $@ -save-temps=obj -MMD

#Make-rule to build file: HallSensor.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/HallSensor.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/HallSensor.o

2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/HallSensor.o: ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/SnsAct/HallSensor.c $(B_GEN_CONFIG_TRICORE_GNUC)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file HallSensor.c for Tricore'
	$(B_GEN_TRICORE_GNUC_CC) $(B_GNUC_TRICORE_CC_OPTIONS) -DBOARD=SHIELD_BUDDY @$(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -c $< -o $@ -save-temps=obj -MMD

#Make-rule to build file: KUSV_ADC.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/KUSV_ADC.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/KUSV_ADC.o

2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/KUSV_ADC.o: ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/SnsAct/KUSV_ADC.c $(B_GEN_CONFIG_TRICORE_GNUC)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file KUSV_ADC.c for Tricore'
	$(B_GEN_TRICORE_GNUC_CC) $(B_GNUC_TRICORE_CC_OPTIONS) -DBOARD=SHIELD_BUDDY @$(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -c $< -o $@ -save-temps=obj -MMD

#Make-rule to build file: KUSV_LineScan.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/KUSV_LineScan.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/KUSV_LineScan.o

2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/KUSV_LineScan.o: ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/SnsAct/KUSV_LineScan.c $(B_GEN_CONFIG_TRICORE_GNUC)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file KUSV_LineScan.c for Tricore'
	$(B_GEN_TRICORE_GNUC_CC) $(B_GNUC_TRICORE_CC_OPTIONS) -DBOARD=SHIELD_BUDDY @$(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -c $< -o $@ -save-temps=obj -MMD

#Make-rule to build file: KUSV_Motor.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/KUSV_Motor.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/KUSV_Motor.o

2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/KUSV_Motor.o: ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/SnsAct/KUSV_Motor.c $(B_GEN_CONFIG_TRICORE_GNUC)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file KUSV_Motor.c for Tricore'
	$(B_GEN_TRICORE_GNUC_CC) $(B_GNUC_TRICORE_CC_OPTIONS) -DBOARD=SHIELD_BUDDY @$(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -c $< -o $@ -save-temps=obj -MMD

#Make-rule to build file: PID_Controller.c
B_GEN_DEP_FILES+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/PID_Controller.d
B_GEN_OBJS_TRICORE_TC+= 2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/PID_Controller.o

2_Out/Tricore_Gnuc/Gnuc_Files/1_ExtSrc/Tricore/SnsAct/PID_Controller.o: ../../MyApp/AurixRacer/0_Src/AppSw/Tricore/SnsAct/PID_Controller.c $(B_GEN_CONFIG_TRICORE_GNUC)
	@mkdir -p $(@D)
	@-rm -f $(B_GEN_ELF_TRICORE_TC) $(B_GEN_HEX_TRICORE_TC)
	@echo 'Building source file PID_Controller.c for Tricore'
	$(B_GEN_TRICORE_GNUC_CC) $(B_GNUC_TRICORE_CC_OPTIONS) -DBOARD=SHIELD_BUDDY @$(B_GEN_INC_LISTFILE_TRICORE) $(B_GEN_EXT_INCLUDE_PATHS) -c $< -o $@ -save-temps=obj -MMD
