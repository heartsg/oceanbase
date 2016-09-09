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

#include "tbnet.h"

namespace tbnet {
/**
  * ���캯������Transport���á�
  *
  * @param  owner:    ����������
  * @param  host:   ����ip��ַ��hostname
  * @param port:   �����˿�
  * @param streamer:   ���ݰ���˫��������packet������������������
  * @param serverAdapter:  ���ڷ������ˣ���Connection��ʼ����Channel����ʱ�ص�ʱ��
  */
TCPComponent::TCPComponent(Transport *owner, Socket *socket,
                           IPacketStreamer *streamer, IServerAdapter *serverAdapter) : IOComponent(owner, socket) {
    _connection = new TCPConnection(socket, streamer, serverAdapter);
    _connection->setIOComponent(this);
    _startConnectTime = 0;
    _isServer = false;
}

/*
 * ��������
 */
TCPComponent::~TCPComponent() {
    if (_connection) {
        _connection->setIOComponent(NULL);
        delete _connection;
        _connection = NULL;
    }
}

/*
 * ���ӵ�ָ���Ļ���
 *
 * @param  isServer: �Ƿ���ʼ��һ����������Connection
 * @return �Ƿ��ɹ�
 */
bool TCPComponent::init(bool isServer) {
    _socket->setSoBlocking(false);
    _socket->setSoLinger(false, 0);
    _socket->setReuseAddress(true);
    _socket->setIntOption(SO_KEEPALIVE, 1);
    _socket->setIntOption(SO_SNDBUF, 640000);
    _socket->setIntOption(SO_RCVBUF, 640000);
    // _socket->setTcpNoDelay(true);
    if (!isServer) {
        if (!socketConnect() && _autoReconn == false) {
            return false;
        }
    } else {
        _state = TBNET_CONNECTED;
    }
    _connection->setServer(isServer);
    _isServer = isServer;

    return true;
}

/*
 * ���ӵ�socket
 */
bool TCPComponent::socketConnect() {
    if (_state == TBNET_CONNECTED || _state == TBNET_CONNECTING) {
        return true;
    }
    _socket->setSoBlocking(false);
    if (_socket->connect()) {
        if (_socketEvent) {
            _socketEvent->addEvent(_socket, true, true);
        }
        _state = TBNET_CONNECTED; 
	_startConnectTime = tbsys::CTimeUtil::getTime();
    } else {
        int error = Socket::getLastError();
        if (error == EINPROGRESS || error == EWOULDBLOCK) {
            _state = TBNET_CONNECTING;
            if (_socketEvent) {
                _socketEvent->addEvent(_socket, true, true);
            }
        } else {
            _socket->close();
            _state = TBNET_CLOSED;
            TBSYS_LOG(ERROR, "���ӵ� %s ʧ��, %s(%d)", _socket->getAddr().c_str(), strerror(error), error);
            return false;
        }
    }
    return true;
}

/*
 * �ر�
 */
void TCPComponent::close() {
    if (_socket) {
        if (_socketEvent) {
            _socketEvent->removeEvent(_socket);
        }
        if (_connection && isConnectState()) {
            _connection->setDisconnState();
        }
        _socket->close();
        if (_connection) {
          _connection->clearInputBuffer(); // clear input buffer after socket closed
        }
        _state = TBNET_CLOSED;
    }
}

/*
 * �������ݿ�д��ʱ��Transport����
 *
 * @return �Ƿ��ɹ�, true - �ɹ�, false - ʧ�ܡ�
 */
bool TCPComponent::handleWriteEvent() {
    _lastUseTime = tbsys::CTimeUtil::getTime();
    bool rc = true;
    if (_state == TBNET_CONNECTED) {
        rc = _connection->writeData();
    } else if (_state == TBNET_CONNECTING) {
        int error = _socket->getSoError();
        if (error == 0) {
            enableWrite(true);
            _connection->clearOutputBuffer();
            _state = TBNET_CONNECTED;
        } else {
            TBSYS_LOG(ERROR, "���ӵ� %s ʧ��: %s(%d)", _socket->getAddr().c_str(), strerror(error), error);
            if (_socketEvent) {
                _socketEvent->removeEvent(_socket);
            }
            _socket->close();
            _state = TBNET_CLOSED;
        }
    }
    return rc;
}

/**
 * �������ݿɶ�ʱ��Transport����
 *
 * @return �Ƿ��ɹ�, true - �ɹ�, false - ʧ�ܡ�
 */
bool TCPComponent::handleReadEvent() {
    _lastUseTime = tbsys::CTimeUtil::getTime();
    bool rc = false;
    if (_state == TBNET_CONNECTED) {
        rc = _connection->readData();
    }
    return rc;
}

/*
 * ��ʱ����
 *
 * @param    now ��ǰʱ��(��λus)
 */
void TCPComponent::checkTimeout(int64_t now) {
    // �����Ƿ����ӳ�ʱ
    if (_state == TBNET_CONNECTING) {
        if (_startConnectTime > 0 && _startConnectTime < (now - static_cast<int64_t>(2000000))) { // ���ӳ�ʱ 2 ��
            _state = TBNET_CLOSED;
            TBSYS_LOG(ERROR, "���ӵ� %s ��ʱ.", _socket->getAddr().c_str());
            _socket->shutdown();
        }
    } else if (_state == TBNET_CONNECTED && _isServer == true && _autoReconn == false) { // ���ӵ�ʱ��, ֻ���ڷ�������
        int64_t idle = now - _lastUseTime;
        if (idle > static_cast<int64_t>(900000000)) { // ����15min�Ͽ�
            _state = TBNET_CLOSED;
            TBSYS_LOG(INFO, "%s ������: %ld (s) ���Ͽ�.", _socket->getAddr().c_str(), (idle/static_cast<int64_t>(1000000)));
            _socket->shutdown();
        }
    }
    // ��ʱ����
    _connection->checkTimeout(now);
}

}
