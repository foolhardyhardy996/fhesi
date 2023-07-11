#include "esi_iointerface.h"
#include "esi_str/esi_str.h"

static const char *esi_iointerface_err_msg[] = ESI_IOINTERFACE_ERR_MSG;

const char *esi_iointerface_strerror(int err) {
    return esi_iointerface_err_msg[err];
}

int esi_io_buf_wrapper_init(esi_io_buf_wrapper_t *p_wrapper, uint8_t *buf, int cap) {
    p_wrapper->buf = buf;
    p_wrapper->cap = cap;
    p_wrapper->rd_ptr = 0;
    p_wrapper->wt_ptr = 0;

    return ESI_IOINTERFACE_ERR_NONE;
}

int esi_io_buf_wrapper_copy(esi_io_buf_wrapper_t *dest, esi_io_buf_wrapper_t *src) {
    int len;

    if (dest->cap >= src->cap) {
        len = src->cap;
    } else {
        len = dest->cap;
    }
    memcpy((void *) dest->buf, (void *) src->buf, len);

    return len;
}

int esi_io_buf_wrapper_read(esi_io_buf_wrapper_t *this_wrapper, esi_io_buf_wrapper_t *dest) {
    int n;
    esi_io_buf_wrapper_t src;

    src.buf = this_wrapper->buf + this_wrapper->rd_ptr;
    src.cap = this_wrapper->cap - this_wrapper->rd_ptr;
    n = esi_io_buf_wrapper_copy(dest, &src);
    this_wrapper->rd_ptr += n;

    return n;
}

int esi_io_buf_wrapper_read_nocopy(esi_io_buf_wrapper_t *this_wrapper, esi_io_buf_wrapper_t *dest) {
    int available_len, n;

    available_len = this_wrapper->cap - this_wrapper->rd_ptr;
    if (available_len >= dest->cap) {
        n = dest->cap;
        dest->buf = this_wrapper->buf + this_wrapper->rd_ptr;
    } else {
        n = available_len;
        dest->buf = this_wrapper->buf + this_wrapper->rd_ptr;
        dest->cap = n;
    }
    return n;
}

int esi_io_buf_wrapper_write(esi_io_buf_wrapper_t *this_wrapper, esi_io_buf_wrapper_t *src) {
    int n;
    esi_io_buf_wrapper_t dest;

    dest.buf = this_wrapper->buf + this_wrapper->wt_ptr;
    dest.cap = this_wrapper->cap - this_wrapper->wt_ptr;
    n = esi_io_buf_wrapper_copy(&dest, src);
    this_wrapper->wt_ptr += n;

    return n;
}

int esi_io_buf_wrapper_reader_wrapper_read(esi_reader_wrapper_t *reader, esi_io_buf_wrapper_t *dest) {
    esi_io_buf_wrapper_t *p_wrapper = (esi_io_buf_wrapper_t *) reader->blob;
    return esi_io_buf_wrapper_read(p_wrapper, dest);
}

int esi_io_buf_wrapper_reader_wrapper_read_nocopy(esi_reader_wrapper_t *reader, esi_io_buf_wrapper_t *dest) {
    esi_io_buf_wrapper_t *p_wrapper = (esi_io_buf_wrapper_t *) reader->blob;
    return esi_io_buf_wrapper_read_nocopy(p_wrapper, dest);
}

int esi_io_buf_wrapper_reader_wrapper_write(esi_reader_wrapper_t *reader, esi_io_buf_wrapper_t *src) {
    esi_io_buf_wrapper_t *p_wrapper = (esi_io_buf_wrapper_t *) reader->blob;
    return esi_io_buf_wrapper_write(p_wrapper, src);
}

int esi_io_buf_wrapper_make_reader_wrapper(esi_io_buf_wrapper_t *p_buf, esi_reader_wrapper_t *p_reader) {
    p_reader->blob = (void *) p_buf;
    p_reader->read = esi_io_buf_wrapper_reader_wrapper_read;
    return ESI_IOINTERFACE_ERR_NONE;
}

int esi_io_buf_wrapper_make_nocopy_reader_wrapper(esi_io_buf_wrapper_t *p_buf, esi_reader_wrapper_t *p_reader) {
    p_reader->blob = (void *) p_buf;
    p_reader->read = esi_io_buf_wrapper_reader_wrapper_read_nocopy;
    return ESI_IOINTERFACE_ERR_NONE;
}

int esi_io_buf_wrapper_make_writer_wrapper(esi_io_buf_wrapper_t *p_buf, esi_writer_wrapper_t *p_writer) {
    p_writer->blob = (void *) p_buf;
    p_writer->write = esi_io_buf_wrapper_reader_wrapper_write;
    return ESI_IOINTERFACE_ERR_NONE;
}