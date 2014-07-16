-MODULE NOTIFY
-INCLUDE 'HOST.INC'
-INCLUDE 'DDT.INC'
-IN72
-STITL NOTIFY
-EJECT
*
************************************************************************
*                                                                      *
*                                                                      *
*           #     #  #######  #######  ###  #######  #     #           *
*           ##    #  #     #     #      #   #         #   #            *
*           # #   #  #     #     #      #   #          # #             *
*           #  #  #  #     #     #      #   #####       #              *
*           #   # #  #     #     #      #   #           #              *
*           #    ##  #     #     #      #   #           #              *
*           #     #  #######     #     ###  #           #              *
*                                                                      *
* NOTIFY                    NOTIFY USER                                *
*                                                                      *
************************************************************************
*
* NOTIFICATION FROM A PROCESS. JUST A WRAPPER FOR notify-send. COULD USE
* DBUS DIRECTLY. TIMEOUT IS IN MILLISECONDS. URGENCY IS LOW, NORMAL,
* CRITICAL. BODY CAN HAVE <I>, </B>, <U>, <IMG>, <A HREF>
*
         DEFINE('NOTIFY(SUMMARY,BODY,URGENCY,TIMEOUT)')    :(NOTIFY_END)
*
NOTIFY
         URGENCY = ' -u ' VDIFFER(URGENCY)
         TIMEOUT = ' -t ' VDIFFER(TIMEOUT)
         SUMMARY = ' "' SUMMARY '"'
         BODY = ' "' BODY '"'
         NOTIFY = '/usr/bin/notify-send' URGENCY TIMEOUT SUMMARY BODY
         HOST(HOST_SYSCMD, NOTIFY)                             :(RETURN)
*
NOTIFY_END
*
* CE: .MSNOBOL4;

