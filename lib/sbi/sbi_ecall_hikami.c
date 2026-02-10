#include <sbi/sbi_ecall.h>
#include <sbi/sbi_ecall_interface.h>
#include <sbi/sbi_error.h>
#include <sbi/sbi_hart.h>
#include <sbi/sbi_trap.h>

static int sbi_ecall_hikami_handler(unsigned long extid, unsigned long funcid,
                                    struct sbi_trap_regs* regs,
                                    struct sbi_ecall_return* out) {
    if (funcid == SBI_EXT_HIKAMI_SET_DELEG_ILL_INSN) {
        /* a0: 1 to enable delegation, 0 to disable */
        sbi_hart_delegate_illegal_insn(regs->a0 ? true : false);
        return 0;
    }

    return SBI_ENOTSUPP;
}

struct sbi_ecall_extension ecall_hikami = {
    .extid_start = SBI_EXT_HIKAMI_BENCHMARK,
    .extid_end = SBI_EXT_HIKAMI_BENCHMARK,
    .handle = sbi_ecall_hikami_handler,
};
