#pragma once

#include <chrono>

#include <osc/OscOutboundPacketStream.h>
#include <ip/UdpSocket.h>

#include <osc/OSCLeapClient.hpp>


namespace ctag::osc {

    // Max size of an osc bundle/message etc
    constexpr size_t kMaxPacketSize {8096u}; // smol buffer
    constexpr unsigned int DEFAULT_PORT {9000};
    constexpr std::string DEFAULT_IP {"127.0.0.1"};

    /**
     * Simple OSC-Client that sends the leap motion data to the osc-server
     */
    class OSCLeapClient {
    public:
        /**
         * @brief Generate a new leap client that automatically connects to the defined server.
         *
         * @param ip The IP to send to, default: 127.0.0.1
         * @param port The Port ot send to, default: 9000
         */
        explicit OSCLeapClient(const std::string ip = DEFAULT_IP,
                               const unsigned int port = DEFAULT_PORT);

        // Public Interface
        // ----------------

        /**
         * @brief Construct an osc message
         *
         * @param path The path to send to
         */
        ::osc::OutboundPacketStream& message(std::string path);

        /**
         * @brief Send the osc package that is currently contained within
         */
        void send();

         /**
          * @brief Free the internal buffer
          */
         void clear();

        /**
         * @brief Terminate the connection to the OSC-Server
         */
        ~OSCLeapClient();

    private:
        /**
         * @brief Connect to a server over a socket connection
         */
        void connect();

        /**
         * @brief Disconnect a socket connection that was established over udp
         */
        void disconnect();

        // Properties

        const std::string ip;
        const unsigned int port;
        char * buffer;
        ::osc::OutboundPacketStream packetStream;
        UdpTransmitSocket socket;
    };
}