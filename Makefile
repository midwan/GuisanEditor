all: gce plugins execute

CFLAGS = -Iplugins -Itinyxml -Iinclude -Werror -Wall -Wno-unused `pkg-config gmodule-2.0 --cflags` `sdl-config --cflags`
LIBS =  `sdl-config --libs`  -lguichan_sdl -lguichan -lSDL_image `pkg-config gmodule-2.0 --libs`
DBG = -g -pedantic


obj/gceFileDialog.o: src/gceFileDialog.cpp include/gceFileDialog.hpp
	g++ $(DBG) -c src/gceFileDialog.cpp -o obj/gceFileDialog.o $(CFLAGS)

obj/fileio.o: src/fileio.cpp
	g++ $(DBG) -c src/fileio.cpp -o obj/fileio.o $(CFLAGS) -DTIXML_USE_STL

obj/gcebase.o: src/gcebase.cpp include/gcebase.hpp
	g++ $(DBG) -c src/gcebase.cpp -o obj/gcebase.o $(CFLAGS)

obj/gceStringList.o: src/gceStringList.cpp include/gceStringList.hpp
	g++ $(DBG) -c src/gceStringList.cpp -o obj/gceStringList.o $(CFLAGS)

obj/mouselistener.o: src/mouselistener.cpp include/mouselistener.hpp
	g++ $(DBG) -c src/mouselistener.cpp -o obj/mouselistener.o $(CFLAGS)

obj/actionlistener.o: src/actionlistener.cpp include/actionlistener.hpp
	g++ $(DBG) -c src/actionlistener.cpp -o obj/actionlistener.o $(CFLAGS)

obj/gceColourSelector.o: src/gceColourSelector.cpp include/gceColourSelector.hpp
	g++ $(DBG) -c src/gceColourSelector.cpp -o obj/gceColourSelector.o $(CFLAGS)

obj/dummylistmodel.o: src/dummyListModel.cpp include/dummyListModel.hpp
	g++ $(DBG) -c src/dummyListModel.cpp -o obj/dummylistmodel.o $(CFLAGS)

obj/tinyxml.o: tinyxml/tinyxml.cpp
	g++ -c -Wall -Wno-format $(DBG) -DDEBUG -DTIXML_USE_STL tinyxml/tinyxml.cpp -o obj/tinyxml.o 
	
obj/tinyxmlparser.o: tinyxml/tinyxmlparser.cpp
	g++ -c -Wall -Wno-format $(DBG) -DDEBUG -DTIXML_USE_STL tinyxml/tinyxmlparser.cpp -o obj/tinyxmlparser.o 

obj/tinyxmlerror.o: tinyxml/tinyxmlerror.cpp
	g++ -c -Wall -Wno-format $(DBG) -DDEBUG -DTIXML_USE_STL tinyxml/tinyxmlerror.cpp -o obj/tinyxmlerror.o 
	
obj/tinystr.o: tinyxml/tinystr.cpp
	g++ -c -Wall -Wno-format $(DBG) -DDEBUG -DTIXML_USE_STL tinyxml/tinystr.cpp -o obj/tinystr.o 

gce: src/gce.cpp obj/fileio.o obj/mouselistener.o obj/actionlistener.o include/plugin.hpp \
		obj/gceStringList.o obj/gceColourSelector.o obj/gcebase.o obj/dummylistmodel.o \
		obj/tinyxml.o obj/tinyxmlparser.o obj/tinyxmlerror.o obj/tinystr.o obj/gcecontainer.o obj/gceFileDialog.o
		
	g++ $(CFLAGS) $(LIBS) $(DBG) src/gce.cpp  obj/actionlistener.o obj/mouselistener.o obj/gceStringList.o \
		obj/gceColourSelector.o obj/fileio.o  obj/gcebase.o obj/dummylistmodel.o \
		obj/tinyxml.o obj/tinyxmlparser.o obj/tinyxmlerror.o obj/tinystr.o \
		obj/gcecontainer.o obj/gceFileDialog.o \
		-o gce


# --- plugins ---

obj/gcecontainer.o: plugins/gcecontainer.cpp plugins/gcecontainer.hpp
	g++ $(DBG) -fPIC -c plugins/gcecontainer.cpp -o obj/gcecontainer.o $(CFLAGS)

plugins/gcetextfield.plug: plugins/gcetextfield.cpp plugins/gcetextfield.hpp plugins/gcetextfieldplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gcetextfield.cpp plugins/gcetextfieldplug.cpp -o plugins/gcetextfield.plug $(LIBS) $(CFLAGS)
	
plugins/gcebutton.plug: plugins/gcebutton.cpp plugins/gcebutton.hpp plugins/gcebuttonplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gcebutton.cpp plugins/gcebuttonplug.cpp -o plugins/gcebutton.plug $(LIBS) $(CFLAGS)
	
plugins/gcelabel.plug: plugins/gcelabel.cpp plugins/gcelabel.hpp plugins/gcelabelplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gcelabel.cpp plugins/gcelabelplug.cpp -o plugins/gcelabel.plug $(LIBS) $(CFLAGS)
	
plugins/gcewindow.plug: plugins/gcewindow.cpp plugins/gcewindow.hpp plugins/gcewindowplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gcewindow.cpp plugins/gcewindowplug.cpp -o plugins/gcewindow.plug $(LIBS) $(CFLAGS)	

plugins/gcecontainer.plug: plugins/gcecontainer.cpp plugins/gcecontainer.hpp plugins/gcecontainerplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gcecontainer.cpp plugins/gcecontainerplug.cpp -o plugins/gcecontainer.plug $(LIBS) $(CFLAGS)

plugins/gceicon.plug: plugins/gceicon.cpp plugins/gceicon.hpp plugins/gceiconplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gceicon.cpp plugins/gceiconplug.cpp -o plugins/gceicon.plug $(LIBS) $(CFLAGS)

plugins/gcecheckbox.plug: plugins/gcecheckbox.cpp plugins/gcecheckbox.hpp plugins/gcecheckboxplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gcecheckbox.cpp plugins/gcecheckboxplug.cpp -o plugins/gcecheckbox.plug $(LIBS) $(CFLAGS)

plugins/gcedropdown.plug: plugins/gcedropdown.cpp plugins/gcedropdown.hpp plugins/gcedropdownplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gcedropdown.cpp plugins/gcedropdownplug.cpp -o plugins/gcedropdown.plug $(LIBS) $(CFLAGS)

plugins/gceradiobutton.plug: plugins/gceradiobutton.cpp plugins/gceradiobutton.hpp plugins/gceradiobuttonplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gceradiobutton.cpp plugins/gceradiobuttonplug.cpp -o plugins/gceradiobutton.plug $(LIBS) $(CFLAGS)

plugins/gcescrollarea.plug: plugins/gcescrollarea.cpp plugins/gcescrollarea.hpp plugins/gcescrollareaplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gcescrollarea.cpp plugins/gcescrollareaplug.cpp -o plugins/gcescrollarea.plug $(LIBS) $(CFLAGS)

plugins/gceslider.plug: plugins/gceslider.cpp plugins/gceslider.hpp plugins/gcesliderplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gceslider.cpp plugins/gcesliderplug.cpp -o plugins/gceslider.plug $(LIBS) $(CFLAGS)

plugins/gcetextbox.plug: plugins/gcetextbox.cpp plugins/gcetextbox.hpp plugins/gcetextboxplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gcetextbox.cpp plugins/gcetextboxplug.cpp -o plugins/gcetextbox.plug $(LIBS) $(CFLAGS)

plugins/gcelistbox.plug: plugins/gcelistbox.cpp plugins/gcelistbox.hpp plugins/gcelistboxplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/gcelistbox.cpp plugins/gcelistboxplug.cpp -o plugins/gcelistbox.plug $(LIBS) $(CFLAGS)

plugins/examplebutton.plug: plugins/examplebutton.cpp plugins/examplebutton.hpp plugins/examplebuttonplug.cpp include/plugin.hpp
	g++ $(DBG) -fPIC -shared plugins/examplebutton.cpp plugins/examplebuttonplug.cpp -o plugins/examplebutton.plug $(LIBS) $(CFLAGS)

#plugins/gcetabber.plug: plugins/gcetabber.cpp plugins/gcetabber.hpp plugins/gcetabberplug.cpp include/plugin.hpp
#	g++ $(DBG) -fPIC -shared plugins/gcetabber.cpp plugins/gcetabberplug.cpp -o plugins/gcetabber.plug $(LIBS) $(CFLAGS)

plugins: \
			plugins/gcebutton.plug \
			plugins/gcecontainer.plug \
			plugins/gceicon.plug \
			plugins/gcelabel.plug \
			plugins/gcewindow.plug \
			plugins/gcescrollarea.plug \
			plugins/gcetextbox.plug \
			plugins/gcetextfield.plug \
			plugins/gcecheckbox.plug \
			plugins/gceradiobutton.plug \
			plugins/gceslider.plug \
			plugins/gcelistbox.plug \
			plugins/gcedropdown.plug \
			plugins/examplebutton.plug

#			plugins/gcetabber.plug \


	

clean:
	rm -f obj/*.o
	rm -f plugins/*.plug
	rm -f gce
	rm -f *~
	rm -f plugins/*~
	rm -f src/*~
	rm -f include/*~
	rm -f core

execute: gce
	./gce
	
