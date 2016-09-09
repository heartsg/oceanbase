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

#ifndef TBSYS_FILE_QUEUE_H
#define TBSYS_FILE_QUEUE_H

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "tblog.h"
#include "threadmutex.h"
#include "fileutil.h"

namespace tbsys {
    
    #define TBFQ_MAX_FILE_SIZE (1024*1024*16)    //16M
    #define TBFQ_MAX_THREAD_COUNT 60
    #define TBFQ_FILE_QUEUE_FLAG  0x31765166     // fQv1
    
	/** 
	 * @brief �������ڴ�����λ��
	 */
    typedef struct unsettle {
        uint32_t seqno;
        int offset;
    } unsettle;
    
    /** 
     * @brief ���нڵ�
     */
    typedef struct queue_item {
        unsettle pos;
        int flag;
        int len;
        char data[0];
    } queue_item;
    
    /** 
     * @brief ����������Ϣ
     */
    typedef struct qinfo_head {
        uint32_t read_seqno;    // ���ļ���seqno
        int read_offset;        // ���ļ���offset
        uint32_t write_seqno;        // д�ļ���seqno
        int write_filesize;     // д�ļ��Ĵ�С
        int queue_size;         // ���г���
        int exit_status;        // �˳�״̬
        int reserve[2];            
        unsettle pos[TBFQ_MAX_THREAD_COUNT]; // ���ڴ�����λ��
    } qinfo_head;
    
    class CFileUtil;
    /** 
     * @brief ������д���ļ��У����ļ��������ǰ����еķ����洢
     * ���ṩ�������еķ����������ļ� 
     */
    class CFileQueue {
        public:
            CFileQueue(const char *rootPath, const char *queueName, int maxFileSize = TBFQ_MAX_FILE_SIZE);
            ~CFileQueue(void);
            // д��һ����
            int push(void *data, int len);
            // ȡ��һ����
            queue_item *pop(uint32_t index = 0);
            // ɾ��һ����
            int clear();
            // �Ƿ�����
            int isEmpty();
            // ����������
            void finish(uint32_t index = 0);
            void backup(uint32_t index = 0);
        
        private:
            // �����ļ�����(��)
            int m_readFd;
            // �����ļ�����(д)
            int m_writeFd;
            // ͷ�ļ�����
            int m_infoFd;
            // queue��ͷ��Ϣ
            qinfo_head m_head;
            // ������·��
            char *m_queuePath;
            // �����ļ���������дһ���ļ�
            int m_maxFileSize;

        private:
            // ���������ļ�д
            inline int openWriteFile();  
            // ���������ļ���
            inline int openReadFile(); 
            //ɾ�����������ļ�
            inline int deleteReadFile();            
            // дheader
            inline int writeHead();
            // �ָ�����
            void recoverRecord();               
    };
}

#endif

//////////////////END
