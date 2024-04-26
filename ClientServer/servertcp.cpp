#include <iostream>
#include <boost/asio.hpp>
#include <vector>
#include <string>

using boost::asio::ip::tcp;

const size_t BUFFER_SIZE = 1024;

class CircularBuffer {
public:
    CircularBuffer(size_t capacity) : buffer_(capacity), head_(0), tail_(0), size_(0) {}

    void push_back(char value) {
        if (size_ < buffer_.size()) {
            buffer_[tail_++] = value;
            tail_ %= buffer_.size();
            ++size_;
        } else {
            std::cerr << "Buffer overflow" << std::endl;
        }
    }

    char pop_front() {
        if (size_ > 0) {
            char value = buffer_[head_++];
            head_ %= buffer_.size();
            --size_;
            return value;
        } else {
            throw std::out_of_range("Buffer underflow");
        }
    }

    size_t size() const {
        return size_;
    }

private:
    std::vector<char> buffer_;
    size_t head_;
    size_t tail_;
    size_t size_;
};


int main() {
    const unsigned short PORT = 666;

    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT));
        std::cout << "Server started, waiting for connection..." << std::endl;

        tcp::socket socket(io_context);
        acceptor.accept(socket);
        std::cout << "Client connected." << std::endl;

        CircularBuffer circularBuffer(BUFFER_SIZE);

        while (true) {
            std::vector<char> data(BUFFER_SIZE);
            boost::system::error_code error;

            size_t length = socket.read_some(boost::asio::buffer(data), error);

            if (error == boost::asio::error::eof) {
                std::cout << "Connection closed by client." << std::endl;
                break;
            } else if (error) {
                std::cerr << "Error reading from socket: " << error.message() << std::endl;
                break;
            }

            for (size_t i = 0; i < length; ++i) {
                circularBuffer.push_back(data[i]);
            }

            std::cout << "Received data from client: ";
            for (size_t i = 0; i < length; ++i) {
                std::cout << data[i];
            }
            std::cout << std::endl;

            std::string response = "Message received";
            boost::asio::write(socket, boost::asio::buffer(response));
            std::cout << "Sent acknowledgment to client." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}