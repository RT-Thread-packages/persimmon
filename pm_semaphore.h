/*
 * File      : pm_semaphore.h
 * COPYRIGHT (C) 2012-2017, Shanghai Real-Thread Technology Co., Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-11-05     realthread   the first version
 */

#pragma once
#include <rtthread.h>

namespace Persimmon
{

class Semaphore
{
public:
    enum type
    {
        FIFO = RT_IPC_FLAG_FIFO,	/**< FIFOed IPC. @ref IPC. */
        PRIO = RT_IPC_FLAG_PRIO,	/**< PRIOed IPC. @ref IPC. */
    };

    Semaphore(const char *name, rt_uint32_t value, rt_uint8_t flag = FIFO);
    virtual ~Semaphore();

    int take(int tick);
    void release(void);

private:
    rt_sem_t semaphore;
};

}

