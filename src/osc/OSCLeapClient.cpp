#include <osc/OSCLeapClient.hpp>

using namespace ctag;
using namespace ctag::osc;

// osc leap client class

OSCLeapClient::OSCLeapClient(const std::string ip, const unsigned int port):
    buffer{new char[kMaxPacketSize]},
    ip{ip},
    port{port},
    packetStream{buffer, kMaxPacketSize},
    socket{IpEndpointName(ip.c_str(), port)} {
    // send the "connect" message, and therefore register with the server:
    this->connect();
}

void OSCLeapClient::clear() {
    ::operator delete(this->buffer);
    this->packetStream.Clear();
}

void OSCLeapClient::send() {
    // send the packet stream over the network
    this->socket.Send(this->packetStream.Data(), this->packetStream.Size());
    // clear the packet stream
    this->packetStream.Clear();
}

::osc::OutboundPacketStream &OSCLeapClient::message(std::string path) {
  return this->packetStream << ::osc::BeginMessage(path.c_str());
}

OSCLeapClient::~OSCLeapClient() {
    // send the "disconnect" message, and close the socket connection:
    this->disconnect();
    this->clear();
}

void OSCLeapClient::connect() {
    this->message("/server/connect") << ::osc::EndMessage;
    this->send();
}

void OSCLeapClient::disconnect() {
    this->message("/server/disconnect") << ::osc::EndMessage;
    this->send();
}