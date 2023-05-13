# aCoral-I User Programming API

## 关于每个API的详细使用方法，参见doxygen文档
---
## 线程相关
* acoral_create_thread 创建线程
* acoral_suspend_self 挂起当前线程
* acoral_suspend_thread_by_id 挂起某个线程
* acoral_resume_thread_by_id 唤醒某个线程
* acoral_delay_self 将当前线程延时
* acoral_kill_thread_by_id 干掉某个线程
* acoral_thread_exit 结束当前线程
* acoral_change_prio_self 改变当前线程优先级
---
## 中断相关
* acoral_intr_attach 给某个plic中断绑定中断服务函数
* acoral_intr_detach 给某个plic中断解绑中断服务函数
* acoral_intr_unmask 使能某个中断
* acoral_intr_mask 除能某个中断
---
## 信号量相关
* acoral_sem_init 初始化一个信号量
* acoral_sem_create 创建信号量并初始化
* acoral_sem_del 删除一个信号量
* acoral_sem_trypend 信号量的申请(非阻塞)
* acoral_sem_pend 信号量的申请(阻塞式)
* acoral_sem_post 信号量的释放
* acoral_sem_getnum 得到当前信号量值