#ifndef _INVENTORY_H_
#define _INVENTORY_H_
#include "syslinux/pxe_api.h"
#include <libupload/upload_backend.h>
#include <stdio.h>
#include <syslinux/pxe.h>
#include <console.h>
#include <consoles.h>
#include <syslinux/vesacon.h>
#include "sys/pci.h"

#include <disk/bootloaders.h>
#include <disk/errno_disk.h>
#include <disk/error.h>
#include <disk/geom.h>
#include <disk/mbrs.h>
#include <disk/msdos.h>
#include <disk/partition.h>
#include <disk/swsusp.h>
#include <disk/read.h>

#include "cpuid.h"
#include "dmi/dmi.h"
//#include "hdt-ata.h"
#include <lib/sys/vesa/vesa.h>
#include <vpd/vpd.h>
#include <libansi.h>
#include <acpi/acpi.h>
#include <libupload/upload_backend.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <bufprintf.h>

extern struct print_buf p_buf;

struct upload_backend *uploadsend;

// struct s_pxe {
//     uint16_t vendor_id;
//     uint16_t product_id;
//     uint16_t subvendor_id;
//     uint16_t subproduct_id;
//     uint8_t rev;
//     uint8_t pci_bus;
//     uint8_t pci_dev;
//     uint8_t pci_func;
//     uint8_t base_class;
//     uint8_t sub_class;
//     uint8_t prog_intf;
//     uint8_t nictype;
//     char mac_addr[18];		/* The current mac address */
//     uint8_t ip_addr[4];
//     pxe_bootp_t dhcpdata;	/* The dhcp answer */
//     struct pci_device *pci_device;	/* The matching pci device */
//     uint8_t pci_device_pos;	/* It position in our pci sorted list */
// };

struct timeval{
    uint32_t year;
    uint32_t month;
    uint32_t day;
    uint32_t hour;
    uint32_t minut;
    uint32_t second;
};
// struct syslinux_ipinfo {
//     uint32_t ipver;
//     uint32_t myip;
//     uint32_t serverip;
//     uint32_t gateway;
//     uint32_t netmask;
// };
// #if BYTE_ORDER == BIG_ENDIAN
// /** Set an IP address given by the four byte-parts */
// #define IP4_ADDR(ipaddr, a,b,c,d) \
//         (ipaddr)->addr = ((uint32_t)((a) & 0xff) << 24) | \
//                          ((uint32_t)((b) & 0xff) << 16) | \
//                          ((uint32_t)((c) & 0xff) << 8)  | \
//                           (uint32_t)((d) & 0xff)
// #else
// /** Set an IP address given by the four byte-parts.
//     Little-endian version that prevents the use of htonl. */
// #define IP4_ADDR(ipaddr, a,b,c,d) \
//         (ipaddr)->addr = ((uint32_t)((d) & 0xff) << 24) | \
//                          ((uint32_t)((c) & 0xff) << 16) | \
//                          ((uint32_t)((b) & 0xff) << 8)  | \
//                           (uint32_t)((a) & 0xff)
// #endif
//                           
#if BYTE_ORDER == BIG_ENDIAN
/** Set an IP address given by the four byte-parts */
#define IP4_ADDR1(ipaddr, a,b,c,d) \
        (ipaddr) = ((uint32_t)((a) & 0xff) << 24) | \
                   ((uint32_t)((b) & 0xff) << 16) | \
                   ((uint32_t)((c) & 0xff) << 8)  | \
                    (uint32_t)((d) & 0xff)
#else
/** Set an IP address given by the four byte-parts.
    Little-endian version that prevents the use of htonl. */
#define IP4_ADDR(ipaddr, a,b,c,d) \
        (ipaddr) = ((uint32_t)((d) & 0xff) << 24) | \
                         ((uint32_t)((c) & 0xff) << 16) | \
                         ((uint32_t)((b) & 0xff) << 8)  | \
                          (uint32_t)((a) & 0xff)
#endif
//                           
                          
                          
#endif