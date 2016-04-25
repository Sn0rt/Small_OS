#ifndef INCLUDE_TASK_H_
#define INCLUDE_TASK_H_

#include "types.h"
#include "pmm.h"
#include "vmm.h"

typedef enum task_state {
  TASK_UNINIT = 0,              /* 未初始化的 */
  TASK_SLEEPING = 1,            /* 睡眠中的 */
  TASK_RUNNABLE = 2,            /* 可运行也许正在运行 */
  TASK_ZOMBIE = 3,              /* 僵尸进程 */
} task_state;

// 内核线程切换上下文需要保存的信息
struct context {
  uint32_t esp;
  uint32_t ebp;
  uint32_t ebx;
  uint32_t esi;
  uint32_t edi;
  uint32_t eflags;
};

// 进程内存地址结构
struct mm_struct {
  pgd_t *pgd_dir;
};

// 进程控制块
struct task_struct {
  volatile task_state state;          /* 进程的当前状态 */
  pid_t pid;                    /* 进程标识符 */
  void *stack;                  /* 进程的内核栈地址 */
  struct mm_struct *mm;         /* 当前进程的内存地址映像 */
  struct context context;       /* 进程切换需要上下文信息 */
  struct task_struct *next;     /* 链表指针 */
};

// 全局pid值
extern pid_t now_pid;

// 内核线程创建
pid_t kernel_thread(int (*fn)(void *), void *arg);

// 内核退出函数
void kthread_exit();

#endif
