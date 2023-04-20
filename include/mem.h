/**
 * @file mem.h
 * @author 王彬浩 (SPGGOGOGO@outlook.com)
 * @brief kernel层，内存相关头文件
 * @version 1.1
 * @date 2023-04-20
 * @copyright Copyright (c) 2023
 * @revisionHistory 
 *  <table> 
 *   <tr><th> 版本 <th>作者 <th>日期 <th>修改内容 
 *   <tr><td> 0.1 <td>jivin <td>2010-03-08 <td>Created 
 *   <tr><td> 1.0 <td>王彬浩 <td> 2022-07-08 <td>Standardized 
 *   <tr><td> 1.1 <td>王彬浩 <td> 2023-04-20 <td>optimized 
 *  </table>
 */
#ifndef ACORAL_MEM_H
#define ACORAL_MEM_H
#include "autocfg.h"

#include "hal.h"

/**
 * 伙伴系统部分
*/
unsigned int buddy_init(unsigned int start, unsigned int end);
void* buddy_malloc(unsigned int  size);
void buddy_free(void *p);
void buddy_scan(void);

#define acoral_malloc(size) buddy_malloc(size)
#define acoral_free(ptr) buddy_free(ptr)
#define acoral_malloc_size(size) buddy_malloc_size(size)
#define acoral_mem_init(start,end) buddy_init(start,end)
#define acoral_mem_scan() buddy_scan()

#ifdef CFG_MEM2
   void * v_malloc(int size);
   void v_free(void * p);
   void v_mem_init(void);
   void v_mem_scan(void);
   #define acoral_mem_init2() v_mem_init()
   #define acoral_malloc2(size) v_malloc(size)
   #define acoral_free2(p) v_free(p)
   #define acoral_mem_scan2() v_mem_scan()
#endif

#define LEVEL 14  ///<最大层数
#define BLOCK_INDEX(index) ((index)>>1) ///<bitmap的index换算，因为除去最大内存块的剩余层中64块用一个32位图表示，所以要除以2
#define BLOCK_SHIFT 7 ///<基本内存块偏移量
#define BASIC_BLOCK_SIZE (1<<BLOCK_SHIFT) ///<基本内存块大小 128B

enum acoralMemAllocStateEnum{
   MEM_NO_ALLOC,  ///<内存系统状态定义：容量太小不可分配
   MEM_OK         ///<内存系统状态定义：容量足够可以分配
};

/**
 * @brief 内存块层数结构体，用于回收内存块时，描述要回收的内存块的大小。
 * 因为知道回收的起始地址，所以就知道要回收的这块内存的第一块基本内存块的编号是多少，那只要知道了这个基本内存块是哪一层分配出去的，就知道实际分配了多少大小的内存。
 * 详见书p131
 * 
 */
typedef struct{
	char level;
}acoral_block_t;

/**
 * @brief 内存控制块结构体
 * 
 */
typedef struct{
	int *free_list[LEVEL];  ///<各层空闲位图链表
	unsigned int *bitmap[LEVEL];    ///<各层内存状态位图块，两种情况：一. 最大内存块层，为一块内存空闲与否；二.其余层，1 标识两块相邻内存块有一块空闲，0 标识没有空闲
	int free_cur[LEVEL];    ///<各层空闲位图链表头
	unsigned int num[LEVEL];        ///<各层内存块个数
	char level;               ///<层数 
	unsigned char state;              ///<状态
	unsigned int start_adr;         ///<内存起始地址
	unsigned int end_adr;           ///<内存终止地址
	unsigned int block_num;         ///<基本内存块数
	unsigned int free_num;          ///<空闲基本内存块数
	unsigned int block_size;        ///<基本内存块大小
}acoral_block_ctr_t;

/**
 * 资源系统部分
*/

#include "core.h"
#include "list.h"
#define ACORAL_MAX_POOLS 40

enum acoralResourceTypeEnum{
   ACORAL_RES_THREAD,
   ACORAL_RES_EVENT,
   ACORAL_RES_TIMER,
   ACORAL_RES_DRIVER,
   /**
    * pegasus  0719
   */
   ACORAL_RES_MSG,
   ACORAL_RES_MST
};

/*------------------*/
/* pegasus  0719*/
/*------------------*/


#define ACORAL_POOL_INDEX_BIT 0
#define ACORAL_POOL_ID_BIT 0

#define ACORAL_RES_TYPE_BIT 10
#define ACORAL_RES_INDEX_BIT 14
#define ACORAL_RES_INDEX_INIT_BIT 16
#define ACORAL_RES_ID_BIT 24

#define ACORAL_POOL_INDEX_MASK 0x000003FF
#define ACORAL_POOL_ID_MASK    0x00003FFF

#define ACORAL_RES_TYPE_MASK   0x00003c00
#define ACORAL_RES_INDEX_MASK  0x00FFC000
#define ACORAL_RES_ID_MASK     0x00FFFFFF

enum acoralResourceReturnValEnum{
   ACORAL_RES_NO_RES,
   ACORAL_RES_NO_POOL,
   ACORAL_RES_NO_MEM,
   ACORAL_RES_MAX_POOL
};

#define ACORAL_RES_TYPE(id) ((id&ACORAL_RES_TYPE_MASK)>>ACORAL_RES_TYPE_BIT) ///<根据资源ID获取某一资源数据块

typedef union {
   int id;
   int next_id;
}acoral_res_t;

/**
 * @brief  资源池控制块
 * 
 */
typedef struct {
  unsigned int type;
  unsigned int size;            ///<size of one single resource eg.size of TCB
  unsigned int num_per_pool;    ///<the amount of resource in one pool eg.there are 20 TCBs in one TCB pool
  unsigned int num;             ///<the amount of pools which contain a certain type of resource(maybe TCB) in system at present will be added once one pool created; restrict by max_pools below;
  unsigned int max_pools;       ///<upbound of the amount of pools for this type. eg. the number of TCB pool limited to 2 because that there are at most 40 thread in system at one time and every TCB pool contains 20.
  acoral_list_t *free_pools;
  acoral_list_t *pools,list[2];
  unsigned char *name;
}acoral_pool_ctrl_t;

/**
 * @brief  资源池
*/
typedef struct {
   void *base_adr; ///<这个有两个作用，在为空闲的时候,它指向下一个pool，否则为它管理的资源的基地址
   void *res_free;
   int id;
   unsigned int size;
   unsigned int num;
   unsigned int position;
   unsigned int free_num;
   acoral_pool_ctrl_t *ctrl;
   acoral_list_t ctrl_list;
   acoral_list_t free_list;
}acoral_pool_t;

void acoral_mem_sys_init();
unsigned int buddy_malloc_size(unsigned int size);
acoral_pool_t *acoral_get_pool_by_id(int id);
acoral_pool_t *acoral_get_free_pool(void);
unsigned int acoral_create_pool(acoral_pool_ctrl_t *pool_ctrl);
void acoral_pool_res_init(acoral_pool_t *pool);
void acoral_release_pool(acoral_pool_ctrl_t *pool_ctrl);
acoral_res_t *acoral_get_res(acoral_pool_ctrl_t *pool_ctrl);
void acoral_release_res(acoral_res_t *res);
acoral_res_t * acoral_get_res_by_id(int id);
void acoral_pool_res_init(acoral_pool_t * pool);
void acoral_res_sys_init(void);
void acoral_pool_ctrl_init(acoral_pool_ctrl_t *pool_ctrl);

#endif
