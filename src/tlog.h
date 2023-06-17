#pragma once

#include "logendpoint.h"

#define BUFFER_LEN 2048

class TLog : public LogEndpoint {
public:
    // TLog(const char *logs_dir, LogMode mode, unsigned long min_free_space, unsigned long max_files)
    //     : LogEndpoint{"ULog", logs_dir, mode, min_free_space, max_files}
    // {
    // }
    TLog(LogOptions conf)
        : LogEndpoint{"TLog", conf}
    {
    }

    bool start() override;
    void stop() override;

    int write_msg(const struct buffer *pbuf) override;
    int flush_pending_msgs() override { return -ENOSYS; }

protected:
    ssize_t _read_msg(uint8_t *buf, size_t len) override { return 0; };
    // bool _start_timeout() override;
    bool _logging_start_timeout() override;

    const char *_get_logfile_extension() override { return "tlog"; };
};