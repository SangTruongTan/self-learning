/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : dlt_logger.h
 * @brief          : Header file to fake the dlt logger in order to reduce the
 *cost of the executation.
 ******************************************************************************
 * @attention
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Sang Tan Truong
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
