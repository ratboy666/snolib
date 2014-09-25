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
* CRITICAL. BODY CAN HAVE <I>, <B>, <U>, <IMG>, <A HREF> MARKUP.
* URGENCY CRITICAL NEEDS TO BE DISMISSED BY THE USER. LOW AND NORMAL
* GO AWAY AFTER TIMEOUT. TESTED WITH GNOME 3 AND XFCE.
*
         DEFINE('NOTIFY(SUMMARY,BODY,URGENCY,TIMEOUT)')    :(NOTIFY_END)
*
NOTIFY   HOST(HOST_GETENV, 'DBUS_SESSION_BUS_ADDRESS')        :F(RETURN)
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

