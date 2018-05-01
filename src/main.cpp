static const char * const normalize_xpm[] = {
"12 12 2 1",
"# c #000000",
". c None",
"............",
"....######..",
"....######..",
"....#....#..",
"..######.#..",
"..######.#..",
"..#....###..",
"..#....#....",
"..#....#....",
"..######....",
"............",
"............"};

#include <qapplication.h>
#include "os.h"

#ifdef OS_WIN
#include <qpixmap.h>
#include <qpopupmenu.h>
#include "trayicon.h"
#endif

#ifdef OS_UNIX
#include<signal.h>
#endif

#include "ctdrive.h"

int main( int argc, char ** argv )
{

#ifdef OS_UNIX
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigaction( SIGPIPE, &sa, 0 );
#endif

	//QCtDrive drive( argc, argv );//2016.11.18
	#ifdef OS_WIN 
	QCtDrive drive( argc, argv ); 
	#else 
	QCtDrive drive( argc, argv, QApplication::Tty ); 
	#endif 

#ifdef OS_WIN	
	QPopupMenu menu;
     menu.insertItem( "&Quit", &drive, SLOT(quit()) );
    TrayIcon tray( QPixmap( (const char**)normalize_xpm ), "modbusRTU Drive", &menu );
 	tray.show();
#endif			
	drive.connect( &drive, SIGNAL(lastWindowClosed()), &drive, SLOT(quit()) );
    return drive.exec();
}
