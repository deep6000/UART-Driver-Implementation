#--------------------------------------------------------------------------------------------------------------------------------------------------------------
#This makefile is for build system supporting threee platforms, FOST(Linux PC), KL25Z (Freedom board)
# and BBB (Beagle Bome Black)
#--------------------------------------------------------------------------------------------------------------------------------------------------------------

#platform to be changed here
PLATFORM = HOST
vpath %.c src/

#Linker for KL25Z
LINKER = MKL25Z128xxx4_flash.ld

#Path for Header File
DEPS = -I inc/


ifeq	($(PLATFORM),HOST)
	CC = gcc
	TARGET = linux
	FLAGS= -D$(TARGET)
	LDFLAGS = -Wl,-Map=$(TARGET).map
	SRC := ring.c main.c
	OBJ := $(SRC:.c=.o)
	CFLAGS = -Wall -g -O0 -std=c99 $(DEPS)
endif

ifeq	($(PLATFORM),KL25Z)
	CC = arm-none-eabi-gcc
	TARGET = KL25Z
	DEPS_KL25Z = $(DEPS) -I kl25z/
	SRC := ring.c main.c system_MKL25Z4.c
	CFLAGS = -Wall -g -O0 -std=c99
	FLAGS = -mthumb -mcpu=cortex-m0plus -march=armv6-m -mfloat-abi=soft -mfpu=fpv4-sp-d16 -specs=nosys.specs $(DEPS_KL25Z)
	LDFLAGS = -Wl,-T $(LINKER)
	CPPFLAGS = -DKL25Z 
	OBJ := $(SRC:.c=.o) startup_MKL25Z4.o
endif

ifeq	($(PLATFORM),BBB)
	CC = arm-linux-gnueabihf-gcc
	TARGET = BBB
	CFLAGS = -Wall -g -O0 -std=c99 $(DEPS)
	CPPFLAGS = -DBBB -D VERBOSE
	LDFLAGS = -Wl,-Map=$(TARGET).map
	SRC := ring.c main.c
	OBJ := $(SRC:.c=.o)
endif

ifeq	($(PLATFORM), HOST)
%.o : %.c
	@echo " "
	@echo "Generating Object Files..."
	@echo " "
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) -c $< -o $@

#Assembly Files
%.asm : %.c
	@echo " "
	@echo "Generating Assembly Files..."
	@echo " "
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS)- S $< -o $@
	
#Pre-Processed Files
%.i : %.c
	@echo " "
	@echo "Generating Pre-Processed Files..."
	@echo " "
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) -E $< -o $@

#Compile and Link to Final Executable
build : $(OBJ)
	@echo " "
	@echo "Linking and generating Final executable..."
	@echo " "
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET)
	
clean :
	rm -f *.o *.elf *.map *.i linux
	@echo " "
	@echo "Generated Files Removed."
	@echo " "

else
%.o : %.c
	@echo " "
	@echo "Generating Object Files..."
	@echo " "
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) -c $< -o $@

#Assembly Files
%.asm : %.c
	@echo " "
	@echo "Generating Assembly Files..."
	@echo " "
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS)- S $< -o $@
	
#Pre-Processed Files
%.i : %.c
	@echo " "
	@echo "Generating Pre-Processed Files..."
	@echo " "
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) -E $< -o $@

#Compile and Link to Final Executable
build : $(OBJ)
	@echo " "
	@echo "Linking and generating Final executable..."
	@echo " "
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET).elf
	
clean :
	rm -f *.o *.elf *.map *.i 
	@echo " "
	@echo "Generated Files Removed."
	@echo " "
endif


