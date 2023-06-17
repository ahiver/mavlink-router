#include "tlog.h"

#include <assert.h>
#include <endian.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>

#include <common/log.h>
#include <common/util.h>

// bool TLog::_start_timeout()
bool TLog::_logging_start_timeout()
{
    return true;
}

bool TLog::start()
{
    if (!LogEndpoint::start()) {
        return false;
    }

    return true;
}

void TLog::stop()
{
    if (_file == -1) {
        log_info("TLog not started");
        return;
    }

    LogEndpoint::stop();
}

int TLog::write_msg(const struct buffer *buffer)
{
    if (_file == -1 && !start()) {
        log_warning("Failed to initialize log.");
        return -1;
    }

    uint64_t ms_since_epoch =
        std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::system_clock::now().time_since_epoch()).count();

    ms_since_epoch = htobe64(ms_since_epoch);

    write(_file, (void*)&ms_since_epoch, sizeof(uint64_t));
    write(_file, buffer->data, buffer->len);
    return buffer->len;
}