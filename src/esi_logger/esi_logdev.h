#pragma once 

/**
 * @file esi_logdev.h
 * @brief "esi_logdev" abstract out the interfaces a device should support to 
 * be a possible underlying logging device for "esi_logger"s
 * 
 * To provide an concrete implementation conforming this interface, a factory, 
 * a finalizer, a write method, and a config method should be provided. It's 
 * caller's responsibility to ensure the underlying device is properly opened 
 * and closed.
 * 
 * @author Li Weida
 * @date 2023.05.16
*/

struct esi_logdev_ops {
    /**
     * @brief write "msg" to "logdev"
     * 
     * @return a status code indicating whether it succeeded or what error 
     * occured
    */
    int (*write)(struct esi_logdev *logdev, const char *msg);

    /**
     * @brief configure possible options of "logdev"
     * @param arg: the concrete content of "arg" is the concern of the 
     * implementation of "config"
     * @return a status code indicating whether it succeeded or what error 
     * occured
    */
    int (*config)(struct esi_logdev *logdev, void *arg);

    /**
     * @brief open "logdev", after "open" return successfully, "write" and 
     * "config" should be avaliable
     * 
     * @return a status code indicating whether it succeeded or what error
     * occured
    */
   int (*open)(struct esi_logdev *logdev, void *arg);

   /**
    * @brief close "logdev"
    * 
    * @return return value would be ignored by caller
   */
  int (*close)(struct esi_logdev *logdev);
};

struct esi_logdev {
    /**< the blob hiding the concrete implementation detail of the device (
     * UART, SPI, I2C, or memory)*/
    void *logdev_struct;

    /**< add one everytime a write fails */
    int err_count;

    /**< interfaces a "log_device" should provide */
    struct esi_logdev_ops *ops;
};
