CFLAGS = -Iplugins -I../tinyxml -Werror -Wall -Wno-unused `pkg-config gmodule-2.0 --cflags` `sdl-config --cflags`
LIBS =  `sdl-config --libs`  -lguichan_sdl -lguichan -lSDL_image `pkg-config gmodule-2.0 --libs`

all: plugins example

plugins/gcebutton.plug: plugins/gcebuttonplug.cpp
	g++ -g -fPIC -shared plugins/gcebuttonplug.cpp -o plugins/gcebutton.plug $(LIBS) $(CFLAGS)

plugins/gcecontainer.plug: plugins/gcecontainerplug.cpp
	g++ -g -fPIC -shared plugins/gcecontainerplug.cpp -o plugins/gcecontainer.plug $(LIBS) $(CFLAGS)

plugins/gcecheckbox.plug: plugins/gcecheckboxplug.cpp
	g++ -g -fPIC -shared plugins/gcecheckboxplug.cpp -o plugins/gcecheckbox.plug $(LIBS) $(CFLAGS)

plugins/gcedropdown.plug: plugins/gcedropdownplug.cpp
	g++ -g -fPIC -shared plugins/gcedropdownplug.cpp -o plugins/gcedropdown.plug $(LIBS) $(CFLAGS)

plugins/gceicon.plug: plugins/gceiconplug.cpp
	g++ -g -fPIC -shared plugins/gceiconplug.cpp -o plugins/gceicon.plug $(LIBS) $(CFLAGS)

plugins/gcelabel.plug: plugins/gcelabelplug.cpp
	g++ -g -fPIC -shared plugins/gcelabelplug.cpp -o plugins/gcelabel.plug $(LIBS) $(CFLAGS)

plugins/gcelistbox.plug: plugins/gcelistboxplug.cpp
	g++ -g -fPIC -shared plugins/gcelistboxplug.cpp -o plugins/gcelistbox.plug $(LIBS) $(CFLAGS)

plugins/gceradiobutton.plug: plugins/gceradiobuttonplug.cpp
	g++ -g -fPIC -shared plugins/gceradiobuttonplug.cpp -o plugins/gceradiobutton.plug $(LIBS) $(CFLAGS)

plugins/gcescrollarea.plug: plugins/gcescrollareaplug.cpp
	g++ -g -fPIC -shared plugins/gcescrollareaplug.cpp -o plugins/gcescrollarea.plug $(LIBS) $(CFLAGS)

plugins/gceslider.plug: plugins/gcesliderplug.cpp
	g++ -g -fPIC -shared plugins/gcesliderplug.cpp -o plugins/gceslider.plug $(LIBS) $(CFLAGS)

plugins/gcetextbox.plug: plugins/gcetextboxplug.cpp
	g++ -g -fPIC -shared plugins/gcetextboxplug.cpp -o plugins/gcetextbox.plug $(LIBS) $(CFLAGS)

plugins/gcetextfield.plug: plugins/gcetextfieldplug.cpp
	g++ -g -fPIC -shared plugins/gcetextfieldplug.cpp -o plugins/gcetextfield.plug $(LIBS) $(CFLAGS)

plugins/gcewindow.plug: plugins/gcewindowplug.cpp
	g++ -g -fPIC -shared plugins/gcewindowplug.cpp -o plugins/gcewindow.plug $(LIBS) $(CFLAGS)

plugins/examplebutton.plug: plugins/examplebuttonplug.cpp plugins/examplebutton.hpp plugins/examplebutton.cpp
	g++ -g -fPIC -shared plugins/examplebutton.cpp plugins/examplebuttonplug.cpp -o plugins/examplebutton.plug $(LIBS) $(CFLAGS)

		

plugins:  \
			plugins/gcebutton.plug \
			plugins/gcecontainer.plug \
			plugins/gcecheckbox.plug \
			plugins/gceicon.plug \
			plugins/gcelabel.plug \
			plugins/gcelistbox.plug \
			plugins/gceradiobutton.plug \
			plugins/gcescrollarea.plug \
			plugins/gceslider.plug \
			plugins/gcetextbox.plug \
			plugins/gcetextfield.plug \
			plugins/gcewindow.plug \
			plugins/gcedropdown.plug \
			plugins/examplebutton.plug 

obj/tinyxml.o: ../tinyxml/tinyxml.cpp
	g++ -c -Wall -Wno-format -g -DDEBUG -DTIXML_USE_STL ../tinyxml/tinyxml.cpp -o obj/tinyxml.o 
	
obj/tinyxmlparser.o: ../tinyxml/tinyxmlparser.cpp
	g++ -c -Wall -Wno-format -g -DDEBUG -DTIXML_USE_STL ../tinyxml/tinyxmlparser.cpp -o obj/tinyxmlparser.o 

obj/tinyxmlerror.o: ../tinyxml/tinyxmlerror.cpp
	g++ -c -Wall -Wno-format -g -DDEBUG -DTIXML_USE_STL ../tinyxml/tinyxmlerror.cpp -o obj/tinyxmlerror.o 
	
obj/tinystr.o: ../tinyxml/tinystr.cpp
	g++ -c -Wall -Wno-format -g -DDEBUG -DTIXML_USE_STL ../tinyxml/tinystr.cpp -o obj/tinystr.o 

obj/loader.o: loader.cpp 
	g++ -c -g $(CFLAGS)  -DTIXML_USE_STL loader.cpp -o obj/loader.o

example: example.cpp obj/loader.o obj/tinystr.o obj/tinyxmlerror.o obj/tinyxmlparser.o obj/tinyxml.o
	g++ $(CFLAGS) $(LIBS) -g example.cpp obj/loader.o obj/tinystr.o obj/tinyxmlerror.o \
								obj/tinyxmlparser.o obj/tinyxml.o -o example
	

clean:
	rm -f obj/*.o
	rm -f plugins/*.plug
	rm -f example
	rm -f *~
	rm -f plugins/*~
	rm -f src/*~
	rm -f core


