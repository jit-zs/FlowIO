#ifndef FLOWIO_FILESTREAM_HPP
#define FLOWIO_FILESTREAM_HPP
#include <stdio.h>
#include <filesystem>

#include <FlowIO/io_error.hpp>
namespace fio {
    enum class write_mode {
        append,
        create
    };
    class binary_stream {
    public:
    private:
        enum class access_mode{
            read,
            write,
            none
        }mCurrentAccessMode = access_mode::none;
        FILE* mFile = nullptr;
        const char* mLastErr = nullptr;
    public:
        binary_stream(const binary_stream& other) = delete;
        binary_stream();
        ~binary_stream();
        const char* open_error_str() const;
        /// @brief Opens the stream for a writing operation
        /// @param file File to write or append to
        /// @param mode Wether we want to append or create a new file
        /// @return If an issue occurs the stream will return false and loa
        bool write_open(const std::filesystem::path& file, write_mode mode = write_mode::create);
        /// @brief Opens the stream for a reading operaton
        /// @param file 
        /// @return If an issue occurs the stream will return false and load a failure reason as the last 
        bool read_open(const std::filesystem::path& file);
        binary_stream& write(const void* bytes, size_t count);
        binary_stream& read(void* bytes, size_t count);

        /// @brief Closes the stream and finalizes the file
        /// @note - If the stream is already closed then the function returns early 
        /// @note - This function will throw an fio::io_error if the closing process fails
        void close();

        operator bool() const;
        bool is_open() const;
    private:
        bool _check_open() const;
        bool _write_open_file(const char* file, write_mode mode);
        bool _read_open_file(const char* file);
        void _raise_error(const char* errorMsg);
    };
}
#endif