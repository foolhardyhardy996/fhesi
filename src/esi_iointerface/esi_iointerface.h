#pragma once 

/**
 * @file esi_iointerface.h
 * @brief esi_iointerface provides io related interfaces to facilitate the 
 * design of io related functions.
 * 
 * 
 * 
 * @author Li Weida
 * @date 2023.07.04
*/

#include <esi_str/esi_str.h>

#include <stdint.h>

enum esi_iointerface_err {
    ESI_IOINTERFACE_ERR_NONE = 0,
    ESI_IOINTERFACE_ERR_CAP = 1,
    ESI_IOINTERFACE_ERR_EMPTY = 2,
    ESI_IOINTERFACE_ERR_OUT_OF_RANGE = 3
};

#define ESI_IOINTERFACE_ERR_MSG {\
    "esi_iointerface: ok", /*0*/\
    "esi_iointerface: capacity has been reached", /*1*/\
    "esi_iointerface: empty", /*2*/\
    "esi_iointerface: index out of range" /*3*/\
}

const char *esi_iointerface_strerror(int err);

struct esi_reader_wrapper;
typedef struct esi_reader_wrapper esi_reader_wrapper_t;
struct esi_writer_wrapper;
typedef struct esi_writer_wrapper esi_writer_wrapper_t;

struct esi_io_buf_wrapper {
    uint8_t *buf;
    int cap;
    int rd_ptr;
    int wt_ptr;
};
typedef struct esi_io_buf_wrapper esi_io_buf_wrapper_t;
int esi_io_buf_wrapper_init(esi_io_buf_wrapper_t *p_wrapper, uint8_t *buf, int cap);
int esi_io_buf_wrapper_copy(esi_io_buf_wrapper_t *dest, esi_io_buf_wrapper_t *src);
int esi_io_buf_wrapper_read(esi_io_buf_wrapper_t *this_wrapper, esi_io_buf_wrapper_t *dest);
int esi_io_buf_wrapper_read_nocopy(esi_io_buf_wrapper_t *this_wrapper, esi_io_buf_wrapper_t *dest);
int esi_io_buf_wrapper_write(esi_io_buf_wrapper_t *this_wrapper, esi_io_buf_wrapper_t *src);
int esi_io_buf_wrapper_reader_wrapper_read(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);
int esi_io_buf_wrapper_reader_wrapper_read_nocopy(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);
int esi_io_buf_wrapper_reader_wrapper_write(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);
int esi_io_buf_wrapper_make_reader_wrapper(esi_io_buf_wrapper_t *p_buf, esi_reader_wrapper_t *p_reader);
int esi_io_buf_wrapper_make_nocopy_reader_wrapper(esi_io_buf_wrapper_t *p_buf, esi_reader_wrapper_t *p_reader);
int esi_io_buf_wrapper_make_writer_wrapper(esi_io_buf_wrapper_t *p_buf, esi_writer_wrapper_t *p_writer);

struct esi_reader_wrapper {
    void *blob;
    int (*read)(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);
};

struct esi_writer_wrapper {
    void *blob;
    int (*write)(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);
};

#define ESI_IO_BUF_DECL(TYPE_ALIAS, CAP) \
extern const int TYPE_ALIAS##_cap;\
struct esi_io_buf_##TYPE_ALIAS {\
    uint8_t buf[CAP];\
    int rd_ptr;\
    int wt_ptr;\
};\
typedef struct esi_io_buf_##TYPE_ALIAS TYPE_ALIAS;\
int TYPE_ALIAS##_init(TYPE_ALIAS *);\
int TYPE_ALIAS##_copy_into(TYPE_ALIAS *, int, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_copy_from(TYPE_ALIAS *, int, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_read(TYPE_ALIAS *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_read_nocopy(TYPE_ALIAS *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_write(TYPE_ALIAS *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_make_io_buf_wrapper(TYPE_ALIAS *, esi_io_buf_wrapper_t *, int, int);\
int TYPE_ALIAS##_make_reader_wrapper(TYPE_ALIAS *, esi_reader_wrapper_t *);\
int TYPE_ALIAS##_make_nocopy_reader_wrapper(TYPE_ALIAS *, esi_reader_wrapper_t *);\
int TYPE_ALIAS##_make_writer_wrapper(TYPE_ALIAS *, esi_writer_wrapper_t *);\
int TYPE_ALIAS##_reader_wrapper_read(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_reader_wrapper_read_nocopy(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_writer_wrapper_write(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);\

#define ESI_IO_BUF_CAP(BUF_T) (BUF_T##_cap)

#define ESI_IO_BUF_INIT(BUF_T, p_buf) BUF_T##_init(p_buf)
#define ESI_IO_BUF_COPY_INTO(BUF_T, p_buf, offset, dest) BUF_T##_copy_into(p_buf, offset, dest)
#define ESI_IO_BUF_COPY_FROM(BUF_T, p_buf, offset, src) BUF_T##_copy_from(p_buf, offset, src)
#define ESI_IO_BUF_READ(BUF_T, p_buf, dest) BUF_T##_read(p_buf, dest)
#define ESI_IO_BUF_READ_NOCOPY(BUF_T, p_buf, dest) BUF_T##_read_nocopy(p_buf, dest)
#define ESI_IO_BUF_WRITE(BUF_T, p_buf, src) BUF_T##_write(p_buf, src)
#define ESI_IO_BUF_MAKE_IO_BUF_WRAPPER(BUF_T, p_buf, p_wrapper, offset, len) BUF_T##_make_io_buf_wrapper(p_buf, p_wrapper, offset, len)
#define ESI_IO_BUF_MAKE_READER_WRAPPER(BUF_T, p_buf, p_reader) BUF_T##_make_reader_wrapper(p_buf, p_reader)
#define ESI_IO_BUF_MAKE_NOCOPY_READER_WRAPPER(BUF_T, p_buf, p_reader) BUF_T##_make_nocopy_reader_wrapper(p_buf, p_reader)
#define ESI_IO_BUF_MAKE_WRITER_WRAPPER(BUF_T, p_buf, p_writer) BUF_T##_make_writer_wrapper(p_buf, p_writer)

#define ESI_IO_BUF_IMPL(TYPE_ALIAS, CAP) \
const int TYPE_ALIAS##_cap = (CAP);\
int TYPE_ALIAS##_init(TYPE_ALIAS * p_buf) {\
    p_buf->rd_ptr = 0;\
    p_buf->wt_ptr = 0;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_copy_into(TYPE_ALIAS *p_buf, int offset, esi_io_buf_wrapper_t *dest) {\
    int aimed_len = dest->cap, available_len = ESI_IO_BUF_CAP(TYPE_ALIAS) - offset;\
    if (available_len >= aimed_len) {\
        memcpy((void *) dest->buf, (const void *) (p_buf->buf + offset), aimed_len);\
        return aimed_len;\
    } else {\
        memcpy((void *) dest->buf, (const void *) (p_buf->buf + offset), available_len);\
        return available_len;\
    }\
}\
int TYPE_ALIAS##_copy_from(TYPE_ALIAS *p_buf, int offset, esi_io_buf_wrapper_t *src) {\
    int aimed_len = src->cap, available_len = ESI_IO_BUF_CAP(TYPE_ALIAS) - offset;\
    if (available_len >= aimed_len) {\
        memcpy((void *) (p_buf->buf + offset), (void *) src->buf, aimed_len);\
        return aimed_len;\
    } else {\
        memcpy((void *) (p_buf->buf + offset), (void *) src->buf, available_len);\
        return available_len;\
    }\
}\
int TYPE_ALIAS##_read(TYPE_ALIAS *p_buf, esi_io_buf_wrapper_t *dest) {\
    int n;\
    n = TYPE_ALIAS##_copy_into(p_buf, p_buf->rd_ptr, dest);\
    p_buf->rd_ptr += n;\
    return n;\
}\
int TYPE_ALIAS##_read_nocopy(TYPE_ALIAS *p_buf, esi_io_buf_wrapper_t *dest) {\
    int aimed_len = dest->cap, available_len = ESI_IO_BUF_CAP(TYPE_ALIAS) - p_buf->rd_ptr;\
    dest->buf = p_buf->buf + p_buf->rd_ptr;\
    if (available_len >= aimed_len) {\
        p_buf->rd_ptr += aimed_len;\
        return aimed_len;\
    } {\
        p_buf->rd_ptr += available_len;\
        dest->cap = available_len;\
        return available_len;\
    }\
}\
int TYPE_ALIAS##_write(TYPE_ALIAS *p_buf, esi_io_buf_wrapper_t *src) {\
    int n;\
    n = TYPE_ALIAS##_copy_from(p_buf, p_buf->wt_ptr, src);\
    p_buf->wt_ptr += n;\
    return n;\
}\
int TYPE_ALIAS##_make_io_buf_wrapper(TYPE_ALIAS *p_buf, esi_io_buf_wrapper_t *res, int offset, int len) {\
    if (offset < 0 || len < 0) {\
        return ESI_IOINTERFACE_ERR_OUT_OF_RANGE;\
    }\
    if (offset + len > ESI_IO_BUF_CAP(TYPE_ALIAS)) {\
        return ESI_IOINTERFACE_ERR_OUT_OF_RANGE;\
    }\
    res->buf = p_buf->buf + offset;\
    res->cap = len;\
    res->rd_ptr = 0;\
    res->wt_ptr = 0;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_make_reader_wrapper(TYPE_ALIAS *p_buf, esi_reader_wrapper_t *res) {\
    res->blob = (void *) p_buf;\
    res->read = TYPE_ALIAS##_reader_wrapper_read;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_make_nocopy_reader_wrapper(TYPE_ALIAS *p_buf, esi_reader_wrapper_t *res) {\
    res->blob = (void *) p_buf;\
    res->read = TYPE_ALIAS##_reader_wrapper_read_nocopy;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_make_writer_wrapper(TYPE_ALIAS *p_buf, esi_writer_wrapper_t *res) {\
    res->blob = (void *) p_buf;\
    res->write = TYPE_ALIAS##_writer_wrapper_write;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_reader_wrapper_read(esi_reader_wrapper_t *p_reader, esi_io_buf_wrapper_t *dest) {\
    TYPE_ALIAS *p_buf = (TYPE_ALIAS *) p_reader->blob;\
    return TYPE_ALIAS##_read(p_buf, dest);\
}\
int TYPE_ALIAS##_reader_wrapper_read_nocopy(esi_reader_wrapper_t *p_reader, esi_io_buf_wrapper_t *dest) {\
    TYPE_ALIAS *p_buf = (TYPE_ALIAS *) p_reader->blob;\
    return TYPE_ALIAS##_read_nocopy(p_buf, dest);\
}\
int TYPE_ALIAS##_writer_wrapper_write(esi_reader_wrapper_t *p_reader, esi_io_buf_wrapper_t *src) {\
    TYPE_ALIAS *p_buf = (TYPE_ALIAS *) p_reader->blob;\
    return TYPE_ALIAS##_write(p_buf, src);\
}

#define ESI_IO_RINGBUF_DECL(TYPE_ALIAS, CAP) \
extern const int TYPE_ALIAS##_cap;\
struct esi_io_ringbuf_##TYPE_ALIAS {\
    uint8_t buf[CAP];\
    int rd_ptr;\
    int wt_ptr;\
};\
typedef struct esi_io_ringbuf_##TYPE_ALIAS TYPE_ALIAS;\
int TYPE_ALIAS##_init(TYPE_ALIAS *);\
int TYPE_ALIAS##_len(TYPE_ALIAS *);\
int TYPE_ALIAS##_copy_into(TYPE_ALIAS *, int, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_copy_from(TYPE_ALIAS *, int, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_read(TYPE_ALIAS *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_read_nocopy(TYPE_ALIAS *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_write(TYPE_ALIAS *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_write_forced(TYPE_ALIAS *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_make_io_buf_wrapper(TYPE_ALIAS *, esi_io_buf_wrapper_t *, int, int);\
int TYPE_ALIAS##_make_reader_wrapper(TYPE_ALIAS *, esi_reader_wrapper_t *);\
int TYPE_ALIAS##_make_nocopy_reader_wrapper(TYPE_ALIAS *, esi_reader_wrapper_t *);\
int TYPE_ALIAS##_make_writer_wrapper(TYPE_ALIAS *, esi_writer_wrapper_t *);\
int TYPE_ALIAS##_make_forced_writer_wrapper(TYPE_ALIAS *, esi_writer_wrapper_t *);\
int TYPE_ALIAS##_reader_wrapper_read(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_reader_wrapper_read_nocopy(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_writer_wrapper_write(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);\
int TYPE_ALIAS##_writer_wrapper_write_forced(esi_reader_wrapper_t *, esi_io_buf_wrapper_t *);\

#define ESI_IO_RINGBUF_CAP(BUF_T) (BUF_T##_cap);

#define ESI_IO_RINGBUF_INIT(BUF_T, p_buf) BUF_T##_init(p_buf)
#define ESI_IO_RINGBUF_LEN(BUF_T, p_buf) BUF_T##_len(p_buf)
#define ESI_IO_RINGBUF_COPY_INTO(BUF_T, p_buf, offset, dest) BUF_T##_copy_into(p_buf, offset, dest)
#define ESI_IO_RINGBUF_COPY_FROM(BUF_T, p_buf, offset, src) BUF_T##_copy_from(p_buf, offset, src)
#define ESI_IO_RINGBUF_READ(BUF_T, p_buf, dest) BUF_T##_read(p_buf, dest)
#define ESI_IO_RINGBUF_READ_NOCOPY(BUF_T, p_buf, dest) BUF_T##_read_nocopy(p_buf, dest)
#define ESI_IO_RINGBUF_WRITE(BUF_T, p_buf, src) BUF_T##_write(p_buf, src)
#define ESI_IO_RINGBUF_WRITE_FORCED(BUF_T, p_buf, src) BUF_T##_write_forced(p_buf, src)
#define ESI_IO_RINGBUF_MAKE_IO_BUF_WRAPPER(BUF_T, p_buf, p_wrapper, offset, len) BUF_T##_make_io_buf_wrapper(p_buf, p_wrapper, offset, len)
#define ESI_IO_RINGBUF_MAKE_READER_WRAPPER(BUF_T, p_buf, reader) BUF_T##_make_reader_wrapper(p_buf, reader)
#define ESI_IO_RINGBUF_MAKE_NOCOPY_READER_WRAPPER(BUF_T, p_buf, reader) BUF_T##_make_nocopy_reader_wrapper(p_buf, reader)
#define ESI_IO_RINGBUF_MAKE_WRITER_WRAPPER(BUF_T, p_buf, writer) BUF_T##_make_writer_wrapper(p_buf, writer)
#define ESI_IO_RINGBUF_MAKE_FORCED_WRITER_WRAPPER(BUF_T, p_buf, writer) BUF_T##_make_forced_writer_wrapper(p_buf, writer)

#define ESI_IO_RINGBUF_IMPL(TYPE_ALIAS, CAP) \
const int TYPE_ALIAS##_cap = (CAP);\
int TYPE_ALIAS##_init(TYPE_ALIAS *p_buf) {\
    p_buf->rd_ptr = 0;\
    p_buf->wt_ptr = 0;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_len(TYPE_ALIAS *p_buf) {\
    return (p_buf->wt_ptr + (CAP) - p_buf->rd_ptr) % (CAP);\
}\
int TYPE_ALIAS##_copy_into(TYPE_ALIAS *p_buf, int offset, esi_io_buf_wrapper_t *dest) {\
    int len, seg1_len, seg2_len;\
    if ((CAP) >= dest->cap) {\
        len = dest->cap;\
    } else {\
        len = (CAP);\
    }\
    if (offset + len > (CAP)) {\
        seg1_len = (CAP) - offset;\
        seg2_len = len - seg1_len;\
        memcpy(dest->buf, p_buf->buf + offset, seg1_len);\
        memcpy(dest->buf + seg1_len, p_buf->buf, seg2_len);\
    } else {\
        memcpy(dest->buf, p_buf->buf + offset, len);\
    }\
    return len;\
}\
int TYPE_ALIAS##_copy_from(TYPE_ALIAS *p_buf, int offset, esi_io_buf_wrapper_t *src) {\
    int len, seg1_len, seg2_len;\
    if ((CAP) >= src->cap) {\
        len = src->cap;\
    } else {\
        len = (CAP);\
    }\
    if (offset + len > (CAP)) {\
        seg1_len = (CAP) - offset;\
        seg2_len = len - seg1_len;\
        memcpy(p_buf->buf + offset, src->buf, seg1_len);\
        memcpy(p_buf->buf, src->buf + seg1_len, seg2_len);\
    } else {\
        memcpy(p_buf->buf + offset, src->buf, len);\
    }\
    return len;\
}\
int TYPE_ALIAS##_read(TYPE_ALIAS *p_buf, esi_io_buf_wrapper_t *dest) {\
    int available_len = TYPE_ALIAS##_len(p_buf), n;\
    esi_io_buf_wrapper_t dest_wrapper;\
    if (dest->cap > available_len) {\
        dest_wrapper.buf = dest->buf;\
        dest_wrapper.cap = available_len;\
    } else {\
        dest_wrapper = *dest;\
    }\
    n = TYPE_ALIAS##_copy_into(p_buf, p_buf->rd_ptr, &dest_wrapper);\
    p_buf->rd_ptr += n;\
    p_buf->rd_ptr %= (CAP);\
    return n;\
}\
int TYPE_ALIAS##_read_nocopy(TYPE_ALIAS *p_buf, esi_io_buf_wrapper_t *dest) {\
    int available_len;\
    if (p_buf->wt_ptr >= p_buf->rd_ptr) {\
        available_len = p_buf->wt_ptr - p_buf->rd_ptr;\
    } else {\
        available_len = (CAP) - p_buf->rd_ptr;\
    }\
    if (dest->cap > available_len) {\
        dest->buf = p_buf->buf + p_buf->rd_ptr;\
        dest->cap = available_len;\
        p_buf->rd_ptr += available_len;\
        p_buf->rd_ptr %= (CAP);\
        return available_len;\
    } else {\
        dest->buf = p_buf->buf + p_buf->rd_ptr;\
        p_buf->rd_ptr += dest->cap;\
        p_buf->rd_ptr %= (CAP);\
        return dest->cap;\
    }\
}\
int TYPE_ALIAS##_write(TYPE_ALIAS *p_buf, esi_io_buf_wrapper_t *src) {\
    int available_len = (CAP) - TYPE_ALIAS##_len(p_buf) - 1, n;\
    esi_io_buf_wrapper_t src_wrapper;\
    if (available_len >= src->cap) {\
        src_wrapper = *src;\
    } else {\
        src_wrapper.buf = src->buf;\
        src_wrapper.cap = available_len;\
    }\
    n = TYPE_ALIAS##_copy_from(p_buf, p_buf->wt_ptr, &src_wrapper);\
    p_buf->wt_ptr += n;\
    p_buf->wt_ptr %= (CAP);\
    return n;\
}\
int TYPE_ALIAS##_write_forced(TYPE_ALIAS *p_buf, esi_io_buf_wrapper_t *src) {\
    int available_len = (CAP) - TYPE_ALIAS##_len(p_buf) - 1;\
    if (available_len >= src->cap) {\
        return TYPE_ALIAS##_write(p_buf, src);\
    } else {\
        int diff = src->cap - available_len;\
        p_buf->rd_ptr += diff;\
        p_buf->rd_ptr %= (CAP);\
        return TYPE_ALIAS##_write(p_buf, src);\
    }\
}\
int TYPE_ALIAS##_make_io_buf_wrapper(TYPE_ALIAS *p_buf, esi_io_buf_wrapper_t *res, int offset, int len) {\
    if (offset < 0 || len < 0) {\
        return ESI_IOINTERFACE_ERR_OUT_OF_RANGE;\
    }\
    if (offset + len > ESI_IO_BUF_CAP(TYPE_ALIAS)) {\
        return ESI_IOINTERFACE_ERR_OUT_OF_RANGE;\
    }\
    res->buf = p_buf->buf + offset;\
    res->cap = len;\
    res->rd_ptr = 0;\
    res->wt_ptr = 0;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_make_reader_wrapper(TYPE_ALIAS *p_buf, esi_reader_wrapper_t *res) {\
    res->blob = (void *) p_buf;\
    res->read = TYPE_ALIAS##_reader_wrapper_read;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_make_nocopy_reader_wrapper(TYPE_ALIAS *p_buf, esi_reader_wrapper_t *res) {\
    res->blob = (void *) p_buf;\
    res->read = TYPE_ALIAS##_reader_wrapper_read_nocopy;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_make_writer_wrapper(TYPE_ALIAS *p_buf, esi_writer_wrapper_t *res) {\
    res->blob = (void *) p_buf;\
    res->write = TYPE_ALIAS##_writer_wrapper_write;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_make_forced_writer_wrapper(TYPE_ALIAS *p_buf, esi_writer_wrapper_t *res) {\
    res->blob = (void *) p_buf;\
    res->write = TYPE_ALIAS##_writer_wrapper_write_forced;\
    return ESI_IOINTERFACE_ERR_NONE;\
}\
int TYPE_ALIAS##_reader_wrapper_read(esi_reader_wrapper_t *p_reader, esi_io_buf_wrapper_t *dest) {\
    TYPE_ALIAS *p_buf = (TYPE_ALIAS *) p_reader->blob;\
    return TYPE_ALIAS##_read(p_buf, dest);\
}\
int TYPE_ALIAS##_reader_wrapper_read_nocopy(esi_reader_wrapper_t *p_reader, esi_io_buf_wrapper_t *dest) {\
    TYPE_ALIAS *p_buf = (TYPE_ALIAS *) p_reader->blob;\
    return TYPE_ALIAS##_read_nocopy(p_buf, dest);\
}\
int TYPE_ALIAS##_writer_wrapper_write(esi_reader_wrapper_t *p_reader, esi_io_buf_wrapper_t *src) {\
    TYPE_ALIAS *p_buf = (TYPE_ALIAS *) p_reader->blob;\
    return TYPE_ALIAS##_write(p_buf, src);\
}\
int TYPE_ALIAS##_writer_wrapper_write_forced(esi_reader_wrapper_t *p_reader, esi_io_buf_wrapper_t *src) {\
    TYPE_ALIAS *p_buf = (TYPE_ALIAS *) p_reader->blob;\
    return TYPE_ALIAS##_write_forced(p_buf, src);\
}