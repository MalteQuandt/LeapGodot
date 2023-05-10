#pragma once

#include <chrono>

#include <osc/OSCLeapClient.hpp>
#include <util/command_line_options.hpp>
#include <oscpp/client.hpp>

#include <boost/asio.hpp>


namespace ctag::osc {

    // Max size of an osc bundle/message etc
    constexpr size_t kMaxPacketSize = 65536u;

    /**
     * Simple OSC-Client that sends the leap motion data to the osc-server
     */
    class OSCLeapClient {
    public:
        /**
         * @brief Generate a new leap client that automatically connects to the defined server.
         *
         * @param clo The command line options container
         */
        explicit OSCLeapClient(const ctag::util::CLOptions& clo);

        // Public Interface
        // ----------------

        /**
         * @brief Prepare a package and send it over the network to the osc-server
         *
         * @param packet The packet to send
         */
        void sendPacket(const OSCPP::Client::Packet& packet);

        /**
         * @brief Prepare a packet
         *
         * @return The package to send
         */
         OSCPP::Client::Packet prepare();

        /**
         * @brief Terminate the connection to the OSC-Server
         */
        ~OSCLeapClient();

    private:
        /**
         * @brief Send a message over the network using udp, of the data that is contained in the current buffer
         *
         * @param packet_size The size of the osc packet to send
         */
        boost::system::error_code sendMessage(size_t packet_size);

        /**
         * @brief Connect to a server over a socket connection
         */
        void connect();

        /**
         * @brief Disconnect a socket connection that was established over udp
         */
        void disconnect();

        // Properties

        Address address;
        void * buffer;
        boost::asio::io_service io_service;
        boost::asio::ip::udp::socket socket;
        boost::asio::ip::udp::endpoint endpoint;
    };

    /**
     * @brief Get the current unix timestamp as milliseconds
     *         The standard duration in ms can be replaced with any duration type
     *
     * @tparam d The duration type to return
     *
     * @return The unix timestamp cast to the std::chrono duration specified in the function parameter
     */
     template<class d=std::chrono::milliseconds>
     unsigned long long int getUnixTimestamp() {
        return std::chrono::duration_cast<d>(std::chrono::system_clock::now().time_since_epoch()).count();
     }
}