#=======================================================================
# UCB VLSI FLOW: Makefile for riscv-custom-bmarks
#-----------------------------------------------------------------------
# Yunsup Lee (yunsup@cs.berkeley.edu)
# Modified by Jihoon Park

XLEN ?= 64

default: all

riscv_bmark_dir = /home/jihoonpark/Projects/riscv-tests/benchmarks
src_dir = .

#--------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------

bmarks = \
	hellorocket \
	helloworld \

#--------------------------------------------------------------------
# Build rules
#--------------------------------------------------------------------

# Refer to https://gcc.gnu.org/onlinedocs/gcc/ for gcc options
# Pay attention to ... 
#   RISC-V options(-mfoo),
#   Link options(-static, -nostdlib, -T, etc), 
#   code-gen options (-ffoo, -fno-foo),
#   optimize options (-01, -02, -03, ..)

RISCV_PREFIX ?= riscv$(XLEN)-unknown-elf-
RISCV_GCC ?= $(RISCV_PREFIX)gcc
RISCV_GCC_OPTS ?= -DPREALLOCATE=1 -mcmodel=medany -static -std=gnu99 -O2 -ffast-math -fno-common -fno-builtin-printf -fno-tree-loop-distribute-patterns
RISCV_LINK ?= $(RISCV_GCC) -T $(riscv_bmark_dir)/common/test.ld $(incs)
RISCV_LINK_OPTS ?= -static -nostdlib -nostartfiles -lm -lgcc -T $(riscv_bmark_dir)/common/test.ld
RISCV_OBJDUMP ?= $(RISCV_PREFIX)objdump --disassemble-all --disassemble-zeroes --section=.text --section=.text.startup --section=.text.init --section=.data
RISCV_SIM ?= spike --isa=rv$(XLEN)gc
ADD_OPTS ?= 

incs  += -I$(riscv_bmark_dir)/../env -I$(riscv_bmark_dir)/common $(addprefix -I$(src_dir)/, $(bmarks))
objs  := 

define compile_template
$(1).riscv: $(wildcard $(src_dir)/$(1)/*) $(wildcard $(riscv_bmark_dir)/common/*)
	$$(RISCV_GCC) $$(incs) $$(RISCV_GCC_OPTS) -o $$@ $(wildcard $(src_dir)/$(1)/*.c) $(wildcard $(riscv_bmark_dir)/common/*.c) $(wildcard $(riscv_bmark_dir)/common/*.S) $$(RISCV_LINK_OPTS) $$(ADD_OPTS)
endef

$(foreach bmark,$(bmarks),$(eval $(call compile_template,$(bmark))))

#------------------------------------------------------------
# Build and run benchmarks on riscv simulator

bmarks_riscv_bin  = $(addsuffix .riscv,  $(bmarks))
bmarks_riscv_dump = $(addsuffix .riscv.dump, $(bmarks))
bmarks_riscv_out  = $(addsuffix .riscv.out,  $(bmarks))

$(bmarks_riscv_dump): %.riscv.dump: %.riscv
	$(RISCV_OBJDUMP) $< > $@

$(bmarks_riscv_out): %.riscv.out: %.riscv
	$(RISCV_SIM) $< > $@

riscv: $(bmarks_riscv_dump)
run: $(bmarks_riscv_out)

junk += $(bmarks_riscv_bin) $(bmarks_riscv_dump) $(bmarks_riscv_temp) $(bmarks_riscv_hex) $(bmarks_riscv_out)


#------------------------------------------------------------
# Clean up

clean:
	rm -rf $(objs) $(junk) *.o *.s *.i
