//
// Created by wurmel_a on 25/09/17.
//

#include <cstdio>
#include <cstring>
#include <iostream>
#include "Message.h"

ERat::Message::Message(MessageType const& type) : _data(headerSize + maxBodySize + 1, 0) {
    std::memset(&_message, 0, sizeof(_message));
    _message.body = nullptr;
    _message.bodySize = 0;
    _message.type = type;
}

ERat::Message::Message(Message const&other) : _data(headerSize + maxBodySize + 1) {
    _message.bodySize = other._message.bodySize;
    _message.type = other._message.type;
    _message.body = new char[_message.bodySize];
    std::memcpy(_message.body, other._message.body, _message.bodySize);
}

char const* ERat::Message::getBody() const {
    return _message.body;
}

char    *ERat::Message::getBody() {
    return _message.body;
}

void    ERat::Message::setBody(const char *body, unsigned int bodySize) {
    if (_message.body) {
        delete[] _message.body;
    }
    _message.bodySize = bodySize;
    _message.body = new char[bodySize];
    std::memcpy(_message.body, body, bodySize);
}

void    *ERat::Message::data() {
    return _data.data();
}

unsigned int    ERat::Message::getBodySize() const {
    return _message.bodySize;
}

bool    ERat::Message::decodeHeader() {
  std::memcpy(&_message, _data.data(), headerSize);
    std::cout << "Decode type: <" << _message.type << ">" << std::endl;
    if (_message.bodySize > maxBodySize) {
        return false;
    }
    if (_message.body) {
        delete[] _message.body;
    }
    _message.body = new char[_message.bodySize];
    std::memset(_message.body, 0, _message.bodySize);
    return true;
}

void    ERat::Message::setType(MessageType type) {
    _message.type = type;
}

void    ERat::Message::encodeData() {
    if (_message.bodySize >= maxBodySize) {
        _message.bodySize = maxBodySize - 1;
    }
    std::memcpy(_data.data() + headerSize, _message.body, _message.bodySize);
}

bool    ERat::Message::encodeHeader() {
    if (_message.bodySize < maxBodySize)
        std::memcpy(_data.data(), &_message, headerSize);
    return _message.bodySize < maxBodySize;
}

ERat::Message::MessageType ERat::Message::getType() const {
    return _message.type;
}

unsigned int    ERat::Message::totalSize() const {
    return getBodySize() + headerSize;
}

ERat::Message::~Message() {
    if (_message.body) {
        delete[] _message.body;
    }
}
