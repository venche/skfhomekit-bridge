
# build helloworld executable when user executes "make"

#helloworld: helloworld.o
#	$(CXX) $(LDFLAGS) helloworld.o -o helloworld
#helloworld.o: helloworld.cpp
#	$(CXX) $(CXXFLAGS) -c helloworld.cpp

#-O2  for permisive error
parentder=Personal-HomeKit-HAP-master
LINK = -lssl -lcrypto -lpthread -ldl -ldns_sd
#LINK = -lssl -lcrypto -lpthread -ldl libavahi-compat-libdnssd
#libavahi-compat-libdnssd
#+libavahi-common +libavahi-client +libdbus 
#LINK = -lssl -lcrypto -ldl -lpthread 
#CFLAGS += -Os -s
CFLAG = -Os -s
CFLAGS += -Os -s
#CPPFLAGS="-I/media/venu/Backup/openwrt_development/openwrt_mips_ar9331_nodejs/openwrtsource/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/include -I/media/venu/Backup/openwrt_development/openwrt_mips_ar9331_nodejs/openwrtsource/staging_dir/target-mips_r2_uClibc-0.9.33.2/include -I/media/venu/Backup/openwrt_development/openwrt_mips_ar9331_nodejs/openwrtsource/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/usr/include -I/media/venu/Backup/openwrt_development/openwrt_mips_ar9331_nodejs/openwrtsource/staging_dir/toolchain-mips_r2_gcc-4.6-linaro_uClibc-0.9.33.2/include "

#CXXFLAGS += -I/media/venu/Backup/openwrt_development/openwrt_mips_ar9331_nodejs/openwrtsource/staging_dir/target-mips_r2_uClibc-0.9.33.2/usr/include/avahi-compat-libdns_sd/

CXXFLAGS = -I/home/amar/venuWorkspace/openwrtsource/staging_dir/target-mips_34kc_uClibc-0.9.33.2/usr/include/avahi-compat-libdns_sd/

PHK_LIBNAME=libphk
#LINK +=  -ldns_sd
PHK_LIBFILE=$(PHK_LIBNAME).so

OBJFILE = ${parentder}/chacha20.o ${parentder}/curve25519.o ${parentder}/ed25519.o ${parentder}/poly1305.o ${parentder}/rfc6234-master/hkdf.o ${parentder}/rfc6234-master/hmac.o ${parentder}/rfc6234-master/sha.o ${parentder}/main.o ${parentder}/PHKAccessory.o ${parentder}/PHKControllerRecord.o ${parentder}/PHKNetworkIP.o ${parentder}/PHKArduinoLightInterface.o ${parentder}/srp/srp.o ${parentder}/srp/cstr.o ${parentder}/srp/t_math.o ${parentder}/srp/srp6_server.o ${parentder}/srp/t_conf.o ${parentder}/srp/t_conv.o ${parentder}/srp/t_pw.o ${parentder}/srp/t_misc.o  ${parentder}/srp/t_truerand.o ${parentder}/srp/t_read.o ${parentder}/Accessory.o ${parentder}/SKFBridgedAccessory.o

#@echo $(Foo)

all: PHK
PHK: $(OBJFILE)	
	 $(CXX) $(CFLAG) $(LDFLAGS) -o PHK $(OBJFILE) $(LINK)  -L/home/venu/work/Development/openwrt_development/OpenWrt-SDK-ar71xx-for-linux-i486-gcc-4.6-linaro_uClibc-0.9.33.2/staging_dir/target-mips_r2_uClibc-0.9.33.2/root-ar71xx/usr/lib
#$(CXX) $(CXXFLAGS)  $(LINK)  $(LDFLAGS) -o PHK $(OBJFILE)        
phklib: PHK
	$(CXX) $(CXXFLAG) -dynamiclib $(LINK) $(LDFLAGS) -o $(PHK_LIBFILE) $(PHK_OBJFILES)
	#$(CXX) $(CXXFLAGS) -static $(LINK)  -dynamiclib -ldns_sd  $(LDFLAGS) -o $(PHK_LIBFILE) $(PHK_OBJFILES)
${parentder}/chacha20.o: ${parentder}/Chacha20/chacha20_simple.c ${parentder}/Chacha20/chacha20_simple.h
	$(CC) $(CFLAG) $(CFLAGS) -w -o ${parentder}/chacha20.o -c ${parentder}/Chacha20/chacha20_simple.c
${parentder}/curve25519.o: ${parentder}/curve25519/curve25519-donna.c ${parentder}/curve25519/curve25519-donna.h
	$(CC) $(CFLAG) $(CFLAGS)  -w -o ${parentder}/curve25519.o -c ${parentder}/curve25519/curve25519-donna.c
${parentder}/ed25519.o: ${parentder}/ed25519-donna/ed25519.c ${parentder}/ed25519-donna/ed25519.h
	$(CC) $(CFLAG) $(CFLAGS) -w -o ${parentder}/ed25519.o -c ${parentder}/ed25519-donna/ed25519.c
${parentder}/poly1305.o: ${parentder}/poly1305-opt-master/poly1305.c ${parentder}/poly1305-opt-master/poly1305.h
	$(CC) $(CFLAG) $(CFLAGS) -w -o ${parentder}/poly1305.o -c ${parentder}/poly1305-opt-master/poly1305.c
${parentder}/rfc6234-master/%.o: ${parentder}/rfc6234-master/%.c
	$(CC) $(CFLAG)  $(CFLAGS) -w -c $< -o $@
${parentder}/srp/%.o: ${parentder}/srp/%.c
	$(CC) $(CFLAG)  $(CFLAGS) -w -c $< -o $@
	#$(CC) $(CFLAGS) -lcrypto -w -c $< -o $@	
${parentder}/%.o: ${parentder}/%.cpp
	$(CXX) $(CXXFLAGS) -w -c $<  -o $@
	#$(CXX) $(CFLAGS) -w -c $<  -o $@

# remove object files and executable when user executes "make clean"
clean:
	rm -rf ${parentder}/*.o ${parentder}/Chacha20/*.o ${parentder}/curve25519/*.o ${parentder}/ed25519-donna/*.o ${parentder}/poly1305-opt-master/*.o ${parentder}/rfc6234-master/*.o ${parentder}/srp/*.o ${parentder}/PHK ${parentder}/$(PHK_LIBFILE)  PHK

#LDFLAGS  += --rpath-link /home/venu/work/Development/openwrt_development/OpenWrt-SDK-ar71xx-for-Linux-i686-gcc-4.3.3+cs_uClibc-0.9.30.1/staging_dir/target-mips_r2_uClibc-0.9.30.1/root-ar71xx/lib/ld-uClibc.so.0

