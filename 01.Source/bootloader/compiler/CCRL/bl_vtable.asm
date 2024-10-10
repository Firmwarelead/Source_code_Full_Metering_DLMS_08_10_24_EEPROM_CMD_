$INCLUDE "bl_config.inc"

.SECTION .vtable, AT 0x0000
    .DB2    _bl_start                               ;   Entry                               0x0000
    ;OCD vector controlled by compile option
    ;.DB2    0xffff                                  ;   OCD
.SECTION .vtable, AT 0x0004
    .DB2    (USER_BRANCH_TABLE + 0x0004*2)          ;   INTWDTI                             0x0004
    .DB2    (USER_BRANCH_TABLE + 0x0006*2)          ;   INTLVI                              0x0006
    .DB2    (USER_BRANCH_TABLE + 0x0008*2)          ;   INTP0                               0x0008
    .DB2    (USER_BRANCH_TABLE + 0x000A*2)          ;   INTP1                               0x000A
    .DB2    (USER_BRANCH_TABLE + 0x000C*2)          ;   INTP2                               0x000C
    .DB2    (USER_BRANCH_TABLE + 0x000E*2)          ;   INTP3                               0x000E
    .DB2    (USER_BRANCH_TABLE + 0x0010*2)          ;   INTP4                               0x0010
    .DB2    (USER_BRANCH_TABLE + 0x0012*2)          ;   INTP5                               0x0012
    .DB2    (USER_BRANCH_TABLE + 0x0014*2)          ;   INTST2/INTSTMG0                     0x0014
    .DB2    (USER_BRANCH_TABLE + 0x0016*2)          ;   INTSR2/INTSRMG0                     0x0016
    .DB2    (USER_BRANCH_TABLE + 0x0018*2)          ;   INTSRE2/INTSREMG0                   0x0018
    .DB2    (USER_BRANCH_TABLE + 0x001A*2)          ;   INTCR/INTSMP00/INTSMP10             0x001A
    .DB2    (USER_BRANCH_TABLE + 0x001C*2)          ;   INTAES/INTAESF                      0x001C
    .DB2    (USER_BRANCH_TABLE + 0x001E*2)          ;   INTCSI00/INTIIC00/INTST0            0x001E
    .DB2    (FAR_BRANCH_VECTOR_TABLE + 0x0020*2)    ;   INTIICA0                            0x0020
    .DB2    (USER_BRANCH_TABLE + 0x0022*2)          ;   INTSR0                              0x0022
    .DB2    (USER_BRANCH_TABLE + 0x0024*2)          ;   INTSRE0/INTTM01H                    0x0024
    .DB2    (USER_BRANCH_TABLE + 0x0026*2)          ;   INTCSI10/INTIIC10/INTST1            0x0026
    .DB2    (USER_BRANCH_TABLE + 0x0028*2)          ;   INTSR1                              0x0028
    .DB2    (USER_BRANCH_TABLE + 0x002A*2)          ;   INTSRE1/INTTM03H                    0x002A
    .DB2    (USER_BRANCH_TABLE + 0x002C*2)          ;   INTTM00                             0x002C
    .DB2    (USER_BRANCH_TABLE + 0x002E*2)          ;   INTRTCALM0/INTSMP01/INTSMP11        0x002E
    .DB2    (USER_BRANCH_TABLE + 0x0030*2)          ;   INTFM/INTSMP02/INTSMP12             0x0030
    .DB2    (USER_BRANCH_TABLE + 0x0032*2)          ;   INTTM01                             0x0032
    .DB2    (FAR_BRANCH_VECTOR_TABLE + 0x0034*2)    ;   INTTM02                             0x0034
    .DB2    (USER_BRANCH_TABLE + 0x0036*2)          ;   INTTM03                             0x0036
    .DB2    (USER_BRANCH_TABLE + 0x0038*2)          ;   INTAD                               0x0038
    .DB2    (USER_BRANCH_TABLE + 0x003A*2)          ;   INTRTCPRD/INTSMP03/INTSMP13         0x003A
    .DB2    (USER_BRANCH_TABLE + 0x003C*2)          ;   INTIT                               0x003C
    .DB2    (USER_BRANCH_TABLE + 0x003E*2)          ;   INTKR/INTRTCALM1/INTSMP04/INTSMP14  0x003E
    .DB2    (USER_BRANCH_TABLE + 0x0040*2)          ;   INTCSI30/INTIIC30/INTST3            0x0040
    .DB2    (USER_BRANCH_TABLE + 0x0042*2)          ;   INTSR3                              0x0042
    .DB2    (FAR_BRANCH_VECTOR_TABLE + 0x0044*2)    ;   INTDSAD/INTSMP05/INTSMP15           0x0044
    .DB2    (USER_BRANCH_TABLE + 0x0046*2)          ;   INTTM04                             0x0046
    .DB2    (USER_BRANCH_TABLE + 0x0048*2)          ;   INTSMOTA0/INTTM05                   0x0048
    .DB2    (USER_BRANCH_TABLE + 0x004A*2)          ;   INTP6                               0x004A
    .DB2    (USER_BRANCH_TABLE + 0x004C*2)          ;   INTP7                               0x004C
    .DB2    (USER_BRANCH_TABLE + 0x004E*2)          ;   INTP12/INTRTCIC2                    0x004E
    .DB2    (USER_BRANCH_TABLE + 0x0050*2)          ;   INTP13/INTRTCIC1                    0x0050
    .DB2    (USER_BRANCH_TABLE + 0x0052*2)          ;   INTP14/INTRTCIC0                    0x0052
    .DB2    (USER_BRANCH_TABLE + 0x0054*2)          ;   INTSMOTB0/INTTM06                   0x0054
    .DB2    (USER_BRANCH_TABLE + 0x0056*2)          ;   INTSMOTA1/INTTM07                   0x0056
    .DB2    (USER_BRANCH_TABLE + 0x0058*2)          ;   INTIT00                             0x0058
    .DB2    (USER_BRANCH_TABLE + 0x005A*2)          ;   INTIT01                             0x005A
    .DB2    (USER_BRANCH_TABLE + 0x005C*2)          ;   INTSRE3                             0x005C
    .DB2    (FAR_BRANCH_VECTOR_TABLE + 0x005E*2)    ;   INTMACLOF/INTSMOTB1                 0x005E
    .DB2    (USER_BRANCH_TABLE + 0x0060*2)          ;   INTOSDC                             0x0060
    .DB2    (USER_BRANCH_TABLE + 0x0062*2)          ;   INTFL                               0x0062
    .DB2    (USER_BRANCH_TABLE + 0x0064*2)          ;   INTP8                               0x0064
    .DB2    (USER_BRANCH_TABLE + 0x0066*2)          ;   INTP9                               0x0066
    .DB2    (USER_BRANCH_TABLE + 0x0068*2)          ;   INTIT10                             0x0068
    .DB2    (USER_BRANCH_TABLE + 0x006A*2)          ;   INTIT11                             0x006A
    .DB2    (USER_BRANCH_TABLE + 0x006C*2)          ;   INTIT20/INTLVDVDD                   0x006C
    .DB2    (USER_BRANCH_TABLE + 0x006E*2)          ;   INTIT21/INTLVDVBAT                  0x006E
    .DB2    (USER_BRANCH_TABLE + 0x0070*2)          ;   INTIT30/INTLVDVRTC                  0x0070
    .DB2    (USER_BRANCH_TABLE + 0x0072*2)          ;   INTIT31/INTLVDEXLVD                 0x0072
    .DB2    (USER_BRANCH_TABLE + 0x0074*2)          ;   INTST4/INTSTMG1                     0x0074
    .DB2    (USER_BRANCH_TABLE + 0x0076*2)          ;   INTSR4/INTSRMG1                     0x0076
    .DB2    (USER_BRANCH_TABLE + 0x0078*2)          ;   INTSRE4/INTSREMG1                   0x0078
    .DB2    (USER_BRANCH_TABLE + 0x007A*2)          ;   INTDSADDEC/INTTRJ0                  0x007A
    .DB2    (USER_BRANCH_TABLE + 0x007C*2)          ;   INTTRJ1                             0x007C
    .DB2    (USER_BRANCH_TABLE + 0x007E*2)          ;   Software break                      0x007E
