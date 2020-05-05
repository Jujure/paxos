#include "misc/fd.hh"

#include "misc/socket.hh"
#include "misc/unistd.hh"

#include <iostream>

namespace misc
{
    FileDescriptor& FileDescriptor::operator=(FileDescriptor&& fileDescriptor)
    {
        if (fd_ != -1)
            sys::close(fd_);
        fd_ = std::exchange(fileDescriptor.fd_, -1);
        return *this;
    }

    FileDescriptor::~FileDescriptor()
    {
        if (*this)
        {
            sys::close(fd_);
            std::cerr << "Closed " << fd_ << "\n";
        }
    }

    FileDescriptor::operator int() const&
    {
        return fd_;
    }

    FileDescriptor::operator bool() const&
    {
        return fd_ >= 0;
    }

    void FileDescriptor::fcntl_set(int flags)
    {
        sys::fcntl_set(fd_, flags);
    }

} // namespace misc
