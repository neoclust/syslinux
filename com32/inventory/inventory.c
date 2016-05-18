/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2006 Erwan Velu - All Rights Reserved
 *
 *   Permission is hereby granted, free of charge, to any person
 *   obtaining a copy of this software and associated documentation
 *   files (the "Software"), to deal in the Software without
 *   restriction, including without limitation the rights to use,
 *   copy, modify, merge, publish, distribute, sublicense, and/or
 *   sell copies of the Software, and to permit persons to whom
 *   the Software is furnished to do so, subject to the following
 *   conditions:
 *
 *   The above copyright notice and this permission notice shall
 *   be included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *   OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 * /usr/bin/gcc -std=gnu99 -m32 -march=i386 -mpreferred-stack-boundary=2 -Os -fomit-frame-pointer -fno-stack-protector -fwrapv -freg-struct-return -fno-exceptions -fno-asynchronous-unwind-tables -fPIC -falign-functions=0 -falign-jumps=0 -falign-labels=0 -falign-loops=0 -mregparm=3 -DREGPARM=3 -W -Wall -Wstrict-prototypes -W -Wall -fomit-frame-pointer -D__COM32__ -D__FIRMWARE_BIOS__ -DDYNAMIC_MODULE -nostdinc -iwithprefix include -I/root/syslinux-6.04-pre1/com32/libutil/include -I/root/syslinux-6.04-pre1/com32/include -I/root/syslinux-6.04-pre1/com32/include/sys -I/root/syslinux-6.04-pre1/com32/gplinclude -I/root/syslinux-6.04-pre1/core/include -I/root/syslinux-6.04-pre1/bios -DLDLINUX="ldlinux.c32" -I/root/syslinux-6.04-pre1/com32/modules/../../core/lwip/src/include -I/root/syslinux-6.04-pre1/com32/modules/../../core/lwip/src/include/ipv4 -I/root/syslinux-6.04-pre1/com32/gplinclude -c  /root/syslinux-6.04-pre1/com32/modules/inventory.c -o /root/dede.prog

 
 
 /usr/bin/gcc -std=gnu99 -m32 -march=i386 -mpreferred-stack-boundary=2 -Os -fomit-frame-pointer -fno-stack-protector -fwrapv -freg-struct-return -fno-exceptions -fno-asynchronous-unwind-tables -fPIC -falign-functions=0 -falign-jumps=0 -falign-labels=0 -falign-loops=0 -mregparm=3 -DREGPARM=3 -W -Wall -Wstrict-prototypes -W -Wall -fomit-frame-pointer -D__COM32__ -D__FIRMWARE_BIOS__ -DDYNAMIC_MODULE -nostdinc -iwithprefix include -I/root/syslinux-6.04-pre1/com32/libutil/include -I/root/syslinux-6.04-pre1/com32/include -I/root/syslinux-6.04-pre1/com32/include/sys -I/root/syslinux-6.04-pre1/com32/gplinclude -I/root/syslinux-6.04-pre1/core/include -I/root/syslinux-6.04-pre1/bios -DLDLINUX="ldlinux.c32" -I/root/syslinux-6.04-pre1/com32/modules/../../core/lwip/src/include -I/root/syslinux-6.04-pre1/com32/modules/../../core/lwip/src/include/ipv4 -I/root/syslinux-6.04-pre1/com32/gplinclude -L/root/syslinux-6.04-pre1/bios/core -llpxelinux.a -c  /root/syslinux-6.04-pre1/com32/modules/inventory.c -o /root/dede.prog
 
 
 * -----------------------------------------------------------------------
*/

/*
 * dmitest.c
 *
 * DMI demo program using libcom32
 */

#include <string.h>
#include <stdio.h>
#include <console.h>
#include "dmi/dmi.h"
#include <stdio.h>

#include "inventory.h"
#include "syslinux/pxe.h"
#include <syslinux/boot.h>
#include "syslinux/config.h"
#include "syslinux/pxe_api.h"
#include <syslinux/reboot.h>
#include <com32.h>
#include <string.h>
#include "../cmenu/libmenu/cmenu.h"
#include "../cmenu/libmenu/com32io.h"
#include <netinet/in.h>


#include <disk/common.h>
#include <disk/geom.h>
#include <disk/read.h>
#include <core.h>
#include <net.h>

#include <libupload/upload_backend.h>


// #include "lwip/err.h"
// #include "lwip/udp.h"
// 
// #include "lwip/ip_addr.h"
// #include "lwip/memp.h"
// 
// #include "lwip/opt.h"
// 
// #include "lwip/init.h"
// #include "lwip/stats.h"
// #include "lwip/sys.h"
// #include "lwip/mem.h"
// #include "lwip/pbuf.h"
// #include "lwip/netif.h"
// #include "lwip/sockets.h"
// #include "lwip/ip.h"
// #include "lwip/raw.h"
// 
// #include "lwip/tcp_impl.h"
// #include "lwip/snmp_msg.h"
// #include "lwip/autoip.h"
// #include "lwip/igmp.h"
// #include "lwip/dns.h"
// #include "lwip/timers.h"
// #include "netif/etharp.h"

// #include <stdlib.h>
// #include <string.h>
// #include <stdio.h>
// #include <getkey.h>
// #include "syslinux/config.h"
// #include "../lib/sys/vesa/vesa.h"
// 
// #include <disk/util.h>
// #include <disk/mbrs.h>
// #include <memory.h>

int result0,result1,result2;

#define sub(val) (((val%1024)*100)>>10)
void timeval(struct timeval *tm);
int detect_pxe(struct s_pxe *pxe);

static uint8_t frombcd(uint8_t v)
{ /*binary codage decimal*/
    uint8_t a = v & 0x0f;
    uint8_t b = v >> 4;

    return a + b*10;
}

void timeval(struct timeval *tm)
{
    /* Days from March 1 for a specific month, starting in March */
    /*Interrupt 1A	BIOS	time of day */
    /*function is specified in register AH*/
    com32sys_t ir, d0, d1, t0;
    memset(&ir, 0, sizeof ir);
    ir.eax.b[1] = 0x04;/*INT 1A,4   Read real time clock date (AT,PS/2)*/
    __intcall(0x1A, &ir, &d0);
    memset(&ir, 0, sizeof ir);
    ir.eax.b[1] = 0x02;/*INT 1A,2   Read real time clock time (AT,PS/2)*/
    __intcall(0x1A, &ir, &t0);
    memset(&ir, 0, sizeof ir);
    ir.eax.b[1] = 0x04;
    __intcall(0x1A, &ir, &d1);
    if (t0.ecx.b[1] < 0x12)
	d0 = d1;
    tm->year    = (uint32_t)frombcd(d0.ecx.b[1])*100+(uint32_t)frombcd(d0.ecx.b[0]);
    tm->month   = frombcd(d0.edx.b[1]);
    tm->day     = frombcd(d0.edx.b[0]);
    tm->hour    = frombcd(t0.ecx.b[1]);
    tm->minut   = frombcd(t0.ecx.b[0]);
    tm->second  = frombcd(t0.edx.b[1]);
}

// get_derivative_info
// const union syslinux_derivative_info *sdi =
// 	syslinux_derivative_info();
int detect_pxe(struct s_pxe *pxe)
{
    void *dhcpdata;
    //struct s_pxe pxe;struct s_pxe *p
    size_t dhcplen;
    memset(pxe, 0, sizeof(struct s_pxe));

    if (!pxe_get_cached_info(PXENV_PACKET_TYPE_DHCP_ACK, &dhcpdata, &dhcplen)) {
	pxe_bootp_t *dhcp = &pxe->dhcpdata;
	memcpy(&pxe->dhcpdata, dhcpdata,
	       sizeof(pxe->dhcpdata));
	snprintf(pxe->mac_addr, sizeof(pxe->mac_addr),
		 "%02x:%02x:%02x:%02x:%02x:%02x", dhcp->CAddr[0],
		 dhcp->CAddr[1], dhcp->CAddr[2], dhcp->CAddr[3],
		 dhcp->CAddr[4], dhcp->CAddr[5]);

            /* Saving our IP address in a easy format */
            pxe->ip_addr[0] = pxe->dhcpdata.yip & 0xff;
            pxe->ip_addr[1] = pxe->dhcpdata.yip >> 8 & 0xff;
            pxe->ip_addr[2] = pxe->dhcpdata.yip >> 16 & 0xff;
            pxe->ip_addr[3] = pxe->dhcpdata.yip >> 24 & 0xff;
    }
return 0;
}
	
char display_line;



/* Try to detect disks from port 0x80 to 0xff */
void detect_disks(struct driveinfo *disk_info, int *nbdisk)
{
    int i = -1;
    int err;
    for (int drive = 0x80; drive < 0xff; drive++) {
	i++;
	disk_info[i].disk = drive;
	err = get_drive_parameters(&disk_info[i]);

	/*
	 * Do not print output when drive does not exist or
	 * doesn't support int13 (cdrom, ...)
	 */
	if (err == -1 || !disk_info[i].cbios)
	    continue;
	(*nbdisk)++;
    }
}
void sectors_to_size(int sectors, char *buffer)
{
    int b = (sectors / 2);
    int mib = b >> 10;
    int gib = mib >> 10;
    int tib = gib >> 10;

    if (tib > 0)
	sprintf(buffer, "%3d.%02d TiB", tib,sub(gib));
    else if (gib > 0)
	sprintf(buffer, "%3d.%02d GiB", gib,sub(mib));
    else if (mib > 0)
	sprintf(buffer, "%3d.%02d MiB", mib,sub(b));
    else
	sprintf(buffer, "%d B", b);
}

/* remove begining spaces */
char *skip_spaces(char *p)
{
    while (*p && *p <= ' ') {
	p++;
    }

    return p;
}

/* remove trailing & begining spaces */
char *remove_spaces(char *p)
{
    char *save = p;
    p += strlen(p) - 1;
    while (*p && *p <= ' ') {
	*p = '\0';
	p--;
    }
    p = save;
    while (*p && *p <= ' ') {
	p++;
    }

    return p;
}

/* remove trailing LF */
char *remove_trailing_lf(char *p)
{
    char *save = p;
    p += strlen(p) - 1;
    while (*p && *p == 10) {
	*p = '\0';
	p--;
    }
    p = save;

    return p;
}
void disks_summary(struct driveinfo *disk_info)
{
    int i = -1;
    bool found = false;
    for (int drive = 0x80; drive < 0xff; drive++) {
	i++;
	if (!disk_info[i].cbios)
	    continue;		/* Invalid geometry */

	found = true;
	struct driveinfo *d = &disk_info[i];
	char disk_size[11];

	if ((int)d->edd_params.sectors > 0)
	    sectors_to_size((int)d->edd_params.sectors, disk_size);
	else
	    memset(disk_size, 0, sizeof disk_size);

	moreprintf("DISK 0x%X:\n", d->disk);
	moreprintf("  C/H/S: %d cylinders, %d heads, %d sectors/track\n",
		    d->legacy_max_cylinder + 1, d->legacy_max_head + 1,
		    d->legacy_sectors_per_track);
	moreprintf("  EDD:   Version: %X, size: %s\n", d->edd_version,
		    disk_size);

	/* Do not print Host Bus & Interface if EDD isn't 3.0 or more */
	if (d->edd_version >= 0x30)
	    moreprintf("         Host bus: %s, Interface type: %s\n\n",
			remove_spaces((char *)d->edd_params.host_bus_type),
			remove_spaces((char *)d->edd_params.interface_type));
    }

    if (found == false)
	moreprintf("No disk found\n");
}

void disks_size_first_disk(struct driveinfo *disk_info, char *disk_size)
{
    int i = -1;
    i++;
    if (!disk_info[i].cbios) {
        memset(disk_size, 0, sizeof disk_size);
        return;
    }


    struct driveinfo *d = &disk_info[i];
    //char disk_size[11];

    if ((int)d->edd_params.sectors > 0)
        sectors_to_size((int)d->edd_params.sectors, disk_size);
    else
        memset(disk_size, 0, sizeof disk_size);
}
// void core_udp_sendto(struct pxe_pvt_inode *socket, const void *data, size_t len,
//                      uint32_t ip, uint16_t port)
// {
//     static __lowmem struct s_PXENV_UDP_WRITE udp_write;
//     void *lbuf;
//     uint16_t tid;
//     IP4_ADDR1(tid,127,0,0,1);
// 
//     lbuf = lmalloc(len);
//     if (!lbuf)
// 	return;
// 
//     memcpy(lbuf, data, len);
//     udp_write.buffer    = FAR_PTR(lbuf);
//     udp_write.ip        = ip;
//     udp_write.gw        = gateway(udp_write.ip);
//     udp_write.src_port  = tid;
//     udp_write.dst_port  = htons(port);
//     udp_write.buffer_size = len;
// 
//     pxe_call(PXENV_UDP_WRITE, &udp_write);
// 
//     lfree(lbuf);
// }
//   /*
//  * Compute the suitable gateway for a specific route -- too many
//  * vendor PXE stacks don't do this correctly...
//  */
// static inline uint32_t gateway(uint32_t ip)
// {
//     if ((ip ^ IPInfo.myip) & IPInfo.netmask)
// 	return IPInfo.gateway;
//     else
// 	return 0;
// }

int senddata( const char * buffer, uint32_t *myip , uint32_t *toip, uint32_t *gwip, uint16_t  toport, uint16_t  fromport ){
    void *lbuf;
    struct s_PXENV_UDP_OPEN udp_open;
    udp_open.status = 0;//PXENV_STATUS_FAILURE
    udp_open.src_ip = *myip;
//     result0 = pxe_call(PXENV_UDP_OPEN, &udp_open);
//     if (udp_open.status != PXENV_STATUS_SUCCESS) {
// 	printf("probleme ouverture udp connexion: %d\n", udp_open.status);
//     }
    int err = pxe_call(PXENV_UDP_OPEN, &udp_open);
    if (err || udp_open.status) {
        printf("Failed to initialize UDP stack ");
        printf("%d\n", udp_open.status);
	kaboom();
        return 0;
    }
    lbuf = lmalloc(sizeof(buffer));
    if (!lbuf)
	return 0;
    memcpy(lbuf, buffer, sizeof(buffer));
    printf("PXENV_STATUS_FAILURE=%d\n",PXENV_STATUS_FAILURE);
    struct s_PXENV_UDP_WRITE udp_write;
    udp_write.status = 0;
    udp_write.ip = *toip;
    udp_write.gw = *gwip;
    udp_write.src_port = htons(fromport);
    udp_write.dst_port = htons(toport);
    udp_write.buffer = FAR_PTR(lbuf);
    udp_write.buffer_size = sizeof(buffer);

    result1 = pxe_call(PXENV_UDP_WRITE, &udp_write);
    if (udp_write.status != PXENV_STATUS_UDP_OPEN) {
	printf("probleme ecriture udp connexion: %d\n", udp_write.status);
    }
    lfree(lbuf);
    struct s_PXENV_UDP_CLOSE udp_close;
    udp_close.status = 1;
     result2 = pxe_call(PXENV_UDP_CLOSE, &udp_close);
    if (udp_close.status != PXENV_STATUS_UDP_CLOSED) {
	printf("probleme ecriture udp connexion: %d\n", udp_close.status);
    }

    printf("\n\nPXENV_STATUS_FAILURE %d\n", PXENV_STATUS_FAILURE);
    printf("\n\nPXENV_STATUS_UDP_OPEN %d\n", PXENV_STATUS_UDP_OPEN);
    printf("PXENV_STATUS_UDP_CLOSED %d\n", PXENV_STATUS_UDP_CLOSED);
    printf("probleme ouverture udp %d\n", udp_open.status);
    printf("probleme ecriture udp : %d\n", udp_write.status);
    printf("probleme close udp %d\n", udp_close.status);
    return result2;
}
int main(void)//const int argc, const char *argv[]
{
    char buffer[1024];
    char hostname[90];
    s_dmi dmi;
    struct timeval tm;
    size_t len =0;
    struct driveinfo disk_info[256];	/* Disk Information */
    int nbdisk=0;
    //uint32_t mbr_ids[256];	/* MBR ids */
    detect_disks(disk_info, &nbdisk);
    disks_summary(disk_info);
    //recuperation ip et macadress
    const union syslinux_derivative_info *sdi;
    char tftp_ip[50], gateway[50], netmask[50], myip[50], ipver[50], subnet[50];
    struct s_pxe pxe;
    char ip_addr1[16];
    char mac_addr[18];
    char date[20];
    char logdate[20];
    uint32_t myipint;
    uint32_t toip;
    uint32_t gwip;
    uint16_t  toport = 5005;
    uint16_t  fromport = 5005;

    hostname[0]=0;
    int error = 0;
    sdi = syslinux_derivative_info();
    detect_pxe(&pxe);
    timeval(&tm);
  
 
    snprintf(date, sizeof(date),
		 "%04d-%02d-%02d-%02d-%02d-%02d",
                                    (uint32_t) tm.year,
                                    (uint32_t) tm.month,
                                    (uint32_t) tm.day,
                                    (uint32_t) tm.hour,
                                    (uint32_t) tm.minut,
                                    (uint32_t) tm.second);
    printf("date %s\n",date );
    snprintf(logdate, sizeof(logdate),
		 "%04d-%02d-%02d %02d:%02d:%02d",
                                    (uint32_t) tm.year,
                                    (uint32_t) tm.month,
                                    (uint32_t) tm.day,
                                    (uint32_t) tm.hour,
                                    (uint32_t) tm.minut,
                                    (uint32_t) tm.second);
    printf("logdate %s\n",logdate );
    //dede $4$NnTZsbX1$NdFRpeMLJPR/VdMLXaWUaxoD+MU$
    // read reseau from pxe
    snprintf(tftp_ip, sizeof(tftp_ip),
		 "%u.%u.%u.%u",
		 ((uint8_t *) & sdi->pxe.ipinfo->serverip)[0],
		 ((uint8_t *) & sdi->pxe.ipinfo->serverip)[1],
		 ((uint8_t *) & sdi->pxe.ipinfo->serverip)[2],
		 ((uint8_t *) & sdi->pxe.ipinfo->serverip)[3]);
    printf("tftp_ip %s\n",tftp_ip );

    uint8_t ip[4];
    ip[0]=((uint8_t *) & sdi->pxe.ipinfo->serverip)[0];
    ip[1]=((uint8_t *) & sdi->pxe.ipinfo->serverip)[1];
    ip[2]=((uint8_t *) & sdi->pxe.ipinfo->serverip)[3];
    ip[3]=((uint8_t *) & sdi->pxe.ipinfo->serverip)[4];
    IP4_ADDR1(toip,
                ((uint8_t *) & sdi->pxe.ipinfo->serverip)[0],
		 ((uint8_t *) & sdi->pxe.ipinfo->serverip)[1],
		 ((uint8_t *) & sdi->pxe.ipinfo->serverip)[2],
		 ((uint8_t *) & sdi->pxe.ipinfo->serverip)[3]);

    snprintf(gateway, sizeof(gateway),
		 "%u.%u.%u.%u",
		 ((uint8_t *) & sdi->pxe.ipinfo->gateway)[0],
		 ((uint8_t *) & sdi->pxe.ipinfo->gateway)[1],
		 ((uint8_t *) & sdi->pxe.ipinfo->gateway)[2],
		 ((uint8_t *) & sdi->pxe.ipinfo->gateway)[3]);
    
    
    
    
    printf("gateway %s\n",gateway );
    snprintf(netmask, sizeof(netmask),
		 "%u.%u.%u.%u",
		 ((uint8_t *) & sdi->pxe.ipinfo->netmask)[0],
		 ((uint8_t *) & sdi->pxe.ipinfo->netmask)[1],
		 ((uint8_t *) & sdi->pxe.ipinfo->netmask)[2],
		 ((uint8_t *) & sdi->pxe.ipinfo->netmask)[3]);
    printf("netmask %s\n",netmask );

    snprintf(myip, sizeof(myip),
		 "%u.%u.%u.%u",
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[0],
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[1],
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[2],
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[3]);
    printf("myip %s\n",myip );
    
    IP4_ADDR1(myipint,
                ((uint8_t *) & sdi->pxe.ipinfo->myip)[0],
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[1],
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[2],
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[3]);
 
                
    
    IP4_ADDR1(gwip,
                 ((uint8_t *) & sdi->pxe.ipinfo->gateway)[0]&((uint8_t *) & sdi->pxe.ipinfo->netmask)[0],
		 ((uint8_t *) & sdi->pxe.ipinfo->gateway)[1]&((uint8_t *) & sdi->pxe.ipinfo->netmask)[1],
		 ((uint8_t *) & sdi->pxe.ipinfo->gateway)[2]&((uint8_t *) & sdi->pxe.ipinfo->netmask)[2],
		 ((uint8_t *) & sdi->pxe.ipinfo->gateway)[3]&((uint8_t *) & sdi->pxe.ipinfo->netmask)[3]);


    

    
    snprintf(subnet, sizeof(subnet),
		 "%u.%u.%u.%u",
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[0] & ((uint8_t *) & sdi->pxe.ipinfo->netmask)[0],
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[1] & ((uint8_t *) & sdi->pxe.ipinfo->netmask)[1],
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[2] & ((uint8_t *) & sdi->pxe.ipinfo->netmask)[2],
		 ((uint8_t *) & sdi->pxe.ipinfo->myip)[3] & ((uint8_t *) & sdi->pxe.ipinfo->netmask)[3]);

    snprintf(ipver, sizeof(ipver),
		 "%u.%u.%u.%u",
		 ((uint8_t *) & sdi->pxe.ipinfo->ipver)[0],
		 ((uint8_t *) & sdi->pxe.ipinfo->ipver)[1],
		 ((uint8_t *) & sdi->pxe.ipinfo->ipver)[2],
		 ((uint8_t *) & sdi->pxe.ipinfo->ipver)[3]);
    printf("ipver %s\n",ipver );

    if (dmi_iterate(&dmi) == -ENODMITABLE) {
	printf("No DMI Structure found\n");
	return -1;
    } else {
	printf("DMI %u.%u present.\n", dmi.dmitable.major_version,
	       dmi.dmitable.minor_version);
	printf("%d structures occupying %d bytes.\n", dmi.dmitable.num,
	       dmi.dmitable.len);
	printf("DMI table at 0x%08X.\n", dmi.dmitable.base);
    }
    parse_dmitable(&dmi);

    snprintf(ip_addr1, sizeof(ip_addr1),
             "%d.%d.%d.%d",
             pxe.ip_addr[0],
             pxe.ip_addr[1],
             pxe.ip_addr[2],
             pxe.ip_addr[3]);
    strncpy(mac_addr, pxe.mac_addr,sizeof(mac_addr));
    for (;;) {
        clear_entire_screen();
        gotoxy(2, 5);
        printf("Tape exit : return menu");
        switch(error){
            case 0: break;
            case 1 :
                 gotoxy(6, 3);
                 printf("hostname labels may contain only 64 ASCII letters.");
                 break;
            case 2 :
                break;
            case 3 :
                 gotoxy(6, 3);
                 printf("hostname labels may contain only the ASCII letters 'a' through 'z'");
                 gotoxy(7, 3);
                 printf("(in a case-insensitive manner),");
                 gotoxy(8, 3);
                 printf("the digits '0' through '9', and the hyphen ('-').");
                 break;
            default:
                break;
        };
        gotoxy(21, 3);
	csprint("Hostname:", 0x07);
        fgets((char*) buffer, sizeof buffer, stdin);
        strncpy(hostname,buffer,strlen(buffer)-1);
        if (!strncmp(buffer,"exit", 4)){
            syslinux_reboot(1);
            }
        // curr = showmenus();	// Initial menu is the one called "main" return 0;
        clear_entire_screen();
        len = strnlen((const char *)buffer,sizeof(buffer))-1;
        error=0;
        if (len > 64) {
            error = 1;
        }
        else {
                if  (len < 1){
                        error = 2;
                }
                else{
                    //printf("len = %d\n",len);
                    for (size_t i = 0; i < len ; i++){
                        if (((buffer[i] >= 97 && buffer[i] <= 122) ||
                            (buffer[i] >= 65 && buffer[i] <= 90) ||
                            (buffer[i] >= 48 && buffer[i] <= 57) ||
                            buffer[i] == 45)){
                        continue;
                        }
                        else{
                            error = 3;
                            break;
                        }
                    }
                }
        }
        /*
	editstring(name, 50);
	gotoxy(21, 1);
        printf("%s",name);*/

        if (error == 0){

            break;
        }
    }


    char deviceid[86];
    strncpy(deviceid,buffer,len);
    strncat(deviceid,"-",sizeof(deviceid));
    strncat(deviceid,date,sizeof(deviceid));

    char bufferxml[4000];
    char header[1024];
    char bios[1024];
    char hardware[1024];
    char networks[1024];
    char storages[1024];
    bufferxml[0]=header[0]=bios[0]=hardware[0]=networks[0]=storages[0]=0;
    snprintf (header, 
            sizeof(header),
            "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<REQUEST>\n"
    "\t<DEVICEID>%s</DEVICEID>\n"
    "\t<QUERY>INVENTORY</QUERY>\n"
    "\t<TAG>root</TAG>\n"
    "\t<CONTENT>\n"
        "\t\t<ACCESSLOG>\n"
        "\t\t\t<LOGDATE>%s</LOGDATE>\n"
        "\t\t\t<USERID>N/A</USERID>\n"
        "\t\t</ACCESSLOG>\n",deviceid,logdate);
        snprintf (bios, 
            sizeof(bios),
                "\t\t<BIOS>\n"
                    "\t\t\t<ASSETTAG/>\n"
                    "\t\t\t<MMANUFACTURER/>\n"
                    "\t\t\t<MMODEL/>\n"
                    "\t\t\t<MSN/>\n"
                    "\t\t\t<SKUNUMBER>%s</SKUNUMBER>\n"
                    "\t\t\t<BDATE>%s</BDATE>\n"
                    "\t\t\t<BMANUFACTURER>%s</BMANUFACTURER>\n"
                    "\t\t\t<BVERSION>%s</BVERSION>\n"
                    "\t\t\t<SMANUFACTURER>%s</SMANUFACTURER>\n"
                    "\t\t\t<SMODEL>%s</SMODEL>\n"
                    "\t\t\t<SSN>%s</SSN>\n"
                "\t\t</BIOS>\n",
                                    dmi.system.sku_number,
                                    dmi.bios.release_date,
                                    dmi.bios.vendor,
                                    dmi.bios.version,
                                    dmi.system.manufacturer,
                                    dmi.system.product_name,
                                    dmi.system.serial);


    snprintf (hardware, 
           sizeof(hardware),
           "\t\t<HARDWARE>\n"
                "\t\t\t<IPADDR>%s</IPADDR>\n"
                "\t\t\t<DEFAULTGATEWAY>%s</DEFAULTGATEWAY>\n"
                "\t\t\t<NAME>%s</NAME>\n"
                "\t\t\t<UUID>%s</UUID>\n"
                "\t\t\t<OSNAME>Unknown operating system (PXE network boot inventory)</OSNAME>\n"
                "\t\t\t<CHASSIS_TYPE>%s</CHASSIS_TYPE>\n"
                "\t\t\t<PROCESSORS>0</PROCESSORS>\n"
                "\t\t\t<PROCESSORN>0</PROCESSORN>\n"
                "\t\t\t<PROCESSORT>Unknown processor</PROCESSORT>\n"
            "\t\t</HARDWARE>\n",ip_addr1,
                                gateway,
                                hostname,
                                dmi.system.uuid,
                                dmi.chassis.manufacturer);

 snprintf (networks, 
           sizeof(networks),
            "\t\t<NETWORKS>\n"
                "\t\t\t<DESCRIPTION>eth0</DESCRIPTION>\n"
                "\t\t\t<IPADDRESS>%s</IPADDRESS>\n"
                "\t\t\t<MACADDR>%s</MACADDR>\n"
                "\t\t\t<IPMASK>%s</IPMASK>\n"
                "\t\t\t<IPGATEWAY>%s</IPGATEWAY>\n"
                "\t\t\t<IPSUBNET>%s</IPSUBNET>\n"
                "\t\t\tSTATUS>Up</STATUS>\n"
                "\t\t\t<TYPE>Ethernet</TYPE>\n"
                "\t\t\t<VIRTUALDEV>0</VIRTUALDEV>\n"
            "\t\t</NETWORKS>\n",
                            myip,
                            mac_addr,
                            netmask,
                            gateway,
                            subnet);
char disk_size[11];
disks_size_first_disk(disk_info,disk_size);
if (disk_size[0] != 0){
    snprintf (storages, 
           sizeof(storages),
           "\t\t<STORAGES>\n"
                "\t\t\t<NAME>hd0</NAME>\n"
                "\t\t\t<TYPE>disk</TYPE>\n"
                "\t\t\t<DISKSIZE>%s</DISKSIZE>\n"
           "\t\t</STORAGES>\n",disk_size);
}
char foot[]="\t</CONTENT>\n"
"</REQUEST>";
        char dataedit[100];
        clear_entire_screen();

    strncpy(bufferxml,header,sizeof(bufferxml));

    strncat(bufferxml,bios,sizeof(bufferxml));
   
    strncat(bufferxml,hardware,sizeof(bufferxml));
      
    strncat(bufferxml,networks,sizeof(bufferxml));
      
    strncat(bufferxml,storages,sizeof(bufferxml));
       
    strncat(bufferxml,foot,sizeof(bufferxml));
     
    //printf("nbdisk %d",nbdisk);
        printf("xml \n%s\n",bufferxml);
        printf("Maintenant il faut envoyé ce xml au servuer inventory\n");
        printf("faire return pour reboot\n");
        fgets( dataedit, sizeof dataedit, stdin);
        char buffertest[255];

        
 /*  
    senddata("hello", &myipint ,&toip, &gwip, toport, fromport);
    printf("%d %d %d %d\n",myipint,toip,gwip,toport);
    printf("%d %d %d\n",result0,result1,result2);
    fgets((char*) buffertest, sizeof buffertest, stdin);*/
 // enregistrer xml
 // cpio_writefile(upload, filename, p_buf.buf, p_buf.len);
 // envoyer xml
 
//flush_data(upload)
// upload = &upload_tftp;
// upload->name = "tftp";
// 
// char filename[512];
// strcpy(filename,"fichiertest");
// 
 upload = &upload_tftp;
 upload->name = "tftp";

//     /* The following defines the behavior of the reporting */
//     char *arg[64];
//     /* The filename */
//     arg[0] = filename;
//     arg[1] = tftp_ip;
//     arg[2] = NULL;
//     /* We initiate the cpio to send */
//     cpio_init(upload, (const char **)arg);
// 
//     cpio_close(upload);
   // cpio_writefile(upload, "dede", bufferxml,strlen(bufferxml));
//     if ((err = flush_data(upload)) != TFTP_OK) {
// 	/* As we manage a tftp connection, let's display the associated error message */
// 	more_printf("Dump failed !\n");
// 	more_printf("TFTP ERROR on  : %s:/%s \n", hardware->tftp_ip, filename);
// 	more_printf("TFTP ERROR num : %d \n", err);
// 	more_printf("TFTP ERROR msg : %s \n", tftp_string_error_message[err]);
//     } else {
// 	more_printf("Dump file sent at %s:/%s\n", hardware->tftp_ip, filename);
//     }

        syslinux_reboot(1);

    return 0;
}
// import socket
// port = 5000
// s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
// s.bind(("", port))
// print "waiting on port:", port
// while 1:
//     data, addr = s.recvfrom(1024)
//     print data
// 



    
//     struct netif *netif, server_netif;
//     struct ip_addr1 ipaddr, pc_ipaddr, netmask, gw;
// 
// 	/* the mac address of the board*/
// 	unsigned char mac_ethernet_address[] = { 0x00, 0x0a, 0x35, 0x00, 0x01, 0x02 };
// 	
// 	struct pbuf *p;
// 	unsigned char buffername[1200] = "my name is xxxxxxx";
// 
// 	netif = &server_netif;
    
    
    
    