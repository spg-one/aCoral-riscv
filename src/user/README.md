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
* acoral_sem_init 初始化信号量
* acoral_sem_create 创建并初始化信号量
* acoral_sem_del 删除信号量
* acoral_sem_trypend 获取信号量(非阻塞)
* acoral_sem_pend 获取信号量(阻塞式)
* acoral_sem_post 释放信号量
* acoral_sem_getnum 得到当前信号量值
---
## 互斥量相关
* acoral_mutex_init 初始化互斥量
* acoral_mutex_create 创建并初始化互斥量
* acoral_mutex_del 删除互斥量
* acoral_mutex_trypend 获取互斥量（非阻塞式）
* acoral_mutex_pend 获取互斥量（优先级继承的优先级反转解决）
* acoral_mutex_pend2 获取互斥量（优先级天花板的优先级反转解决）
* acoral_mutex_post 释放互斥量