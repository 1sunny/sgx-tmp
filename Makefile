# SGX_SDK ?= /opt/intel/sgxsdk
SGX_SDK := /opt/alibaba/teesdk/intel/sgxsdk
# SGX_MODE ?= HW
SGX_MODE := HW
# SGX_ARCH ?= x64
SGX_ARCH := x64
# SGX_DEBUG ?= 1
SGX_DEBUG := 1

$(info SGX_TRUSTED_LIBRARY_PATH is $(SGX_TRUSTED_LIBRARY_PATH))
$(info SGX_SDK is $(SGX_SDK))

include $(SGX_SDK)/buildenv.mk

ifeq ($(shell getconf LONG_BIT), 32)
	SGX_ARCH := x86
else ifeq ($(findstring -m32, $(CXXFLAGS)), -m32)
	SGX_ARCH := x86
endif

ifeq ($(SGX_ARCH), x86)
	SGX_COMMON_FLAGS := -m32
	SGX_LIBRARY_PATH := $(SGX_SDK)/lib
	SGX_ENCLAVE_SIGNER := $(SGX_SDK)/bin/x86/sgx_sign
	SGX_EDGER8R := $(SGX_SDK)/bin/x86/sgx_edger8r
else
	SGX_COMMON_FLAGS := -m64
	SGX_LIBRARY_PATH := $(SGX_SDK)/lib64
	SGX_ENCLAVE_SIGNER := $(SGX_SDK)/bin/x64/sgx_sign
	SGX_EDGER8R := $(SGX_SDK)/bin/x64/sgx_edger8r
endif

ifeq ($(SGX_DEBUG), 1)
ifeq ($(SGX_PRERELEASE), 1)
$(error Cannot set SGX_DEBUG and SGX_PRERELEASE at the same time!!)
endif
endif

ifeq ($(SGX_DEBUG), 1)
        SGX_COMMON_FLAGS += -O0 -g
else
        SGX_COMMON_FLAGS += -O2
endif

SGX_COMMON_FLAGS += -Wall -Wextra -Winit-self -Wpointer-arith -Wreturn-type \
                    -Waddress -Wsequence-point -Wformat-security \
                    -Wmissing-include-dirs -Wfloat-equal -Wundef -Wshadow \
                    -Wcast-align -Wcast-qual -Wconversion -Wredundant-decls
SGX_COMMON_CFLAGS := $(SGX_COMMON_FLAGS) -Wjump-misses-init -Wstrict-prototypes -Wunsuffixed-float-constants
SGX_COMMON_CXXFLAGS := $(SGX_COMMON_FLAGS) -Wnon-virtual-dtor -std=c++11

######## App Settings ########

ifneq ($(SGX_MODE), HW)
	Urts_Library_Name := sgx_urts_sim
else
	Urts_Library_Name := sgx_urts
endif

App_C_Files := App/alloc.c App/App.c App/list.c App/encrypt.c App/salt.c
App_Include_Paths := -IInclude -IApp -I$(SGX_SDK)/include

App_C_Flags := -fPIC -Wno-attributes $(App_Include_Paths)

# Three configuration modes - Debug, prerelease, release
#   Debug - Macro DEBUG enabled.
#   Prerelease - Macro NDEBUG and EDEBUG enabled.
#   Release - Macro NDEBUG enabled.
ifeq ($(SGX_DEBUG), 1)
        App_C_Flags += -DDEBUG -UNDEBUG -UEDEBUG
else ifeq ($(SGX_PRERELEASE), 1)
        App_C_Flags += -DNDEBUG -DEDEBUG -UDEBUG
else
        App_C_Flags += -DNDEBUG -UEDEBUG -UDEBUG
endif

App_Cpp_Flags := $(App_C_Flags)
App_Link_Flags := -L$(SGX_LIBRARY_PATH) -l$(Urts_Library_Name) -lpthread -lcrypt

App_Cpp_Objects := $(App_C_Files:.c=.o)

App_Name := app

######## Enclave Settings ########

ifneq ($(SGX_MODE), HW)
	Trts_Library_Name := sgx_trts_sim
	Service_Library_Name := sgx_tservice_sim
else
	Trts_Library_Name := sgx_trts
	Service_Library_Name := sgx_tservice
endif
Crypto_Library_Name := sgx_tcrypto

### Enclave1 ###
Enclave_C_Files := $(wildcard Enclave/*.c)
Enclave_Include_Paths := -IInclude -IEnclave -I$(SGX_SDK)/include -I$(SGX_SDK)/include/tlibc -I$(SGX_SDK)/include/libcxx

Enclave_C_Flags := $(Enclave_Include_Paths) -nostdinc -fvisibility=hidden -fpie -ffunction-sections -fdata-sections $(MITIGATION_CFLAGS)
CC_BELOW_4_9 := $(shell expr "`$(CC) -dumpversion`" \< "4.9")
ifeq ($(CC_BELOW_4_9), 1)
	Enclave_C_Flags += -fstack-protector
else
	Enclave_C_Flags += -fstack-protector-strong
endif

Enclave_Cpp_Flags := $(Enclave_C_Flags) -nostdinc++
### Enclave1 ###

### Enclave2 ###
Enclave2_C_Files := $(wildcard Enclave2/*.c)

Enclave2_Include_Paths := -IInclude -IEnclave2 -I$(SGX_SDK)/include -I$(SGX_SDK)/include/tlibc -I$(SGX_SDK)/include/libcxx

Enclave2_C_Flags := $(Enclave2_Include_Paths) -nostdinc -fvisibility=hidden -fpie -ffunction-sections -fdata-sections $(MITIGATION_CFLAGS)
CC_BELOW_4_9 := $(shell expr "`$(CC) -dumpversion`" \< "4.9")
ifeq ($(CC_BELOW_4_9), 1)
	Enclave2_C_Flags += -fstack-protector
else
	Enclave2_C_Flags += -fstack-protector-strong
endif

Enclave2_Cpp_Flags := $(Enclave2_C_Flags) -nostdinc++
### Enclave2 ###

### Common ###

# Enable the security flags
Enclave_Security_Link_Flags := -Wl,-z,relro,-z,now,-z,noexecstack

# To generate a proper enclave, it is recommended to follow below guideline to link the trusted libraries:
#    1. Link sgx_trts with the `--whole-archive' and `--no-whole-archive' options,
#       so that the whole content of trts is included in the enclave.
#    2. For other libraries, you just need to pull the required symbols.
#       Use `--start-group' and `--end-group' to link these libraries.
# Do NOT move the libraries linked with `--start-group' and `--end-group' within `--whole-archive' and `--no-whole-archive' options.
# Otherwise, you may get some undesirable errors.
Enclave_Link_Flags := $(MITIGATION_LDFLAGS) $(Enclave_Security_Link_Flags) \
    -Wl,--no-undefined -nostdlib -nodefaultlibs -nostartfiles -L$(SGX_TRUSTED_LIBRARY_PATH) \
	-Wl,--whole-archive -l$(Trts_Library_Name) -Wl,--no-whole-archive \
	-Wl,--start-group -lsgx_tstdc -lsgx_tcxx -l$(Crypto_Library_Name) -l$(Service_Library_Name) -Wl,--end-group \
	-Wl,-Bstatic -Wl,-Bsymbolic -Wl,--no-undefined \
	-Wl,-pie,-eenclave_entry -Wl,--export-dynamic  \
	-Wl,--defsym,__ImageBase=0 -Wl,--gc-sections   \
	-Wl,--version-script=Enclave/Enclave.lds

### Common ###

### Enclave1 ###
Enclave_C_Objects := $(sort $(Enclave_C_Files:.c=.o))

Enclave_Name := enclave.so
Signed_Enclave_Name := enclave.signed.so
Enclave_Config_File := Enclave/Enclave.config.xml
Enclave_Test_Key := Enclave/Enclave_private_test.pem
### Enclave1 ###

### Enclave2 ###
Enclave2_C_Objects := $(sort $(Enclave2_C_Files:.c=.o))

Enclave2_Name := enclave2.so
Signed_Enclave2_Name := enclave2.signed.so
Enclave2_Config_File := Enclave2/Enclave2.config.xml
Enclave2_Test_Key := Enclave2/Enclave2_private_test.pem
### Enclave2 ###

ifeq ($(SGX_MODE), HW)
ifeq ($(SGX_DEBUG), 1)
	Build_Mode = HW_DEBUG
else ifeq ($(SGX_PRERELEASE), 1)
	Build_Mode = HW_PRERELEASE
else
	Build_Mode = HW_RELEASE
endif
else
ifeq ($(SGX_DEBUG), 1)
	Build_Mode = SIM_DEBUG
else ifeq ($(SGX_PRERELEASE), 1)
	Build_Mode = SIM_PRERELEASE
else
	Build_Mode = SIM_RELEASE
endif
endif


.PHONY: all target run
all: .config_$(Build_Mode)_$(SGX_ARCH)
	@$(MAKE) target

ifeq ($(Build_Mode), HW_RELEASE)
target:  $(App_Name) $(Enclave_Name)
	@echo "The project has been built in release hardware mode."
	@echo "Please sign the $(Enclave_Name) first with your signing key before you run the $(App_Name) to launch and access the enclave."
	@echo "To sign the enclave use the command:"
	@echo "   $(SGX_ENCLAVE_SIGNER) sign -key <your key> -enclave $(Enclave_Name) -out <$(Signed_Enclave_Name)> -config $(Enclave_Config_File)"
	@echo "You can also sign the enclave using an external signing tool."
	@echo "To build the project in simulation mode set SGX_MODE=SIM. To build the project in prerelease mode set SGX_PRERELEASE=1 and SGX_MODE=HW."


else
target: $(App_Name) $(Signed_Enclave_Name) $(Signed_Enclave2_Name)
# target: $(App_Name) $(Signed_Enclave2_Name)
ifeq ($(Build_Mode), HW_DEBUG)
	@echo "The project has been built in debug hardware mode."
else ifeq ($(Build_Mode), SIM_DEBUG)
	@echo "The project has been built in debug simulation mode."
else ifeq ($(Build_Mode), HW_PRERELEASE)
	@echo "The project has been built in pre-release hardware mode."
else ifeq ($(Build_Mode), SIM_PRERELEASE)
	@echo "The project has been built in pre-release simulation mode."
else
	@echo "The project has been built in release simulation mode."
endif

endif

run: all
ifneq ($(Build_Mode), HW_RELEASE)
	@$(CURDIR)/$(App_Name)
	@echo "RUN  =>  $(App_Name) [$(SGX_MODE)|$(SGX_ARCH), OK]"
endif

.config_$(Build_Mode)_$(SGX_ARCH):
	@rm -f .config_* $(App_Name) $(Enclave_Name) $(Signed_Enclave_Name) $(App_Cpp_Objects) App/Enclave_u.* $(Enclave_C_Objects) Enclave/Enclave_t.*
	@touch .config_$(Build_Mode)_$(SGX_ARCH)

######## App Objects ########

### Enclave1 ###

App/Enclave_u.h: $(SGX_EDGER8R) Enclave/Enclave.edl
	@cd App && $(SGX_EDGER8R) --untrusted ../Enclave/Enclave.edl --search-path ../Enclave --search-path $(SGX_SDK)/include
	@echo "GEN  =>  $@"

App/Enclave_u.c: App/Enclave_u.h

App/Enclave_u.o: App/Enclave_u.c
	@$(CC) $(SGX_COMMON_CFLAGS) $(App_C_Flags) -c $< -o $@
	@echo "CC   <=  $<"

### Enclave1 ###

### Enclave2 ###

App/Enclave2_u.h: $(SGX_EDGER8R) Enclave2/Enclave2.edl
	@cd App && $(SGX_EDGER8R) --untrusted ../Enclave2/Enclave2.edl --search-path ../Enclave2 --search-path $(SGX_SDK)/include
	@echo "GEN  =>  $@"

App/Enclave2_u.c: App/Enclave2_u.h

App/Enclave2_u.o: App/Enclave2_u.c
	@$(CC) $(SGX_COMMON_CFLAGS) $(App_C_Flags) -c $< -o $@
	@echo "CC   <=  $<"

### Enclave2 ###


App/%.o: App/%.c  App/Enclave_u.h App/Enclave2_u.h
	@$(CC) $(SGX_COMMON_CFLAGS) $(App_C_Flags) -c $< -o $@
	@echo "CC  <=  $<"

$(App_Name): App/Enclave_u.o App/Enclave2_u.o $(App_Cpp_Objects)
	@$(CC) $^ -o $@ $(App_Link_Flags)
	@echo "LINK =>  $@"

# App/%.o: App/%.c  App/Enclave2_u.h
# 	@$(CC) $(SGX_COMMON_CFLAGS) $(App_C_Flags) -c $< -o $@
# 	@echo "CC  <=  $<"

# $(App_Name): App/Enclave2_u.o $(App_Cpp_Objects)
# 	@$(CC) $^ -o $@ $(App_Link_Flags)
# 	@echo "LINK =>  $@"


######## Enclave1 Objects ########

Enclave/Enclave_t.h: $(SGX_EDGER8R) Enclave/Enclave.edl
	@cd Enclave && $(SGX_EDGER8R) --trusted ../Enclave/Enclave.edl --search-path ../Enclave --search-path $(SGX_SDK)/include
	@echo "GEN  =>  $@"

Enclave/Enclave_t.c: Enclave/Enclave_t.h

Enclave/Enclave_t.o: Enclave/Enclave_t.c
	@$(CC) $(SGX_COMMON_CFLAGS) $(Enclave_C_Flags) -c $< -o $@
	@echo "CC   <=  $<"

Enclave/%.o: Enclave/%.c Enclave/Enclave_t.h
	@$(CC) $(SGX_COMMON_CFLAGS) $(Enclave_Cpp_Flags) -c $< -o $@
	@echo "CC  <=  $<"

$(Enclave_Name): Enclave/Enclave_t.o $(Enclave_C_Objects)
	@$(CC) $^ -o $@ $(Enclave_Link_Flags)
	@echo "LINK =>  $@"

$(Signed_Enclave_Name): $(Enclave_Name)
ifeq ($(wildcard $(Enclave_Test_Key)),)
	@echo "There is no enclave test key<Enclave_private_test.pem>."
	@echo "The project will generate a key<Enclave_private_test.pem> for test."
	@openssl genrsa -out $(Enclave_Test_Key) -3 3072
endif
	@$(SGX_ENCLAVE_SIGNER) sign -key $(Enclave_Test_Key) -enclave $(Enclave_Name) -out $@ -config $(Enclave_Config_File)
	@echo "SIGN =>  $@"

######## Enclave1 Objects ########

######## Enclave2 Objects ########

Enclave2/Enclave2_t.h: $(SGX_EDGER8R) Enclave2/Enclave2.edl
	@cd Enclave2 && $(SGX_EDGER8R) --trusted ../Enclave2/Enclave2.edl --search-path ../Enclave2 --search-path $(SGX_SDK)/include
	@echo "GEN  =>  $@"

Enclave2/Enclave2_t.c: Enclave2/Enclave2_t.h

Enclave2/Enclave2_t.o: Enclave2/Enclave2_t.c
	@$(CC) $(SGX_COMMON_CFLAGS) $(Enclave2_C_Flags) -c $< -o $@
	@echo "CC   <=  $<"

Enclave2/%.o: Enclave2/%.c Enclave2/Enclave2_t.h
	@$(CC) $(SGX_COMMON_CFLAGS) $(Enclave2_Cpp_Flags) -c $< -o $@
	@echo "CC  <=  $<"

$(Enclave2_Name): Enclave2/Enclave2_t.o $(Enclave2_C_Objects)
	@$(CC) $^ -o $@ $(Enclave_Link_Flags)
	@echo "LINK =>  $@"

$(Signed_Enclave2_Name): $(Enclave2_Name)
ifeq ($(wildcard $(Enclave2_Test_Key)),)
	@echo "There is no enclave test key<Enclave_private_test.pem>."
	@echo "The project will generate a key<Enclave_private_test.pem> for test."
	@openssl genrsa -out $(Enclave2_Test_Key) -3 3072
endif
	@$(SGX_ENCLAVE_SIGNER) sign -key $(Enclave2_Test_Key) -enclave $(Enclave2_Name) -out $@ -config $(Enclave2_Config_File)
	@echo "SIGN =>  $@"

######## Enclave2 Objects ########

.PHONY: clean

clean:
	@rm -f .config_* $(App_Name) $(Enclave_Name) $(Enclave2_Name) $(Signed_Enclave_Name) $(Signed_Enclave2_Name) $(App_Cpp_Objects) App/Enclave_u.* App/Enclave2_u.* $(Enclave_C_Objects) $(Enclave2_C_Objects) Enclave/Enclave_t.* Enclave2/Enclave2_t.* $(Enclave_Test_Key) $(Enclave2_Test_Key)