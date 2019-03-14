#ifndef AWS_HTTP_H
#define AWS_HTTP_H

/*
 * Copyright 2010-2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <aws/http/exports.h>

#include <aws/common/byte_buf.h>

enum aws_http_errors {
    AWS_ERROR_HTTP_UNKNOWN = 0x0800,
    AWS_ERROR_HTTP_PARSE,
    AWS_ERROR_HTTP_USER_CALLBACK_EXIT,
    AWS_ERROR_HTTP_INVALID_PARSE_STATE,
    AWS_ERROR_HTTP_CONNECTION_CLOSED,
    AWS_ERROR_HTTP_UNSUPPORTED_PROTOCOL,
    AWS_ERROR_HTTP_REACTION_REQUIRED,
    AWS_ERROR_HTTP_DATA_NOT_AVAILABLE,
    AWS_ERROR_HTTP_END_RANGE = 0x0C00,
};

enum aws_http_version {
    AWS_HTTP_VERSION_UNKNOWN, /* Invalid version. */
    AWS_HTTP_VERSION_1_0,
    AWS_HTTP_VERSION_1_1,
    AWS_HTTP_VERSION_2_0,
    AWS_HTTP_VERSION_COUNT, /* Max enum value */
};

enum aws_http_method {
    AWS_HTTP_METHOD_UNKNOWN, /* Invalid request. */
    AWS_HTTP_METHOD_CONNECT,
    AWS_HTTP_METHOD_DELETE,
    AWS_HTTP_METHOD_GET,
    AWS_HTTP_METHOD_HEAD,
    AWS_HTTP_METHOD_OPTIONS,
    AWS_HTTP_METHOD_PATCH,
    AWS_HTTP_METHOD_POST,
    AWS_HTTP_METHOD_PUT,
    AWS_HTTP_METHOD_TRACE,
    AWS_HTTP_METHOD_COUNT, /* Max enum value */
};

enum aws_http_header_name {
    /*
     * Valid request header key, but not mapped to an enum (e.g. uncommon headers are
     * not apart of this enum.
     */
    AWS_HTTP_HEADER_UNKNOWN,

    AWS_HTTP_HEADER_ACCEPT,
    AWS_HTTP_HEADER_ACCEPT_CHARSET,
    AWS_HTTP_HEADER_ACCEPT_ENCODING,
    AWS_HTTP_HEADER_ACCEPT_LANGUAGE,
    AWS_HTTP_HEADER_ACCEPT_RANGES,
    AWS_HTTP_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN,
    AWS_HTTP_HEADER_AGE,
    AWS_HTTP_HEADER_ALLOW,
    AWS_HTTP_HEADER_AUTHORIZATION,
    AWS_HTTP_HEADER_CACHE_CONTROL,
    AWS_HTTP_HEADER_CONNECTION,
    AWS_HTTP_HEADER_CONTENT_DISPOSITION,
    AWS_HTTP_HEADER_CONTENT_ENCODING,
    AWS_HTTP_HEADER_CONTENT_LANGUAGE,
    AWS_HTTP_HEADER_CONTENT_LENGTH,
    AWS_HTTP_HEADER_CONTENT_LOCATION,
    AWS_HTTP_HEADER_CONTENT_RANGE,
    AWS_HTTP_HEADER_CONTENT_TYPE,
    AWS_HTTP_HEADER_COOKIE,
    AWS_HTTP_HEADER_DATE,
    AWS_HTTP_HEADER_ETAG,
    AWS_HTTP_HEADER_EXPECT,
    AWS_HTTP_HEADER_EXPIRES,
    AWS_HTTP_HEADER_FORWARDED,
    AWS_HTTP_HEADER_FROM,
    AWS_HTTP_HEADER_HOST,
    AWS_HTTP_HEADER_IF_MATCH,
    AWS_HTTP_HEADER_IF_MODIFIED_SINCE,
    AWS_HTTP_HEADER_IF_NONE_MATCH,
    AWS_HTTP_HEADER_IF_RANGE,
    AWS_HTTP_HEADER_IF_UNMODIFIED_SINCE,
    AWS_HTTP_HEADER_KEEP_ALIVE,
    AWS_HTTP_HEADER_LAST_MODIFIED,
    AWS_HTTP_HEADER_LINK,
    AWS_HTTP_HEADER_LOCATION,
    AWS_HTTP_HEADER_MAX_FORWARDS,
    AWS_HTTP_HEADER_ORIGIN,
    AWS_HTTP_HEADER_PROXY_AUTHENTICATE,
    AWS_HTTP_HEADER_PROXY_AUTHORIZATION,
    AWS_HTTP_HEADER_RANGE,
    AWS_HTTP_HEADER_REFERRER,
    AWS_HTTP_HEADER_REFRESH,
    AWS_HTTP_HEADER_RETRY_AFTER,
    AWS_HTTP_HEADER_SERVER,
    AWS_HTTP_HEADER_SET_COOKIE,
    AWS_HTTP_HEADER_STRICT_TRANSPORT_SECURITY,
    AWS_HTTP_HEADER_TRANSFER_ENCODING,
    AWS_HTTP_HEADER_UPGRADE,
    AWS_HTTP_HEADER_USER_AGENT,
    AWS_HTTP_HEADER_VARY,
    AWS_HTTP_HEADER_VIA,
    AWS_HTTP_HEADER_WWW_AUTHENTICATE,
};

enum aws_http_code {
    AWS_HTTP_CODE_UNKNOWN, /* Invalid status code. */
    AWS_HTTP_CODE_REQUEST_NOT_MADE = -1,
    AWS_HTTP_CODE_CONTINUE = 100,
    AWS_HTTP_CODE_SWITCHING_PROTOCOLS = 101,
    AWS_HTTP_CODE_PROCESSING = 102,
    AWS_HTTP_CODE_OK = 200,
    AWS_HTTP_CODE_CREATED = 201,
    AWS_HTTP_CODE_ACCEPTED = 202,
    AWS_HTTP_CODE_NON_AUTHORITATIVE_INFORMATION = 203,
    AWS_HTTP_CODE_NO_CONTENT = 204,
    AWS_HTTP_CODE_RESET_CONTENT = 205,
    AWS_HTTP_CODE_PARTIAL_CONTENT = 206,
    AWS_HTTP_CODE_MULTI_STATUS = 207,
    AWS_HTTP_CODE_ALREADY_REPORTED = 208,
    AWS_HTTP_CODE_IM_USED = 226,
    AWS_HTTP_CODE_MULTIPLE_CHOICES = 300,
    AWS_HTTP_CODE_MOVED_PERMANENTLY = 301,
    AWS_HTTP_CODE_FOUND = 302,
    AWS_HTTP_CODE_SEE_OTHER = 303,
    AWS_HTTP_CODE_NOT_MODIFIED = 304,
    AWS_HTTP_CODE_USE_PROXY = 305,
    AWS_HTTP_CODE_SWITCH_PROXY = 306,
    AWS_HTTP_CODE_TEMPORARY_REDIRECT = 307,
    AWS_HTTP_CODE_PERMANENT_REDIRECT = 308,
    AWS_HTTP_CODE_BAD_REQUEST = 400,
    AWS_HTTP_CODE_UNAUTHORIZED = 401,
    AWS_HTTP_CODE_PAYMENT_REQUIRED = 402,
    AWS_HTTP_CODE_FORBIDDEN = 403,
    AWS_HTTP_CODE_NOT_FOUND = 404,
    AWS_HTTP_CODE_METHOD_NOT_ALLOWED = 405,
    AWS_HTTP_CODE_NOT_ACCEPTABLE = 406,
    AWS_HTTP_CODE_PROXY_AUTHENTICATION_REQUIRED = 407,
    AWS_HTTP_CODE_REQUEST_TIMEOUT = 408,
    AWS_HTTP_CODE_CONFLICT = 409,
    AWS_HTTP_CODE_GONE = 410,
    AWS_HTTP_CODE_LENGTH_REQUIRED = 411,
    AWS_HTTP_CODE_PRECONDITION_FAILED = 412,
    AWS_HTTP_CODE_REQUEST_ENTITY_TOO_LARGE = 413,
    AWS_HTTP_CODE_REQUEST_URI_TOO_LONG = 414,
    AWS_HTTP_CODE_UNSUPPORTED_MEDIA_TYPE = 415,
    AWS_HTTP_CODE_REQUESTED_RANGE_NOT_SATISFIABLE = 416,
    AWS_HTTP_CODE_EXPECTATION_FAILED = 417,
    AWS_HTTP_CODE_IM_A_TEAPOT = 418,
    AWS_HTTP_CODE_AUTHENTICATION_TIMEOUT = 419,
    AWS_HTTP_CODE_METHOD_FAILURE = 420,
    AWS_HTTP_CODE_UNPROCESSABLE_ENTITY = 422,
    AWS_HTTP_CODE_LOCKED = 423,
    AWS_HTTP_CODE_FAILED_DEPENDENCY = 424,
    AWS_HTTP_CODE_UPGRADE_REQUIRED = 426,
    AWS_HTTP_CODE_PRECONDITION_REQUIRED = 427,
    AWS_HTTP_CODE_TOO_MANY_REQUESTS = 429,
    AWS_HTTP_CODE_REQUEST_HEADER_FIELDS_TOO_LARGE = 431,
    AWS_HTTP_CODE_LOGIN_TIMEOUT = 440,
    AWS_HTTP_CODE_NO_RESPONSE = 444,
    AWS_HTTP_CODE_RETRY_WITH = 449,
    AWS_HTTP_CODE_BLOCKED = 450,
    AWS_HTTP_CODE_REDIRECT = 451,
    AWS_HTTP_CODE_REQUEST_HEADER_TOO_LARGE = 494,
    AWS_HTTP_CODE_CERT_ERROR = 495,
    AWS_HTTP_CODE_NO_CERT = 496,
    AWS_HTTP_CODE_HTTP_TO_HTTPS = 497,
    AWS_HTTP_CODE_CLIENT_CLOSED_TO_REQUEST = 499,
    AWS_HTTP_CODE_INTERNAL_SERVER_ERROR = 500,
    AWS_HTTP_CODE_NOT_IMPLEMENTED = 501,
    AWS_HTTP_CODE_BAD_GATEWAY = 502,
    AWS_HTTP_CODE_SERVICE_UNAVAILABLE = 503,
    AWS_HTTP_CODE_GATEWAY_TIMEOUT = 504,
    AWS_HTTP_CODE_HTTP_VERSION_NOT_SUPPORTED = 505,
    AWS_HTTP_CODE_VARIANT_ALSO_NEGOTIATES = 506,
    AWS_HTTP_CODE_INSUFFICIENT_STORAGE = 507,
    AWS_HTTP_CODE_LOOP_DETECTED = 508,
    AWS_HTTP_CODE_BANDWIDTH_LIMIT_EXCEEDED = 509,
    AWS_HTTP_CODE_NOT_EXTENDED = 510,
    AWS_HTTP_CODE_NETWORK_AUTHENTICATION_REQUIRED = 511,
    AWS_HTTP_CODE_NETWORK_READ_TIMEOUT = 598,
    AWS_HTTP_CODE_NETWORK_CONNECT_TIMEOUT = 599
};

struct aws_http_header {
    enum aws_http_header_name name;
    struct aws_byte_cursor name_str;
    struct aws_byte_cursor value;
};

enum aws_http_log_subject {
    AWS_LS_HTTP_GENERAL = 0x800,
    AWS_LS_HTTP_CONNECTION,
    AWS_LS_HTTP_SERVER,
    AWS_LS_HTTP_STREAM,
};

AWS_EXTERN_C_BEGIN

/**
 * Loads error strings for this API so that aws_last_error_str etc. will return useful debug strings.
 */
AWS_HTTP_API void aws_http_load_error_strings(void);

/**
 * Load aws-c-http's log subject strings.
 */
AWS_HTTP_API void aws_http_load_log_subject_strings(void);

AWS_HTTP_API const char *aws_http_header_name_to_str(enum aws_http_header_name name);
AWS_HTTP_API const char *aws_http_method_to_str(enum aws_http_method method);
AWS_HTTP_API const char *aws_http_version_to_str(enum aws_http_version version);
AWS_HTTP_API const char *aws_http_code_to_str(enum aws_http_code code);

AWS_HTTP_API enum aws_http_method aws_http_str_to_method(struct aws_byte_cursor cursor);
AWS_HTTP_API enum aws_http_version aws_http_str_to_version(struct aws_byte_cursor cursor);
AWS_HTTP_API enum aws_http_header_name aws_http_str_to_header_name(struct aws_byte_cursor cursor);
AWS_HTTP_API enum aws_http_code aws_http_int_to_code(int code);

AWS_EXTERN_C_END

#endif /* AWS_HTTP_H */
