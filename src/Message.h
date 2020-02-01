//
// Created by wurmel_a on 25/09/17.
//

#ifndef NETWORK_MESSAGE_H
#define NETWORK_MESSAGE_H

#include <vector>

namespace ERat {
    class Message {
    public:
        enum    MessageType {
            Unknown = 0,
            Cmd = 1
        };


#if __linux__ || __APPLE__
	struct __attribute__((packed)) AMessage {
            MessageType type;
            unsigned int bodySize;
            char    *body;
        };

#else
	#include "packed.h"
	struct AMessage {
            unsigned short magicNumber;
            MessageType type;
            unsigned int bodySize;
            char    *body;
        } PACKED;
	#include "endpacked.h"
#endif

        enum { headerSize = sizeof(MessageType) + sizeof(unsigned int) };
        enum { maxBodySize = 512 };

    public:
        Message(MessageType const&);
        Message(Message const&);
        ~Message();

    public:
        void    setBody(const char *, unsigned int);
        char    *getBody();
        char const* getBody() const;
        void    *data();
        bool    decodeHeader();
        bool    encodeHeader();
        void    encodeData();
        unsigned int    getBodySize() const;
        unsigned int    totalSize() const;
        MessageType getType() const;
        void    setType(MessageType);

    private:
        unsigned int    _bodySize;
        AMessage    _message;
        std::vector<char>   _data;
    };
}

#endif //NETWORK_MESSAGE_H
