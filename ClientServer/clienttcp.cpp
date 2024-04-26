#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <chrono>
#include <thread>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_context io_context;

        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);
        auto endpoint = resolver.resolve("localhost", "666");
        
        boost::asio::connect(socket, endpoint);

        std::cout << "Connected to the server." << std::endl;

        std::vector<std::string> messages = {
            "Server",
            "Connecting",
            "People"
        };

        for (const auto& message : messages) {
            boost::asio::write(socket, boost::asio::buffer(message));
            std::cout << "Sent: " << message << std::endl;

            char response[1024] = {0}; // Буфер для ответа
            size_t length = socket.read_some(boost::asio::buffer(response));

            std::cout << "Received acknowledgment from server: " << std::string(response, length) << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        socket.close();
        std::cout << "Connection closed." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}