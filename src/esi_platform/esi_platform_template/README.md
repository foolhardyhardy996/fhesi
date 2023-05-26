# esi_platform: decoupling platform specific particularities from the actual application running on it

# General Structure of esi_platform

- `/boot` contains boot-up code. 
- `esi_platform_info` provides platform vendor infomation like name, version, etc..
- `esi_platform_features` provides feature test macros to inform the programmer which peripherals, components, etc.. are available.
- `esi_low_level` provides those low-level APIs which other high-level APIs of fhesi build upon

