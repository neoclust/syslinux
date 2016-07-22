/* ----------------------------------------------------------------------- *
 *
 *   Copyright 2011 Erwan Velu - All Rights Reserved
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
 *
 * -----------------------------------------------------------------------
 */
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "hdt-common.h"
#include "hostname.h"
#include <syslinux/reboot.h>
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




void hostname_input(struct s_hardware *hardware)
{
    char buffer[255];
    int error = 0;

   if (hardware->bhostname == false)
	return ;

   for (;;) {
        size_t len =0;
        hardware->hostname[0]=0;
        buffer[0]=0;
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
        /* reboot if type exit */ 
        if (!strncmp(buffer,"exit", 4)){
            syslinux_reboot(1);
        }
        strncpy(hardware->hostname,buffer,sizeof hardware->hostname);
        hardware->hostname[strlen(hardware->hostname)-1]=0;
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
        gotoxy(1, 1);
        printf("\nRegistration machine : %s (Y/N)", hardware->hostname);
        fgets((char*) buffer, sizeof buffer, stdin);
            if (buffer[0] == 'y' || buffer[0] == 'Y'){
                break; 
            }
        }
    }
}
