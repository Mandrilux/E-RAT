class SocketServer
{
    public:
        SocketServer(int port);
        ~SocketServer();

    protected:
        SOCKET mastersocket;
};
