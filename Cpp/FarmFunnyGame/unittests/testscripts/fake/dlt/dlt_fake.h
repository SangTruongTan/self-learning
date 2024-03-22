/**
 ******************************************************************************
 * @file           : dlt_logger.h
 * @brief          : Header file to fake the dlt logger in order to reduce the
 *                   cost of the executation.
 ******************************************************************************
 * @attention
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2024, Sang Tan Truong.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Sang Tan Truong nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DLT_LOGGER_H
#define __DLT_LOGGER_H

/* Includes ------------------------------------------------------------------*/
#include <dlt/dlt_user.h>

/* Definitions ---------------------------------------------------------------*/
DltReturnValue dlt_unregister_app(void) {
    DltReturnValue retval{DLT_RETURN_TRUE};
    return retval;
}

DltReturnValue dlt_register_app([[maybe_unused]] const char *apid,
                                [[maybe_unused]] const char *description) {
    DltReturnValue retval{DLT_RETURN_TRUE};
    return retval;
}

DltReturnValue dlt_register_context([[maybe_unused]] DltContext *handle,
                                    [[maybe_unused]] const char *contextid,
                                    [[maybe_unused]] const char *description) {
    DltReturnValue retval{DLT_RETURN_TRUE};
    return retval;
}

DltReturnValue
dlt_check_library_version([[maybe_unused]] const char *user_major_version,
                          [[maybe_unused]] const char *user_minor_version) {
    DltReturnValue retval{DLT_RETURN_TRUE};
    return retval;
}

DltReturnValue
dlt_user_log_write_start([[maybe_unused]] DltContext *handle,
                         [[maybe_unused]] DltContextData *log,
                         [[maybe_unused]] DltLogLevelType loglevel) {
    DltReturnValue retval{DLT_RETURN_TRUE};
    return retval;
}

DltReturnValue dlt_unregister_context([[maybe_unused]] DltContext *handle) {
    DltReturnValue retval{DLT_RETURN_TRUE};
    return retval;
}

DltReturnValue
dlt_user_log_write_constant_string([[maybe_unused]] DltContextData *log,
                                   [[maybe_unused]] const char *text) {
    DltReturnValue retval{DLT_RETURN_TRUE};
    return retval;
}
DltReturnValue dlt_user_log_write_finish([[maybe_unused]] DltContextData *log) {
    DltReturnValue retval{DLT_RETURN_TRUE};
    return retval;
}

#endif /* __DLT_LOGGER_H */
