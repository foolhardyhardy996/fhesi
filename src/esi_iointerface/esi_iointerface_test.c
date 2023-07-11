#include "esi_iointerface.h"
#include "esi_str/esi_str.h"

#include <stdio.h>

ESI_IO_BUF_DECL(my_buf_t, 32);
ESI_IO_BUF_IMPL(my_buf_t, 32);

ESI_IO_RINGBUF_DECL(my_ringbuf_t, 32);
ESI_IO_RINGBUF_IMPL(my_ringbuf_t, 32);

static const char *str11 = "0123456789";
static const char *str27 = "qazwsxedcrfvtgbyhnujmikolp";

static char buf11[11] = {0};
static char buf27[27] = {0};

static my_buf_t my_buf;

static void print_io_buf_stat(my_buf_t *);
static void print_io_buf_stat(my_buf_t *p_buf) {
    printf("p_buf{\nrd_ptr = %d, wt_ptr = %d\n}\n", p_buf->rd_ptr, p_buf->wt_ptr);
}

static void init_io_buf_test(void);
static void init_io_buf_test(void) {
    ESI_IO_BUF_INIT(my_buf_t, &my_buf);
    printf("[INFO]: after init io_buf\n");
    print_io_buf_stat(&my_buf);
}

static void run_io_buf_test(void) {
    esi_io_buf_wrapper_t str11_wrapper, str27_wrapper;
    esi_io_buf_wrapper_t buf11_wrapper, buf27_wrapper;
    int n1, n2;
    str11_wrapper.buf = (uint8_t *) str11;
    str11_wrapper.cap = 11;
    str27_wrapper.buf = (uint8_t *) str27;
    str27_wrapper.cap = 27;
    ESI_IO_BUF_COPY_FROM(my_buf_t, &my_buf, 0, &str11_wrapper);
    printf("[INFO]: after copy_from(&my_buf, 0, &str11_wrapper):\n");
    printf("my_buf.buf = %s\n", (const char *) my_buf.buf);
    my_buf.wt_ptr = 10;
    ESI_IO_BUF_WRITE(my_buf_t, &my_buf, &str27_wrapper);
    my_buf.buf[31] = 0;
    printf("[INFO]: after write(&my_buf, &str27_wrapper):\n");
    printf("my_buf.buf = %s\n", (const char *) my_buf.buf);
    buf11_wrapper.buf = (uint8_t *) buf11;
    buf11_wrapper.cap = 10;
    buf27_wrapper.buf = (uint8_t *) buf27;
    buf27_wrapper.cap = 26;
    n1 = ESI_IO_BUF_READ(my_buf_t, &my_buf, &buf11_wrapper);
    n2 = ESI_IO_BUF_READ(my_buf_t, &my_buf, &buf27_wrapper);
    printf("[INFO]: after read(&my_buf, &buf11_wrapper) and read(&my_buf, &buf27_wrapper)\n");
    printf("n1 = %d, n2 = %d\n", n1, n2);
    buf11_wrapper.buf[10] = 0;
    buf27_wrapper.buf[26] = 0;
    print_io_buf_stat(&my_buf);
    printf("buf11.buf = %s\nbuf27.buf = %s\n", (char *) buf11_wrapper.buf, (char *) buf27_wrapper.buf);
}

static my_ringbuf_t my_ringbuf;

static void print_ringbuf_stat(my_ringbuf_t *p_buf) {
    printf("ringbuf{\nrd_ptr = %d, wt_ptr = %d, len = %d\n}\n", p_buf->rd_ptr, p_buf->wt_ptr, ESI_IO_RINGBUF_LEN(my_ringbuf_t, p_buf));
}

static void init_ringbuf_test(void);
static void init_ringbuf_test(void) {
    ESI_IO_RINGBUF_INIT(my_ringbuf_t, &my_ringbuf);
    printf("[INFO]: after init ringbuf\n");
    print_ringbuf_stat(&my_ringbuf);
}

static void run_ringbuf_test(void) {
    esi_io_buf_wrapper_t str11_wrapper, str27_wrapper;
    esi_io_buf_wrapper_t buf11_wrapper, buf27_wrapper;
    int n1, n2;
    str11_wrapper.buf = (uint8_t *) str11;
    str11_wrapper.cap = 11;
    str27_wrapper.buf = (uint8_t *) str27;
    str27_wrapper.cap = 27;
    ESI_IO_RINGBUF_WRITE(my_ringbuf_t, &my_ringbuf, &str11_wrapper);
    ESI_IO_RINGBUF_WRITE(my_ringbuf_t, &my_ringbuf, &str27_wrapper);
    my_ringbuf.buf[10] = '-';
    my_ringbuf.buf[31] = 0;
    printf("[INFO]: after write(&my_buf, &str11_wrapper) and write(&my_buf, &str27_wrapper):\n");
    printf("my_ringbuf.buf = %s\n", (const char *) my_ringbuf.buf);
    print_ringbuf_stat(&my_ringbuf);
    my_ringbuf.wt_ptr = 10;
    ESI_IO_RINGBUF_WRITE_FORCED(my_ringbuf_t, &my_ringbuf, &str27_wrapper);
    printf("[INFO]: after setting wt_ptr = 10, write_forced(&my_ringbuf, &str27_wrapper)\n");
    printf("my_ringbuf.buf = %s\n", (const char *) my_ringbuf.buf);
    print_ringbuf_stat(&my_ringbuf);
    my_ringbuf.rd_ptr = 10;
    buf27_wrapper.buf = (uint8_t *) buf27;
    buf27_wrapper.cap = 27;
    n1 = ESI_IO_RINGBUF_READ(my_ringbuf_t, &my_ringbuf, &buf27_wrapper);
    printf("[INFO]: after setting rd_ptr = 10, read(&my_ringbuf, &buf27_wrapper)\n");
    printf("n = %d, buf = %s\n", n1, (char *) buf27);
    print_ringbuf_stat(&my_ringbuf);
}

int main(int argc, char *argv[]) {
    init_io_buf_test();
    printf("[INFO]: test io_buf >>>>>>>>>>\n");
    run_io_buf_test();
    init_ringbuf_test();
    printf("[INFO]: test io_ringbuf >>>>>>>>>>\n");
    run_ringbuf_test();
    printf("[INFO]: everything is okay.\n");
    return 0;
}