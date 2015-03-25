#include "kprintf.h"
#include "Thread.h"
#include "backtrace.h"
#include "InterruptUtils.h"
#include "ArchThreads.h"
#include "KernelMemoryManager.h" // for use of "kernel_end_address"
#include "umap.h"
#include "ArchCommon.h"
#include "ArchMemory.h"
#include "Loader.h"
#include "arch_backtrace.h"

extern Thread* currentThread;

int backtrace(pointer *call_stack, int size, Thread *thread, bool use_stored_registers)
{
  if (!call_stack ||
      (use_stored_registers && !thread) ||
      (!use_stored_registers && thread != currentThread) ||
      size <= 1)
    return 0;

  void *ebp = 0;

  if (!use_stored_registers)
  {
    __asm__ __volatile__(" \
       movl %%ebp, %0\n"
        : "=g" (ebp)
    );
  }
  else
    ebp = (void*)thread->kernel_registers_->ebp;

  int i = 0;
  StackFrame *CurrentFrame = (StackFrame*)ebp;
  void *StackStart = (void*)((uint32)thread->kernel_stack_ + sizeof(thread->kernel_stack_)); // the stack "starts" at the high addresses...
  void *StackEnd = (void*)thread->kernel_stack_; // ... and "ends" at the lower ones.

  if (use_stored_registers)
    call_stack[i++] = thread->kernel_registers_->eip;

  void *StartAddress = (void*)0x80000000;
  void *EndAddress = (void*)ArchCommon::getFreeKernelMemoryEnd();

  while (i < size &&
      ADDRESS_BETWEEN(CurrentFrame, StackEnd, StackStart) &&
      ADDRESS_BETWEEN(CurrentFrame->return_address, StartAddress, EndAddress) &&
      ADDRESS_BETWEEN(StackEnd, StartAddress, EndAddress) &&
      ADDRESS_BETWEEN(StackStart, StartAddress, EndAddress))
  {
    call_stack[i++] = (pointer)CurrentFrame->return_address;
    CurrentFrame = CurrentFrame->previous_frame;
  }

  return i;
}

int backtrace_user(pointer *call_stack, int size, Thread *thread, bool /*use_stored_registers*/)
{
  if (!call_stack || !size || !thread->user_registers_)
    return 0;

  void *ebp = (void*)thread->user_registers_->ebp;
  StackFrame *CurrentFrame = (StackFrame*)ebp;
  StackFrame *CurrentFrameI = (StackFrame*)thread->loader_->arch_memory_.checkAddressValid(ebp);

  // the userspace stack is allowed to be anywhere in userspace
  void *StackStart = (void*)0x7fffffff;
  void *StackEnd = (void*)thread->user_arch_thread_info_->esp;

  void *StartAddress = (void*)0x1;
  void *EndAddress = (void*)0x80000000;

  int i = 0;
  while (i < size &&
      ADDRESS_BETWEEN(CurrentFrame, StackEnd, StackStart) &&
      ADDRESS_BETWEEN(StackEnd, StartAddress, EndAddress) &&
      ADDRESS_BETWEEN(StackStart, StartAddress, EndAddress) &&
      CurrentFrameI &&
      ADDRESS_BETWEEN(CurrentFrameI->return_address, StartAddress, EndAddress))
  {
    call_stack[i++] = (pointer)CurrentFrameI->return_address;
    CurrentFrame = CurrentFrameI->previous_frame;
    CurrentFrameI = (StackFrame*)thread->loader_->arch_memory_.checkAddressValid((uint32)CurrentFrameI->previous_frame);
  }

  return i;
}
