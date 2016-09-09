/*
 * (C) 2007-2010 Taobao Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 * Version: $Id$
 *
 * Authors:
 *   duolong <duolong@taobao.com>
 *
 */

#ifndef TBSYS_TIMEUTIL_H_
#define TBSYS_TIMEUTIL_H_

#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

namespace tbsys {

	/** 
	 * @brief linuxʱ�������򵥵ķ�װ
	 */
class CTimeUtil {
public:
    /**
     * �õ���ǰʱ��
     */
    static int64_t getTime();
    /**
     * �õ�����������ʱ��
     */
    static int64_t getMonotonicTime();
    /**
     * ��intת��20080101101010�ĸ�ʽ
     */ 
    static char *timeToStr(time_t t, char *dest);
    /**
     * ���ֽڴ�ת��ʱ��(����ʱ��)
     */
    static int strToTime(const char *str);
};

}

#endif
