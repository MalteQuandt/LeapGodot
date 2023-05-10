#include <oscpp/client.hpp>

#include <osc/OSCLeapClient.hpp>

using namespace ctag;
using namespace ctag::osc;
using namespace ctag::util;

using namespace boost::asio;
using namespace boost::asio::ip;
using namespace OSCPP;
using namespace OSCPP::Client;

// osc leap client class

OSCLeapClient::OSCLeapClient(const CLOptions &clo):
    buffer{new char[kMaxPacketSize]},
    address{clo.getAddress()},
    io_service{},
    socket(io_service),
    endpoint(address::from_string(std::get<0>(address)), std::get<1>(address)) {
    // send the "connect" message, and therefore register with the server:
    this->connect();
}

OSCPP::Client::Packet OSCLeapClient::prepare() {
    return {this->buffer, kMaxPacketSize};
}

void OSCLeapClient::sendPacket(const OSCPP::Client::Packet& packet) {
    this->sendMessage(packet.size());
}

OSCLeapClient::~OSCLeapClient() {
    // send the "disconnect" message, and close the socket connection:
    this->disconnect();
    ::operator delete(this->buffer);
}

void OSCLeapClient::connect() {
    // open the socket connection
    socket.open(udp::v4());
    // construct the osc packet
    OSCPP::Client::Packet packet(this->buffer, kMaxPacketSize);

    packet
        .openBundle(getUnixTimestamp())
            .openMessage("/server/connect", 0)
            .closeMessage()
        .closeBundle();

    // send the "connect" message
    this->sendMessage(packet.size());
}

void OSCLeapClient::disconnect() {
    // send the "disconnect" message
    OSCPP::Client::Packet packet(this->buffer, kMaxPacketSize);

    // construct the package
    packet
            .openBundle(getUnixTimestamp())
            .openMessage("/server/disconnect", 0)
            .closeMessage()
            .closeBundle();

    // send the "connect" message
    this->sendMessage(packet.size());

    // close the socket connection
    this->socket.close();
}

boost::system::error_code OSCLeapClient::sendMessage(const size_t packet_size) {
    boost::system::error_code err_code;
    socket.send_to(boost::asio::buffer(this->buffer,packet_size), this->endpoint, 0, err_code);
    return err_code;
}