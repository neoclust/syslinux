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
// #include <netinet/in.h>
// #include <disk/common.h>
// #include <disk/geom.h>
// #include <disk/read.h>
// #include <core.h>
// #include <net.h>

#include <libupload/upload_backend.h>

#include "hdt-common.h"

int display_line_nb = 0;
bool disable_more_printf = false;
int result0,result1,result2;
int max_console_lines = MAX_CLI_LINES;
#define sub(val) (((val%1024)*100)>>10)
void timeval(struct timeval *tm);
int detect_pxelocal(struct s_pxe *pxe);

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
int detect_pxelocal(struct s_pxe *pxe)
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

void printpointmsleep(int millisecond, int nbpoint, const char *timereboot){
    int t=2;
    if (!strncmp(timereboot, "10", 2)){
    t = 10;
    }else if (!strncmp(timereboot, "11", 2)){
    t = 11;
    }else if (!strncmp(timereboot, "12", 2)){
    t = 12;
    }else if (!strncmp(timereboot, "13", 2)){
    t = 13;
    }else if (!strncmp(timereboot, "14", 2)){
    t = 14;
    }else if (!strncmp(timereboot, "15", 2)){
    t = 15;
    }else if (!strncmp(timereboot, "16", 2)){
    t = 16;
    }else if (!strncmp(timereboot, "17", 2)){
    t = 17;
    }else if (!strncmp(timereboot, "18", 2)){
    t = 18;
    }else if (!strncmp(timereboot, "19", 2)){
    t = 19;
    }else if (!strncmp(timereboot, "20", 2)){
    t = 20;
    }else if (!strncmp(timereboot, "1", 1)){
    t = 1;
    }else if (!strncmp(timereboot, "2", 1)){
    t = 2;
    }else if (!strncmp(timereboot, "3", 1)){
    t = 3;
    }else if (!strncmp(timereboot, "4", 1)){
    t = 4; 
    }else if (!strncmp(timereboot, "5", 1)){
    t = 5;
    }else if (!strncmp(timereboot, "6", 1)){
    t = 6;
    }else if (!strncmp(timereboot, "7", 1)){
    t = 7;
    }else if (!strncmp(timereboot, "8", 1)){
    t = 8;
    }else if (!strncmp(timereboot, "9", 1)){
    t = 9;
    }else if (!strncmp(timereboot, "10", 1)){
    t = 10;
    }

    for (int i=0;i <= nbpoint; i++){
        msleep(millisecond*t);
        printf(".");
    }
}

char display_line;


/* remove trailing & begining spaces */
char *remove_spaceslocal(char *p)
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

int main(const int argc, const char *argv[])
{
    char buffer[1024]={0};
    char hostname[90]={0};
    s_dmi dmi;
    struct timeval tm;
    size_t len =0;
    //struct driveinfo disk_info[256];	/* Disk Information */
    char gpxe[4]={0};
    char myip[16]={0};
    char mac_addr[18]={0};
    char date[20]={0};
    char logdate[20]={0};
    char manufacturer[20]={0};
    int error = 0;
     char version_string[256];
    //uint32_t mbr_ids[256];	/* MBR ids */
     snprintf(version_string, sizeof version_string, "%s %s (%s)",
	     PRODUCT_NAME, VERSION, CODENAME);
    static struct s_hardware hardware;
    init_hardware(&hardware);
    detect_syslinux(&hardware);
    detect_parameters(argc, argv, &hardware);
    detect_hardware(&hardware);

    if (strlen(hardware.gateway) == 0 || strlen(hardware.tftp_ip) == 0 ||
        strlen(hardware.subnet) == 0 || strlen(hardware.mask) == 0 ||
        strlen(hardware.dump_path)== 0 )
    {
     printf("missing parameters \nPlease change parameters in file menu\n"\
     "\nParameters : subnet, gateway, mask, tftp_ip and dump_path are required\n"\
     "example : \n"\
     "COM32 inventory.c32\n"\
     "APPEND dump_path=inventories gateway=8.8.8.8 subnet=192.168.1.0 mask=255.255.255.0 tftp_ip=192.168.1.19");
     printf("\nType <Return> to continue\n");
     fgets((char*) buffer, sizeof buffer, stdin);
     syslinux_reboot(1);
    }
    printf("PARAMTERS:\n");
    printf("\tgateway %s  \n",hardware.gateway);
    printf("\ttftp_ip %s  \n",hardware.tftp_ip);
    printf("\tsubnet %s  \n",hardware.subnet);
    printf("\tmask %s  \n",hardware.mask);
    if (hardware.debug){
        printf("\tmode debug");
    }
    if (hardware.xml){
        printf("\t display xml");
    }
    printf("\n\t-----------------------------------\n");
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
    struct s_pxe *p = &hardware.pxe;

    if ((hardware.pci_ids_return_code == -ENOPCIIDS)
	|| (p->pci_device == NULL)) {
    } else {
	snprintf(manufacturer, sizeof buffer, "%s",
		 p->pci_device->dev_info->vendor_name);
	printf("%s  \n", manufacturer);
	snprintf(buffer, sizeof buffer, "Product      : %s",
		 p->pci_device->dev_info->product_name);
	printf("%s  \n",buffer);

    }
    snprintf(mac_addr, sizeof mac_addr, "%s", p->mac_addr);
    printf("Mac address %s  \n",mac_addr);
    snprintf(myip, sizeof myip, "%d.%d.%d.%d",p->ip_addr[0], p->ip_addr[1], p->ip_addr[2], p->ip_addr[3]);
    printf("IP address : %s  \n",myip);
    if (is_gpxe()) snprintf(gpxe,sizeof(gpxe),"%s","Yes");
    else snprintf (gpxe, sizeof(gpxe), "%s", "No");
    snprintf(buffer, sizeof buffer, "gPXE Detected: %s", gpxe);
    printf("%s  \n",buffer);


    if (dmi_iterate(&dmi) == -ENODMITABLE) {
	printf("No DMI Structure found\n");
	return -1;
    } else {
	printf("DMI %u.%u present.\n", dmi.dmitable.major_version,
	       dmi.dmitable.minor_version);
	printf("%d structures occupying %d bytes.\n", dmi.dmitable.num,
	       dmi.dmitable.len);
	printf("DMI table at 0x%08X.\n", dmi.dmitable.base);
        parse_dmitable(&dmi);
        printf("number %s  ",dmi.system.sku_number);
        printf("release date %s\n",dmi.bios.release_date);
        printf("vendor  %s  ",dmi.bios.vendor);
        printf("version  %s",dmi.bios.version);
        printf("manufacturer sys  %s\n",dmi.system.manufacturer);
        printf("product name %s  uuid sys %s \n",dmi.system.product_name,dmi.system.uuid);
        printf("serial name %s chassis %s",dmi.system.serial,dmi.chassis.manufacturer);
    }
    for (;;) {
        hostname[0]=0;
        buffer[0]=0;
        if (hardware.debug==false)
            clear_entire_screen();
        switch(error){
            case 0: break;
            case 1 :
                 gotoxy(6, 3);
                 printf("Hostname labels may contain only 15 characters (alphanumeric and hyphen).");
                 break;
            case 2 :
                break;
            case 3 :
                 gotoxy(6, 3);
                 printf("Hostname labels may contain only the ASCII letters 'a' through 'z'");
                 gotoxy(7, 3);
                 printf("(in a case-insensitive manner),");
                 gotoxy(8, 3);
                 printf("the digits '0' through '9', and the hyphen ('-').");
                 break;
            default:
                break;
        };
        gotoxy(21, 3);
        printf("Type exit to return to menu");
        gotoxy(22, 3);
	csprint("Hostname:", 0x07);
        fgets((char*) buffer, sizeof buffer, stdin);
        strncpy(hostname,buffer,sizeof hostname);
        hostname[strlen(hostname)-1]=0;
        if (!strncmp(buffer,"exit", 4)){
            syslinux_reboot(1);
            }
        // curr = showmenus();	// Initial menu is the one called "main" return 0;
        clear_entire_screen();
        len = strnlen((const char *)buffer,sizeof(buffer))-1;
        error=0;
        if (len > 15) {
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
        if (error == 0){

            break;
        }
    }


    char deviceid[86];
    deviceid[0]=0;
    strncpy(deviceid,hostname,sizeof(deviceid));
    strncat(deviceid,"-",sizeof(deviceid));
    strncat(deviceid,date,sizeof(deviceid));

    char bufferxml[8000];
    char header[1024];
    char bios[1024];
    char hardwarelocal[1024];
    char networks[1024];
    char storages[1024];
    bufferxml[0]=header[0]=bios[0]=hardwarelocal[0]=networks[0]=storages[0]=0;
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
                    "\t\t\t<MMANUFACTURER>%s</MMANUFACTURER>\n"
                    "\t\t\t<MMODEL/>\n"
                    "\t\t\t<MSN/>\n"
                    "\t\t\t<SKUNUMBER>%s</SKUNUMBER>\n"
                    "\t\t\t<BDATE>%s</BDATE>\n"
                    "\t\t\t<BMANUFACTURER>%s</BMANUFACTURER>\n"
                    "\t\t\t<BVERSION>%s</BVERSION>\n"
                    "\t\t\t<SMANUFACTURER>%s</SMANUFACTURER>\n"
                    "\t\t\t<SMODEL>%s</SMODEL>\n"
                    "\t\t\t<SSN>%s</SSN>\n"
                "\t\t</BIOS>\n",    manufacturer,
                                    dmi.system.sku_number,
                                    dmi.bios.release_date,
                                    dmi.bios.vendor,
                                    dmi.bios.version,
                                    dmi.system.manufacturer,
                                    dmi.system.product_name,
                                    dmi.system.serial);


    snprintf (hardwarelocal,
           sizeof(hardwarelocal),
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
            "\t\t</HARDWARE>\n", myip,
                                 hardware.gateway,
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
                "\t\t\t<STATUS>Up</STATUS>\n"
                "\t\t\t<TYPE>Ethernet</TYPE>\n"
                "\t\t\t<VIRTUALDEV>0</VIRTUALDEV>\n"
            "\t\t</NETWORKS>\n",
                            myip,
                            mac_addr,
                            hardware.mask,
                            hardware.gateway,
                            hardware.subnet
                            );
//     snprintf (storages, 
//            sizeof(storages),
//            "\t\t<STORAGES>\n"
//                 "\t\t\t<NAME></NAME>\n"
//                 "\t\t\t<TYPE></TYPE>\n"
//                 "\t\t\t<DISKSIZE></DISKSIZE>\n"
//            "\t\t</STORAGES>\n");

char foot[]="\t</CONTENT>\n"
"</REQUEST>";
        clear_entire_screen();
        gotoxy(1, 1);
        strncpy(bufferxml,header,sizeof(bufferxml));
        strncat(bufferxml,bios,sizeof(bufferxml));
        strncat(bufferxml,hardwarelocal,sizeof(bufferxml));
        strncat(bufferxml,networks,sizeof(bufferxml));
        //strncat(bufferxml,storages,sizeof(bufferxml));
        strncat(bufferxml,foot,sizeof(bufferxml));

        if(hardware.xml){
            printf("%s\n",bufferxml);
            printf("Type <return> to continue");
            fgets((char*) buffer, sizeof buffer, stdin);
        }
        clear_entire_screen();
        gotoxy(1, 1);
        printf("\nRegistration machine : %s (Y/N)", hostname);
        fgets((char*) buffer, sizeof buffer, stdin);
        if (buffer[0] == 'y' || buffer[0] == 'Y'){
            if (dump(&hardware,bufferxml) == 0){
                printpointmsleep(100,30,hardware.timereboot);
                syslinux_reboot(1);
            }
            else{
                printf("\nerror Transfert inventory  :  return to quit\n");
                fgets((char*) buffer, sizeof buffer, stdin);
                syslinux_reboot(1);
            }
        }
        printf("\nRegistration cancel : return to quit\n");
        fgets((char*) buffer, sizeof buffer, stdin);
        syslinux_reboot(1);
    return 0;
}
