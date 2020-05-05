/**
 * \file misc/fd.hh
 * \brief FileDescriptor declaration.
 */
#pragma once

#include <fcntl.h>
#include <memory>
#include <unistd.h>
#include <utility>

#include "misc/sys-wrapper.hh"

namespace misc
{
    /**
     * \class FileDescriptor
     * \brief A resource object representing a fd.
     */
    struct FileDescriptor
    {
        /**
         * \brief Construct a FileDescriptor from a given fd.
         * \param fd int
         */

        explicit FileDescriptor(int fd)
            : fd_{fd}
        {}

        FileDescriptor() = default;
        FileDescriptor(const FileDescriptor&) = delete;
        FileDescriptor& operator=(const FileDescriptor&) = delete;

        FileDescriptor(FileDescriptor&& fileDescriptor)
            : fd_{std::exchange(fileDescriptor.fd_, -1)}
        {}
        FileDescriptor& operator=(FileDescriptor&& fileDescriptor);

        ~FileDescriptor();

        /**
         * \brief Implicit conversion to int.
         */
        operator int() const&;

        /**
         * \brief Implicit conversion to bool.
         *
         * \return Whether or not the FileDescriptor holds a valid fd.
         */
        operator bool() const&;

        /**
        *   \brief man 2 fcntl
        */
        void fcntl_set(int flags);

        /**
         * \brief The fd held by the FileDescriptor object.
         */
        int fd_ = -1;
    };

    /**
     * \brief Alias to the smart pointer used to manage FileDescriptors
     * memory allocation.
     */
    using shared_fd = std::shared_ptr<FileDescriptor>;
} // namespace misc
