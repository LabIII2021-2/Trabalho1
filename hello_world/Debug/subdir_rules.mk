################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/Program Files (x86)/Texas Instruments/C5500 Code Generation Tools 4.4.1/bin/cl55" -v5502 --memory_model=large -g --include_path="C:/Users/pedro/workspace_v10/hello_word" --include_path="C:/Program Files (x86)/Texas Instruments/C5500 Code Generation Tools 4.4.1/include" --define=c5502 --display_error_number --diag_warning=225 --ptrdiff_size=32 --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


